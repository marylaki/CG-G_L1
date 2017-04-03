
#include "LibGraph.h"
#include <string>
#define ID_M 2002
#define ID_F 2004

class CMyMainWnd : public CFrameWnd
{
public:
	CMyMainWnd()
	{
		Create(NULL, L" √и√ Laba 1 \"CMatrix\"");
		
	}
	CMenu *menu;
	afx_msg int OnCreate(LPCREATESTRUCT);
	void Matrix();
	void Functions();
	DECLARE_MESSAGE_MAP();
};
class CMyApp : public CWinApp
{
public:
	CMyApp(){};
	virtual BOOL InitInstance()
	{
		m_pMainWnd = new CMyMainWnd();
		m_pMainWnd->ShowWindow(SW_SHOW);
		
		return TRUE;
	}
};
BEGIN_MESSAGE_MAP(CMyMainWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_M, Matrix)
	ON_COMMAND(ID_F, Functions)
END_MESSAGE_MAP()

afx_msg int CMyMainWnd::OnCreate(LPCREATESTRUCT)
{
	menu = new CMenu();
	menu->CreateMenu();
	CMenu *subMenu = new CMenu();
	subMenu->CreatePopupMenu();
	subMenu->AppendMenu(MF_STRING, ID_M, _T("Matrix"));
	subMenu->AppendMenu(MF_STRING, ID_F, _T("Functions"));
	this->menu->AppendMenu(MF_POPUP | MF_STRING, (UINT)subMenu->m_hMenu, _T("Tests"));
	SetMenu(menu);
	return 0;
}

void CMyMainWnd::Matrix()
{
	InvalidateRect(0);
	UpdateWindow();
	CClientDC dc(this);
	CChildView M;
	int yout = 20;
	int xout = 700;
	dc.Rectangle(650, 0, 651, 800);
	dc.TextOut(xout, yout + 32, "A = ");
	PrintMatrix(dc, xout+40, yout, *M.A);
	dc.TextOut(xout, (yout+=120) + 32, "B = ");
	PrintMatrix(dc, xout + 40, yout, *M.B);
	dc.TextOut(xout, (yout += 120) + 32, "V1 = ");
	PrintMatrix(dc, xout + 40, yout, *M.V1);
	dc.TextOut(xout, (yout += 120) + 32, "V2 = ");
	PrintMatrix(dc, xout + 40, yout, *M.V2);
	/* C1=A+B */
	yout = 20;
	xout = 10;
	dc.TextOut(xout , yout -15, "C1=A+B");
	PrintMatrix(dc, xout, yout, *M.A);
	dc.TextOut(xout += 185, yout + 32, "+");
	PrintMatrix(dc, xout += 35, yout, *M.B);
	dc.TextOut(xout += 185, yout + 32, "=");
	CMatrix C1 = *M.A + *M.B;
	PrintMatrix(dc, xout += 35, yout, C1);
	/* C2=A*B */
	xout = 10;
	yout += 120;
	dc.TextOut(xout, yout - 15, "C2=A*B");
	PrintMatrix(dc, xout, yout, *M.A);
	dc.TextOut(xout += 185, yout + 32, "x");
	PrintMatrix(dc, xout += 35, yout, *M.B);
	dc.TextOut(xout += 185, yout + 32, "=");
	CMatrix C2 = *M.A * *M.B;
	PrintMatrix(dc, xout += 35, yout, C2);
	/* D=A*V1 */
	xout = 10;
	yout += 120;
	dc.TextOut(xout, yout - 15, "D=A*V1");
	PrintMatrix(dc, xout, yout, *M.A);
	dc.TextOut(xout += 185, yout + 32, "x");
	PrintMatrix(dc, xout += 35, yout, *M.V1);
	dc.TextOut(xout += 70, yout + 32, "=");
	CMatrix D = (*M.A)*(*M.V1);
	PrintMatrix(dc, xout += 35, yout, D);
	CMatrix q, p;
	/* q=v1t*v2 */
	xout = 10;
	yout += 120;
	dc.TextOut(xout, yout - 15, "q=V1 *V2");
	dc.TextOut(xout+31, yout - 23, "т");
	PrintMatrix(dc, xout, yout+32, (*M.V1).Transp());
	dc.TextOut(xout += 185, yout+32, "x");
	PrintMatrix(dc, xout += 35, yout, *M.V2);
	dc.TextOut(xout += 70, yout+32, "=");
	q = (*M.V1).Transp()*(*M.V2);
	PrintMatrix(dc, xout += 35, yout+32, q);
	/* p=v1t*A*v2 */
	xout = 10;
	yout += 120;
	dc.TextOut(xout, yout - 15, "p=V1 *A*V2");
	dc.TextOut(xout + 31, yout - 23, "т");
	PrintMatrix(dc, xout, yout + 32, (*M.V1).Transp());
	dc.TextOut(xout += 185, yout + 32, "x");
	PrintMatrix(dc, xout+=35, yout, *M.A);
	dc.TextOut(xout += 185, yout + 32, "x");
	PrintMatrix(dc, xout += 35, yout, *M.V2);
	dc.TextOut(xout += 70, yout + 32, "=");
	p = (*M.V1).Transp()*(*M.A)*(*M.V2);
	PrintMatrix(dc, xout += 35, yout + 32, p);

}
void CMyMainWnd::Functions()
{
	char t[10];
	InvalidateRect(0);
	UpdateWindow();
	CClientDC dc(this);
	CChildView M;
	int yout = 20;
	int xout = 700;
	dc.Rectangle(600, 0, 601, 800);
	dc.TextOut(xout, (yout += 120) + 32, "V1 = ");
	PrintMatrix(dc, xout + 40, yout, *M.V1);
	dc.TextOut(xout, (yout += 120) + 32, "V2 = ");
	PrintMatrix(dc, xout + 40, yout, *M.V2);
	yout = 20;
	xout = 10;
	dc.TextOut(xout, yout - 15, "VectorMult");
	CMatrix Mult = VectorMult(*M.V1, *M.V2);
	PrintMatrix(dc, xout, yout, Mult);
	dc.TextOut(xout, (yout+=120) - 15, "ScalarMult");
	sprintf_s(t,"%3.2f",ScalarMult(*M.V1, *M.V2));
	dc.TextOut(xout, yout, t);
	dc.TextOut(xout, (yout +=65) - 15, "ModVec V1");
	dc.TextOut(xout+100, (yout) - 15, "ModVec V2");
	sprintf_s(t, "%f", ModVec(*M.V1));
	dc.TextOut(xout, yout, t);
	sprintf_s(t, "%f", ModVec(*M.V2));
	dc.TextOut(xout+100, yout, t);
	dc.TextOut(xout, (yout += 65) - 15, "CosV1V2");
	sprintf_s(t, "%f", CosV1V2(*M.V1,*M.V2));
	dc.TextOut(xout, yout, t);
	dc.TextOut(xout, (yout += 65) - 15, "—ферические");
	dc.TextOut(xout+185, yout - 15, "ƒекартовы");
	dc.TextOut(xout + 100, yout - 15, "->");
	CMatrix s(3);
	PrintMatrix(dc, xout, yout, s);
	PrintMatrix(dc, xout+185, yout, SphereToCart(s));
	dc.TextOut(xout + 100, yout+32, "->");
}
CMyApp theApp;