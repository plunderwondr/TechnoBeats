class VertexBuffer
{
private: 

	// buffer handles (VBOs)
	unsigned int vertexHandle;
	unsigned int normalHandle;
	unsigned int texcoordHandle;

	// array handle (VAO)
	unsigned int vaoHandle;
	
	// total number of vertices to be rendered
	unsigned int numVertices;

public: 

	// default ctor
	VertexBuffer();

	// dtor
	~VertexBuffer();

	// release all data from graphics memory
	void Release();

	// initialize VAO, specifying which data will be used
	// returns 1 for success, 0 for failure
	int Initialize(unsigned int numVerts, bool useNormals, bool useTexcoords);

	// add raw attribute data to respective buffers
	// returns 1 if successful, 0 if failure
	int AddVertices(const float *rawVertices);
	int AddNormals(const float *rawNormals);
	int AddTexcoords(const float *rawTexcoords);

	// activate this VAO for rendering
	void Activate() const;

	// deactivate VAO
	static void Deactivate();

	// render this VAO
	void Render() const;
	void ActivateAndRender() const;

};