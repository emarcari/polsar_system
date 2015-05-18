/*!
  \file Util.h
  \brief Some useful functions for polsar system.
*/

#ifndef __POLSARSYSTEM_INTERNAL_UTIL_H
#define __POLSARSYSTEM_INTERNAL_UTIL_H

// Terralib
#include <raster.h>

// STL
#include <memory>
#include <vector>

namespace polsarsystem {
  namespace util {
    /*!
      \brief Convert to string.

      \param t What to convert.

      \return Converted string.
    */
    template<class T>
      std::string toString( const T& t ) {
      std::ostringstream ss;
      ss << t;
      return ss.str();
    }
    
    /*!
      \brief Convert to string.

      \param t What to convert.
      \param s Converted string.
    */
    template<class T>
      void toString( const T& t, const std::string& s ) {
      t = toString<T>( s );
    }
    
    /*!
      \brief Convert from string.

      \param s String to be converted.

      \return Converted value.
    */
    template<class T>
      T fromString( const std::string& s ) {
      std::istringstream ss( s );
      T t = T(); // set only to avoid valgrind error message
      ss >> t;
      return t;
    }
    
    /*!
      \brief Convert from string.

      \param t Converted value.
      \param s String to be converted.
    */
    template<class T>
      void fromString( T& t, const std::string& s ) {
      t = fromString<T>( s );
    }

    /*!
      \brief Create a new complex raster into a GDAL datasource.
      \param rasterGrid The template grid used to create the output raster.
      \param fileName The output tif file name.
      \return true if OK, false on errors.
    */
    bool CopyComplex2DiskRaster( const te::rst::Raster& inputRaster,
				 const std::string& fileName );
    
    
  } // end namespace polsarsystem
} // end namespace util

#endif // __POLSARSYSTEM_INTERNAL_UTIL_H
