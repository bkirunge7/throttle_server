//
//  RequestHandler.cpp
//  ThrottleServer
//
//  Created by Basavaraj Kirunge on 11/23/20.
//  Copyright © 2020 Basavaraj Kirunge. All rights reserved.
//
#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>
#include <sstream>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

const string THROTTLE_SERVER = "127.0.0.1";
const int PORT = 8077;

class Client {
  string server;
  int port;
  int sock;
  long valread;
  struct sockaddr_in serv_addr;

 public:
  Client(const string &server_host, const int &server_port)
      : server(server_host), port(server_port) {}
  int get_socket() {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      cerr << "Socket creation error" << endl;
      return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, server.c_str(), &serv_addr.sin_addr) <= 0) {
      cerr << "Invalid address" << endl;
      return -1;
    }
    return 0;
  }
  int getToken(const string &user, string &resp) {
    if (get_socket() != 0) {
      cerr << "Issue initializing socket " << endl;
      return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
      cerr << "Connection Failed" << endl;
      return -1;
    }
    char buffer[1024] = {0};
    // Send GetToken Request
    // Prepare Request
    string req = string("GetToken") + string(" ") + user;

    send(sock, req.c_str(), req.length(), 0);
    valread = read(sock, buffer, 1024);
    resp = string(buffer);
    close(sock);

    return 0;
  }
};

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    cout << "Usage: generate_request <user> <request_count_per_sec>" << endl;
    exit(1);
  }
  string user = argv[1];
  string count = argv[2];
  stringstream ss(count);
  unsigned reqCount = 0;
  ss >> reqCount;
  cout << "Generating Request for User:" << user
       << " Request Count:" << reqCount << endl;

  // Calculate sleep time to add to send n requests in one second
  unsigned sleepTime = 1000000 / reqCount;

  Client cl(THROTTLE_SERVER, PORT);

  for (int i = 0; i < reqCount; i++) {
    usleep(sleepTime);
    string resp;
    if (cl.getToken(user, resp) != 0) {
      cerr << "Faile to send request" << endl;
    } else {
      cout << "[" << user << "] " << resp << endl;
    }
  }
}
