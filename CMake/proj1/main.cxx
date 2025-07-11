// A simple program that computes the square root of a number
#include <cmath>
#include <cstdlib> // TODO 5: Remove this line
#include <iostream>
#include <string>

#include "proj1Config.h"
#include "Mathlib.h"

// TODO 11: Include TutorialConfig.h

int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cout << argv[0] << " Version " << proj1_VERSION_MAJOR << "."
              << proj1_VERSION_MINOR << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }

  // convert input to double
  // TODO 4: Replace atof(argv[1]) with std::stod(argv[1])
  const double inputValue = atof(argv[1]);

  // calculate square root
  const double outputValue = mysqrt(inputValue);
  std::cout << "The square root of " << inputValue << " is " << outputValue
            << std::endl;
  return 0;
}

