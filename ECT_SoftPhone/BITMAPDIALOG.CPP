
// BitmapDialog.cpp
//

#include "stdafx.h"
#include "BitmapDialog.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapDialog dialog

CBitmapDialog::CBitmapDialog()
{
	CommonConstruct();
}

CBitmapDialog::~CBitmapDialog()
{
	m_HollowBrush.DeleteObject();
}

CBitmapDialog::CBitmapDialog(UINT uResource, CWnd* pParent /*=NULL*/)
	: CDialog(uResource, pParent)
{
	CommonConstruct();
}


CBitmapDialog::CBitmapDialog(LPCTSTR pszResource, CWnd* pParent /*=NULL*/)
	: CDialog(pszResource, pParent)
{
	CommonConstruct();
}

BOOL CBitmapDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    m_hAccel = ::LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)); 
    ASSERT(m_hAccel); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CBitmapDialog::PreTranslateMessage(MSG* pMsg) 
{
    if (WM_KEYFIRST <= pMsg->message && 
        pMsg->message <= WM_KEYLAST) 
    { 
        HACCEL hAccel = m_hAccel; 
        if (hAccel && 
            ::TranslateAccelerator(m_hWnd, hAccel, pMsg)) 
            return TRUE; 
    } 
    return CDialog::PreTranslateMessage(pMsg);
}

void CBitmapDialog::CommonConstruct()
{
	m_nType = BITMAP_TILE;
	VERIFY(m_HollowBrush.CreateStockObject(HOLLOW_BRUSH));

	//{{AFX_DATA_INIT(CBitmapDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


BOOL CBitmapDialog :: SetBitmap(UINT uResource, int nType /*BITMAP_TILE*/) {
	m_nType = nType;
	ASSERT(m_nType == BITMAP_TILE || m_nType == BITMAP_STRETCH || m_nType == BITMAP_CENTER);
	return m_bmpBackground.LoadResource(uResource);
}


void CBitmapDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBitmapDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBitmapDialog, CDialog)
	//{{AFX_MSG_MAP(CBitmapDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapDialog message handlers

BOOL CBitmapDialog::OnEraseBkgnd(CDC* pDC) 
{
	if(m_bmpBackground.GetPixelPtr() != 0) {
		ASSERT(m_nType == BITMAP_TILE || m_nType == BITMAP_STRETCH || m_nType == BITMAP_CENTER);
		
		CRect rc;
		GetClientRect(rc);
		int x = 0, y = 0;

		switch(m_nType) {
			case BITMAP_CENTER:
				// center the bitmap
				CDialog::OnEraseBkgnd(pDC);
				x = (rc.Width() - m_bmpBackground.GetWidth()) / 2;
				y = (rc.Height() - m_bmpBackground.GetHeight()) / 2;
				m_bmpBackground.DrawDIB(pDC, x, y);
				break;

			case BITMAP_STRETCH:
				// stretch bitmap so it will best fit to the dialog
				m_bmpBackground.DrawDIB(pDC, 0, 0, rc.Width(), rc.Height());
				break;

			default:
				// tile the bitmap
				while(y < rc.Height()) {
					while(x < rc.Width()) {
						m_bmpBackground.DrawDIB(pDC, x, y);
						x += m_bmpBackground.GetWidth();
					}
					x = 0;
					y += m_bmpBackground.GetHeight();
				}
				break;
		}
	} else
		// no bitmap set. behave like a normal dialog
		return CDialog::OnEraseBkgnd(pDC);

	return TRUE;
}

HBRUSH CBitmapDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if(m_bmpBackground.GetPixelPtr() != 0) {
		switch(nCtlColor) {
			case CTLCOLOR_STATIC:
			case CTLCOLOR_BTN:
				// let static controls shine through
				pDC->SetBkMode(TRANSPARENT);
				return HBRUSH(m_HollowBrush);

			default:
				break;
		}
	}
	
	// if we reach this line, we haven't set a brush so far
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

BOOL CBitmapDialog::OnQueryNewPalette() 
{
	CPalette * pPal = m_bmpBackground.GetPalette();
	if( pPal != 0 && GetSafeHwnd() != 0 ) {
		CClientDC dc(this);
		CPalette * pOldPalette = dc.SelectPalette(pPal, FALSE);
		UINT nChanged = dc.RealizePalette();
		dc.SelectPalette(pOldPalette, TRUE);

		if (nChanged == 0)
			return FALSE;

		Invalidate();
		return TRUE;
	}
	return CDialog::OnQueryNewPalette();
}

void CBitmapDialog::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CPalette * pPal = m_bmpBackground.GetPalette();
	if( pPal != 0 && GetSafeHwnd() != 0 && pFocusWnd != this && ! IsChild(pFocusWnd) ) {
		CClientDC dc(this);
		CPalette * pOldPalette = dc.SelectPalette(pPal, TRUE);
		UINT nChanged = dc.RealizePalette();
		dc.SelectPalette(pOldPalette, TRUE);

		if( nChanged )
			Invalidate();
	} else
		CDialog::OnPaletteChanged(pFocusWnd);
}

void CBitmapDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
//	TRACE("Begin to PostNcDestroy\n");
	CDialog::PostNcDestroy();
}



BOOL CBitmapDialog::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
/*
#ifdef _AFX_NO_OCC_SUPPORT 
	BOOL bResult = ::DestroyWindow(m_hWnd); 
#else //_AFX_NO_OCC_SUPPORT 
	BOOL bResult; 
	if (m_pCtrlSite == NULL) 
		bResult = ::DestroyWindow(m_hWnd); 
	else 
		;//bResult = m_pCtrlSite->DestroyControl(); 
#endif //_AFX_NO_OCC_SUPPORT */
	TRACE("DestroyWindow\n");

	::DestroyWindow(m_hWnd);
	return TRUE;	
//	return CDialog::DestroyWindow();
}
