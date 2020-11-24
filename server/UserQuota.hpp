//
//  UserQuota.hpp
//  ThrottleServer
//
//  Created by Basavaraj Kirunge on 11/23/20.
//  Copyright © 2020 Basavaraj Kirunge. All rights reserved.
//

#ifndef UserQuota_hpp
#define UserQuota_hpp

#include <map>
#include <string>

class UserQuota {
 public:
  std::map<std::string, int> quota;
  std::map<std::string, int> active;
  void addUser(const std::string &user, const int &limit);
};
#endif /* UserQuota_hpp */
