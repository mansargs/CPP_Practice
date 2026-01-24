#ifndef WEAK_PTR_HPP
# define WEAK_PTR_HPP

# include "SharedPtr.hpp"

template<typename T>
class WeakPtr {
	private:
		ControlBlock<T>* ctrl;

		void release() {
			if (!ctrl)
				return ;
			--ctrl->weak_count;
			if (ctrl->weak_count == 0 && ctrl->strong_count == 0) {
				delete(ctrl);
				ctrl = nullptr;
			}
		}
	public:
		WeakPtr() : ctrl(nullptr) {}

		WeakPtr(const SharedPtr<T>& shp) : ctrl(shp.ctrl) {
			if (ctrl)
				++ctrl->weak_count;
		}

		WeakPtr(const WeakPtr<T>& other) : ctrl(other.ctrl) {
			if (ctrl)
				++ctrl->weak_count;
		}

		WeakPtr(WeakPtr<T>&& other) noexcept : ctrl(other.ctrl) {
			other.ctrl = nullptr;
		}

		~WeakPtr() {
			release();
		}

		WeakPtr<T>& operator=(const WeakPtr<T>& other) {
			if (this != &other) {
				release();
				ctrl = other.ctrl;
				if (ctrl)
					++ctrl->weak_count;
			}
			return *this;
		}

		WeakPtr<T>& operator=(WeakPtr<T>&& other) noexcept {
			if (this != &other) {
				release();
				ctrl = other.ctrl;
				other.ctrl = nullptr;
			}
			return *this;
		}

		SharedPtr<T> lock() const {
			if (ctrl && ctrl->strong_count > 0)
				return SharedPtr<T>(ctrl);
			return SharedPtr<T>();
		}

		bool expired() const {
			return !ctrl || ctrl->strong_count == 0;
		}

		size_t use_count() const {
			return ctrl ? ctrl->strong_count : 0;
		}

		explicit operator bool() const {
			return !expired();
		}

		void reset() {
			release();
			ctrl = nullptr;
		}

		void swap(WeakPtr<T>& other) noexcept {
			std::swap(this->ctrl, other.ctrl);
		}
};

#endif
