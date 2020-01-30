#include "Model.h"
#include <stdio.h>
using namespace std;
//Default constructor
Model::Model(void)
{
	form.numFaces = 0;	//Set the number of faces to 0

	tex = 0;			//Set the texture to 0
	VertexBuffer *ModelVertexBuffer = new VertexBuffer;
}

//Constructor with files, accepts 2 strings as the parameters that contain file locations
//Send the files to their respective functions
Model::Model(char* modelFile, std::string texFile)
{
	
	loadModel(modelFile);	//Send modelFile to the loadModel function to make the mesh

	loadTex(texFile);		//Send the texFile to the loadTex function to get the texture
}

Model::~Model(void)
{
}

//loadObject function, accepts 2 strings as parameters that contain file locations
//Send the files to their respective functions
void Model::loadObject(char* modelFile, std::string texFile)
{
	//Same as overloaded constructor above
	loadModel(modelFile);

	loadTex(texFile);
}

//loadModel function, accepts one string as a parameter that contains a file location for the .obj
//OBJ Loader
void Model::loadModel(char* modelFile)
{

	float * vertex;
	float * normals;
	float * uv;
	/*
	int fileEnd = 1;	//fileEnd, used for checking if we have reached the end of the file. Initialized to 1 to start the loop.
	char line[32];		//Char array, used for assigning values from the file stream
	FILE* modelMesh;	//FILE pointer, the stream for the obj file is assigned to this value so it can be read
	modelMesh = fopen(modelFile.c_str(), "rt");		//Open the stream and assign it to our FILE variable, uses the file sent in. "rt" makes it read-only text

	Vector3<float> tempVert;						//Create a 3D vector to store temporary vertex values
	std::vector<Vector3<float>> tempVerts;			//Create a dynamic array of 3D vectors to save all the temporary vertices
	
	UV_Vector tempUV;								//Create a UV vector to store temporary values
	std::vector<UV_Vector> tempUVs;					//Dynamic array for UV vectors
	
	Vector3<float> tempNorm;						//Temporary Normals
	std::vector<Vector3<float>> tempNormals;		//Dynamic array of tmeporary normals
	
	Face tempFace;									//Temporary Face to save the vertices, UVs and normals
	
	Object objTemp;									//Temporary Object to save all this information
	
	//Loop while the program is not at the end of the file
	while (fileEnd != EOF)							
	{
		fileEnd = fscanf(modelMesh, "%s", line);	//Scan the file stream for a string, assign the first string encountered to the line variable (array of characters)
	
		//Check if the string is a v (vertex), vt (texture vertex), vn (normal vector)
		//or f (face).

		//If the string is v...
		if (strcmp(line, "v" ) == 0)
		{
			fscanf(modelMesh, "%f %f %f", &tempVert.x, &tempVert.y, &tempVert.z);	//Search the stream for 3 float values separated by spaces and assign them to the temporary Vertex
			tempVerts.push_back(tempVert);											//Add the temporary vertex to the dynamic array
		}
		//If the string is vt...
		else if (strcmp(line, "vt" ) == 0)
		{
			fscanf(modelMesh, "%f %f", &tempUV.u,&tempUV.v);						//Search the stream for 2 float values separated by spaces and assign them to the temporary UV
			//tempUV.u -= 1.0f;
			//tempUV.v = tempUV.v - 1;
			tempUV.v = 1 - tempUV.v;

			tempUVs.push_back(tempUV);												//Add the temporary UV to the dynamic array
		}
		//If the string is vn...
		else if (strcmp(line, "vn" ) == 0)
		{
			fscanf(modelMesh, "%f %f %f", &tempNorm.x, &tempNorm.y, &tempNorm.z);	//Search the stream for 3 float values separated by spaces and assign them to the temporary Normal
			tempNormals.push_back(tempNorm);										//Add the temporary Normal to the dynamic array
		}
		//If the string is f...
		else if (strcmp(line, "f") == 0)
		{
			float index[9];																			//Create an array of floats
			fscanf(modelMesh,"%f/%f/%f %f/%f/%f %f/%f/%f", &index[0], &index[1], &index[2],			//Scan the stream for 9 floats separated by spaces and slashes. The first values (0,3,6) are the indices for the Vertices of the face
														   &index[3], &index[4], &index[5],			//The next values (1,4,7) are the indices for the UV coordinates of the face
														   &index[6], &index[7], &index[8]);		//The next values are the indices for the Normals of the face
			
			//Load the Vertices to a temporary face based on index
			//Load the UVs to a temporary face based on index
			//Load the Normals to a temporary face based on index
			tempFace.pos.push_back(tempVerts[index[0]-1]);							
			tempFace.uvVec.push_back(tempUVs[index[1]-1]);							
			tempFace.norm.push_back(tempNormals[index[2]-1]);						
	
			//Ditto
			tempFace.pos.push_back(tempVerts[index[3]-1]);
			tempFace.uvVec.push_back(tempUVs[index[4]-1]);
			tempFace.norm.push_back(tempNormals[index[5]-1]);
	
			//Ditto
			tempFace.pos.push_back(tempVerts[index[6]-1]);
			tempFace.uvVec.push_back(tempUVs[index[7]-1]);
			tempFace.norm.push_back(tempNormals[index[8]-1]);
	
			//Add the temporary face to the temporary object
			objTemp.faces.push_back(tempFace);										

			//Clear all the dynamic arrays for the temporary face for future use
			tempFace.pos.clear();													
			tempFace.uvVec.clear();
			tempFace.norm.clear();
		}


			vertexlist = new std::vector<Vector3<float>>[objTemp.faces.size()];
			
			normalslist = new std::vector<Vector3<float>>[objTemp.faces.size()];
			//std::vector<Vector2<float>> *uvlist;
			theuvlist = new std::vector<Vector2<float>>[objTemp.faces.size()];
			//numvertex = vertexIndices.size();
			
			for( unsigned int i=0; i<objTemp.faces.size(); i++ )
			{
				//unsigned int vertexIndex = tempVerts[i];
				//unsigned int uvIndex = uvIndices[i];
				//unsigned int normalIndex = normalIndices[i];
				Vector3<float> vertex = tempVerts[ 22 ];
				//glm::vec3 vertex = vertexIndices[ vertexIndex-1 ];

				Vector3<float> normal = tempNormals[ normalIndex-1 ];
				Vector3<float> uv = tempUV[ uvIndex-1 ];
				//out_vertices.push_back(vertex[i]);		
				vertexlist[i] = vertex;
				theuvlist[i] = uv;
				normalslist[i] = normal;
	
			}

	}

	
//	ModelVertexBuffer.Initialize(1, true, true);


*/

std::vector < glm::vec3 > out_vertices;
	std::vector < glm::vec2 > out_uvs;
	std::vector < glm::vec3 > out_normals;
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;
	FILE * file = fopen(modelFile, "r");
	if( file == NULL )
	{
		//cout << FileName;
		printf("Impossible to open the file !\n");
	//return false;
	}
	else
	{
		while( 1 )
		{ 	
			char lineHeader[128];
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; 
			if ( strcmp( lineHeader, "v" ) == 0 )
			{
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
				temp_vertices.push_back(vertex);
			}
			else if ( strcmp( lineHeader, "vt" ) == 0 )
			{
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y );
				temp_uvs.push_back(uv);
			}
			else if ( strcmp( lineHeader, "vn" ) == 0 )
			{
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
				temp_normals.push_back(normal);
			}
			else if ( strcmp( lineHeader, "f" ) == 0 )
			{
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
				if (matches != 9)
				{
					//cout << "File can't be read by our simple parser : ( Try exporting with other options\n";
				}
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
					uvIndices    .push_back(uvIndex[0]);
					uvIndices    .push_back(uvIndex[1]);
					uvIndices    .push_back(uvIndex[2]);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[1]);
					normalIndices.push_back(normalIndex[2]);
				}
			}
			vertexlist = new glm::vec3[vertexIndices.size()];
			uvlist = new glm::vec2[uvIndices.size()];
			normalslist = new glm::vec3[normalIndices.size()];
			//numvertex = vertexIndices.size();
			
			for( unsigned int i=0; i<vertexIndices.size(); i++ )
			{
				unsigned int vertexIndex = vertexIndices[i];
				unsigned int uvIndex = uvIndices[i];
				unsigned int normalIndex = normalIndices[i];
				glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
				//glm::vec3 vertex = vertexIndices[ vertexIndex-1 ];

				glm::vec3 normal = temp_normals[ normalIndex-1 ];
				glm::vec2 uv = temp_uvs[ uvIndex-1 ];
				//out_vertices.push_back(vertex[i]);		
				vertexlist[i] = vertex;
				uvlist[i] = uv;
				normalslist[i] = normal;

				//if(vertexlist[i].x > MaxX)
				//{
				//	MaxX = vertexlist[i].x;
				//}
				//if(vertexlist[i].y > MaxY)
				//{
				//	MaxY = vertexlist[i].y;
				//}
				//if(vertexlist[i].x < MinX)
				//{
				//	MinX = vertexlist[i].x;
				//}
				//if(vertexlist[i].y < MinY)
				//{
				//	MinY = vertexlist[i].y;
				//}		
			}
		
		
	}





	vertex = new GLfloat[vertexIndices.size() * 9];
