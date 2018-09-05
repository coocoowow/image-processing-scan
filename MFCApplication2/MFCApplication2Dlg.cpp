
// MFCApplication2Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include	"cv.h"
#include	"highgui.h"
#include	"CvvImage.h"	
#include "time.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace cv;
char *name;
CString szFileName;
// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	//void CMFCApplication2Dlg::DrawPicToHDC(IplImage *img, UINT ID);
	// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	// 程式碼實作
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


// CMFCApplication2Dlg 對話方塊


Mat log(const Mat &input)
{

	Mat gray = input.clone();
	cvtColor(input, gray, CV_BGR2GRAY);
	blur(gray, gray, Size(9, 9));
	Mat fg;
	gray.convertTo(fg, CV_32F);

	for (int h = 0; h < fg.rows; h++)
	{
		for (int w = 0; w < fg.cols; w++)
		{
			fg.at<float>(h, w) = pow(fg.at<float>(h, w), 0.8);

		}
	}

	normalize(fg, fg, 0, 255, NORM_MINMAX);
	convertScaleAbs(fg, fg);

	adaptiveThreshold(fg, fg, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 65, 0);



	//namedWindow("log", WINDOW_NORMAL);                            //創建視窗
	//resizeWindow("log", input.cols / 4, input.rows / 4);
	//imshow("log", fg);
	return fg;

}

double tt_tic=0;

void tic(){
	tt_tic = getTickCount();
}

double toc(){
	double tt_toc = (getTickCount() - tt_tic)/(getTickFrequency());
	printf ("toc: %4.3f sn", tt_toc);
	return tt_toc;
}




CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CMFCApplication2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication2Dlg::OnBnClickedButton4)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMFCApplication2Dlg::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 訊息處理常式

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication2Dlg::DrawPicToHDC(IplImage *img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID) -> GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(img);
	cimg.DrawToHDC(hDC, &rect);
	ReleaseDC(pDC);
}


void CMFCApplication2Dlg::OnBnClickedButton1()
{
	char szFilter[] = "jpg Files(*.jpg)|*.jpg|bin Files (*.bin)|*.bin|All Files (*.*)|*.*||";



	CFileDialog fileDlg(TRUE,"jpg", "*.jpg", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, NULL); 

	if(fileDlg.DoModal() == IDOK) //此時才談出對話框
	{ 

		szFileName = fileDlg.GetPathName();//取得開啟檔案全名(包含路徑) 

		name=szFileName.GetBuffer(0);


	}

}


