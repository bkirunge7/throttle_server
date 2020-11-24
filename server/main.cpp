//
//  main.cpp
//  ThrottleServer 
//
//  Created by Basavaraj Kirunge on 11/22/20.
//  Copyright © 2020 Basavaraj Kirunge. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include "ThrottleServer.hpp"

const int port = 8077;
// Load User Quota Config file
// user1:10
bool loadConfig(const std::string &quotaConfFile, UserQuota &u) {
  std::ifstream quotaf;
  quotaf.open(quotaConfFile);
  if (!quotaf) {
    std::cerr << "Unable to open file" << std::endl;
    return false;
  }
  std::string line;
  while (getline(quotaf, line)) {
    size_t pos = line.find(":");
    if (pos == std::string::npos) {
      std::cerr << "Error Parsing file" << std::endl;
      return false;
    }
    std::string user = line.substr(0, pos);
    std::string slimit = line.substr(pos + 1, line.length());
    std::stringstream lm(slimit);
    int limit = 0;
    lm >> limit;
    u.addUser(user, limit);
  }
  quotaf.close();
  return true;
}
// Start Throttling server

int main(int argc, char const *argv[]) {
  UserQuota uquota;
  if (argc < 2) {
    std::cerr << "Usage: throtlleserver <quota.cnf>" << std::endl;
    exit(1);
  }
  std::string quotaConfFile = argv[1];
  if (!loadConfig(quotaConfFile, uquota)) {
    std::cerr << "Failed to load config" << std::endl;
    exit(1);
  }
  ThrottleServer server(uquota);
  server.run(port);

  return 0;
}
