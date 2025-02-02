#include "opt_cc1.h"
#include "common_main.h"
#include <fstream>
#include <string>
#include <stdlib.h>
struct edge {
    int to;
    int from;
};
class my_main: public main_t
{
public:
    node_t*  parent;
    long* pid;
    long* id;
    long size;
    int* count;
    int* star;
    int* parId;
    int* parNode;
    int* minPid;
    int* minPar;

    virtual ~my_main() {
        delete[] parent;
        delete[] pid;
        delete[] count;
        delete[] id;
        delete[] star;
        delete[] parId;
        delete[] parNode;
        delete[] minPid;
        delete[] minPar;
    }

    my_main() : parent(NULL),pid(NULL),id(NULL),count(NULL),size(0),star(NULL) {
    }

    virtual bool prepare() {
        printf("prepare");
        return true;
    }

    virtual bool run()
    {
        node_t*  parent = new node_t[G.num_nodes()+1];
        long* pid = new long[G.num_nodes()+1];
        long* id = new long[G.num_nodes()+1];
        long size = G.num_nodes();
        int* count = new int[G.num_nodes()+1];
        int* star = new int[G.num_nodes()+1];
        int* parId = new int[G.num_nodes()+1];
        int* parNode = new int[G.num_nodes()+1];
        int* minPid = new int[G.num_nodes()+1];
        int* minPar = new int[G.num_nodes()+1];

        printf("Graph has %d node\n",G.num_nodes());
        for (int i = 0; i < G.num_nodes(); i++)
        {

            id[i] = i;
            pid[i] = i;
            count[i] = 0;
            star[i] = 1;
        }
        init(G, parent,id,pid);
        singleton_elimination(G,size,parent,id,pid,count);
        long ret1 = star_detection(G,parent,id,pid,star,count);
        int ii = 0;
        int hookingRet1 = 0;
        int hookingRet2 = 0;
        while(true){
            hookingRet1 =  C_star_hooking(G,size,parent,id,pid,star,count);
            star_detection(G,parent,id,pid,star,count);
            hookingRet2 = U_star_hooking(G,size,parent,id,pid,star,count);
            long ret1 = star_detection(G,parent,id,pid,star,count);
            pointer_jumping(G,parent,id,pid,star,count);
            star_detection(G,parent,id,pid,star,count);
            if(ret1 == size && hookingRet1 == 0 && hookingRet2 == 0)
                break;
        }
        long rettt = ret_cc_num(G,id,pid);
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
    gm_graph G;
    for(int i=0;i<=9;i++){
        G.add_node();
    }
    int edges[][2] = {{0,2},{2,4},{4,6},{1,3},{3,5},{5,7},{6,7}};

    for(int i=0;i<(sizeof(edges)/sizeof(edges[0]));i++){
	    G.add_edge(edges[i][0],edges[i][1]);
	    G.add_edge(edges[i][1],edges[i][0]);
    }

    node_t*  parent = new node_t[G.num_nodes()+1];
    long* pid = new long[G.num_nodes()+1];
    long* id = new long[G.num_nodes()+1];
    int* count = new int[G.num_nodes()+1];
    long size = G.num_nodes();
    int* star = new int[G.num_nodes()+1];


     printf("Graph has %d node\n",G.num_nodes());
       for (int i = 0; i < G.num_nodes(); i++)
        {
	   id[i] = i;
           pid[i] = i;

	   count[i] = 0;
	   star[i] = 0;
	}


    /* init(G, parent,id,pid);
    // mistake(G,parent,id,pid);
  //   for(int i =0;i<G.num_nodes();i++){
    //        printf("%d's parent = %ld\n",i,pid[i]);
     //}
     singleton_elimination(G,size,parent,id,pid,count);
    // for(int i =0;i<G.num_nodes();i++){
      //      printf("%d's son count = %ld\n",i,count[i]);
    // }
     //for(int i =0;i<G.num_nodes();i++){
       //     printf("%d's parent = %ld\n",i,pid[i]);
     //}
    long ret1 = star_detection(G,parent,id,pid,star);
   // printf("%ld \n",ret1);
     //for(int i =0;i<G.num_nodes();i++){
       //     printf("%d's star = %ld\n",i,star[i]);
    // }
    int ii = 0;
   int hookingRet1 = 0;
   int hookingRet2 = 0;
    //avoid while(true)
   while(ii++ < 500){
    hookingRet1 =  C_star_hooking(G,size,parent,id,pid,star);
     star_detection(G,parent,id,pid,star);
     hookingRet2 = U_star_hooking(G,size,parent,id,pid,star);
     star_detection(G,parent,id,pid,star);
     pointer_jumping(G,parent,id,pid);

     long ret1 = star_detection(G,parent,id,pid,star);

     if(ret1 == size && hookingRet1 == 0 && hookingRet2 == 0)
      	    break;
    }
     long rettt = ret_cc_num(G,id,pid);
    printf("ret = %ld \n",rettt);
*/
      init(G, parent,id,pid);
        singleton_elimination(G,size,parent,id,pid,count);
        long ret1 = star_detection(G,parent,id,pid,star);
        int ii = 0;
        int hookingRet1 = 0;
        int hookingRet2 = 0;
        while(true){

           hookingRet1 =  C_star_hooking(G,size,parent,id,pid,star);
           star_detection(G,parent,id,pid,star);
           hookingRet2 = U_star_hooking(G,size,parent,id,pid,star);
	        star_detection(G,parent,id,pid,star);
            pointer_jumping(G,parent,id,pid);
            long ret1 = star_detection(G,parent,id,pid,star);

           if(ret1 == size && hookingRet1 == 0 && hookingRet2 == 0 && ii!=0)
      	        break;
           if(ret1 == size && hookingRet1 == 0 && hookingRet2 == 0)
               ii=1;
        }
        long rettt = ret_cc_num(G,id,pid);
        printf("ret = %ld",rettt);
#endif
}
