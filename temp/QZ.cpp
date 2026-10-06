// QZ.cpp: implementation of the QZ class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "MFCcaocaohrd.h"
#include "QZ.h"
#include <sstream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
inline int e(TGPoint &p)
{
	return p.l * N + p.c;
}
inline int e(int i, int j)
{
	return i * N + j;
}
TGPoint::TGPoint(int _l,int _c):l(_l),c(_c){
	

}
string print(int Map[M][N])
{
	stringstream cout2;
	for (int i = 0;i < M;i++)
	{

		for (int j = 0;j < N;j++)
		{
			cout2 << Map[i][j] << " ";
		}
		cout2 << endl;
	}
	cout2 << endl;
	return cout2.str();
}
string print(vector<TQZ>& QZs)
{
	stringstream cout2;
	for (int i = 0;i < QZs.size();i++)
	{
		TQZ& tmp = QZs[i];
		cout2 << "i,j:" << tmp.p.l << "," << tmp.p.c << " m,n:" << tmp.typep.l << "," << tmp.typep.c << " " << tmp.type << endl;
	}
	return cout2.str();
}
string  print(string& s)
{
	stringstream cout2;
	for (int i = 0;i < M;i++)
	{
		for (int j = 0;j < N;j++)
		{
			cout2 << int(s[e(TGPoint(i, j))]) << " ";
		}
		cout2 << endl;
	}
	cout2 << endl;
	return cout2.str();
}
  //                      11 12    54     31 32  41 42  1 2   21 22  s
  
   char NAME[12][8] = {"ÕÅ·É","²Ü²Ù","Âí³¬","»ÆÖÒ","¹ØÓð","ÕÔÔÆ","±ø","±ø","±ø","±ø","",""};
const  int   ISHAPE[12] = { 2,     4,    2,     2,       3,   2,      1,   1,  1,  1,1,1 };
TQZShape::TQZShape(int _type){
	type=_type;
	//typep = TGPoint(1, 1);
	switch(type){
	case 1: typep= TGPoint(1,1); break;
	case 2: typep= TGPoint(2,1); break;
	case 3: typep= TGPoint(1,2); break;
	case 4: typep= TGPoint(2,2); break;
	}
}

map<int , TQZShape> qz_shapes;
TGPoint mshp[4] = { TGPoint(1, 1) ,TGPoint(2, 1) ,TGPoint(1, 2) ,TGPoint(2, 2) };
void TQZ::initidshapes() {
	//qz_shapes.clear();
	/* qz_shapes[1] = TQZShape(1, 1);
	qz_shapes[2]=TQZShape(2, 1);
	qz_shapes[3]=TQZShape(1, 2);
	qz_shapes[4]=TQZShape(2, 2);*/
	TGPoint shp[4] = { TGPoint(1, 1) ,TGPoint(2, 1) ,TGPoint(1, 2) ,TGPoint(2, 2) };
	for(int i=0;i<4;i++){
		mshp[i] = shp[i];
	}
	//string xNAME[12] = { "ÕÅ·É","²Ü²Ù","Âí³¬","»ÆÖÒ","¹ØÓð","ÕÔÔÆ","±ø","±ø","±ø","±ø","","" };
 

}

void  TQZ::setType(int _type, TQZ& qz) {
	qz.type = _type;
	if(_type>0 && _type<=4)
	  qz.typep = mshp[_type-1];
}
TQZ::TQZ():id(0),type(1) {
	//id = 0, type = 1;

}
TQZ::TQZ(TGPoint _p,int _id)
{
	id = _id;
	p = _p;
	type = ISHAPE[_id];
	if (type > 0 && type <= 4)
		typep = mshp[type - 1];
	name = NAME[id];
}
TQZ::TQZ(TGPoint _p, int _id, int _type) {
	id = _id;
	p = _p;
	type = _type;
	if (type > 0 && type <= 4)
		typep = mshp[type - 1];
	name = NAME[id];
}
TQZ TQZ::fromRole(TRole& rl) {
	TQZ  mqz = TQZ(TGPoint(rl.l, rl.c), rl.id, rl.type);
	return mqz;
}
TQZ::~TQZ()
{

}
/// <summary>
/// 
/// </summary>
/// ;
TBoardMAP::TBoardMAP()
{
	if (mshp[0].l == 0) 
	{
		TQZ::initidshapes();;
	}
	QZs.push_back(TQZ(TGPoint(0, 0), 0));
	QZs.push_back(TQZ(TGPoint(0, 1), 1));
	QZs.push_back(TQZ(TGPoint(0, 3), 2));
	QZs.push_back(TQZ(TGPoint(2, 0), 3));
	QZs.push_back(TQZ(TGPoint(2, 1), 4));
	QZs.push_back(TQZ(TGPoint(2, 3), 5));
	QZs.push_back(TQZ(TGPoint(3, 1), 6));
	QZs.push_back(TQZ(TGPoint(3, 2), 7));
	QZs.push_back(TQZ(TGPoint(4, 0), 8));
	QZs.push_back(TQZ(TGPoint(4, 3), 9));
}
TBoardMAP::TBoardMAP(string& s, vector<TQZ>& _QZs, int _d )
{
	strMap = s;
	QZs = _QZs;
	d = _d;
}


