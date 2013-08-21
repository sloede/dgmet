#include <cstdlib>
#include <iostream>

#include "dgmet/aux/globals.h"

int main(int argc, char* argv[]) {
  Int nDim = 2;
  Num fraction = nDim / nDimMax;

  std::cout << "nDim = " << nDim << ", nDimMax = " << nDimMax << ", fraction = "
            << fraction << std::endl;

  return EXIT_SUCCESS;
}
