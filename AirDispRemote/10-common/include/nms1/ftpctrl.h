/*=============================================================================
ģ   ��   ��: ���ܹ���ģ���
��   ��   ��: ftpctrl.h
�� ��  �� ��: ftpctrl.cpp
�ļ�ʵ�ֹ���: FTP�ϴ����ؿ���
��        ��: ���
��        ��: V4.0  Copyright(C) 2003-2005 KDC, All rights reserved.
˵        ��: ��Ҫʹ��MFC, ʹ������Ҫ����wininet.lib��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2005/09/29  4.0     ���        ����
=============================================================================*/

#ifndef _FTPCTRL_20050929_H_
#define _FTPCTRL_20050929_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wininet.h>
#include "kdvtype.h"

#define IP_LEN                  (s32)16     //  IP��ַ�ַ�������
#define FTP_USER_LEN            (s32)32     //  FTP�û�������
#define FTP_PWD_LEN             (s32)32     //  FTP���볤��
#define PROXY_NAME_LEN          (s32)64     //  �������Ƴ���
#define PROXY_PWD_LEN           (s32)32     //  �������볤��

#define FTP_TIMEOUT             (u32)20 * 1000  //  FTP�̳߳�ʱʱ��, 20��

#define FTP_AGENT               _T("Ftp_Ctrl")  //  InternetOpen��һ������

//  FTP���䷽��
enum EmFtpDirect
{
    emFtpUpload     = (u8)0,    //  �ϴ�
    emFtpDownload   = (u8)1     //  ����
};

#ifndef _UNICODE
//  FTP����״̬
enum EmFtpStatus
{
    emFtpBegin      = (u32)0,   //��ʼ����, WPARAM = emFtpBegin, LPARAM��ʾҪ������ļ���С
    emFtpTransfer   = (u32)1,   //���ڴ���, WPARAM = emFtpTransfer, LPARAM��ʾ���η��ʹ�С
    emFtpEnd        = (u32)2,   //ֹͣ����, WPARAM = emFtpEnd, LPARAM��ʾ���, 0--�ɹ�, !0--������
};

#else
//  FTP����״̬
enum EmFtpStatus
{
	emFtpConnect    = (u32)0,
	emFtpBegin      = (u32)1,   //��ʼ����, WPARAM = emFtpBegin, LPARAM��ʾҪ������ļ���С
	emFtpTransfer   = (u32)2,   //���ڴ���, WPARAM = emFtpTransfer, LPARAM��ʾ���η��ʹ�С
	emFtpEnd        = (u32)3,   //ֹͣ����, WPARAM = emFtpEnd, LPARAM��ʾ���, 0--�ɹ�, !0--������
	emFtpWarning	= (u32)4,   //������Ϣ, WPARAM = emFtpWarning, LPARAM ������
};

class CFtpCtrlMsgDeal
{
public:
	CFtpCtrlMsgDeal(){};
	virtual ~CFtpCtrlMsgDeal(){};
	virtual void OnMessage( WPARAM wParam, LPARAM lParam ) = 0;
};

#endif



class CFtpCtrl
{
public:
    /*=============================================================================
    �� �� ��:CFtpCtrl
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    CFtpCtrl();

    /*=============================================================================
    �� �� ��:~CFtpCtrl
    ��    ��:��������
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    virtual ~CFtpCtrl();

public:
    /*=============================================================================
    �� �� ��:SetServerParam
    ��    ��:����FTP�����������Ӳ���
    ��    ��:LPCTSTR pszIpAddr                  [in]    ������IP��ַ
             LPCTSTR pszUser                    [in]    ��¼�û�����
             LPCTSTR pszPwd                     [in]    ��¼����
             u16 wPort                          [in]    FTP�������˿�
             LPCTSTR pszProxyName               [in]    ��������
             LPCTSTR pszProxyPwd                [in]    ��������
    ע    ��:��
    �� �� ֵ:�Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    BOOL32 SetServerParam(LPCTSTR pszIpAddr, LPCTSTR pszUser, LPCTSTR pszPwd,
                          u16 wPort = INTERNET_DEFAULT_FTP_PORT,
                          LPCTSTR pszProxyName = NULL,
                          LPCTSTR pszProxyPwd = NULL);

	 /*=============================================================================
    �� �� ��:CreateFtpDirectory
    ��    ��:����FTP�ϴ���Ŀ¼
    ��    ��:LPCTSTR lpszFtpFilePath			[in] �ϴ����ļ��ľ���·��
    ע    ��:��
    �� �� ֵ:�Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    =============================================================================*/
	BOOL32 CreateFtpDirectory(LPCTSTR lpszFtpFilePath);

