// QZ.h: interface for the QZ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QZ_H__9CDF6E05_28F5_4EB7_9230_58C6B4D1FFC5__INCLUDED_)
#define AFX_QZ_H__9CDF6E05_28F5_4EB7_9230_58C6B4D1FFC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include<unordered_set>
#include<queue>
#include<sstream>
using namespace std; 
struct TGPoint{
	int l;
	int c;
	TGPoint(int _l, int _c);

};
struct TQZShape{
	TGPoint typep= TGPoint(1, 1);
	int type;
    TQZShape(int _type);
	//TQZShape() {};
	 
};
struct TRole;
struct TQZ  
{

public:
	static void initidshapes();
	static void setType(int _type, TQZ&qz);
	TGPoint p=TGPoint(0,0);
	int id;
	TGPoint typep = TGPoint(1, 1);
	int type;
	string name;
	TQZ();
	TQZ(TGPoint _p,int _id);
	TQZ(TGPoint _p, int _id,int _type);
	virtual ~TQZ();
	static TQZ fromRole(TRole& rl);

};
const int M = 5, N = 4;
const int caocao_qzIdx = 1;

string print(int Map[M][N]);
string print(vector<TQZ>& QZs);
string  print(string& s);
enum TDir{QZLEFT=0,QZUP=1,QZRIGHT=2,QZDOWN=3};
struct TBoardMAP {
	//int Map[M][N]={{2,4,4,2},{2,4,4,2},{2,3,3,2},{2,1,1,2},{1,0,0,1}};
	//{"0张飞2*1","1曹操2*2","2马超2*1","3黄忠2*1","4关羽1*2","5赵云2*1","兵","兵","兵","兵" };    
	//0为空，1为1*1的兵，2为2*1的武将，3为1*2的武将，4为2*2的曹操
	static string st1; ///= "0000;0000;0000;0000;0000";
	string strMap = "24422442233221121001";
	int d = 0;
	vector<TQZ> QZs;
	TBoardMAP();
	TBoardMAP(string& s, vector<TQZ>& _QZs, int _d = 0);
	static string getMapString(vector<TQZ>& qzs);
	static string  getMapBString(vector<TQZ>& qzs);

	//0为左，1为上，2为右，3为下 
	bool ifmove(int QZ_idx, int dir);
	void move(int QZ_idx, int dir);
	string move2string(int QZ_idx, int dir);
	string move2stringx(int QZ_idx, int dir);
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
	string genString(int _Map[M][N]);
	void genMap(string& s);
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
	bool ifEnd();
};
struct Move {
	int qzIdx=0, dir=0;
	string lastStrMap;
	vector<TQZ> lastQZs;
};
struct  TAutoSolver {
	map<string, Move> path;
	string mirror(string& s);
	//0为左，1为上，2为右，3为下 
	//static string DIRS[] = { "左","上","右","下 ","" };
	string genMoveStr(Move& mv);
	string genResStr(vector<TQZ>& QZs);
	void writeRes(vector<Move>& resPath);
	string bfs();
	int main();
	int solve(int Map[M][N]);
	int solveNew(vector<TQZ>& QZs);
	string genstrMap(vector<TQZ>& qzs);
	stringstream cout2;
	vector<Move> m_resPath;
};
#endif // !defined(AFX_QZ_H__9CDF6E05_28F5_4EB7_9230_58C6B4D1FFC5__INCLUDED_)
