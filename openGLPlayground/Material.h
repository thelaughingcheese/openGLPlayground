#ifndef MATERIAL
#define MATERIAL

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <unordered_map>

class Material{
private:
protected:
	static GLuint programID;
public:
	static void initMaterial();
	virtual void loadMaterialData(std::string& data) = 0;
	virtual void loadUniforms(glm::mat4& mvp) = 0;
};

class MaterialRecord{
public:
	virtual void init() = 0;
	virtual void unload() = 0;
	virtual Material* create() = 0;
};

class MaterialDictionary{
public:
	static std::unordered_map<std::string,MaterialRecord*>* getMaterialDictionary(){
		static std::unordered_map<std::string,MaterialRecord*> MaterialDictionary;
		return &MaterialDictionary;
	}
	static void registerInitializer(std::string name,MaterialRecord* initializer){
		(*MaterialDictionary::getMaterialDictionary())[name] = initializer;
	}
	static void initMaterials(){
		std::unordered_map<std::string,MaterialRecord*>* dict = getMaterialDictionary();
		std::unordered_map<std::string,MaterialRecord*>::iterator it = dict->begin();
		for(; it != dict->end(); ++it){
			it->second->init();
		}
	}
	static void unloadMaterials(){
		std::unordered_map<std::string,MaterialRecord*>* dict = getMaterialDictionary();
		std::unordered_map<std::string,MaterialRecord*>::iterator it = dict->begin();
		for(; it != dict->end(); ++it){
			it->second->unload();
		}
	}
};

template<class T>
class MaterialCreator: public MaterialRecord{
public:
	MaterialCreator(const char* name){
		MaterialDictionary::registerInitializer(name,this);
	}

	void init(){
		T::initMaterial();
	}

	void unload(){
		T::unloadMaterial();
	}

	Material* create(){
		return new T;
	}
};

#define REGISTER_MATERIAL(className) \
	static const MaterialCreator<className> materialInitializer(#className);

#endif