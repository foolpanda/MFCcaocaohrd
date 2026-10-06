// MFCChess.cpp : implementation file
//

#include "pch.h"
#include "MFCcaocaohrd.h"
#include "MFCChess.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MFCChess

MFCChess::MFCChess()
{
}

MFCChess::~MFCChess()
{
}


BEGIN_MESSAGE_MAP(MFCChess, CButton)
	//{{AFX_MSG_MAP(MFCChess)
//	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MFCChess message handlers

void MFCChess::Set(int x, int y, int t)
{
	this->posX = x;
	this->posY = y;
	this->type = t;
}

CRect MFCChess::GetRect()
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

bool MFCChess::CanUp()
{
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	int dir = TDir::QZUP;
	bool bres = app->cb.ifmove(this->NO, dir);
	return bres;
	switch(this->type)
	{
	case 3:
		return ((this->posX == app->ch[10].posX && this->posY-1 == app->ch[10].posY)
			|| (this->posX == app->ch[11].posX && this->posY-1 == app->ch[11].posY));
		break;
	case 2:
		return ( (abs(app->ch[10].posX - app->ch[11].posX) == 1 
			&& app->ch[10].posY == app->ch[11].posY)
			&& this->posY-1 == app->ch[10].posY
			&& this->posX*2+1 == app->ch[10].posX+app->ch[11].posX );
		break;
	case 1:
		return ( (this->posX == app->ch[10].posX && this->posY-1 == app->ch[10].posY)
			|| (this->posX == app->ch[11].posX && this->posY-1 == app->ch[11].posY));
		break;
	case 4:
		return ( (abs(app->ch[10].posX - app->ch[11].posX) == 1 
			&& app->ch[10].posY == app->ch[11].posY)
			&& this->posY-1 == app->ch[10].posY
			&& this->posX*2+1 == app->ch[10].posX+app->ch[11].posX );
		break;
	}
	return false;
}

bool MFCChess::CanDown()
{
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	int dir = TDir::QZDOWN;
	bool bres=app->cb.ifmove(this->NO,dir );
	return bres;
	switch(this->type)
	{
	case 3:
		return ((this->posX == app->ch[10].posX && this->posY+2 == app->ch[10].posY)
			|| (this->posX == app->ch[11].posX && this->posY+2 == app->ch[11].posY));
		break;
	case 2:
		return ( (abs(app->ch[10].posX - app->ch[11].posX) == 1 
			&& app->ch[10].posY == app->ch[11].posY)
			&& this->posY+1 == app->ch[10].posY
			&& this->posX*2+1 == app->ch[10].posX+app->ch[11].posX );
		break;
	case 1:
		return ( (this->posX == app->ch[10].posX && this->posY+1 == app->ch[10].posY)
			|| (this->posX == app->ch[11].posX && this->posY+1 == app->ch[11].posY));
		break;
	case 4:
		return ( (abs(app->ch[10].posX - app->ch[11].posX) == 1 
			&& app->ch[10].posY == app->ch[11].posY)
			&& this->posY+2 == app->ch[10].posY
			&& this->posX*2+1 == app->ch[10].posX+app->ch[11].posX );
		break;
	}
	return bres;
}

bool MFCChess::CanLeft()
{
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	int dir = TDir::QZLEFT;
	bool bres = app->cb.ifmove(this->NO, dir);
	return bres;
	switch(this->type)
	{
	case 2:
		return ( (app->ch[10].posX == app->ch[11].posX && abs(app->ch[10].posY - app->ch[11].posY) == 1)
			&& this->posY*2+1 == app->ch[10].posY+app->ch[11].posY
			&& this->posX-1 == app->ch[10].posX );
		break;
	case 3:
		return ( (this->posY == app->ch[10].posY && this->posX-1 == app->ch[10].posX)
			|| (this->posY == app->ch[11].posY && this->posX-1 == app->ch[11].posX) );
		break;
	case 1:
		return ( (this->posY == app->ch[10].posY && this->posX-1 == app->ch[10].posX)
			|| (this->posY == app->ch[11].posY && this->posX-1 == app->ch[11].posX) );
		break;
	case 4:
		return ( (app->ch[10].posX == app->ch[11].posX && abs(app->ch[10].posY - app->ch[11].posY) == 1)
			&& this->posY*2+1 == app->ch[10].posY+app->ch[11].posY
			&& this->posX-1 == app->ch[10].posX );
		break;
	}
	return false;
}

