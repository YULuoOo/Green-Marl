#include "mytest.h"
int main(int argc, char** argv) {
    gm_graph G;
    for(int i=0;i<=19;i++){
        G.add_node();
    }
    int edges[][2] = {{1,10},{2,14},{2,19},{3,4},{3,13},{4,11},{5,6},{5,15},{6,15},{7,8},{7,18}
            ,{8,18},{9,12},{10,12},{10,17},{12,17},{14,19},{15,18},{16,17},{17,19}};
    for(int i=0;i<20;i++){
        G.add_edge(edges[i][0],edges[i][1]);
        G.add_edge(edges[i][1],edges[i][0]);
    }
    long*  parent = new long[G.num_nodes()+1];
    long* id = new long[G.num_nodes()+1];
    printf("Graph has %d node\n",G.num_nodes());
    for (int i = 0; i < G.num_nodes(); i++)
    {
        id[i] = i;
        parent[i] = i;
    }
    mytest(G, parent,id);
    parent[12] = 10;
    for(int i =0;i<G.num_nodes();i++){
        printf("%d's parent = %ld\n",i,parent[i]);
    }
}