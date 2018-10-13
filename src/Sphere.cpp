#include "../Inc/Sphere.h"

Sphere::Sphere(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext)
{
	this->Device = Device;
	this->DeviceContext = DeviceContext;
}

Sphere::~Sphere()
{
}

void Sphere::Generate(double Parallels, double Meridians, double Radius)
{
	std::vector<Vertex> Vertices;
	std::vector<int> Indices;

	for (double i = 0; i <= Parallels; i++)
	{
		double theta = i * M_PI / Parallels;
		double sinTheta = sin(theta);
		double cosTheta = cos(theta);

		for (double j = 0; j <= Meridians; j++) 
		{
			double phi = j * 2 * M_PI / Meridians;
			double sinPhi = sin(phi);
			double cosPhi = cos(phi);

			Vertex vs;
			vs.Normal.x = cosPhi * sinTheta;
			vs.Normal.y = cosTheta;
			vs.Normal.z = sinPhi * sinTheta;
			vs.texCoord.x = 1 - (j / Meridians);
			vs.texCoord.y = 1 - (i / Parallels);
			vs.Position.x = Radius * vs.Normal.x;
			vs.Position.y = Radius * vs.Normal.y;
			vs.Position.z = Radius * vs.Normal.z;
			Vertices.push_back(vs);
		}

		for (int k = 0; k < Parallels; k++) 
		{
			for (int l = 0; l < Meridians; l++) 
			{
				int a = (k * (Meridians + 1)) + l;
				int b = a + Meridians + 1;

				Indices.push_back(a);
				Indices.push_back(b);
				Indices.push_back(a + 1);

				Indices.push_back(b);
				Indices.push_back(b + 1);
				Indices.push_back(a + 1);
			}
		}

		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(Vertex) * Vertices.size();
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData;
		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
		vertexBufferData.pSysMem = &Vertices.at(0);
		HR(Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, VertexBuffer.GetAddressOf()));


		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned int) * Indices.size();
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA iinitData;
		iinitData.pSysMem = &Indices.at(0);
		HR(Device->CreateBuffer(&indexBufferDesc, &iinitData, IndexBuffer.GetAddressOf()));
		IndiciesCount = Indices.size();
	}
}

void Sphere::Draw()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	DeviceContext->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	DeviceContext->IASetVertexBuffers(0, 1, VertexBuffer.GetAddressOf(), &stride, &offset);
	DeviceContext->DrawIndexed(IndiciesCount, 0, 0);
 }