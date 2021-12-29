#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define WORD 120
#define TXT 50
int main(){

     char word[WORD];
     char text[TXT];
     pnode *head = NULL;
     int j=0;
     int k=0;
     for(int i=0; i<WORD; i++){
        scanf("%c", &word[i]);
        if(word[i] == '\n'){
            word[i] = '\0';
            break;
        }
    }
    for (int i = 1; i < sizeof(word); i++)
    {
        if(word[i] != 'B' && word[i] != 'D' && word[i] != 'S' && word[i] != 'P' && word[i] != 'T'){
        text[j++] = word[i];
        }
        else{
            break;
        }
    }
    for (int i = 0; i < sizeof(word); i++)
    {
        if(word[i] == 'A'){
            build_graph_cmd(head, text);
        }
        if(word[i] == 'A'){
            build_graph_cmd(head, text);
        }
    }
    
    return 0;
}

void build_graph_cmd(pnode *head, char text[]){
 
    deleteGraph_cmd(head);
    for (int i = 0; i < sizeof(text); i++)
    {
        
    }
    
}
void deleteGraph_cmd(pnode* head){
      if(head){
        pnode *p = head;
        while (p)
        {
            pnode *temp = p;
            p=(&(*p)->next);
            delete_node_cmd(temp);
        }
    }
}
void delete_node_cmd(pnode *head){
    printf("Enter node id for deletion");
    int del;
    scanf("%d", &del);
    pnode p = *head;
    pnode *prev = head;

    while (p && p->node_num == del)
    {

            prev = &(p->next);
            p = p->next;
    }

    if (!p)
    {
        return;
    }

    else if(p->node_num == del){
        //delete out edges
    pedge e = p->edges;
    while (e)
    {
        pedge temp = e;
        e = p->edges->next;
        free(temp);
    }
    }
      //delete in edges
    pnode start = *head;
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
    free(p);
}
void delete_out_edges(pnode head){

    pnode p = head;

    if (!p)
    {
        return;
    }
        //delete out edges
    pedge e = p->edges;
    while (e)
    {
        pedge temp = e;
        e = p->edges->next;
        free(temp);
    }
    }
void insert_node_cmd(pnode *head){

    printf("Enter node id for insertion");
    int id;
    scanf("%d", &id);
    pnode p = *head;
    pnode pn = *head;
    pnode node = *head;
    // pnode prev = 
    while (p)
    {
        if (p->node_num == id)
        {
            node = p;
            delete_out_edges(p);
        }else{
            p= p->next;
        }
    }
    if(node->node_num == id){
    add_edge(node);
    //the node dosen`t 
    }else{
        pnode n = (pnode)malloc(sizeof(node));
        while (pn)
        {
            pn=pn->next;
        }
        pn = n;
        add_edge(pn);
    }
}
void add_edge(pnode node){
    
}