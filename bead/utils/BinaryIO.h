#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>



namespace bead
{
	namespace IO
	{
		inline std::string removeSpaces(std::string s) {
			std::string tmp(s);
			tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
			return tmp;
		}

		inline std::vector<char> ReadAllBytes(std::string filename)
		{
			std::ifstream ifs(removeSpaces(filename), std::ios::binary | std::ios::ate);
			std::ifstream::pos_type pos = ifs.tellg();

			std::vector<char>  result(pos);

			ifs.seekg(0, std::ios::beg);
			ifs.read(&result[0], pos);

			return result;
		}

		inline bool Exists(std::string path)
		{
			auto val = std::filesystem::exists(std::filesystem::path(path));
			return val;
		}

		inline void WriteString(std::ofstream& bin, const std::string& value)
		{
			bin.write(value.data(), value.length() + 1);
		}

		inline void WriteString(std::fstream& bin, const std::string& value)
		{
			bin.write(value.data(), value.length() + 1);
		}

		inline void WriteShort(std::ofstream& bin, int16_t value)
		{
			bin.put(static_cast<uint8_t>(value & 0xff));
			bin.put(static_cast<uint8_t>((value >> 8) & 0xff));
		}

		inline void WriteByte(std::ofstream& bin, char value)
		{
			bin.write(&value, 1);
		}
		inline
		void WriteInt(std::ofstream& bin, int value)
		{
			bin.write((char*)&value, 4);
		}

		inline std::string ReadString(std::ifstream& bin)
		{
			char data[256];
			bin.read(data, 1);
			char* chr = data;
			while (*chr != '\0')
				bin.read(++chr, 1);
			return data;
		}

		inline std::string ReadString(std::fstream& bin)
		{
			char data[256];
			bin.read(data, 1);
			char* chr = data;
			while (*chr != '\0')
				bin.read(++chr, 1);
			return data;
		}

		inline int16_t ReadShort(std::ifstream& bin)
		{
			int16_t value;
			bin.read(reinterpret_cast<char*>(&value), 2);
			return value;
		}

		inline int ReadInt(std::ifstream& bin)
		{
			int value;
			bin.read(reinterpret_cast<char*>(&value), 4);
			return value;
		}

		template <class T>
		inline void WriteVector(std::ofstream& bin, const std::vector<T>& value)
		{
			WriteInt(bin, (int)value.size());
			//std::cout << value.size() * sizeof(T) << std::endl;
			bin.write((char*)&value[0], value.size() * sizeof(T));
		}

		template <class T>
		inline std::vector<T> ReadVector(std::ifstream& bin)
		{
			auto size = ReadInt(bin);
			//std::cout << size << std::endl;
			std::vector<T> data;
			data.resize(size);
			bin.read((char*)&data[0], size * sizeof(T));

			return data;
		}
	}
}