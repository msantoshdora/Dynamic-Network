#ifndef NETWORK_H
#define NETWORK_H

class Network{
	private:
		
	public:
		Network();
		void generateRequest();
		void allocateBandwidth();
		void beginServing();
		void releaseResources();
};

#endif