normals = new GLfloat[normalIndices.size() * 9];
uv = new GLfloat[uvIndices.size() * 6];

int mult3 = 0;
		for(int i = 0; i < vertexIndices.size(); i++)
		{
			vertex[mult3 * 3] = vertexlist[i].x;
			vertex[mult3 * 3 + 1] = vertexlist[i].y;
			vertex[mult3 * 3 + 2] = vertexlist[i].z;

			normals[mult3 * 3] = normalslist[i].x;
			normals[mult3 * 3 + 1] = normalslist[i].y;
			normals[mult3 * 3 + 2] = normalslist[i].z;

			uv[mult3 * 2] = uvlist[i].x;
			uv[mult3 * 2 + 1] = uvlist[i].y;	


			i++;
			vertex[mult3 * 3 + 3] = vertexlist[i].x;
			vertex[mult3 * 3 + 4] = vertexlist[i].y;
			vertex[mult3 * 3 + 5] = vertexlist[i].z;

			normals[mult3 * 3 + 3] = normalslist[i].x;
			normals[mult3 * 3 + 4] = normalslist[i].y;
			normals[mult3 * 3 + 5] = normalslist[i].z;

			uv[mult3 * 2 + 2] = uvlist[i].x;
			uv[mult3 * 2 + 3] = uvlist[i].y;

			i++;
			vertex[mult3 * 3 + 6] = vertexlist[i].x;
			vertex[mult3 * 3 + 7] = vertexlist[i].y;
			vertex[mult3 * 3 + 8] = vertexlist[i].z;

			normals[mult3 * 3 + 6] = normalslist[i].x;
			normals[mult3 * 3 + 7] = normalslist[i].y;
			normals[mult3 * 3 + 8] = normalslist[i].z;

			uv[mult3 * 2 + 4] = uvlist[i].x;
			uv[mult3 * 2 + 5] = uvlist[i].y;

			mult3 += 3;
		}




	int numverts = vertexIndices.size();



		

	vbo.Initialize(numverts, true, true);

		//	const float vertex[18] = {
		//	-1, -1, 0,
		//	1, -1, 0,
		//	-1, 1, 0,
		//	-1, 1, 0,
		//	1, -1, 0,
		//	1, 1, 0
		//};

	vbo.AddVertices(vertex);
	vbo.AddNormals(normals);
	vbo.AddTexcoords(uv);
	
	//form.numFaces = objTemp.faces.size();	//The number of faces for the model is equal to the number of elements in the array for the temporary object
	//.faces = objTemp.faces;				//Assign the faces of the temporary object to the faces of the model
	

	//fclose(modelMesh);						//Close the stream...VERY IMPORTANT
}