bool MFCChess::CanRight()
{
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	int dir = TDir::QZRIGHT;
	bool bres = app->cb.ifmove(this->NO, dir);
	return bres;
	switch(this->type)
	{
	case 2:
		return ( (app->ch[10].posX == app->ch[11].posX && abs(app->ch[10].posY - app->ch[11].posY) == 1)
			&& this->posY*2+1 == app->ch[10].posY+app->ch[11].posY
			&& this->posX+1 == app->ch[10].posX );
		break;
	case 3:
		return ( (this->posY == app->ch[10].posY && this->posX+2 == app->ch[10].posX)
			|| (this->posY == app->ch[11].posY && this->posX+2 == app->ch[11].posX) );
		break;
	case 1:
		return ( (this->posY == app->ch[10].posY && this->posX+1 == app->ch[10].posX)
			|| (this->posY == app->ch[11].posY && this->posX+1 == app->ch[11].posX) );
		break;
	case 4:
		return ( (app->ch[10].posX == app->ch[11].posX && abs(app->ch[10].posY - app->ch[11].posY) == 1)
			&& this->posY*2+1 == app->ch[10].posY+app->ch[11].posY
			&& this->posX+2 == app->ch[10].posX );
		break;
	}
	return false;
}

void MFCChess::Up()
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

void MFCChess::Down()
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

void MFCChess::Left()
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

void MFCChess::Right()
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
void MFCChess::OnClicked() 
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

void MFCChess::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	lbdownpt=point;
	CButton::OnLButtonDown(nFlags, point);
}


void MFCChess::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    int 	dx=point.x-lbdownpt.x;
	int 	dy=point.y-lbdownpt.y;
	if(abs(dx)<3 && abs(dy)<3 ){
	}else{
      moveself(dx,dy);
	}
	CButton::OnLButtonUp(nFlags, point);
}
void movepos(MFCChess &a) {
	CRect ir = a.GetRect();
	int cx = ir.Width(), cy = ir.Height();
	//::SetWindowPos(a.m_hWnd, NULL,ir.left,ir.top,cx, cy, SWP_NOSIZE);
	//a.ShowWindow(SW_SHOW);
	a.SetWindowPos(NULL, ir.left, ir.top, cx, cy, SWP_NOSIZE);
	a.RedrawWindow();
}
void  MFCChess::moveself(int dx,int dy){
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	app->flag = false;
	int count = 0;
	count = this->CanUp() + this->CanDown() + this->CanLeft() + this->CanRight();
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
	movepos(*this);
//	movepos(app->ch[10]);
//	movepos(app->ch[11]);
	/*
	for(int i=0; i<10; i++)
	{
		if(this->NO == i)
		{
			app->ch[i].DestroyWindow();
			app->ch[i].Create(NULL,WS_CHILD | BS_OWNERDRAW |BS_PUSHBUTTON | WS_VISIBLE,
					app->ch[i].GetRect(),AfxGetMainWnd(),i);
			
			if(this->type == 3 || this->type == 4 || this->type == 2)
			{
				app->ch[0].LoadBitmaps(10*i+this->type);
			}
			else if(this->NO >= 6 && this->NO <=9)
				app->ch[i].LoadBitmaps(IDB_S);
			app->ch[i].RedrawWindow();
			app->ch[i].ShowWindow (SW_SHOW);
		}
	}
	*/
	//app->dir.direction += 1;
}
 
void MFCChess::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CBitmapButton::DrawItem(lpDrawItemStruct);
	 
	CDC* pdc = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;//空间选择
	 
	CPen pen;//边框颜色
	pen.CreatePen(PS_SOLID, 2, RGB(153, 217, 234));
	 
	CGdiObject *pold=pdc->SelectObject(&pen);
	CGdiObject* pold2 = pdc->SelectStockObject(NULL_BRUSH);
	pdc->Rectangle(rect);
	//pdc->MoveTo(rect.TopLeft());
	//pdc->LineTo(rect.BottomRight());

	pdc->SelectObject(pold);
	pdc->SelectObject(pold2);
	//pen.DeleteObject();
//	pdc->Detach();
	//pdc->DeleteDC();

}

 