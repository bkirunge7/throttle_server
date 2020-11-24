//
//  TokenProcessor.hpp
//  httpServer
//
//  Created by Basavaraj Kirunge on 11/22/20.
//  Copyright © 2020 Basavaraj Kirunge. All rights reserved.
//

#ifndef TokenProcessor_hpp
#define TokenProcessor_hpp
#include <unistd.h>

class TokenProcessor {
 public:
  void operator()(int &token, const int &limit);
};
#endif /* TokenProcessor_hpp */
