#include "request.h"


//Default Constructor
Request::Request(){}
// Request constructor
Request::Request(int src, int dest, double h_time, double bw){

	setRequest(src,dest,h_time,bw);

}
// Request member Function to set request
void Request::setRequest(int src, int dest, double h_time, double bw){
	source = src;
	destination = dest;
	holding_time = h_time;
	bandwidth = bw;
}
