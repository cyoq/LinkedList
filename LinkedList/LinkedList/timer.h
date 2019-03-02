#pragma once


#include <chrono>
#include <utility>

#define TIME_NOW() std::chrono::high_resolution_clock::now()

template <typename F, typename ...Args>
double measureTime(F func, Args && ...args) {
	std::chrono::high_resolution_clock::time_point before = TIME_NOW();
	func(std::forward<Args>(args)...);
	return std::chrono::duration_cast<std::chrono::microseconds>(TIME_NOW() - before).count();
};