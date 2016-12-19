#include "stdafx.h"
#include "ImageButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TRANSPARENT_COLOR RGB(255,0,255)

CImageButton::CImageButton()
{
	m_dwExtendedStyle = NULL;//BMPBTN_AUTOSIZE | BMPBTN_HOVER;
	m_lpstrToolTipText = NULL;
	
	m_bMouseOver = FALSE;
	m_bFocus = FALSE;
	m_bPressed = FALSE;

	m_nImage[_nImageNormal] = -1;
	m_nImage[_nImagePushed] = -1;
	m_nImage[_nImageFocusOrHover] = -1;
	m_nImage[_nImageDisabled] = -1;

	m_clrText = ::GetSysColor(COLOR_BTNTEXT);

	m_dcBackground.m_hDC = NULL;
}


CImageButton::~CImageButton()
{
	if((m_dwExtendedStyle & BMPBTN_SHAREIMAGELISTS) == 0)
		m_ImageList.DeleteImageList();
	delete [] m_lpstrToolTipText;
}


BEGIN_MESSAGE_MAP(CImageButton, CButton)
	//{{AFX_MSG_MAP(CImageButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CAPTURECHANGED()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ENABLE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()


/********************************************************************/
/*																	*/
/* Function name : GetBitmapButtonExtendedStyle						*/
/* Description   : Get extended style of bitmap button.				*/
/*																	*/
/********************************************************************/
DWORD CImageButton::GetBitmapButtonExtendedStyle() const
{
	return m_dwExtendedStyle;
}


/********************************************************************/
/*																	*/
/* Function name : SetBitmapButtonExtendedStyle						*/
/* Description   : Set extended style of bitmap button.				*/
/*																	*/
/********************************************************************/
DWORD CImageButton::SetBitmapButtonExtendedStyle(DWORD dwExtendedStyle, DWORD dwMask)
{
	DWORD dwPrevStyle = m_dwExtendedStyle;
	if(dwMask == 0)
		m_dwExtendedStyle = dwExtendedStyle;
	else
		m_dwExtendedStyle = (m_dwExtendedStyle & ~dwMask) | (dwExtendedStyle & dwMask);
	return dwPrevStyle;
}


/********************************************************************/
/*																	*/
/* Function name : GetImageList										*/
/* Description   : Get image list.									*/
/*																	*/
/********************************************************************/
HIMAGELIST CImageButton::GetImageList() const
{
	return m_ImageList;
}


/********************************************************************/
/*																	*/
/* Function name : SetImageList										*/
/* Description   : Set image list.									*/
/*																	*/
/********************************************************************/
HIMAGELIST CImageButton::SetImageList(HIMAGELIST hImageList)
{
	HIMAGELIST hImageListPrev = m_ImageList.Detach();

	m_ImageList.Attach(hImageList);
	if((m_dwExtendedStyle & BMPBTN_AUTOSIZE) != 0 && ::IsWindow(m_hWnd))
		SizeToImage();
	return hImageListPrev;
}


/********************************************************************/
/*																	*/
/* Function name : GetToolTipTextLength								*/
/* Description   : Get text length of tooltip						*/
/*																	*/
/********************************************************************/
int CImageButton::GetToolTipTextLength() const
{
	return (m_lpstrToolTipText == NULL) ? -1 : lstrlen(m_lpstrToolTipText);
}


/********************************************************************/
/*																	*/
/* Function name : GetToolTipText									*/
/* Description   : Get text of tooltip.								*/
/*																	*/
/********************************************************************/
BOOL CImageButton::GetToolTipText(LPTSTR lpstrText, int nLength) const
{
	ASSERT(lpstrText != NULL);
	if(m_lpstrToolTipText == NULL)
		return FALSE;
	return (lstrcpyn(lpstrText, m_lpstrToolTipText, min(nLength, lstrlen(m_lpstrToolTipText) + 1)) != NULL);
}


