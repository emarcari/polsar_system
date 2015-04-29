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

    // @todo - etore - Change it to extract raster and bands as reference
    std::vector<std::pair<te::rst::Raster*,size_t>>
      rasterInfo = polsarsystem::util::extractRastersFromArgs( argc, argv );

    std::string outputPrefix =
      polsarsystem::util::extractOutputPrefixFromArgs( argc, argv );

    std::vector<te::rst::Raster*> inputRasters;
    std::vector<size_t> inputBands;

    for( size_t i = 0; i < rasterInfo.size(); ++i ) {
      inputRasters.push_back( rasterInfo[i].first );
      inputBands.push_back( rasterInfo[i].second );
    }

    std::map<std::string, std::string> outRasterInfo;
    outRasterInfo["URI"] = outputPrefix;

    std::auto_ptr< te::rst::Raster > outDiskRasterPtr;    

    bool result = te::rp::radar::CreateCovarianceRaster( inputRasters, inputBands, 
							 outRasterInfo,
							 "GDAL", outDiskRasterPtr );
    
    
    if( result ) {
      std::cout << "processing ok" << std::endl;
    } else {
      std::cout << "error in processing" << std::endl;
    }
    
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
