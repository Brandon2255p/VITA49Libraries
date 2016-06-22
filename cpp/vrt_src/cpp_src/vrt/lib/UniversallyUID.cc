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

#include "UniversallyUID.h"
#include <stdlib.h>

using namespace vrt;

#if INTERNAL_UniversallyUID_LIB != 0
# if INTERNAL_UniversallyUID_LIB == 2
#  include <gcrypt.h> // used for gcry_randomize(..)
#  ifndef _GCRYPT_H
#   error ****************************************************
#   error * Could not find system GCRYPT library, try building
#   error * with INTERNAL_UniversallyUID_LIB=1
#   error ****************************************************
#  endif
    void UniversallyUID_generate (VRTUniversallyUID_t out) {
      unsigned char *u = (unsigned char*)out;
    
      gcry_randomize(u, 16, GCRY_STRONG_RANDOM);
    
      u[6] = (u[6] & 0x0F) | 0x40; // version = 1000 (4 = random)
      u[8] = (u[8] & 0x3F) | 0x80; // variant = 10x  (RFC 4122)
    }
# endif
  void UniversallyUID_clear (VRTUniversallyUID_t out);
  int  UniversallyUID_compare (const VRTUniversallyUID_t uu1, const VRTUniversallyUID_t uu2);
  void UniversallyUID_generate (VRTUniversallyUID_t out);
  int  UniversallyUID_is_null (const VRTUniversallyUID_t uu);
  void UniversallyUID_unparse (const VRTUniversallyUID_t uu, char *out);
  int  UniversallyUID_parse (char *in, VRTUniversallyUID_t uu);

#endif

UniversallyUID::UniversallyUID () {
  UniversallyUID_clear(uu);
}

UniversallyUID::UniversallyUID (const UniversallyUID &UniversallyUID) {
  memcpy(uu, UniversallyUID.uu, 16);
}

UniversallyUID::UniversallyUID (const VRTUniversallyUID_t UniversallyUID) {
  memcpy(uu, UniversallyUID, 16);
}

#if INTERNAL_UniversallyUID_LIB != 1
  UniversallyUID UniversallyUID::randomUniversallyUID () {
    UniversallyUID val;
    UniversallyUID_generate(val.uu);
    return val;
  }
#endif

bool UniversallyUID::isNullValue () const {
  return (UniversallyUID_is_null(uu) != 0);
}

bool UniversallyUID::equals (const VRTObject &o) const {
  try {
    return equals(*checked_dynamic_cast<const UniversallyUID*>(&o));
  }
  catch (ClassCastException e) {
    return false;
  }
}

bool UniversallyUID::equals (const UniversallyUID &UniversallyUID) const {
  return (UniversallyUID_compare(uu, UniversallyUID.uu) == 0);
}

