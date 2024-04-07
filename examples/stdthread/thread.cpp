//
// Created by 29451 on 2024/4/5.
//
#include <thread>
#include "iostream"
#include <vector>
#include <iomanip>
#include "algorithm"

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
int main(){
	std::thread thread1(test);
	thread1.join();
}
