#include "mytest.h"
#include "common_main.h"

class my_main: public main_t
{
public:
    node_t*  parent;
    long* pid;
    long* id;
    int* count;
    long size;
    int* star;

    virtual ~my_main() {
        delete[] parent;
        delete[] pid;
        delete[] id;
        delete[] count;
        delete[] star;
    }

    my_main(){
        printf("main");
        node_t*  parent = null;
        long* pid = null;
        long* id = null;
        int* count = null;
        long size = null;
        int* star = null;
    }

    virtual bool prepare() {
        printf("prepare");
        node_t*  parent = new node_t[G.num_nodes()+1];
        long* pid = new long[G.num_nodes()+1];
        long* id = new long[G.num_nodes()+1];
        int* count = new int[G.num_nodes()+1];
        long size = G.num_nodes();
        int* star = new int[G.num_nodes()+1];
        return true;
    }

    virtual bool run()
    {
        printf("Graph has %d node\n",G.num_nodes());
        for (int i = 0; i < G.num_nodes(); i++)
        {
            id[i] = i;
            pid[i] = i;
            count[i] = 0;
            star[i] = 0;
        }

        printf("init");
        init(G, parent,id,pid);
        //mistake(G,parent,id,pid);
        for(int i =0;i<G.num_nodes();i++){
            printf("%d's parent = %ld\n",i,pid[i]);
        }
        singleton_elimination(G,size,parent,id,pid,count);
        for(int i =0;i<G.num_nodes();i++){
            printf("%d's son count = %ld\n",i,count[i]);
        }
        for(int i =0;i<G.num_nodes();i++){
            printf("%d's parent = %ld\n",i,pid[i]);
        }
        long ret1 = star_detection(G,parent,id,pid,star);
        printf("%ld \n",ret1);
        for(int i =0;i<G.num_nodes();i++){
            printf("%d's star = %ld\n",i,star[i]);
        }
        int ii = 0;
        //avoid while(true)
        while(ii++ < 100000){
            C_star_hooking(G,size,parent,id,pid,star);
            U_star_hooking(G,size,parent,id,pid,star);

            for(int i =0;i<G.num_nodes();i++){
                node_t fn = parent[i];
                printf("%d's parent = %ld = %d\n",i,pid[i],fn);
            }

            for(int i =0;i<G.num_nodes();i++){
                printf("%d's star = %ld\n",i,star[i]);
            }

            pointer_jumping(G,parent,id,pid);

            for(int i =0;i<G.num_nodes();i++){
                node_t fn = parent[i];
                printf("%d's parent = %ld = %d\n",i,pid[i],fn);
            }

            for(int i =0;i<G.num_nodes();i++){
                printf("%d's star = %ld\n",i,star[i]);
                star[i] = 0;
            }

            long ret1 = star_detection(G,parent,id,pid,star);

            printf("%ld \n",ret1);
            for(int i =0;i<G.num_nodes();i++){
                printf("%d's star = %ld\n",i,star[i]);
            }

            if(ret1 == size)
                break;
        }
        return true;
    }

    virtual bool post_process() {
        for(int i =0;i<G.num_nodes();i++){
            node_t fn = parent[i];
            printf("%d's parent = %ld = %d\n",i,pid[i],fn);
        }
        return true;
    }
};

#define TEST_LARGE  1

int main(int argc, char** argv)
{
#if TEST_LARGE
    my_main M;
    M.main(argc, argv);
#else
    gm_graph G;
    for(int i=0;i<=19;i++){
        G.add_node();
    }
    int edges[][2] = {{1,10},{2,14},{2,19},{3,4},{3,13},{4,11},{5,6},{5,15},{6,15},{7,8},{7,18}
			,{8,18},{9,12},{10,12},{10,17},{12,17},{14,19},{15,18},{16,17},{17,19}};

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


     init(G, parent,id,pid);
     mistake(G,parent,id,pid);
     for(int i =0;i<G.num_nodes();i++){
            printf("%d's parent = %ld\n",i,pid[i]);
     }
     singleton_elimination(G,size,parent,id,pid,count);
     for(int i =0;i<G.num_nodes();i++){
            printf("%d's son count = %ld\n",i,count[i]);
     }
     for(int i =0;i<G.num_nodes();i++){
            printf("%d's parent = %ld\n",i,pid[i]);
     }
    long ret1 = star_detection(G,parent,id,pid,star);
    printf("%ld \n",ret1);
     for(int i =0;i<G.num_nodes();i++){
            printf("%d's star = %ld\n",i,star[i]);
     }
    int ii = 0;
   //avoid while(true)
   while(ii++ < 100000){
     C_star_hooking(G,size,parent,id,pid,star);
     U_star_hooking(G,size,parent,id,pid,star);

     for(int i =0;i<G.num_nodes();i++){
	    node_t fn = parent[i];
            printf("%d's parent = %ld = %d\n",i,pid[i],fn);
     }

     for(int i =0;i<G.num_nodes();i++){
            printf("%d's star = %ld\n",i,star[i]);
     }

     pointer_jumping(G,parent,id,pid);

     for(int i =0;i<G.num_nodes();i++){
	    node_t fn = parent[i];
            printf("%d's parent = %ld = %d\n",i,pid[i],fn);
     }

     for(int i =0;i<G.num_nodes();i++){
            printf("%d's star = %ld\n",i,star[i]);
	    star[i] = 0;
     }

     long ret1 = star_detection(G,parent,id,pid,star);

     printf("%ld \n",ret1);
     for(int i =0;i<G.num_nodes();i++){
            printf("%d's star = %ld\n",i,star[i]);
     }

     if(ret1 == size)
	    break;
   }
#endif
}
