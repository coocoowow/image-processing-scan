
// MFCApplication2Dlg.h : 標頭檔
//

#pragma once
#include	"cv.h"
#include	"highgui.h"
#include	"CvvImage.h"



// CMFCApplication2Dlg 對話方塊
class CMFCApplication2Dlg : public CDialogEx
{
// 建構
public:
	CMFCApplication2Dlg(CWnd* pParent = NULL);	// 標準建構函式
	void CMFCApplication2Dlg::DrawPicToHDC(IplImage *img, UINT ID);
// 對話方塊資料
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
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
