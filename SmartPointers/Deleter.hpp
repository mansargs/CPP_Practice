#ifndef DELETER_HPP
# define DELETER_HPP

template<typename T>
class DefaultDeleter {
public:
	void operator()(T* ptr) const {
		delete ptr;
	}
};

template<typename T>
class DefaultDeleter<T[]> {
public:
	void operator()(T* ptr) const {
		delete[] ptr;
	}
};

#endif