/********************************************************************/
/*																	*/
/* Function name : SetToolTipText									*/
/* Description   : Set text of tooltip.								*/
/*																	*/
/********************************************************************/
BOOL CImageButton::SetToolTipText(LPCTSTR lpstrText)
{
	if(m_lpstrToolTipText != NULL)
	{
		delete [] m_lpstrToolTipText;
		m_lpstrToolTipText = NULL;
	}
	if(lpstrText == NULL)
	{
		if(IsWindow(m_tip.m_hWnd))
			m_tip.Activate(FALSE);
		return TRUE;
	}
	m_lpstrToolTipText = new TCHAR[lstrlen(lpstrText) + 1];

	if(m_lpstrToolTipText == NULL)
		return FALSE;

	BOOL bRet = (lstrcpy(m_lpstrToolTipText, lpstrText) != NULL);
	if(bRet && IsWindow(m_tip.m_hWnd))
	{
		m_tip.Activate(TRUE);
		m_tip.AddTool(this, m_lpstrToolTipText);
	}
	return bRet;
}


/********************************************************************/
/*																	*/
/* Function name : SetImages										*/
/* Description   : Set index of specific images.					*/
/*																	*/
/********************************************************************/
void CImageButton::SetImages(int nNormal, int nPushed, int nDisabled, int nFocusOrHover)
{
//	if(nNormal != -1)
	m_nImage[_nImageNormal] = nNormal;
//	if(nPushed != -1)
	m_nImage[_nImagePushed] = nPushed;
//	if(nDisabled != -1)
	m_nImage[_nImageDisabled] = nDisabled;
//	if(nFocusOrHover != -1)
	m_nImage[_nImageFocusOrHover] = nFocusOrHover;
}


/********************************************************************/
/*																	*/
/* Function name : SizeToImage										*/
/* Description   : Resize bitmap button to the size of the bitmap.	*/
/*																	*/
/********************************************************************/
BOOL CImageButton::SizeToImage()
{
	ASSERT(::IsWindow(m_hWnd) && m_ImageList.m_hImageList != NULL);
	int cx = 0;
	int cy = 0;
	
	if(!ImageList_GetIconSize(m_ImageList.m_hImageList, &cx, &cy))
		return FALSE;

	return SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOZORDER);
}


/********************************************************************/
/*																	*/
/* Function name : DrawItem											*/
/* Description   : Called by the framework when a visual aspect of	*/
/*				   an owner-draw button changes.					*/
/*																	*/
/********************************************************************/
void CImageButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// image list must be set
	if (m_ImageList.m_hImageList == NULL)
		return;

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	// create memory dc to reduce flickering
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CRect rect;
	rect.CopyRect(&lpDrawItemStruct->rcItem);

	CBitmap bitmapMem;
    bitmapMem.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	CBitmap *pOldBitmap = memDC.SelectObject(&bitmapMem);

	// main bitmap must be set
	ASSERT(m_nImage[0] != -1);			

	// set bitmap according to the current button state
	int nImage = -1;
	BOOL bHover = IsHoverMode();

	if(m_bPressed)
		nImage = m_nImage[_nImagePushed];
	else 
	if((!bHover && m_bFocus) || (bHover && m_bMouseOver))
		nImage = m_nImage[_nImageFocusOrHover];
	else 
	if(!IsWindowEnabled())
		nImage = m_nImage[_nImageDisabled];
	
	// not there, use default one
	if(nImage == -1)	
		nImage = m_nImage[_nImageNormal];

	// draw the button image
	int xyPos = 0;
	if((m_bPressed) && ((m_dwExtendedStyle & (BMPBTN_AUTO3D_SINGLE | BMPBTN_AUTO3D_DOUBLE)) != 0) && (m_nImage[_nImagePushed] == -1))
		xyPos = 1;

	// let the background shine through
	DrawBackground(rect, &memDC);

	// draw the button's bitmap
	m_ImageList.Draw(&memDC, nImage, CPoint(xyPos, xyPos), ILD_TRANSPARENT);

	// draw 3D border if required
	if((m_dwExtendedStyle & (BMPBTN_AUTO3D_SINGLE | BMPBTN_AUTO3D_DOUBLE)) != 0)
	{
		if(m_bPressed == 1)
			memDC.DrawEdge(&rect, ((m_dwExtendedStyle & BMPBTN_AUTO3D_SINGLE) != 0) ? BDR_SUNKENOUTER : EDGE_SUNKEN, BF_RECT);
		else 
		if(!bHover || m_bMouseOver == 1)
			memDC.DrawEdge(&rect, ((m_dwExtendedStyle & BMPBTN_AUTO3D_SINGLE) != 0) ? BDR_RAISEDINNER : EDGE_RAISED, BF_RECT);

		if(!bHover && m_bFocus == 1)
		{
			::InflateRect(&rect, -2 * ::GetSystemMetrics(SM_CXEDGE), -2 * ::GetSystemMetrics(SM_CYEDGE));
			memDC.DrawFocusRect(&rect);
		}
	}
	
	// get button's text
	CString strText;
	GetWindowText(strText);
	   
	// set text properties
	COLORREF oldTextColor = memDC.SetTextColor(m_clrText);
	int oldBkMode = memDC.SetBkMode(TRANSPARENT);

	// set default font
	CFont *pOldFont = memDC.SelectObject(GetFont());

	// calculate text's rectangle depending on button style
	CRect rcText = lpDrawItemStruct->rcItem;
	CalcTextRect(&memDC, rcText);

	// is button pushed ?
	if(m_bPressed)
		rcText.OffsetRect(1, 1);

	BOOL bIsDisabled = (lpDrawItemStruct->itemState & ODS_DISABLED);

	// paint button's text
	memDC.DrawState(rcText.TopLeft(), rcText.Size(), (LPCTSTR)strText, (bIsDisabled ? DSS_DISABLED : DSS_NORMAL), TRUE, 0, (CBrush*)NULL);

	// restore old values
	memDC.SelectObject(pOldFont);
	memDC.SetTextColor(oldTextColor);
	memDC.SetBkMode(oldBkMode);

	// blit the image to the screen
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
}


