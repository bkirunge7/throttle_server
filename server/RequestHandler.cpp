//
//  RequestHandler.cpp
//  ThrottleServer
//
//  Created by Basavaraj Kirunge on 11/23/20.
//  Copyright © 2020 Basavaraj Kirunge. All rights reserved.
//

#include "RequestHandler.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

// Handles client request
// Checks available tokens for user and return allow or deny
std::string RequestHandler::read_request(const int &client_sock) {
  char buffer[60] = {0};
  long valread = read(client_sock, buffer, 60);
  std::cout << "Recieved Request [" << buffer << "] " << std::endl;
  return buffer;
}
void RequestHandler::send_response(const int &client_sock,
                                   const std::string &resp) {
  write(client_sock, resp.c_str(), resp.length());
}
void RequestHandler::operator()(const int &client_sock, UserQuota &uquota) {

  std::string resp = "Deny";
  std::string request = read_request(client_sock);

  unsigned pos = request.find(" ");
  if (pos == std::string::npos || !(request.substr(0, pos) == "GetToken")) {
    std::cerr << "Invalid Request Format" << std::endl;
    resp = "Invalid Request Format";
  } else {
    std::string user = request.substr(pos + 1, request.length());

    auto i = uquota.active.find(user);
    if (i != uquota.active.end()) {
      // Check if tokens available in Bucket
      // Need to protect token counter with lock, but mostly will not lead to
      // any severe effect
      // at the most client might send 1 request less than max allowed.
      if (i->second > 0) {
        std::cout << "user :" << user
                  << " token quota available:" << uquota.active[user]
                  << std::endl;
        --i->second;
        resp = "Allow";
      }
    }
  }
  send_response(client_sock, resp);
  close(client_sock);
}
