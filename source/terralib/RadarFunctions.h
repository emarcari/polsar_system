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
  \file RadarFunctions.h
  \brief Radar Raster Processing functions.
*/

#ifndef __TERRALIB_RP_INTERNAL_RADAR_FUNCTIONS_H
#define __TERRALIB_RP_INTERNAL_RADAR_FUNCTIONS_H

#include <Raster.h>

namespace te
{
  namespace rp
  {
    namespace radar
    {
      /*!
      \brief Create a multi-band raster representing the covariance matrix.
      The number of bands is based on the number of input rasters.
      If the number of input rasters is 3, the method assumes that the input
      is a scattering vector, and the rasters contain data for HH, HV(VH) and
      VV polarizations.
      In case of size 4, the method assumes that the input data is complete, 
      containing the HH, HV, VH and VV polarizations.
      The method assumes that the bands from rasters have the same dimension.
      \param inputRasterPointers Input rasters pointers.
      \param inputRasterBands Input raster bands (one band for each input 
      raster).
      \param outputRasterInfo Output raster connection info.
      \param outputDataSourceType Output raster datasource type.
      \param outputRasterPtr A pointer to the generated output raster.
      \param enableProgressInterface Enable/disable the use of a progress 
      interface when applicable. 
      \return true if OK, false on errors.
      \note The number of bands in output raster is based on input. For the 
      scattering vector, the output raster will contain 9 bands and, for the
      complete input (scattering matrix), the output will contain 16 bands.
      \ingroup rp_radar_func
      */
      bool CreateCovarianceRaster( const std::vector<te::rst::Raster*>& inputRasterPointers,
				   const std::vector<unsigned int>& inputRasterBands,
				   const std::map<std::string, std::string>& outputRasterInfo,
				   const std::string& outputDataSourceType,
				   std::auto_ptr<te::rst::Raster>& outputRasterPtr,
				   const bool enableProgressInterface = false );

      /*!
        \brief Just a sample function.
        \return true if OK, false on errors.
        \ingroup rp_radar_func
      */
      bool SampleFunction( const te::rst::Raster& inputRaster );

    } // end namespace radar
  } // end namespace rp
}   // end namespace te

#endif  // __TERRALIB_RP_INTERNAL_FUNCTIONS_H
