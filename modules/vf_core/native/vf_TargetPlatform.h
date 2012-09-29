/*============================================================================*/
/*
  VFLib: https://github.com/vinniefalco/VFLib

  Copyright (C) 2008 by Vinnie Falco <vinnie.falco@gmail.com>

  This library contains portions of other open source products covered by
  separate licenses. Please see the corresponding source files for specific
  terms.
  
  VFLib is provided under the terms of The MIT License (MIT):

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/
/*============================================================================*/

#ifndef VF_TARGETPLATFORM_VFHEADER
#define VF_TARGETPLATFORM_VFHEADER

// Decode platform
//
#if (defined (_WIN32) || defined (_WIN64))
# define VF_WIN32 1
# define VF_WINDOWS 1
#elif defined (VF_ANDROID)
# undef VF_ANDROID
# define VF_ANDROID 1
#elif defined (LINUX) || defined (__linux__)
# define VF_LINUX 1
#elif defined (__APPLE_CPP__) || defined(__APPLE_CC__)
# define Point CarbonDummyPointName
# define Component CarbonDummyCompName
# include <CoreFoundation/CoreFoundation.h>
# undef Point
# undef Component
# if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#  define VF_IPHONE 1
#  define VF_IOS 1
# else
#  define VF_MAC 1
# endif
#else
# error "Unknown platform!"
#endif

// Decode Windows environment
//
#if VF_WINDOWS
# ifdef _MSC_VER
#  ifdef _WIN64
#   define VF_64BIT 1
#  else
#   define VF_32BIT 1
#  endif
# endif
# ifdef _DEBUG
#  define VF_DEBUG 1
# endif
# ifdef __MINGW32__
#  define VF_MINGW 1
#  ifdef __MINGW64__
#   define VF_64BIT 1
#  else
#   define VF_32BIT 1
#  endif
# endif
# define VF_LITTLE_ENDIAN 1
# define VF_INTEL 1
#endif

// Decode OS X / iOS environment
//
#if VF_MAC || VF_IOS
# if defined (DEBUG) || defined (_DEBUG) || ! (defined (NDEBUG) || defined (_NDEBUG))
#  define VF_DEBUG 1
# endif
# if ! (defined (DEBUG) || defined (_DEBUG) || defined (NDEBUG) || defined (_NDEBUG))
#  warning "NDEBUG or DEBUG not set"
# endif
# ifdef __LITTLE_ENDIAN__
#  define VF_LITTLE_ENDIAN 1
# else
#  define VF_BIG_ENDIAN 1
# endif
#endif

// Decode additional OS X environment options
#if VF_MAC
# if defined (__ppc__) || defined (__ppc64__)
#  define VF_PPC 1
# else
#  define VF_INTEL 1
# endif
# ifdef __LP64__
#  define VF_64BIT 1
# else
#  define VF_32BIT 1
# endif
# if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_4
#  error "Building for OSX 10.3 is not supported!"
# endif
# ifndef MAC_OS_X_VERSION_10_5
#  error "Building for OSX 10.4 is not supported!"
# endif
#endif

// Decode Linux / Android environment options
#if VF_LINUX || VF_ANDROID
# ifdef _DEBUG
#  define VF_DEBUG 1
# endif
# if defined (__LITTLE_ENDIAN__) || ! defined (VF_BIG_ENDIAN)
#  // Big-endian Linux platform override
#  define VF_LITTLE_ENDIAN 1
#  undef VF_BIG_ENDIAN
# else
#  undef VF_LITTLE_ENDIAN
#  define VF_BIG_ENDIAN 1
# endif
# if defined (__LP64__) || defined (_LP64)
#  define VF_64BIT 1
# else
#  define VF_32BIT 1
# endif
# if __MMX__ || __SSE__ || __amd64__
#  define VF_INTEL 1
# endif
#endif

// Decode compiler
//
#ifdef __GNUC__
# define VF_GCC 1
#elif defined (_MSC_VER)
# define VF_MSVC 1
# if _MSC_VER < 1500
#  define VF_VC8_OR_EARLIER 1
#  if _MSC_VER < 1400
#   define VF_VC7_OR_EARLIER 1
#   if _MSC_VER < 1300
#    error "MSVC 6.0 is not supported!"
#   endif
#  endif
# endif
# if VF_64BIT || ! VF_VC7_OR_EARLIER
#  define VF_USE_INTRINSICS 1
# endif
#else
# error unknown compiler
#endif

// Check for Clang
//
#ifdef __clang__
# define VF_CLANG 1
#endif

#endif