//loadTex function, accepts one string as a parameter that contains a file location for the texture
//Texture Loader
void Model::loadTex(std::string texFile)
{
	sf::Image texImg;							//Create a new Image

	if (!texImg.loadFromFile(texFile.c_str()))	//Open the image based on the file that is sent in	
		exit(1);								//End the program if the game can not find the image
	
    glGenTextures(1, &tex);						//Generate a new texture on the tex variable
    glBindTexture(GL_TEXTURE_2D, tex);			//Bind the 2D texture to tex
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, texImg.getSize().x, texImg.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, texImg.getPixelsPtr());	//Create the texture based on the image
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

//readObject function, draws the model with the texture it has assigned to it
void Model::readObject()
{
	glBindTexture(GL_TEXTURE_2D, tex);												//Bind the texture
	vbo.ActivateAndRender();
	//glBegin(GL_TRIANGLES);															//Begin drawing triangles
	//	for (int j = 0; j < form.numFaces; j++)										//Loop through all the faces of the model
	//	{
	//		glTexCoord2f(form.faces[j].uvVec[0].u,form.faces[j].uvVec[0].v);		//Specify the UV coordinates for the texture, bind it to the coordinate
	//		glNormal3f(form.faces[j].norm[0].x,										//Specify the normal
	//				   form.faces[j].norm[0].y, 
	//				   form.faces[j].norm[0].z);


	//				   
	//		glVertex3f(form.faces[j].pos[0].x,										//Get the point for the vertex from the face
	//					form.faces[j].pos[0].y,
	//					form.faces[j].pos[0].z);
	//		
	//		glTexCoord2f(form.faces[j].uvVec[1].u,form.faces[j].uvVec[1].v);		//Repeat
	//		glNormal3f(form.faces[j].norm[0].x,										
	//				   form.faces[j].norm[0].y, 
	//				   form.faces[j].norm[0].z);
	//		glVertex3f(form.faces[j].pos[1].x,
	//					form.faces[j].pos[1].y,
	//					form.faces[j].pos[1].z);
	//		
	//		glTexCoord2f(form.faces[j].uvVec[2].u,form.faces[j].uvVec[2].v);		//Repeat
	//		glNormal3f(form.faces[j].norm[0].x,										
	//				   form.faces[j].norm[0].y, 
	//				   form.faces[j].norm[0].z);
	//		glVertex3f(form.faces[j].pos[2].x,
	//					form.faces[j].pos[2].y,
	//					form.faces[j].pos[2].z);
	//	}						  
	//glEnd();																		//After looping through all the faces, stop drawing
}

