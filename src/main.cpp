#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
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
#define  WL 5                   //Number of Wave Lengths
#define ALLOWED_SERVE_TIME 20

int wavelengths[WL*2];         //To store available Wavelengths
int currentWavelength;	       //Current Available Wavelength to allocate
std::priority_queue<Request> reqs;	//Data Structure to store Requests generated in unit time to serve
std::priority_queue<Request> reqsS1,reqsS2,reqsS3,reqsS4,reqsS5,reqsS6,t;  //Individual request storage for stations
int total_requests;

void paus(double holdTime);
void assignWavelengths();
void displayResult(int total_requests,int count_number_of_requests_served);
double displayPath(std::multimap<int,Request> network,std::priority_queue<Request>&temp,double elapsed_time,clock_t start);
bool checkDeadline(std::priority_queue<Request> temp,double delayedTime);

/**
 * To Add a Priority to signal to noise ratio to server the request in that order.
 */
bool operator<(const Request& a, const Request& b) {
    return a.sinr < b.sinr;
}

int main(){
	double temp_elapsed_time = 0;
	std::fstream outputFile; 
        outputFile.open("requestFile.txt", std::ios::out | std::ios::trunc); 
        //To contiue for indefinite period
	while(1){
	        total_requests = 0;
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
		       std::cout<<"For Station "<<i<<" , Number of New Requests Generated: "<<req<<"\n";
		       
	      	       total_requests+=req;
		       Request r1;
		       diff = 0;                         //Intializing to 0
		       begin = clock();		        // Recording the beginning Time
			while((diff < 1) ){
	
				while((diff<1) && (req>0) ){
					
					r1 = n1.generateRequest(i);	
					reqs.push(r1);	
					network.insert(std::pair<int,Request> (i,r1));             //Storing of request in network
				 	if(i == 1){
						//std::cout<<"Number of Requests Generated..."<<i<<"\n";
						reqsS1.push(r1);					
					}
					if(i == 2){
						reqsS2.push(r1);					
					}
					if(i == 3){
						reqsS3.push(r1);					
					}
					if(i == 4){
						reqsS4.push(r1);					
					}
					if(i == 5){
						reqsS5.push(r1);					
					}
					if(i == 6){
						reqsS6.push(r1);					
					}
					clock_t end = clock();
					diff = double(end - begin) / CLOCKS_PER_SEC;
					req--;
				}
			clock_t end = clock();
			diff = double(end - begin)/CLOCKS_PER_SEC;
		}
	}
		currentWavelength = 0;
		const clock_t start = clock();
		int serial = 1;	
		//std::priority_queue<Request> t;
		temp_elapsed_time = 0;
		while(temp_elapsed_time < ALLOWED_SERVE_TIME){ 
		        
			
			if(serial == 1) t = reqsS1;
			if(serial == 2) t = reqsS2;
			if(serial == 3) t = reqsS3;
			if(serial == 4) t = reqsS4;
			if(serial == 5) t = reqsS5;
			if(serial == 6) t = reqsS6;
                        if(serial == 1){
				std::cout<<"Size: "<<t.size()<<"\n";
			}
			temp_elapsed_time = displayPath(network,t,temp_elapsed_time,start);
			if(serial == 1) reqsS1 = t;
			if(serial == 2) reqsS2 = t;
			if(serial == 3) reqsS3 = t;
			if(serial == 4) reqsS4 = t;
			if(serial == 5) reqsS5 = t;
			if(serial == 6) reqsS6 = t;
			++serial;
		}
		if(serial <=6){
			std::cout<<"\n Subscriber Stations: ";
		}
		while(serial <= 6){
			std::cout<<serial<<",";
			++serial;
		}
		std::cout<<" aren't served within 1 unit time\n";

		myfile << diff;            //To be removed at the end
		myfile.close();            //To be removed at the end
	}

	outputFile.close();
		return 0;
}


/**
 * Input: Object of the network which is a mapping from node number to Request Object
 * To Display the path and the allocated Resources 
 */
