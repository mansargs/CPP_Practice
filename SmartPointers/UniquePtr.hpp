#ifndef UNIQUEPTR_HPP
# define UNIQUEPTR_HPP

#include <cstddef>

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


template <typename T, typename D = DefaultDeleter<T>>
class UniquePtr {
	private:
		T* data;
		D  deleter;

	public:
		explicit UniquePtr(T* ptr = nullptr) noexcept
			: data(ptr), deleter() {}

		UniquePtr(T* ptr, D del) noexcept
			: data(ptr), deleter(del) {}

		~UniquePtr() noexcept {
			if (data)
				deleter(data);
		}

		UniquePtr(const UniquePtr&) = delete;
		UniquePtr& operator=(const UniquePtr&) = delete;

		UniquePtr(UniquePtr&& other) noexcept
			: data(other.data), deleter(other.deleter) {
			other.data = nullptr;
		}

		UniquePtr& operator=(UniquePtr&& other) noexcept {
			if (this != &other) {
				if (data)
					deleter(data);
				data = other.data;
				deleter = other.deleter;
				other.data = nullptr;
			}
			return *this;
		}

		T* get() const { return data; }

		T* release() {
			T* temp = data;
			data = nullptr;
			return temp;
		}

		void reset(T* ptr = nullptr) {
			T* old = data;
			data = ptr;
			if (old)
				deleter(old);
		}

		T& operator*() const {
			return *data;
		}

		T* operator->() const{
			return data;
		}

		operator bool() const {
			return data != nullptr;
		}

		D& get_deleter() const {
			return deleter;
		}

		void swap(UniquePtr& other) {
			using std::swap;
			swap(this->data, other.data);
			swap(this->deleter, other.deleter);
		}

		bool operator==(std::nullptr_t) const { return data == nullptr; }
		bool operator!=(std::nullptr_t) const { return data != nullptr; }
};

template<typename T, typename... Args>
UniquePtr<T> my_make_unique(Args&&... args)
{
	return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
UniquePtr<T[]> my_make_unique(size_t n)
{
	return UniquePtr<T[]>(new T[n]);
}

#endif
