// bdldfp_denselypackeddecimalimputil.h                               -*-C++-*-
#ifndef INCLUDED_BDLDFP_DENSELYPACKEDDECIMALIMPUTIL
#define INCLUDED_BDLDFP_DENSELYPACKEDDECIMALIMPUTIL

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id$")

//@PURPOSE: Utilities for working with Densely Packed Decimal representation.
//
//@CLASSES:
//  bdldfp::DenselyPackedDecimalImpUtil: namespace for DPD functions.
//
//@SEE ALSO: bdldfp_decimal, bdldfp_decimalplatform
//
//@DESCRIPTION: The 'bdldfp::DenselyPackeDecimalImpUtil' provides a suite of
// functions for manipulating a Densely Packed Decimal (DPD) representation of
// a decimal floating point value.
//
///Usage
///-----
// This section shows the intended use of this component.
//
///Example 1: Get the DPD representation of a 10 digit binary number
///- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Decimal floating point numbers are used to represent, in human-convenient
// form, approximations of real-number-line values.  The Densely Packed Decimal
// format is a storage format which represents significant digits of a value in
// a compressed Binary-Coded Decimal (BCD) format.  Densely Packed Decimal
// significands consist of a seqence of declets, each declet encoding 3 decimal
// digits, in 10 bits.  The encoding is not a 1:1 mapping with the binary
// values corresponding to the decimal value of any three digits.
//
// In the following example we used 'DenselyPackedDecimalImpUtil' to encode an
// integer value.  Suppose we have a 0 to 3 digit value which we want to encode
// in declet form, for use in DenselyPackedDecimal operations.
//
// First, we represent our decimal digits as an integer:
//..
//  int value = 842;
//..
// Now, we encode the integer using the 'encodeDeclet' function:
//..
//  int asDeclet = bdldfp::DenselyPackedDecimalImpUtil::encodeDeclet(value);
//..
// Finally, we can confirm that the declet representation converts back to the
// binary representation of our three digits:
//..
//  assert(
//       value == bdldfp::DenselyPackedDecimalImpUtil::decodeDeclet(asDeclet));
//..



#ifndef INCLUDED_BDLSCM_VERSION
#include <bdlscm_version.h>
#endif

#ifndef INCLUDED_BDLDFP_DECIMALPLATFORM
#include <bdldfp_decimalplatform.h>
#endif

#ifndef INCLUDED_BDLDFP_UINT128
#include <bdldfp_uint128.h>
#endif

namespace BloombergLP {
namespace bdldfp {

                        // =================================
                        // class DenselyPackedDecimalImpUtil
                        // =================================

struct DenselyPackedDecimalImpUtil {
    // This 'struct' provides a namespace for implementation functions that
    // provide common DPD formatted decimal floating point.

    // TYPES
    typedef unsigned           int StorageType32;
    typedef unsigned long long int StorageType64;
    typedef bdldfp::Uint128        StorageType128;

    // CLASS METHODS
    static unsigned encodeDeclet(unsigned digits);
        // Return an unsigned integer whose bits encode the value of the
        // specified 'digits' in the Densely Packed Decimal (DPD) format.  The
        // behavior is undefined unless '0 <= digits < 1000'.  Note that the
        // result will be a bit pattern whose binary representation corresponds
        // to a value in the range '[0, 1024]'.  Also note that this function
        // encodes a *single* declet (not a complete DPD decimal floating point
        // representation), and returns an 'unsigned int' as it is intended for
        // use with raw bit manipulation functions.

    static unsigned decodeDeclet(unsigned declet);
        // Return the (unsigned integer) value encoded in the specified
        // 'declet'.  The behavior is undefined unless the binary value of
        // 'declet < 1024', 'declet' is encoded in Densely Packed Decimal
        // (DPD), and every unused bit in the densely packed state is set to 0.
        // Note that the result will be an integer in the range '[0, 999]'.
        // Also note that this function decodes a *single* declet (not a
        // complete DPD decimal floating point representation), and returns
        // 'unsigned int' type values, as it is intended for use with raw bit
        // manipulation functions.

    static StorageType32 makeDecimalRaw32(int mantissa, int exponent);
        // Return a 'StorageType32' object representing a decimal floating
        // point number consisting of the specified 'mantissa' and 'exponent',
        // with the sign given by the 'mantissa'.  If 'mantissa' is 0, the
        // result is 0 but the quanta of the result is unspecified.  The
        // behavior is undefined unless 'abs(mantissa) <= 9,999,999' and
        // '-101 <= exponent <= 90'.

    static StorageType64 makeDecimalRaw64(unsigned long long int mantissa,
                                                             int exponent);
    static StorageType64 makeDecimalRaw64(         long long int mantissa,
                                                             int exponent);
    static StorageType64 makeDecimalRaw64(unsigned           int mantissa,
            int exponent);
    static StorageType64 makeDecimalRaw64(                   int mantissa,
                                                             int exponent);
        // Create a 'StorageType64' object representing a decimal floating
        // point number consisting of the specified 'mantissa' and 'exponent',
        // with the sign given by the 'mantissa'.  If 'mantissa' is 0, the
        // result is 0 but the quanta of the result is unspecified.  The
        // behavior is undefined unless
        // 'abs(mantissa) <= 9,999,999,999,999,999' and
        // '-398 <= exponent <= 369'.

    static StorageType128 makeDecimalRaw128(unsigned long long int mantissa,
                                                               int exponent);
    static StorageType128 makeDecimalRaw128(         long long int mantissa,
                                                               int exponent);
    static StorageType128 makeDecimalRaw128(unsigned           int mantissa,
                                                               int exponent);
    static StorageType128 makeDecimalRaw128(                   int mantissa,
                                                               int exponent);
        // Create a 'StorageType128' object representing a decimal floating
        // point number consisting of the specified 'mantissa' and 'exponent',
        // with the sign given by the 'mantissa'.  If 'mantissa' is 0, the
        // result is 0 but the quanta of the result is unspecified.  The
        // behavior is undefined unless '-6176 <= exponent <= 6111'.
};

}  // close package namespace
}  // close enterprise namespace

#endif

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Bloomberg L.P.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------- END-OF-FILE ----------------------------------