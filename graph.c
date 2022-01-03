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
void to_matrix(pnode head, int **m);
int size_of_nodes(pnode head);
char* shortsPath_cmd(pnode head, char *word);
int key_word(char * word);
pnode new_node(pnode next, int id, pedge edge);
int index_add(int temp, char* index_src);

    
    char word[WORD];
    char* next;
    int count = 0;
    pnode *head = NULL;
    pnode *head_final = NULL;
int main(){
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
    int s = strlen(word);
    //    for(int i=0; i<s; i++){
    //         printf("\n word[i] = %c",word[i]);
    //     }
    int k=0;
    while(count > 0){
        if(next[0] == 'A'){
            k++;
            printf("index_src: %c", *next);
            printf("51");
            // deleteGraph_cmd(head);
            if(head){
                printf("61");
                pnode *p = head;
                while (p)
                {
                    printf("66");
                    pnode *temp = p;
                    pnode prev = *temp;
                    p=&((*p)->next);
                    delete_out_edges(*temp);
                    delete_in_edges(temp, (*temp)->node_num);
                    free(prev);
                }
                head = NULL;
            }
            char *index_src = next;
            while((*index_src)=='A' || (*index_src)==' '){
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
                    // printf("index: %c\n", *index_src);
                    int id_node = key_word(index_src);
                    int ans = index_add(id_node,index_src);
                    index_src+=ans;
                    // printf("%d\n",id_node);
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
                        // printf("head is ot null\n");
                        pnode head_temp = *head;
                        while (head_temp)
                        {
                            head_temp = head_temp->next;
                        }
                        n = exists_in_graph(head,id_node);
                        if(n == NULL){
                            // printf("n is null\n");
                            n = add_node(head,id_node);
                            head_temp = n;
                        }
                    }
                    // printf("n node num: %d\n", n->node_num);
                    // printf("n node num: %d\n", n->node_num);
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
                        if(!n->edges){
                            n->edges = (pedge)(malloc(sizeof(edge)));
                            n->edges->next = NULL;
                            n->edges->endpoint = dest;
                            n->edges->weight = w;
                        }else{
                            pedge edge = n->edges;
                            // printf("edge pointer: %p, %p\n", edge, n->edges);
                            // printf("edge: %d node n: %d\n", edge->endpoint->node_num, n->node_num);
                            while(edge->next){
                                edge = edge->next;
                            }
                            // printf("edge: %p node dest: %d\n", edge, dest->node_num);
                            edge->next = (pedge)(malloc(sizeof(edge)));
                            edge->next->next=NULL;
                            edge->next->endpoint = dest;
                            edge->next->weight = w;
                        }
                    }
                    pnode temp = (*head);
                    while(temp != NULL){
                        // printf("id node: %d\n", temp->node_num);
                        pedge edge = temp->edges;
                        // printf("n node num: %p\n", temp->edges);
                        while(edge != NULL){
                            // printf("edge: %d, %d\n", edge->endpoint->node_num, edge->weight);
                            edge = edge->next;
                        } 
                        temp = temp->next;
                    }
                    index_src--;        
                }
                index_src++;
            }
            head_final = head;
            // printf("head* is: %p\n", *head);
            // printf("head is: %p\n", head);
            next = index_src;// build_graph_cmd(head, word);
            head = head_final;
            // printf("head isss: %p\n", head);
            // printf("head is!!!: %d\n", (*head)->node_num);
            count--;
            // printf("next[0] is: %c", next[0]);
            printf("\nindex_src: %c\n", *next);
        }else if(next[0] == 'B'){
           printf("55");
        //    printf("head isss: %p\n", head);
           next = insert_node_cmd_b(head, next);
           head = head_final;
        //    printf("head: %p\n", head);
        //    printf("num: %d\n", (*head)->node_num);
           count--;
        }
        else if(next[0] == 'D'){
            
            // printf("head_num: %d", (*head_final)->node_num);
            if(head_final == NULL){
                printf("*************88");
            }
            // printf("next[0]: %c\n", *(next+2));
            printf("59\n");
            // printf("head_num: %d", (*head_final)->node_num);
            
            next = delete_node_cmd(head, next);
            head = head_final;
            printf("\nindex_src!!: %c\n", *next);
            // pnode temp = (*head);
            // while(temp != NULL){
            //     printf("id node: %d\n", temp->node_num);
            //     pedge edge = temp->edges;
            //     while(edge != NULL){
            //         printf("edge: %d, %d\n", edge->endpoint->node_num, edge->weight);
            //         edge = edge->next;
            //     } 
            //     temp = temp->next;
            // }
            // exit(1);
            count--;
        }
        else if(next[0] == 'S'){
            // printf("63");
            next = shortsPath_cmd(*head, next);
            count--;
        }
        else if(next[0] == 'T'){
            // printf("68");
            count--;
            continue;
        }
    }
    //   printf("\n%d\n", k);
    // printGraph_cmd(*head);
    return 0;
}
// void deleteGraph_cmd(pnode *head){
    
