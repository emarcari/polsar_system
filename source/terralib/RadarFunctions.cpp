/*  Copyright (C) 2001-2009 National Institute For Space Research (INPE) - Brazil.

    This file is part of the TerraLib - a Framework for building GIS enabled applications.

    TerraLib is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License,
    or (at your option) any later version.

    TerraLib is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with TerraLib. See COPYING. If not, write to
    TerraLib Team at <terralib-team@terralib.org>.
*/

/*!
  \file RadarFunctions.cpp
*/

#include "RadarFunctions.h"

#include <raster/Enums.h>

namespace te
{
  namespace rp
  {
    namespace radar
    {
      bool CreateCovarianceRaster( const std::vector<te::rst::Raster*>& inputRasterPointers,
				   const std::vector<unsigned int>& inputRasterBands,
				   const std::map<std::string, std::string>& outputRasterInfo,
				   const std::string& outputDataSourceType,
				   std::auto_ptr<te::rst::Raster>& outputRasterPtr,
				   const bool enableProgressInterface )
      {
	outputRasterPtr.reset();

	size_t inputRasterBandsSize = inputRasterBands.size();
	
	if( inputRasterBandsSize != inputRasterPointers.size() ) {
	  return false;
	}

	if( outputDataSourceType.empty() ) {
	  return false;
	}

	size_t outputBands = inputRasterBandsSize * inputRasterBandsSize;

	// creating the output raster
	{
	  te::rst::Raster const* inputRasterPtr = inputRasterPointers[0];

	  std::auto_ptr<te::rst::Grid>
	    outputGridPtr( new te::rst::Grid( *inputRasterPtr->getGrid() ) );

	  // validate input data
	  // for now, use the dimension of first raster as default
	  // @todo - etore - Should we check if input dimensions are equal?
	  for( size_t i = 0; i < inputRasterBandsSize; ++i ) {
	    inputRasterPtr = inputRasterPointers[i];

	    if( inputRasterBands[i] >= inputRasterPtr->getNumberOfBands() ) {
	      return false;
	    }
	  }

	  inputRasterPtr = inputRasterPointers[0];
	  std::vector< te::rst::BandProperty* > bandsProperties;

	  for( size_t i = 0; i < outputBands; ++i ) {
	    te::rst::BandProperty*
	      inputBandProperty( new te::rst::BandProperty( *( inputRasterPtr->getBand
							       ( 0 )->getProperty()) ) );

	    te::rst::BandProperty* bandProperty
	      ( new te::rst::BandProperty( *inputBandProperty ) );

	    // @todo - etore - check this. It sounds weird
	    if( i != 0 ) {
	      bandProperty->m_colorInterp = te::rst::UndefCInt;
	    } else {
	      bandProperty->m_colorInterp = te::rst::GrayIdxCInt;
	    }
	    bandsProperties.push_back( bandProperty );
	  }
	  
	  outputRasterPtr.reset( te::rst::RasterFactory::make( outputDataSourceType,
							       outputGridPtr.release(),
							       bandsProperties, outputRasterInfo, 0, 0 ) );
	  if( outputRasterPtr.get() == 0 ) {
	    return false;
	  }
	}

	// create data for each band
	{
	  std::complex< double > value = 0;
	  //inputRasterBandsSize

	  const unsigned int nOutRows = outputRasterPtr->getNumberOfRows();
	  const unsigned int nOutCols = outputRasterPtr->getNumberOfColumns();
	  
	  te::rst::Band& inBand =
	    *inputRasterPointers[0]->getBand( 0 );
	    
	  for( size_t i = 0; i < outputBands; ++i ) {
	    te::rst::Band& outBand =
	      *outputRasterPtr->getBand( i );

	    for( size_t j = 0; j < nOutRows; ++j ) {
	      for( size_t k = 0; k < nOutCols; ++k ) {
		inBand.getValue( k, j, value );
		outBand.setValue( k, j, value );
	      }
	    }
	  }
	}
	  
	return true;
      }

      bool SampleFunction( const te::rst::Raster& inputRaster )
      {
	return false;
      }
    } // end namespace radar
  } // end namespace rp
}   // end namespace te
