
// MFCApplication2Dlg.h : ���Y��
//

#pragma once
#include	"cv.h"
#include	"highgui.h"
#include	"CvvImage.h"



// CMFCApplication2Dlg ��ܤ��
class CMFCApplication2Dlg : public CDialogEx
{
// �غc
public:
	CMFCApplication2Dlg(CWnd* pParent = NULL);	// �зǫغc�禡
	void CMFCApplication2Dlg::DrawPicToHDC(IplImage *img, UINT ID);
// ��ܤ�����
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedButton5();
};
