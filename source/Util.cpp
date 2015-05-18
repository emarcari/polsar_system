/*!
  \file Util.cpp
  \brief Some useful functions for polsar system.
*/

// Local
#include "Util.h"

// Terralib
#include <rp/Functions.h>
#include <rp/RasterHandler.h>

namespace polsarsystem {
  namespace util {
    bool CopyComplex2DiskRaster( const te::rst::Raster& inputRaster,
				 const std::string& fileName )
    {
      if( !( inputRaster.getAccessPolicy() & te::common::RAccess ) ) {
	return false;
      };

      const unsigned int nBands = inputRaster.getNumberOfBands();
      const unsigned int nCols = inputRaster.getNumberOfColumns();
      const unsigned int nRows = inputRaster.getNumberOfRows();
      unsigned int bandIdx =0;
      unsigned int col = 0;
      unsigned int row = 0;

      std::vector<te::rst::BandProperty*> bandsProperties;
      for( bandIdx = 0 ; bandIdx < nBands ; ++bandIdx ) {
	bandsProperties.push_back
	  ( new te::rst::BandProperty
	    ( *( inputRaster.getBand( bandIdx )->getProperty() ) ) );
      }

      te::rp::RasterHandler outRasterHandler;

      if( !CreateNewGdalRaster( *( inputRaster.getGrid() ), bandsProperties,
				fileName, outRasterHandler ) ) {
	return false;
      }

      std::complex<double> value = 0;

      for( bandIdx = 0 ; bandIdx < nBands ; ++bandIdx ) {
	const te::rst::Band& inBand = *inputRaster.getBand( bandIdx );
	te::rst::Band& outBand = *outRasterHandler.getRasterPtr()->getBand( bandIdx );

	for( row = 0 ; row < nRows ; ++row ) {
	  for( col = 0 ; col < nCols ; ++col ) {
	    inBand.getValue( col, row, value );
	    outBand.setValue( col, row, value );
	  }
	}
      }

      return true;
    }
  } // end namespace polsarsystem
} // end namespace util
