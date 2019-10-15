#include "fwbw_scc.h"
#include "common_main.h"
#include <string>
#include <stdlib.h>

class my_main: public main_t
{
public:
    int* scc;
    int* state;

    virtual ~my_main() {
        delete[] scc;
        delete[] state;

    }

    my_main() : scc(NULL),state(NULL) {
    }

    virtual bool prepare() {
        printf("prepare");
        scc = new int[G.num_nodes()];
        state = new int[G.num_nodes()];

#pragma omp parallel for
        for (int i = 0; i < G.num_nodes(); i++)
        {
            scc[i] = 0;
            state[i] = 0;
        }
        printf("Graph has %d node\n",G.num_nodes());
        return true;
    }

    virtual bool run()
    {
        long rettt = opt_cc(G,size,parent,id,pid,star,count);
        printf("ret = %ld",rettt);
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
