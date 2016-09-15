#ifndef REQUEST_H
#define REQUEST_H

class Request{
	private:
		int source;
		int destination;
		double holding_time;
		double bandwidth;
	public:
		Request();
		Request(int src, int dest, double h_time, double bw);
		void setRequest(int src, int dest, double h_time, double bw);
		
};

#endif
