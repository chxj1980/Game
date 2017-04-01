#pragma once
#include "DuiBaseWindow.h"
#include "UnitLayout.h"

// CFiveFrame �Ի���
class CFiveFrame : public CDuiBaseWindow
{
public:
	CFiveFrame();
	~CFiveFrame();

	LPCTSTR GetWindowClassName() const;

	virtual CStdString GetSkinFolder();
	virtual CStdString GetSkinFile();

	virtual void Init();
	virtual void OnFinalMessage(HWND hWnd);

	// ������Ӧ;
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	virtual CControlUI* CreateControl(LPCTSTR pstrClass);

	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	// Caption˫���¼�;
	virtual LRESULT OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:	

	void Notify(TNotifyUI& msg);

public:
	void BeginGame();		// ��ʼ��Ϸ;
	void EndGame();			// ������Ϸ;

	int ValidateGame();	//	��֤��Ϸ;

private:

	CUnitLayout*		m_pArrUnit[15][15];		// �˴���ָ�룬�����Ƕ���;��Ϊ��������������¹һ�
};