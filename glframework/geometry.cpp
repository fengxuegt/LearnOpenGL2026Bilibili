//
// Created by fengxuegt on 2026/3/12.
//

#include "geometry.h"

#include <vector>

Geometry::Geometry() {
}

Geometry::Geometry(const std::vector<float> &positions, const std::vector<float> &normals,
	const std::vector<float> &uvs, const std::vector<unsigned int> &indices) {
	mIndicesCount = indices.size();
	glGenBuffers(1, &mPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mPosVbo);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &mUvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mUvVbo);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), uvs.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &mNormalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mNormalVbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

	//3 EBO创建
	glGenBuffers(1, &mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	//4 VAO创建
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	glBindBuffer(GL_ARRAY_BUFFER, mPosVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, mUvVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, mNormalVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	//5.4 加入ebo到当前的vao
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);

	glBindVertexArray(0);

}

Geometry::~Geometry() {
	if (mVao) {
		glDeleteVertexArrays(1, &mVao);
	}
	if (mPosVbo) {
		glDeleteBuffers(1, &mPosVbo);
	}
	if (mUvVbo) {
		glDeleteBuffers(1, &mUvVbo);
	}
	if (mNormalVbo) {
		glDeleteBuffers(1, &mNormalVbo);
	}
	if (mTangentVbo) {
		glDeleteBuffers(1, &mTangentVbo);
	}
    if (mEbo) {
        glDeleteBuffers(1, &mEbo);
    }
}

GLuint Geometry::getVao() {
    return mVao;
}

GLuint Geometry::getIndicesCount() {
    return mIndicesCount;
}

Geometry * Geometry::createBox(float size) {
	Geometry* geometry = new Geometry();
	geometry->mIndicesCount = 36;

	float halfSize = size / 2.0f;

	float positions[] = {
		// Front face
		-halfSize, -halfSize, halfSize, halfSize, -halfSize, halfSize, halfSize, halfSize, halfSize, -halfSize, halfSize, halfSize,
		// Back face
		-halfSize, -halfSize, -halfSize, -halfSize, halfSize, -halfSize, halfSize, halfSize, -halfSize, halfSize, -halfSize, -halfSize,
		// Top face
		-halfSize, halfSize, halfSize, halfSize, halfSize, halfSize, halfSize, halfSize, -halfSize, -halfSize, halfSize, -halfSize,
		// Bottom face
		-halfSize, -halfSize, -halfSize, halfSize, -halfSize, -halfSize, halfSize, -halfSize, halfSize, -halfSize, -halfSize, halfSize,
		// Right face
		halfSize, -halfSize, halfSize, halfSize, -halfSize, -halfSize, halfSize, halfSize, -halfSize, halfSize, halfSize, halfSize,
		// Left face
		-halfSize, -halfSize, -halfSize, -halfSize, -halfSize, halfSize, -halfSize, halfSize, halfSize, -halfSize, halfSize, -halfSize
	};

	float uvs[] = {
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
	};

	float normals[] = {
		//前面
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		//后面
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		//上面
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		//下面
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		//右面
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		//左面
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
	};

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0,   // Front face
		4, 5, 6, 6, 7, 4,   // Back face
		8, 9, 10, 10, 11, 8,  // Top face
		12, 13, 14, 14, 15, 12, // Bottom face
		16, 17, 18, 18, 19,  16, // Right face
		20, 21, 22, 22, 23, 20  // Left face
	};

	//2 VBO创建
	GLuint& posVbo = geometry->mPosVbo, uvVbo = geometry->mUvVbo, normalVbo = geometry->mNormalVbo ;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	glGenBuffers(1, &normalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

	//3 EBO创建
	glGenBuffers(1, &geometry->mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//4 VAO创建
	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);

	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	//5.4 加入ebo到当前的vao
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);

	glBindVertexArray(0);

	return geometry;
}

