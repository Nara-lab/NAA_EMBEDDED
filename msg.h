#include <afxwin.h>

class mydialog:public CDialog
{
public:
	mydialog();
	mydialog(int id);
	BOOL OnInitDialog();
	void DoDataExchange(CDataExchange* pDX);
	BOOL PreTranslateMessage(MSG *msg);
	void func();

	CString str1;
	CString str2;
	DECLARE_MESSAGE_MAP()
};

class myapp:public CWinApp
{
public:
BOOL InitInstance();
};
