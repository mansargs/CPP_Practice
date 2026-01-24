#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP

#include "ControlBlock.hpp"

template<typename T>
class SharedPtr {
	private:
		ControlBlock<T>* ctrl;

		void release() {
			if (!ctrl)
				return;
			--ctrl->strong_count;
			if (ctrl->strong_count == 0) {
				ctrl->deleter(ctrl->data);
				ctrl->data = nullptr;
				if (ctrl->weak_count == 0) {
					delete ctrl;
				}
			}
			ctrl = nullptr;
		}

	public:
		SharedPtr() : ctrl(nullptr) {}

		SharedPtr(T* ptr, Deleter d = DefaultDeleter()) {
			ctrl = new ControlBlock<T>(ptr, d);
		}

		SharedPtr(ControlBlock<T>* c) : ctrl(c) {
			if (ctrl)
				++ctrl->strong_count;
		}

		SharedPtr(const SharedPtr<T>& other) {
			ctrl = other.ctrl;
			if (ctrl)
				++ctrl->strong_count;
		}

		SharedPtr(SharedPtr<T>&& other) noexcept {
			ctrl = other.ctrl;
			other.ctrl = nullptr;
		}

		SharedPtr<T>& operator=(const SharedPtr<T>& other) {
			if (this != &other) {
				release();
				ctrl = other.ctrl;
				if (ctrl)
					++ctrl->strong_count;
			}
			return *this;
		}

		SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept {
			if (this != &other) {
				release();
				ctrl = other.ctrl;
				other.ctrl = nullptr;
			}
			return *this;
		}

		~SharedPtr() {
			release();
		}

		T* get() const {
			return ctrl ? ctrl->data : nullptr;
		}

		T& operator*() const {
			return *get();
		}

		T* operator->() const {
			return get();
		}

		size_t use_count() const {
			return ctrl ? ctrl->strong_count : 0;
		}

		bool unique() const {
			return use_count() == 1;
		}

		explicit operator bool() const {
			return get() != nullptr;
		}

		void reset(T* ptr = nullptr, Deleter d = DefaultDeleter()) {
			release();
			if (ptr)
				ctrl = new ControlBlock<T>(ptr, d);
		}

		void swap(SharedPtr<T>& other) noexcept {
			std::swap(ctrl, other.ctrl);
		}

		template<typename U>
		friend class WeakPtr;
};

#endif
