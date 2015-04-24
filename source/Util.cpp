/*!
  \file Util.cpp
  \brief Some useful functions for polsar system.
*/

// Local
#include "Util.h"

namespace polsarsystem {
  namespace util {

    std::vector<std::pair<te::rst::Raster*,size_t>>
    extractRastersFromArgs( int argc, char* argv[] ) {
      std::vector<std::pair<te::rst::Raster*,size_t>> vec;

      if( argc < 4 ) {
	std::cout << "Please check input command line." << std::endl;
	return vec;
      }

      for( int i = 1; i < ( argc - 1 ); i += 2 ) {
	std::string rasterName = "NONE";
	size_t rasterBand = 0;
	
	try {
	  rasterName = argv[i];
	  rasterBand = fromString<size_t>( argv[i+1] );
	  
	  std::map<std::string, std::string> inputRasterInfo;
	  inputRasterInfo["URI"] = rasterName;

	  te::rst::Raster*
	    inputRasterPointer( te::rst::RasterFactory::open( inputRasterInfo ));

	  assert( inputRasterPointer );

	  vec.push_back( std::make_pair<te::rst::Raster*,size_t>( inputRasterPointer,
								  rasterBand ));

	} catch( ... ) {
	  std::cout << "Error loading input raster file " << rasterName << std::endl;
	  throw( "Aborting." );
	}
      }

      return vec;
    }

    std::string extractOutputPrefixFromArgs( int argc, char* argv[] ) {
      return std::string( argv[argc-1] );
    }
  } // end namespace polsarsystem
} // end namespace util
