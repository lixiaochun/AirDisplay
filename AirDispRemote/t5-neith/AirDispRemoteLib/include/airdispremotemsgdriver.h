/*=======================================================================
ģ����      : RKC����̨
�ļ���      : rckmsgdriver.h
����ļ�    : 
�ļ�ʵ�ֹ���: RCK��Ϣ������
����        : Ҷ��ƽ
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����

=======================================================================*/
#ifndef AirDispRemoteMSGDRIVER_H
#define AirDispRemoteMSGDRIVER_H

#include <vector>
#include "kdvdispevent.h"
#include "ospmsg.h"
//#include "eventoutrkcentre.h"
#include "AirDispRemotemessage.h"

#define     AID_AirDispRemote_APP     53
#define     AID_AIRDIS_APP      62

class CAirDispRemoteMsgDriver
{
public:
    CAirDispRemoteMsgDriver();
    ~CAirDispRemoteMsgDriver();

    // �õ�������Ϣ��ָ��
    COspMsg* GetOspMsgPtr(BOOL32 bClear = TRUE);
    // ע��һ��������Ϣ�����ָ��
    void RegHandler(CKdvDispEvent* const pDispEvnet);
    // ����CMessage osp��Ϣ
    virtual void PostCMsg(u16 wEvenId, void* pConent, u16 wLen);
    // ����osp��Ϣ
    virtual u16 PostMsg(u32 dwType = TYPE_CMESSAGE);

    // ���õ�ǰ���ӽڵ�
    void SetNodeId(u32 dwId) { m_dwNodeId = dwId; }
    u32 GetNodeId(){ return m_dwNodeId;}

    // ����ʹ�õ�APPID��
    void SetAppId( u16 wAppID ){ m_wAppID = wAppID; } 
    u16  GetAppId(){ return m_wAppID; }

public:
    static CAirDispRemoteMsgDriver *s_pMsgDriver;

    // ��ӦWM_OSPMESSAGECOMING��Ϣ
    void OnOspMessageComing(WPARAM wParam, LPARAM lParam);

protected:
    COspMsg     m_tOspMsg;              //osp������Ϣ
    CMessage    m_cMsg;			        //���ڷ���������Ϣ����Ϣ�ṹ
private:
    void MappingEventName();

    vector<CKdvDispEvent*> m_vpDispEvent;   // ��Ϣ�ַ���

    u32  m_dwNodeId;        // ��ǰ���ӵĽڵ�
    u16  m_wAppID;			// ���ӵ�APPID��
};


#endif //AirDispRemoteMSGDRIVER_H