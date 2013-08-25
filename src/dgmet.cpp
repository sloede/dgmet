#include <cstdlib>
#include <iostream>

#include "dgmet/aux/globals.hpp"

int main(int argc, char* argv[]) {
  using namespace dgmet;
  Int ndim = 2;
  Num fraction = static_cast<Num>(ndim) / ndim_max;

  std::cout << "ndim = " << ndim << ", ndim_max = " << ndim_max
            << ", fraction = " << fraction << std::endl;

  return EXIT_SUCCESS;
}
