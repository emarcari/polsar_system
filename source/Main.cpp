/*!
  \file main.cpp

  \brief Main program.

  \author Etore Marcari Jr. <etore@dpi.inpe.br>
*/

// Local
#include "terralib/RadarFunctions.h"

#include "LoadModules.h"
#include "Util.h"

// TerraLib
#include <common.h>

// Boost
#include <boost/shared_ptr.hpp>

int main( int argc, char* argv[] ) {
  try {
    // load terralib
    std::cout << "Loading Terralib...";
    TerraLib::getInstance().initialize();
    std::cout << " done" << std::endl;

    // load modules
    LoadModules();

    std::vector<std::pair<te::rst::Raster*,size_t>>
      raster_info = polsarsystem::util::extractRastersFromArgs( argc, argv );

    std::string outputPrefix =
      polsarsystem::util::extractOutputPrefixFromArgs( argc, argv );

    



    

    // close terralib
    std::cout << "Closing Terralib...";
    TerraLib::getInstance().finalize();
    std::cout << " done" << std::endl;

    // Just a pause to allow screen analysis
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
