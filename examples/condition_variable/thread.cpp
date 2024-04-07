#include <mutex>
#include <atomic>
#include <deque>
#include <condition_variable>
#include <thread>
#include "iostream"
#include <semaphore>
std::mutex mtx;
std::deque <int> q;
std::condition_variable cv;
int leastmaxvalue = 6;
std::counting_semaphore<6> csem(6);
//using std::binary_semaphore  = std::counting_semaphore<1>;
std::binary_semaphore bsem(0);
void task1(){
	int i = 0;
	while(true){
		std::unique_lock<std::mutex>lock(mtx);
		q.push_back(i);
		cv.notify_one();//随机唤醒一个
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		if(i<999999){
			i++;
		}
		else{
			i=0;
		}
	}
}
void task2(){
	int data = 0;
	while(true){
		std::unique_lock<std::mutex>lock(mtx);
		while(q.empty()){
			cv.wait(lock);//休眠，顺便释放掉锁lock.unlock()
		}

			data = q.front();
			q.pop_front();
			std::cout<<"deque2:"<<data<<std::endl;
		}
}
void task3(){
	int data = 0;
	while(true){
		std::unique_lock<std::mutex>lock(mtx);
		while(q.empty()){
			cv.wait(lock);//休眠，顺便释放掉锁lock.unlock()
		}

		data = q.front();
		q.pop_front();
		std::cout<<"deque3:"<<data<<std::endl;
	}
}
void task_sem(){
	std::cout<<"ready to receive:release\n"<<std::endl;

	bsem.acquire();//计数器减一，等于0时会阻塞
	std::cout<<"acquire end\n"<<std::endl;

}
int main()
{
//	std::thread thread1(task1);
//	std::thread thread2(task2);
//	std::thread thread3(task3);
//	thread1.join();
//	thread2.join();
//	thread3.join();
	std::thread t(task_sem);
	t.join();
	std::cout<<"ready to signal:release\n"<<std::endl;
	bsem.release();//会让计数器加一
	std::cout<<"signal end\n"<<std::endl;


	return 0;
}