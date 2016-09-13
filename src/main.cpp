#include<iostream>
#include<ctime>
#include<fstream>
#include"request.h"
#include"network.h"



int main(){
	
	clock_t begin = clock();
	double diff = 0;
	std::fstream myfile;
	myfile.open("result.txt", std::ios::out | std::ios::trunc);

	while(diff < 1){
		
		clock_t end = clock();
		diff = double(end - begin) / CLOCKS_PER_SEC;
	
	}
	myfile << diff;
	myfile.close();
	return 0;
}

