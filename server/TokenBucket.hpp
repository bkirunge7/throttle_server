//
//  TokenBucket.hpp
//  httpServer
//
//  Created by Basavaraj Kirunge on 11/22/20.
//  Copyright © 2020 Basavaraj Kirunge. All rights reserved.
//

#ifndef TokenBucket_hpp
#define TokenBucket_hpp
#include <thread>
#include <iostream>
#include "UserQuota.hpp"

/*  Uses Token bucket Algorithm
 */

class TokenBucket {

 public:
  void operator()(UserQuota &userquota);
};

#endif /* TokenBucket_hpp */