Model Model::operator+ (const Model &model) const
{
	Model temp;
	temp.form.numFaces = form.numFaces;

	Face tempFace;
	for (int i = 0; i < form.numFaces;i++)
	{
		tempFace.pos.push_back(form.faces[i].pos[0] + model.form.faces[i].pos[0]);
		tempFace.pos.push_back(form.faces[i].pos[1] + model.form.faces[i].pos[1]);
		tempFace.pos.push_back(form.faces[i].pos[2] + model.form.faces[i].pos[2]);
		
		tempFace.uvVec.push_back(form.faces[i].uvVec[0] + model.form.faces[i].uvVec[0]);
		tempFace.uvVec.push_back(form.faces[i].uvVec[1] + model.form.faces[i].uvVec[1]);
		tempFace.uvVec.push_back(form.faces[i].uvVec[2] + model.form.faces[i].uvVec[2]);

		tempFace.norm.push_back(form.faces[i].norm[0] + model.form.faces[i].norm[0]);
		tempFace.norm.push_back(form.faces[i].norm[1] + model.form.faces[i].norm[1]);
		tempFace.norm.push_back(form.faces[i].norm[2] + model.form.faces[i].norm[2]);

		temp.form.faces.push_back(tempFace);
	}

	temp.tex = tex;

	return temp;
}

Model Model::operator* (const float f) const
{
	Model temp;
	temp.form.numFaces = form.numFaces;

	Face tempFace;
	for (int i = 0; i < form.numFaces;i++)
	{
		tempFace.pos.push_back(form.faces[i].pos[0] * f);
		tempFace.pos.push_back(form.faces[i].pos[1] * f);
		tempFace.pos.push_back(form.faces[i].pos[2] * f);
		
		tempFace.uvVec.push_back(form.faces[i].uvVec[0]);
		tempFace.uvVec.push_back(form.faces[i].uvVec[1]);
		tempFace.uvVec.push_back(form.faces[i].uvVec[2]);

		tempFace.norm.push_back(form.faces[i].norm[0]);
		tempFace.norm.push_back(form.faces[i].norm[1]);
		tempFace.norm.push_back(form.faces[i].norm[2]);

		temp.form.faces.push_back(tempFace);
	}

	temp.tex = tex;

	return temp;
}