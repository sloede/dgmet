#include <cstdlib>
#include <iostream>

#include "dgmet/aux/globals.hpp"

int main(int argc, char* argv[]) {
  using namespace dgmet;
  Int nDim = 2;
  Num fraction = static_cast<Num>(nDim) / nDimMax;

  std::cout << "nDim = " << nDim << ", nDimMax = " << nDimMax << ", fraction = "
            << fraction << std::endl;

  return EXIT_SUCCESS;
}
