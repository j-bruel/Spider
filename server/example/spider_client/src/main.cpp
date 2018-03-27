//
// Created by brd6 on 03/10/17.
//

#include <cstdlib>
#include "Network/ClientNetwork.hpp"

int main(int ac, char const **av)
{
//  ts::ClientNetwork clientNetwork("127.0.0.1", 4242);
  ts::ClientNetwork clientNetwork("192.168.0.46", 4242);

  clientNetwork.run();

  return EXIT_SUCCESS;
}