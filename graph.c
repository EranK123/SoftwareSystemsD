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
char* delete_node_cmd(pnode *head, char text[]);
void delete_in_edges(pnode *head, int id);
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
int dijikstra_tsp(pnode head, int **graph, int n, int start_node, int end_node);
void to_matrix(pnode head, int **m);
int size_of_nodes(pnode head);
char* shortsPath_cmd(pnode head, char *word);
int key_word(char * word);
pnode new_node(pnode next, int id, pedge edge);
int index_add(int temp, char* index_src);
char* TSP_cmd(pnode head, char *word);

    
    char word[WORD];
    char* next;
    int count = 0;
    pnode *head = NULL;
    pnode *head_final = NULL;
int main(){
     for(int i=0; i<MAX; i++){
        scanf("%c", &word[i]);
        if (word[i] == 'A' || word[i] == 'B' || word[i] == 'D' || word[i] == 'S' || word[i] == 'T' || word[i] == 'Z'){
            count++;
        }
        
        if(word[i] == '\n' || word[i] == EOF){
            word[i] = '\0';
            break;
        }
    }
    next = word;
    while(count > 0){
        if(next[0] == 'A'){
            if(head){
                pnode *p = head;
                while (*p)
                {
                    pnode *temp = p;
                    pnode prev = *temp;
                    (*p) = (*p)->next;
                    // p=&((*p)->next);
                    delete_out_edges(prev);
                    delete_in_edges(temp, prev->node_num);
                    free(prev);
                }
                head=NULL;
                
            }
        
            char *index_src = next;
            while((*index_src)=='A' || (*index_src)==' '){
                index_src++;
            }
            
            while ((*index_src) != '\n' && (*index_src) != 'B' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S')
            {

                if (*index_src == 'n')
                {
                  
                    while (*index_src == ' ' || *index_src == 'n')
                    {
                        index_src++;
                    }
                    int id_node = key_word(index_src);
                    int ans = index_add(id_node,index_src);
                    index_src+=ans;
                    int id_node_dest;
                    int w;
                    pnode n_first;
                    pnode n;
                    if(head == NULL){//first node
                        n_first = add_node(head,id_node);
                        head = &n_first;
                        *head = n_first;
                        n = n_first;
                    }else{
                        pnode head_temp = *head;
                        while (head_temp)
                        {
                            head_temp = head_temp->next;
                        }
                        n = exists_in_graph(head,id_node);
                        if(n == NULL){
                            n = add_node(head,id_node);
                            head_temp = n;
                        }
                    }
                    while((*index_src) != 'n' && (*index_src) != '\n' && (*index_src) != 'B' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S'){
                 
                        id_node_dest = key_word(index_src);
                
                        ans = index_add(id_node_dest,index_src);
                        index_src+=ans;
                     
                        w = key_word(index_src);
                        ans = index_add(w,index_src);
                        index_src+=ans;
                       
                        pnode dest = exists_in_graph(head,id_node_dest);
                       
                        if(dest == NULL){
                            dest = add_node(head,id_node_dest);
                        }
                        if(!n->edges){
                            n->edges = (pedge)(malloc(sizeof(edge)));
                            n->edges->next = NULL;
                            n->edges->endpoint = dest;
                            n->edges->weight = w;
                        }else{
                            pedge edge = n->edges;
                            while(edge->next){
                                edge = edge->next;
                            }
                            
                            edge->next = (pedge)(malloc(sizeof(edge)));
                            edge->next->next=NULL;
                            edge->next->endpoint = dest;
                            edge->next->weight = w;
                        }
                    }
                   
                    index_src--;        
                }
                index_src++;
            }
         
            next = index_src;
            
            count--;
            
        }else if(next[0] == 'B'){
        
           next = insert_node_cmd_b(head, next);
       
           count--;

        }
        else if(next[0] == 'D'){
            
            if(head == NULL){
            }
            
            next = delete_node_cmd(head, next);
          
            count--;
        }
        else if(next[0] == 'S'){
            next = shortsPath_cmd(*head, next);
            count--;
            printf("\n");
        }
        else if(next[0] == 'T'){
            next = TSP_cmd((*head), next);
            count--;   
            printf("\n");
        }
    }
            printf("\n");
    return 0;
}

char* build_graph_cmd(pnode *head, char text[]){
 
    text = insert_node_cmd_a(head, text);
    return text;
}
char* delete_node_cmd(pnode *head, char text[]){

    while((*text) == 'D' || (*text) == ' '){
        text++;
    }
    char *ptr = text;
    int del = key_word(ptr);
    int ans = index_add(del, ptr);
    ptr+=ans;
    pnode p = *head;
    pnode prev;

    if(p != NULL && p->node_num == del){
        (*head) = p->next;
        delete_out_edges(p);
        //delete in edges
        delete_in_edges(head, del);
        free(p);
        return text;
    }
    while (p != NULL && p->node_num != del)
    {
            prev = p;
            p = p->next;
    }
    if(p == NULL){
        return ptr;
    }else{
    prev->next = p->next;
    delete_out_edges(p);
    delete_in_edges(head, del);
    free(p);
    return ptr;
    }
    return ptr;
}

void delete_in_edges(pnode* head, int del){
    pnode start = *head;
    
    while (start)
    {
        int count=0;
        pedge *e = &(start->edges);
        pedge prev;
        pedge temp = *e;
        if(start->edges){
        if(e != NULL && (*e)->endpoint->node_num == del){

        (*e) = temp->next;
        free(temp);
        start = start->next;
        count++;
        }else{
        while (temp && temp->endpoint->node_num != del){
            prev = temp;
            temp = temp->next;
        }
        if(temp == NULL){
            start=start->next;
            count++;
        }else{
        prev->next = temp->next;
        free(temp);
        start = start->next;
        count++;
    }
        if(count == 0){
        start=start->next;
    }
        }
        }else{
        start=start->next;
    }
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
    while (e && *e)
    {
        pedge temp = *e;
        e = &((*e)->next);
        free(temp);
    }
    p->edges = NULL;
}

pnode add_node(pnode *head, int id){
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

pnode add_node2(pnode** head, int id){
    pnode pn = (pnode)malloc(sizeof(node));
    if(!pn){
    }
    pnode* n = *head;
    while ((*n) && (*n)->next != NULL)
    {
        (*n)=(*n)->next;
    }
    (*n)->next = pn;
    (*n)->next->edges=NULL;
    (*n)->next->next=NULL;
    (*n)->next->node_num=id;
    return (*n)->next;
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
    int id_node_dest;
    int w;
    pnode n = add_node(head,id_node);
    if(head == NULL){//first node
        head = &n;
    }
    while((*index_src) != 'n'){
        id_node_dest = key_word(index_src);
        ans = index_add(id_node_dest,index_src);
        index_src+=ans;
        w = key_word(index_src);
        ans = index_add(w,index_src);
        index_src+=ans;
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
    }
    pnode temp = (*head);
    while(temp != NULL){
        temp = temp->next;
    }
    pedge edge = n->edges;
    while(edge != NULL){
        edge = edge->next;
    }
}

void add_edge2(pnode* head, int dest_num, int src_num, int w){
    
    pedge e = (pedge)(malloc(sizeof(edge)));
    pnode src = *head;
    while(src && src->node_num != src_num){
        src = src->next;
    }
    pnode dest = *head;
    while(dest && dest->node_num != dest_num){
        dest = dest->next;
    }
    pedge edge = src->edges;
    while(edge){
        edge = edge->next;
    }
    edge = e;
    edge->next=NULL;
    edge->endpoint = dest;
    edge->weight = w;
}


char* insert_node_cmd_a(pnode *head1, char text[]){
    char *index_src = text;
    while((*index_src)=='A' || (*index_src)==' '){
        index_src++;
    }
    pnode *head = head1;
    while ((*index_src) != '\n' && (*index_src) != 'B' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S')
    {
        if (*index_src == 'n')
        {
            while (*index_src == ' ' || *index_src == 'n')
            {
                index_src++;
            }
            int id_node = key_word(index_src);
            int ans = index_add(id_node,index_src);
            index_src+=ans;
            int id_node_dest;
            int w;
            pnode n_first;
            pnode n;
            if(head == NULL){//first node
                n_first = add_node(head,id_node);
                head = &n_first;
                *head = n_first;
                n = n_first;
            }else{
                pnode head_temp = *head;
                while (head_temp)
                {
                    head_temp = head_temp->next;
                }
                n = exists_in_graph(head,id_node);
                if(n == NULL){
                    n = add_node(head,id_node);
                    head_temp = n;
                }
            }
            while((*index_src) != 'n' && (*index_src) != '\n' && (*index_src) != 'B' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S'){
                id_node_dest = key_word(index_src);
                ans = index_add(id_node_dest,index_src);
                index_src+=ans;
                w = key_word(index_src);
                ans = index_add(w,index_src);
                index_src+=ans;
                pnode dest = exists_in_graph(head,id_node_dest);
                if(dest == NULL){
                    dest = add_node(head,id_node_dest);
                }
                if(!n->edges){
                    n->edges = (pedge)(malloc(sizeof(edge)));
                    n->edges->next = NULL;
                    n->edges->endpoint = dest;
                    n->edges->weight = w;
                }else{
                    pedge edge = n->edges;
                    while(edge->next){
                        edge = edge->next;
                    }
                    edge->next = (pedge)(malloc(sizeof(edge)));
                    edge->next->next=NULL;
                    edge->next->endpoint = dest;
                    edge->next->weight = w;
                }
            }
            pnode temp = (*head);
            while(temp != NULL){
                pedge edge = temp->edges;
                while(edge != NULL){
                    edge = edge->next;
                } 
                temp = temp->next;
            }
            index_src--;        
        }
        index_src++;
    }
    head_final = head;
    return index_src;
}

char* insert_node_cmd_b(pnode *head1, char text[]){
    char *index_src = text;
    while((*index_src)=='B' || (*index_src)==' '){
        index_src++;
    }
    int id_node = key_word(index_src);
    int ans = index_add(id_node,index_src);
    index_src+=ans;
    int id_node_dest;
    int w;
    pnode n = *head;
    while (n && n->next != NULL && n->node_num != id_node)
    {
        n=n->next;
    }
    if(!(n->next) && n->node_num != id_node){
        pnode pn = (pnode)malloc(sizeof(node));
        n->next = pn;
        n->next->edges=NULL;
        n->next->next=NULL;
        n->next->node_num=id_node;
        n=n->next;
    }else{
        pedge *e = &(n->edges);
        while (e && *e)
        {
            pedge temp = *e;
            e = &((*e)->next);
            free(temp);
        }
        n->edges = NULL;
    }
    while((*index_src) != 'n' && (*index_src) != '\n' && (*index_src) != 'B' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S'){
        id_node_dest = key_word(index_src);
        ans = index_add(id_node_dest,index_src);
        index_src+=ans;
        w = key_word(index_src);
        ans = index_add(w,index_src);
        index_src+=ans;
        pnode dest = exists_in_graph(head,id_node_dest);
        if(dest == NULL){
            dest = add_node(head,id_node_dest);
        }
        if(!n->edges){
            n->edges = (pedge)(malloc(sizeof(edge)));
            n->edges->next = NULL;
            n->edges->endpoint = dest;
            n->edges->weight = w;
        }else{
            pedge edge = n->edges;
            while(edge->next){
                edge = edge->next;
            }
            edge->next = (pedge)(malloc(sizeof(edge)));
            edge->next->next=NULL;
            edge->next->endpoint = dest;
            edge->next->weight = w;
        }
    }
    pnode temp = (*head);
    while(temp != NULL){
        pedge edge = temp->edges;
        while(edge != NULL){
            edge = edge->next;
        } 
        temp = temp->next;
    }
    return index_src;
}

pnode exists_in_graphb(pnode *head, int id){

    pnode* temp = head;
    
    while ((*temp))
    {
        if((*temp)->node_num == id){
            return (*temp);
        }else{
            (*temp)=(*temp)->next;
        }
    }
    return NULL;
}

char* insert_node_cmd_b2(pnode *head1, char text[]){
    char *index_src = text;
    while((*index_src)=='B' || (*index_src)==' '){
        index_src++;
    }
    pnode *head = head1;
    while ((*index_src) != 0 && (*index_src) != '\n' && (*index_src) != 'A' && (*index_src) != 'B' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S')
    {
            
            int id_node = key_word(index_src);
            int ans = index_add(id_node,index_src);
            index_src+=ans;
            int id_node_dest;
            int w;
            pnode n;
                    n = add_node2(&head,id_node);
                pnode head_temp = *head;
                while (head_temp->next)
                {
                    head_temp = head_temp->next;
                }
                    head_temp = n;
            
            while((*index_src) != 0 && (*index_src) != '\n' && (*index_src) != 'A' && (*index_src) != 'B' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S'){

                while (*index_src == ' ' || *index_src == 'n')
                {
                    index_src++;
                }
                id_node_dest = key_word(index_src);
                ans = index_add(id_node_dest,index_src);
                index_src+=ans;
                w = key_word(index_src);
                ans = index_add(w,index_src);
                index_src+=ans;
                pnode dest = exists_in_graph(head,id_node_dest);
                if(dest == NULL){
                    dest = add_node(head,id_node_dest);
                }
                if(!n->edges){
                    n->edges = (pedge)(malloc(sizeof(edge)));
                    n->edges->next = NULL;
                    n->edges->endpoint = dest;
                    n->edges->weight = w;
                }else{
                    pedge edge = n->edges;
                    while(edge->next){
                        edge = edge->next;
                    }
                    edge->next = (pedge)(malloc(sizeof(edge)));
                    edge->next->next=NULL;
                    edge->next->endpoint = dest;
                    edge->next->weight = w;
                }
            }
    }
    head_final = head;
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
    return e;
}
pnode exists_in_graph(pnode *head, int id){

    pnode temp = *head;
    
    while (temp)
    {
        if(temp->node_num == id){
            return temp;
        }else{
            temp=temp->next;
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

char* shortsPath_cmd(pnode head, char *word){


    char *index_src = word;
    while(*index_src == 'S' || *index_src == ' '){
        index_src++;
    }
    int src = key_word(index_src);
    int ans = index_add(src,index_src);
    index_src+=ans;
    int dest = key_word(index_src);
    ans = index_add(dest,index_src);
    index_src+=ans;
    int size = size_of_nodes(head);
    int **matrix = (int **)malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++) matrix[i] = (int *)malloc(size * sizeof(int));
    to_matrix(head, matrix);
    dijikstra(head, matrix, size, src, dest);
    for (int i = 0; i < size; i++)
{
    int* currentIntPtr = matrix[i];
    free(currentIntPtr);
}
    free(matrix);
    return index_src;
}
void to_matrix(pnode head, int **m){
    pnode pn = head;
    int count = 0;
    while (pn)
    {
        pn = pn->next;
        count++;
    }
    
    pnode node = head;
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
    int cost[MAX][MAX], distance[MAX];
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
        for(i=0;i < n;i++){
            if(!visited[i])
                if(mindistance+cost[nextnode][i] < distance[i])
                {
                    distance[i]=mindistance+cost[nextnode][i];
                }  
        }
            count++;
    }

    if(distance[end_node] == INFINITY){
        printf("Dijsktra shortest path: -1 ");
    }else{
        printf("Dijsktra shortest path: %d ", distance[end_node]);
}
}

int key_word(char * word){

    while (*word == ' ' || *word == 'n')
    {
        word++;
    }
    char* str = word;
    if(strlen(word) != 1){
    int i=1;
    while (word[i] != ' ')
    {
       str[i] = word[i];
       i++;
    }
    }
    int key = atoi(str);
    return key;
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

int dijikstra_tsp(pnode head, int **graph, int n, int start_node, int end_node){

    start_node = pos(head, start_node);
    end_node = pos(head, end_node);
    int cost[MAX][MAX], distance[MAX];
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
        for(i=0;i < n;i++){
            if(!visited[i])
                if(mindistance+cost[nextnode][i] < distance[i])
                {
                    distance[i]=mindistance+cost[nextnode][i];
                }  
        }
            count++;
    }
    return distance[end_node];
}


int shortsPath_tsp(pnode head, int src, int dest){

    int size = size_of_nodes(head);
    int **matrix = (int **)malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++) matrix[i] = (int *)malloc(size * sizeof(int));
    to_matrix(head, matrix);
    int dis = dijikstra_tsp(head, matrix, size, src, dest);
    for (int i = 0; i < size; i++)
{
    int* currentIntPtr = matrix[i];
    free(currentIntPtr);
}
    free(matrix);
    return dis;
}

    char* TSP_cmd(pnode head, char *word){

    char *index = word;
    while((*index) == 'T' || (*index) == ' '){
        index++;
    }
    int size = key_word(index);
    int ans = index_add(size, index);
    index += ans;
    int *arr = (int*)malloc(size*sizeof(int));
    int i=0;
    int j=0;
    int num=0, min=INFINITY;
    int temp1=0, temp2=0, temp3=0, temp4=0, temp5=0;
    while(i<size){
        int key = key_word(index);
        arr[j++] = key;
        ans = index_add(key, index);
        index += ans;
        i++;
    }
    for(int i=0; i<size; i++){
        num=0;
        temp1=0, temp2=0, temp3=0, temp4=0, temp5=0;
        for(int j=0; j<size; j++){
            if(i != j){
            num -= temp1;
            temp1 = shortsPath_tsp(head, arr[i], arr[j]);
            num += temp1;
            if(size == 2){
                if(num < min){
                        min = num;
                    }
            }
            for(int k=0; k<size; k++){
                if(j != k && i != k){
                num -= temp2;
                temp2 = shortsPath_tsp(head, arr[j], arr[k]);
                num += temp2;
                if(size == 3){
                if(num < min){
                        min = num;
                    }
            }
                for(int a=0; a<size; a++){
                    if(i != a && j != a && k != a){
                    num -= temp3;
                    temp3 = shortsPath_tsp(head, arr[k], arr[a]);
                    num += temp3;
                    if(size == 4){
                        if(num < min){
                            min = num;
                            }
                    }
                    for(int q=0; q<size; q++){
                        if(i != q && j != q && k != q && a != q){
                        num -= temp4;
                        temp4 = shortsPath_tsp(head, arr[a], arr[q]);
                        num += temp4;
                        if(size == 5){
                            if(num < min){
                                min = num;
                                }
                        }
                        for(int p=0; p<size; p++){
                            if(i != p && j != p && k != p && a != p && q != p){
                                num -= temp5;
                                temp5 = shortsPath_tsp(head, arr[p], arr[q]);
                                num += temp5;
                                if(size == 6){
                                    if(num < min){
                                            min = num;
                                            
                                        }
                                }
    }
                        }
                    }
                    
    }
    }
                }
            }
        }
        }
    }
    }
                    free(arr);
                    if(min >= INFINITY){
                        min = -1;
                    }
                    printf("TSP shortest path: %d ", min);
                    return index;
    }
