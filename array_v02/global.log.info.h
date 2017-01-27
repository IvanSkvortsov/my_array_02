#ifndef __GLOBAL_LOG_INFO_H__
#define __GLOBAL_LOG_INFO_H__

#ifdef  __GLOBAL_LOG_INFO__
  #define __log_info__( address ) std::clog << "[" << (void const *)(address) << "] " << __PRETTY_FUNCTION__ << std::endl
#else
  #define __log_info__( address )
#endif

#endif//__GLOBAL_LOG_INFO_H__