    /*=============================================================================
    �� �� ��:BeginDownload
    ��    ��:��ʼ�����ļ�
    ��    ��:HWND hWnd                          [in]    ������Ϣ�Ĵ��ھ��
             LPCTSTR pszRemoteFile              [in]    Զ���ļ�����
             LPCTSTR pszLocalFile               [in]    ���汾�ص��ļ�����
             u32 dwFileType                     [in]    �ļ���������
             LPCTSTR pszAgent                   [in]    InternetOpen��һ������
             BOOL32 bDeleteRemoteFile           [in]    ������Ϻ��Ƿ�ɾ��Զ���ļ�
    ע    ��:��
    �� �� ֵ:�Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
#ifndef _UNICODE
    BOOL32 BeginDownload(HWND hWnd, LPCTSTR pszRemoteFile,
                         LPCTSTR pszLocalFile,
                         u32 dwFileType = FTP_TRANSFER_TYPE_UNKNOWN,
                         LPCTSTR pszAgent = FTP_AGENT,
                         BOOL32 bDeleteRemoteFile = TRUE);
    /*=============================================================================
    �� �� ��:BeginUpload
    ��    ��:��ʼ�ϴ��ļ�
    ��    ��:HWND hWnd                          [in]    ������Ϣ�Ĵ��ھ��
             LPCTSTR pszRemoteFile              [in]    Զ���ļ�����
             LPCTSTR pszLocalFile               [in]    ���汾�ص��ļ�����
             u32 dwFileType                     [in]    �ļ���������
             LPCTSTR pszAgent                   [in]    InternetOpen��һ������
    ע    ��:��
    �� �� ֵ:�Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    BOOL32 BeginUpload(HWND hWnd, LPCTSTR pszRemoteFile,
                       LPCTSTR pszLocalFile,
                       u32 dwFileType = FTP_TRANSFER_TYPE_UNKNOWN,
                       LPCTSTR pszAgent = FTP_AGENT);

#else
	BOOL32 BeginDownload( LPCTSTR pszRemoteFile,
		LPCTSTR pszLocalFile,
		u32 dwFileType = FTP_TRANSFER_TYPE_UNKNOWN,
		LPCTSTR pszAgent = FTP_AGENT,
		BOOL32 bDeleteRemoteFile = TRUE);

	BOOL32 BeginUpload( LPCTSTR pszRemoteFile,
		LPCTSTR pszLocalFile,
		u32 dwFileType = FTP_TRANSFER_TYPE_UNKNOWN,
		LPCTSTR pszAgent = FTP_AGENT,
		BOOL32 bIsCreateNewDirectory = FALSE);

	//ɾ��FTP�ļ�
	BOOL32 DeleteRemoteFile( LPCTSTR aszRemoteFile );

	void SethWnd( HWND hWnd ) { m_hWnd = hWnd; }

    /*=============================================================================
    �� �� ��:SetMsgDeal
    ��    ��:���ô�����Ϣ����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:���ھ��
    =============================================================================*/
	void SetMsgDeal( CFtpCtrlMsgDeal* pMsgDeal ){ m_pMsgDeal = pMsgDeal; }
#endif

