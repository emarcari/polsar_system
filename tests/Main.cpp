/*!
  \file main.cpp

  \brief Simple code for calling another test files.

  \author Etore Marcari Jr. <etore@dpi.inpe.br>
*/

// Local
#include "LoadModules.h"
#include "MultiResolutionTests.h"
#include "NumericalTests.h"
#include "RadarFunctionsTests.h"
#include "TerralibMathTests.h"

// TerraLib
#include <common.h>

int main( int argc, char* argv[] ) {
  try {
    std::cout << "Loading Terralib...";
    TerraLib::getInstance().initialize();
    LoadModules();
    std::cout << " done" << std::endl;

    run_multiresolution_tests();
    run_numerical_tests();
    run_radarfunctions_tests();
    run_terralib_math_tests();

    std::cout << "Closing Terralib...";
    TerraLib::getInstance().finalize();
    std::cout << " done" << std::endl;

    system("pause");

  } catch( const std::exception& exc ) {
    std::cout << "Exception found :" << exc.what() << std::endl;
    return EXIT_FAILURE;
  } catch( ... ) {
    std::cout << "Unknown exception!" << std::endl;
    return EXIT_FAILURE;
  }
	
  return EXIT_SUCCESS;
}
