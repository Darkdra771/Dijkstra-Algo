// Author Sean Davis

#include <iostream>
#include "tripper.h"
#include "RoadRunner.h"
#include "QueueAr.h"
#include "QuadraticProbing.h"
#include "BinaryHeap.h"
#include "StackAr.h"
using namespace std;



Tripper::Tripper(Road *roads, int numRoads, int size): adjacentHash( new Vertex,size*size), tableHash(new TableRow, size*size), heap(10000), mystack(1000), size(size)
{

	for ( int i = 0; i < size * size; i++){
		Vertex* a = new Vertex(i);
		adjacentHash.insert(a);
	}



	//making of adjacent hash
	for (int i = 0; i < numRoads; i++){
		VertexNode* c = new VertexNode(roads[i].city2, roads[i].distance, roads[i].num);
		Vertex* b = new Vertex(roads[i].city1);
		Vertex* a = adjacentHash.find(b);
		//cout << a->getVertexNum() << " " << a->getAdjacentNum() << flush << endl;
		a->enqueue(c);
		a->incrementAdjacent();
	}


} // Tripper()



Tripper::~Tripper()
{
	adjacentHash.makeEmpty();
	tableHash.makeEmpty();
	mystack.makeEmpty();
	heap.makeEmpty();

} // ~Tripper()


int Tripper::findPath(int city1, int city2, int path[], int *pathCount)
{

	//making of djikstras table
	for ( int i = 0 ; i < size * size; i++){
		TableRow* a = new TableRow(i, -1);
		tableHash.insert(a);
	}

	int root = city1;
	int numState = 1;

	TableRow* a = new TableRow(root, -1); //change table row of root
	TableRow* b = tableHash.find(a);
	b->changeDv(0);
	b->changeDisPv(0);
	b->changeState(true);


	//at this point i have djikstars table with root being true


	Vertex* v = new Vertex(root); //update djikstras with adjacenthash
	Vertex* p = adjacentHash.find(v);
	for (int i = 0; i < p->getAdjacentNum(); i++){
		VertexNode* n = p->dequeue();
		p->enqueue(n); //put back into queue
		TableRow* a = new TableRow(n->getVertexNum(), n->getId());
		TableRow* b = tableHash.find(a); //updating table
		b->changePv(root);
		b->changeDisPv(n->getDistance());
		b->changeDv(n->getDistance());
		b->changeId(n->getId());
		VertexNode l(n->getVertexNum(), n->getDistance(), n->getId());
		heap.insert(l); //insert into binary heap
	}

	TableRow* final = new TableRow(city2, -1);

	while (numState != size * size){

			//checks if reach the final destination
			TableRow* change = tableHash.find(final);
			if ( change->getState()){ //check if final destination is true
				(*pathCount) = 0;
				int i = 0;
				int distance = change->getDv();
				while(change->getPv() != -1){
					TableRow* path = new TableRow(change->getPv(), change->getId());
					mystack.push(change->getId());
					change = tableHash.find(path);
				}
				while(!mystack.isEmpty()){
					(*pathCount)++;
					path[i] = mystack.topAndPop();
					i++;
				}
				mystack.makeEmpty();
				tableHash.makeEmpty();
				heap.makeEmpty();
				return distance;
			}


		if(heap.isEmpty()){heap.makeEmpty();cout << "p " << city1 << " " << city2 <<flush << endl;return 0;}
		int currDv = (heap.findMin()).getDistance();
		int currId = (heap.findMin()).getVertexNum();
		int currNum = (heap.findMin()).getId();



		TableRow* check = new TableRow(currId, currNum);
		 change = tableHash.find(check);
		if (change->getState()) {heap.deleteMin();continue;} //if already true
		else { //if not true
			heap.deleteMin();
			change->changeState(true);
			numState++; //increment true count
			//changing the lowest dv to true

			Vertex* q = new Vertex(currId); //finding the adjacency of lowest id
			Vertex* j = adjacentHash.find(q);
			for ( int i = 0; i < j->getAdjacentNum(); i++){
				VertexNode* n = j->dequeue();
				j->enqueue(n);
				TableRow* a = new TableRow(n->getVertexNum(), -1);
				TableRow* b = tableHash.find(a);
				if (b->getState()){continue;} //if known is true continue
				else{
					if ((currDv + n->getDistance()) < b->getDv()){ //if smaller than prev dv
						b->changeDv(currDv + n->getDistance());
						b->changePv(currId);
						b->changeDisPv(n->getDistance());
						b->changeId(n->getId());
						VertexNode k(n->getVertexNum(), currDv + n->getDistance(), n->getId()); //add to heap once updated
						heap.insert(k);
					}
					else {continue;}
				}
			}//end for
		}//end else

	}

	tableHash.makeEmpty();
	heap.makeEmpty();

  return 0;  // to avoid warning for now

}  // findPath()
