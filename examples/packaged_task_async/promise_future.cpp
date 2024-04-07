#include <deque>
#include "iostream"
#include <future>
#include <functional>
int task1(int a,int b){
	int ret_a = a*a;
	int ret_b = b*2;
	return ret_a+ret_b;
}

int main()
{

	std::promise<int> promise_ret;
	std::future<int>f_ret;
	std:: future<int>fu = std::async(task1,1,2);
	std:: future<int>fu2 = std::async(std::launch::deferred,task1,1,2);
	std:: future<int>fu1 = std::async(std::launch::async,task1,1,2);
	std::cout <<fu.get()<<std::endl;


	std::packaged_task<int(int,int)>task(task1);
	task(1,2);
	std::cout <<task.get_future().get()<<std::endl;

	std::packaged_task<int()>task_bind(std::bind(task,1,2));
	task_bind();
	std::cout <<task.get_future().get()<<std::endl;
}