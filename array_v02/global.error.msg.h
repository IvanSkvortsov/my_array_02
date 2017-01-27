#ifndef __GLOBAL_ERROR_MSG_H__
#define __GLOBAL_ERROR_MSG_H__

#ifdef  __GLOBAL_ERROR_MSG__
  #define __error_msg__( address, message )\
	std::cerr << "Error: [" << (void const *)(address) << "] " << __PRETTY_FUNCTION__ << ", " << (message) << std::endl
#else
  #define __error_msg__( address, message )
#endif
  
#endif//__GLOBAL_ERROR_MSG_H__
