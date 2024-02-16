/*******************************************************************************************************************
Purpose: 
This program is a simplified version of the bitwise calculator and it was developed by using GUI.


Author: Taner Giray Sonmez

Date: 24/12/2021

Any known bugs: No known bugs
******************************************************************************************************************/



// taners_Sonmez_Taner_HW6Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "taners_Sonmez_Taner_HW6.h"
#include "taners_Sonmez_Taner_HW6Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

//Global variable for keeping track of which radio button is selected, initially, it is "AND".
CString BitwiseOperator= _T("AND");

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ctaners_Sonmez_Taner_HW6Dlg dialog



Ctaners_Sonmez_Taner_HW6Dlg::Ctaners_Sonmez_Taner_HW6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctaners_Sonmez_Taner_HW6Dlg::IDD, pParent)
	, groupedRadio(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctaners_Sonmez_Taner_HW6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, shiftingCombo); //Combo list that contains "right" and "left".
	DDX_Radio(pDX, IDC_RADIO1, groupedRadio); //Grouped radio buttons for picking bitwise operation.
	DDX_Control(pDX, IDC_CHECK1, checkboxShifting); //Checkbox for deciding whether there is a shift.
	DDX_Control(pDX, IDC_EDIT1, operand1);
	DDX_Control(pDX, IDC_EDIT2, operand2);
	DDX_Control(pDX, IDC_EDIT3, shiftingInput);//A Number of shifting.
	DDX_Control(pDX, IDC_LIST1, resultList); //Listbox for printing results.
}

BEGIN_MESSAGE_MAP(Ctaners_Sonmez_Taner_HW6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &Ctaners_Sonmez_Taner_HW6Dlg::OnBnClickedRadio1)//"AND" Radio Button.
	ON_BN_CLICKED(IDC_CHECK1, &Ctaners_Sonmez_Taner_HW6Dlg::OnBnClickedCheck1)//"Shift" Checkbox.
ON_BN_CLICKED(IDC_BUTTON1, &Ctaners_Sonmez_Taner_HW6Dlg::OnBnClickedButton1) //"Compute" Button.
ON_BN_CLICKED(IDC_RADIO2, &Ctaners_Sonmez_Taner_HW6Dlg::OnBnClickedRadio2)//"OR" Radio Button.
ON_BN_CLICKED(IDC_RADIO3, &Ctaners_Sonmez_Taner_HW6Dlg::OnBnClickedRadio3)//"XOR" Radio Button.
END_MESSAGE_MAP()


// Ctaners_Sonmez_Taner_HW6Dlg message handlers

BOOL Ctaners_Sonmez_Taner_HW6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	shiftingCombo.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Ctaners_Sonmez_Taner_HW6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Ctaners_Sonmez_Taner_HW6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Ctaners_Sonmez_Taner_HW6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//If the first radio button is selected, this function changes the global variable as a "AND".
void Ctaners_Sonmez_Taner_HW6Dlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	BitwiseOperator=_T("AND");
}

//For enabling and disabling desired tools such as ComboBox and Edit Text for "Bits to shift".
void Ctaners_Sonmez_Taner_HW6Dlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	if (checkboxShifting.GetCheck())
	{
		shiftingCombo.EnableWindow(TRUE);
		shiftingInput.EnableWindow(TRUE);
	}
	else
	{
		shiftingCombo.EnableWindow(FALSE);
		shiftingInput.EnableWindow(FALSE);
	}
}



//Keeping size of the string which have maximum length for extending horizontal scrollbar.
int maxSize =0;

