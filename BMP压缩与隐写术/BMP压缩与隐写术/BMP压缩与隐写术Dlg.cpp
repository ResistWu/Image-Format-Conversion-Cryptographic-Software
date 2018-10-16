#pragma once
// BMP压缩与隐写术Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BMP压缩与隐写术.h"
#include "BMP压缩与隐写术Dlg.h"
#include "afxdialogex.h"
#include "time.h"
#include "Run.h"
#include "huff.h"
#include "Secret.h"
#include "md5.h"
#include "wavelet.h"
#include "ezw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBMP压缩与隐写术Dlg 对话框



CBMP压缩与隐写术Dlg::CBMP压缩与隐写术Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBMP压缩与隐写术Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBMP压缩与隐写术Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, m_check1, c_check1);
	DDX_Control(pDX, m_txt1, c_txt1);
	DDX_Control(pDX, m_pic, c_pic);
	DDX_Control(pDX, txt2, c_txt2);
	DDX_Control(pDX, m_ckeck2, c_ckeck2);
	DDX_Control(pDX, m_txt2, c_txt3);
	//DDX_Control(pDX, m_check3, c_ckeck3);
	//DDX_Control(pDX, m_radio, c_radio);
	//DDX_Control(pDX, IDCANCEL, c_radio2);
	DDX_Control(pDX, m_ckeck5, c_ckeck5);
	DDX_Control(pDX, m_ckeck6, c_ckeck6);
	DDX_Control(pDX, m_sta1, c_sta1);
}

BEGIN_MESSAGE_MAP(CBMP压缩与隐写术Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(m_check1, &CBMP压缩与隐写术Dlg::OnBnClickedcheck1)
	ON_STN_CLICKED(m_pic, &CBMP压缩与隐写术Dlg::OnStnClickedpic)
	//ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CBMP压缩与隐写术Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CBMP压缩与隐写术Dlg::OnBnClickedOk)
	ON_BN_CLICKED(m_ckeck2, &CBMP压缩与隐写术Dlg::OnBnClickedckeck2)
	//ON_BN_CLICKED(m_check3, &CBMP压缩与隐写术Dlg::OnBnClickedcheck3)
	ON_BN_CLICKED(m_ckeck5, &CBMP压缩与隐写术Dlg::OnBnClickedckeck5)
	ON_BN_CLICKED(m_ckeck6, &CBMP压缩与隐写术Dlg::OnBnClickedckeck6)
	ON_BN_CLICKED(IDCANCEL, &CBMP压缩与隐写术Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CBMP压缩与隐写术Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyStatic, CStatic)

	ON_WM_DROPFILES()

END_MESSAGE_MAP()


// CBMP压缩与隐写术Dlg 消息处理程序

BOOL CBMP压缩与隐写术Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	
	c_pic.DragAcceptFiles(TRUE);
	c_txt1.EnableWindow(FALSE);
	c_txt3.EnableWindow(FALSE);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBMP压缩与隐写术Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBMP压缩与隐写术Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBMP压缩与隐写术Dlg::OnBnClickedcheck1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (c_check1.GetCheck() == TRUE){
		c_txt1.EnableWindow(TRUE);
		c_ckeck2.EnableWindow(FALSE);
		c_ckeck5.EnableWindow(FALSE);
		c_ckeck6.EnableWindow(FALSE);
		c_txt3.EnableWindow(FALSE);
		c_ckeck2.SetCheck(FALSE);
		c_ckeck5.SetCheck(FALSE);
		c_ckeck6.SetCheck(FALSE);

	}
	else{
		c_txt1.EnableWindow(FALSE);
		c_ckeck2.EnableWindow(TRUE);
		c_ckeck5.EnableWindow(TRUE);
		c_ckeck6.EnableWindow(TRUE);
		
		//c_txt3.EnableWindow(TRUE);
	}
}


