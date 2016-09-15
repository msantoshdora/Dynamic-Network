#include"request.h"
#include"network.h"
#include<iostream>
//Network constructor
Network::Network(){}

//Network request generator
Request Network::generateRequest(){
	Request obj;
	std::cout<<"Hello\n";
	return obj;
}

//Resource allocator
void Network::allocateBandwidth(){

}

//Initialize the serving
void Network::beginServing(){}

//Release the Resource after finishing the request
void Network::releaseResources(){}


