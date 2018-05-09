// MapTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "Scene.h"
#include "FileInfo.h"
// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
	, m_iTileX(0)
	, m_iTileY(0)
{

}

CMapTool::~CMapTool()
{
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_TileList);
	DDX_Control(pDX, IDC_LIST2, m_ObjListBox);
	DDX_Text(pDX, IDC_EDIT1, m_iTileX);
	DDV_MinMaxInt(pDX, m_iTileX, 0, 1000);
	DDX_Text(pDX, IDC_EDIT2, m_iTileY);
	DDV_MinMaxInt(pDX, m_iTileY, 0, 1000);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedTileSave)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnBnClickedTileLoad)
	ON_BN_CLICKED(IDC_BUTTON3, &CMapTool::OnBnClickedMapObjSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CMapTool::OnBnClickedMapObjLoad)
	ON_BN_CLICKED(IDC_RADIO1, &CMapTool::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMapTool::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMapTool::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CMapTool::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CMapTool::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CMapTool::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CMapTool::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_BUTTON5, &CMapTool::OnBnClickedCreateMap)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelchangeTileList)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMapTool::OnLbnSelchangeMapObjList)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.
BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pScene = ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pScene;

	HMODULE hModule = GetModuleHandle(nullptr);
	ASSERT(hModule != 0);

	TCHAR szFullPath[MAX_PATH] = L"";
	GetModuleFileNameW(hModule, szFullPath, MAX_PATH);
	PathRemoveFileSpecW(szFullPath);
	PathRemoveFileSpecW(szFullPath);
	lstrcat(szFullPath, L"\\Texture\\TILE\\*.*");

	FindDirAddFile(szFullPath, true);

	GetModuleFileNameW(hModule, szFullPath, MAX_PATH);
	PathRemoveFileSpecW(szFullPath);
	PathRemoveFileSpecW(szFullPath);
	lstrcat(szFullPath, L"\\Texture\\OBJECT\\*.*");
	FindDirAddFile(szFullPath, false);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMapTool::OnLbnSelchangeTileList()
{
	UpdateData(TRUE);

	m_pScene->SetObjViewRenderMode(true);

	CString		strSelectDigit;
	int		iSelect = m_TileList.GetCurSel();
	if (iSelect < 0)
		return;

	m_TileList.GetText(iSelect, strSelectDigit);

	int		i = 0;
	for (; i < strSelectDigit.GetLength(); ++i)
	{
		if (isdigit(strSelectDigit[i]) != 0)
			break;
	}
	CString strSelectName = strSelectDigit;

	strSelectName.Delete(i, strSelectName.GetLength() - i);
	strSelectDigit.Delete(0, i);
	m_wstrStateKey = strSelectName;
	m_byDrawID = _tstoi(strSelectDigit);

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bTilePicking = true;

	UpdateData(FALSE);
}

void CMapTool::OnLbnSelchangeMapObjList()
{
	UpdateData(TRUE);

	m_pScene->SetObjViewRenderMode(false);

	CString		strSelectDigit;
	int		iSelect = m_ObjListBox.GetCurSel();
	if (iSelect < 0)
		return;

	m_ObjListBox.GetText(iSelect, strSelectDigit);

	int		i = 0;
	for (; i < strSelectDigit.GetLength(); ++i)
	{
		if (isdigit(strSelectDigit[i]) != 0)
			break;
	}
	CString strSelectName = strSelectDigit;

	strSelectName.Delete(i, strSelectName.GetLength() - i);
	strSelectDigit.Delete(0, i);
	m_wstrStateKey = strSelectName;
	m_iCount = _tstoi(strSelectDigit);

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bTilePicking = false;

	UpdateData(FALSE);
}