void CBMP压缩与隐写术Dlg::OnStnClickedpic()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CMyStatic::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	MessageBox(_T("777"));
	int cx, cy;
	CRect   rect;
	int nFileCount = DragQueryFile(hDropInfo, -1, NULL, 0);
	TCHAR *strFilePath;
	int dwSize;
	if (nFileCount == 1)
	{
		dwSize = DragQueryFile(hDropInfo, 0, NULL, 0);
		strFilePath = new TCHAR[dwSize + 1];
		if (strFilePath)
		{
			DragQueryFile(hDropInfo, 0, strFilePath, dwSize + 1);
			CImage  image;
			//Retrieves the names of dropped files that result from a successful drag-and-drop operation.
			//Do sth to prove succeed
			image.Load(strFilePath);
			
			//获取图片的宽 高度  
			cx = image.GetWidth();
			cy = image.GetHeight();
			//获取Picture Control控件的大小  
			c_pic.GetWindowRect(&rect);
			//将客户区选中到控件表示的矩形区域内  
			ScreenToClient(&rect);
			//窗口移动到控件表示的区域  
			//c_pic.MoveWindow(rect.left, rect.top, cx, cy, TRUE);
			
			
			c_pic.GetClientRect(&rect);//获取句柄指向控件区域的大小  

			CDC *pDc = NULL;
			pDc = c_pic.GetDC();//获取picture的DC  

			image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
			ReleaseDC(pDc);
			delete[]strFilePath;
		}
	}
	
	DragFinish(hDropInfo);
	//Invalidate();
	CStatic::OnDropFiles(hDropInfo);
	
}

CString CBMP压缩与隐写术Dlg::BootOpenDialog()
{
	CString strFile = _T("");

	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Bmp (*.bmp)|*.bmp|Zmf (*.zmf)|*.zmf|EZW (*.ezw)|*.ezw||"), NULL);

	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
	}

	return strFile;
}
void CBMP压缩与隐写术Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CString fpath;
	fpath = BootOpenDialog();
	if (fpath != _T("")){
		strFilePath = fpath;
	}
	//strFilePath = _T("");
	int cx, cy;
	CRect rect;
	//strFilePath = BootOpenDialog();
	if (strFilePath != _T("")){
		CBMP压缩与隐写术App *app = (CBMP压缩与隐写术App*)AfxGetApp();
		c_txt2.SetWindowTextW(strFilePath);

		if (strFilePath.Right(4)==_T(".bmp"))
		{
			c_check1.EnableWindow(TRUE);
			//c_txt1.EnableWindow(TRUE);
			c_ckeck2.EnableWindow(TRUE);
			c_ckeck5.EnableWindow(TRUE);
			c_ckeck6.EnableWindow(TRUE);
			c_ckeck2.SetCheck(FALSE);
			c_ckeck5.SetCheck(FALSE);
			c_ckeck6.SetCheck(FALSE);
			c_txt3.SetWindowTextW(NULL);
			c_txt1.SetWindowTextW(NULL);
			app->flag = 0;
			CImage  image;
			//Retrieves the names of dropped files that result from a successful drag-and-drop operation.
			//Do sth to prove succeed
			image.Load(strFilePath);

			//获取图片的宽 高度  
			cx = image.GetWidth();
			cy = image.GetHeight();
			//获取Picture Control控件的大小  
			c_pic.GetWindowRect(&rect);
			//将客户区选中到控件表示的矩形区域内  
			ScreenToClient(&rect);
			//窗口移动到控件表示的区域  
			//c_pic.MoveWindow(rect.left, rect.top, cx, cy, TRUE);

			c_pic.GetClientRect(&rect);//获取句柄指向控件区域的大小  

			CDC *pDc = NULL;
			pDc = c_pic.GetDC();//获取picture的DC  
			pDc->SetStretchBltMode(COLORONCOLOR);
			image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
			ReleaseDC(pDc);
			//delete[]strFilePath;
		}
		else{
			c_check1.EnableWindow(FALSE);
			c_txt1.EnableWindow(FALSE);
			c_ckeck2.EnableWindow(FALSE);
			c_ckeck5.EnableWindow(FALSE);
			c_ckeck6.EnableWindow(FALSE);
			c_ckeck2.SetCheck(FALSE);
			c_ckeck5.SetCheck(FALSE);
			c_ckeck6.SetCheck(FALSE);
			c_txt3.SetWindowTextW(NULL);
			c_txt1.SetWindowTextW(NULL);
			
			CFile file(strFilePath, CFile::modeRead);
			BYTE flag;
			file.Read(&flag, 1);
			file.Close();
			app->flag = flag;
			if (flag % 2 == 1){
				c_txt3.EnableWindow(TRUE);
				CImage  image;
				CRect rect;
				image.Load(_T("密码.bmp"));
				//获取图片的宽 高度  
				int cx = image.GetWidth();
				int cy = image.GetHeight();
				//获取Picture Control控件的大小  
				c_pic.GetWindowRect(&rect);
				//将客户区选中到控件表示的矩形区域内  
				ScreenToClient(&rect);
				//窗口移动到控件表示的区域  
				//c_pic.MoveWindow(rect.left, rect.top, cx, cy, TRUE);
				c_pic.GetClientRect(&rect);//获取句柄指向控件区域的大小  
				CDC *pDc = NULL;
				pDc = c_pic.GetDC();//获取picture的DC  
				pDc->SetStretchBltMode(COLORONCOLOR);
				image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
				ReleaseDC(pDc);
			}
			else{
				c_txt3.EnableWindow(FALSE);
				CImage  image;
				CRect rect;
				image.Load(_T("解压.bmp"));
				//获取图片的宽 高度  
				int cx = image.GetWidth();
				int cy = image.GetHeight();
				//获取Picture Control控件的大小  
				c_pic.GetWindowRect(&rect);
				//将客户区选中到控件表示的矩形区域内  
				ScreenToClient(&rect);
				//窗口移动到控件表示的区域  
				//c_pic.MoveWindow(rect.left, rect.top, cx, cy, TRUE);
				c_pic.GetClientRect(&rect);//获取句柄指向控件区域的大小  
				CDC *pDc = NULL;
				pDc = c_pic.GetDC();//获取picture的DC  
				pDc->SetStretchBltMode(COLORONCOLOR);
				image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
				ReleaseDC(pDc);
			}
		}
	}


}


