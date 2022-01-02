#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#define WORD 1024
#define TXT 50
#define MAX 1000
#define INFINITY 10000

char* build_graph_cmd(pnode *head, char text[]);
void deleteGraph_cmd(pnode *head);
void delete_node_cmd(pnode *head, char text[]);
void delete_in_edges(pnode head, int id);
void delete_out_edges(pnode head);
char* insert_node_cmd_a(pnode *head, char text[]);
char* insert_node_cmd_b(pnode *head, char text[]);
pedge add_edge(pnode node, pnode dest, int w);
pnode add_node(pnode *head, int id);
void printGraph_cmd(pnode head);
void print_out_edges(pedge edge);
pnode exists_in_graph(pnode *head, int id);
int pos(pnode head, int node_id);
int get_weight(pnode head, int i, int j);
void dijikstra(pnode head, int **graph, int n, int start_node, int end_node);
void to_matrix(pnode head, int **m);
int size_of_nodes(pnode head);
void shortsPath_cmd(pnode head, char *word);
int key_word(char * word);
pnode new_node(pnode next, int id, pedge edge);

    char word[WORD];
    char* next;
    int count = 0;
    pnode *head_ptr = NULL;
    pnode *head = NULL;
int main(){
    // pnode p = NULL;
    // head = &p;
     int j=0;
     for(int i=0; i<MAX; i++){
        scanf("%c", &word[i]);
        if (word[i] == 'A' || word[i] == 'B' || word[i] == 'D' || word[i] == 'S' || word[i] == 'T' || word[i] == 'Z'){
            count++;
        }
        
        if(word[i] == '\n'){
            word[i] = '\0';
            break;
        }
    }
    next = word;
    while(count > 0){
        if(next[0] == 'A'){
            printf("51");
            next = build_graph_cmd(head, next);
            count--;
            head = head_ptr;
            // printf("Address of head: %p\n", &head);
            // printf("Address of a: %p\n", &(*head));
           // printf("head: %d", (*head)->node_num);
           printf("head_ptr ##: %d\n" , (*head_ptr)->node_num);
           printf("CH: %c \n", next[0]);
        }else if(next[0] == 'B'){
           printf("55**************");

           next = insert_node_cmd_b(head, next);
           count--;
        }
        else if(next[0] == 'D'){
            // printf("59");
            delete_node_cmd(head, next);
            count--;
        }
        else if(next[0] == 'S'){
            // printf("63");
            shortsPath_cmd(*head, next);
            count--;
        }
        else if(next[0] == 'T'){
            // printf("68");
            count--;
            continue;
        }
    }
    // printGraph_cmd(*head);
    return 0;
}

char* build_graph_cmd(pnode *head, char text[]){
 
    // deleteGraph_cmd(head);
    text = insert_node_cmd_a(head, text);
    return text;
}
void deleteGraph_cmd(pnode *head){
    printf("91");
      if(head){
          printf("head: %d ,%p", (*head)->node_num, (*head)->next);
          printf("93");
        pnode *p = head;
        while (p)
        {
            pnode temp = *p;
            p=&((*p)->next);
                printf("109");
                delete_out_edges(temp);
                delete_in_edges(temp, temp->node_num);
                free(temp);
            }
        }
        // delete_out_edges(*head);
        // delete_in_edges(*head, (*head)->node_num);
        // free(*head);
    }
void delete_node_cmd(pnode *head, char text[]){

    char* ptr = text + 1;
    int del = *ptr - '0';
    pnode p = *head;
    pnode *prev = head;

    while (p && p->node_num == del)
    {
            prev = &(p->next);
            p = p->next;
    }

    delete_out_edges(p);
    //delete in edges
    delete_in_edges(p, del);
    free(p);
    text = ptr + 1;
}
void delete_in_edges(pnode head, int del){
    pnode start = head;
    pedge e = start->edges;
    while (start)
    {
        while (e)
        {
           if(e->endpoint->node_num == del){
            pedge temp = e;
            e = e->next;
            free(temp);
        }else{
            e = e->next;
        }
        }
        start = start->next;
    }
}

