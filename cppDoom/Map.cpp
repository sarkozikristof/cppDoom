#include "Map.h"

Map::Map(std::string sName) : m_sName(sName) {}

Map::~Map(){}

void Map::AddVertex(Vertex& v) {
	m_Vertexes.push_back(v);
}

void Map::AddLinedef(Linedef& l) {
	m_Linedef.push_back(l);
}

std::string Map::GetName() {
	return m_sName;
}