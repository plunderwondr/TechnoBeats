#include "NavMesh.h"
#include <list>
#include <iostream>

NavMesh::NavMesh(void)
{
}


NavMesh::~NavMesh(void)
{

}

void NavMesh::LoadMesh(std::string MeshFile)
{
	int fileEnd = 1;	//fileEnd, used for checking if we have reached the end of the file. Initialized to 1 to start the loop.
	char line[32];		//Char array, used for assigning values from the file stream
	FILE* navMesh;	//FILE pointer, the stream for the obj file is assigned to this value so it can be read
	navMesh = fopen(MeshFile.c_str(), "rt");		//Open the stream and assign it to our FILE variable, uses the file sent in. "rt" makes it read-only text

	Vector3<float> tempVert;						//Create a 3D vector to store temporary vertex values
	std::vector<Vector3<float>> tempVerts;			//Create a dynamic array of 3D vectors to save all the temporary vertices

	//Loop while the program is not at the end of the file
	while (fileEnd != EOF)							
	{
		fileEnd = fscanf(navMesh, "%s", line);	//Scan the file stream for a string, assign the first string encountered to the line variable (array of characters)

		//If the string is v...
		if (strcmp(line, "v" ) == 0)
		{
			fscanf(navMesh, "%f %f %f", &tempVert.x, &tempVert.y, &tempVert.z);	//Search the stream for 3 float values separated by spaces and assign them to the temporary Vertex
			tempVerts.push_back(tempVert);										//Add the temporary vertex to the dynamic array
			Node temp;															//Create a temp node	
			temp.Position = tempVert;											//Set the nodes position
			temp.NodeNumber = Nodes.size();										//Set the nodes number to be the last in the list
			Nodes.push_back(temp);											//Add it to the vector of nodes;
		}
		//If the string is f...
		else if (strcmp(line, "f") == 0)
		{
			bool first(false), second(false);
			float index[9];																			//Create an array of floats
			fscanf(navMesh,"%f/%f/%f %f/%f/%f %f/%f/%f", &index[0], &index[1], &index[2],			//Scan the stream for 9 floats separated by spaces and slashes. The first values (0,3,6) are the indices for the Vertices of the face
														   &index[3], &index[4], &index[5],			//The next values (1,4,7) are the indices for the UV coordinates of the face
														   &index[6], &index[7], &index[8]);		//The next values are the indices for the Normals of the face
			
			//Loop through the neighbours of one the three nodes
			for (int i = 0; i < Nodes[index[0]-1].neighbours.size() - 1 && Nodes[index[0]-1].neighbours.size() > 0; i++)
			{
				//If either node is already in the list, skip adding it
				if (Nodes[index[0]-1].neighbours[i] == index[3]-1)
					first = true;
				else if (Nodes[index[0]-1].neighbours[i] == index[6]-1)
					second = true;
			}

			//If the nodes were not in the list, add them to the nodes neighbours
			if (!first)
				Nodes[index[0]-1].neighbours.push_back(index[3]-1);
			if (!second)
				Nodes[index[0]-1].neighbours.push_back(index[6]-1);

			first = false;
			second = false;
			
			//Repeat for the other 2 nodes
			for (int i = 0; i < Nodes[index[3]-1].neighbours.size() -1 && Nodes[index[3]-1].neighbours.size() > 0; i++)
			{
				if (Nodes[index[3]-1].neighbours[i] == index[0]-1)
					first = true;
				else if (Nodes[index[3]-1].neighbours[i] == index[6]-1)
					second = true;
			}

			if (!first)
				Nodes[index[3]-1].neighbours.push_back(index[0]-1);
			if (!second)
				Nodes[index[3]-1].neighbours.push_back(index[6]-1);

			first = false;
			second = false;
			
			//Repeat
			for (int i = 0; i < Nodes[index[6]-1].neighbours.size() -1 && Nodes[index[6]-1].neighbours.size() > 0; i++)
			{
				if (Nodes[index[6]-1].neighbours[i] == index[0]-1)
					first = true;
				else if (Nodes[index[6]-1].neighbours[i] == index[3]-1)
					second = true;
			}

			if (!first)
				Nodes[index[6]-1].neighbours.push_back(index[0]-1);
			if (!second)
				Nodes[index[6]-1].neighbours.push_back(index[3]-1);

			first = false;
			second = false;
		}
	}

	fclose(navMesh);						//Close the stream
}

void NavMesh::FindPath(int Start)
{
	//If the node being searched from is not within the list, automatically exit
	if (Start > Nodes.size()-1)
		return;

	//Create a vector for nodes being searched
	std::vector<Node> NodesSearching;

	//Create a node for current
	Node current;

	//Create a float for checking the shortest distance
	float shortestDist;
	//Create an int to track which node is to be checked next
	int nextCheck(0);

	//Set all node distances to -1, set visited to false and previous to NULL
	for (int i = 0; i < Nodes.size()-1;i++)
	{
		Nodes[i].dist = -1;
		Nodes[i].visited = false;
		Nodes[i].previous = NULL;
	}

	//Set the start nodes distance to 0
	Nodes[Start].dist = 0.0;

	//Add the start node to the searching list
	NodesSearching.push_back(Nodes[Start]);

	//while the searching list is not empty
	while (!NodesSearching.empty())
	{
		//The shortest distance is equal to the last nodes distance
		shortestDist = NodesSearching.end()->dist;

		//Loop through all the nodes being searched
		for (int i = 0; i <= NodesSearching.size()-1; i++)
		{
			//Check if their distances are less than the shortest distance and if they have been checked
			if (NodesSearching[i].dist < shortestDist && !NodesSearching[i].visited)
			{
				//If the node is unchecked and they have the shortest distance, set shortest distance to their distance
				shortestDist =  NodesSearching[i].dist;
				//Check the node next
				nextCheck = i;
			}
		}

		//Set the current node to be the next searched node
		current = NodesSearching[nextCheck];

		//Create an iterator
		std::vector<Node>::iterator it;

		//Run through the list of nodes being searched
		for (it = NodesSearching.begin(); it != NodesSearching.end();)
		{
			//Hold the current iterator information
			Node t = (*it);

			//If the current node is the node being checked remove it from the list
			if (t.NodeNumber == current.NodeNumber)
				it = NodesSearching.erase(it);
			else
				it++;
		}

		//Loop through all the neighbours of the node being checked
		for (int i = 0; i <= current.neighbours.size()-1;i++)
		{
			//Set the distance to be the current node's distance plus the distance between the current node and the neighbour
			float dist = current.dist + (current.Position - Nodes[current.neighbours[i]].Position).GetLength();
			
			//If distance is less than the neighbour's distance, or their distance is -1
			if (dist < Nodes[current.neighbours[i]].dist || Nodes[current.neighbours[i]].dist == -1)
			{
				//Set the neighbour's distance to the distance calculated
				Nodes[current.neighbours[i]].dist = dist;
				//Set their previous node to point to the current node
				Nodes[current.neighbours[i]].previous = &current;

				//If the current neighbour is not visited
				if (!Nodes[current.neighbours[i]].visited)
				{
					//Set visited to true
					Nodes[current.neighbours[i]].visited = true;
					//Add it to the search list
					NodesSearching.push_back(Nodes[current.neighbours[i]]);
				}
			}
		}
	}
}
