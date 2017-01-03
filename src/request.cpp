#include "request.h"


//Default Constructor
Request::Request(){ 
	setRequest(0,0,0,0,0);
}
// Request constructor
Request::Request(int src, int dest, double h_time, double bw,float sn){

	setRequest(src,dest,h_time,bw,sn);

}
// Request member Function to set request
void Request::setRequest(int src, int dest, double h_time, double bw, float sn){
	source = src;
	destination = dest;
	holding_time = h_time;
	bandwidth = bw;
	sinr = sn;
}
