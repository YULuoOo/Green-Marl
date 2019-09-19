#include "mytest.h"
int main(int argc, char** argv) {
    gm_graph G;
    for (int i = 0; i <= 19; i++) {
        G.add_node();
    }
    int edges[][2] = {{1,  10},
                      {2,  14},
                      {2,  19},
                      {3,  4},
                      {3,  13},
                      {4,  11},
                      {5,  6},
                      {5,  15},
                      {6,  15},
                      {7,  8},
                      {7,  18},
                      {8,  18},
                      {9,  12},
                      {10, 12},
                      {10, 17},
                      {12, 17},
                      {14, 19},
                      {15, 18},
                      {16, 17},
                      {17, 19}};
    for (int i = 0; i < (sizeof(edges) / sizeof(edges[0])); i++) {
        G.add_edge(edges[i][0], edges[i][1]);
        G.add_edge(edges[i][1], edges[i][0]);
    }
    node_t *parent = new node_t[G.num_nodes() + 1];
    long *pid = new long[G.num_nodes() + 1];
    long *id = new long[G.num_nodes() + 1];
    int *count = new int[G.num_nodes() + 1];
    long size = G.num_nodes();
    int *star = new int[G.num_nodes() + 1];
    printf("Graph has %d node\n", G.num_nodes());
    for (int i = 0; i < G.num_nodes(); i++) {
        id[i] = i;
        pid[i] = i;

        count[i] = 0;
        star[i] = 0;
    }
    init(G, parent, id, pid);
    mistake(G, parent, id, pid);
    for (int i = 1; i < G.num_nodes(); i++) {
        printf("%d's parent = %ld\n", i, pid[i]);
    }
    singleton_elimination(G, size, parent, id, pid, count);
    for (int i = 1; i < G.num_nodes(); i++) {
        printf("%d's son count = %ld\n", i, count[i]);
    }
    for (int i = 1; i < G.num_nodes(); i++) {
        printf("%d's parent = %ld\n", i, pid[i]);
    }
    star_detection(G, parent, id, pid, star);
    for (int i = 1; i < G.num_nodes(); i++) {
        printf("%d's star = %ld\n", i, star[i]);
    }
}