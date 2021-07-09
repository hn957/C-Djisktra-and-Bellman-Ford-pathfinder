#ifndef SHORTPATH_H_
#define SHORTPATH_H_

#include <queue>
#include "myHeap.full.h"  // This is my version of HW 2.  You can include your own binary heap

#define LARGE1 9999999

using namespace std;


struct arc{
  struct arc *next;
  int length;
  int end;
  };

typedef struct node{
   struct arc *first; /* first arc in linked list */
   int id;  // The number of the vertex in this node 
   int key;  /* Distance estimate, named key to reuse heap code*/
   int P;  /* Predecessor node in shortest path */
   int position;  /* Position of node in heap, from 0 to Nm, where 0 is best */
   } nodeitem;

void BellmanFord(nodeitem N[], int Or, int Nm)
{
    // You program this, a  Bellman Ford algorithm that uses a work queue.  DO NOT implement this as 3 for loops. 
    // That can be very slow, and waste many iterations. 
    struct arc* edge;
    int v, dv, min_d, min_v;
    N[Or].key = 0;
    min_v = Or;
    min_d = 0;
    queue<int> q;
    q.push(Or);
    edge = N[Or].first;
    N[Or].position = 1;



    while (!q.empty()) {
        while (edge != NULL) {
            v = edge->end;
            dv = min_d + edge->length;
            if (N[v].key > dv) {
                N[v].key = dv;
                N[v].P = q.front();
                if (N[v].position == -1) {
                    N[v].position = 1;
                    q.push(v);
                }
            }
            edge = edge->next;
        }

        if (q.size() == 1) {
            q.pop();
        }
        else {
            N[q.front()].position = -1;
            q.pop();
            edge = N[q.front()].first;
            min_d = N[q.front()].key;
        }

    }

}
/* ---------------*/


void Dijkstra(nodeitem N[], int Or, int Nm)
{
    int Mark[Nm+1];
    struct arc *edge;
    int v, dv, min_d, min_v, finished;
    for (int i=1; i<=Nm; i++){
        Mark[i]=-1;
    }
    N[Or].key = 0;
    Mark[Or] = 1;
    finished = 1;
    min_v = Or;
    min_d = 0;
    while (finished < Nm){
        edge = N[min_v].first;  //update distances
        while (edge != NULL){ // explore the outgoing arcs of u 
            v = edge->end;
            dv = min_d + edge->length;
            if (N[v].key > dv){
                N[v].key = dv;
                N[v].P = min_v;
            }//if D > dv 
            edge = edge->next;
        }// while edge           
        
        min_d = LARGE1;
        for (int j = 0; j <= Nm; j++){
            if (Mark[j] < 1){
                if (N[j].key < min_d){
                    min_d = N[j].key;
                    min_v = j;
                }
            }
        } 
        Mark[min_v]=1;
        finished++;
    } 
} /* end Dijkstra */


void DijkstraHeap(nodeitem N[], int Or, int Nm)
{
    Heap<nodeitem>* thisHeap;
    struct arc* edge;
    nodeitem* node;
    thisHeap = new Heap<nodeitem>;


    node = &N[Or];
    node->key = 0;
    thisHeap->insert(node);

    while (!thisHeap->IsEmpty()) {
        node = thisHeap->remove_min();
        edge = node->first;
        while (edge != NULL) {
            int v = edge->end;
            int dv = edge->length + node->key;
            if (N[v].key > dv) {
                N[v].key = dv;
                N[v].P = node->id;
                if (N[v].position == -1) {
                    thisHeap->insert(&N[v]);
                }
                else {
                    thisHeap->decreaseKey(N[v].position, N[v].key);
                }
            }
            edge = edge->next;
        }
    }
    return;
}
#endif
