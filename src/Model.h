#pragma once
#include "Mesh.h"
#include "Material.h"
#include "ModelDependencies.h"

class Model
{
	friend class Mesh;
public:
	Model();
	~Model();
	bool Load(std::string, ID3D11Device*, ID3D11DeviceContext*);
	bool flipUVs = false;
	const std::vector<Mesh*>& GetMeshes() const;
	const std::vector<Material*>& GetMaterials() const;
	void Draw(ID3D11DeviceContext*);
private:
	unsigned int NumberOfMeshes;
	std::vector<Mesh*> Meshes;
	std::vector<Material*> Materials;
};