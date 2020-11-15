
#include "utils/time.h"
#include <chrono>
#include <iostream>
#include <thread>

void f(int sleep_in_ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(sleep_in_ms));
}

int main()
{
	utils_time::Timer timer{};
	// std::cout << "Hello World!\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << timer << "\n";

	utils_time::MeasureCallTime{ f, 200 };
	auto today = utils_time::get_today();
	std::cout << "today is " << today << "\n";
	std::cout << "cur time is " << utils_time::get_cur_time() << "\n";
	return 0;
}
