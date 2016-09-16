#ifndef NETWORK_H
#define NETWORK_H

class Network{
	private:
		int src;
		int dest;
		double bw;
		double htime;	
	public:
		Network();
		Request generateRequest(int source);
		void allocateBandwidth();
		void beginServing();
		void releaseResources();
};

#endif
