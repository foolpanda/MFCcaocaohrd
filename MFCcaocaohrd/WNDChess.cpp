// WNDChess.cpp : implementation file
//

#include "pch.h"
#include "MFCcaocaohrd.h"
#include "WNDChess.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WNDChess

WNDChess::WNDChess()
{
}

WNDChess::~WNDChess()
{
}


BEGIN_MESSAGE_MAP(WNDChess, CButton)
	//{{AFX_MSG_MAP(WNDChess)
//	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WNDChess message handlers

void WNDChess::Set(int x, int y, int t)
{
	this->posX = x;
	this->posY = y;
	this->type = t;
}

CRect WNDChess::GetRect()
{   //0 空   1 1*2         2 2*1           3 1*1           4 2*2
	//0为空，1为1 * 1的兵，2为2 * 1的武将，3为1 * 2的武将，4为2 * 2的曹操
	//1: 3   2:2    3:1    4:4
	const int  wu = 80, hu = 80;
	int i = 48, yt = 60;
	switch(this->type)
	{
	case 2:
		this->recX1 = this->posX*wu +i;
		this->recY1 = this->posY*hu + yt;
		this->recX2 = this->recX1 + wu;
		this->recY2 = this->recY1 + 2*hu ;
		break;
	case 3:
		this->recX1 = this->posX*wu +i;
		this->recY1 = this->posY*hu + yt;
		this->recX2 = this->recX1 + 2*wu ;
		this->recY2 = this->recY1 + hu ;
		break;
	case 1:
		this->recX1 = this->posX*wu +i;
		this->recY1 = this->posY*hu + yt;
		this->recX2 = this->recX1 + wu;
		this->recY2 = this->recY1 + hu;
		break;
	case 4:
		this->recX1 = this->posX*80 +i;
		this->recY1 = this->posY*80 + yt;
		this->recX2 = this->recX1 + 2*wu;
		this->recY2 = this->recY1 + 2*hu;
		break;
	}
	return CRect(this->recX1,this->recY1,this->recX2,this->recY2);
}

bool WNDChess::CanUp()
{
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	int dir = TDir::QZUP;
	bool bres = app->cb.ifmove(this->NO, dir);
	return bres;

}

bool WNDChess::CanDown()
{
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	int dir = TDir::QZDOWN;
	bool bres=app->cb.ifmove(this->NO,dir );
	return bres;

}

bool WNDChess::CanLeft()
{
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	int dir = TDir::QZLEFT;
	bool bres = app->cb.ifmove(this->NO, dir);
	return bres;

}

bool WNDChess::CanRight()
{
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	int dir = TDir::QZRIGHT;
	bool bres = app->cb.ifmove(this->NO, dir);
	return bres;

}

void WNDChess::Up()
{
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	switch(this->type)
	{
	case 2:
		if(this->posX == app->ch[10].posX && this->posY-1 == app->ch[10].posY)
		{
			this->posY -= 1;
			app->ch[10].posY += 2;
		}
		else
		{
			this->posY -= 1;
			app->ch[11].posY += 2;
		}
		break;
	case 3:
		this->posY -= 1;
		app->ch[10].posY += 1;
		app->ch[11].posY += 1;
		break;
	case 1:
		if(this->posX == app->ch[10].posX && this->posY-1 == app->ch[10].posY)
		{
			this->posY -= 1;
			app->ch[10].posY += 1;
		}
		else
		{
			this->posY -= 1;
			app->ch[11].posY += 1;
		}
		break;
	case 4:
		this->posY -= 1;
		app->ch[10].posY += 2;
		app->ch[11].posY += 2;
		break;
	}
}
//连续两次马超下 之后 出现退出问题
void WNDChess::Down()
{
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	switch(this->type)
	{
	case 2:
		if(this->posX == app->ch[10].posX && this->posY+2 == app->ch[10].posY)
		{
			this->posY += 1;
			app->ch[10].posY -= 2;
		}
		else
		{
			this->posY += 1;
			app->ch[11].posY -= 2;
		}
		break;
	case 3:
		this->posY += 1;
		app->ch[10].posY -= 1;
		app->ch[11].posY -= 1;
		break;
	case 1:
		if(this->posX == app->ch[10].posX && this->posY+1 == app->ch[10].posY)
		{
			this->posY += 1;
			app->ch[10].posY -= 1;
		}
		else
		{
			this->posY += 1;
			app->ch[11].posY -= 1;
		}
		break;
	case 4:
		this->posY += 1;
		app->ch[10].posY -= 2;
		app->ch[11].posY -= 2;
		break;
	}
	 
}

