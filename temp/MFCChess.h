#if !defined(AFX_MFCCHESS_H__938D8862_E665_469B_877F_D77E86BE08AE__INCLUDED_)
#define AFX_MFCCHESS_H__938D8862_E665_469B_877F_D77E86BE08AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MFCChess.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MFCChess window

class MFCChess : public CBitmapButton
{
// Construction
public:
	MFCChess();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MFCChess)
	//}}AFX_VIRTUAL

// Implementation
public:
	CPoint lbdownpt;
	void moveself(int dx,int dy);
	int posX;
	int posY;
	int recX1;
	int recX2;
	int recY1;
	int recY2;
	int type;
	int NO;
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
	virtual ~MFCChess();

	// Generated message map functions
protected:
	//{{AFX_MSG(MFCChess)
	afx_msg void OnClicked();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
 virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCCHESS_H__938D8862_E665_469B_877F_D77E86BE08AE__INCLUDED_)
