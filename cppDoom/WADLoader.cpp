#include "WADLoader.h"
#include "WADReader.h"
#include <iostream>

using namespace std;

WADLoader::WADLoader(string sWADFilePath) : m_WADDAta(NULL), m_sWADFilePath(sWADFilePath)
{
}


WADLoader::~WADLoader() {
	delete[] m_WADDAta;
	m_WADDAta = NULL;
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

	if (m_WADDAta) {
		delete[] m_WADDAta;
		m_WADDAta = NULL;
	}

	m_WADDAta = new uint8_t[length];

	if (m_WADDAta == NULL) {
		cout << "Error: Failed to locate memory for WAD file" << length << endl;
		return false;
	}

	m_WADFile.seekg(ifstream::beg);
	m_WADFile.read((char*)m_WADDAta, length);

	m_WADFile.close();

	cout << "Info: Loading WAD file completed" << endl;

	return true;
}


bool WADLoader::ReadDirectories() {
	WADReader reader;
	Header header;
	Directory directory;

	reader.ReadHeaderData(m_WADDAta, 0, header);

	cout << header.WADType << endl;
	cout << header.DirectoryCount << endl;
	cout << header.DirectoryOffset << endl;
	cout << endl << endl;

	for (int i = 0; i < header.DirectoryCount; ++i) {
		reader.ReadDirectoryData(m_WADDAta, header.DirectoryOffset + (i * 16), directory);

		m_WADDirectories.push_back(directory);

		cout << directory.LumpOffset << endl;
		cout << directory.LumpSize << endl;
		cout << directory.LumpName << endl;
		cout << endl;
	}

	return true;
}