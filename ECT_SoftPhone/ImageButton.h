#if !defined(AFX_IMAGEBUTTON_H__86B85480_B41F_11D6_AB47_00D0B70C3D79__INCLUDED_)
#define AFX_IMAGEBUTTON_H__86B85480_B41F_11D6_AB47_00D0B70C3D79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// bitmap button extended styles
#define BMPBTN_HOVER		0x00000001
#define BMPBTN_AUTO3D_SINGLE	0x00000002
#define BMPBTN_AUTO3D_DOUBLE	0x00000004
#define BMPBTN_AUTOSIZE		0x00000008
#define BMPBTN_SHAREIMAGELISTS	0x00000010
#define BMPBTN_AUTOFIRE		0x00000020

class CImageButton : public CButton
{
	enum
	{
		_nImageNormal = 0,
		_nImagePushed,
		_nImageFocusOrHover,
		_nImageDisabled,
		_nImageCount = 4,
	};

	enum
	{
		ID_TIMER_FIRST = 1000,
		ID_TIMER_REPEAT = 1001
	};

// Construction
public:
	CImageButton();

// Attributes
protected:
	COLORREF m_clrText;

	// Bitmap button specific extended styles
	DWORD m_dwExtendedStyle;

	CImageList m_ImageList;
	int m_nImage[_nImageCount];

	CToolTipCtrl m_tip;
	LPTSTR m_lpstrToolTipText;

	// Internal states
	BOOL m_bMouseOver;
	BOOL m_bFocus;
	BOOL m_bPressed;

	BOOL IsHoverMode() const
	{
		return ((m_dwExtendedStyle & BMPBTN_HOVER) != 0);
	}

	BOOL StartTrackMouseLeave();
	BOOL CalcTextRect(CDC *pDC, CRect &rcText);

public:
	DWORD GetBitmapButtonExtendedStyle() const;
	DWORD SetBitmapButtonExtendedStyle(DWORD dwExtendedStyle, DWORD dwMask = 0);
	HIMAGELIST GetImageList() const;
	HIMAGELIST SetImageList(HIMAGELIST hImageList);
	int GetToolTipTextLength() const;
	BOOL GetToolTipText(LPTSTR lpstrText, int nLength) const;
	BOOL SetToolTipText(LPCTSTR lpstrText);

	void SetImages(int nNormal, int nPushed = -1, int nDisabled = -1, int nFocusOrHover = -1);
	BOOL SizeToImage();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetTextColor(COLORREF clrText);
	BOOL AutoLoad(UINT nBitmapID, int nImageCount=4, int nBorderLeft=0, int nBorderTop=0, int nBorderRight=0, int nBorderBottom=0);
	virtual ~CImageButton();

	// Generated message map functions
protected:
	CDC m_dcBackground;
	void DrawBackground(CRect &rcButton, CDC *pDC);
	//{{AFX_MSG(CImageButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	LPARAM OnMouseLeave(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEBUTTON_H__86B85480_B41F_11D6_AB47_00D0B70C3D79__INCLUDED_)
