//
// Created by fengxuegt on 2026/3/6.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "core.h"

class Texture {
public:
	static Texture* createTexture(const std::string& path, unsigned int unit);
	static Texture* createTextureFromMemory(
		const std::string& path, 
		unsigned int unit,
		unsigned char* dataIn,
		uint32_t widthIn,
		uint32_t heightIn
	);

public:
    Texture(const std::string &path, int unitID);
	Texture(unsigned int unit,
		unsigned char* dataIn,
		uint32_t widthIn,
		uint32_t heightIn);
    ~Texture();

public:
    void Bind();
	int getWidth();
	int getHeight();

private:
    GLuint mTextureID;
    GLuint mUnitID;
	int mWidth{0};
	int mHeight{0};
	static std::map<std::string, Texture*> mTextureCache;
	

};




#endif //TEXTURE_H