//     pnode temp = *head;
//     pnode prev = NULL;

//     if(temp != NULL){
//         while (temp)
//         {
//             prev = temp;
//             delete_out_edges(prev);
//             delete_in_edges(&prev, prev->node_num);
//             temp = temp->next;
//         }
        
//     }
// }
// void deleteGraph_cmd(pnode *head){
//     printf("233");
//       if(head){
//         pnode *p = head;
//         while (p)
//         {
//             printf("238");
//             pnode *temp = p;
//             pnode prev = *temp;
//             p=&((*p)->next);
//             delete_out_edges(*temp);
//             delete_in_edges(temp, (*temp)->node_num);
//             free(prev);
//             }
//         }
//     }

char* build_graph_cmd(pnode *head, char text[]){
 
    // deleteGraph_cmd(head);
    text = insert_node_cmd_a(head, text);
    return text;
}
char* delete_node_cmd(pnode *head, char text[]){

    while((*text) == 'D' || (*text) == ' '){
        text++;
    }
    char *ptr = text;
    // printf("ptr: %c\n", *ptr);
    int del = key_word(ptr);
    // printf("del: %d\n", del);
    pnode p = *head;
    pnode prev;

    if(p != NULL && p->node_num == del){
        // printf("im the first\n");
        (*head) = p->next;
        delete_out_edges(p);
        
        //delete in edges
        delete_in_edges(head, del);
        free(p);
        return text;
    }
    while (p != NULL && p->node_num != del)
    {
        // printf("im not the first\n");
            prev = p;
            p = p->next;
    }
    if(p == NULL){
        // printf("not exsist\n");
        return text;
    }else{
    prev->next = p->next;
    delete_out_edges(p);
    delete_in_edges(head, del);
    // printf("***************\n");
    // pnode temp = (*head);
    // while(temp != NULL){
    //     printf("id nodeD: %d\n", temp->node_num);
    //     pedge edge = temp->edges;
    //     while(edge != NULL){
    //         printf("edge: %d, %d\n", edge->endpoint->node_num, edge->weight);
    //         edge = edge->next;
    //     } 
    //     temp = temp->next;
    // }
    
    free(p);
    }
    return text;
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
        }
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
        }
        if(count == 0){
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
    // pedge edge = *e;
    while (e && *e)
    {
        pedge temp = *e;
        e = &((*e)->next);
        free(temp);
    }
    p->edges = NULL;
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

pnode add_node2(pnode** head, int id){
    // printf("head* is: %p\n", *head);
    pnode pn = (pnode)malloc(sizeof(node));
    if(!pn){
        printf("no memory\n");
    }
    // printf("head is: %p\n", head);
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
    // printf("edge in add: %d,%d\n", edge->endpoint->node_num, edge->weight);
    // return edge;
}


char* insert_node_cmd_a(pnode *head1, char text[]){
    char *index_src = text;
    while((*index_src)=='A' || (*index_src)==' '){
        index_src++;
    }
    int num_of_nodes = key_word(index_src);
    // printf("%d\n",num_of_nodes);
    // printf("index: %c\n", *index_src);
    pnode *head = head1;
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
            // printf("index: %c\n", *index_src);
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
                n = n_first;
            }else{
                // printf("head is ot null\n");
                pnode head_temp = *head;
                while (head_temp)
                {
                    head_temp = head_temp->next;
                }
                n = exists_in_graph(head,id_node);
                if(n == NULL){
                    // printf("n is null\n");
                    n = add_node(head,id_node);
                    head_temp = n;
                }
            }
            // printf("n node num: %d\n", n->node_num);
            printf("n node num: %d\n", n->node_num);
            while((*index_src) != 'n' && (*index_src) != '\n' && (*index_src) != 'B' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S'){
                // printf("index: %c\n", *index_src);
                id_node_dest = key_word(index_src);
                // printf("id: %d\n", id_node_dest);
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
                    printf("edge pointer: %p, %p\n", edge, n->edges);
                    printf("edge: %d node n: %d\n", edge->endpoint->node_num, n->node_num);
                    while(edge->next){
                        edge = edge->next;
                    }
                    printf("edge: %p node dest: %d\n", edge, dest->node_num);
                    edge->next = (pedge)(malloc(sizeof(edge)));
                    edge->next->next=NULL;
                    edge->next->endpoint = dest;
                    edge->next->weight = w;
                }
            }
            pnode temp = (*head);
            while(temp != NULL){
                printf("id node: %d\n", temp->node_num);
                pedge edge = temp->edges;
                while(edge != NULL){
                    printf("edge: %d, %d\n", edge->endpoint->node_num, edge->weight);
                    edge = edge->next;
                } 
                temp = temp->next;
            }
            index_src--;        
        }
        index_src++;
    }
    head_final = head;
    printf("head* is: %p\n", *head);
    printf("head is: %p\n", head);
    return index_src;
}

