#include "pch.h"
#include "TStage.h"
static int mysizep[5][2] = { {0,0},{1,1},{2,1},{1,2},{2,2} };
string  TStage::getMapBString()
{
	static string st2;st2.resize(20);//  = "00000000000000000000";
	string res = st2;
	for (int k = 0;k < 10;k++) {
		TRole& rl = roles[k];
		int hw[2] = { mysizep[rl.type][0],mysizep[rl.type][1] };
		for (int i = 0;i < hw[0];i++)
			for (int j = 0;j < hw[1];j++) {
				int J = rl.l + i, I = rl.c + j;
				res[I + J * 4] = rl.type;
			}
	}
	return res;
}
void TStage::initBlank() {
	string  brd = getMapBString();
	int id = 10;
	for (int i = 0;i < 20;i++) {
		if ( brd[i] == 0) {
			int l = i / N, c = i % N;
			roles[id].l = l;roles[id].c =c;
			roles[id].id = id, roles[id].type = 1;
			id++;
			if (id == 12) break;
		}
	}
}
void  TGame::fromRole2Stage(vector<TRole> &rols, TStage& stg)
{
	for (int i = 0;i < 10;i++) {
		TRole &tr= rols[i];
		stg.roles[tr.id] = tr;
	}
	stg.initBlank();
	this->m_stages.push_back(stg);
	rols.clear();
}
bool mylog(const char* logname, const char* str)
{
	FILE* pfile;
	//char pbuff[200];
	//sprintf(pbuff, "%s;\n", str);
	CString strx = str;
	strx += "\r\n";
	 errno_t t = fopen_s(&pfile,logname, "wt");
	if (pfile)
	{
		fputs(strx, pfile);
		fclose(pfile);
		pfile = NULL;
		return true;
	}
	return false;
};
int TGame::WriteMapFile(CString outfilename) {
	CString str;
	TAutoSolver sol;
	vector<TQZ> Qzs;
	for (TStage st : m_stages) {
		CString temp = st.name.c_str();
		temp + "\r\n";
		for (int vi = 0; vi < 10; vi++)
		{
			TRole& rl = st.roles[vi];
			//TQZ  mqz = TQZ(TGPoint(rl.l,rl.c),rl.id,rl.type);// st->m_ch[vi];
			TQZ  mqz = TQZ::fromRole(rl);
			Qzs.push_back(mqz);
		}
		temp += sol.genstrMap(Qzs).c_str();
		temp + "\r\n";
		str += temp;
	}

	return mylog(outfilename, str);

}
int TGame::ReadFromFile(CString filename) {
	CString LineString;
	char pLine[255];
	FILE* fInfo=NULL;
	strcpy_s(pLine,250, (LPCSTR)filename);
	errno_t t = fopen_s(&fInfo,pLine, "rt");
	if (fInfo == NULL) return 1;
	pLine[0] = 0;
	TStage stg;
	vector<TRole> rols;
	while (!feof(fInfo))
	{
		fgets(pLine, 250, fInfo);
		LineString = pLine;
		LineString.TrimLeft();
		LineString.TrimRight();
		if (LineString.GetLength()==0 || LineString.Find("#") >= 0)  continue;
		if (LineString.Find("M") >= 0) {
			if (rols.size() >=10&& rols.size()<12){
			   fromRole2Stage(rols, stg);
			}
			stg.name = LineString;
			 
		}
		else {
			TRole rl;
			sscanf_s(LineString, "%d %d %d %d", &rl.id, &rl.l, &rl.c, &rl.type);
			rols.push_back(rl);
			if (rols.size() == 12) {
				fromRole2Stage(rols, stg);
			}
		}
	}
	if (rols.size() >= 10 && rols.size() < 12) {
		fromRole2Stage(rols, stg);
	}
	fclose(fInfo);
	return 0;
}