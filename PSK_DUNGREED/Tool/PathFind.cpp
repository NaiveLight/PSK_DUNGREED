// PathFind.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "PathFind.h"
#include "afxdialogex.h"
#include "FileInfo.h"


// CPathFind 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPathFind, CDialog)

CPathFind::CPathFind(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PATHFIND, pParent)
{

}

CPathFind::~CPathFind()
{
}

void CPathFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}


BEGIN_MESSAGE_MAP(CPathFind, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPathFind::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON2, &CPathFind::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_BUTTON6, &CPathFind::OnBnClickedDelete)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CPathFind 메시지 처리기입니다.

void CPathFind::OnDropFiles(HDROP hDropInfo)
{
	UpdateData(TRUE);

	int		iFileCount = DragQueryFile(hDropInfo, -1, nullptr, 0);
	TCHAR	szFullPath[MAX_PATH] = L"";

	CFileInfo		FileInfo;

	for (int i = 0; i < iFileCount; ++i)
	{
		DragQueryFile(hDropInfo, i, szFullPath, MAX_PATH);
		FileInfo.DirInfoExtraction(szFullPath, m_PathInfolist);

		std::wstring		wstrCombined = L"";
		TCHAR		szBuf[128] = L"";

		for (auto& iter : m_PathInfolist)
		{
			_itow_s(iter->iCount, szBuf, 10);

			wstrCombined = iter->wstrObjKey + L"|" + iter->wstrStateKey + L"|";
			wstrCombined += szBuf;
			wstrCombined += L"|" + iter->wstrPath;

			m_ListBox.AddString(wstrCombined.c_str());
		}
	}

	UpdateData(FALSE);
}

void CPathFind::OnBnClickedSave()
{
	std::wofstream		SaveFile;
	SaveFile.open(L"../Data/ImgPath.txt", std::ios::out);

	int		iCount = 0;
	for (auto& iter : m_PathInfolist)
	{
		++iCount;
		SaveFile << iter->wstrObjKey << L"|";
		SaveFile << iter->wstrStateKey << L"|";
		SaveFile << iter->iCount << L"|";

		if (iCount == m_PathInfolist.size())
			SaveFile << iter->wstrPath << std::flush;
		else
			SaveFile << iter->wstrPath << std::endl;
	}
	SaveFile.close();
}


void CPathFind::OnBnClickedLoad()
{
	UpdateData(TRUE);
	std::wifstream		LoadFile;
	LoadFile.open(L"../Data/ImgPath.txt", std::ios::in);

	TCHAR		szObjKey[128] = L"";
	TCHAR		szStateKey[128] = L"";
	TCHAR		szCount[128] = L"";
	TCHAR		szImgPath[MAX_PATH] = L"";

	std::wstring		wstrCombined = L"";
	m_ListBox.ResetContent();

	while (!LoadFile.eof())
	{
		LoadFile.getline(szObjKey, 128, '|');
		LoadFile.getline(szStateKey, 128, '|');
		LoadFile.getline(szCount, 128, '|');
		LoadFile.getline(szImgPath, MAX_PATH);

		wstrCombined = std::wstring(szObjKey) + L"|" + std::wstring(szStateKey) + L"|";
		wstrCombined += szCount;
		wstrCombined += L"|" + std::wstring(szImgPath);

		m_ListBox.AddString(wstrCombined.c_str());
	}
	LoadFile.close();
	UpdateData(FALSE);
}


void CPathFind::OnBnClickedDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