void CMapTool::OnBnClickedTileSave()
{
	CFileDialog Dlg(FALSE, L".dat", L".dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	HMODULE hModule = GetModuleHandle(nullptr);
	ASSERT(hModule != 0);

	TCHAR szFullPath[MAX_PATH] = L"";
	GetModuleFileName(hModule, szFullPath, MAX_PATH);
	PathRemoveFileSpec(szFullPath);
	PathRemoveFileSpec(szFullPath);
	lstrcat(szFullPath, L"%s\\Data\\");

	Dlg.m_ofn.lpstrInitialDir = szFullPath;
	if (Dlg.DoModal() == IDCANCEL)
		return;

	HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD dwByte = 0;

	std::vector<TILE*>* pVecTile = m_pScene->GetVecTile();

	WriteFile(hFile, &m_iTileX, sizeof(int), &dwByte, nullptr);
	WriteFile(hFile, &m_iTileY, sizeof(int), &dwByte, nullptr);

	for (auto& pTile : *pVecTile)
		WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

	CloseHandle(hFile);
}


void CMapTool::OnBnClickedTileLoad()
{
	CFileDialog Dlg(TRUE, L".dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	HMODULE hModule = GetModuleHandle(nullptr);
	ASSERT(hModule != 0);

	TCHAR szFullPath[MAX_PATH] = L"";
	GetModuleFileNameW(hModule, szFullPath, MAX_PATH);
	PathRemoveFileSpecW(szFullPath);
	PathRemoveFileSpecW(szFullPath);
	lstrcat(szFullPath, L"%s\\Data\\");

	Dlg.m_ofn.lpstrInitialDir = szFullPath;
	if (Dlg.DoModal() == IDCANCEL)
		return;

	HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD dwByte = 0;

	ReadFile(hFile, &m_iTileX, sizeof(int), &dwByte, nullptr);
	ReadFile(hFile, &m_iTileY, sizeof(int), &dwByte, nullptr);
	
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->SetScrollSizes(MM_TEXT, CSize(m_iTileX * TILECX, m_iTileY * TILECY));

	m_pScene->TileRelease();
	std::vector<TILE*>* pVecTile = m_pScene->GetVecTile();
	m_pScene->SetTileSize(m_iTileX, m_iTileY);
	while (true)
	{
		TILE* pTile = new TILE;
		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

		if (dwByte == 0)
		{
			Safe_Delete(pTile);
			break;
		}

		pVecTile->push_back(pTile);
	}

	CloseHandle(hFile);
}


void CMapTool::OnBnClickedMapObjSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE, L".dat", L".dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	HMODULE hModule = GetModuleHandle(nullptr);
	ASSERT(hModule != 0);

	TCHAR szFullPath[MAX_PATH] = L"";
	GetModuleFileName(hModule, szFullPath, MAX_PATH);
	PathRemoveFileSpec(szFullPath);
	PathRemoveFileSpec(szFullPath);
	lstrcat(szFullPath, L"%s\\Data\\");

	Dlg.m_ofn.lpstrInitialDir = szFullPath;
	if (Dlg.DoModal() == IDCANCEL)
		return;

	HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD dwByte = 0;

	std::vector<MAPOBJ*>* pVecObj = m_pScene->GetVecMapObj();

	int iVecSize = pVecObj->size();
	WriteFile(hFile, &iVecSize, sizeof(int), &dwByte, nullptr);

	for (auto& pTile : *pVecObj)
		WriteFile(hFile, pTile, sizeof(MAPOBJ), &dwByte, nullptr);

	CloseHandle(hFile);
}


void CMapTool::OnBnClickedMapObjLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(TRUE, L".dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	HMODULE hModule = GetModuleHandle(nullptr);
	ASSERT(hModule != 0);

	TCHAR szFullPath[MAX_PATH] = L"";
	GetModuleFileNameW(hModule, szFullPath, MAX_PATH);
	PathRemoveFileSpecW(szFullPath);
	PathRemoveFileSpecW(szFullPath);
	lstrcat(szFullPath, L"%s\\Data\\");

	Dlg.m_ofn.lpstrInitialDir = szFullPath;
	if (Dlg.DoModal() == IDCANCEL)
		return;

	HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD dwByte = 0;

	int iVecSize = 0;
	ReadFile(hFile, &iVecSize, sizeof(int), &dwByte, nullptr);

	m_pScene->MapObjRelease();
	std::vector<MAPOBJ*>* pVecObj = m_pScene->GetVecMapObj();

	while (true)
	{
		MAPOBJ* pObj = new MAPOBJ;
		ReadFile(hFile, pObj, sizeof(MAPOBJ), &dwByte, nullptr);

		if (dwByte == 0)
		{
			Safe_Delete(pObj);
			break;
		}

		pVecObj->push_back(pObj);
	}

	CloseHandle(hFile);
}

void CMapTool::OnBnClickedCreateMap()
{
	UpdateData(TRUE);
	m_pScene->CreateTileMap(m_iTileX, m_iTileY);
	UpdateData(FALSE);
}

void CMapTool::OnBnClickedRadio1()
{
	m_byOption = 0;
}

void CMapTool::OnBnClickedRadio2()
{
	m_byOption = 1;
}


void CMapTool::OnBnClickedRadio3()
{
	m_byOption = 2;
}


void CMapTool::OnBnClickedRadio4()
{
	m_byOption = 3;
}


void CMapTool::OnBnClickedRadio5()
{
	m_byOption = 4;
}

void CMapTool::OnBnClickedRadio6()
{
	m_byOption = 5;
}

void CMapTool::OnBnClickedRadio7()
{
	m_byOption = 6;
}

void CMapTool::FindDirAddFile(const std::wstring & wstrPath, bool bIsTile)
{
	_wfinddata_t		FindData;

	std::wstring		wstrCombinedPath;
	long		handle;
	int		iContinue = 1;

	handle = _wfindfirst(wstrPath.c_str(), &FindData);
	if (handle == -1)
		return;

	while (true)
	{
		iContinue = _wfindnext(handle, &FindData);

		if (iContinue == -1)
			break;

		if (!lstrcmp(FindData.name, L".") || !lstrcmp(FindData.name, L".."))
			continue;

		wstrCombinedPath = wstrPath.substr(0, wstrPath.length() - 3) + FindData.name;
		if (FindData.size != 0)
		{
			AddFileInfo(wstrCombinedPath.c_str(), bIsTile);
		}
		else
			FindDirAddFile(wstrCombinedPath + L"\\*.*", bIsTile);
	}
}

void CMapTool::AddFileInfo(const TCHAR * pFilePath, bool bIsTile)
{
	CFileInfo		FileInfo;
	std::wstring wstrRelativePath = FileInfo.ConvertRelativePath(pFilePath);

	std::wstring	wstrFileName = PathFindFileName(wstrRelativePath.c_str());
	TCHAR	szName[128] = L"";
	lstrcpy(szName, wstrFileName.c_str());
	PathRemoveExtension(szName);

	if (bIsTile)
		m_TileList.AddString(szName);
	else
		m_ObjListBox.AddString(szName);
}
