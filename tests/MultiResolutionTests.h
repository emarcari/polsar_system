/*!
  \file math_tests.h

  \brief Simple code for testing some terralib math features.

  \author Etore Marcari Jr. <etore@dpi.inpe.br>
*/

#include "../source/terralib/MultiResolution.h"

#include <rp/Functions.h>
#include <Raster.h>

#include "Common.h"

void basic_test() {
  std::cout << "Running multiresolution basic tests... ";

  // openning input raster
  std::map<std::string, std::string> inputRasterInfo;
  inputRasterInfo["URI"] = "ImagPol240_0.bin";
  te::rst::Raster* inputRaster( te::rst::RasterFactory::open( inputRasterInfo ) );
  
  te::rp::radar::MultiResolution*
    multiRes = new te::rp::radar::MultiResolution( *inputRaster, 4, false );

  size_t levels = multiRes->getNumberOfLevels();
  assert( levels == 5 );
  
  //
  // L0
  //
  te::rst::Raster* levelZeroRaster = multiRes->getLevel( 0 );

  std::complex<double> v1, v2, v3, v4;
  levelZeroRaster->getValue( 0, 0, v1 );
  levelZeroRaster->getValue( 1, 0, v2 );
  levelZeroRaster->getValue( 0, 1, v3 );
  levelZeroRaster->getValue( 1, 1, v4 );

  size_t nCols = levelZeroRaster->getNumberOfColumns();
  size_t nRows = levelZeroRaster->getNumberOfRows();
  assert( nCols == 240 );
  assert( nRows == 240 );
  
  double eps = 1e-6;

  assert( ( v1.real() + 0.003844 ) < eps );
  assert( ( v1.imag() - 0.035258 ) < eps );

  assert( ( v2.real() - 0.059669 ) < eps );
  assert( ( v2.imag() + 0.006968 ) < eps );

  assert( ( v3.real() - 0.011045 ) < eps );
  assert( ( v3.imag() + 0.045011 ) < eps );

  assert( ( v4.real() - 0.015729 ) < eps );
  assert( ( v4.imag() + 0.049620 ) < eps );
  
  std::complex<double> sum = v1 + v2 + v3 + v4;
  std::complex<double> mean = sum / 4.;

  assert( ( sum.real() - 0.082599 ) < eps );
  assert( ( sum.imag() + 0.066342 ) < eps );

  assert( ( mean.real() - 0.020650 ) < eps );
  assert( ( mean.imag() + 0.016585 ) < eps );

  // The values in L0 must be the same from Input image.
  // So, check this.
  std::complex<double> iv1, iv2, iv3, iv4;
  inputRaster->getValue( 0, 0, iv1 );
  inputRaster->getValue( 1, 0, iv2 );
  inputRaster->getValue( 0, 1, iv3 );
  inputRaster->getValue( 1, 1, iv4 );

  assert( ( v1.real() - iv1.real() ) < eps );
  assert( ( v2.real() - iv2.real() ) < eps );
  assert( ( v3.real() - iv3.real() ) < eps );
  assert( ( v4.real() - iv4.real() ) < eps );
    
  //
  // L1
  //
  te::rst::Raster* levelOneRaster = multiRes->getLevel( 1 );

  nCols = levelOneRaster->getNumberOfColumns();
  nRows = levelOneRaster->getNumberOfRows();
  assert( nCols == 120 );
  assert( nRows == 120 );
    
  std::complex<double> l2v1;
  levelOneRaster->getValue( 0, 0, l2v1 );
  assert( ( l2v1.real() - 0.020650 ) < eps );
  assert( ( l2v1.imag() + 0.016585 ) < eps );

  delete levelZeroRaster;
  delete levelOneRaster;

  std::cout << "done." << std::endl;
}

void multires_test() {
  std::cout << "Running multiresolution tests... ";

  // openning input raster
  std::map<std::string, std::string> inputRasterInfo;
  inputRasterInfo["URI"] = "ImagPol240_0.bin";
  te::rst::Raster* inputRaster( te::rst::RasterFactory::open( inputRasterInfo ) );

  te::rp::radar::MultiResolution*
    multiRes = new te::rp::radar::MultiResolution( *inputRaster, 3, false );
  
  te::rst::Raster* levelRaster = multiRes->getLevel( 0 );
  size_t nCols = levelRaster->getNumberOfColumns();
  size_t nRows = levelRaster->getNumberOfRows();
  assert( nCols == 240 );
  assert( nRows == 240 );

  // @todo - etore - check against reference images and fix the output directory
  te::rp::Copy2DiskRaster( *levelRaster, "multires_test_l0.tif" );

  levelRaster = multiRes->getLevel( 1 );
  nCols = levelRaster->getNumberOfColumns();
  nRows = levelRaster->getNumberOfRows();
  assert( nCols == 120 );
  assert( nRows == 120 );
  
  te::rp::Copy2DiskRaster( *levelRaster, "multires_test_l1.tif" );

  levelRaster = multiRes->getLevel( 2 );
  nCols = levelRaster->getNumberOfColumns();
  nRows = levelRaster->getNumberOfRows();
  assert( nCols == 60 );
  assert( nRows == 60 );
  
  te::rp::Copy2DiskRaster( *levelRaster, "multires_test_l2.tif" );

  delete levelRaster;
  delete inputRaster;
  
  std::cout << "done." << std::endl;
}

void run_multiresolution_tests() {
  basic_test();
  multires_test();
}
