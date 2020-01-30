#pragma once
#include "Vector.h"
#include <vector>
#include <string>

//Node structure, stores the node number, the position of the node and the node numbers for all of its neighbours
//dist, visited and previous are used for Dijkstra's
struct Node
{
	int NodeNumber;
	Vector3<float> Position;
	std::vector<int> neighbours;

	float dist;
	bool visited;
	Node* previous;
};

//NavMesh class, contains the mesh being used for navigation.
//Mesh is usually a plane made in Maya where each vertex represents a node
class NavMesh
{
public:
	NavMesh(void);
	~NavMesh(void);

	//Loads in a mesh and generates node values.
	void LoadMesh(std::string MeshFile);

	//Finds the paths
	void FindPath(int Start);

	//Stores the nodes
	std::vector<Node> Nodes;
};

