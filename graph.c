#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#define WORD 1024
#define TXT 50

void build_graph_cmd(pnode *head, char text[]);
void deleteGraph_cmd(pnode *head);
void delete_node_cmd(pnode *head, char text[], char index_node);
void delete_in_edges(pnode head, int id);
void delete_out_edges(pnode head);
void insert_node_cmd(pnode *head, char text[], char index_src);
void add_edge(pnode node, pnode dest, int w);
pnode add_node(pnode *head, int id);
void printGraph_cmd(pnode head);
void print_out_edges(pedge edge);
int exists_in_graph(pnode *head, char id);

int main(){

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
        if(word[i] == EOF){
            word[i] = '\0';
            break;
        }
    }
    for(int i=0; i<strlen(word); i++){
        printf("%c", word[i]);
    }
    int word_len = strlen(word);
    for(int q=j; q<word_len; q++)
    {
    for (int i = q; i < word_len; i++)
    {
        if(word[q] == 'A'){
        text_a[j++] = word[i];
        }

        else if(word[q] == 'B'){
        text_b[j++] = word[i];
        }
  
        else if(word[q] == 'D'){
        text_d[j++] = word[i];
        }
     
        else if(word[q] == 'S'){
        text_s[j++] = word[i];
        }
        else if(word[q] == 'T'){
        text_t[j++] = word[i];
        }
        else{
            exit(1);
        }
    }
    }
    for (int i = 0; i < sizeof(word); i++)
    {
        if(word[i] == 'A'){
            printf("69");
            build_graph_cmd(head, text_a);
        }
        else if(word[i] == 'B'){
            insert_node_cmd(head, text_b, text_b[1]);
        }
        else if(word[i] == 'D'){
            delete_node_cmd(head, text_d, text_d[1]);
        }
        else if(word[i] == 'S'){
            continue;
            // insert_node_cmd(head, text_s);
        }
        else if(word[i] == 'T'){
            continue;
            // insert_node_cmd(head, text_t);
        }
    }
    printGraph_cmd(*head);
    return 0;
}

void build_graph_cmd(pnode *head, char text[]){
 
    deleteGraph_cmd(head);
    int len = strlen(text);
    for (int i = 2; i < len-2; i++)
    {
        if(text[i] == 'n'){
            i++;
        }
        insert_node_cmd(head, text, i);
    }
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
void delete_node_cmd(pnode *head, char text[], char index_node){

    int del = index_node - '0';
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
void insert_node_cmd(pnode *head, char text[], char index_src){

    // printf("Enter node id for insertion");
    int index_dest=(index_src - '0') + 1;
    while (text[index_dest] != 'n' && text[index_dest] != '\n')
    {
    int id = text[index_src] - '0';
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
            p= p->next;
        }
    }
    if(node->node_num != id){
        src = add_node(head, text[index_src]);

    }if((exists_in_graph(head, text[index_dest])) == 0){
        dest = add_node(head, text[index_dest]);
    }
    add_edge(src, dest, text[index_dest+1]);
    index_dest+=2;
    }
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