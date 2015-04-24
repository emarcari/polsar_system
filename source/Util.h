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
      \brief Given an argc/argv pair, it extracts a vector of pairs 
      <raster*,band_number>.

      \param argc Argc.
      \param argv Argv.

      \warning The argv must follow the pattern:
      command line inputFile0 inputBand0 inputFile1 inputBand1 ...
      inputFileN inputBandN outputPrefix
      
      \return A vector of pair<raster*,band_number>.
     */
    std::vector<std::pair<te::rst::Raster*,size_t>>
      extractRastersFromArgs( int argc, char* argv[] );

    /*!
      \brief Given an argc/argv pair, it extracts the output prefix.
      The output prefix is used in the output files names creation.

      \param argc Argc.
      \param argv Argv.

      \warning The argv must follow the pattern:
      command line inputFile0 inputBand0 inputFile1 inputBand1 ...
      inputFileN inputBandN outputPrefix
      
      \return The output prefix.
     */
    std::string extractOutputPrefixFromArgs( int argc, char* argv[] );

    
  } // end namespace polsarsystem
} // end namespace util

#endif // __POLSARSYSTEM_INTERNAL_UTIL_H
