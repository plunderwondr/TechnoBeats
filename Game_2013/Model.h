//Model Header

#ifndef MODEL_H
#define MODEL_H

#pragma once

#include <vector>
#include <string>

#include "SFML\include\SFML\OpenGL.hpp"
#include "SFML\include\SFML\Graphics.hpp"
#include "SFML\include\glm\glm.hpp"
// #include <SFML\OpenGL.hpp>
//#include <SFML\Graphics.hpp>
//#include <glm\glm.hpp>
#include "Vector.h"
#include "AnimationMath.h"
#include "VertexBuffer.h"

//Face struct
//Maintains the 3 points of the face
//UV coordinates for the face
//Normals for each point
typedef struct Face {
	std::vector<Vector3<float>> pos;		//Position of points
	std::vector<UV_Vector> uvVec;			//UV Coordinates
	std::vector<Vector3<float>> norm;		//Normals
} Face;

//Object struct
//Maintains the number of faces the model has
//Maintains each Face
typedef struct Object {
	int numFaces;
	std::vector<Face> faces;
} Object;

//Model Class
class Model
{
public:
	//Default Constructor
	Model(void);
	//Constructor with the file for the mesh and the file for the texture
	Model(char* modelFile, std::string texFile);
	//Default Deconstructor
	~Model(void);
	
	//Load the model using a model file and a texture file
	void loadObject(char* modelFile, std::string texFile);
	
	//Load the texture using a texture file
	void loadModel(char* modelFile);
	
	//Load the model using a texture file
	void loadTex(std::string texFile);

	//Read the object
	void readObject();

	//Overloaded operators for use in Interpolation
	Model operator+(const Model &model) const;
	Model operator*(const float f) const;

	//Object contains the mesh for the model
	Object form;
	//Texture contains the texture
	GLuint tex;
	glm::vec3 *vertexlist;
	glm::vec3 *normalslist;
	glm::vec2 *uvlist;
	VertexBuffer vbo;
};

#endif