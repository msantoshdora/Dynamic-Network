#ifndef REQUEST_H
#define REQUEST_H

class Request{
	public:
		int source;
		int destination;
		double holding_time;
		double bandwidth;
		float sinr;
	public:
		Request();
		Request(int src, int dest, double h_time, double bw,float sn);
		void setRequest(int src, int dest, double h_time, double bw,float sn);
		
};

#endif
