/*  Copyright (C) 2001-2015 National Institute For Space Research (INPE) - Brazil.

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
  \file MultiResolution.h
  \brief Specific multiresolution class that handles complex radar data.
*/

#ifndef __TERRALIB_RP_RADAR_INTERNAL_MULTIRESOLUTION_H
#define __TERRALIB_RP_RADAR_INTERNAL_MULTIRESOLUTION_H

#include <Raster.h>

namespace te {
  namespace rp {
    namespace radar {
      /*!
	\class MultiResolution

	\brief MultiResolution facility class.

	\details This multiresolution class is necessary because te::raster uses
	gdal, that works differently from desired behaviour in subsampling process.

	\ingroup rp_radar_seg
      */
      class MultiResolution
      {
      public:
	/*!
	  \brief Constructor.

	  \param inputRaster Input raster.
	  \param levels Number of levels to be created in the multi resolution.
	  \param enableProgressInterface Enable/disable the use of a progress.
	*/
	MultiResolution( const te::rst::Raster& inputRaster, size_t levels,
			 const bool enableProgressInterface = false );

	/*!
	  \brief Constructor.

	  \param inputRaster Input raster.
	  \param levels Number of levels in the multi resolution.
	  \param bandsNumbers Numbers of bands to be used when computing stats.
	  \param enableProgressInterface Enable/disable the use of a progress.
	*/
	MultiResolution( const te::rst::Raster& inputRaster, size_t levels,
			 const std::vector<size_t>& bandsNumbers,
			 const bool enableProgressInterface = false );

	/// Descructor.
	~MultiResolution();

	/*!
	  \brief Return the number of multi resolution levels.
	  
	  \return Number of multi resolution levels.
	*/
	size_t getNumberOfLevels() const;

	/*!
	  \brief Return the desired multi resolution @a level.

	  \param level Desired multi resolution level.
	  \return The raster of the given level.
	*/
	te::rst::Raster* getLevel( size_t level ) const;

	/*!
	  \!brief Remove all multi resolution stored rasters.
	 */
	void remove();

      protected:
	/*!
	  \brief Create the multi resolution levels.
	*/
	void createLevels();

	/*!
	  \brief Create a new multi resolution level based on the original one.
	  The new level must have a half number of lines and columns when compared to
	  the original one.

	  \param srcRaster Source raster, to read information from.
	  \param dstRaster Destination raster, to write information into.
	*/
	void createLevel( const te::rst::Raster& srcRaster,
			  te::rst::Raster& dstRaster );

      private:
	std::vector<size_t> m_bandsNumbers; //!< Bands used in the multi resolution creation.
	std::vector<te::rst::Raster*> m_levels; //!< Internal levels.
	bool m_enableProgress; //!< Enable/Disable the progress interface.
      };	
      
    } // end namespace radar
  } // end namespace rp
} // end namespace te

#endif // __TERRALIB_RP_RADAR_INTERNAL_MULTIRESOLUTION_H
