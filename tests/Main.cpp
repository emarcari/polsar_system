/*!
  \file main.cpp

  \brief Simple code for calling another test files.

  \author Etore Marcari Jr. <etore@dpi.inpe.br>
*/

// Local
#include "NumericalTests.h"
#include "TerralibTests.h"

// TerraLib
#include <common.h>

int main( int argc, char* argv[] ) {
  try {
    std::cout << "Loading Terralib...";
    TerraLib::getInstance().initialize();
    std::cout << " done" << std::endl;

    run_numerical_tests();
    run_terralib_tests();
    
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
