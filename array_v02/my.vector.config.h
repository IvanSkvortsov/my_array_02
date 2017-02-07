#ifndef __MY_VECTOR_CONFIG_H__
#define __MY_VECTOR_CONFIG_H__

#if !defined( __MY_VECTOR_H__ )
#error This file should follow 'my.vector.h' file
#endif

#if defined( __GLOBAL_LOG_INFO_H__ ) || defined( __GLOBAL_ERROR_MSG_H__ ) || defined( assert )
#error This file should precede 'global.log.info.h', 'global.error.msg.h', and 'assert.h' files
#endif

#ifdef  __MY_VECTOR_LOG_INFO__
  #ifndef __GLOBAL_LOG_INFO__
  #define __GLOBAL_LOG_INFO__
  #endif
#else
  #undef  __GLOBAL_LOG_INFO__
#endif

#ifdef  __MY_VECTOR_ERROR_MSG__
  #ifndef __GLOBAL_ERROR_MSG__
  #define __GLOBAL_ERROR_MSG__
  #endif
#else
  #undef  __GLOBAL_ERROR_MSG__
#endif

#if defined( __MY_VECTOR_LOG_INFO__ ) || defined( __MY_VECTOR_ERROR_MSG__ )
  #include<iostream>
#endif

#ifdef  __MY_VECTOR_NDEBUG__
  #ifndef NDEBUG
  #define NDEBUG
  #endif
#else
  #ifdef  NDEBUG
  #undef  NDEBUG
  #endif
#endif

#endif//__MY_VECTOR_CONFIG_H__
