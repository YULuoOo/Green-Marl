#include "fwbw_scc.h"
#include "common_main.h"
#include <string>
#include <stdlib.h>

class my_main: public main_t
{
public:
    int* scc;
    int* color;
    int* id;


    virtual ~my_main() {
        delete[] scc;
        delete[] color;
        delete[] id;
    }

    my_main() : scc(NULL),color(NULL),id(NULL) {
    }

    virtual bool prepare() {
        printf("prepare");
        scc = new int[G.num_nodes()];
        color = new int[G.num_nodes()];
        id = new int[G.num_nodes()];

#pragma omp parallel for
        for (int i = 0; i < G.num_nodes(); i++)
        {
            scc[i] = 0;
            color[i] = i;
            id[i] = i;
        }
        printf("Graph has %d node\n",G.num_nodes());
        return true;
    }

    virtual bool run()
    {
        Int ret = scc(G,color,id,scc,G.num_nodes());
        printf("ret = %d",rettt);
        return true;
    }

    virtual bool post_process() {
        return true;
    }

    rec_scc(state){

    }
};

#define TEST_LARGE 1

int main(int argc, char** argv)
{
#if TEST_LARGE
    my_main M;
    M.main(argc, argv);
#else

#endif
}
