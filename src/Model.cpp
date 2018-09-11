#include "../Inc/Model.h"

Model::Model()
{
}

Model::~Model()
{
	for (Mesh* t : Meshes)
	{
		delete t;
	}

	for (Material* t : Materials)
	{
		delete t;
	}
}

bool Model::Load(std::string fileName, ID3D11Device* Device, ID3D11DeviceContext* DeviceContext)
{
	Assimp::Importer importer;


	unsigned int flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_GenNormals | aiProcess_ConvertToLeftHanded; //aiProcess_FlipWindingOrder
	std::string me = importer.GetErrorString();
	if (flipUVs)
	{
		flags |= aiProcess_FlipUVs;
	}

	const aiScene* scene = importer.ReadFile(fileName, flags);
	if (scene == nullptr)
	{
		return false;
	}

	if (scene->HasMaterials())
	{
		for (unsigned i = 0; i < scene->mNumMaterials; i++)
		{
			Materials.push_back(new Material(*this, scene->mMaterials[i], Device, DeviceContext));
		}
	}

	if (scene->HasMeshes())
	{
		NumberOfMeshes = scene->mNumMeshes;
		for (unsigned int i = 0; i < NumberOfMeshes; i++)
		{
			Meshes.push_back(new Mesh(*this, *(scene->mMeshes[i]), Device));

		}
	}
	return true;
}

const std::vector<Mesh*>& Model::GetMeshes() const
{
	return Meshes;
}

const std::vector<Material*>& Model::GetMaterials() const
{
	return Materials;
}

void Model::Draw(ID3D11DeviceContext* DeviceContext)
{
	for (Mesh* t : Meshes)
	{
		t->DrawMesh(DeviceContext);
	}
}