	/*=============================================================================
    �� �� ��:EndFtpFile
    ��    ��:ֹͣFTP����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    BOOL32 EndFtpFile(void);

    /*=============================================================================
    �� �� ��:GetCurrentSession
    ��    ��:�õ���ǰFTP�ĻỰ���
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��ǰFTP�ĻỰ���
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    HINTERNET GetCurrentSession(void) const { return m_hSession; }

    /*=============================================================================
    �� �� ��:GetCurrentConnect
    ��    ��:�õ���ǰ�����Ӿ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��ǰ���Ӿ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    HINTERNET GetCurrentConnect(void) const { return m_hConnect; }

    /*=============================================================================
    �� �� ��:GetCurrentRemoteFile
    ��    ��:��ȡԶ���ļ�����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Զ���ļ�����
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    LPCTSTR GetCurrentRemoteFile(void) const { return m_aszRemoteFile; }

    /*=============================================================================
    �� �� ��:GetCurrentLocalFile
    ��    ��:��ȡ�����ļ�����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�����ļ�����
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    LPCTSTR GetCurrentLocalFile(void) const { return m_aszLocalFile; }

    /*=============================================================================
    �� �� ��:GetFtpSvrIP
    ��    ��:��ȡFTP������IP
    ��    ��:��
    ע    ��:��
    �� �� ֵ:������IP
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    LPCTSTR GetFtpSvrIP(void) const { return m_aszFtpSrvIp; }

    /*=============================================================================
    �� �� ��:GetFtpSvrPort
    ��    ��:��ȡFTP�������˿�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�������˿�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    u16 GetFtpSvrPort(void) const { return m_wFtpSrvPort; }

    /*=============================================================================
    �� �� ��:GetFtpUser
    ��    ��:��ȡFTP�û���
    ��    ��:��
    ע    ��:��
    �� �� ֵ:FTP�û���
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    LPCTSTR GetFtpUser(void) const { return m_aszFtpSrvUser; }

    /*=============================================================================
    �� �� ��:GetFtpPwd
    ��    ��:��ȡFTP����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:FTP����
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    LPCTSTR GetFtpPwd(void) const { return m_aszFtpSrvPwd; }

    /*=============================================================================
    �� �� ��:GetFtpProxyName
    ��    ��:��ȡ��������
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    LPCTSTR GetFtpProxyName(void) const { return m_aszProxyName; }

    /*=============================================================================
    �� �� ��:GetFtpProxyPwd
    ��    ��:��ȡ��������
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    LPCTSTR GetFtpProxyPwd(void) const { return m_aszProxyPwd; }

    /*=============================================================================
    �� �� ��:GetCurrentFileType
    ��    ��:��ȡ��ǰ������ļ�����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�ļ�����
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    u32 GetCurrentFileType(void) const { return m_dwFileType; }

    /*=============================================================================
    �� �� ��:SetFileSize
    ��    ��:����FTP�ļ��ܳ���
    ��    ��:u32 dwFileSize             [in]    FTP�ļ��ܳ���
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    void SetFileSize(u32 dwFileSize) { m_dwTotalFileSize = dwFileSize; }

    /*=============================================================================
    �� �� ��:GetTotalFileSize
    ��    ��:��ȡ�ļ��ܳ���
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�ļ��ܳ���
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    u32 GetTotalFileSize(void) const { return m_dwTotalFileSize; }

    /*=============================================================================
    �� �� ��:GetCurrentFtpSize
    ��    ��:��ȡ��ǰ�Ѿ�����Ĵ�С
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�Ѿ�����Ĵ�С
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    u32 GetCurrentFtpSize(void) const { return m_dwCurrentFtpSize; }

    /*=============================================================================
    �� �� ��:IncreaseFtpSize
    ��    ��:���ļ����������, ����ʵ���Ѿ�������ļ���С
    ��    ��:u32 dwProcSize             [in]    ����ɴ�С
    ע    ��:��
    �� �� ֵ:����ɴ�С
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    u32 IncreaseFtpSize(u32 dwProcSize);

    /*=============================================================================
    �� �� ��:GetCurProcSize
    ��    ��:��ȡ��ǰ�ļ����еĴ�С
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��ǰ�ļ����еĴ�С
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    u32 GetCurProcSize(void) const { return m_dwCurrentFtpSize; }

    /*=============================================================================
    �� �� ��:RegisterMsgHandle
    ��    ��:ע��һ����Ϣ
    ��    ��:u32 dwEventId              [in]    ��Ϣ��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    void RegisterMsgHandle(u32 dwEventId) { m_dwEventId = dwEventId; }

    /*=============================================================================
    �� �� ��:GetRegisterMsgHandle
    ��    ��:��ȡ�Ѿ�ע�����Ϣ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�Ѿ�ע�����Ϣ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    u32 GetRegisterMsgHandle(void) const { return m_dwEventId; }

    /*=============================================================================
    �� �� ��:GethWnd
    ��    ��:��ȡ��ǰ���������Ϣ���ھ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:���ھ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    HWND GethWnd(void) const { return m_hWnd; }



    /*=============================================================================
    �� �� ��:SetFtpDirect
    ��    ��:����FTP���䷽��
    ��    ��:EmFtpDirect byFtpDirect            [in]    ���䷽��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    void SetFtpDirect(EmFtpDirect byFtpDirect) { m_byFtpDirect = byFtpDirect; }

    /*=============================================================================
    �� �� ��:GetFtpDirect
    ��    ��:��ȡFTP���䷽��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:FTP���䷽��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    EmFtpDirect GetFtpDirect(void) const { return m_byFtpDirect; }

    /*=============================================================================
    �� �� ��:IsDelRemoteFileAfterDownload
    ��    ��:�ж��ļ����ؽ������Ƿ�ɾ��Զ���ļ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�Ƿ�ɾ��Զ���ļ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    BOOL32 IsDelRemoteFileAfterDownload(void) const { return m_bDelRemoteFile; }

    /*=============================================================================
    �� �� ��:PostMsg
    ��    ��:��Ϣ����
    ��    ��:WPARAM wParam                  [in]    ��Ϣ������
             LPARAM lParam                  [in]    ��Ϣ����
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/10/08  4.0     ���    ����
    =============================================================================*/
    virtual void PostMsg(WPARAM wParam, LPARAM lParam = 0);