/********************************************************************/
/*																	*/
/* Function name : DrawBackground									*/
/* Description   : Draw original background (parent) for non-		*/
/*				   rectangular buttons.								*/
/*																	*/
/********************************************************************/
void CImageButton::DrawBackground(CRect &rcButton, CDC *pDC)
{
	if (m_dcBackground.m_hDC == NULL)
	{
		// let the background shine through
		CClientDC dcParent(GetParent());

		CBitmap bmpBackground;
		CRect rcParent;

		// get parent rectangle
		GetWindowRect(&rcParent);
		GetParent()->ScreenToClient(rcParent);

		m_dcBackground.CreateCompatibleDC(&dcParent);
		bmpBackground.CreateCompatibleBitmap(&dcParent, rcButton.Width(), rcButton.Height());
		
		m_dcBackground.SelectObject(&bmpBackground);

		// copy background (parent)in dc
		m_dcBackground.BitBlt(0, 0, rcButton.Width(), rcButton.Height(), &dcParent, rcParent.left, rcParent.top, SRCCOPY);
	}
	// copy to our bitmap dc
	pDC->BitBlt(0, 0, rcButton.Width(), rcButton.Height(), &m_dcBackground, 0, 0, SRCCOPY);
}


/********************************************************************/
/*																	*/
/* Function name : PreSubclassWindow								*/
/* Description   : Initialize stuff.								*/
/*																	*/
/********************************************************************/
void CImageButton::PreSubclassWindow() 
{
	// We need this style to prevent Windows from painting the button
	ModifyStyle(0, BS_OWNERDRAW);

	// create a tool tip
	m_tip.Create(this);
	if(IsWindow(m_tip.m_hWnd) && m_lpstrToolTipText != NULL)
	{
		m_tip.Activate(TRUE);
		m_tip.AddTool(this, m_lpstrToolTipText);
	}

	if(m_ImageList.m_hImageList != NULL && (m_dwExtendedStyle & BMPBTN_AUTOSIZE) != 0)
		SizeToImage();
	
	CButton::PreSubclassWindow();
}


/********************************************************************/
/*																	*/
/* Function name : SetTextColor										*/
/* Description   : Set button's text color							*/
/*																	*/
/********************************************************************/
void CImageButton::SetTextColor(COLORREF clrText)
{
	m_clrText = clrText;
}


/********************************************************************/
/*																	*/
/* Function name : OnLButtonDown									*/
/* Description   : Called when left mouse button is pressed.		*/
/*																	*/
/********************************************************************/
void CImageButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(IsHoverMode())
		SetCapture();
	else
		CButton::OnLButtonDown(nFlags, point);

	if(::GetCapture() == m_hWnd)
	{
		m_bPressed = TRUE;
		Invalidate();
		UpdateWindow();
	}
	if((m_dwExtendedStyle & BMPBTN_AUTOFIRE) != 0)
	{
		int nElapse = 250;
		int nDelay = 0;
		if(::SystemParametersInfo(SPI_GETKEYBOARDDELAY, 0, &nDelay, 0))
			nElapse += nDelay * 250;	// all milli-seconds
//		SetTimer(ID_TIMER_FIRST, nElapse, NULL);
	}
}


