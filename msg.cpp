#include "Msg.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(mydialog,CDialog)
END_MESSAGE_MAP()
mydialog::mydialog()
{}
mydialog::mydialog(int id):CDialog(id)
{}

BOOL mydialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}


void mydialog::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX,IDC_EDIT1,str1);
	DDX_Text(pDX,IDC_EDIT2,str2);
}

BOOL myapp::InitInstance()
{
	mydialog d(IDD_DIALOG1);
	m_pMainWnd = &d;
	d.DoModal();
	return FALSE;
}

BOOL mydialog::PreTranslateMessage(MSG* msg)
{
	if(msg ->message == WM_CHAR && msg ->wParam == VK_RETURN)
	{
		int ctrlid = this ->GetFocus()->GetDlgCtrlID();
		if(ctrlid == IDC_EDIT1)
		{
			UpdateData();
			str2 = str1;
			str1 = _T("");
			UpdateData(FALSE);
		}
	}
	return FALSE;
}
