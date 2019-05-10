/** @defgroup ˫����ʾ
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2016.8.9
 */
#pragma once
#include "Decoder.h"

class CVideoLogic : public CNotifyUIImpl, public Singleton<CVideoLogic>
{
public:
	CVideoLogic(void);
	~CVideoLogic(void);

    //�˳�Ԥ��
    bool OnHideVideo(TNotifyUI& msg);
protected:
	/** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

	/** ��ʼ����Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnInit(TNotifyUI& msg);
	
	/** ���� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	//˫����Ӧ
    bool OnShowVideo(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool HideDualView();
	void RestoreVedioWnd();
	bool OnDualRecvStateNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnStartRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	bool OnDualCodeEnCryptKeyNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
public:
	void AskKeyFrame( BOOL32 bForce );

	void SetDecVol( u8 abyVol );

	u8 GetDecVol();
	APP_DECLARE_MSG_MAP()
private:
	//��ʼ/ֹͣ �ۿ�˫����ʾ
	void PlayDual();

	void InitParam();

private:
	CDecoder  m_cDecoder;
	TTPCnMediaTransPort		m_tVedioIpTransAddr;
	TTPCnMediaTransPort		m_tAudioIpTransAddr;


	static String m_wndVedio;     //������ʾvedio��wnd

	static String m_strSchmFullScreen;  //ȫ������

	static String m_strSchmHideScreen;  //���ط���

	BOOL32 m_bRecvStream;
	BOOL32 m_bDecod;

	BOOL32 m_bFullScreen;
	BOOL32 m_bIsClkBtn;          //���ڱ�־�Ƿ��ǵ���tpad�տ���ʾ��ť���յ��Ļظ���Ϣ
	TTpEncryptKey m_tTpEncryptKey;

};