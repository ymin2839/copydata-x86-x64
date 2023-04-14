#pragma once


class CTestDlg : public CDialogEx
{
public:
	CTestDlg(CWnd* pParent = nullptr);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);


protected:
	virtual BOOL OnInitDialog();

	afx_msg void OnOK();
	afx_msg void OnDataSize();

	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

	DECLARE_MESSAGE_MAP()
};
