//
//  UserQuota.cpp
//  httpServer
//
//  Created by Basavaraj Kirunge on 11/22/20.
//  Copyright © 2020 Basavaraj Kirunge. All rights reserved.
//

#include "UserQuota.hpp"

void UserQuota::addUser(const std::string &user, const int &limit) {
  quota[user] = limit;
  active[user] = limit;
}
