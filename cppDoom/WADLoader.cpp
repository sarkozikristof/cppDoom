#include "WADLoader.h"
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

	m_WADDAta = new uint8_t[length];

	if (m_WADDAta == NULL) {
		cout << "Error: Failed alocate memory for WAD file of size" << length << endl;
	}

	m_WADFile.seekg(ifstream::beg);
	m_WADFile.read((char*)m_WADDAta, length);

	m_WADFile.close();

	cout << "Info: Loading completed." << endl;
	return true;
}


bool WADLoader::ReadDirectories() {
	return true;
}