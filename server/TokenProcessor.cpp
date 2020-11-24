//
//  TokenProcessor.cpp
//  httpServer
//
//  Created by Basavaraj Kirunge on 11/22/20.
//  Copyright © 2020 Basavaraj Kirunge. All rights reserved.
//

#include "TokenProcessor.hpp"
void TokenProcessor::operator()(int &token, const int &limit) {
  sleep(1);
  token = limit;
}
