# Throttling Server
  Its Based on Token Bucket Algorithm, should be run as a service (daemon)
  Uses quota.cnf file to initialize with max number of tokens allowed per second
  Every second User's Bucket are filled with allowed max tokens per second.
  When a request recieved for GetToken from client, Bucket is checked if there 
  are any available tokens, if no tokens then return "Deny" else decrement number of
  tokens by 1 and respond as "Allow".

  Runs on Port 8077 
  Request Format:  "GetToken UserName"
  Respone Format:  "Allow" 
                   "Deny"


# Pre-requisites

  1. cmake --version
   cmake version 3.19.0

  2. gcc --version
   gcc (GCC) 4.8.5 20150623 (Red Hat 4.8.5-28)
  
  3. c++ 11 or higher

# Dir Structure

  1. Source files: throttleserver/server

  2. Config file : throttleserver/quota.cnf

  3. Client tool src : throttleserver/server/generate_throttle_request.cpp

    
# Build

  1. Generate cmake build files  

     $cd throttleserver  
     $cmake server

  2. Build  throttleserver and generate_throttle_request client tool

     $cd throttleserver
     $cmake --build . 

# Run and Test

   1. Prepare quota.cnf file

      <User>:<max_tokens_per_second>  
      sample below
      $cat quota.cnf
      John:5
      Amit:15
      Peter:5
      Bob:10
      Eve:5
      Tom:20

   2. Run throttles server

      $cd throttleserver 
      $./throttleserver 
      Usage: throtlleserver <quota.cnf>
      $./throttleserver

   3. Run client tool
      
      ./generate_throttle_request 
      Usage: generate_request <user> <request_count_per_sec>
      
      Send 50 requests per second for user Tom
      ./generate_throttle_request Tom 50
      
      Sample output
      [root@dev throttle_server]# ./generate_throttle_request Bob 50
      Generating Request for User:Bob Request Count:50
      [Bob] Allow
      [Bob] Allow
      [Bob] Allow
      [Bob] Allow
      [Bob] Allow
      [Bob] Allow
      [Bob] Allow
      [Bob] Allow
      [Bob] Allow
      [Bob] Allow
      [Bob] Deny
