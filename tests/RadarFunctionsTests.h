/*!
  \file RadarFunctionsTests.h

  \brief Simple code for testing the radar functions.

  \author Etore Marcari Jr. <etore@dpi.inpe.br>
*/

#include "../source/terralib/RadarFunctions.h"

#include <Raster.h>

#include "Common.h"

void create_covariance_test() {
  std::cout << "Running radar functions (covariance) tests... ";

  // openning input raster
  std::map<std::string, std::string> inputRasterInfo;
  inputRasterInfo["URI"] = "ImagPol240_0.bin";
  te::rst::Raster* inputRaster( te::rst::RasterFactory::open( inputRasterInfo ) );

  std::vector<unsigned int> inputBands;
  std::vector<te::rst::Raster*> inputRasters;

  for( size_t i = 0; i < 3; ++i ) {
    inputBands.push_back( i );
    inputRasters.push_back( inputRaster );
  }

  std::auto_ptr<te::rst::Raster> covMatrixRaster;
  std::map<std::string, std::string> covRasterInfo;

  bool result = te::rp::radar::CreateCovarianceRaster( inputRasters, inputBands,
						       covRasterInfo,
						       "MEM", covMatrixRaster );

  // @todo - etore - insert check of values.
  
  // @todo - etore - check against reference images and fix the output directory
  te::rp::Copy2DiskRaster( *covMatrixRaster, "cov_matrix_test.tif" );

  // @todo - etore - release pointers
  
  std::cout << "done." << std::endl;
}

void create_intensity_test() {
  std::cout << "Running radar functions (intensity) tests... ";

  // openning input raster
  std::map<std::string, std::string> inputRasterInfo;
  inputRasterInfo["URI"] = "ImagPol240_0_cov.tif";
  te::rst::Raster* inputRaster( te::rst::RasterFactory::open( inputRasterInfo ) );

  std::auto_ptr<te::rst::Raster> intensityRaster;
  std::map<std::string, std::string> intRasterInfo;

  bool result = te::rp::radar::CreateIntensityRaster( inputRaster,
						      intRasterInfo,
						      "MEM", intensityRaster );

  // @todo - etore - insert check of values.
  
  // @todo - etore - check against reference images
  // and fix the output directory
  te::rp::Copy2DiskRaster( *intensityRaster, "intensity_test.tif" );
 
  // @todo - etore - release pointers
  
  std::cout << "done." << std::endl;
}

void run_radarfunctions_tests() {
  create_covariance_test();
  create_intensity_test();
}
