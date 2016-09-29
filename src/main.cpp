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
#define  WL 5         //Number of Wave Lengths

int wavelengths[WL*2];
int currentWavelength;

void paus(clock_t begin,int *holdTime);
void assignWavelengths();
int displayPath(std::multimap<int,Request> network);


int main(){
	
	clock_t begin = clock();
	double diff = 0;
	int req;
	//int wavelengths[WL];

	std::multimap<int,Request> network;
       // std::multimap<int,Request>::key_compare mycomp = network.key_comp();

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
				network.insert(std::pair<int,Request> (i,r1));
				clock_t end = clock();
				diff = double(end - begin) / CLOCKS_PER_SEC;
				req--;
			}
			clock_t end = clock();
			diff = double(end - begin)/CLOCKS_PER_SEC;
		}
	}
	currentWavelength = 0;
	assignWavelengths();	
	displayPath(network);

	myfile << diff;
	myfile.close();
	return 0;
}


/**
 * Input: Object of the network which is a mapping from node number to Request Object
 * To Display the path and the allocated Resources 
 */
int displayPath(std::multimap<int,Request> network){

 	 std::multimap<int,Request>::key_compare mycomp= network.key_comp();
	 std::multimap<int,Request>::iterator it = network.begin(); //To iterator over elements
	
         int highest = network.rbegin()->first;     // key value of last element
	 int lsource,ldestination;
	 int wl_used;
	  int time_hold;
	 do {   
   		 creat();
		 lsource = (*it).first;
		 ldestination = (*it).second.destination;
   		 std::cout <<"Source: "<< (*it).first << " Destination: " << (*it).second.destination <<"\n";
		 SPT(lsource,ldestination);
		// printf("\n shortest path between %d to %d ==%d\n path  ",lsource,ldestination,dist[ldestination]);
		 std::cout<<"Bandwidth Allocated: "<<(*it).second.bandwidth<<"\n";
		while(wavelengths[currentWavelength] != 0){
			 if(wavelengths[currentWavelength] != 0){
				std::cout<<"Allocated Wavelength: "<<wavelengths[currentWavelength]<<"\n";			
				wavelengths[currentWavelength] ==0;
				//(++currentWavelength)%= WL;	
				currentWavelength++;
				currentWavelength = currentWavelength%WL;
				break;
			 }else{
			      wavelengths[currentWavelength] =  wavelengths[currentWavelength + WL];
			      currentWavelength++;
				currentWavelength = currentWavelength%WL;
	    		}
		
		}
		
		time_hold = (*it).second.holding_time;
   		 for(int k=top;k>=0;k--){
			if(k==top){
				std::cout<<"Path: ";
			}
 			std::cout<<stack[k];
			paus(clock(),&time_hold);
			if(time_hold == 0){
				std::cout<<"Cannot allocate this resource!\n";
				break;			
			}
			if(k>0){
				std::cout<<"-->";
			}
		  }
		std::cout<<"\n";

   		 
 	 } while (mycomp((*it++).first, highest) );

return 0;


}

/**
 *  Assign available wavelengths
 */
void assignWavelengths(){
	int wl1 = 64;
	for(int i = 0;i<WL;i++){
		wavelengths[i] = wl1;
		wavelengths[i+WL] = wl1;  //To keep a temporary Storage of the wavelengths 
		wl1= wl1*2;			
	}
}

void paus(clock_t begin,int *holdTime){
	
	double diff = 0;
	diff = 0;                         //Intializing to 0
	
   	while(diff <=0.1){
        	clock_t end = clock();
		diff = double(end - begin) / CLOCKS_PER_SEC;
		holdTime--;
	}
	
}