    /*=============================================================================
    �� �� ��:IsFileAscii
    ��    ��:�ж�һ��Ҫ�����ļ�������ļ��Ƿ���ASCII��ʽ��
    ��    ��:LPCTSTR pszFileName                [in]    �ļ���
    ע    ��:��
    �� �� ֵ:�Ƿ�ASCII��ʽ
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    static BOOL32 IsFileAscii(LPCTSTR pszFileName);

    /*=============================================================================
    �� �� ��:FormatFtpError
    ��    ��:��ȡϵͳ�Ĵ�������
    ��    ��:u32 dwErrorCode                    [in]    ������
             LPTSTR *ppszMsg                    [out]   ������Ϣ
    ע    ��:ppszMsgʹ�ý����������LocalFree���ͷŸÿռ�
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    static void FormatFtpError(DWORD dwErrorCode, LPTSTR *ppszMsg);

	/*=============================================================================
	�� �� ��:DeleteFile
	��    ��:��Ϣ����
	��    ��:LPCSTR lpszFileName                 [in]    �ļ�����
	ע    ��:��
	�� �� ֵ:TRUE:�ļ�ɾ���ɹ�	FALSE:�ļ�ɾ��ʧ��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���  �޸�����
	2011/03/21  5.0     ������    ����
	=============================================================================*/
	BOOL32 DeleteFile(LPCSTR lpszFileName);

	/*=============================================================================
    �� �� ��:CreateDir
    ��    ��:����Ŀ¼
    ��    ��:LPCTSTR strDir  Ŀ¼��    ʹ�÷�Χ���ϼ�Ŀ¼����
    ע    ��:��
    �� �� ֵ:�Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/26  4.0     ����ӡ    ����
    =============================================================================*/
    BOOL32 CreateDir( LPCTSTR strDir );

	/*=============================================================================
    �� �� ��:SetIsRenameTransFile
    ��    ��:�Ƿ������������ļ�   �ǣ�����������Զ��رշ�����   �ȴ�Rename��رշ�����
    ��    ��:BOOL32 bIsRename
    ע    ��:��
    �� �� ֵ:�Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/26  4.0     ����ӡ    ����
    =============================================================================*/
    void SetIsRenameTransFile( BOOL32 bIsRename ){ m_bIsRenameTransFile = bIsRename;};
    BOOL32 GetIsRenameTransFile(){ return m_bIsRenameTransFile;};