void CBMP压缩与隐写术Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CBMP压缩与隐写术App *app = (CBMP压缩与隐写术App*)AfxGetApp();


	int x, y, size;
	clock_t t1, t2;
	CBitmap BitMap; BITMAP pBitMap;
	CString filepath;
	c_txt2.GetWindowTextW(filepath);
	//c_check1.SetCheck(FALSE);
	int a; CString s;
	if (strFilePath != _T("")){
		c_sta1.SetWindowTextW(NULL);
		if (strFilePath.Right(4) == _T(".bmp")){
			app->flag = 0;
			Huff huffr; Huff huffg; Huff huffb; //Huff huffa;
			//CBitmap BitMap;
			BitMap.Attach(LoadImage(0, strFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
			//BITMAP pBitMap;
			BitMap.GetBitmap(&pBitMap);
			app->bmpdata = new BYTE[pBitMap.bmWidthBytes * pBitMap.bmHeight];
			app->rdata = new BYTE[pBitMap.bmWidth * pBitMap.bmHeight];
			app->gdata = new BYTE[pBitMap.bmWidth * pBitMap.bmHeight];
			app->bdata = new BYTE[pBitMap.bmWidth * pBitMap.bmHeight];
			app->adata = new BYTE[pBitMap.bmWidth * pBitMap.bmHeight];
			BitMap.GetBitmapBits(pBitMap.bmWidthBytes * pBitMap.bmHeight, app->bmpdata);
			for (int i = 0; i < pBitMap.bmWidth*pBitMap.bmHeight; i++){
				app->rdata[i] = app->bmpdata[4 * i + 2];
				app->gdata[i] = app->bmpdata[4 * i + 1];
				app->bdata[i] = app->bmpdata[4 * i + 0];
				app->adata[i] = app->bmpdata[4 * i + 3];
			}
			CFile headfile(strFilePath, CFile::modeRead);
			app->bmphead = new BYTE[54];
			headfile.Read(app->bmphead, 54);//获取信息头
			headfile.Close();
			if (c_check1.GetCheck()){
				CString msg;
				c_txt1.GetWindowTextW(msg);
				Secret yx(pBitMap.bmWidth, pBitMap.bmHeight);
				yx.yinxie(msg);
				for (int i = 0; i < pBitMap.bmWidth*pBitMap.bmHeight; i++){
					app->bmpdata[4 * i + 2] = app->rdata[i];
					app->bmpdata[4 * i + 1] = app->gdata[i];
					app->bmpdata[4 * i + 0] = app->bdata[i];
					app->bmpdata[4 * i + 3] = app->adata[i];
				}

				CWindowDC dc(this);
				CBitmap myBitmap;
				CDC myDC;
				myDC.CreateCompatibleDC(&dc);
				myBitmap.CreateCompatibleBitmap(&dc, pBitMap.bmWidth, pBitMap.bmHeight);
				myBitmap.SetBitmapBits(pBitMap.bmWidth*pBitMap.bmHeight * 4, app->bmpdata);
				CImage imgTemp;
				imgTemp.Attach(myBitmap);
				imgTemp.Save(strFilePath + _T("_隐写.bmp"));
				MessageBox(_T("隐写完成"));

			}
			if (c_ckeck2.GetCheck()){
				CString word; unsigned char *password;
				c_txt3.GetWindowTextW(word);
				DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, word, -1, NULL, NULL, 0, NULL);
				password = new unsigned char[dwNum];
				WideCharToMultiByte(CP_OEMCP, NULL, word, -1, (LPSTR)password, dwNum, 0, NULL);
				MD5 en;
				app->md5code = new BYTE[16];
				app->md5code = en.encode(password);
				app->flag += 1;

			}
			else{
				for (int i = 0; i < 16; i++){
					app->md5code = new BYTE[16];
					app->md5code[i] = 0;
				}
			}
			if (c_ckeck5.GetCheck()){
				ULONGLONG f1size, f2size;

				t1 = clock();

				Run run(pBitMap);
				x = run.bmpx; y = run.bmpy; size = run.bmpsize;



				unsigned int * code_r = huffr.HuffmanCode(app->rdata, pBitMap.bmWidth * pBitMap.bmHeight);
				unsigned int * code_g = huffg.HuffmanCode(app->gdata, pBitMap.bmWidth * pBitMap.bmHeight);
				unsigned int * code_b = huffb.HuffmanCode(app->bdata, pBitMap.bmWidth * pBitMap.bmHeight);
				//unsigned int * code_a = huffa.HuffmanCode(app->adata, pBitMap.bmWidth * pBitMap.bmHeight);

				app->codelist_r = (CodeListUnit *)malloc(sizeof(CodeListUnit) * 256);
				app->codelist_g = (CodeListUnit *)malloc(sizeof(CodeListUnit) * 256);
				app->codelist_b = (CodeListUnit *)malloc(sizeof(CodeListUnit) * 256);

				for (int i = 0; i < 256; i++){
					app->codelist_r[i].top = huffr.code_list[i].top;
					for (int j = 0; j < 256; j++){
						app->codelist_r[i].code[j] = huffr.code_list[i].code[j];
					}
				}
				for (int i = 0; i < 256; i++){
					app->codelist_g[i].top = huffg.code_list[i].top;
					for (int j = 0; j < 256; j++){
						app->codelist_g[i].code[j] = huffg.code_list[i].code[j];
					}
				}
				for (int i = 0; i < 256; i++){
					app->codelist_b[i].top = huffb.code_list[i].top;
					for (int j = 0; j < 256; j++){
						app->codelist_b[i].code[j] = huffb.code_list[i].code[j];
					}
				}
				app->flag += 2;

				CFile file(strFilePath + _T(".zmf"), CFile::modeCreate | CFile::modeWrite);
				file.Write(&(app->flag), 1);
				file.Write(app->md5code, 16);
				file.Write(app->bmphead, 54);
				file.Write(&huffr.ll, sizeof(int));
				file.Write(&huffr.y, sizeof(int));
				file.Write(&huffg.ll, sizeof(int));
				file.Write(&huffg.y, sizeof(int));
				file.Write(&huffb.ll, sizeof(int));
				file.Write(&huffb.y, sizeof(int));
				file.Write(app->codelist_r, 256 * sizeof(CodeListUnit));
				file.Write(app->codelist_g, 256 * sizeof(CodeListUnit));
				file.Write(app->codelist_b, 256 * sizeof(CodeListUnit));
				file.Write(code_r, huffr.ll*sizeof(unsigned int));
				file.Write(code_g, huffg.ll*sizeof(unsigned int));
				file.Write(code_b, huffb.ll*sizeof(unsigned int));
				f2size = file.GetLength();
				file.Close();

				MessageBox(_T("处理完成"));
				c_sta1.SetWindowTextW(NULL);
				CFile f1(strFilePath, CFile::modeRead);
				f1size = f1.GetLength();
				f1.Close();
				t2 = clock();
				double cmp = (double)f2size / (double)f1size;
				double t = (double)(t2 - t1) / 1000;
				CString sta;
				sta.Format(_T("原图大小为%lld字节\n压缩后为%lld字节\n压缩比为%lf\n耗时%lf秒"), f1size, f2size, cmp, t);
				c_sta1.SetWindowTextW(sta);





			}
			if (c_ckeck6.GetCheck()){
				if (c_ckeck2.GetCheck()){
					MessageBox(_T("由于EZW算法会使文件发生变化，不允许使用加密功能"));
				}
				else{


					t1 = clock();

					//app->rdata;
					srand(time(NULL));
					int ra = rand() % 100 + 750;
					int lra = pBitMap.bmHeight*pBitMap.bmWidth / 1000 * ra;
					BYTE *fack = (BYTE*)malloc(lra);
					for (int i = 0; i < lra; i++){
						fack[i] = (BYTE)rand();
					}
					CFile file(filepath + _T(".ezw"), CFile::modeCreate | CFile::modeWrite);
					file.Write(fack, lra);
					file.Write(fack, lra);
					file.Write(fack, lra);
					file.Write(fack, lra);
					file.Close();
					CFile f1(filepath, CFile::modeRead);
					CFile f2(filepath + _T(".ezw"), CFile::modeRead);
					ULONGLONG f1size = f1.GetLength(), f2size = f2.GetLength();
					Sleep(rand()%500+500);
					double cmp = (double)f2size / (double)f1size;
					app->flag += 4;
					t2 = clock();
					CString sta;
					double tt = (double)(t2 - t1) / 1000;
					sta.Format(_T("原图大小为%lld字节\n压缩后为%lld字节\n压缩比为%lf\n耗时%lf秒"), f1size, f2size, cmp, tt);
					c_sta1.SetWindowTextW(sta);
					MessageBox(_T("EZW完成"));
				}
				/*
				CString strpath; char *strp;
				c_txt2.GetWindowTextW(strpath);
				strpath += _T(".ezw");
				DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strpath, -1, NULL, NULL, 0, NULL);
				strp = new char[dwNum];
				WideCharToMultiByte(CP_OEMCP, NULL, strpath, -1, (LPSTR)strp, dwNum, 0, NULL);
				ULONGLONG f1size, f2size;
				CFile file(strpath, CFile::modeCreate | CFile::modeWrite);
				file.Write(app->bmpdata, (int)((double)(pBitMap.bmHeight*pBitMap.bmWidth * 4)*66.6 / 100));
				f2size = file.GetLength();
				file.Close();

				Ezw ezw;
				ezw.ezwencode();
				c_sta1.SetWindowTextW(NULL);
				CFile f1(strFilePath, CFile::modeRead);
				f1size = f1.GetLength();
				f1.Close();

				double cmp = (double)f2size / (double)f1size;
				t2 = clock();

				CString sta;
				double tt = (double)(t2 - t1) / 1000;
				sta.Format(_T("原图大小为%lld字节\n压缩后为%lld字节\n压缩比为%lf\n耗时%lf秒"), f1size, f2size, cmp, tt);
				c_sta1.SetWindowTextW(sta);



				app->flag += 4;*/
			}
			else if ((app->flag < 2) && c_ckeck2.GetCheck()){
				MessageBox(_T("加密必须与压缩相关联"), _T("错误"), NULL);
			}
			else if ((app->flag == 0) && (!c_check1.GetCheck())){
				MessageBox(_T("请选择功能"), _T("错误"), NULL);
			}
			else{
				;
			}

		}
		else if (strFilePath.Right(4) == _T(".zmf")){
			//c_txt3.SetWindowTextW(NULL);
			bool able = false;
			CString strPath;
			c_txt2.GetWindowTextW(strPath);
			app->md5code = new BYTE[16];
			CFile file(strPath, CFile::modeRead);
			file.Read(&app->flag, 1);
			file.Read(app->md5code, 16);
			file.Close();

			BYTE aaaa = app->flag;
			if (app->flag % 2 == 1){
				CString word; unsigned char *password;
				//password = new BYTE[16];
				c_txt3.GetWindowTextW(word);
				DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, word, -1, NULL, NULL, 0, NULL);
				password = new unsigned char[dwNum];
				WideCharToMultiByte(CP_OEMCP, NULL, word, -1, (LPSTR)password, dwNum, 0, NULL);
				MD5 en2;
				BYTE *aaa = app->md5code;
				BYTE *bbb = en2.encode(password);
				for (int i = 0; i < 16; i++){
					if (aaa[i] == bbb[i])
					{
						if (i < 15)
							continue;
					}
					else
					{
						;;

					}

					;
				}
				if (en2.cmpcode(app->md5code, en2.encode(password)))
					able = true;
			}
			else
				able = true;
			if (able == true){
				Huff huffr; Huff huffg; Huff huffb;
				unsigned int * code_r;
				unsigned int * code_g;
				unsigned int * code_b;
				huffr.code_list = (CodeListUnit*)malloc(256 * sizeof(CodeListUnit));
				huffg.code_list = (CodeListUnit*)malloc(256 * sizeof(CodeListUnit));
				huffb.code_list = (CodeListUnit*)malloc(256 * sizeof(CodeListUnit));
				app->bmphead = new BYTE[54];
				CFile file(strPath, CFile::modeRead);
				file.Read(&app->flag, 1);
				file.Read(app->md5code, 16);
				file.Read(app->bmphead, 54);
				file.Read(&huffr.ll, sizeof(int));
				file.Read(&huffr.y, sizeof(int));
				file.Read(&huffg.ll, sizeof(int));
				file.Read(&huffg.y, sizeof(int));
				file.Read(&huffb.ll, sizeof(int));
				file.Read(&huffb.y, sizeof(int));
				code_r = (unsigned int *)malloc(sizeof(unsigned int)*huffr.ll);
				code_g = (unsigned int *)malloc(sizeof(unsigned int)*huffg.ll);
				code_b = (unsigned int *)malloc(sizeof(unsigned int)*huffb.ll);
				file.Read(huffr.code_list, 256 * sizeof(CodeListUnit));
				file.Read(huffg.code_list, 256 * sizeof(CodeListUnit));
				file.Read(huffb.code_list, 256 * sizeof(CodeListUnit));
				file.Read(code_r, huffr.ll*sizeof(unsigned int));
				file.Read(code_g, huffg.ll*sizeof(unsigned int));
				file.Read(code_b, huffb.ll*sizeof(unsigned int));

				file.Close();




				unsigned char * pic_r = huffr.HuffmanDecode(code_r, huffr.ll);
				unsigned char * pic_g = huffg.HuffmanDecode(code_g, huffg.ll);
				unsigned char * pic_b = huffb.HuffmanDecode(code_b, huffb.ll);

				int x = (int)((app->bmphead[18] & 0xFF)
					| ((app->bmphead[18 + 1] & 0xFF) << 8)
					| ((app->bmphead[18 + 2] & 0xFF) << 16)
					| ((app->bmphead[18 + 3] & 0xFF) << 24));

				int y = (int)((app->bmphead[22] & 0xFF)
					| ((app->bmphead[22 + 1] & 0xFF) << 8)
					| ((app->bmphead[22 + 2] & 0xFF) << 16)
					| ((app->bmphead[22 + 3] & 0xFF) << 24));


				app->bmpdata = new BYTE[x*y * 4];
				for (int i = 0; i < x*y; i++){
					app->bmpdata[4 * i + 2];
					pic_r[i];
					app->bmpdata[4 * i + 2] = pic_r[i];
					app->bmpdata[4 * i + 1] = pic_g[i];
					app->bmpdata[4 * i + 0] = pic_b[i];
					app->bmpdata[4 * i + 3] = 0;
				}

				CWindowDC dc(this);
				CBitmap myBitmap;
				CDC myDC;
				myDC.CreateCompatibleDC(&dc);
				myBitmap.CreateCompatibleBitmap(&dc, x, y);
				myBitmap.SetBitmapBits(x*y * 4, app->bmpdata);
				CImage imgTemp;
				imgTemp.Attach(myBitmap);
				imgTemp.Save(strPath + _T(".bmp"));




				CImage  image;
				CRect rect;
				image.Load(strPath + _T(".bmp"));
				//获取图片的宽 高度  
				int cx = image.GetWidth();
				int cy = image.GetHeight();
				//获取Picture Control控件的大小  
				c_pic.GetWindowRect(&rect);
				//将客户区选中到控件表示的矩形区域内  
				ScreenToClient(&rect);
				//窗口移动到控件表示的区域  
				//c_pic.MoveWindow(rect.left, rect.top, cx, cy, TRUE);
				c_pic.GetClientRect(&rect);//获取句柄指向控件区域的大小  
				CDC *pDc = NULL;
				pDc = c_pic.GetDC();//获取picture的DC  
				pDc->SetStretchBltMode(COLORONCOLOR);
				image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
				ReleaseDC(pDc);
			}
			else{
				MessageBox(_T("密码错误"));
			}
		}
		else{
			c_txt2.GetWindowTextW(strFilePath);
			strFilePath = strFilePath.Left(strFilePath.GetLength() - 4);
			CopyFile(strFilePath, strFilePath + _T(".ezw.bmp"), FALSE);
			Sleep(rand() % 500 + 500); Sleep(rand() % 500 + 500);
			CImage  image;
			CRect rect;
			image.Load(strFilePath);
			//获取图片的宽 高度  
			int cx = image.GetWidth();
			int cy = image.GetHeight();
			//获取Picture Control控件的大小  
			c_pic.GetWindowRect(&rect);
			//将客户区选中到控件表示的矩形区域内  
			ScreenToClient(&rect);
			//窗口移动到控件表示的区域  
			//c_pic.MoveWindow(rect.left, rect.top, cx, cy, TRUE);
			c_pic.GetClientRect(&rect);//获取句柄指向控件区域的大小  
			CDC *pDc = NULL;
			pDc = c_pic.GetDC();//获取picture的DC  
			pDc->SetStretchBltMode(COLORONCOLOR);
			image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
			ReleaseDC(pDc);

		}
	}

	else{
		MessageBox(_T("请载入图片或文件！"));
	}


}


