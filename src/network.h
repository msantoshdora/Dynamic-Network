#ifndef NETWORK_H
#define NETWORK_H

class Network{
	//private:
		
	public:
		Network();
		Request generateRequest();
		void allocateBandwidth();
		void beginServing();
		void releaseResources();
};

#endif
