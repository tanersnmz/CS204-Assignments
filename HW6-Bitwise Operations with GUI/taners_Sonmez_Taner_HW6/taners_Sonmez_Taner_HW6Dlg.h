
// taners_Sonmez_Taner_HW6Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Ctaners_Sonmez_Taner_HW6Dlg dialog
class Ctaners_Sonmez_Taner_HW6Dlg : public CDialogEx
{
// Construction
public:
	Ctaners_Sonmez_Taner_HW6Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TANERS_SONMEZ_TANER_HW6_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox shiftingCombo;
	afx_msg void OnBnClickedRadio1();
	int groupedRadio;
	CButton checkboxShifting;
	afx_msg void OnBnClickedCheck1();
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton1();
	CEdit operand1;
	CEdit operand2;
	CEdit shiftingInput;
	CListBox resultList;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnLbnSelchangeList1();
};
