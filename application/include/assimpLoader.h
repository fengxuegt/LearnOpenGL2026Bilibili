//
// Created by fengxuegt on 2026/3/18.
//

#ifndef ASSIMPLOADER_H
#define ASSIMPLOADER_H
#include "object.h"
#include "core.h"
#include "mesh.h"
#include "texture.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
class AssimpLoader {
public:
    AssimpLoader();
    ~AssimpLoader();

    static Object* load(const std::string &path);
private:
    static void processNode(aiNode *ainode, Object *parent, const aiScene *scene, const std::string &rootPath);
    static Mesh* processMesh(aiMesh *mesh, const aiScene *scene, const std::string &rootPath);

	static Texture* processTexture(
		const aiMaterial* aimat,
		const aiTextureType& type,
		const aiScene* scene,
		const std::string& rootPath
	);

	static glm::mat4 getMat4f(aiMatrix4x4 value);
};



#endif //ASSIMPLOADER_H
