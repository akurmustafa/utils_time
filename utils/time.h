
#ifndef UTILS_TIME_H
#define UTILS_TIME_H

#include <chrono>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <string>

namespace utils_time
{ // all declarations in the namespace time_wrapper
enum class duration_type{ nano, micro, mili, sec};
namespace stdc = std::chrono;

class Timer {
private:
	stdc::time_point<stdc::system_clock> t_start;
public:
	Timer();
	std::int64_t elapsed(duration_type dt = duration_type::mili, bool reset=false);
	void reset();
	friend std::ostream& operator<<(std::ostream& os, Timer& timer);
};


struct MeasureCallTime {
	template<typename Func, typename... Args>
	MeasureCallTime(Func f, Args... args) {
		auto t_start = std::chrono::high_resolution_clock::now();
		f(args...);
		auto t_end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
		std::cout << "elapsed time: " << elapsed << " milliseconds\n";
	}
};

inline std::tm localtime_xp(std::time_t timer);
std::string get_today();
std::string get_cur_time();
}  // namespace utils_time

#endif  // end of UTILS_TIME_H
