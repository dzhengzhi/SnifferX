#pragma once

#include <atomic>
#include <list>
#include <mutex>
#include <condition_variable>

using namespace std;


namespace snifferx {

	namespace utils {

		//��������
		template<class T>
		class SnBlockingQueue
		{
		public:
			bool TryTake(T & t) {

				if (size_.load() > 0) {
					t = Take();
					return true;
				}
				return false;
			}

			T Take() {
				unique_lock<mutex> lock(mutex_);
				condition_variable_.wait(lock, [this] {	//Pred����mutex.lock()��ִ�е�
					return Count() > 0;
				});
				T k(list_.front());
				list_.pop_front();
				size_.fetch_sub(1);	//����ԭ�Ӽ�
				return k;
			}

			void Put(const T & value) {
				{
					lock_guard<mutex> lock(mutex_);
					list_.push_back(value);
					size_.fetch_add(1);	 //����ԭ�Ӽ�
				}	//����ȥ��
				condition_variable_.notify_all();
			}

			int Count() {
				return size_.load();
			}

			SnBlockingQueue() {};
			~SnBlockingQueue() {};
		private:
			list<T> list_;
			atomic_int size_;
			mutex mutex_;
			condition_variable condition_variable_;
		};
	}
}