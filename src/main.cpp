#include<iostream>
#include<ctime>
#include<fstream>
#include"request.h"
#include"network.h"
#include<random>

#define  NETWORK_MEAN 6
#define  NETWORK_NODES 6
#define  REQUESTS 6

int main(){
	
	clock_t begin = clock();
	double diff = 0;

	std::default_random_engine generator;
	std::default_random_engine request_generator;
	std::poisson_distribution<int> distribution(NETWORK_MEAN);
	std::poisson_distribution<int> no_of_request(REQUESTS);
	
	std::fstream myfile;
	
	myfile.open("result.txt", std::ios::out | std::ios::trunc);
  	for(int i = 1; i<= NETWORK_NODES; i++){
	       int req = no_of_request(request_generator);
	       std::cout<<"For "<<i<<"Station: \n";
	       Network n1;
	       Request r1;
	       diff = 0;                         //Intializing to 0
	       begin = clock();		        // Recording the beginning Time
		while(diff < 1 ){
		
			while((diff<1) && req){
			r1 = n1.generateRequest();		
			clock_t end = clock();
			diff = double(end - begin) / CLOCKS_PER_SEC;
			req--;
			}
			clock_t end = clock();
			diff = double(end - begin)/CLOCKS_PER_SEC;
		}
	}

	myfile << diff;
	myfile.close();
	return 0;
}