void WNDChess::Left()
{
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	switch(this->type)
	{
	case 3:
		this->posX -= 1;
		app->ch[10].posX += 1;
		app->ch[11].posX += 1;
		break;
	case 2:
		if(this->posY == app->ch[10].posY && this->posX-1 == app->ch[10].posX)
		{
			this->posX -= 1;
			app->ch[10].posX += 2;
		}
		else
		{
			this->posX -= 1;
			app->ch[11].posX += 2;
		}
		break;
	case 1:
		if(this->posY == app->ch[10].posY && this->posX-1 == app->ch[10].posX)
		{
			this->posX -= 1;
			app->ch[10].posX += 1;
		}
		else
		{
			this->posX -= 1;
			app->ch[11].posX += 1;
		}
		break;
	case 4:
		this->posX -= 1;
		app->ch[10].posX += 2;
		app->ch[11].posX += 2;
		break;
	}
}

void WNDChess::Right()
{
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	switch(this->type)
	{
	case 3:
		this->posX += 1;
		app->ch[10].posX -= 1;
		app->ch[11].posX -= 1;
		break;
	case 2:
		if(this->posY == app->ch[10].posY && this->posX+2 == app->ch[10].posX)
		{
			this->posX += 1;
			app->ch[10].posX -= 2;
		}
		else
		{
			this->posX += 1;
			app->ch[11].posX -= 2;
		}
		break;
	case 1:
		if(this->posY == app->ch[10].posY && this->posX+1 == app->ch[10].posX)
		{
			this->posX += 1;
			app->ch[10].posX -= 1;
		}
		else
		{
			this->posX += 1;
			app->ch[11].posX -= 1;
		}
		break;
	case 4:
		this->posX += 1;
		app->ch[10].posX -= 2;
		app->ch[11].posX -= 2;
		break;
	}
}
 /* 
void WNDChess::OnClicked() 
{
	// TODO: Add your control notification handler code here
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	app->flag = false;
	int count = 0;
	count = this->CanUp() + this->CanDown() + this->CanLeft() + this->CanRight();
	if(count == 2 && app->dir.direction < 0)
	{
		switch(app->dir.direction)
		{
		case -1:
			if(this->CanUp())
			{
				this->Up();
				app->cb.Up(this->NO);////////////
				app->flag = true;
			}
			break;
		case -2:
			if(this->CanDown())
			{
				this->Down();
				app->cb.Down(this->NO);////////////
				app->flag = true;
			}
			break;
		case -3:
			if(this->CanLeft())
			{
				this->Left();
				app->cb.Left(this->NO);////////////
				app->flag = true;
			}
			break;
		case -4:
			if(this->CanRight())
			{
				this->Right();
				app->cb.Right(this->NO);////////////
				app->flag = true;
			}
			break;
		}
		app->dir.direction = 0;
	}
	else if(app->dir.direction%3 != 0)
	{
		if(!app->flag && this->CanUp())
		{
			this->Up();
			app->cb.Up(this->NO);////////////
			app->flag = true;
		}
		if(!app->flag && this->CanDown())
		{
			this->Down();
			app->cb.Down(this->NO);
			app->flag = true;
		}
		if(!app->flag && this->CanLeft())
		{
			this->Left();
			app->cb.Left(this->NO);
			app->flag = true;
		}
		if(!app->flag && this->CanRight())
		{
			this->Right();
			app->cb.Right(this->NO);
			app->flag = true;
		}
	}
	else if(app->dir.direction%3 == 0)
	{
		if(!app->flag && this->CanRight())
		{
			this->Right();
			app->cb.Right(this->NO);
			app->flag = true;
		}
		if(!app->flag && this->CanLeft())
		{
			this->Left();
			app->cb.Left(this->NO);
			app->flag = true;
		}
		if(!app->flag && this->CanDown())
		{
			this->Down();
			app->cb.Down(this->NO);
			app->flag = true;
		}
		if(!app->flag && this->CanUp())
		{
			this->Up();
			app->cb.Up(this->NO);
			app->flag = true;
		}
	}
	for(int i=0; i<10; i++)
	{
		if(this->NO == i)
		{
			app->ch[i].DestroyWindow();
			app->ch[i].Create(NULL,WS_CHILD | BS_OWNERDRAW |BS_PUSHBUTTON | WS_VISIBLE,
					app->ch[i].GetRect(),AfxGetMainWnd(),i);
			
			if(this->type == 1 || this->type == 4 || this->type == 2)
			{
				app->ch[0].LoadBitmaps(10*i+this->type);
			}
			else if(this->NO >= 6 && this->NO <=9)
				app->ch[i].LoadBitmaps(IDB_S);
			app->ch[i].RedrawWindow();
			app->ch[i].ShowWindow (SW_SHOW);
		}
	}

	app->dir.direction += 1;
}
 */