char* insert_node_cmd_b(pnode *head1, char text[]){
    char *index_src = text;
    while((*index_src)=='B' || (*index_src)==' '){
        index_src++;
    }
    pnode *head = head_final;
    // printf("head* is: %p\n", *head);
    // printf("head is: %p\n", head);
    int id_node = key_word(index_src);
    int ans = index_add(id_node,index_src);
    index_src+=ans;
    // printf("id: %d\n",id_node);
    int id_node_dest;
    int w;
    pnode n = *head;
    // printf("head is: %p %p\n", head_final, *head_final);
    while (n && n->next != NULL && n->node_num != id_node)
    {
        n=n->next;
    }
    if(!(n->next) && n->node_num != id_node){
        // printf("head is: %p\n", n);
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
            // printf("edge: %d node n: %d\n", temp->endpoint->node_num, n->node_num);
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
            // printf("edge pointer: %p, %p\n", edge, n->edges);
            // printf("edge: %d node n: %d\n", edge->endpoint->node_num, n->node_num);
            while(edge->next){
                edge = edge->next;
            }
            // printf("edge: %p node dest: %d\n", edge, dest->node_num);
            edge->next = (pedge)(malloc(sizeof(edge)));
            edge->next->next=NULL;
            edge->next->endpoint = dest;
            edge->next->weight = w;
        }
    }
    pnode temp = (*head);
    while(temp != NULL){
        // printf("id node: %d\n", temp->node_num);
        pedge edge = temp->edges;
        while(edge != NULL){
            // printf("edge: %d, %d\n", edge->endpoint->node_num, edge->weight);
            edge = edge->next;
        } 
        temp = temp->next;
    }
    // printf("head* is: %p\n", *head);
    // printf("head is: %p\n", head);
    return index_src;
}

pnode exists_in_graphb(pnode *head, int id){

    int key = id;
    printf("head* is: %p\n", *head);
    printf("head is: %p\n", head);
    pnode* temp = head;
    
    // printf("id node in exist befor while: %d, %p, %p\n", id, head, *head);
    while ((*temp))
    {
        if((*temp)->node_num == id){
            // printf("id node in exist: %d\n", (*head)->node_num);
            printf("head* is: %p\n", *head);
    printf("head is: %p\n", head);
            return (*temp);
        }else{
            // printf("id node in exist: %d\n", (*head)->node_num);
            (*temp)=(*temp)->next;
        }
    }
    printf("head* is: %p\n", *head);
    printf("head is: %p\n", head);
    return NULL;
}

