class Particle{

//variabile
public:
	unsigned int vbo, ibo, vao, num_indices;
	glm::vec3 pozitie, viteza, culoare;
	glm::mat4 model_matrix;
//metode
public:
	Particle() {
		model_matrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		viteza = glm::vec3((float)rand() / RAND_MAX * 20, 0, 0);
		culoare = glm::vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);

		std::vector<lab::VertexFormat> vertices;
		std::vector<unsigned int> indices;
		int n = 1;

		// Geneream punctele si indecsii

		float dy = ((float)rand() / RAND_MAX)*50;

		vertices.push_back(lab::VertexFormat(-n, -n+dy, 0, 0, 0));
		vertices.push_back(lab::VertexFormat(n, -n + dy, 0, 1, 0));
		vertices.push_back(lab::VertexFormat(n, n + dy, 0, 1, 1));
		vertices.push_back(lab::VertexFormat(-n, n + dy, 0, 0, 1));

		indices.push_back(0); 			indices.push_back(1);			indices.push_back(2);
		indices.push_back(0);			indices.push_back(2);			indices.push_back(3);

		// declar containere de date
		unsigned int vao_id, vbo_id, ibo_id;

		//init vertex array object 
		glGenVertexArrays(1, &vao_id);
		glBindVertexArray(vao_id);

		//init vertex buffer object
		glGenBuffers(1, &vbo_id);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(lab::VertexFormat), &vertices[0], GL_STATIC_DRAW);

		//init ibo
		glGenBuffers(1, &ibo_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		//legare de atribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)0);						//trimite pozitii pe 0
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)(2 * sizeof(float)* 3));		//trimite texcoords pe 2

		vao = vao_id;
		vbo = vbo_id;
		ibo = ibo_id;
		num_indices = indices.size();
	
	}
	~Particle() {}
	void translate(float x, float y, float z){
		model_matrix = glm::translate(model_matrix, glm::vec3(x, y, z));
	}
	void translate2(glm::vec3 x){
		model_matrix = glm::translate(model_matrix, x);
	}
	void rotate(float angle, float x, float y, float z){
		model_matrix = glm::rotate(model_matrix, angle, glm::vec3(x, y, z));
	}
	void scale(float x, float y, float z){
		model_matrix = glm::scale(model_matrix, glm::vec3(x, y, z));
	}
};