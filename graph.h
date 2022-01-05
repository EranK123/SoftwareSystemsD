#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;

typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

char* build_graph_cmd(pnode *head, char text[]);
char* insert_node_cmd_a(pnode *head, char text[]);
char* insert_node_cmd_b(pnode *head, char text[]);
char* delete_node_cmd(pnode *head, char text[]);
// void printGraph_cmd(pnode head); //for self debug
// void deleteGraph_cmd(pnode* head);
char* shortsPath_cmd(pnode head, char *word);
char* TSP_cmd(pnode head, char *word);

#endif
