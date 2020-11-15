
#include "utils/time.h"

#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <string>

namespace utils_time 
{
namespace stdc = std::chrono;
Timer::Timer() {
	t_start = std::chrono::system_clock::now();
}

std::int64_t Timer::elapsed(duration_type dt, bool reset) {
	auto t_cur = stdc::system_clock::now();
	std::int64_t elapsed{ 0 };
	switch (dt) {
	case duration_type::nano:
		elapsed = stdc::duration_cast<stdc::nanoseconds>(t_cur - t_start).count();
		break;
	case duration_type::micro:
		elapsed = stdc::duration_cast<stdc::microseconds>(t_cur - t_start).count();
		break;
	case duration_type::mili:
		elapsed = stdc::duration_cast<stdc::milliseconds>(t_cur - t_start).count();
		break;
	case duration_type::sec:
		elapsed = stdc::duration_cast<stdc::seconds>(t_cur - t_start).count();
		break;
	default:
		elapsed = -1; // indication of a problem, shouldn't happen
	}
	if (reset) {
		t_start = stdc::system_clock::now();
	}
	return elapsed;
}


void Timer::reset() {
	t_start = stdc::system_clock::now();
}


std::ostream& operator<<(std::ostream& os, Timer& timer) {
	auto time_elapsed = timer.elapsed(duration_type::nano, false);
	std::int64_t mili_nano{ 1000000 };	// 1e6
	std::int64_t sec_nano{ mili_nano*1000 };	// 1e9
	std::int64_t minute_nano{ sec_nano * 60 };
	std::int64_t hour_nano{ sec_nano * 60 * 60 };
	std::int64_t hh = (time_elapsed/(hour_nano));
	time_elapsed = time_elapsed % hour_nano;
	std::int64_t mm = (time_elapsed / minute_nano);
	time_elapsed = time_elapsed % minute_nano;
	std::int64_t ss = (time_elapsed / sec_nano);
	time_elapsed = time_elapsed % sec_nano;
	std::int64_t msec = (time_elapsed / mili_nano);
	time_elapsed = time_elapsed % mili_nano;
	os << std::setfill('0') << std::setw(2) << hh << "::" << std::setw(2) << mm<< "::" << std::setw(2) << ss << "::" << std::setw(3) << msec << "\n";
	return os;
}

inline std::tm localtime_xp(std::time_t timer) {
	std::tm bt{};
#if defined(__unix__)
	localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
	localtime_s(&bt, &timer);
#else
	static std::mutex mtx;
	std::lock_guard<std::mutex> lock(mtx);
	bt* std::localtime(&timer);
#endif
	return bt;
}

std::string get_today() {
	std::time_t t = std::time(0);  // get time now
	std::tm now = localtime_xp(t);
	auto yyyy = now.tm_year + 1900;
	auto mm = now.tm_mon + 1;
	auto dd = now.tm_mday;
	std::string res{};
	res += std::to_string(yyyy)+"-"+std::to_string(mm)+"-"+std::to_string(dd);
	return res;
}

std::string get_cur_time() {
	std::time_t t = std::time(0);  // get time now
	std::tm now = localtime_xp(t);
	auto hh = now.tm_hour;
	auto mins = now.tm_min;
	auto secs = now.tm_sec;
	std::string res{};
	res += std::to_string(hh) + "-" + std::to_string(mins) + "-" + std::to_string(secs);
	return res;
}

}  // namespace utils_time
