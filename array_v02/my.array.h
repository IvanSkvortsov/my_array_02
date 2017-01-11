#ifndef __MY_ARRAY_H__
#define __MY_ARRAY_H__
#include<cstdint>// uint32_t

#define __MY_ARRAY_LOGIN__
#ifdef  __MY_ARRAY_LOGIN__
  #include<iostream>
  #define __my_array_login__( stm, ptr, method_name ) stm << "Log: [" << ptr << "] " << method_name << std::endl
  #define function_name() __PRETTY_FUNCTION__
#else
  #define __my_array_login__( stm, ptr, method_name )
  #define function_name()
#endif

#define NDEBUG

class my_array
{
public:
	typedef uint32_t size_type;
private:
	struct array_struct;
	array_struct * _M_data;
protected:
	void free();
	void allocate( size_type __size );
public:
	my_array();
	my_array( my_array const & );
	my_array & operator=( my_array const & );
	~my_array();

	void * data();
	void const * data()const;
	size_type size()const;
	int resize( size_type __size );// return value: 0 - if __size -eq this->size(), or if __size -eq 0; 1 - otherwise
};

#endif//__MY_ARRAY_H__