/********************************************************************/
/*																	*/
/* Function name : OnLButtonUp										*/
/* Description   : Called when left mouse button is released.		*/
/*																	*/
/********************************************************************/
void CImageButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	BOOL bHover = IsHoverMode();
	if(!bHover)
		CButton::OnLButtonUp(nFlags, point);
	
	if(::GetCapture() == m_hWnd)
	{
		if(bHover && m_bPressed)
		{
			::ReleaseCapture();
			::SendMessage(GetParent()->m_hWnd, WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
		}
	}	
}


/********************************************************************/
/*																	*/
/* Function name : OnCaptureChanged									*/
/* Description   : Mouse capture status has been changed			*/
/*																	*/
/********************************************************************/
void CImageButton::OnCaptureChanged(CWnd *pWnd) 
{
	if(m_bPressed)
	{
		m_bPressed = FALSE;
		Invalidate();
		UpdateWindow();
	}
	CButton::OnCaptureChanged(pWnd);
}


/********************************************************************/
/*																	*/
/* Function name : OnEraseBkgnd										*/
/* Description   : Prevent flickering								*/
/*																	*/
/********************************************************************/
BOOL CImageButton::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;//CButton::OnEraseBkgnd(pDC);
}


/********************************************************************/
/*																	*/
/* Function name : OnLButtonDblClk									*/
/* Description   : Called when user double-clicks left mouse button.*/
/*																	*/
/********************************************************************/
void CImageButton::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if(!IsHoverMode())
		CButton::OnLButtonDblClk(nFlags, point);
	
	if(::GetCapture() != m_hWnd)
		SetCapture();
	
	if(!m_bPressed)
	{
		m_bPressed = TRUE;
		Invalidate();
		UpdateWindow();
	}	
}


/********************************************************************/
/*																	*/
/* Function name : OnEnable											*/
/* Description   : Called when button is enabled/disabled			*/
/*																	*/
/********************************************************************/
void CImageButton::OnEnable(BOOL bEnable) 
{
	CButton::OnEnable(bEnable);
	
	Invalidate();
	UpdateWindow();	
}


/********************************************************************/
/*																	*/
/* Function name : OnMouseMove										*/
/* Description   : Called when mouse is moved						*/
/*																	*/
/********************************************************************/
void CImageButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(::GetCapture() == m_hWnd)
	{
		POINT ptCursor = point;
		ClientToScreen(&ptCursor);
		RECT rect;
		GetWindowRect(&rect);
		BOOL bPressed = ::PtInRect(&rect, ptCursor) ? 1 : 0;
		if(m_bPressed != bPressed)
		{
			m_bPressed = bPressed;
			Invalidate();
			UpdateWindow();
		}
	}
	else 
	if(IsHoverMode() && m_bMouseOver == 0)
	{
		m_bMouseOver = TRUE;
		Invalidate();
		UpdateWindow();
		StartTrackMouseLeave();
	}	
//	CButton::OnMouseMove(nFlags, point);
}


/********************************************************************/
/*																	*/
/* Function name : OnMouseLeave										*/
/* Description   : Called when mouse leaves button area				*/
/*																	*/
/********************************************************************/
LPARAM CImageButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if(m_bMouseOver)
	{
		m_bMouseOver = FALSE;
		Invalidate();
		UpdateWindow();
	}	
	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : OnTimer											*/