Geometry *Geometry::createPlane(float width, float height) {
    Geometry *geometry = new Geometry();
    float hw = width * 0.5f;
    float hh = height * 0.5f;

    float data [] = {
    	-hw,  -hh, 0.0f,
		 hw,  -hh, 0.0f,
		hw, hh, 0.0f,
		 -hw, hh, 0.0f
    };

	float uvs[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
	};

	float normals [] = {
		0.0f,  0.0f, 1.0f,
		0.0f,  0.0f, 1.0f,
		0.0f,  0.0f, 1.0f,
		0.0f,  0.0f, 1.0f
	};



    unsigned int ebos[] = {
        0, 1, 2,
        2, 3, 0
    };
    geometry->mIndicesCount = 6;
    glGenVertexArrays(1, &geometry->mVao);
    glBindVertexArray(geometry->mVao);
    glGenBuffers(1, &geometry->mPosVbo);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glGenBuffers(1, &geometry->mUvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glGenBuffers(1, &geometry->mNormalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->mNormalVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glGenBuffers(1, &geometry->mEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ebos), ebos, GL_STATIC_DRAW);


    glBindVertexArray(0);
    return geometry;
}

Geometry * Geometry::createScreenPlane() {
	Geometry *geometry = new Geometry();
	float vertices [] = {
		-1.0f, 1.0f, 0.0f, // left up
		-1.0f, -1.0f, 0.0f, // left down
		1.0f, 1.0f, 0.0f, // right up
		1.0f, -1.0f, 0.0f// right down
	};

	float uvs [] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};
	unsigned int indices [] = {
		0, 1, 3,
		0, 3, 2
	};

	geometry->mIndicesCount = 6;
	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);
	glGenBuffers(1, &geometry->mPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	glGenBuffers(1, &geometry->mUvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	glGenBuffers(1, &geometry->mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

	return geometry;
}

Geometry * Geometry::createSphere(float radius) {
	Geometry* geometry = new Geometry();

	//目标：1 位置 2 uv 3 索引
	//1 主要变量声明
	std::vector<GLfloat> positions{};
	std::vector<GLfloat> uvs{};
	std::vector<GLfloat> normals{};
	std::vector<GLuint> indices{};

	//声明纬线与经线的数量
	int numLatLines = 60;//纬线
	int numLongLines = 60;//经线

	//2 通过两层循环（纬线在外，经线在内）->位置、uv、法线
	for (int i = 0; i <= numLatLines; i++) {
		for (int j = 0; j <= numLongLines; j++) {
			float phi = i * glm::pi<float>() / numLatLines;
			float theta = j * 2 * glm::pi<float>() / numLongLines;

			float y = radius * cos(phi);
			float x = radius * sin(phi) * cos(theta);
			float z = radius * sin(phi) * sin(theta);

			positions.push_back(x);
			positions.push_back(y);
			positions.push_back(z);

			float u = 1.0 - (float)j / (float)numLongLines;
			float v = 1.0 - (float)i / (float)numLatLines;

			uvs.push_back(u);
			uvs.push_back(v);

			//注意：法线方向没有问题，法线的长度不为1
			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);
		}
	}


	//3 通过两层循环（这里没有=号）->顶点索引
	for (int i = 0; i < numLatLines; i++) {
		for (int j = 0; j < numLongLines; j++) {
			int p1 = i * (numLongLines + 1) + j;
			int p2 = p1 + numLongLines + 1;
			int p3 = p1 + 1;
			int p4 = p2 + 1;

			indices.push_back(p1);
			indices.push_back(p2);
			indices.push_back(p3);

			indices.push_back(p3);
			indices.push_back(p2);
			indices.push_back(p4);
		}
	}


	//4 生成vbo与vao
	GLuint& posVbo = geometry->mPosVbo, uvVbo = geometry->mUvVbo, normalVbo = geometry->mNormalVbo;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), uvs.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &normalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &geometry->mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);

	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);

	glBindVertexArray(0);

	geometry->mIndicesCount = indices.size();


	return geometry;
}



