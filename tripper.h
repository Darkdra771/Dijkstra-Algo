// Author Sean Davis
#ifndef _TRIPPER_H
#define	_TRIPPER_H

#include "RoadRunner.h"
#include "QuadraticProbing.h"
#include "QueueAr.h"
#include "BinaryHeap.h"
#include "StackAr.h"
using namespace std;



class VertexNode{

	private:
		int vertexNum; //num of vertex
		int distance; //distance from origin vertex
		int id;


	public:
		VertexNode(int num, int numD, int n) { vertexNum = num; distance = numD; id = n;}
		VertexNode(void) {vertexNum = -1; distance = 0; id = -1;}
		int getVertexNum(void) const{ return vertexNum;}
		int getDistance(void) const { return distance;}
		int getId(void) const {return id;}
		bool operator<(const VertexNode& a)const{
			if( this->distance < a.getDistance()){
				return true;}
			else{
				return false;}
		}
		bool operator!=(const VertexNode& a) const{
			if (this->vertexNum != a.getVertexNum()){ return true;}
			else { return false;}
		}

};

class Vertex{
	
	private:
		int vertexNum; //vertex num
		int numAdjacent; //number of adjacent cities
		Queue<VertexNode*> adjacentList;

	public:
		Vertex(int num): adjacentList(10000) {vertexNum = num; numAdjacent = 0;}
		Vertex(void): adjacentList(10000) {vertexNum = -1; numAdjacent = 0;}
		int getAdjacentNum() const{return numAdjacent;}
		void incrementAdjacent(void) {numAdjacent++;}
		int getVertexNum() const{ return vertexNum;}
		void enqueue(VertexNode* a) { adjacentList.enqueue(a);}
		VertexNode* dequeue(void) {return adjacentList.dequeue();}
		bool isEmpty(void) const { return adjacentList.isEmpty();}
		bool operator!=(const Vertex& RHS) const {
			if (this->vertexNum != RHS.getVertexNum()){ return true;}
			else{ return false;}
		}
			 
};

class TableRow{

	private:
		int vertexId;
		bool known;
		int dv;
		int pv;
		int disPv;
		int id;
	
	public:
		TableRow(void) {vertexId = -1; known = false; dv = 9999; pv = -1;id = -1;disPv = 0;}
		TableRow(int num, int i) { vertexId = num; known = false; dv = 9999; pv = -1; id = i;disPv = 0;}
		int getVertexNum() const{ return vertexId;}
		int getDv() const {return dv;}
		void changeDv(int a) { dv = a;}
		int getPv() const{return pv;}
		void changePv(int a) { pv = a;}
		int getDisPv() const{return disPv;}
		void changeDisPv(int a) { disPv = a;}
		int getId(void) const { return id;}
		void changeId(int i) {id = i;}
		bool getState() const{ return known;}
		void changeState(bool a) { known =a;}
		bool operator!=(const TableRow& RHS) const{
			if(this->vertexId != RHS.getVertexNum()){return true;}
			else { return false;}
		}



};

class Tripper {
private:
  QuadraticHashTable<Vertex*> adjacentHash;
  QuadraticHashTable<TableRow*> tableHash;
  BinaryHeap<VertexNode> heap;
  StackAr<int> mystack;
  int size;

public:
  Tripper(Road *roads, int numRoads, int size);
  int findPath(int city1, int city2, int path[], int *pathCount);
  ~Tripper();


}; // class Tripper


#endif	/* _TRIPPER_H */

