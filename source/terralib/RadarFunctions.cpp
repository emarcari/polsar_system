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

	  // @todo - etore - what to do when grid is missing in the input file?
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

	  // use the properties from the first band / first raster to create
	  // the output bands
	  inputRasterPtr = inputRasterPointers[0];
	  te::rst::BandProperty*
	    inputBandProperty( new te::rst::BandProperty( *( inputRasterPtr->getBand
							     ( 0 )->getProperty()) ) );

	  std::vector< te::rst::BandProperty* > bandsProperties;

	  for( size_t i = 0; i < outputBands; ++i ) {
	    te::rst::BandProperty* bandProperty
	      ( new te::rst::BandProperty( *inputBandProperty ) );

	    // @todo - etore - check this. It sounds weird
	    // if we don't do this, the warn is shown
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
	  const unsigned int nOutRows = outputRasterPtr->getNumberOfRows();
	  const unsigned int nOutCols = outputRasterPtr->getNumberOfColumns();

	  std::vector< std::complex< double > > inputComplex( inputRasterBandsSize );
	  std::vector< std::complex< double > > conjugatedComplex( inputRasterBandsSize );

	  // for each pixel (line,column), compute the values
	  for( size_t j = 0; j < nOutRows; ++j ) {
	    for( size_t k = 0; k < nOutCols; ++k ) {
	      // get the input values
	      for( size_t i = 0; i < inputRasterPointers.size(); ++i ) {
		std::complex< double > inputComplexValue;
		inputRasterPointers[ i ]->getBand( inputRasterBands[ i ] )->getValue( k, j, inputComplexValue );
		inputComplex[ i ] = inputComplexValue;
		conjugatedComplex[ i ] = std::conj( inputComplexValue );
	      }

	      for( size_t l = 0; l < inputComplex.size(); ++ l ) {
		for( size_t m = 0; m < conjugatedComplex.size(); ++ m ) {
		  size_t pos = ( inputRasterBandsSize * l ) + m;

		  std::complex<double> value = inputComplex[ l ] * conjugatedComplex[ m ];
		  outputRasterPtr->getBand( pos )->setValue( k, j, value );
		}
	      }
	    }
	  }
	}

	// @todo - etore - release pointers, if necessary.
	
	return true;
      }

      bool CreateIntensityRaster( const te::rst::Raster* inputRasterPtr,
				  const std::map<std::string, std::string>& intensityRasterInfo,
				  const std::string& outputDataSourceType,
				  std::auto_ptr<te::rst::Raster>& intensityRasterPtr,
				  const bool enableProgressInterface ) {


	intensityRasterPtr.reset();
	
	size_t inputRasterBandsSize = inputRasterPtr->getNumberOfBands();

	// only 3 and 4 bands are supported.
	if( inputRasterBandsSize != 9 && inputRasterBandsSize != 16 ) {
	  return false;
	}
	
	if( outputDataSourceType.empty() ) {
	  return false;
	}

	// creating the output raster
	{
	  // @todo - etore - what to do when grid is missing in the input file?
	  std::auto_ptr<te::rst::Grid>
	    outputGridPtr( new te::rst::Grid( *inputRasterPtr->getGrid() ) );

	  std::vector< te::rst::BandProperty* > bandsProperties;

	  te::rst::BandProperty*
	    inputBandProperty( new te::rst::BandProperty( *( inputRasterPtr->getBand
							     ( 0 )->getProperty() ) ) );

	  te::rst::BandProperty* bandProperty
	    ( new te::rst::BandProperty( *inputBandProperty ) );

	  bandProperty->m_colorInterp = te::rst::GrayIdxCInt;

	  bandsProperties.push_back( bandProperty );

	  intensityRasterPtr.reset( te::rst::RasterFactory::make( outputDataSourceType,
								  outputGridPtr.release(),
								  bandsProperties,
								  intensityRasterInfo,
								  0, 0 ) );

	  if( intensityRasterPtr.get() == 0 ) {
	    return false;
	  }
	}

	// create data
	{
	  const unsigned int nOutRows = intensityRasterPtr->getNumberOfRows();
	  const unsigned int nOutCols = intensityRasterPtr->getNumberOfColumns();

	  // get bands for extract input values
	  std::vector< size_t > intensityBands;
	  std::complex< double > value = 0.;

	  if( inputRasterBandsSize == 9 ) {
	    intensityBands.push_back( 0 );
	    intensityBands.push_back( 4 );
	    intensityBands.push_back( 8 );

	  } else {
	    intensityBands.push_back( 0 );
	    intensityBands.push_back( 5 );
	    intensityBands.push_back( 10 );
	    intensityBands.push_back( 15 );
	  }
	  
	  te::rst::Band& outBand = *intensityRasterPtr->getBand( 0 );

	  // for each pixel (line,column), compute the values
	  for( size_t j = 0; j < nOutRows; ++j ) {
	    for( size_t k = 0; k < nOutCols; ++k ) {
	      std::complex< double > resultValue = 1.;

	      for( size_t b = 0; b < intensityBands.size(); ++b ) {
		inputRasterPtr->getBand( intensityBands[ b ] )->getValue( k, j, value );
		resultValue *= value;
	      }
	      
	      outBand.setValue( k, j, resultValue );
	    }
	  }
	}

	// @todo - etore - release pointers, if necessary.
	
	return true;
      }      
    } // end namespace radar
  } // end namespace rp
}   // end namespace te
