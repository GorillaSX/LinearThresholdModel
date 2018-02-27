//declare a node class
#ifndef _NODE_H
#define _NODE_H
#include <iostream>
#include <set>
using namespace std;
#include "neighbor.h"
//Node class
class Node
{
	public:
		//constructor
		Node(int name,int min,int max);
		Node(int name);
		//get node name
		int getName(void)const;
		//get node threshold
		double getThreshold(void)const;
		//get the node tendency
		double getTendency(void)const;
		//update node tendency
		void updateTendency(double weight);
		//add a neightbor
		void addNeighbor(Neighbor& neighbor);
		//get a neighbor weight
		double getNeighborWeight(Neighbor& neighbor)const;
		//get neighbor current size
		int getNeighborsSize(void)const;
		//print Node information
		void print(void)const;	
		//initializing node neighbors
		void initNeighbor(set<Node>& nodes);
		//set neighbors weight
		void setNeighborsWeight(void);
		//when node active affect node neighbor
		void affectNeighbor(set<Node>& nodes);
		//overload operator < 
		bool operator < (const Node& r)const;

	private:
		int m_name;
		double m_threshold;
		set<Neighbor> m_neighbors;
		double m_tendency;
};
#endif //_NODE_H
