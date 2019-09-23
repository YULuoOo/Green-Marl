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

    my_main() : parent(NULL),pid(NULL),id(NULL),count(NULL),size(0),star(NULL) {
    }

    virtual bool prepare() {
        printf("prepare");
        //node_t*  parent = new node_t[G.num_nodes()+1];
        //long* pid = new long[G.num_nodes()+1];
        //long* id = new long[G.num_nodes()+1];
        //int* count = new int[G.num_nodes()+1];
        //long size = G.num_nodes();
        //int* star = new int[G.num_nodes()+1];
        return true;
    }

    virtual bool run()
    {
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
        while(ii++ < 3){
            C_star_hooking(G,size,parent,id,pid,star);
            U_star_hooking(G,size,parent,id,pid,star);

            for(int i =0;i<G.num_nodes();i++){
                node_t fn = parent[i];
                printf("%d's parent = %ld = %d\n",i,pid[i],fn);
            }

            for(int i =0;i<G.num_nodes();i++){
               // printf("%d's star = %ld\n",i,star[i]);
            }

            pointer_jumping(G,parent,id,pid);

            for(int i =0;i<G.num_nodes();i++){
                node_t fn = parent[i];
                printf("%d's parent = %ld = %d\n",i,pid[i],fn);
            }

            for(int i =0;i<G.num_nodes();i++){
               // printf("%d's star = %ld\n",i,star[i]);
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
        long rettt = ret_cc_num(G,id,pid);
        printf("ret = %ld",rettt);
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
    gm_graph G;
    for(int i=0;i<=99;i++){
        G.add_node();
    }
   // int edges[][2] = {{1,10},{2,14},{2,19},{3,4},{3,13},{4,11},{5,6},{5,15},{6,15},{7,8},{7,18}
//			,{8,18},{9,12},{10,12},{10,17},{12,17},{14,19},{15,18},{16,17},{17,19}};
//int edges[][2] = {{7,49},{23,8},{30,22},{44,28},{23,9},{40,15},{42,37},{3,27},{29,40},{12,3},{19,9},{7,10},{33,49},{28,16},{35,47},{26,12},{17,10},{33,29},{49,29},{21,17},{22,43},{36,35},{45,28},{41,44},{7,1},{3,8},{44,18},{40,24},{46,30},{3,22},{16,49},{24,1},{8,28},{33,48},{31,35},{13,15},{14,13},{36,25},{19,15},{44,29},{1,17},{45,5},{4,1},{48,38},{23,5},{32,2},{16,37},{38,44},{1,47},{21,28},{37,8}};
int edges[][2] = {{7,49},{58,73},{30,72},{44,78},{9,23},{40,65},{42,92},{3,87},{27,29},{12,40},{3,69},{9,57},{33,60},{78,99},{16,35},{26,97},{12,67},{10,33},{49,79},{21,79},{67,72},{36,93},{45,85},{28,91},{57,94},{1,53},{8,44},{68,90},{24,96},{3,30},{22,66},{24,49},{8,77},{28,33},{81,98},{13,35},{14,65},{36,63},{25,69},{15,94},{1,29},{17,95},{4,5},{51,98},{23,88},{5,82},{52,66},{16,37},{38,44},{1,97},{28,71},{37,58},{77,97},{4,94},{9,31},{45,75},{35,98},{42,99},{12,68},{57,60},{8,94},{68,95},{13,30},{6,62},{42,65},{52,82},{21,67},{12,95},{1,71},{31,90},{38,57},{16,90},{40,79},{6,35},{72,98},{19,95},{23,54},{60,89},{5,26},{6,23},{13,70},{38,94},{20,44},{34,66},{26,94},{38,63},{44,90},{50,59},{23,47},{17,85},{39,72},{47,85},{85,96},{20,23},{44,68},{15,35},{25,34},{11,42},{52,79},{44,95},{18,96},{15,92},{33,91},{69,97},{47,53},{10,25},{11,62},{25,61},{35,68},{76,95},{39,67},{31,74},{1,56},{60,72},{84,94},{55,89},{7,15},{69,93},{55,80},{6,55},{2,63},{8,76},{31,49},{8,97},{49,51},{3,31},{14,31},{19,75},{9,80},{23,29},{54,60},{37,45},{17,25},{0,56},{64,97},{4,48},{50,76},{12,54},{4,97},{48,81},{65,78},{9,99},{29,53},{47,83},{7,73},{5,22},{53,76},{24,30},{0,66},{44,70},{16,85},{55,98},{33,57},{76,78},{57,66},{11,78},{14,19},{33,37},{20,91},{33,62},{31,97},{88,89},{73,77},{4,58},{0,54},{15,60},{47,80},{30,55},{7,46},{0,38},{26,35},{13,57},{14,93},{18,57},{29,85},{15,63},{2,17},{19,43},{47,67},{69,95},{3,73},{3,48},{58,85},{6,59},{32,73},{3,97},{20,50},{31,80},{0,3},{20,33},{3,58},{34,80},{32,79},{49,74},{42,49},{10,71},{79,83},{40,70},{23,50},{29,71},{18,46}};

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
    for(int i =0;i<G.num_nodes();i++){
           star[i] = 0;
     } 
     star_detection(G,parent,id,pid,star);
     U_star_hooking(G,size,parent,id,pid,star);
     for(int i =0;i<G.num_nodes();i++){
           star[i] = 0;
     }
     star_detection(G,parent,id,pid,star);

     for(int i =0;i<G.num_nodes();i++){
	   // node_t fn = parent[i];
           // printf("%d's parent = %ld = %d\n",i,pid[i],fn);
     }

     for(int i =0;i<G.num_nodes();i++){
            //printf("%d's star = %ld\n",i,star[i]);
     }

     pointer_jumping(G,parent,id,pid);

     for(int i =0;i<G.num_nodes();i++){
	    node_t fn = parent[i];
	    long ppid = pid[i];
            printf("%d's parent = %ld grand = %ld\n",i,pid[i],pid[ppid]);
     }

     for(int i =0;i<G.num_nodes();i++){
           // printf("%d's star = %ld\n",i,star[i]);
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
     long rettt = ret_cc_num(G,id,pid);
    printf("ret = %ld \n",rettt);
#endif
}
