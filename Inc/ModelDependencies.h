#pragma once

//Local
#include "VertexLayout.h"
#include "Result.h"
//STL
#include <memory>
#include <string>
#include <vector>
#include <map>
//Assimp
#include "../Assimp/include/assimp/Importer.hpp"
#include "../Assimp/include/assimp/scene.h"
#include "../Assimp/include/assimp/postprocess.h"
#include "../Assimp/include/assimp/material.h"
//Microsoft
#include <Windows.h>
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <D3Dcompiler.h>
#pragma comment(lib, "D3DCompiler.lib")
#include "../DirectXTK/Inc/WICTextureLoader.h"

enum TextureMapTypes
{
	DiffuseMap,
	SpecularMap,
	AmbientMap
};

enum MaterialColors
{
	Diffuse,
	Specular,
	Ambient
};

enum MaterialScalars
{
	Opacity,
	Shininess
};