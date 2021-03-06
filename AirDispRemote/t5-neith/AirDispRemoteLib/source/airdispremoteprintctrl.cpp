/*****************************************************************************
模块名      :  
文件名      : printctrl.cpp
相关文件    : 
作者        : ylp
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2018/03/05  1.0          ylp      创建
******************************************************************************/

#include "stdafx.h"
#include "AirDispRemoteprintctrl.h"
#include "osp.h"

CAirDispRemotePrintCtrl* CAirDispRemotePrintCtrl::m_pPrtCtrl = NULL ;

map<u16, u8>            CAirDispRemotePrintCtrl::m_mapEventLevel;
map<u16, CString>       CAirDispRemotePrintCtrl::m_mapEventsName;
BOOL32                  CAirDispRemotePrintCtrl::m_bPrintAllMsg =  FALSE ;    //for test 
u8                      CAirDispRemotePrintCtrl::m_bayPrintLevel = 0;
u32                     CAirDispRemotePrintCtrl::m_dwPrintMsgID  = 0 ;        //要打印的消息号
u32                     CAirDispRemotePrintCtrl::m_dwPrintRangeMax = 0;       //要打印的消息范围 中的最大值
u32                     CAirDispRemotePrintCtrl::m_dwPrintRangeMin = 0;       //要打印的消息范围 中的最小值

CAirDispRemotePrintCtrl::CAirDispRemotePrintCtrl()
{
#ifdef _DEBUG
    //m_bPrintAllMsg = TRUE;
    m_bayPrintLevel = 2;
#endif
}


CAirDispRemotePrintCtrl::~CAirDispRemotePrintCtrl()
{
    if ( NULL != m_pPrtCtrl ) 
    {
        delete[] m_pPrtCtrl;
        m_pPrtCtrl = NULL;
    }
}

const CAirDispRemotePrintCtrl*CAirDispRemotePrintCtrl::GetPrintCtrl()  
{
    if ( m_pPrtCtrl == NULL )
    {    
        m_pPrtCtrl = new CAirDispRemotePrintCtrl();
    }

    return m_pPrtCtrl;
}

const CString CAirDispRemotePrintCtrl::GetTime()
{
    SYSTEMTIME st;
    GetLocalTime(&st);  
    CString time = "";
    time.Format("%4d/%.2d/%.2d %.2d:%.2d:%.2d ",
        st.wYear, st.wMonth,  st.wDay,
        st.wHour, st.wMinute, st.wSecond);
    return time;
}

bool CAirDispRemotePrintCtrl::IsPrintMsg( u16 dwMsgID )
{
    if (m_bPrintAllMsg)
    {
        return TRUE;
    }

    if (m_dwPrintMsgID == dwMsgID)
    {
        return TRUE;
    }

    if (m_dwPrintRangeMin <= dwMsgID
        && dwMsgID <= m_dwPrintRangeMax)
    {
        return TRUE;
    }

    map<u16, u8>::iterator itr = m_mapEventLevel.find(dwMsgID);
    if(itr != m_mapEventLevel.end())
    {  	
        if ( m_bayPrintLevel >= (*itr).second )
        {
            return TRUE;
        } 
    }  
    return FALSE;
}

void CAirDispRemotePrintCtrl::PrintMsg(u16 dwMsgID, EmScoketEventType emScoketEventType, char * format,... )
{
    if (!IsPrintMsg(dwMsgID))
    {
        return;
    }
    //打印消息名
    char szMsg[200] = {0}; 
    _snprintf(szMsg,sizeof(szMsg),"\n%s%s: %s.  ", GetTime(), GetEventTypeDescribe(emScoketEventType), GetEventDescribe(dwMsgID) );

    int n = strlen(szMsg);
    szMsg[n] = '\0';
    OspPrintf( TRUE, FALSE,  szMsg );  

    //打印消息体
    va_list arg_ptr;  
    char szBuffer[300] = { 0 };

    va_start(arg_ptr, format);  
    _vsnprintf ( szBuffer, sizeof (szBuffer) / sizeof (TCHAR),format, arg_ptr) ; 

    va_end(arg_ptr);  

    n = strlen(szBuffer);
    szBuffer[n] = '\0';

    OspPrintf(TRUE,FALSE,szBuffer); 
    OspPrintf(TRUE,FALSE,"\n");  

}

void CAirDispRemotePrintCtrl::PrintMsg(u16 dwMsgID, char * format,... )
{
    if (!IsPrintMsg(dwMsgID))
    {
        return;
    }
    OspPrintf(TRUE,FALSE,"\n");
    va_list arg_ptr;  
    char szBuffer[1024] = { 0 };

    va_start(arg_ptr, format);  
    _vsnprintf ( szBuffer, sizeof (szBuffer) / sizeof (TCHAR),format, arg_ptr) ; 

    va_end(arg_ptr); 

    int n = strlen(szBuffer);

    szBuffer[n] = '\0';

    OspPrintf(TRUE,FALSE,szBuffer); 
    OspPrintf(TRUE,FALSE,"\n");
}

void CAirDispRemotePrintCtrl::PrintMsg( char * format,... )
{
    va_list arg_ptr;  
    char szBuffer[1024] = { 0 };

    va_start(arg_ptr, format);  
    _vsnprintf ( szBuffer, sizeof (szBuffer) / sizeof (TCHAR),format, arg_ptr) ; 

    va_end(arg_ptr); 

    int n = strlen(szBuffer);

    szBuffer[n] = '\0';

    OspPrintf(TRUE,FALSE,szBuffer); 
}

void CAirDispRemotePrintCtrl::MappingHelper(u16 wEvent, const CString& strName, u8 abyLevel )
{
    m_mapEventsName[wEvent] = strName;
    m_mapEventLevel[wEvent] = abyLevel;
}

CString CAirDispRemotePrintCtrl::GetEventTypeDescribe(EmScoketEventType emType )
{
    CString str = " ";
    switch(emType) 
    {
    case emEventTypeOspSend:
        str = "[osp send]";
        break;
    case emEventTypeOspRecv:
        str = "[osp recv]";
        break;
    default:
        ;
    }

    return str;
}

CString CAirDispRemotePrintCtrl::GetEventDescribe( u16 wEvent )
{  
    CString str = "";
    map<u16, CString>::iterator itr = m_mapEventsName.find(wEvent);
    if(itr != m_mapEventsName.end())
    {
        str = (*itr).second; 
    }

    return str;
}

void CAirDispRemotePrintCtrl::PrintAllMsg()
{
    //m_bPrintAllMsg = TRUE;
    m_bayPrintLevel = 2;
}

void CAirDispRemotePrintCtrl::PrintMsgLevel( u8 abyLevel )
{
    m_bayPrintLevel = abyLevel;
}

void CAirDispRemotePrintCtrl::SetPrintMsgID( const u32 dwPrintEventId )
{
    m_dwPrintMsgID = dwPrintEventId;
} 

void CAirDispRemotePrintCtrl::SetPrintMsgRange( const u32 dwMaxMsgID, const u32 dwMinMsgID )
{
    m_dwPrintRangeMax = dwMaxMsgID;
    m_dwPrintRangeMin = dwMinMsgID;
}

void CAirDispRemotePrintCtrl::StopPrint()
{ 
    m_bPrintAllMsg = FALSE;
    m_dwPrintRangeMax = 0;
    m_dwPrintRangeMin = 0;
    m_dwPrintMsgID = 0;
    m_bayPrintLevel = 0;
}