/* Description   : Handle timer										*/
/*																	*/
/********************************************************************/
void CImageButton::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)	// timer ID
	{
	case ID_TIMER_FIRST:
		KillTimer(ID_TIMER_FIRST);
		if(m_bPressed)
		{
			::SendMessage(GetParent()->m_hWnd, WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
			int nElapse = 250;
			int nRepeat = 40;
			if(::SystemParametersInfo(SPI_GETKEYBOARDSPEED, 0, &nRepeat, 0))
				nElapse = 10000 / (10 * nRepeat + 25);	// milli-seconds, approximated
//			SetTimer(ID_TIMER_REPEAT, nElapse, NULL);
		}
		break;
	case ID_TIMER_REPEAT:
		if(m_bPressed)
			::SendMessage(GetParent()->m_hWnd, WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
		else 
		if(::GetCapture() != m_hWnd)
			KillTimer(ID_TIMER_REPEAT);
		break;
	default:	// not our timer
		break;
	}	
	CButton::OnTimer(nIDEvent);
}


/********************************************************************/
/*																	*/
/* Function name : StartTrackMouseLeave								*/
/* Description   : Start tracking mouse (to generate WM_MOUSELEAVE)	*/
/*																	*/
/********************************************************************/
BOOL CImageButton::StartTrackMouseLeave()
{
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = m_hWnd;
	return _TrackMouseEvent(&tme);
}


/********************************************************************/
/*																	*/
/* Function name : AutoLoad											*/
/* Description   : Autload button images and size them to button	*/
/*																	*/
/********************************************************************/
BOOL CImageButton::AutoLoad(UINT nBitmapID, int nImageCount, int nBorderLeft, int nBorderTop, int nBorderRight, int nBorderBottom)
{
	CDC *pDC = GetDC();

	// get button size
    CRect rect;
    GetClientRect(&rect);

	// create source DC
	CBitmap bitmapSource;
	bitmapSource.LoadBitmap(nBitmapID);
    
	BITMAP bmpInfo;
    bitmapSource.GetBitmap(&bmpInfo);
    int bmpWidth = bmpInfo.bmWidth / nImageCount;
    int bmpHeight = bmpInfo.bmHeight;

    CDC sourceDC;
    sourceDC.CreateCompatibleDC(pDC);

	// select source bitmap into dc
    CBitmap* pOldBitmap1 = sourceDC.SelectObject(&bitmapSource);

    // create memory dc
	CDC memDC; 
    memDC.CreateCompatibleDC(pDC);

	// create bitmap that's nImageCount x button width
	CBitmap bitmapMem;
    bitmapMem.CreateCompatibleBitmap(pDC, rect.Width() * nImageCount, rect.Height());

	// select destination bitmap into dc
    CBitmap* pOldBitmap2 = memDC.SelectObject(&bitmapMem);

	// size the bitmaps
	for (int i=0; i < nImageCount; i++)
	{
		int nSourceOffset = bmpWidth * i;
		int nOffset = rect.Width() * i;

		// complete image (without borders)
		memDC.StretchBlt(nOffset + nBorderLeft,
						 nBorderTop,
						 rect.Width()  - nBorderLeft - nBorderRight,
						 rect.Height() - nBorderTop - nBorderBottom,
						 &sourceDC,
						 nSourceOffset + nBorderLeft,
						 nBorderTop,
						 bmpWidth - nBorderLeft - nBorderRight,
						 bmpHeight - nBorderTop - nBorderBottom,
						 SRCCOPY);

		// left-top corner
		memDC.BitBlt(nOffset, 
					0, 
					nBorderLeft, 
					nBorderTop, 
					&sourceDC, 
					nSourceOffset, 
					0, 
					SRCCOPY);

		// right-top corner
		memDC.BitBlt(nOffset + rect.right - nBorderRight, 
					0,
					nBorderRight, 
					nBorderTop, 
					&sourceDC,
					nSourceOffset + bmpWidth - nBorderRight,
					0,
					SRCCOPY);
		
		// right-bottom corner
		memDC.BitBlt(nOffset + rect.right - nBorderRight,
					rect.bottom - nBorderBottom,
					nBorderRight,
					nBorderBottom,
					&sourceDC,
					nSourceOffset + bmpWidth - nBorderRight,
					bmpHeight - nBorderBottom,
					SRCCOPY);

		// left-bottom corner
		memDC.BitBlt(nOffset, 
					rect.bottom - nBorderBottom, 
					nBorderLeft, nBorderBottom, 
					&sourceDC,
					nSourceOffset,
					bmpHeight - nBorderBottom,
					SRCCOPY);

		// top border
		memDC.StretchBlt(nOffset + nBorderLeft,
						0, 
						rect.Width() - nBorderLeft - nBorderRight, 
						nBorderTop,
						&sourceDC,
						nSourceOffset + nBorderLeft, 
						0, 
						bmpWidth - nBorderLeft - nBorderRight, 
						nBorderTop,
						SRCCOPY);

		// right border
		memDC.StretchBlt(nOffset + rect.right - nBorderRight,
						nBorderTop,
						nBorderRight,
						rect.bottom - nBorderTop - nBorderBottom,
						&sourceDC, 
						nSourceOffset +  bmpWidth - nBorderRight,
						nBorderTop, 
						nBorderRight, 
						bmpHeight - nBorderTop - nBorderBottom,
						SRCCOPY);

		// bottom border
		memDC.StretchBlt(nOffset + nBorderLeft, 
						rect.bottom - nBorderBottom, 
						rect.Width() - nBorderLeft - nBorderRight, 
						nBorderBottom,
						&sourceDC,
						nSourceOffset + nBorderLeft,
						bmpHeight - nBorderBottom, 
						bmpWidth - nBorderLeft - nBorderRight, 
						nBorderBottom, 
						SRCCOPY);

		// left border
		memDC.StretchBlt(nOffset, 
						nBorderTop, 
						nBorderLeft,
						rect.bottom - nBorderTop - nBorderBottom,
						&sourceDC, 
						nSourceOffset,
						nBorderTop, 
						nBorderLeft, 
						bmpHeight - nBorderTop - nBorderBottom,
						SRCCOPY);
	}

    sourceDC.SelectObject(pOldBitmap1);
    memDC.SelectObject(pOldBitmap2);

    ReleaseDC(&sourceDC);
    ReleaseDC(&memDC);

    ReleaseDC(pDC);

	// create CImageList
	m_ImageList.Create(rect.Width(), rect.Height(), ILC_COLOR16 | ILC_MASK, 0, 1);
	m_ImageList.Add(&bitmapMem, TRANSPARENT_COLOR);
	
	SetImages(0, (nImageCount > 1) ? 1 : -1, (nImageCount > 2) ? 2 : -1, (nImageCount > 3) ? 3 : -1);
	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : CalcTextRect										*/
/* Description   : Calculate text's rectangle depending on button	*/
/*				   style.											*/
/*																	*/
/********************************************************************/
BOOL CImageButton::CalcTextRect(CDC *pDC, CRect &rcText)
{
	CRect rc = rcText;

	CString strText;
	GetWindowText(strText);
	pDC->DrawText(strText, -1, &rc, DT_CALCRECT);

	int nOffset;

	DWORD dwStyle = GetStyle();

	switch(dwStyle & (BS_CENTER|BS_RIGHT))
	{
		case BS_LEFT:    
			rc.left += 4;  
			rc.right += 4;  
			break;

		case BS_RIGHT:   
			nOffset = rc.Width();
            rc.right = rcText.right - 4;
            rc.left = rc.right - nOffset;
            break;
		
		case BS_CENTER:  
		default:
			nOffset = rc.Width();
            rc.left = rcText.left + (rcText.Width() - nOffset) / 2;
            rc.right = rc.left + nOffset; 
			break;
	}

   	switch (dwStyle & (BS_VCENTER|BS_BOTTOM))
	{
		case BS_TOP:     
			rc.top += 4;  
			rc.bottom += 4;  
			break;
		
		case BS_BOTTOM:  
			nOffset = rc.Height();
            rc.bottom = rcText.bottom - 4;
            rc.top = rc.bottom - nOffset;
            break;
		
		case BS_VCENTER: 
		default:
			nOffset = rc.Height();
            rc.top = rcText.top + (rcText.Height() - nOffset) / 2;
            rc.bottom = rc.top + nOffset;
			break;
	}
	rcText = rc;
	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : OnSetFocus										*/
/* Description   : Button has focus									*/
/*																	*/
/********************************************************************/
void CImageButton::OnSetFocus(CWnd* pOldWnd) 
{
	CButton::OnSetFocus(pOldWnd);
	
	m_bFocus = TRUE;
	Invalidate();
	UpdateWindow();
}


/********************************************************************/
/*																	*/
/* Function name : OnKillFocus										*/
/* Description   : Button lost focus								*/
/*																	*/
/********************************************************************/
void CImageButton::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	m_bFocus = FALSE;
	Invalidate();
	UpdateWindow();
}


