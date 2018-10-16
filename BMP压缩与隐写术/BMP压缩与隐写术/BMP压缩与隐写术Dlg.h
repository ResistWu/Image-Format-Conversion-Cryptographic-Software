#pragma once
// BMP压缩与隐写术Dlg.h : 头文件
//

#include "afxwin.h"
#include "resource.h"


// CBMP压缩与隐写术Dlg 对话框
class CBMP压缩与隐写术Dlg : public CDialogEx
{
// 构造
public:
	CBMP压缩与隐写术Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BMP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	CButton c_check1;
	CEdit c_txt1;
	afx_msg void OnBnClickedcheck1();
	afx_msg void OnStnClickedpic();
	
	//afx_msg void OnDropFiles(HDROP hDropInfo);
	CStatic c_pic;
	CEdit c_txt2;
	CString strFilePath;
	afx_msg void OnBnClickedButton1();
	CString BootOpenDialog();

	
	afx_msg void OnBnClickedOk();
	CButton c_ckeck2;
	CEdit c_txt3;
	//CButton c_ckeck3;
	CButton c_radio;
	afx_msg void OnBnClickedckeck2();
	CButton c_radio2;
	afx_msg void OnBnClickedckeck5();
	CButton c_ckeck5;
	CButton c_ckeck6;
	afx_msg void OnBnClickedckeck6();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	CStatic c_sta1;
};

class CMyStatic : public CStatic
{
	DECLARE_DYNAMIC(CMyListCtrl)

public:
	CMyStatic();
	virtual ~CMyStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CStatic c_pic;
};

//图片信息