//This function computes necessary calculations and lists them when the "Compute" button is clicked.
void Ctaners_Sonmez_Taner_HW6Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CDC *pDC  = GetDC();
	CFont *pOldFont = pDC->SelectObject(GetFont());
	CSize cz;
	unsigned int data1,data2;
	CString lhs,rhs,directionOfShifting,timesOfShifting,resultString,resultData,warning;
	operand1.GetWindowTextW(lhs);//lhs is left hand side, i.e operand1.
	operand2.GetWindowTextW(rhs);//rhs is right hand side, i.e operand2.
	data1 = _tcstoul(lhs,nullptr,10);
	data2 = _tcstoul(rhs,nullptr,10);

	if (checkboxShifting.GetCheck())//If there is a shift.
	{
		shiftingCombo.GetWindowTextW(directionOfShifting);
		shiftingInput.GetWindowTextW(timesOfShifting);
		if(timesOfShifting.GetLength() > 0 && (!lhs.GetLength()>0 || !rhs.GetLength()>0))
		{
			resultList.AddString(_T("At least 1 operand was not entered."));
			warning = _T("At least 1 operand was not entered.");
		}	
		else if (!timesOfShifting.GetLength() > 0 && (lhs.GetLength()>0 && rhs.GetLength()>0))
		{
			resultList.AddString(_T("Specify how many bits you want to shift."));
			warning =_T("Specify how many bits you want to shift.");
		}
		else if(!timesOfShifting.GetLength() > 0 && (!lhs.GetLength()>0 && !rhs.GetLength()>0))
		{
			resultList.AddString(_T("At least 1 operand was not entered."));
			warning =_T("At least 1 operand was not entered.");
		}
		else if (!timesOfShifting.GetLength() > 0 && (!lhs.GetLength()>0 && rhs.GetLength()>0))
		{
			resultList.AddString(_T("At least 1 operand was not entered."));
			warning =_T("At least 1 operand was not entered.");
		}
		else if (!timesOfShifting.GetLength() > 0 && (lhs.GetLength()>0 && !rhs.GetLength()>0))
		{
			resultList.AddString(_T("At least 1 operand was not entered."));
			warning =_T("At least 1 operand was not entered.");
		}
		else//Calculations are starting.
		{
			int shiftingAmount = _ttoi(timesOfShifting);
			if (directionOfShifting==_T("Left"))//Shifting to left.
			{
				data1= (data1 << shiftingAmount);
				data2= (data2 << shiftingAmount);
			}
			else if (directionOfShifting==_T("Right"))//Shifting to right.
			{
				data1= (data1 >> shiftingAmount);
				data2= (data2 >> shiftingAmount);	
			}
			if (BitwiseOperator==_T("AND"))
			{
				resultData.Format(_T("%u"),data1&data2);
				lhs.Format(_T("%u"),data1);
				rhs.Format(_T("%u"),data2);
				resultString = lhs + _T(" AND ")+ rhs + _T(" = ")+resultData;
				resultList.AddString(resultString);

			}
			else if (BitwiseOperator==_T("OR"))
			{
				resultData.Format(_T("%u"),data1|data2);
				lhs.Format(_T("%u"),data1);
				rhs.Format(_T("%u"),data2);
				resultString = lhs + _T(" OR ")+ rhs + _T(" = ")+resultData;
				resultList.AddString(resultString);
			}
			else if (BitwiseOperator==_T("XOR"))
			{
				resultData.Format(_T("%u"),data1^data2);
				lhs.Format(_T("%u"),data1);
				rhs.Format(_T("%u"),data2);
				resultString = lhs + _T(" XOR ")+ rhs + _T(" = ")+resultData;
				resultList.AddString(resultString);
			}
			//Extending horizontal bar for calculations.
			cz = pDC->GetTextExtent(resultString);
			if(cz.cx > maxSize)
				maxSize = cz.cx;
			resultList.SetHorizontalExtent(maxSize+4);
		}
		//Extending horizontal bar for error messages.
		cz = pDC->GetTextExtent(warning);
		if(cz.cx > maxSize)
			maxSize = cz.cx;
		resultList.SetHorizontalExtent(maxSize+4);
	}
	else //If there is no shift.
	{
		if(!lhs.GetLength()>0 || !rhs.GetLength()>0)
		{
			resultList.AddString(_T("At least 1 operand was not entered."));
			warning =_T("At least one operand 1 not entered.");
			cz = pDC->GetTextExtent(warning);
			if(cz.cx > maxSize)
				maxSize = cz.cx;
			resultList.SetHorizontalExtent(maxSize+4);
		}
		else//Calculations are starting.
		{
			if (BitwiseOperator==_T("AND"))
			{
				resultData.Format(_T("%u"),data1&data2);
				lhs.Format(_T("%u"),data1);
				rhs.Format(_T("%u"),data2);
				resultString = lhs + _T(" AND ")+ rhs + _T(" = ")+resultData;
				resultList.AddString(resultString);
			}
			else if (BitwiseOperator==_T("OR"))
			{
				resultData.Format(_T("%u"),data1|data2);
				lhs.Format(_T("%u"),data1);
				rhs.Format(_T("%u"),data2);
				resultString = lhs + _T(" OR ")+ rhs + _T(" = ")+resultData;
				resultList.AddString(resultString);

			}
			else if (BitwiseOperator==_T("XOR"))
			{
				resultData.Format(_T("%u"),data1^data2);
				lhs.Format(_T("%u"),data1);
				rhs.Format(_T("%u"),data2);
				resultString = lhs + _T(" XOR ")+ rhs + _T(" = ")+resultData;
				resultList.AddString(resultString);
			}

			//Extending horizontal bar.
			cz = pDC->GetTextExtent(resultString);
			if(cz.cx > maxSize)
				maxSize = cz.cx;
			resultList.SetHorizontalExtent(maxSize+4);
		}
	}
}

//If the second radio button is selected, this function changes the global variable as a "OR".
void Ctaners_Sonmez_Taner_HW6Dlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	BitwiseOperator=_T("OR");
}

//If the third radio button is selected, this function changes the global variable as a "XOR".
void Ctaners_Sonmez_Taner_HW6Dlg::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
	BitwiseOperator=_T("XOR");
}