char* insert_node_cmd_b2(pnode *head1, char text[]){
    char *index_src = text;
    printf("index_src: %c\n", *index_src);
    while((*index_src)=='B' || (*index_src)==' '){
        index_src++;
    }
    printf("index: %c\n", *index_src);
    pnode *head = head1;
    while ((*index_src) != 0 && (*index_src) != '\n' && (*index_src) != 'A' && (*index_src) != 'B' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S')
    {
        // printf("index: %c\n", *index_src);
      
            // build_node(index_src,head);
            // while (*index_src == ' ')
            // {
            //     index_src++;
            // }
            // printf("index: %c\n", *index_src);
            
            int id_node = key_word(index_src);
            // printf("id_node %d", id_node);
            int ans = index_add(id_node,index_src);
            printf("index_src %c\n", (*index_src));
            printf("ans is: %d\n", ans);
            index_src+=ans;
            printf("index_src %c\n", (*index_src));
            printf("id_node: %d\n",id_node);
            int id_node_dest;
            int w;
            pnode n_first;
            pnode n;
            // pnode pn = NULL;
            // if(head == NULL){//first node
            //     printf("the head is null: %d\n", id_node_dest);
            //     n_first = add_node(head,id_node);
            //     head = &n_first;
            //     *head = n_first;
            //     n = n_first;
            // }else{
                // printf("head is ot null\n");
                // n = exists_in_graphb(head,id_node);
                // pnode* temp = head;
    
            // printf("id node in exist befor while: %d, %p, %p\n", id, head, *head);
            // while ((*temp))
            // {
            //     if((*temp)->node_num == id){
            //         // printf("id node in exist: %d\n", (*head)->node_num);
            //         printf("head* is: %p\n", *head);
            // printf("head is: %p\n", head);
            //         n=(*temp);
            //     }else{
            //         // printf("id node in exist: %d\n", (*head)->node_num);
            //         (*temp)=(*temp)->next;
            //     }
            // }
                // if(n == NULL){
                    // printf("n is null\n");
                    n = add_node2(&head,id_node);
            // exit(0);
                    // head = head1;
                pnode head_temp = *head;
            //     pnode temp = (*head);
            // while(temp != NULL){
            //     printf("id node: %d\n", temp->node_num);
            //     pedge edge = temp->edges;
            //     // printf("n node num: %p\n", temp->edges);
            //     while(edge != NULL){
            //         printf("edge: %d, %d\n", edge->endpoint->node_num, edge->weight);
            //         edge = edge->next;
            //     } 
            //     temp = temp->next;
            // }
                while (head_temp->next)
                {
                    head_temp = head_temp->next;
                }
                    head_temp = n;
                // }
            // }
            
            while((*index_src) != 0 && (*index_src) != '\n' && (*index_src) != 'A' && (*index_src) != 'B' && *index_src != 'D' && *index_src != 'T' && *index_src != 'S'){
                printf("index!!!11: %c\n", *index_src);
                printf("index!!!11: %d\n", *index_src);
                while (*index_src == ' ' || *index_src == 'n')
                {
                    index_src++;
                }
                id_node_dest = key_word(index_src);
                printf("id_node_dest: %d\n", id_node_dest);
                ans = index_add(id_node_dest,index_src);
                printf("index_src is!: %c\n", (*index_src));
                index_src+=ans;
                printf("index_src is!!: %c\n", (*index_src));
                printf("ans!!!!!!!!!!!!!!!!!: %d\n", ans);
                w = key_word(index_src);
                ans = index_add(w,index_src);
                index_src+=ans;
                printf("ans: %d\n", ans);
                printf("id dest: %d\n",id_node_dest);
                printf("w: %d\n",w);
                pnode dest = exists_in_graph(head,id_node_dest);
                printf("dest pointer: %p, node id:%d\n", dest, id_node_dest);
                if(dest == NULL){
                    printf("the dest is null! %p", dest);
                    dest = add_node(head,id_node_dest);
                }
                if(!n->edges){
                    n->edges = (pedge)(malloc(sizeof(edge)));
                    n->edges->next = NULL;
                    n->edges->endpoint = dest;
                    n->edges->weight = w;
                }else{
                    pedge edge = n->edges;
                    printf("edge pointer: %p, %p\n", edge, n->edges);
                    printf("edge: %d node n: %d\n", edge->endpoint->node_num, n->node_num);
                    while(edge->next){
                        edge = edge->next;
                    }
                    printf("edge: %p node dest: %d\n", edge, dest->node_num);
                    edge->next = (pedge)(malloc(sizeof(edge)));
                    edge->next->next=NULL;
                    edge->next->endpoint = dest;
                    edge->next->weight = w;
                }
            }
            pnode temp = (*head);
            while(temp != NULL){
                printf("id node: %d\n", temp->node_num);
                pedge edge = temp->edges;
                // printf("n node num: %p\n", temp->edges);
                while(edge != NULL){
                    printf("edge: %d, %d\n", edge->endpoint->node_num, edge->weight);
                    edge = edge->next;
                } 
                temp = temp->next;
            }
            // index_src--;        
        printf("index___src: %d\n", (*index_src));
        // head_final = head;
        // index_src++;
    }
    head_final = head;
    printf("%p\n", head_final);
    printf("%d\n", (*head_final)->node_num);
    // printf("%c", *index_src);
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

    int key = id;
    // printf("head* is: %p\n", *head);
    // printf("head is: %p\n", head);
    pnode temp = *head;
    
    // printf("id node in exist befor while: %d, %p, %p\n", id, head, *head);
    while (temp)
    {
        if(temp->node_num == id){
            // printf("id node in exist: %d\n", (*head)->node_num);
            return temp;
        }else{
            // printf("id node in exist: %d\n", (*head)->node_num);
            temp=temp->next;
        }
    }
    return NULL;
    // int key = id;
    // // pnode temp = *head;
    // while ((*head))
    // {
    //     if((*head)->node_num == id){
            // printf("id node in exist: %d\n", (*head)->node_num);
    //         return (*head);
    //     }else{
            // printf("id node in exist: %d\n", (*head)->node_num);
    //         (*head)=(*head)->next;
    //     }
    // }
    // return NULL;
}


// pnode add_node(pnode *head, int id){
//     // if(head == NULL){
        // printf("297");
//     //     head = (pnode*)malloc(sizeof(pnode*));
//     //     // (*head) = (pnode)malloc(sizeof(node));
//     //     // (*head)->node_num=id;
//     //     // (*head)->edges=NULL;
//     //     // (*head)->next=NULL;
//     //     // pnode n = (pnode)malloc(sizeof(node));
//     //     // (*head)->next = n;
//     //     // return *head;
//     // }else{
        // printf("317");
//         pnode n = (pnode)malloc(sizeof(node));
//         pnode pn = NULL;
//         if(!head){
//             n->node_num=id;
//             n->edges=NULL;
//             n->next=NULL;
//             // pn->next = n;
//             head=&n;
//         }else{
//         pn = *head;
//         n->node_num=id;
//         n->edges=NULL;
//         n->next=NULL;
//         pn->next = n;
//         while (pn->next)
//         {
//             pn=pn->next;
//         }
//     }
    
    // return n;
// }

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

char* shortsPath_cmd(pnode head, char *word){

    pnode temp =head;

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
    printf("src: %d, dest: %d", src, dest);
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

    for(int k=0;k < n; k++){
        printf("\ndistance[%d] =  %d\n", k, distance[k]);
    }
    if(distance[end_node] == INFINITY){
        printf("Dijsktra shortest path: -1");
    }else{
        printf("Dijsktra shortest path: %d", distance[end_node]);
}
}

int key_word(char * word){

    while (*word == ' ' || *word == 'n')
    {
        word++;
    }
    char* str = word;
    // printf();
    if(strlen(word) != 1){
    int i=1;
    while (word[i] != ' ')
    {
       str[i] = word[i];
       i++;
    }
    }
    int key = atoi(str);
    // word = (word+i);
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