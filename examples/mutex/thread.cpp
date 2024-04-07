//
// Created by 29451 on 2024/4/5.
//
#include <thread>
#include <mutex>
#include "iostream"
#include <vector>
#include <iomanip>
#include "algorithm"
#include <atomic>
std::mutex mtx;
std::mutex mtx2;
typedef  struct  abbox{
	float x,y,w,h;
};
typedef  struct axdl_object_t{
int label;
abbox bbox;
};
void test(){
	int index1,index2;
	std::vector<axdl_object_t> objvector1;
	std::vector<axdl_object_t> objvector2;
	axdl_object_t mObjects[8];
	mObjects[0].label = 0;
	mObjects[1].label = 14;
	mObjects[2].label = 0;
	mObjects[3].label = 13;
	mObjects[4].label = 1;
	mObjects[5].label = 20;
	mObjects[6].label = 1;
	mObjects[7].label = 17;

	mObjects[0].bbox.y = 10;
	mObjects[1].bbox.y = 10;
	mObjects[2].bbox.y = 20;
	mObjects[3].bbox.y = 20;
	mObjects[4].bbox.y = 30;
	mObjects[5].bbox.y = 30;
	mObjects[6].bbox.y = 40;
	mObjects[7].bbox.y = 40;

	for (int i=0;i<8;i++){
		if(mObjects[i].label<=1){
			objvector1.push_back(mObjects[i]);
			index1 = index1+1;
		}
		else if (mObjects[i].label<=29){
			objvector2.push_back(mObjects[i]);
			index2 = index2+1;
		}
	}
	if ((index1 ==4)and(index2 ==4)){
		std::sort(objvector1.begin(),objvector1.end(),[](const axdl_object_t& a,const axdl_object_t& b ){
			return a.bbox.y< b.bbox.y;
		});
		std::sort(objvector2.begin(),objvector2.end(),[](const axdl_object_t& a,const axdl_object_t& b ){
			return a.bbox.y< b.bbox.y;
		});
		printf("checking ocr results.....\n");
		std::vector<unsigned char> dataArray = {0xFF, 0xFF,0xFF,0xFF,
		                                        (unsigned char)objvector2[0].label,
		                                        (unsigned char)(objvector1[0].label+1),
		                                        (unsigned char)objvector2[1].label,
		                                        (unsigned char)(objvector1[1].label+1),
		                                        (unsigned char)objvector2[2].label,(unsigned char)(objvector1[2].label+1),
		                                        (unsigned char)objvector2[3].label,(unsigned char)(objvector1[3].label+1),
		                                        0xfe,0xfe,0xfe,0xfe};
		for (unsigned char val : dataArray) {
			std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)val << " ";
		}
		std::cout << std::endl;
	}
}
int globalvariable = 0;

void task1(){
		for (int i =0;i<10000;i++){
			mtx.lock();
			globalvariable++;
			globalvariable--;
			mtx.unlock();
		}
}
int task2(){
	for (int i =0;i<10000;i++){
		mtx.lock();
		globalvariable++;
		if(i==1000){
			return 0;//死锁
		}
		globalvariable--;
		mtx.unlock();
	}
}
void task3(){
	for (int i =0;i<10000;i++){
		mtx.lock();
		mtx2.lock();//已经被task4拿走了
		globalvariable++;
		globalvariable--;
		mtx.unlock();
		mtx2.unlock();
	}
}
void task4(){
	for (int i =0;i<10000;i++){
		mtx2.lock();
		mtx.lock();//已经被task1拿走了
		globalvariable++;
		globalvariable--;
		mtx2.unlock();
		mtx.unlock();

	}
}
void task5(){

	for (int i =0;i<10000;i++){
		std::lock_guard<std::mutex> guard(mtx);
		std::lock_guard<std::mutex> guard2(mtx2);//可以避免没有释放
		globalvariable++;
		globalvariable--;

	}
}
class A{//类似这种方式
	A(std::mutex & mtx){
		mtx.lock();
	}
	~A(){
		mtx.unlock();
	}
private:
	std::mutex mtx;
};
void task6(){
	for (int i =0;i<10000;i++){
		std::lock(mtx,mtx2);
		globalvariable++;
		globalvariable--;

	}
}

void task7(){

	for (int i =0;i<10000;i++){
//		std::lock_guard<std::mutex> guard(mtx);
//		std::lock_guard<std::mutex> guard2(mtx2);//可以避免没有释放,但是不灵活，只能作用在整个循环
		std::unique_lock<std::mutex> lock1(mtx);
		lock1.unlock();//更加灵活
		globalvariable++;
		globalvariable--;

	}
}

std::atomic<int >atomicvariable = 0;//自动涉及上锁解锁

void task8(){

	for (int i =0;i<10000;i++){
//		std::lock_guard<std::mutex> guard(mtx);
//		std::lock_guard<std::mutex> guard2(mtx2);//可以避免没有释放,但是不灵活，只能作用在整个循环
		std::unique_lock<std::mutex> lock1(mtx);
		lock1.unlock();//更加灵活
		globalvariable++;
		globalvariable--;

	}
}
int main(){
	std::thread thread1(test);
	thread1.join();
	std::thread thread2(task1);
	std::thread thread3(task1);
	thread2.join();
	thread3.join();
	std::cout<<"variable:"<<globalvariable<<std::endl;
}