double displayPath(std::multimap<int,Request> network,std::priority_queue<Request>&temp,double se,clock_t start){

 	 std::multimap<int,Request>::key_compare mycomp= network.key_comp();
	 std::multimap<int,Request>::iterator it = network.begin(); //To iterator over elements
	 
         int highest = network.rbegin()->first;     // key value of last element
	 int lsource,ldestination;      // For Iterator way
	 int ls,ld;                     //For Priority Queue way
	 int wl_used;
	 int time_hold;
	 int trequests;

	// std::priority_queue<Request> temp = reqs;
	//std::cout<<"Inside displayPath Function size: "<<temp.size()<<"\n";
	 Request temp1;
	 int count_number_of_requests_served = 0;
	 double seconds_elapsed, delayedTime;
	 trequests  = temp.size(); 


	 do {   
		 clock_t now1 = clock();
		 temp1 = temp.top();
        	 clock_t delta1 = now1 - temp1.birth ;          //birth is the request generation time.(Time request was born)
         	 delayedTime = (double)delta1 / CLOCKS_PER_SEC * 100.0;                //To calculate the deadline
			
		 while(checkDeadline(temp,delayedTime) && !temp.empty()){
		       //Checks if the Requests has not crossed the deadline
			    std::cout<<delayedTime<<"  Request Deadline: "<<temp.top().deadline<<"\n";
                            std::cout<<"Request Discarded because deadline is over!!\n";
			     temp.pop();
			   
		 }

		if(temp.empty()){
			//To handle exception case
		    t = temp;
		    
		    return std::max(seconds_elapsed,se);		
		}
		 count_number_of_requests_served++;
   		 creat();
		 temp1 = temp.top();
		 lsource = (*it).first;             //For Iterator way
		 ls = temp1.source;
   		 ld = temp1.destination;
		/* if(ls == ld || ((ls==1 && ld == 6) || (ls==6 && ld ==1)  ) ){
			temp.pop();
		  	trequests--;
			continue;
		 } */
		 
		 ldestination = (*it).second.destination;
 /*   // MULTIMAP DATA STRUCTURE USED TO DISPLAY REQUESTS		 

		 std::cout <<"\nSource: "<< (*it).first << " Destination: " << (*it).second.destination <<"\n";
		 SPT(lsource,ldestination);
		
		 std::cout<<"Bandwidth Given: "<<(*it).second.bandwidth<<"\n";
		 std::cout<<"Processing Time: "<<(*it).second.holding_time<<"\n";
		 //Wait for the holding time of the request then show path
	          paus((*it).second.holding_time);
		  //For Displaying Path
		 time_hold = (*it).second.holding_time;   //for iterator
*/
// PRIORITY QUEUE DATA STRUCTURE IS USED TO DISPLAY THE REQUESTS
		 std::cout <<"\n             Source: "<< ls<< " Destination: " << ld<<"\n";
		 SPT(ls,ld);
		
		 std::cout<<"              Bandwidth Given: "<<temp1.bandwidth<<"\n";
		 std::cout<<"              Processing Time: "<<temp1.holding_time<<"\n";
		 std::cout<<"              Signal to Noise Ratio : "<<temp1.sinr<<"\n";
		 //Wait for the holding time of the request then show path
	          paus(temp1.holding_time);
		 //For Displaying path
		  time_hold = temp1.holding_time;          //for priority queue

//END OF PRIORITY QUEUE DATA STRUCTURE


		 

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
				std::cout<<"               Path: ";
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
         	seconds_elapsed = static_cast<double>(delta) / CLOCKS_PER_SEC + se;
   		 
 	 } while (seconds_elapsed < ALLOWED_SERVE_TIME && !temp.empty());    //&& mycomp((*it++).first, highest)

	t = temp;               //To manage the Queue size in different Functions
	//std::cout<<"Size after removing: "<<temp.size()<<" Seconds Elapsed: "<<seconds_elapsed<<"\n";
 	displayResult(trequests,count_number_of_requests_served);

return seconds_elapsed;


}

/**
*  If deadline gets over,then it returns true;else false
*/

bool checkDeadline(std::priority_queue<Request> temp,double delayedTime){

	if(temp.empty()) return false;
	if(temp.top().deadline > delayedTime) return false;

	return true;
}

void displayResult(int total_requests,int count_number_of_requests_served){

	std::cout<<"Total Requests: "<<total_requests<<"\n";
	std::cout<<"Requests served within 1 unit time: "<<count_number_of_requests_served<<"\n\n";
}

/**
 *  Assign available wavelengths
 */
void assignWavelengths(){
	int wl1 = 64;
	for(int i = 0; i<WL;i++){
		wavelengths[i] = wl1;
		wavelengths[i+WL] = wl1;  //To keep a temporary Storage of the wavelengths 
		wl1= wl1*2;			
	}
}
/**
*  To give a pause till the holding time of the serving request gets finished.
*/
void paus(double holdTime){
	std::cout<<"\n              Serving... \n";


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
