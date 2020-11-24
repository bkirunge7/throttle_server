//
//  ThrottleServer.hpp
//  httpServer
//
//  Created by Basavaraj Kirunge on 11/22/20.
//  Copyright © 2020 Basavaraj Kirunge. All rights reserved.
//

#ifndef ThrottleServer_hpp
#define ThrottleServer_hpp

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <thread>
#include "UserQuota.hpp"

class ThrottleServer {
  UserQuota uquota;

 public:
  ThrottleServer(UserQuota &u) : uquota(u) {};
  void run(int port);
};
#endif /* ThrottleServer_hpp */