	/*=============================================================================
    �� �� ��:RenameFtpFile
    ��    ��:������FTP�ļ�
    ��    ��:LPCTSTR pszRemoteTempFile  �����е�Դ�ļ�, LPCTSTR pszRemoteFile  �����н�Դ�ļ��滻ΪĿ���ļ�
    ע    ��:��
    �� �� ֵ:�Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/26  4.0     ����ӡ    ����
    =============================================================================*/
    BOOL32 RenameFtpFile( LPCTSTR pszRemoteTempFile, LPCTSTR pszRemoteFile );

	/*=============================================================================
    �� �� ��:ConnectServer
    ��    ��:����FTP������
    ��    ��:��
    ע    ��:������������ӷ�����
    �� �� ֵ:�Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/08/06  4.0     ������    ����
    =============================================================================*/
	BOOL32 ConnectServer();

	/*=============================================================================
    �� �� ��:FindfFtpFile
    ��    ��:����FTP�ļ�
    ��    ��: LPCTSTR pszRemotePath  �ļ�·��, LPCTSTR pstrRemoteName �ļ�����
    ע    ��:��
    �� �� ֵ:�Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/08/06  4.0     ������    ����
    =============================================================================*/
	BOOL32 FindfFtpFile( LPCTSTR pszRemotePath, LPCTSTR pstrRemoteName );
	
	/*=============================================================================
    �� �� ��:SetIsRenameTransFile
    ��    ��:�Ƿ�ر�ftp����   Ĭ�����ڲ����ƹر� 
    ��    ��:BOOL32 bAutoEnd
    ע    ��:���ļ��ϴ����ⲿ����ftp�ر�
    �� �� ֵ:�Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/12/11  4.0     ������    ����
    =============================================================================*/
    void SetAutoEndFtpFile( BOOL32 bAutoEnd ){ m_bAutoEndFtpFile = bAutoEnd;};
    BOOL32 GetAutoEndFtpFile(){ return m_bAutoEndFtpFile;};

	//����Զ���ļ������֣����ڻ�ȡԶ���ļ���С
    void SetRemoteFileName(LPCTSTR pszRemoteFileName);

	/*=============================================================================
    �� �� ��:GetRemoteFileSize
    ��    ��:��ȡԶ���ļ��Ĵ�С
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Զ���ļ��Ĵ�С
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    virtual u32	GetRemoteFileSize(void);
	

	BOOL32 isNeedUpdate( u32 dwProcSize );
protected:
    /*=============================================================================
    �� �� ��:CheckParam
    ��    ��:��鿪ʼ�ϴ�������ʱ����Ĳ����Ƿ���ȷ
    ��    ��:LPCTSTR pszRemoteFile              [in]    Զ���ļ�����
             LPCTSTR pszLocalFile               [in]    ���汾�ص��ļ�����
             u32 dwFileType                     [in]    �ļ���������
    ע    ��:��
    �� �� ֵ:�����Ƿ���ȷ
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    BOOL32 CheckParam(LPCTSTR pszRemoteFile, LPCTSTR pszLocalFile, u32 dwFileType);

    /*=============================================================================
    �� �� ��:DownloadFile
    ��    ��:�����ļ�
    ��    ��:LPCTSTR pszRemoteFile              [in]    Զ���ļ�����
             LPCTSTR pszLocalFile               [in]    ���汾�ص��ļ�����
             u32 dwFileType                     [in]    �ļ���������
             LPCTSTR pszAgent                   [in]    InternetOpen��һ������
    ע    ��:��
    �� �� ֵ:�����Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    virtual BOOL32 DownloadFile(LPCTSTR pszRemoteFile, LPCTSTR pszLocalFile,
                                u32 dwFileType, LPCTSTR pszAgent);

    /*=============================================================================
    �� �� ��:UploadFile
    ��    ��:�ϴ��ļ�
    ��    ��:LPCTSTR pszRemoteFile              [in]    Զ���ļ�����
             LPCTSTR pszLocalFile               [in]    ���汾�ص��ļ�����
             u32 dwFileType                     [in]    �ļ���������
             LPCTSTR pszAgent                   [in]    InternetOpen��һ������
    ע    ��:��
    �� �� ֵ:�ϴ��Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    virtual BOOL32 UploadFile(LPCTSTR pszRemoteFile, LPCTSTR pszLocalFile,
                              u32 dwFileType, LPCTSTR pszAgent);

    /*=============================================================================
    �� �� ��:ConnectSrv
    ��    ��:���ӷ�����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�����Ƿ�ɹ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    virtual BOOL32 ConnectSrv(void);

    /*=============================================================================
    �� �� ��:GetLocalFileSize
    ��    ��:��ȡ�����ļ��Ĵ�С
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�����ļ��Ĵ�С
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    u32	GetLocalFileSize(void);

    /*=============================================================================
    �� �� ��:GetWinRemoteFileSize
    ��    ��:��ȡԶ��windows�ļ���С
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Զ��windows�ļ���С
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    u32 GetWinRemoteFileSize(void);

    /*=============================================================================
    �� �� ��:GetVaxRemoteFileSize
    ��    ��:��ȡԶ��VAX�ļ���С
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Զ��VAX�ļ���С
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/09/29  4.0     ���    ����
    =============================================================================*/
    u32 GetVaxRemoteFileSize(void);


