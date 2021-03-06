/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Alopex/Helium
*     All rights reserved.
*
* @file		WinProcess.cpp
* @brief	This Program is WinProcess DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2017-11-29
*/
#include "WinProcess.h"
#include "WinUtilities.h"

#include "LiveCore.h"

CLiveCore g_LiveCore;

float g_fLastTime = 0.0f;
float g_fCurrentTime = 0.0f;
float g_fDeltaTime = 0.0f;

//------------------------------------------------------------------
// @Function:	 SetWindowParameterCallBack(void)
// @Purpose: WinMain设置窗口相关参数回调函数
// @Since: v1.00a
// @Para: None
// @Return: WndPara*
//------------------------------------------------------------------
WndPara* SetWindowParameterCallBack(void)
{
	WndPara* pWindowParameter = new WndPara;
	pWindowParameter->nWndWidth = USER_WINDOWWIDTH;//窗口宽度
	pWindowParameter->nWndHeight = USER_WINDOWHEIGHT;//窗口高度
	pWindowParameter->lpszTitle = USER_WINDOWTITLE;//窗口标题名称
	pWindowParameter->wIcon = USER_WINDOWICON;//窗口标题图标
	return pWindowParameter;
}

//------------------------------------------------------------------
// @Function:	 InitWindowExtraCallBack(void)
// @Purpose: WinMain初始化窗口相关内容回调函数(DirectX 初始化)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL InitWindowExtraCallBack(void)
{
	return g_LiveCore.CLiveCoreInit();
}

//------------------------------------------------------------------
// @Function:	 ReleaseWindowExtraCallBack(void)
// @Purpose: WinMain释放窗口相关内容回调函数(DirectX 释放)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void ReleaseWindowExtraCallBack(void)
{
	g_LiveCore.CLiveCoreRelease();
}

//------------------------------------------------------------------
// @Function:	 Direct3DRenderCallBack(void)
// @Purpose: Direct3D渲染相关回调函数(DirectX 渲染)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void Direct3DRenderCallBack(void)
{
	float fDeltaTime = 1.0f / g_LiveCore.m_nVideoFreq;

	g_fLastTime = (float)timeGetTime()*0.001f;

	g_LiveCore.CLiveCoreUpdate();
	g_LiveCore.CLiveCoreRender();

	g_fCurrentTime = (float)timeGetTime()*0.001f;
	g_fDeltaTime = g_fCurrentTime - g_fLastTime;
	
	if (g_fDeltaTime < fDeltaTime)
	{
		Sleep((DWORD)((fDeltaTime - g_fDeltaTime) * 1000.0f));
	}
}