//0Îª×ó£¬1ÎªÉÏ£¬2ÎªÓÒ£¬3ÎªÏÂ 
bool TBoardMAP::ifmove(int QZ_idx, int dir)
{
	TQZ& temp = QZs[QZ_idx];
	int i = temp.p.l, j = temp.p.c, m = temp.typep.l, n = temp.typep.c;
	//cout<<"ifmove:"<<i<<" "<<j<<" "<<dir<<endl;
	if (dir == 0)
	{
		if (j > 0 && strMap[e(TGPoint(i, j - 1))] == 0)
		{
			if (temp.typep.l == 1 || strMap[e(TGPoint(i + 1, j - 1))] == 0)
				return true;
		}
	}
	else if (dir == 1)
	{
		if (i > 0 && strMap[e(TGPoint(i - 1, j))] == 0)
		{
			if (temp.typep.c == 1 || strMap[e(TGPoint(i - 1, j + 1))] == 0)
				return true;
		}
	}
	else if (dir == 2)
	{
		if (m == 1)
		{
			if (n == 1)
			{
				if (j + 1 < N && strMap[e(TGPoint(i, j + 1))] == 0)
					return true;
			}
			else
			{
				if (j + 2 < N && strMap[e(TGPoint(i, j + 2))] == 0)
					return true;
			}
		}
		else
		{
			if (n == 1)
			{
				if (j + 1 < N && strMap[e(TGPoint(i, j + 1))] == 0 && strMap[e(TGPoint(i + 1, j + 1))] == 0)
					return true;
			}
			else
			{
				if (j + 2 < N && strMap[e(TGPoint(i, j + 2))] == 0 && strMap[e(TGPoint(i + 1, j + 2))] == 0)
					return true;
			}
		}
	}
	else
	{
		if (m == 1)
		{
			if (n == 1)
			{
				if (i + 1 < M && strMap[e(TGPoint(i + 1, j))] == 0)
					return true;
			}
			else
			{
				if (i + 1 < M && strMap[e(TGPoint(i + 1, j))] == 0 && strMap[e(TGPoint(i + 1, j + 1))] == 0)
					return true;
			}
		}
		else
		{
			if (n == 1)
			{
				if (i + 2 < M && strMap[e(TGPoint(i + 2, j))] == 0)
					return true;
			}
			else
			{
				if (i + 2 < M && strMap[e(TGPoint(i + 2, j))] == 0 && strMap[e(TGPoint(i + 2, j + 1))] == 0)
					return true;
			}
		}
	}
	return false;
}
void TBoardMAP::move(int QZ_idx, int dir)
{
	TQZ& temp = QZs[QZ_idx];
	string& tmpMap = strMap;
	for (int i = 0;i < temp.typep.l;i++)
		for (int j = 0;j < temp.typep.c;j++)
		{
			int I = temp.p.l + i, J = temp.p.c + j;
			tmpMap[e(I,J)] = 0;
		}
	for (int i = 0;i < temp.typep.l;i++)
		for (int j = 0;j < temp.typep.c;j++)
		{
			int I = temp.p.l + i, J = temp.p.c + j;
			if (dir == 0)
			{
				tmpMap[e(I, J - 1)] = temp.type;

			}
			else if (dir == 1)
			{
				tmpMap[e(I - 1 ,J)] = temp.type;

			}
			else if (dir == 2)
			{
				tmpMap[e(I ,J + 1)] = temp.type;

			}
			else
			{
				tmpMap[e(I + 1, J)] = temp.type;
			}
		}
	if (dir == 0)
	{
		temp.p.c--;

	}
	else if (dir == 1)
	{
		temp.p.l--;

	}
	else if (dir == 2)
	{
		temp.p.c++;

	}
	else
	{
		temp.p.l++;
	}

}
string  TBoardMAP::move2stringx(int QZ_idx, int dir) {
	TQZ& temp = QZs[QZ_idx];
	string tmpMap = strMap;
	for (int i = 0;i < temp.typep.l;i++)
		for (int j = 0;j < temp.typep.c;j++)
		{
			int I = temp.p.l + i, J = temp.p.c + j;
			tmpMap[e(I, J)] = 0;
		}
	for (int i = 0;i < temp.typep.l;i++)
		for (int j = 0;j < temp.typep.c;j++)
		{
			int I = temp.p.l + i, J = temp.p.c + j;
			if (dir == 0)
			{
				tmpMap[e(I, J - 1)] = temp.type;

			}
			else if (dir == 1)
			{
				tmpMap[e(I - 1, J)] = temp.type;

			}
			else if (dir == 2)
			{
				tmpMap[e(I, J + 1)] = temp.type;

			}
			else
			{
				tmpMap[e(I + 1, J)] = temp.type;
			}
		}
	//cout<<"finish"<<endl;
	return tmpMap;
}
string TBoardMAP::move2string(int QZ_idx, int dir)
{
	TQZ& temp = QZs[QZ_idx];
	string tmpMap = strMap;
	for (int i = 0;i < temp.typep.l;i++)
		for (int j = 0;j < temp.typep.c;j++)
		{
			int I = temp.p.l + i, J = temp.p.c + j;
			tmpMap[e(I, J)] = 0;
		}
	for (int i = 0;i < temp.typep.l;i++)
		for (int j = 0;j < temp.typep.c;j++)
		{
			int I = temp.p.l + i, J = temp.p.c + j;
			if (dir == 0)
			{
				tmpMap[e(I, J - 1)] = temp.type;

			}
			else if (dir == 1)
			{
				tmpMap[e(I - 1, J)] = temp.type;

			}
			else if (dir == 2)
			{
				tmpMap[e(I, J + 1)] = temp.type;

			}
			else
			{
				tmpMap[e(I + 1, J)] = temp.type;
			}
		}
	//cout<<"finish"<<endl;
	return tmpMap;

}
//	string genString()
//	{
//		string s="";
//		for(int i=0;i<M;i++)
//		{
//			for(int j=0;j<N;j++)
//			{
//				s+=to_string(int(Map[i][j]));
//			}
//			s+=";";
//		}
//		return s;
//	}
string genString(int _Map[M][N])
{
	string s = "";
	for (int i = 0;i < M;i++)
	{
		for (int j = 0;j < N;j++)
		{
			s += int(_Map[i][j]);
		}
	}
	//cout<<"s finish"<<endl;
	return s;
}
void TBoardMAP::genMap(string& s)
{
	int Map[M][N] = { 0 };
	for (int i = 0;i < M;i++)
		for (int j = 0;j < N;j++)
		{
			int idx = i * N + j;
			Map[i][j] = s[idx];
		}
}
//	void genQZs()
//	{
//		int tmpMap[M][N];
//		memcpy(tmpMap,Map,sizeof(Map));
//		int I=0;
//		for(int i=0;i<M;i++)
//			for(int j=0;j<N;j++)
//			{
//				if(tmpMap[i][j]==2)
//				{
//					tmpMap[i+1][j]=-2;
//					QZs[I++].set(2,1,i,j);
//				}
//				else if(tmpMap[i][j]==4)
//				{
//					tmpMap[i][j+1]=-4;
//					tmpMap[i+1][j+1]=-4;
//					tmpMap[i+1][j]=-4;
//					QZs[I++].set(2,2,i,j);
//					caocao_qzIdx=I-1;
//				}
//				else if(tmpMap[i][j]==3)
//				{
//					tmpMap[i][j+1]=-3;
//					QZs[I++].set(1,2,i,j);
//				}
//				else if(tmpMap[i][j]==1)
//				{
//					QZs[I++].set(1,1,i,j);
//				}
//			}
//	}
bool TBoardMAP::ifEnd()
{
	TQZ& temp = QZs[caocao_qzIdx];
	if (temp.p.l == 3 && temp.p.c == 1)
		return true;
	return false;
}
string TBoardMAP::st1 = "0000;0000;0000;0000;0000";
string strinitMap = "2442;2442;2332;2112;1001";
string  TBoardMAP::getMapString(vector<TQZ>& qzs) 
{
	//static string st1 = "0000;0000;0000;0000;0000";
	string res = st1;
	for (TQZ qz : qzs) {
		int y = qz.p.l, x = qz.p.c;
		for(int i=0;i<qz.typep.l;i++)
			for (int j = 0;j < qz.typep.c;j++) {
				int J = y + i, I = x + j;
				res[I+ J*5] = '0' + qz.type;
			}
	}
	return res;
 }