void CMFCApplication2Dlg::OnBnClickedButton2()
{
	double nStart,nEnd ;

	nStart= clock(); //Start time

	int largest_area = 0;
	int largest_contour_index = 0;
	Rect bounding_rect;

	Mat src = imread(name); // Load source image
	Mat thr(src.rows, src.cols, CV_8UC1);
	Mat dst(src.rows, src.cols, CV_8UC3, Scalar::all(0));

	namedWindow("yyy", CV_WINDOW_NORMAL); // Show the source image
	imshow("yyy",src);

	cvtColor(src, thr, CV_BGR2GRAY); // Convert to gray
	//imwrite("cvtColor.jpg",thr);

	Mat happy;
	threshold(thr, thr, 80, 255, THRESH_BINARY|THRESH_OTSU ); // Threshold the gray
	//imwrite("threshold.jpg",thr);

	Mat erodeStruct = getStructuringElement(MORPH_RECT,Size(10,10)); // Do the morphological method
	erode(thr,thr,erodeStruct);
	erode(thr,thr,erodeStruct);
	dilate(thr,thr,erodeStruct);
	//imwrite("morphology.jpg",thr);

	vector<vector<Point>> contours; // Vector for storing contour
	vector<Vec4i> hierarchy;

	findContours(thr, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE); // Find the contours in the image

	for(int i = 0; i < contours.size(); i++) //  each contour
	{
		double a = contourArea(contours[i], false); // Find the area of contour
		if(a > largest_area){
			largest_area = a;
			largest_contour_index = i; // Store the index of largest contour
			bounding_rect = boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
		}
	}

	vector<vector<Point>> approxpoint(contours.size()); // Vector for storing contour
	approxPolyDP(contours[largest_contour_index],approxpoint[0],50,true); // Approximate the whole contours to rectangle's contours
	//approxpoint[0]=contours[largest_contour_index];
	Scalar color3(0,255,0); // Green
	drawContours(dst, approxpoint,0, color3, 5, 8, hierarchy); // Draw the largest contour using previously stored index.

	rectangle(src, bounding_rect, Scalar(0,255,0), 1, 8, 0);

	//imwrite("Largest_Contour.jpg",dst);

	double left_up=0;
	double	left_down=0,right_up=0,right_down=0,leftup=0,leftdown=0,rightup=0,rightdown=0;
	left_up = approxpoint[0][0].x + approxpoint[0][0].y;
	left_down = approxpoint[0][0].x - approxpoint[0][0].y;
	right_up = approxpoint[0][0].x - approxpoint[0][0].y;
	right_down = approxpoint[0][0].x + approxpoint[0][0].y;

	for(int i=0;i<approxpoint[0].size();i++)
	{
		if(approxpoint[0][i].x+approxpoint[0][i].y < left_up)//左上
		{
			left_up = approxpoint[0][i].x+approxpoint[0][i].y;
			leftup = i;
		}
		if(approxpoint[0][i].x-approxpoint[0][i].y < left_down)//左下
		{
			left_down = approxpoint[0][i].x-approxpoint[0][i].y;
			leftdown = i;
		}
		if(approxpoint[0][i].x-approxpoint[0][i].y > right_up)//右上
		{
			right_up = approxpoint[0][i].x-approxpoint[0][i].y;
			rightup = i;
		}
		if(approxpoint[0][i].x+approxpoint[0][i].y >right_down)//右下
		{
			right_down = approxpoint[0][i].x+approxpoint[0][i].y;
			rightdown = i;
		}
	}

//(左上,左下,右下,右上)
	Point2f pts1[] = {Point2f(approxpoint[0][leftup].x,approxpoint[0][leftup].y), Point2f(approxpoint[0][leftdown].x,approxpoint[0][leftdown].y), Point2f(approxpoint[0][rightdown].x,approxpoint[0][rightdown].y), Point2f(approxpoint[0][rightup].x,approxpoint[0][rightup].y)};
	Point2f pts2[] = {Point2f(0,0), Point2f(0,src.rows), Point2f(src.cols,src.rows), Point2f(src.cols,0)};
	
	Mat perspective_matrix = getPerspectiveTransform(pts1, pts2);
	Mat dst_img;
	// 變換
	warpPerspective(src, dst_img, perspective_matrix, src.size(), cv::INTER_LINEAR);
	namedWindow("dst_img",WINDOW_NORMAL);
	imshow("dst_img",dst_img);
	imwrite("dst_img.jpg",dst_img);

	nEnd= clock(); //End time
	double time;
	time=(nEnd-nStart)/CLOCKS_PER_SEC;
	CString str;

	str.Format(_T("%lf"),time);

	SetDlgItemText(IDC_EDIT1,str);
	waitKey(0);
}


void CMFCApplication2Dlg::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CDialogEx::OnOK();
}