void delete_out_edges(pnode head){

    pnode p = head;

    if (!p)
    {
        return;
    }
    //delete out edges
    pedge *e = &(p->edges);
    // pedge edge = *e;
    while (*e)
    {
        pedge temp = *e;
        e = &(p->edges->next);
        free(temp);
    }
}

pnode add_node(pnode *head, int id){
    // pnode pn = new_node(NULL, id, NULL);
    pnode pn = (pnode)malloc(sizeof(node));
    pn->edges=NULL;
    pn->next=NULL;
    pn->node_num=id;
    if(head == NULL){
        head = &pn;
        *head = pn;
    }else{
        pnode n = *head;
        while (n->next != NULL)
        {
            n=n->next;
        }
        n->next = pn;
    }
    return pn;
}

int index_add(int temp, char* index_src){
    if(temp == 0)
        return 2;
    int ans = 0;
    while(temp != 0){
        ans++;
        temp /= 10;
    }
    return ans+1;
}

void build_node(char* index_src, pnode* head){
    int id_node = key_word(index_src);
    int ans = index_add(id_node,index_src);
    index_src+=ans;
    // printf("%d\n",id_node);
    int id_node_dest;
    int w;
    pnode n = add_node(head,id_node);
    if(head == NULL){//first node
        head = &n;
    }
    while((*index_src) != 'n'){
        // printf("index: %c\n", *index_src);
        id_node_dest = key_word(index_src);
        // printf("id: %d\n", id_node_dest);
        ans = index_add(id_node_dest,index_src);
        index_src+=ans;
        // printf("ans: %d\n", ans);
        w = key_word(index_src);
        ans = index_add(w,index_src);
        index_src+=ans;
        // printf("ans: %d\n", ans);
        // printf("id dest: %d\n",id_node_dest);
        // printf("w: %d\n",w);
        pnode dest = exists_in_graph(head,id_node_dest);
        if(dest == NULL){
            dest = add_node(head,id_node_dest);
        }
        pedge e = add_edge(n,dest,w);
        pedge el = n->edges;
        while (el != NULL)
        {
            el = el->next;
        }
        el = e;
        // printf("el: %d, %d\n", el->weight, el->endpoint->node_num);
    }
    pnode temp = (*head);
    while(temp != NULL){
        // printf("id node: %d\n", temp->node_num);
        temp = temp->next;
    }
    pedge edge = n->edges;
    while(edge != NULL){
        // printf("edge: %d, %d\n", edge->endpoint->node_num, edge->weight);
        edge = edge->next;
    }
}

