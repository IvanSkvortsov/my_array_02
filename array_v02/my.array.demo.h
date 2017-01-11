#include"my.array.h"
#include"my.array.hpp"
#include<iostream>
#include<iomanip>
#include<cstdlib>// atoi
#include"bitprint.hpp"
#include"smart.bits.hpp"
using namespace std;

template<typename T>
int my_array_demo( char * arg )
{
	const uint32_t size = atoi( arg );
	my_array_t<T> a;
	cout << "a.size: " << a.size() << endl;
	cout << "a.data: [" << a.data() << "]" << endl;
	a.resize( size );
	cout << "a.size: " << a.size() << endl;
	cout << "a.data: [" << a.data() << "]" << endl;
	T const * data = 0, * p = 0;
	data = a.data();
	p = ( data ? data + (a.size() - 1) : 0 );
	for(int i = 0; i < a.size(); ++i )
		a[i] = 2 * i + 1;
	for(int i = 0; i < a.size(); ++i )
		cout << setw(4) << i << ": " << setw(20) << a[i] << "  [" << &a[i] << "]" << endl;
	cout << "a.size: " << a.size() << endl;
	cout << "data  : [" << data << "]  " << ( data ? *data : 0 ) << endl;
	cout << "p     : [" << p << "]  " << ( p ? *p : 0 ) << endl;
	for(int i = 0; i < a.size(); ++i )
		cout << setw(4) << i << ": " << setw(20) << a[i] << "  [" << &a[i] << "]" << endl;
	my_array_t<T> b( a );
	cout << "data  : [" << data << "]  " << ( data ? *data : 0 ) << endl;
	cout << "p     : [" << p << "]  " << ( p ? *p : 0 ) << endl;
	cout << "b.size: " << b.size() << endl;
	for(int i = 0; i < b.size(); ++i )
		cout << setw(4) << i << ": " << setw(20) << b[i] << "  [" << &b[i] << "]" << endl;
	return 0;
}

int main( int argc, char ** argv )
{
	if( argc != 2 )
	{
		cerr << "Error: [main] usage './main.exe num'" << endl;
		return 1;
	}
	return my_array_demo<long double>( argv[1] );
}
