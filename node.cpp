//implement  a node class
#include "node.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <set>
using namespace std;
#include "random.h"
//Node class
//constructor
Node::Node(int name,int min,int max):m_name(name)
{
	m_threshold = random<double>(0.00,1.00);
	m_numOfNeighbor = random<int>(min,max);
	m_tendency = 0.00;	
}
Node::Node(int name):m_name(name){}
//get node name
int Node::getName(void)const
{
	return m_name;
}
//get node threshold
double Node::getThreshold(void)const
{
	return m_threshold;
}
//get the number of the node
int Node::getNumOfNeighbor(void)const
{
	return m_numOfNeighbor;
}
//get the node tendency
double Node::getTendency(void)const
{
	return m_tendency;
}
//update node tendency
void Node::updateTendency(double weight)
{
	m_tendency = m_tendency + weight;
}
//add a neighbor
void Node::addNeighbor(Neighbor& neighbor)
{
	m_neighbors.insert(neighbor);
}
//get a neighbor weight
double Node::getNeighborWeight(Neighbor& neighbor)const
{
	set<Neighbor>::iterator it = m_neighbors.find(neighbor);
	return it->getWeight();
}
//get neighbor current size
int Node::getNeighborsSize(void)const
{
	return m_neighbors.size();
}
//print node information
void Node::print(void)const
{
	cout << "Node name: " << m_name<< endl;
	cout << "Node threshold: "<< m_threshold << endl;
	cout << "Node tendency: " << m_tendency << endl;
	cout << "Node neighbor size(): " << m_numOfNeighbor << endl;
	cout << "Node size() " << m_neighbors.size() << endl;
	for(set<Neighbor>::iterator it = m_neighbors.begin();it != m_neighbors.end();++it)
	{
		cout << "Neighbors: "<< it->getName() << ":" << it->getWeight() << " , ";
	}
	cout << endl;
}
//initializing node neighbors
void Node::initNeighbor(set<Node>& nodes)
{
	//cout << "start to init neighbors..." << endl; //node neighbor size will be changed until the whole community finished //initNeighbors,so we will update the neighbor size when set the 
//	neighbor weight
	for(int  i = m_neighbors.size();i < m_numOfNeighbor;i++)
	{
		while(1)
		{
				//random generate a neighbor name
				int nodename = random<int>(0,nodes.size()-1);
				if(nodename == m_name)
						continue;
				//find the neighbor check whether it's neighbors is full
				Node neighbor(nodename);
				set<Node>::iterator it = nodes.find(neighbor);
				if(it != nodes.end())
				{
					//if neighbor's neighbors is not full, add this node as a neighbor
					if(it->getNeighborsSize() < it->getNumOfNeighbor())
					{
						Neighbor neighb(it->getName());
						Neighbor self(m_name);
						pair<set<Neighbor>::iterator, bool> ret;
						ret = m_neighbors.insert(neighb);
						if(ret.second == true)
						{
							const_cast<Node&>(*it).addNeighbor(self);
							break;
						}
					}
				}
		}
	}
//	cout << "end init neighbors" << endl;
}
//set neighbors weight
void Node::setNeighborsWeight(void)
{
	double Totalweight = 1.0;
	double weight = 0.0;
	int num = 0;
	//update each node's neighborsize
	m_numOfNeighbor = m_neighbors.size();
	for(set<Neighbor>::iterator it = m_neighbors.begin(); it != m_neighbors.end();++it)
	{
		if(num != m_numOfNeighbor-1)
		{
		//	double w = random(0.0,Totalweight - weight);
//	        double w = random(0.0, Totalweight/m_neighbors.size());	
			double w = Totalweight/m_neighbors.size();
			const_cast<Neighbor&>(*it).setWeight(w);
			weight = weight + w;
		}
		else
		{
			const_cast<Neighbor&>(*it).setWeight(Totalweight - weight);
		}
		num++;
	}
}
//when node active affect node neighbor
void Node::affectNeighbor(set<Node>& nodes)
{
	for(set<Neighbor>::iterator it = m_neighbors.begin(); it != m_neighbors.end();++it)
	{
		int nodename = it->getName();
		Node node(nodename);
		set<Node>::iterator nit = nodes.find(node);	
		if(nit != nodes.end())
		{
			Neighbor neighbor(m_name);
			double weight = nit->getNeighborWeight(neighbor);	
			const_cast<Node&>(*nit).updateTendency(weight);
		}
	}
}

//overload operator <
bool Node::operator < (const Node& r)const
{
	return this->m_name < r.m_name;
}