void CMFCApplication2Dlg::OnBnClickedButton3(){
	double nStart,nEnd ;

	nStart= clock();
	int largest_area = 0;
	int largest_contour_index = 0;
	Rect bounding_rect;

	Mat src = imread(name); // Load source image
	Mat thr(src.rows, src.cols, CV_8UC1);
	Mat dst(src.rows, src.cols, CV_8UC3, Scalar::all(0));
	Mat test(src.rows,src.cols,CV_32FC1);

	namedWindow("yyy", CV_WINDOW_NORMAL); 
	imshow("yyy",src);

	thr= log(src);
//	imwrite("After_log.jpg",thr);

	int newthr_cols=(thr.cols)/10;
	int newthr_rows=(thr.rows)/10;
	int newthr_cols44=(thr.cols)*9/10;
	int newthr_rows44=(thr.rows)*9/10;
	rectangle(thr,Point(newthr_cols,newthr_rows),Point(newthr_cols44,newthr_rows44),Scalar(0,0,0),100);
	rectangle(thr,Point(thr.cols,thr.rows),Point(0,0),Scalar(0,0,0),250);

	vector<vector<Point>> contours; // Vector for storing contour
	vector<Vec4i> hierarchy;

	findContours(thr, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE); // Find the contours in the image

	for(int i = 0; i < contours.size(); i++) 
	{
		double a = contourArea(contours[i], false); // Find the area of contour
		if(a > largest_area)
		{
			largest_area = a;
			largest_contour_index = i; // Store the index of largest contour
			bounding_rect = boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
		}
	}

	vector<vector<Point>> approxpoint(contours.size()); // Vector for storing contour
	approxPolyDP(contours[largest_contour_index],approxpoint[0],10,true);

	Scalar color3(0,255,0);
	drawContours(dst, approxpoint,0, color3, 5, 8, hierarchy); // Draw the largest contour using previously stored index.
	//imwrite("Contours.jpg",dst);

	double left_up=0;
	double	left_down=0,right_up=0,right_down=0,leftup=0,leftdown=0,rightup=0,rightdown=0;
	left_up = approxpoint[0][0].x + approxpoint[0][0].y;
	left_down = approxpoint[0][0].x - approxpoint[0][0].y;
	right_up = approxpoint[0][0].x - approxpoint[0][0].y;
	right_down = approxpoint[0][0].x + approxpoint[0][0].y;

	for(int i=0;i<approxpoint[0].size();i++)
	{
		if(approxpoint[0][i].x+approxpoint[0][i].y < left_up)//左上
		{
			left_up = approxpoint[0][i].x+approxpoint[0][i].y;
			leftup = i;
		}
		if(approxpoint[0][i].x-approxpoint[0][i].y < left_down)//左下
		{
			left_down = approxpoint[0][i].x-approxpoint[0][i].y;
			leftdown = i;
		}
		if(approxpoint[0][i].x-approxpoint[0][i].y > right_up)//右上
		{
			right_up = approxpoint[0][i].x-approxpoint[0][i].y;
			rightup = i;
		}
		if(approxpoint[0][i].x+approxpoint[0][i].y >right_down)//右下
		{
			right_down = approxpoint[0][i].x+approxpoint[0][i].y;
			rightdown = i;
		}
	}

	//  (左上,左下,右下,右上)
	Point2f pts1[] = {Point2f(approxpoint[0][leftup].x,approxpoint[0][leftup].y), Point2f(approxpoint[0][leftdown].x,approxpoint[0][leftdown].y), Point2f(approxpoint[0][rightdown].x,approxpoint[0][rightdown].y), Point2f(approxpoint[0][rightup].x,approxpoint[0][rightup].y)};
	Point2f pts2[] = {Point2f(0,0), Point2f(0,src.rows), Point2f(src.cols,src.rows), Point2f(src.cols,0)};

	Mat perspective_matrix = getPerspectiveTransform(pts1, pts2);
	Mat dst_img;
	// 變換
	warpPerspective(src, dst_img, perspective_matrix, src.size(), cv::INTER_LINEAR);
	namedWindow("dst_img",WINDOW_NORMAL);
	imshow("dst_img",dst_img);
//	imwrite("dst_img.jpg",dst_img);

	nEnd= clock(); 
	double time;
	time=(nEnd-nStart)/CLOCKS_PER_SEC;
	CString str;

	str.Format(_T("%lf"),time);

	SetDlgItemText(IDC_EDIT1,str);

	waitKey(0);
}




