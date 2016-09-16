#include"request.h"
#include"network.h"
#include<iostream>
#include<random>
#include<stdlib.h>
#include<time.h>

//Network constructor
Network::Network(){}

//Network request generator
Request Network::generateRequest(int source){
	Request obj;
	std::default_random_engine generator;
	std::poisson_distribution<int> distribution(10);
	/* initialize random seed */
	srand(time(NULL));

	src = source;
	dest = rand() % 6 +1;

	bw = distribution(generator);
	htime = distribution(generator);
	obj.setRequest(src,dest,bw,htime);
	std::cout<<"Matching: "<<obj.destination<<"\n";	
	return obj;
}

//Resource allocator
void Network::allocateBandwidth(){

}

//Initialize the serving
void Network::beginServing(){}

//Release the Resource after finishing the request
void Network::releaseResources(){}


