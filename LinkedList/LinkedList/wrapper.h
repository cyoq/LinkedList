#pragma once

template <typename T>
class Wrapper {
public:
	Wrapper(T *ptr) : ptr(ptr) {}
	T* operator*() {
		return ptr;
	}
	void wrap(T *ptr) { this->ptr = ptr; }
private:
	T *ptr;
};