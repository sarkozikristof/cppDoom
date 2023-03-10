#include "WADLoader.h"
#include "WADReader.h"
#include "Map.h"
#include "DataTypes.h"
#include <iostream>

using namespace std;

WADLoader::WADLoader(string sWADFilePath) : m_WADData(NULL), m_sWADFilePath(sWADFilePath)
{
}


WADLoader::~WADLoader() {
	delete[] m_WADData;
	m_WADData = NULL;
}


bool WADLoader::LoadWAD(){
	if (!OpenAndLoad()) {
		return false;
	}

	if (!ReadDirectories()) {
		return false;
	}

	return true;
}


bool WADLoader::OpenAndLoad() {
	cout << "Info: Loading WAD file: " << m_sWADFilePath << endl;

	m_WADFile.open(m_sWADFilePath, ifstream::binary);

	if (!m_WADFile.is_open()) {
		cout << "Error: Failed to open WAD file " << m_sWADFilePath << endl;
		return false;
	}

	m_WADFile.seekg(0, m_WADFile.end);
	size_t length = m_WADFile.tellg();

	if (m_WADData) {
		delete[] m_WADData;
		m_WADData = NULL;
	}

	m_WADData = new uint8_t[length];

	if (m_WADData == NULL) {
		cout << "Error: Failed to locate memory for WAD file" << length << endl;
		return false;
	}

	m_WADFile.seekg(ifstream::beg);
	m_WADFile.read((char*)m_WADData, length);

	m_WADFile.close();

	cout << "Info: Loading WAD file completed" << endl;

	return true;
}

bool WADLoader::LoadMapData(Map& map) {
	if (!ReadMapVertex(map)) {
		cout << "Error: Failed loading map vertex" << map.GetName() << endl;
		return false;
	}
	if (!ReadMapLinedef(map)) {
		cout << "Error: Failed loading map linedef" << map.GetName() << endl;
		return false;
	}

	return true;
}

bool WADLoader::ReadDirectories() {
	Header header;
	Directory directory;

	m_Reader.ReadHeaderData(m_WADData, 0, header);

	cout << header.WADType << endl;
	cout << header.DirectoryCount << endl;
	cout << header.DirectoryOffset << endl;
	cout << endl << endl;

	for (unsigned int i = 0; i < header.DirectoryCount; ++i) {
		m_Reader.ReadDirectoryData(m_WADData, header.DirectoryOffset + (i * 16), directory);

		m_WADDirectories.push_back(directory);

		cout << directory.LumpOffset << endl;
		cout << directory.LumpSize << endl;
		cout << directory.LumpName << endl;
		cout << endl;
	}

	return true;
}

int WADLoader::FindMapIndex(Map& map) {
	for (int i = 0; i < m_WADDirectories.size(); ++i) {
		if (m_WADDirectories[i].LumpName == map.GetName()) {
			return i;
		}
	}

	return -1;
}

bool WADLoader::ReadMapVertex(Map& map) {
	int iMapIndex = FindMapIndex(map);

	if (iMapIndex == -1) {
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eVERTEXES;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "VERTEXES") != 0) {
		return false;
	}


	int iVertexSizeInBytes = sizeof(Vertex);
	int iVertexCount = m_WADDirectories[iMapIndex].LumpSize / iVertexSizeInBytes;


	Vertex vertex;
	for (int i = 0; i < iVertexCount; ++i) {
		m_Reader.ReadVertexData(m_WADData, m_WADDirectories[iMapIndex].LumpOffset + i * iVertexSizeInBytes, vertex);

		map.AddVertex(vertex);

		cout << vertex.XPosition << endl;
		cout << vertex.YPosition << endl;
		std::cout << std::endl;
	}

	return true;
}

bool WADLoader::ReadMapLinedef(Map& map) {
	int iMapIndex = FindMapIndex(map);

	if (iMapIndex == -1) {
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eLINEDEFS;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "LINEDEFS") != 0) {
		return false;
	}

	int iLinedefSizeInBytes = sizeof(Linedef);
	int iLinedefCount = m_WADDirectories[iMapIndex].LumpSize / iLinedefSizeInBytes;

	Linedef linedef;
	for (int i = 0; i < iLinedefCount; ++i) {
		m_Reader.ReadLinedefData(m_WADData, m_WADDirectories[iMapIndex].LumpOffset + i * iLinedefSizeInBytes, linedef);

		map.AddLinedef(linedef);

		cout << linedef.StartVertex << endl;
		cout << linedef.EndVertex << endl;
		cout << endl;
	}

	return true;
}
