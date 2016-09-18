#include"request.h"
#include"network.h"
#include<iostream>
#include<random>
#include<stdlib.h>
#include<time.h>
#include<climits>


#define V 6

//Network constructor
Network::Network(){}

//Network request generator
Request Network::generateRequest(int source){
	Request obj;
        std::random_device rd;			//For randomly generating default_random_engine
        std::default_random_engine generator(rd());
	std::poisson_distribution<int> distribution(10);
	/* initialize random seed */
	srand(time(NULL));

	src = source;
	dest = rand() % 6 +1;

	bw = distribution(generator);
	htime = distribution(generator);
	obj.setRequest(src,dest,bw,htime);
	std::cout<<"Holding Time: "<<htime<<"\n";	
	return obj;
}

//Resource allocator
void Network::allocateBandwidth(){
	
}

//Initialize the serving
void Network::beginServing(){}

//Release the Resource after finishing the request
void Network::releaseResources(){}

//A utility function to find the vertex with minimum distance
//value, from the set of vertices not yet included in shortest
//path tree
int Network::minDistance(int dist[], bool sptSet[]){
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;

}

// To print the shortest path from source to destination
void Network::printPath(int destin){
    // Base Case : If j is source
    if (parent[destin]==-1)
        return;
 
    printPath( parent[destin]);
 
    printf("%d ", destin);
}


//Find shortest path to allocate the resources
void Network::findShortestPath(int graph[V][V], int src){

	
 
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        parent[src] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)
 
            // Update dist[v] only if is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }  
    }
	
}



