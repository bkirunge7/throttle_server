//
//  ThrottleServer.cpp
//  ThrottleServer
//
//  Created by Basavaraj Kirunge on 11/23/20.
//  Copyright © 2020 Basavaraj Kirunge. All rights reserved.
//

#include "ThrottleServer.hpp"
#include "TokenBucket.hpp"
#include "RequestHandler.hpp"
#include <vector>

void ThrottleServer::run(int port) {
  int server_fd;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  // Start TokenBucket thread pool that creates a thread for each user
  // Each user thread keep filling Bucket with max tokens allowed per second
  std::thread thread1 = std::thread(TokenBucket(), std::ref(uquota));

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    std::cerr << "socket call failed" << std::endl;
    exit(1);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  std::cout << std::endl << "Throttle Server Listening on Port [" << port << "]"
            << std::endl;
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    std::cerr << "bind failed" << std::endl;
    exit(1);
  }
  if (listen(server_fd, 10) < 0) {
    std::cerr << "Socket listen failed" << std::endl;
    exit(1);
  }

  while (1) {
    int new_socket = 0;

    // std::cout<<"\n+++++++ Waiting for new connection ++++++++\n\n";
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0) {
      std::cerr << "Socket accept failed" << std::endl;
      exit(1);
    }
    // Pass on to Request Handler

    std::thread requestHander =
        std::thread(RequestHandler(), std::ref(new_socket), std::ref(uquota));

    if (requestHander.joinable()) {
      requestHander.join();
    }
  }
}
