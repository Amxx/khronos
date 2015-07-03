#include <iostream>
#include <khronos/khronos.hh>


int main()
{
	boost::asio::io_service ios;

	khronos::Timer c1(ios, [&](size_t i, khronos::Timer& self){
			printf("[C1 - fast][%lu] tick\n", i);
			return i%10;
		}, boost::posix_time::millisec(100)
	);

	khronos::Timer c2(ios, [&](size_t i, khronos::Timer& self){
			bool trigger = i%2 == 0;
			printf("[C2 - slow][%lu] %s\n", i, trigger?"start":"stop");
			if (trigger) c1.start();
			return i%10;
		}, boost::posix_time::millisec(1000)
	);

	printf("BEGIN\n");
	ios.run();
	printf("END\n");

	return 0;
}