void WNDChess::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	lbdownpt=point;
	m_bdown = true;
	CButton::OnLButtonDown(nFlags, point);
}


void WNDChess::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	if (m_bdown) { 
		int 	dx = point.x - lbdownpt.x;
		int 	dy = point.y - lbdownpt.y;
		if (abs(dx) < 3 && abs(dy) < 3) {
		}
		else {
		//	moveself(dx, dy);
		 	int dir = 0;
			int qzid = NO;
			if (abs(dx) > abs(dy)) 	dir = dx < 0 ? TDir::QZLEFT : TDir::QZRIGHT;
			else  	dir = dy < 0 ? TDir::QZUP : TDir::QZDOWN;
			CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
			CWnd* pmaindlg = app->m_pMainWnd;
			pmaindlg->PostMessage(QZ_MOVE, qzid, dir);
		}
    }
	m_bdown = false;
	CButton::OnLButtonUp(nFlags, point);
	Invalidate(true);
}
void movepos(WNDChess *pa) {
	CRect ir = pa->GetRect();
	int cx = ir.Width(), cy = ir.Height();
	//::SetWindowPos(a.m_hWnd, NULL,ir.left,ir.top,cx, cy, SWP_NOSIZE);
	//a.ShowWindow(SW_SHOW);
	pa->SetWindowPos(NULL, ir.left, ir.top, cx, cy, SWP_NOSIZE);
	//a.RedrawWindow();
}
void  WNDChess::moveself(int dx,int dy){
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	app->flag = false;
	int count = 0;
	//count = this->CanUp() + this->CanDown() + this->CanLeft() + this->CanRight();
	if(abs(dx)>abs(dy)){
		if(dx<0){
			if(this->CanLeft())
			{
				this->Left();
				app->cb.move(this->NO, TDir::QZLEFT);////////////
				app->flag = true;
			}
		}else{
			if(this->CanRight())
			{
				this->Right();
				app->cb.move(this->NO, TDir::QZRIGHT);////////////
				app->flag = true;
			}
		}
	}else{
		if(dy<0){
			if(this->CanUp())
			{
				this->Up();
				app->cb.move(this->NO,TDir::QZUP);////////////
				app->flag = true;
			}
		}else{
			if(this->CanDown())
			{
				this->Down();
				app->cb.move(this->NO, TDir::QZDOWN);////////////
				app->flag = true;
			}
		}
	}
	movepos(this);

}
 
void WNDChess::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CBitmapButton::DrawItem(lpDrawItemStruct);
	
	CDC* pdc = CDC::FromHandle(lpDrawItemStruct->hDC);
	ASSERT(pdc != NULL);
	CRect rect = lpDrawItemStruct->rcItem;//空间选择
	 
	CPen pen;//边框颜色
	int pw = m_bdown ? 4 : 2;
	COLORREF color = m_bdown ? RGB(20, 20, 245) : RGB(153, 217, 234);
	pen.CreatePen(PS_SOLID, pw,color);
	CGdiObject *pold=pdc->SelectObject(&pen);
	CGdiObject* pold2 = pdc->SelectStockObject(NULL_BRUSH);
	pdc->Rectangle(rect);
	//pdc->MoveTo(rect.TopLeft());
	//pdc->LineTo(rect.BottomRight());
	if(this->NO>=6){
		CString str; str.Format("%d", NO);
		pdc->SetTextColor(RGB(50, 50, 245));
		pdc->SetBkMode(TRANSPARENT);
		pdc->DrawText(str,&CRect(60,50,80,80), DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
	}
	pdc->SelectObject(pold);
	pdc->SelectObject(pold2);
	//pen.DeleteObject();
//	pdc->Detach();
	//pdc->DeleteDC();

}

 