void CMFCApplication2Dlg::OnBnClickedButton4()
{
	double nStart, nEnd;

	nStart= clock();

	int largest_area = 0;
	int largest_contour_index = 0;
	Rect bounding_rect;

	Mat src = imread(name); // Load source image
	Mat thr(src.rows, src.cols, CV_8UC1);
	Mat dst(src.rows, src.cols, CV_8UC3, Scalar::all(0));
	Mat test(src.rows,src.cols,CV_32FC1);

	namedWindow("yyy", CV_WINDOW_NORMAL); 
	imshow("yyy",src);

	thr= log(src);
	//imwrite("After_log.jpg",thr);

	int newthr_cols=(thr.cols)/10;
	int newthr_rows=(thr.rows)/10;
	int newthr_cols44=(thr.cols)*9/10;
	int newthr_rows44=(thr.rows)*9/10;

	rectangle(thr,Point(thr.cols,thr.rows),Point(0,0),Scalar(0,0,0),250);

	vector<vector<Point>> contours; // Vector for storing contour
	vector<Vec4i> hierarchy;


	findContours(thr, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE); // Find the contours in the image

	Scalar color(0,0,255);


	for(int i = 0; i < contours.size(); i++) 
	{

		double a = contourArea(contours[i], false); // Find the area of contour
		if(a > largest_area){
			largest_area = a;
			largest_contour_index = i; // Store the index of largest contour
			bounding_rect = boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
		}
	}
	vector<vector<Point>> approxpoint(contours.size()); // Vector for storing contour
	approxPolyDP(contours[largest_contour_index],approxpoint[0],10,true);


	double left_up=0;
	double	left_down=0,right_up=0,right_down=0,leftup=0,leftdown=0,rightup=0,rightdown=0;
	left_up = approxpoint[0][0].x + approxpoint[0][0].y;
	left_down = approxpoint[0][0].x - approxpoint[0][0].y;
	right_up = approxpoint[0][0].x - approxpoint[0][0].y;
	right_down = approxpoint[0][0].x + approxpoint[0][0].y;

	for(int i=0;i<approxpoint[0].size();i++)
	{
		if(approxpoint[0][i].x+approxpoint[0][i].y < left_up)//左上
		{
			left_up = approxpoint[0][i].x+approxpoint[0][i].y;
			leftup = i;
		}
		if(approxpoint[0][i].x-approxpoint[0][i].y < left_down)//左下
		{
			left_down = approxpoint[0][i].x-approxpoint[0][i].y;
			leftdown = i;
		}
		if(approxpoint[0][i].x-approxpoint[0][i].y > right_up)//右上
		{
			right_up = approxpoint[0][i].x-approxpoint[0][i].y;
			rightup = i;
		}
		if(approxpoint[0][i].x+approxpoint[0][i].y >right_down)//右下
		{
			right_down = approxpoint[0][i].x+approxpoint[0][i].y;
			rightdown = i;
		}
	}

	Scalar color3(0,255,0);
	drawContours(dst, approxpoint,0, color3, 5, 8, hierarchy); // Draw the largest contour using previously stored index.
	//imwrite("Contours.jpg",dst);

	//  (左上,左下,右下,右上)
	Point2f pts1[] = {Point2f(approxpoint[0][leftup].x,approxpoint[0][leftup].y), Point2f(approxpoint[0][leftdown].x,approxpoint[0][leftdown].y), Point2f(approxpoint[0][rightdown].x,approxpoint[0][rightdown].y), Point2f(approxpoint[0][rightup].x,approxpoint[0][rightup].y)};
	Point2f pts2[] = {Point2f(0,0), Point2f(0,src.rows), Point2f(src.cols,src.rows), Point2f(src.cols,0)};

	Mat perspective_matrix = getPerspectiveTransform(pts1, pts2);
	Mat dst_img;
	// 變換
	warpPerspective(src, dst_img, perspective_matrix, src.size(), cv::INTER_LINEAR);
	namedWindow("dst_img",WINDOW_NORMAL);
	imshow("dst_img",dst_img);
	//imwrite("dst_img.jpg",dst_img);
	nEnd= clock(); 
	double time;
	time=(nEnd-nStart)/CLOCKS_PER_SEC;
	CString str;

	str.Format(_T("%lf"),time);

	SetDlgItemText(IDC_EDIT1,str);

	waitKey(0);
}

void CMFCApplication2Dlg::OnLbnSelchangeList2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}