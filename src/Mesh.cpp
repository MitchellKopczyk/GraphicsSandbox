#include "../Inc/Mesh.h"

Mesh::Mesh(Model& model, aiMesh& mesh, ID3D11Device* Device)
{
	std::vector<DirectX::XMFLOAT3> Vertices;
	std::vector<DirectX::XMFLOAT3> Textures;
	std::vector<DirectX::XMFLOAT3> Normals;
	std::vector<DirectX::XMFLOAT3> Tangents;
	std::vector<DirectX::XMFLOAT3> BiNormals;
	std::vector<UINT> Indices;

	if (mesh.HasPositions())
	{
		Vertices.reserve(mesh.mNumVertices);
		for (unsigned int i = 0; i < mesh.mNumVertices; i++)
		{
			Vertices.push_back(DirectX::XMFLOAT3(reinterpret_cast<const float*>(&mesh.mVertices[i])));
		}
	}

	if (mesh.HasNormals())
	{
		Normals.reserve(mesh.mNumVertices);
		for (unsigned int i = 0; i < mesh.mNumVertices; i++)
		{
			Normals.push_back(DirectX::XMFLOAT3(reinterpret_cast<const float*>(&mesh.mNormals[i])));
		}
	}

	if (mesh.HasTangentsAndBitangents())
	{
		Tangents.reserve(mesh.mNumVertices);
		BiNormals.reserve(mesh.mNumVertices);
		for (unsigned i = 0; i < mesh.mNumVertices; i++)
		{
			Tangents.push_back(DirectX::XMFLOAT3(reinterpret_cast<const float*>(&mesh.mTangents[i])));
			BiNormals.push_back(DirectX::XMFLOAT3(reinterpret_cast<const float*>(&mesh.mBitangents[i])));
		}
	}

	if (mesh.HasTextureCoords(0))
	{
		TextureCoords = true;
		aiVector3D* aiTextureCoordinates = mesh.mTextureCoords[0];
		for (unsigned int i = 0; i < mesh.mNumVertices; i++)
		{
			Textures.push_back(DirectX::XMFLOAT3(reinterpret_cast<const float*>(&aiTextureCoordinates[i])));
		}
	}

	if (mesh.HasFaces())
	{
		FaceCount = mesh.mNumFaces;
		Indices.reserve(FaceCount);
		for (unsigned int i = 0; i < FaceCount; i++)
		{
			aiFace* face = &mesh.mFaces[i];
			for (unsigned int j = 0; j < face->mNumIndices; j++)
			{
				Indices.push_back(face->mIndices[j]);
			}
		}
	}

	std::vector<Vertex> TempVertexStorgae;
	TempVertexStorgae.reserve(mesh.mNumVertices);
	if (TextureCoords)
	{
		for (unsigned int i = 0; i < Vertices.size(); i++)
		{
			TempVertexStorgae.push_back(Vertex(Vertices.at(i).x, Vertices.at(i).y, Vertices.at(i).z,
				Textures.at(i).x, Textures.at(i).y, Normals.at(i).x, Normals.at(i).y, Normals.at(i).z));
		}
	}
	else
	{
		for (unsigned int i = 0; i < Vertices.size(); i++)
		{
			TempVertexStorgae.push_back(Vertex(Vertices.at(i).x, Vertices.at(i).y, Vertices.at(i).z, 0.0f, 0.0f, Normals.at(i).x,
				Normals.at(i).y, Normals.at(i).z));
		}
	}

	Material = model.Materials.at(mesh.mMaterialIndex);

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * TempVertexStorgae.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = &TempVertexStorgae.at(0);
	Microsoft::WRL::ComPtr<ID3D11Buffer> tempVertexBuffer;
	HR(Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, VertexBuffer.GetAddressOf()));

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * Indices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &Indices.at(0);
	Microsoft::WRL::ComPtr<ID3D11Buffer> tempIndexBuffer;
	HR(Device->CreateBuffer(&indexBufferDesc, &iinitData, IndexBuffer.GetAddressOf()));

	IndexDrawCount = Indices.size();
}

Mesh::~Mesh()
{
}

unsigned int Mesh::GetFaceCount() const
{
	return FaceCount;
}

void Mesh::DrawMesh(ID3D11DeviceContext* DeviceContext)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	std::map<TextureMapTypes, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>::iterator it = this->Material->TextureBuffers.find(TextureMapTypes::DiffuseMap);
	if (it != this->Material->TextureBuffers.end())
	{
		DeviceContext->PSSetShaderResources(0, 1, it->second.GetAddressOf());
	}

	DeviceContext->IASetVertexBuffers(0, 1, VertexBuffer.GetAddressOf(), &stride, &offset);
	DeviceContext->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	DeviceContext->DrawIndexed(IndexDrawCount, 0, 0);
}