#if INTERNAL_UniversallyUID_LIB >= 1
  /** Converts two hex chars to an Int8 returning -1 on error. */
  static inline int32_t hexToDec (char a, char b) {
    int32_t _a;
    int32_t _b;
    
         if ((a >= '0') && (a <= '9')) _a = a - '0';
    else if ((a >= 'A') && (a <= 'F')) _a = a - 'A' + 10;
    else if ((a >= 'a') && (a <= 'f')) _a = a - 'a' + 10;
    else                               return -1;

         if ((b >= '0') && (b <= '9')) _b = b - '0';
    else if ((b >= 'A') && (b <= 'F')) _b = b - 'A' + 10;
    else if ((b >= 'a') && (b <= 'f')) _b = b - 'a' + 10;
    else                               return -1;
    
    return (_a << 4) | _b;
  }
  
  void UniversallyUID_clear (VRTUniversallyUID_t out) {
    char *u = (char*)out;
    
    for (size_t i = 0; i < 16; i++) {
      u[i] = 0;
    }
  }

  int  UniversallyUID_compare (const VRTUniversallyUID_t uu1, const VRTUniversallyUID_t uu2) {
    char *u1 = (char*)uu1;
    char *u2 = (char*)uu2;
    
    for (size_t i = 0; i < 16; i++) {
      if (u1[i] != u2[i]) return u1[i] - u2[i];
    }
    
    return 0;
  }
  
  int UniversallyUID_is_null (const VRTUniversallyUID_t uu) {
    char *u = (char*)uu;
    
    for (size_t i = 0; i < 16; i++) {
      if (u[i] != 0) return 0;
    }
    return 1;
  }
  
  void UniversallyUID_unparse (const VRTUniversallyUID_t uu, char *out) {
    char *u = (char*)uu;
    sprintf(out, "%.2x%.2x%.2x%.2x-"
                 "%.2x%.2x-%.2x%.2x-"
                 "%.2x%.2x-%.2x%.2x"
                 "%.2x%.2x%.2x%.2x",
                 0xFF&(int32_t)u[ 0], 0xFF&(int32_t)u[ 1], 0xFF&(int32_t)u[ 2], 0xFF&(int32_t)u[ 3],
                 0xFF&(int32_t)u[ 4], 0xFF&(int32_t)u[ 5], 0xFF&(int32_t)u[ 6], 0xFF&(int32_t)u[ 7],
                 0xFF&(int32_t)u[ 8], 0xFF&(int32_t)u[ 9], 0xFF&(int32_t)u[10], 0xFF&(int32_t)u[11],
                 0xFF&(int32_t)u[12], 0xFF&(int32_t)u[13], 0xFF&(int32_t)u[14], 0xFF&(int32_t)u[15]);
  }
  
  int UniversallyUID_parse (char *in, VRTUniversallyUID_t uu) {
    if ((strlen(in) != 36) || (in[ 8] != '-') || (in[13] != '-')
                           || (in[18] != '-') || (in[23] != '-')) {
      return -1;
    }
    char u[16];
    int  t;
    
    t = hexToDec(in[ 0],in[ 1]);    if (t < 0) return -1;    u[ 0] = (char)t;
    t = hexToDec(in[ 2],in[ 3]);    if (t < 0) return -1;    u[ 1] = (char)t;
    t = hexToDec(in[ 4],in[ 5]);    if (t < 0) return -1;    u[ 2] = (char)t;
    t = hexToDec(in[ 6],in[ 7]);    if (t < 0) return -1;    u[ 3] = (char)t;
    t = hexToDec(in[ 9],in[10]);    if (t < 0) return -1;    u[ 4] = (char)t;
    t = hexToDec(in[11],in[12]);    if (t < 0) return -1;    u[ 5] = (char)t;
    t = hexToDec(in[14],in[15]);    if (t < 0) return -1;    u[ 6] = (char)t;
    t = hexToDec(in[16],in[17]);    if (t < 0) return -1;    u[ 7] = (char)t;
    t = hexToDec(in[19],in[20]);    if (t < 0) return -1;    u[ 8] = (char)t;
    t = hexToDec(in[21],in[22]);    if (t < 0) return -1;    u[ 9] = (char)t;
    t = hexToDec(in[24],in[25]);    if (t < 0) return -1;    u[10] = (char)t;
    t = hexToDec(in[26],in[27]);    if (t < 0) return -1;    u[11] = (char)t;
    t = hexToDec(in[28],in[29]);    if (t < 0) return -1;    u[12] = (char)t;
    t = hexToDec(in[30],in[31]);    if (t < 0) return -1;    u[13] = (char)t;
    t = hexToDec(in[32],in[33]);    if (t < 0) return -1;    u[14] = (char)t;
    t = hexToDec(in[34],in[35]);    if (t < 0) return -1;    u[15] = (char)t;
    
    memcpy(uu, u, 16);
    return 0;
  }
#endif
  
string UniversallyUID::getUniversallyUID () const {
  char str[40]; // technically only 37 are required (36 + '\0')
  UniversallyUID_unparse(uu,str);
  return str;
}

void UniversallyUID::setUniversallyUID (const string &UniversallyUID) {
  // for some reason UniversallyUID_parse(..) wants a non-const 'char*'
  char *str = (char*)malloc(UniversallyUID.length()+1);
  memcpy(str, UniversallyUID.c_str(), UniversallyUID.length()+1);
  int ok = UniversallyUID_parse(str,uu);
  free(str);
  if (ok != 0) {
    throw VRTException("Error while parsing UniversallyUID '%s'", UniversallyUID.c_str());
  }
}

int32_t UniversallyUID::getFieldCount () const {
  return 1;
}

string UniversallyUID::getFieldName (int32_t id) const {
  switch (id) {
    case 0: return "UniversallyUID";
    default: throw VRTException("Invalid field #%d in %s", id, getClassName().c_str());
  }
}

ValueType UniversallyUID::getFieldType (int32_t id) const {
  switch (id) {
    case 0: return ValueType_String;
    default: throw VRTException("Invalid field #%d in %s", id, getClassName().c_str());
  }
}

Value* UniversallyUID::getField (int32_t id) const {
  switch (id) {
    case 0:  return new Value(getUniversallyUID());
    default: return new Value(); // null value
  }
}

void UniversallyUID::setField (int32_t id, const Value* val) {
  switch (id) {
    case 0: setUniversallyUID((string)*val); return;
    default: throw VRTException("Invalid field #%d in %s", id, getClassName().c_str());
  }
}

