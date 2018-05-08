#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

const std::wstring CFileInfo::ConvertRelativePath(const std::wstring & wstrFullPath)
{
	TCHAR szRelativePath[MAX_PATH] = L"";
	TCHAR szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);

	PathRelativePathTo((LPWSTR)szRelativePath
		, szDirPath
		, FILE_ATTRIBUTE_DIRECTORY
		, wstrFullPath.c_str()
		, FILE_ATTRIBUTE_NORMAL
	);

	return szRelativePath;
}

void CFileInfo::DirInfoExtraction(const std::wstring & wstrPath, std::list<IMGPATH*>& rInfolist)
{
	CFileFind Find;

	Find.FindFile(wstrPath.c_str());

	int iContinue = 1;
	while (iContinue)
	{
		iContinue = Find.FindNextFileW();
		if (Find.IsDots())
			continue;

		if (Find.IsDirectory())
		{
			DirInfoExtraction(std::wstring(Find.GetFilePath() + L"\\*.*"), rInfolist);
		}
		else
		{
			if (Find.IsSystem())
				continue;

			IMGPATH* pImgPath = new IMGPATH;
			TCHAR		szPathBuf[MAX_PATH] = L"";

			lstrcpy(szPathBuf, Find.GetFilePath().operator LPCWSTR());
			PathRemoveFileSpec(szPathBuf);

			pImgPath->iCount = DirFileCount(szPathBuf);

			std::wstring wstrTextureName = Find.GetFileTitle().operator LPCWSTR();
			wstrTextureName = wstrTextureName.substr(0, wstrTextureName.size() - 1) + L"%d.png";

			TCHAR szBuf[MAX_PATH] = L"";
			lstrcpy(szBuf, Find.GetFilePath().operator LPCWSTR());
			PathRemoveFileSpec(szBuf);
			PathCombine(szBuf, szBuf, (LPWSTR)wstrTextureName.c_str());
			pImgPath->wstrPath = ConvertRelativePath(szBuf);

			PathRemoveFileSpec(szBuf);
			//szBuf[0] = szBuf[0] - 'A' + 'a';
			pImgPath->wstrStateKey = PathFindFileName(szBuf);

			PathRemoveFileSpec(szBuf);
			pImgPath->wstrObjKey = PathFindFileName(szBuf);

			rInfolist.push_back(pImgPath);

			iContinue = 0;
		}
	}
}

int CFileInfo::DirFileCount(const std::wstring & wstrPath)
{
	return 0;
}
