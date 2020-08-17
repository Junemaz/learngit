#include <iostream>
#include <vector>
#include <map>
using namespace std;

template <typename T>
class UniquePointer {
public:
	UniquePointer() :ptr_(nullptr) {}
	UniquePointer(T* ptr) :ptr_(ptr) {}

	UniquePointer(const UniquePointer&&) = delete;
	UniquePointer(UniquePointer&& other) {
		if (other.ptr_ != this->ptr_) {
			ptr_ = other.ptr_;
			other.ptr_ = nullptr;
		}
	}

	UniquePointer& operator=(const UniquePointer&&) = delete;
	UniquePointer& operator=(UniquePointer&& other) {
		if (other.ptr_ != this->ptr_) {
			ptr_ = other.ptr_;
			other.ptr_ = nullptr;
		}
		return *this;
	}

	operator bool() {
		return ptr_;
	}

	T* get() {
		return ptr_;
	}
	T& operator*() {
		return ptr_;
	}
	T& operator->() {
		return ptr_;
	}
	void reset(T* ptr = nullptr) {
		if (ptr_) {
			ptr_ = nullptr;
		}
		ptr_ = ptr;
	}

	~UniquePointer() {
		if (ptr_ != nullptr) {
			delete ptr_;
		}
	}
private:
	T* ptr_;
};

struct Demo {
	~Demo() {
		cout << "xigoule" << endl;
	}
};


int main() {
	Demo* demo = new Demo();
	UniquePointer<Demo> ptr(demo);
	UniquePointer<Demo> ptrs(new Demo());
	ptr = move(ptr);
	ptr = move(ptrs);

	return 0;
}