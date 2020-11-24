//
//  TokenBucket.cpp
//  ThrottleServer
//
//  Created by Basavaraj Kirunge on 11/23/20.
//  Copyright © 2020 Basavaraj Kirunge. All rights reserved.
//

#include "TokenBucket.hpp"
#include "TokenProcessor.hpp"
// Start a thread for every user and reset available tokens every secondls
//      Tom        Bob
//   |        |  |       |
//    | **** |    | *** |
//     | ** |      | * |
//       ---        ---
void TokenBucket::operator()(UserQuota &usermap) {
  while (1) {
    for (auto i = usermap.active.begin(); i != usermap.active.end(); i++) {
      //       std::cout<<i->first <<"  "<<i->second <<" "<<std::endl;
      std::thread processor = std::thread(TokenProcessor(), std::ref(i->second),
                                          usermap.quota[i->first]);
      processor.join();
    }
  }
}
