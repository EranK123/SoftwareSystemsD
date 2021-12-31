#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#define WORD 1024
#define TXT 50

void build_graph_cmd(pnode *head, char text[]);
void deleteGraph_cmd(pnode *head);
void delete_node_cmd(pnode *head, char text[]);
void delete_in_edges(pnode head, int id);
void delete_out_edges(pnode head);
void insert_node_cmd_a(pnode *head, char text[]);
void insert_node_cmd_b(pnode *head, char text[]);
void add_edge(pnode node, pnode dest, int w);
pnode add_node(pnode *head, int id);
void printGraph_cmd(pnode head);
void print_out_edges(pedge edge);
int exists_in_graph(pnode *head, char id);

int main(){
     char* next;
     int count = 0;
     char word[WORD];
     char text_a[TXT];
     char text_b[TXT];
     char text_d[TXT];
     char text_s[TXT];
     char text_t[TXT];
     pnode *head = NULL;
     int j=0;
     int k=0;
     for(int i=0; i<WORD; i++){
        scanf("%c", &word[i]);
        if (word[i] >= 'A' && word[i] <= 'Z'){
            count++;
        }
        
        if(word[i] == EOF){
            word[i] = '\0';
            break;
        }
    }
  
    while(count > 0){
        if(word[0] == 'A'){
            build_graph_cmd(head, word);
            count--;
        }
        else if(word[0] == 'B'){
           insert_node_cmd_b(head, word);
           count--;
        }
        else if(word[0] == 'D'){
            delete_node_cmd(head, word);
            count--;
        }
        else if(word[0] == 'S'){
            
            count--;
        }
        else if(word[0] == 'T'){
        
            count--;
        }
    }
    printGraph_cmd(*head);
    return 0;
}

void build_graph_cmd(pnode *head, char text[]){
 
    deleteGraph_cmd(head);
    // int len = strlen(text);
    // for (int i = 2; i < len-2; i++)
    // {
    //     if(text[i] == 'n'){
    //         i++;
    //     }
    insert_node_cmd_a(head, text);
}
void deleteGraph_cmd(pnode *head){
      if(head){
        pnode *p = head;
        while (p)
        {
            pnode temp = *p;
            p=&((*p)->next);
            if ((temp)->node_num != (*head)->node_num)
            {
                delete_out_edges(temp);
                delete_in_edges(*head, temp->node_num);
                free(temp);
            }
        }
        delete_out_edges(*head);
        delete_in_edges(*head, (*head)->node_num);
        free(*head);
    }
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
void insert_node_cmd_a(pnode *head, char text[]){
    int num_of_nodes;
    char *index_src;
    index_src = text + 3;

   
    while (*index_src != '\n' && *index_src >= 'B' && *index_src <= 'Z')
    {
        if (*index_src == 'n')
        {
            index_src++;
        }
        
    int id = *index_src - '0';
    pnode p = *head;
    pnode node = *head;
    pnode src = node;
    pnode dest = NULL;
    while (p)
    {
        if (p->node_num == id)
        {
            node = p;
            src = node;
            delete_out_edges(p);
        }else{
            p = p->next;
        }
    }
    if(node->node_num != id){
        src = add_node(head, *index_src);

    }if((exists_in_graph(head, *index_src)) == 0){
        dest = add_node(head, *(index_src+1));
    }
    add_edge(src, dest, *(index_src + 2));
    index_src = index_src + 3;
    }
    text = index_src;
}

void insert_node_cmd_b(pnode *head, char text[]){
    int num_of_nodes;
    char *index_src;
    index_src = text + 1;
    
   
    while (*index_src != '\n' && *index_src >= 'C' && *index_src <= 'Z' && *index_src != 'A')
    {
        
    int id = *index_src - '0';
    pnode p = *head;
    pnode node = *head;
    pnode src = node;
    pnode dest = NULL;
    while (p)
    {
        if (p->node_num == id)
        {
            node = p;
            src = node;
            delete_out_edges(p);
        }else{
            p = p->next;
        }
    }
    if(node->node_num != id){
        src = add_node(head, *index_src);

    }if((exists_in_graph(head, *index_src)) == 0){
        dest = add_node(head, *(index_src+1));
    }
    add_edge(src, dest, *(index_src + 2));
    index_src = index_src + 3;
    }
    text = index_src;
}
void add_edge(pnode node, pnode dest, int w){
    
    pedge e = (pedge)(malloc(sizeof(edge)));
    pedge edge = node->edges;
    while(edge->next){
        edge = edge->next; 
}
    edge->next=e;
    e->next=NULL;
    e->endpoint = dest;
    e->weight = w;
}
int exists_in_graph(pnode *head, char id){

    int key = id - '0';
    pnode temp = *head;
    while (temp)
    {
        if(temp->node_num == id){
            return 1;
        }else{
            temp=temp->next;
        }
    }
    return 0;
}
pnode add_node(pnode *head, int id){
    pnode n = (pnode)malloc(sizeof(node));
    pnode pn = *head;
    while (pn->next)
    {
        pn=pn->next;
    }
    n->node_num=id;
    n->edges=NULL;
    n->next=NULL;
    pn->next = n;
    return n;
}
void printGraph_cmd(pnode head){

    pnode n = head;
    while (n)
    {
        printf("251");
        printf("%d", head->node_num);
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

void shortsPath_cmd(pnode head){

}

void to_matrix(pnode *head){
    pnode pn = *head;
    int count = 0;
    while (pn->next)
    {
        pn = pn->next;
        count++;
    }
    int m[count][count];
    pnode node = *head;
    pedge e = node->edges;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            m[i][j] = 
        } 
    }
    
}