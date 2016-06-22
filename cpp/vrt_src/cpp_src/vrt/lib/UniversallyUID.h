/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file
 * distributed with this source distribution.
 *
 * This file is part of REDHAWK.
 *
 * REDHAWK is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * REDHAWK is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

#ifndef _UniversallyUID_h
#define _UniversallyUID_h

#include "VRTObject.h"
#include "HasFields.h"
#include <string.h>    // required for memcpy(..) on GCC4.4/libc6 2.11.1

#ifndef INTERNAL_UniversallyUID_LIB
# define INTERNAL_UniversallyUID_LIB 1  // see comments at top of UniversallyUID class
#endif

#if INTERNAL_UniversallyUID_LIB == 0
# include <UniversallyUID/UniversallyUID.h>
# ifndef _UniversallyUID_UniversallyUID_H
#  error *******************************************************
#  error * Could not find system UniversallyUID library, try building with
#  error * INTERNAL_UniversallyUID_LIB=1 or INTERNAL_UniversallyUID_LIB=2
#  error *******************************************************
# endif
#else
  typedef unsigned char VRTUniversallyUID_t[16];
#endif

namespace vrt {
  /** A 128-bit universally unique identifier (UniversallyUID). This provides an OO wrapper for the
   *  <tt>UniversallyUID_t</tt> value defined in the <tt>UniversallyUID/UniversallyUID.h</tt> library that allows its inclusion
   *  in VRT packets similar to other values.
   *  <pre>
   *    By default the standard UniversallyUID library (-lUniversallyUID) will be used when working with
   *    UniversallyUIDs in the C++ code. Since some platforms do not have this library installed,
   *    there is a mini UniversallyUID library internal to the VRT C++ code. (The internal library
   *    supports the minimum set of functions required here and is not intended for use
   *    by external users.) The internal library has two versions: the second version
   *    supports generation of RFC 4122-compliant UniversallyUIDs using gcrypt as a source of
   *    secure-random numbers; the first version does not depend on gcrypt but does
   *    not support generation of UniversallyUIDs (use the first version only as a last resort).
   *      Standard UniversallyUID library:            setenv INTERNAL_UniversallyUID_LIB 0
   *      Internal UniversallyUID library (no gen):   setenv INTERNAL_UniversallyUID_LIB 1
   *      Internal UniversallyUID library (random):   setenv INTERNAL_UniversallyUID_LIB 2
   *  </pre>
   *  @author 
   */
  class UniversallyUID : public VRTObject, public HasFields {
    /** The 128-bit UniversallyUID. */
    private: VRTUniversallyUID_t uu; // VRTUniversallyUID_t is a typedef for a char[16]

    /** Destructor. */
    public: ~UniversallyUID () { }

    /** Basic no-argument constructor. */
    public: UniversallyUID ();

    /** Copy constructor. */
    public: UniversallyUID (const UniversallyUID &UniversallyUID);

    /** Copy constructor. */
    public: UniversallyUID (const VRTUniversallyUID_t UniversallyUID);

#if INTERNAL_UniversallyUID_LIB != 1
    /** Generates a random UniversallyUID. */
    public: static UniversallyUID randomUniversallyUID ();
#endif

    /** A UniversallyUID is considered null if all bits are set to 0 (this is not a valid UniversallyUID). */
    public: virtual bool isNullValue () const;

    public: virtual bool equals (const VRTObject &o) const;
    
    /** Checks to see if two UniversallyUIDs are equal. */
    public: virtual bool equals (const UniversallyUID &UniversallyUID) const;

    /** Converts the UniversallyUID to a string. */
    public: inline virtual string toString () const {
      return getUniversallyUID();
    }

    /** Gets a pointer to the UniversallyUID value. */
    public: VRTUniversallyUID_t &getUniversallyUIDPointer() {
      return uu;
    }

    /** Gets the 16-byte UniversallyUID value into the given buffer. */
    public: inline void getValue (void *buf) const {
      memcpy(buf, uu, 16);
    }

    /** Sets the 16-byte UniversallyUID value from the given buffer. */
    public: inline void setValue (const void *buf) {
      memcpy(uu, buf, 16);
    }

    /** Gets the 16-byte UniversallyUID value into the given buffer. */
    public: string getUniversallyUID () const;

    /** Sets the 16-byte UniversallyUID value from the given buffer. */
    public: void setUniversallyUID (const string &UniversallyUID);
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Implement HasFields
    //////////////////////////////////////////////////////////////////////////////////////////////////
    public: virtual int32_t   getFieldCount () const;
    public: virtual string    getFieldName  (int32_t id) const;
    public: virtual ValueType getFieldType  (int32_t id) const;
    public: virtual Value*    getField      (int32_t id) const;
    public: virtual void      setField      (int32_t id, const Value* val);
  };

  namespace VRTMath {
    /** Pack a 16-byte UniversallyUID into a buffer.
        @param buf   byte array of data [OUTPUT]
        @param off   Offset into array
        @param val   value to pack [INPUT]
     */
    inline void packUniversallyUID (vector<char> &buf, int32_t off, const UniversallyUID &val) {
      val.getValue(&buf[off]);
    }

    /** Unpack a 16-byte UniversallyUID from a buffer.
        @param buf   byte array of data
        @param off   Offset into array
        @return The unpacked value
     */
    inline UniversallyUID unpackUniversallyUID (const vector<char> &buf, int32_t off) {
      UniversallyUID val;
      val.setValue(&buf[off]);
      return val;
    }
  };
};
#endif /* _UniversallyUID_h */
