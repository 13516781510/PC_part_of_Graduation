#include <mutex>
#include <atomic>
#include <deque>
#include <condition_variable>
#include <thread>
#include "iostream"
#include <semaphore>
#include <future>
std::mutex mtx;
std::deque <int> q;
std::condition_variable cv;
int leastmaxvalue = 6;
std::counting_semaphore<6> csem(6);
//using std::binary_semaphore  = std::counting_semaphore<1>;
std::binary_semaphore bsem(0);
void task1(int a,int b,int& ret){
	cv.notify_one();
	int ret_a = a*a;
	int ret_b = b*2;
	std::unique_lock<std::mutex>lock(mtx);
	ret = ret_a+ret_b;
}
void task2(int a,int b,std::promise<int> &ret){
	int ret_a = a*a;
	int ret_b = b*2;
	ret.set_value(ret_a+ret_b) ;
}
void task3(int a,std::future<int>& b,std::promise<int> &ret){
	int ret_a = a*a;
	int ret_b = b.get()*2;
	ret.set_value(ret_a+ret_b) ;
}
int main()
{

	int ret = 0;
//	std::thread t(task1,1,2,std::ref(ret));
//	std::unique_lock<std::mutex>lock(mtx);
//	cv.wait(lock);
//	std::cout <<"return value is "<< ret;
//	t.join();
//	return 0;

//std::promise<int> promise1;
//std::future<int>future1;
//future1=promise1.get_future();
//std::thread t(task2,1,2,std::ref(promise1));
//std::cout<<"return value is:"<<future1.get()<<std::endl;
//t.join();

	std::promise<int> promise_ret;
	std::promise<int> promise_in;
	std::future<int>f_ret;
	std::future<int>f_in;
	std::shared_future<int> s_f = f_in.share();
	f_ret=promise_ret.get_future();
	f_in = promise_in.get_future();
	std::thread t(task3,1,std::ref(f_in),std::ref(promise_ret));
	promise_in.set_value(2);
	std::cout<<"return value is:"<<f_ret.get()<<std::endl;
	t.join();
}