	friend DWORD WINAPI FtpCtrlDownloadThread(LPVOID pParam);
	friend DWORD WINAPI FtpCtrlUploadThread(LPVOID pParam);
public:
    u32         m_dwFtpHead;                    //  FTP����ͷ--�Դ�InternetConnect֮���͵Ĵ���
	BOOL        m_bIsConnect;					//  �ж��Ƿ��Ѿ�����ftp������(�ⲿ��ȡ)
protected:
    HINTERNET   m_hSession;                     //  Ӧ����InternetOpen
    HINTERNET   m_hConnect;                     //  Ӧ����InternetConnect

    TCHAR       m_aszFtpSrvIp[IP_LEN];          //  FTP��������IP��ַ
    TCHAR       m_aszFtpSrvUser[FTP_USER_LEN];  //  FTP�������ĵ�¼�û�
    TCHAR       m_aszFtpSrvPwd[FTP_PWD_LEN];    //  FTP�������ĵ�¼����
    TCHAR       m_aszProxyName[PROXY_NAME_LEN]; //  ����������
    TCHAR       m_aszProxyPwd[PROXY_PWD_LEN];   //  �����Ŀ���
    TCHAR       m_aszRemoteFile[MAX_PATH];      //  Զ���ļ���
    TCHAR       m_aszLocalFile[MAX_PATH];       //  �����ļ���
    u16         m_wFtpSrvPort;                  //  FTP�������ļ����˿�

    HANDLE      m_hFtpThread;                   //  FTP������߳̾��
    LPTSTR      m_pszAgent;                     //  InternetOpen��һ������
    DWORD       m_dwFtpThreadId;                //  FTP������̱߳��
    HWND        m_hWnd;                         //  ���մ��������Ϣ�Ĵ���
    u32         m_dwFileType;		            //  ������ļ�����
    u32         m_dwCurrentFtpSize;             //  ��ǰ����Ĵ�С
    u32         m_dwTotalFileSize;              //  �ļ��ܴ�С
    u32         m_dwEventId;                    //  ��Ϣ��, ����綨��
    BOOL32      m_bTransfering;                 //  �Ƿ����ڴ���
    BOOL32      m_bDelRemoteFile;               //  FTP������Ϻ��Ƿ�ɾ��Զ���ļ�
	BOOL32		m_bCreateNewDirectory;			//  FTP �ϴ�Ŀ¼������ʱ���Ƿ񴴽���Ŀ¼

    EmFtpDirect m_byFtpDirect;                  //  ���䷽��, Ĭ��Ϊ����
	BOOL32		m_bIsRenameTransFile;			//  ���������������������   �������������ٹر�FTP   by ldy 2013.01.22
	BOOL32		m_bAutoEndFtpFile;				//  ���ļ��������ⲿ���ƹر�ftp
	u32			m_LastTimeSendMesFileSize;				//add ��һ�δ����ļ���С
#ifdef _UNICODE

	CFtpCtrlMsgDeal* m_pMsgDeal;				//	������Ϣ����
#endif
};

#endif  //  _FTPCTRL_20050929_H_