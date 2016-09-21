#include<iostream>
#include<ctime>
#include<fstream>
#include"request.h"
#include"network.h"
#include<random>
#include<map>
#include<list>
#include"spt.h"


#define  NETWORK_MEAN 6
#define  NETWORK_NODES 6
#define  REQUESTS 6


int main(){
	
	clock_t begin = clock();
	double diff = 0;
	int req;
	std::multimap<int,Request> network;
        std::multimap<int,Request>::key_compare mycomp = network.key_comp();

	std::random_device rd;
        std::default_random_engine generator(rd());
	//std::default_random_engine generator;
	std::default_random_engine request_generator(rd());
	std::poisson_distribution<int> distribution(NETWORK_MEAN);
	std::poisson_distribution<int> no_of_request(REQUESTS);
	
	std::fstream myfile;
	Network n1;

	myfile.open("result.txt", std::ios::out | std::ios::trunc);
  	
	//For first 6 seconds
	for(int i = 1; i<= NETWORK_NODES; i++){

	       req = no_of_request(request_generator);
	       std::cout<<"For "<<i<<" Station, Number of Requests: "<<req<<"\n";
	      
	       Request r1;
	       diff = 0;                         //Intializing to 0
	       begin = clock();		        // Recording the beginning Time
		while((diff < 1) ){
	
			while((diff<1) && (req>0) ){
				r1 = n1.generateRequest(i);		
				//network[i] = r1;
				network.insert(std::pair<int,Request> (i,r1));
/*
				std::cout<<"Destination: "<<network[i].destination<<"\n";
				std::cout<<"Source: "<<network[i].source<<"\n";
				std::cout<<"Bw: "<<network[i].bandwidth<<"\n";
				std::cout<<"Ht: "<<network[i].holding_time<<"\n";

*/				clock_t end = clock();
				diff = double(end - begin) / CLOCKS_PER_SEC;
				req--;
			}
			clock_t end = clock();
			diff = double(end - begin)/CLOCKS_PER_SEC;
		}
	}
	
	 std::multimap<int,Request>::iterator it = network.begin(); //To iterator over elements
	
         int highest = network.rbegin()->first;     // key value of last element
	 int lsource,ldestination;
	 do {   
   		 creat();
		 lsource = (*it).first;
		 ldestination = (*it).second.destination;
   		 std::cout <<"Source: "<< (*it).first << " Destination: " << (*it).second.destination << '\n';
		 SPT(lsource,ldestination);
		// printf("\n shortest path between %d to %d ==%d\n path  ",lsource,ldestination,dist[ldestination]);
   		 for(int k=top;k>=0;k--){
 			std::cout<<stack[k]<<"--> ";
		  }
		std::cout<<"\n";

   		 
 	 } while (mycomp((*it++).first, highest) );
	

	myfile << diff;
	myfile.close();
	return 0;
}