string  TBoardMAP::getMapBString(vector<TQZ>& qzs)
{
	static string st2;st2.resize(20);//  = "00000000000000000000";
	string res = st2;
	for (TQZ qz : qzs) {
		int y = qz.p.l, x = qz.p.c;
		for (int i = 0;i < qz.typep.l;i++)
			for (int j = 0;j < qz.typep.c;j++) {
				int J = y + i, I = x + j;
				res[I + J*4 ] =   qz.type;
			}
	}
	return res;
}
TBoardMAP mymap;
string templateStrMap = "";
////
string TAutoSolver::mirror(string& s)
{
	string s1 = s;
	for (int i = 0;i < M;i++)
		for (int j = 0;j < N;j++)
		{
			s1[e(TGPoint(i, N - j - 1))] = s[e(TGPoint(i, j))];
		}
	return s1;
}
//0Îª×ó£¬1ÎªÉÏ£¬2ÎªÓÒ£¬3ÎªÏÂ 
static string DIRS[] = { "×ó","ÉÏ","ÓÒ","ÏÂ ","" };
string TAutoSolver::genMoveStr(Move& mv) {
	string nm = NAME[mv.qzIdx] + to_string(mv.qzIdx);
	string dr = DIRS[mv.dir];
	string pm = "  <^>v" + nm + "  " + dr;
	return pm;
}
string TAutoSolver::genResStr(vector<TQZ>& QZs)
{
	string s = templateStrMap;
	for (int I = 0;I < QZs.size();I++)
	{
		TQZ& q = QZs[I];
		int i = q.p.l, j = q.p.c;
		if (q.type == 1)
		{
			s.replace(i * (2 * N + 1) + 2 * j, 2, "±ø");
		}
		else if (q.type == 2)
		{
			s.replace(i * (2 * N + 1) + 2 * j, 2, q.name.substr(0, 2));
			s.replace((i + 1) * (2 * N + 1) + 2 * j, 2, q.name.substr(2, 2));
		}
		else if (q.type == 3)
		{
			s.replace(i * (2 * N + 1) + 2 * j, 2, q.name.substr(0, 2));
			s.replace(i * (2 * N + 1) + 2 * (j + 1), 2, q.name.substr(2, 2));
		}
		else
		{
			s.replace(i * (2 * N + 1) + 2 * j, 4, q.name);
			s.replace((i + 1) * (2 * N + 1) + 2 * j, 4, q.name);
		}
	}
	string s1 = " ", s2 = "¿Ú";
	int index = 0;
	while ((index = s.find(s1)) != string::npos) {    //for each location where Hello is found
		s.replace(index, s2.length(), s2); //remove and replace from that position
	}
	return s;
}
void TAutoSolver::writeRes(vector<Move>& resPath)
{
	ofstream wr;
	wr.open("hrd_out.txt", ios::app);
	for (int i = resPath.size() - 1;i >= 0;i--)
	{
		Move& m = resPath[i];
		for (int i = 0;i < M;i++)
		{
			for (int j = 0;j < N;j++)
			{

			}
			wr << endl;
		}
	}
}
string TAutoSolver::bfs()
{

	queue<TBoardMAP> q;
	q.push(mymap);
	string sr=TBoardMAP::getMapString(mymap.QZs);
	bool b = false;
	if (sr == strinitMap) {
		b = true;
	}
	unordered_set<string> visited;
	visited.insert(mymap.strMap);
	int D = 0;
	while (!q.empty())
	{
		TBoardMAP tmpNode = q.front();
		string& s0 = tmpNode.strMap;
		//print(s0);
		vector<TQZ>& QZs = tmpNode.QZs;
		//print(QZs);
		int d = tmpNode.d;
		q.pop();
		if (d > D)
		{
			D = d;
			//cout2 << d << " " << endl;
			// cout2<<print(s0);
			// cout2 << endl;
		}
		if (tmpNode.ifEnd())
		{
			return s0;
		}
		for (int i = 0;i < QZs.size();i++)
		{
			TQZ& temp = QZs[i];
			//cout<<"i="<<i<<endl;
			for (int dir = 0;dir < 4;dir++)
			{
				//cout<<"dir"<<dir<<endl;
				if (tmpNode.ifmove(i, dir))
				{
					//cout<<temp.i<<" "<<temp.j<<" "<<dir<<endl;
					//mymap.move(i,dir);
					string s1 = tmpNode.move2stringx(i, dir);
					//cout<<"next"<<endl;
					if (!visited.count(s1))
					{
						//cout<<"next0"<<endl;
						visited.insert(s1);
						//string sx2 = tmpNode.move2string(i, dir);
						visited.insert(mirror(s1));
						path[s1] = { i,dir,s0,QZs };
						TBoardMAP map1(s1, QZs, d + 1);
						TQZ& temp1 = map1.QZs[i];
						if (dir == 0)
						{
							temp1.p.c--;

						}
						else if (dir == 1)
						{
							temp1.p.l--;

						}
						else if (dir == 2)
						{
							temp1.p.c++;

						}
						else
						{
							temp1.p.l++;
						}
						if (map1.ifEnd())
						{
							return s1;
						}
						q.push(map1);
						//cout<<s1<<endl;
						//cout<<"next1"<<endl;
					}

				}
			}
		}
	}
	return templateStrMap;
}

