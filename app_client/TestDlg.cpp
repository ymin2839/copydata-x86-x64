#include "pch.h"
#include "framework.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include <string>

#include "DefineStruct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTestDlg::CTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_DIALOG, pParent)
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, OnOK)
	ON_BN_CLICKED(ID_DATASIZE, OnDataSize)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(L"client");	

	CenterWindow();

	CRect rect;
	GetWindowRect(rect);
	rect.OffsetRect(100, 0);
	MoveWindow(rect);

	return TRUE;
}

void CTestDlg::OnOK()
{
	STDATA data;
	sprintf_s(data.str1, "from client");
	swprintf_s(data.str2, L"to server");
	data.num1 = 11;
	data.num2 = 22;
	data.num3 = 33;
	//data.num4 = 44;

	HWND hwnd = ::FindWindow(NULL, L"server");
	if (hwnd)
	{
		COPYDATASTRUCT cdata;
		cdata.dwData = 0x0202;
		cdata.cbData = sizeof(STDATA);
		cdata.lpData = (void*)&data;

		PDWORD_PTR lpdwResult = 0;
		::SendMessageTimeout(hwnd, WM_COPYDATA, (WPARAM)this, (LPARAM)&cdata, SMTO_NORMAL, 1000, lpdwResult);
		if (ERROR_SUCCESS != GetLastError())
		{
			TRACE(L"TimeOut");
		}
	}
	else
	{
		AfxMessageBox(L"not find server");
	}

	return;
}

BOOL CTestDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	STDATA* data = (STDATA*)pCopyDataStruct->lpData;
	
	
	std::string		str1 = data->str1;
	CString			str2 = data->str2;
	int				num1 = data->num1;
	DWORD			num2 = data->num2;
	UINT_PTR		num3 = data->num3;
	UINT			num4 = data->num4;

	std::wstring	_str1;
	_str1.assign(str1.begin(), str1.end());
	

	CString msg;
	msg.AppendFormat(L"size:%d", sizeof(STDATA));
	msg.AppendFormat(L" %s", _str1.c_str());
	msg.AppendFormat(L" %s", str2);
	msg.AppendFormat(L" %d", num1);
	msg.AppendFormat(L" %d", num2);
	msg.AppendFormat(L" %d", num3);
	msg.AppendFormat(L" %d", num4);
	AfxMessageBox(msg);

	return TRUE;
}

void CTestDlg::OnDataSize()
{
	CString msg;
	msg.AppendFormat(L"stdata size : %d", sizeof(STDATA));	
	msg.AppendFormat(L"\n char size : %d", sizeof(char));
	msg.AppendFormat(L"\n WCHAR size : %d", sizeof(WCHAR));
	msg.AppendFormat(L"\n char* size : %d", sizeof(char*));
	msg.AppendFormat(L"\n WCHAR* size : %d", sizeof(WCHAR*));
	msg.AppendFormat(L"\n int size : %d", sizeof(int));
	msg.AppendFormat(L"\n DWORD size : %d", sizeof(DWORD));
	msg.AppendFormat(L"\n UINT_PTR size : %d", sizeof(UINT_PTR));
	msg.AppendFormat(L"\n UINT size : %d", sizeof(UINT));
	AfxMessageBox(msg);
}