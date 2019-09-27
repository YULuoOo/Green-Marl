#include "common_main.h"
#include "mst_prim.h"  // defined in generated
#include "gm_rand.h"
class my_main: public main_t
{
public:
    int* len;

    virtual ~my_main() {
        delete[] len;
    }

    my_main() : len(NULL) {
    }

    virtual bool prepare() {
        len = new int[G.num_edges()];
        return true;
    }

    virtual bool run()
    {
        return true;
    }

    virtual bool post_process() {
        return true;
    }
};

#define TEST_LARGE  0

int main(int argc, char** argv)
{
    #if TEST_LARGE
        my_main M;
        M.main(argc, argv);
    #else
	gm_rand32 xorshift_rng;
        gm_graph G;
        for(int i=0;i<=15;i++){
            G.add_node();
        }
        //int edges[][2] = {{0,1},{2,3},{0,3},{1,2},{1,3},{0,2}};
        //for(int i=0;i<(sizeof(edges)/sizeof(edges[0]));i++){
        for(int i=0;i<G.num_nodes();i++){
	    for(int j=i+1;j<G.num_nodes();j++){  
	        G.add_edge(i,j);
                G.add_edge(j,i);
            }
	}
        int* len;
        int  num_membership;
        int rett = 0;
	int rettt = 0;
	len = new int[G.num_edges()];
        for (edge_t i = 0; i < G.num_edges(); i++){
            len[i] = (xorshift_rng.rand() % 100) + 1;
	}

	makeEdgeSame(G,len);
        for (node_t i = 0; i < G.num_nodes(); i++){
            for (node_t j = i+1; j < G.num_nodes(); j++){
                if(i!=j){
                    rett = printEdgeLen(G,len,i,j);
		    rettt = printEdgeLen(G,len,j,i);
                    printf("%d to %d len = %d %d\n",i,j,rett,rettt);
                }
            }
        }
	node_t root = 0;
	int sum = prim(G,len,root,G.num_nodes());
	printf("mst sum = %d\n",sum);
    #endif
}


