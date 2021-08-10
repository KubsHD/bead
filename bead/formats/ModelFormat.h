#pragma once

#include "../utils/BinaryIO.h"

using namespace bead;

enum TextureType {
	Diffuse = 0x01,
	Normal = 0x02,
	Specular = 0x03,
	Roughness = 0x04,
	Occlusion = 0x05,
	Mask = 0x06
};

struct TextureData {
	std::string magic = "TEX";
	TextureType type;
	std::vector<char> data;

	void Write(std::ofstream& bin)
	{
		IO::WriteString(bin, magic);
		IO::WriteInt(bin,int(type));
		IO::WriteVector(bin, data);
	}

	void Read(std::ifstream& bin)
	{
		magic = IO::ReadString(bin);
		type = (TextureType)IO::ReadInt(bin);
		data = IO::ReadVector<char>(bin);
	}
};

struct VertexData
{
	struct {
		float x;
		float y;
		float z;
	} position;

	struct {
		float u;
		float v;
	} uv;

	struct {
		float x;
		float y;
		float z;
	} normal;
};

struct MeshData
{
	std::string meshName;

	uint64_t vertex_count;
	uint64_t index_count;

	std::vector<uint32_t> indices;
	std::vector<VertexData> vertices;

	uint64_t tex_count;

	std::vector<TextureData> textures;

	void Write(std::ofstream& bin)
	{

		IO::WriteString(bin, meshName);

		IO::WriteInt(bin, vertex_count);
		IO::WriteInt(bin, index_count);


		//IO::WriteVector(bin, materialData.albedoMap);
		//IO::WriteVector(bin, materialData.normalMap);
		//IO::WriteVector(bin, materialData.metallicMap);
		//IO::WriteVector(bin, materialData.roughnessMap);

		IO::WriteVector<VertexData>(bin, vertices);
		IO::WriteVector<uint32_t>(bin, indices);

		IO::WriteInt(bin, tex_count);
		for (int i = 0; i < tex_count; i++)
		{
			textures[i].Write(bin);
		}
	}

	void Read(std::ifstream& bin)
	{
		meshName = IO::ReadString(bin);

		vertex_count = IO::ReadInt(bin);
		index_count = IO::ReadInt(bin);

		//materialData.albedoMap = IO::ReadVector<char>(bin);
		//materialData.normalMap = IO::ReadVector<char>(bin);
		//materialData.metallicMap = IO::ReadVector<char>(bin);
		//materialData.roughnessMap = IO::ReadVector<char>(bin);

		vertices = IO::ReadVector<VertexData>(bin);
		indices = IO::ReadVector<uint32_t>(bin);

		tex_count = IO::ReadInt(bin);

		textures.resize(tex_count);

		for (int i = 0; i < tex_count; i++)
		{
			textures[i].Read(bin);
		}
	}
};

struct ModelData
{
	std::string SIGNATURE = "SMDL";
	uint32_t VERSION = 1;

	std::string name;

	uint32_t meshCount;
	std::vector<MeshData> meshes;
};