char* insert_node_cmd_a(pnode *head, char text[]){
    char *index_src = text;
    printf("Character : %c \n", *index_src);
    while((*index_src) == 'A' || (*index_src) == ' '){
        index_src++;
    }
    int num_of_nodes = key_word(index_src);
    // printf("%d\n",num_of_nodes);
    // printf("index: %c\n", *index_src);
    // pnode *head = head1;
    while ((*index_src) != '\n' && (*index_src) != 'B' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S')
    {
        // printf("index: %c\n", *index_src);
        if (*index_src == 'n')
        {
            // build_node(index_src,head);
            while (*index_src == ' ' || *index_src == 'n')
            {
                index_src++;
            }
            printf("index: %c\n", *index_src);
            int id_node = key_word(index_src);
            int ans = index_add(id_node,index_src);
            index_src+=ans;
            printf("%d\n",id_node);
            int id_node_dest;
            int w;
            pnode n_first;
            pnode n;
            if(head == NULL){//first node
                n_first = add_node(head,id_node);
                head = &n_first;
                *head = n_first;
            }else{
                // printf("head is not null\n");
                n = exists_in_graph(head,id_node);
                if(n == NULL){
                    // printf("n is null\n");
                    n = add_node(head,id_node);
                }
            }
            n = n_first;
            while((*index_src) != 'n' && (*index_src) != '\n' && (*index_src) != 'B' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S'){
                // printf("index: %c\n", *index_src);
                id_node_dest = key_word(index_src);
                // printf("id: %d\n", id_node_dest);
                ans = index_add(id_node_dest,index_src);
                index_src+=ans;
                // printf("ans: %d\n", ans);
                w = key_word(index_src);
                ans = index_add(w,index_src);
                index_src+=ans;
                // printf("ans: %d\n", ans);
                // printf("id dest: %d\n",id_node_dest);
                // printf("w: %d\n",w);
                pnode dest = exists_in_graph(head,id_node_dest);
                // printf("dest pointer: %p, node id:%d\n", dest, id_node_dest);
                if(dest == NULL){
                    dest = add_node(head,id_node_dest);
                }
                pedge e = add_edge(n,dest,w);
                pedge el = n->edges;
                while (el != NULL)
                {
                    el = el->next;
                }
                el = e;
                // printf("el: %d, %d\n", el->weight, el->endpoint->node_num);
            }
            pnode temp = (*head);
            while(temp != NULL){
                // printf("id node: %d\n", temp->node_num);
                temp = temp->next;
            }
            pedge edge = n->edges;
            while(edge != NULL){
                // printf("edge: %d, %d\n", edge->endpoint->node_num, edge->weight);
                edge = edge->next;
            } 
            index_src--;        
        }
        index_src++;
    }
    head_ptr = head;
    printf("head_ptr : %d \n", (*head_ptr)->node_num);
    return index_src;
}


char* insert_node_cmd_b(pnode *head, char text[]){
    char *index_src = text;
    printf("344");
    printf("head : %d \n", (*head)->node_num);
    printf("index_src: %c\n", *index_src);
    while((*index_src)=='B' || (*index_src)==' '){
        index_src++;
    }
    // pnode *head = head1;
    while ((*index_src) != '\n' && (*index_src) != 'A' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S')
    {
        printf("index: %c\n", *index_src);
            int id_node = key_word(index_src);
            int ans = index_add(id_node,index_src);
            index_src+=ans;
            printf("id_node: %d\n",id_node);
            int id_node_dest;
            int w;
            pnode n_first;
            pnode n;   
            printf("head is not null\n");
            n = exists_in_graph(head,id_node);
            printf("368");
            if(n == NULL){
                printf("369");
                printf("n is null\n");
                n = add_node(head,id_node);
            }
            
            printf("375");
            n = n_first;
            while((*index_src) != '\n' && (*index_src) != 'A' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S'){
                printf("index: %c\n", *index_src);
                id_node_dest = key_word(index_src);
                printf("id_node_dest: %d\n", id_node_dest);
                ans = index_add(id_node_dest,index_src);
                index_src+=ans;
                w = key_word(index_src);
                ans = index_add(w,index_src);
                index_src += ans;
                printf("id dest: %d\n",id_node_dest);
                printf("w: %d\n",w);
                pnode dest = exists_in_graph(head,id_node_dest);
                printf("dest pointer: %p, node id:%d\n", dest, id_node_dest);
                if(dest == NULL){
                    printf("*********");
                    dest = add_node(head,id_node_dest);
                }
                pedge e = add_edge(n,dest,w);
                pedge el = n->edges;
                while (el != NULL)
                {
                    el = el->next;
                }
                el = e;
                printf("el: %d, %d\n", el->weight, el->endpoint->node_num);
            }
            pnode temp = (*head);
            while(temp != NULL){
                printf("id node: %d\n", temp->node_num);
                temp = temp->next;
            }
            pedge edge = n->edges;
            while(edge != NULL){
                printf("edge: %d, %d\n", edge->endpoint->node_num, edge->weight);
                edge = edge->next;
            } 
            // index_src--;        
        index_src++;
    }
    return index_src;
}
pedge add_edge(pnode node, pnode dest, int w){
    
    pedge e = (pedge)(malloc(sizeof(edge)));
    pedge edge = node->edges;
    while(edge){
        edge = edge->next; 
    }
    edge=e;
    e->next=NULL;
    e->endpoint = dest;
    e->weight = w;
    // printf("edge in add: %d,%d\n", edge->endpoint->node_num, edge->weight);
    return e;
}
pnode exists_in_graph(pnode *head, int id){
    pnode temp = *head;
    // printf("id node in exist befor while: %d, %p, %p\n", id, head, *head);
    while (temp)
    {
        if(temp->node_num == id){
            // printf("id node in exist: %d\n", (*head)->node_num);
            return temp;
        }else{
            // printf("id node in exist: %d\n", (*head)->node_num);
            temp = temp->next;
        }
    }
    return NULL;
  
}


pnode new_node(pnode next, int id, pedge edge){
    pnode n = (pnode)malloc(sizeof(node));
    n->edges=edge;
    n->next=next;
    n->node_num=id;
    return n;
}
void printGraph_cmd(pnode head){

    pnode n = head;
    while (n)
    {
        // printf("%d", head->node_num);
        pedge e = head->edges;
        while (e)
        {
            print_out_edges(e);
        } 
        n=n->next;
    }
    
}
void print_out_edges(pedge edge){

    pedge e = edge;
    while (e)
    {
        printf("%d", e->weight);
        e = e->next;
    }
}

void shortsPath_cmd(pnode head, char *word){

    int src = key_word(word);
    int dest = key_word(word);
    int size = size_of_nodes(head);
    // int **matrix=NULL;
    int **matrix = (int **)malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++) matrix[i] = (int *)malloc(size * sizeof(int));
    to_matrix(head, matrix);
    dijikstra(head, matrix, size, src, dest);
    for (int i = 0; i < size; i++)
{
    int* currentIntPtr = matrix[i];
    free(currentIntPtr);
}
}
int key_word(char * word){

    while (*word == ' ' || *word == 'n')
    {
        word++;
    }
    char* str = word;
    int i=1;
    while (word[i] != ' ')
    {
       str[i] = word[i];
       i++;
    }
    int key = atoi(str);
    // word = (word+i);
    return key;
}

void to_matrix(pnode head, int **m){
    pnode pn = head;
    int count = 0;
    while (pn->next)
    {
        pn = pn->next;
        count++;
    }
    
    pnode node = head;
    pedge e = node->edges;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if(i == j){
                m[i][j] = 0;
            }else{
            m[i][j] = get_weight(node, i, j);
        } 
    }
}
}
void dijikstra(pnode head, int **graph, int n, int start_node, int end_node){

    start_node = pos(head, start_node);
    end_node = pos(head, end_node);
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode, i,j;
    for(i=0;i < n;i++)
        for(j=0;j < n;j++)
            if(graph[i][j]==0)
                cost[i][j]=INFINITY;
            else
                cost[i][j]=graph[i][j];

    for(i=0;i< n;i++)
    {
        distance[i]=cost[start_node][i];
        pred[i]=start_node;
        visited[i]=0;
    }
    distance[start_node]=0;
    visited[start_node]=1;
    count=1;
    while(count < n-1){
        mindistance=INFINITY;
        for(i=0;i < n;i++)
            if(distance[i] < mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }
        visited[nextnode]=1;
        for(i=0;i < n;i++)
            if(!visited[i])
                if(mindistance+cost[nextnode][i] < distance[i])
                {
                    distance[i]=mindistance+cost[nextnode][i];
                    pred[i]=nextnode;
                }
            count++;
    }
 
    for(i=0;i < n;i++)
        if(i!=start_node)
        {
            printf("\nDistance of %d = %d", i, distance[i]);
            j=i;
            do
            {
                j=pred[j];
                printf(" <-%d", j);
            }
            while(j!=start_node);
        }
}
int pos(pnode head, int node_id){

    pnode node = head;
    int count=0;
    while (node->node_num != node_id)
    {
        node = node->next;
        count++;
    }
    return count;

}
int get_weight(pnode head, int i, int j){

    int w=0;
    pnode node1 = head;
    pnode node2 = head;
    while (i > 0)
    {
        node1 = node1->next;
        i--;
    }
    while(j > 0){
        node2 = node2->next;
        j--;
    }
    pedge e = node1->edges;
    while(e){
        if(e->endpoint->node_num == node2->node_num){
            w = e->weight;
            return w;
        }else{
            e=e->next;
        }
    }
    return w;
}
int size_of_nodes(pnode head){

    int size=0;
    pnode p = head;
    while (p)
    {
        size++;
        p=p->next;
    }
    return size;
}