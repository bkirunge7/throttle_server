//
//  RequestHandler.hpp
//  ThrottleServer
//
//  Created by Basavaraj Kirunge on 11/23/20.
//  Copyright © 2020 Basavaraj Kirunge. All rights reserved.
//

#ifndef RequestHandler_hpp
#define RequestHandler_hpp

#include <iostream>
#include "UserQuota.hpp"

class RequestHandler {
  std::string read_request(const int &client_sock);
  void send_response(const int &client_sock, const std::string &resp);

 public:
  void operator()(const int &client_sock, UserQuota &uquota);
};
#endif /* RequestHandler_hpp */
