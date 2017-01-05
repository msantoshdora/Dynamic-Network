#include "request.h"
#include<bits/stdc++.h>


//Default Constructor
Request::Request(){ 
	setRequest(0,0,0,0,0,0,0);
}
// Request constructor
Request::Request(int src, int dest, double h_time, double bw,float sn,double dl,clock_t br){

	setRequest(src,dest,h_time,bw,sn,dl,br);

}
// Request member Function to set request
void Request::setRequest(int src, int dest, double h_time, double bw, float sn,double dl,clock_t br){
	source = src;
	destination = dest;
	holding_time = h_time;
	bandwidth = bw;
	sinr = sn;
	deadline = dl;
	birth = br;
}
