#pragma once

#include "QZ.h"
struct TRole {
	int l;
	int c;
	int id;
	int type;
};
struct TStage
{
	string name;
	TRole roles[12];
	void initBlank();
	string  getMapBString();
};

struct TGame {
	vector<TStage>  m_stages;
	void fromRole2Stage(vector<TRole>& rols, TStage& stg);
	int ReadFromFile(CString filename);
	int WriteMapFile(CString outfilename);
};