int TAutoSolver::main() {
	cout2 << "huarongdao" << endl;
	TQZ::initidshapes();
	int Map[M][N] = { {2,4,4,2},{2,4,4,2},{2,3,3,2},{2,1,1,2},{1,0,0,1} };
	return solve(Map);
}
string TAutoSolver::genstrMap(vector<TQZ>& qzs) {
	stringstream cout3;
	templateStrMap = "";
	for (int i = 0;i < M;i++)
	{
		for (int j = 0;j < N;j++)
		{
			templateStrMap += "  ";
		}
		templateStrMap += "\n";
	}
	string sbrd = TBoardMAP::getMapBString(qzs);
	mymap.QZs = qzs;
	mymap.strMap = sbrd;
	cout3 << print(mymap.strMap);
	cout3 << genResStr(mymap.QZs) << endl;
	return cout3.str();
}
int TAutoSolver::solveNew(vector<TQZ>& qzs)
{
	cout2 << genstrMap(qzs);
	string s = bfs();

	cout2 << print(s);
	vector<Move> resPath;
	while (path.count(s))
	{
		resPath.push_back(path[s]);
		s = path[s].lastStrMap;
	}
	size_t len = resPath.size() - 1;
	m_resPath.clear();
	for (int i = len;i >= 0;i--)
	{
		cout2 << genResStr(resPath[i].lastQZs) << endl;
		cout2 << "  " << len - i << genMoveStr(resPath[i]) << endl;
		m_resPath.push_back(resPath[i]);
		 
	}
		return 0;
}
int TAutoSolver::solve(int Map[M][N]) {
	for (int i = 0;i < M;i++)
	{
		for (int j = 0;j < N;j++)
		{
			mymap.strMap[e(TGPoint(i, j))] = Map[i][j];
			templateStrMap += "  ";
		}
		templateStrMap += "\n";
	}
	//string s1="2442;2442;2332;2112;0110";
	//mymap.strMap=s1;
	//mymap.genMap(mymap.strMap);
	//mymap.genQZs();
	cout2 << print(mymap.strMap);
	cout2 << endl;
	cout2 << templateStrMap;
	cout2 << genResStr(mymap.QZs) << endl;
	//	for(int I=0;I<2;I++)
	//	for(int i=0;i<mymap.QZs.size();i++)
	//	{
	//		QZ &temp=mymap.QZs[i];
	//		for(int dir=0;dir<4;dir++)
	//		{
	//		
	//		if(mymap.ifmove(i,dir))
	//		{
	//		cout<<temp.i<<" "<<temp.j<<" "<<dir<<endl;
	//			mymap.move(i,dir);
	//			
	//			print(mymap.strMap);
	//			print(mymap.QZs);
	//			cout<<endl;
	//		}
	//	}
	//	}
	 
	string s = bfs();
	 
	cout2<<print(s);
	vector<Move> resPath;
	while (path.count(s))
	{
		resPath.push_back(path[s]);
		s = path[s].lastStrMap;
	}
	size_t len = resPath.size() - 1;
	m_resPath.clear();
	for (int i = len;i >= 0;i--)
	{
		cout2 << genResStr(resPath[i].lastQZs) << endl;
		cout2 << "  " << len - i << genMoveStr(resPath[i]) << endl;
		m_resPath.push_back( resPath[i]);

	}
	//m_resPath = resPath;
	return 0;
}
