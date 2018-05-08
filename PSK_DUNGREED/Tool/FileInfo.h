#pragma once

#include "Include.h"
class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();

public:
	const std::wstring ConvertRelativePath(const std::wstring& wstrFullPath);
	void DirInfoExtraction(const std::wstring& wstrPath, std::list<IMGPATH*>& rInfolist);
	int DirFileCount(const std::wstring& wstrPath);
};

