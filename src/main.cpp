#include<iostream>
#include<bits/stdc++.h>
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
std::priority_queue<Request> reqs;

void paus(double holdTime);
void assignWavelengths();
int displayPath(std::multimap<int,Request> network);

/**
 * To Add a Priority to deadline for the priority
 */
bool operator<(const Request& a, const Request& b) {
    return a.sinr < b.sinr;
}

int main(){
	while(1){
	clock_t begin = clock();
	double diff = 0;
	int req;
	

	std::multimap<int,Request> network;          //THIS STORES REQUEST *** 


       // std::multimap<int,Request>::key_compare mycomp = network.key_comp();

	std::random_device rd;
        std::default_random_engine generator(rd());
	//std::default_random_engine generator;
	std::default_random_engine request_generator(rd());
	std::poisson_distribution<int> distribution(NETWORK_MEAN);
	std::poisson_distribution<int> no_of_request(REQUESTS);
	
	std::fstream myfile;                //To be removed at the end(Just to verify the time duration)

	Network n1;

	myfile.open("result.txt", std::ios::out | std::ios::trunc);      //To be removed at the end
  	
	//For first 6 seconds             
	for(int i = 1; i<= NETWORK_NODES; i++){                  // i is the request number
	
	       req = no_of_request(request_generator);
	       std::cout<<"For "<<i<<" Station, Number of Requests: "<<req<<"\n";
	      
	       Request r1;
	       diff = 0;                         //Intializing to 0
	       begin = clock();		        // Recording the beginning Time
		while((diff < 1) ){
	
			while((diff<1) && (req>0) ){
				r1 = n1.generateRequest(i);	
				reqs.push(r1);	
				network.insert(std::pair<int,Request> (i,r1));             //Storing of request in network
				clock_t end = clock();
				diff = double(end - begin) / CLOCKS_PER_SEC;
				req--;
			}
			clock_t end = clock();
			diff = double(end - begin)/CLOCKS_PER_SEC;
		}
	}
	currentWavelength = 0;
	//assignWavelengths();	
	displayPath(network);
	


	myfile << diff;            //To be removed at the end
	myfile.close();            //To be removed at the end
	}
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
	 int lsource,ldestination;      // For Iterator way
	 int ls,ld;                     //For Priority Queue way
	 int wl_used;
	 int time_hold;
	 std::priority_queue<Request> temp;
	 temp = reqs;
	 Request temp1;
	 int count_number_of_requests_served = 0;
	  double seconds_elapsed;
	 const clock_t start = clock();
// do stuff here

	 do {   
		
		 count_number_of_requests_served++;
   		 creat();
		 temp1 = temp.top();
		 lsource = (*it).first;             //For Iterator way
		 ls = temp1.source;
   		 ld = temp1.destination;
		 ldestination = (*it).second.destination;
 /*  		 

		 std::cout <<"\nSource: "<< (*it).first << " Destination: " << (*it).second.destination <<"\n";
		 SPT(lsource,ldestination);
		
		 std::cout<<"Bandwidth Given: "<<(*it).second.bandwidth<<"\n";
		 std::cout<<"Processing Time: "<<(*it).second.holding_time<<"\n";
		 //Wait for the holding time of the request then show path
	          paus((*it).second.holding_time);
		  //For Displaying Path
		 time_hold = (*it).second.holding_time;   //for iterator
*/
// For Priority Queue
		 std::cout <<"\nSource: "<< ls<< " Destination: " << ld<<"\n";
		 SPT(ls,ld);
		
		 std::cout<<"Bandwidth Given: "<<temp1.bandwidth<<"\n";
		 std::cout<<"Processing Time: "<<temp1.holding_time<<"\n";
		 std::cout<<"Signal to Noise Ratio : "<<temp1.sinr<<"\n";
		 //Wait for the holding time of the request then show path
	          paus(temp1.holding_time);
		 //For Displaying path
		  time_hold = temp1.holding_time;          //for priority queue

//End of priority Queue


		 

		while(wavelengths[currentWavelength] != 0){
			 if(wavelengths[currentWavelength] != 0){
				std::cout<<"Allocated Wavelength: "<<wavelengths[currentWavelength]<<"\n";			
				wavelengths[currentWavelength] ==0;
					
				currentWavelength++;
				currentWavelength = currentWavelength%WL;
				break;
			 }else{
			      wavelengths[currentWavelength] =  wavelengths[currentWavelength + WL];
			      currentWavelength++;
				currentWavelength = currentWavelength%WL;
	    		}
		
		}
		
		
	

   		 for(int k=top;k>=0;k--){
			if(k==top){
				std::cout<<"Path: ";
			}
			
 			std::cout<<stack[k];
			
			if(time_hold == 0){
				std::cout<<"Cannot allocate this resource!\n";
				break;			
			}
			if(k>0){
				
				std::cout<<"-->";
				//paus(clock(),&time_hold);
			}
		  }
		std::cout<<"\n";
	        temp.pop();               //Deleting the Request which is served
	//To check if under given serving time or not.
	clock_t now = clock();
        clock_t delta = now - start;
         seconds_elapsed = static_cast<double>(delta) / CLOCKS_PER_SEC;
   		 
 	 } while (seconds_elapsed < 15 );    //&& mycomp((*it++).first, highest)

std::cout<<"Total Requests served within 1 unit time: "<<count_number_of_requests_served<<"\n";

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
/**
*  To give a pause till the holding time of the serving request gets finished.
*/
void paus(double holdTime){
	std::cout<<"Serving... \n";


	const clock_t start = clock();
	clock_t now = clock();

	clock_t delta = now - start;
	double seconds_elapsed = static_cast<double>(delta) / CLOCKS_PER_SEC;
	while(seconds_elapsed <= (holdTime/10)){
	
		clock_t now = clock();
		clock_t delta = now - start;
		seconds_elapsed = static_cast<double>(delta) / CLOCKS_PER_SEC;
	}
	
}
