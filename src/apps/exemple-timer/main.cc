#include <iostream>
#include <khronos/khronos.hh>


int main()
{
	boost::asio::io_service ios;

	khronos::timer c1(ios, [&](size_t i, auto& self){ // auto = kronos::timer
			printf("[C1 - fast][%lu] tick\n", i);
			return i%5;
		}, boost::posix_time::millisec(100)
	);

	khronos::timer c2(ios, [&](size_t i, auto& self){ // auto = kronos::timer
			printf("[C2 - slow][%lu] tick\n", i);
			c1.start();
			return i%10;
		}, boost::posix_time::millisec(1000)
	);

	printf("BEGIN\n");
	ios.run();
	printf("END\n");

	return 0;
}
