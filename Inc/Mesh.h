#pragma once
#include "Model.h"
#include "Material.h"
#include "ModelDependencies.h"

class Mesh
{
	friend class Model;
public:
	~Mesh();
	unsigned int GetFaceCount() const;

	void DrawMesh(ID3D11DeviceContext*);

private:
	Mesh(Model&, aiMesh&, ID3D11Device*);
	Material* Material;

	Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer;
	void BuildBuffers(ID3D11Device*, std::vector<Vertex>&, std::vector<UINT>&);

	UINT IndexDrawCount;
	bool TextureCoords = false;
	unsigned int FaceCount;
};