#include "opt_cc.h"
#include "common_main.h"
#include <string>
#include <stdlib.h>

class my_main: public main_t
{
public:
    node_t*  parent;
    long* pid;
    long* id;
    long size;
    int* count;
    int* star;

    virtual ~my_main() {
        delete[] parent;
        delete[] pid;
        delete[] count;
        delete[] id;
        delete[] star;
    }

    my_main() : parent(NULL),pid(NULL),id(NULL),count(NULL),size(0),star(NULL) {
    }

    virtual bool prepare() {
        printf("prepare");
        return true;
    }

    virtual bool run()
    {  struct timeval T1, T2;
        node_t*  parent = new node_t[G.num_nodes()+1];
        long* pid = new long[G.num_nodes()+1];
        long* id = new long[G.num_nodes()+1];
        long size = G.num_nodes();
        int* count = new int[G.num_nodes()+1];
        int* star = new int[G.num_nodes()+1];
        printf("Graph has %d node\n",G.num_nodes());
        for (int i = 0; i < G.num_nodes(); i++)
        {

            id[i] = i;
            pid[i] = i;
            count[i] = 0;
            star[i] = 1;
        }
        long rettt = opt_cc(G,size,parent,id,pid,star,count);
        printf("ret = %ld",rettt);
        return true;
    }

    virtual bool post_process() {
        return true;
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