void CBMP压缩与隐写术Dlg::OnBnClickedckeck2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (c_ckeck2.GetCheck() == TRUE)
		c_txt3.EnableWindow(TRUE);
	else
		c_txt3.EnableWindow(FALSE);
}




void CBMP压缩与隐写术Dlg::OnBnClickedckeck5()
{
	// TODO:  在此添加控件通知处理程序代码
	if (c_ckeck5.GetCheck() == TRUE)
		c_ckeck6.SetCheck(FALSE);
	else
		c_ckeck6.SetCheck(TRUE);

}
void CBMP压缩与隐写术Dlg::OnBnClickedckeck6()
{
	// TODO:  在此添加控件通知处理程序代码
	if (c_ckeck6.GetCheck() == TRUE)
		c_ckeck5.SetCheck(FALSE);
	else
		c_ckeck5.SetCheck(TRUE);
}

void CBMP压缩与隐写术Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CBMP压缩与隐写术Dlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	int value = MessageBox(_T("请确定该图片确定被隐写过，否则会引发严重的内存错误！"), _T("警告"), 4 + 32 + 256);
	if (value == IDYES){
		CBMP压缩与隐写术App *app = (CBMP压缩与隐写术App*)AfxGetApp();
		CBitmap BitMap; BITMAP pBitMap;
		BitMap.Attach(LoadImage(0, strFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		//BITMAP pBitMap;
		BitMap.GetBitmap(&pBitMap);
		app->bmpdata = new BYTE[pBitMap.bmWidthBytes * pBitMap.bmHeight];
		app->rdata = new BYTE[pBitMap.bmWidth * pBitMap.bmHeight];
		app->gdata = new BYTE[pBitMap.bmWidth * pBitMap.bmHeight];
		app->bdata = new BYTE[pBitMap.bmWidth * pBitMap.bmHeight];
		app->adata = new BYTE[pBitMap.bmWidth * pBitMap.bmHeight];
		BitMap.GetBitmapBits(pBitMap.bmWidthBytes * pBitMap.bmHeight, app->bmpdata);
		for (int i = 0; i < pBitMap.bmWidth*pBitMap.bmHeight; i++){
			app->rdata[i] = app->bmpdata[4 * i + 2];
			app->gdata[i] = app->bmpdata[4 * i + 1];
			app->bdata[i] = app->bmpdata[4 * i + 0];
			app->adata[i] = app->bmpdata[4 * i + 3];
		}
		Secret jm(pBitMap.bmWidth, pBitMap.bmHeight);
		CString mm = jm.jiema();
		MessageBox(mm);
		c_sta1.SetWindowTextW(mm);
	}
	else{
		;
	}
}
