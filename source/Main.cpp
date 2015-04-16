/*!
  \file main.cpp

  \brief Main program.

  \author Etore Marcari Jr. <etore@dpi.inpe.br>
*/

// TerraLib
#include <common.h>

// Local
#include "LoadModules.h"

int main( int argc, char* argv[] ) {
  try {
    // load terralib
    std::cout << "Loading Terralib...";
    TerraLib::getInstance().initialize();
    std::cout << " done" << std::endl;

    // load modules
    LoadModules();

    // do the job



    /*
    std::map<std::string, std::string> inputRasterInfo;
    inputRasterInfo["URI"] = TERRALIB_DATA_DIR "/rasters/cbers2b_rgb342_crop.tif";

    boost::shared_ptr< te::rst::Raster > inputRasterPointer ( te::rst::RasterFactory::open(
											   inputRasterInfo ) );
    CPPUNIT_ASSERT( inputRasterPointer.get() );
    */


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
