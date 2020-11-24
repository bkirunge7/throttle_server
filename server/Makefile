CXX = g++ CXXFLAGS =
    -Wall - Werror - Wextra - pedantic - std =
        c++ 11 - g - fsanitize =
            address - pthread LDFLAGS = -fsanitize = address SRC =
                main.cpp UserQuota.cpp ThrottleServer.cpp RequestHandler
                    .cpp TokenBucket.cpp TokenProcessor.cpp OBJ =
                    $(SRC
                      : .cc = .o) EXEC = throttleserver all : $(EXEC) $(EXEC)
    : $(OBJ) $(CXX) $(LDFLAGS) - o $ @$(OBJ) $(LBLIBS) clean : rm - rf $(OBJ)
                                                               $(EXEC)