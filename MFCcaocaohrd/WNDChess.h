#if !defined(AFX_WNDChess_H__938D8862_E665_469B_877F_D77E86BE08AE__INCLUDED_)
#define AFX_WNDChess_H__938D8862_E665_469B_877F_D77E86BE08AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WNDChess.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WNDChess window

class WNDChess : public CBitmapButton
{
// Construction
public:
	WNDChess();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WNDChess)
	//}}AFX_VIRTUAL

// Implementation
public:
	CPoint lbdownpt;
	void moveself(int dx,int dy);
	int posX=0;
	int posY=0;
	int recX1;
	int recX2;
	int recY1;
	int recY2;
	int type=1;
	int NO=6;
	void Set(int x,int y,int t);
	CRect GetRect();
	bool CanUp();
	bool CanDown();
	bool CanLeft();
	bool CanRight();
	void Up();
	void Down();
	void Left();
	void Right();
	virtual ~WNDChess();
	BOOL m_bdown=false;
	// Generated message map functions
protected:
	//{{AFX_MSG(WNDChess)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
 virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDChess_H__938D8862_E665_469B_877F_D77E86BE08AE__INCLUDED_)
