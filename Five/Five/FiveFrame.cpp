#include "stdafx.h"
#include "Five.h"
#include "FiveFrame.h"
#include "UnitLayout.h"

CFiveFrame::CFiveFrame()
{
	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			m_pArrUnit[i][j] = NULL;
		}
	}
}

CFiveFrame::~CFiveFrame()
{
	// �򸸿ؼ��Ѿ������ӿؼ�, �˴�m_pArrUnit��delete;
}

LPCTSTR CFiveFrame::GetWindowClassName() const
{
	return _T("CFiveFrame");
}

CStdString CFiveFrame::GetSkinFolder()
{
	CStdString strFolder = CPaintManagerUI::GetInstancePath() + _T("skin\\");
	return strFolder;
}

CStdString CFiveFrame::GetSkinFile()
{
	return _T("FiveFrame.xml");
}

void CFiveFrame::Init()
{
	CDuiBaseWindow::Init();

	CHorizontalLayoutUI* pBoard = static_cast<CHorizontalLayoutUI*>(m_pmUI.FindControl(_T("lay_board")));
	if (NULL == pBoard)
	{
		return;
	}
	
	/*<Label float="true" pos="53,23,0,0" width="25" height="25" bkimage="black_normal.png" />
			<Label float="true" pos="83,23,0,0" width="25" height="25" bkimage="black_normal.png" />
			<Label float="true" pos="113,23,0,0" width="25" height="25" bkimage="black_normal.png" />
			<Label float="true" pos="143,23,0,0" width="25" height="25" bkimage="black_normal.png" />
			<Label float="true" pos="173,23,0,0" width="25" height="25" bkimage="black_normal.png" />
			<Label float="true" pos="203,23,0,0" width="25" height="25" bkimage="black_normal.png" />*/
	int iLeft = 53;
	int iTop  = 23;
	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 15; j++)
		{			
			CUnitLayout* pLabel = new CUnitLayout();
			m_pArrUnit[i][j] = pLabel;
			if (NULL == m_pArrUnit[i][j])
			{
				return;
			}
			pBoard->Add(pLabel);

			pLabel->SetFloat(true);
			RECT rt;
			rt.left = iLeft + 30*i;
			rt.top  = iTop + 30*j;
			rt.right = 0;
			rt.bottom  = 0;
			pLabel->SetPos(rt);
			pLabel->SetFixedWidth(25);
			pLabel->SetFixedHeight(25);
		}
	}

	pBoard->Invalidate();
}

void CFiveFrame::OnFinalMessage(HWND hWnd)
{
	CDuiBaseWindow::OnFinalMessage(hWnd);
	delete this;

	::PostQuitMessage(0);
}

LRESULT CFiveFrame::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		// Close(IDCANCEL);
		return TRUE;
	}

	return FALSE;
}

CControlUI* CFiveFrame::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT CFiveFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

void CFiveFrame::Notify(TNotifyUI& msg)
{
	CStdString strType = msg.sType;
	CStdString strName = msg.pSender->GetName();
	if ( 0 == strType.Compare(_T("windowinit")) )
	{
		//OnPrepare(msg);
	}
	else if ( 0 == strType.Compare(_T("click")) )
	{
		if (0 == strName.Compare(_T("btn_close")) )
		{
			Close(IDCANCEL);
		}
		else if ( 0 == strName.Compare(_T("btn_min")) )
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
	}
}

LRESULT CFiveFrame::OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;	// ����˫�����;
	return 0;
}

void CFiveFrame::BeginGame()
{
	g_iUnitIndex = 0;

	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			if (NULL != m_pArrUnit[i][j])
			{
				m_pArrUnit[i][j]->Begin();
			}
		}
	}
}

void CFiveFrame::EndGame()
{
	CHorizontalLayoutUI* pBoard = static_cast<CHorizontalLayoutUI*>(m_pmUI.FindControl(_T("lay_board")));
	if (NULL != pBoard)
	{
		pBoard->SetEnabled(false);	// ����, ������Ӧ�¼�;
	}

	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			if (NULL != m_pArrUnit[i][j])
			{
				m_pArrUnit[i][j]->SetEnabled(false);	// ����, ������Ӧ�¼�;
			}
		}
	}
}

int CFiveFrame::ValidateGame()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			int iCount = 0; // ͳ������������ӵĺ�;
			for (int iIndex = 0; iIndex < 5; iIndex++ )
			{
				if (NULL != m_pArrUnit)
				{
					iCount = iCount + m_pArrUnit[i+iIndex][j]->GetUnitType();

					if (abs(iCount) > iIndex)
					{
						// ȫ��ͬɫ����,�����ж�;
						if ( 5 == abs(iCount) )
						{
							if (iCount < 0)
							{
								//CStdString str = _T("��ʤ");
								return - 1;
							}
							else
							{
								//CStdString str = _T("��ʤ");
								return 1;
							}
						}
						continue;
					}
					else
					{
						// �����ڲ�ͬɫ������ֱ���ж���һ��;
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			int iCount = 0; // ͳ������������ӵĺ�;
			for (int iIndex = 0; iIndex < 5; iIndex++ )
			{
				if (NULL != m_pArrUnit)
				{
					iCount = iCount + m_pArrUnit[i][j+iIndex]->GetUnitType();

					if (abs(iCount) > iIndex)
					{
						// ȫ��ͬɫ����,�����ж�;
						if ( 5 == abs(iCount) )
						{
							if (iCount < 0)
							{
								//CStdString str = _T("��ʤ");
								return - 1;
							}
							else
							{
								//CStdString str = _T("��ʤ");
								return 1;
							}
						}
						continue;
					}
					else
					{
						// �����ڲ�ͬɫ������ֱ���ж���һ��;
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			int iCount = 0; // ͳ������������ӵĺ�;
			for (int iIndex = 0; iIndex < 5; iIndex++ )
			{
				if (NULL != m_pArrUnit)
				{
					if ( (i+iIndex >= 15) || (j+iIndex >= 15) )
					{
						break;
					}

					iCount = iCount + m_pArrUnit[i+iIndex][j+iIndex]->GetUnitType();

					if (abs(iCount) > iIndex)
					{
						// ȫ��ͬɫ����,�����ж�;
						if ( 5 == abs(iCount) )
						{
							if (iCount < 0)
							{
								//CStdString str = _T("��ʤ");
								return - 1;
							}
							else
							{
								//CStdString str = _T("��ʤ");
								return 1;
							}
						}
						continue;
					}
					else
					{
						// �����ڲ�ͬɫ������ֱ���ж���һ��;
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			int iCount = 0; // ͳ���������б�ӵĺ�;
			for (int iIndex = 0; iIndex < 5; iIndex++ )
			{
				if (NULL != m_pArrUnit)
				{
					if ( (i+iIndex >= 15) || (j+iIndex >= 15) )
					{
						break;
					}

					iCount = iCount + m_pArrUnit[i+iIndex][j+iIndex]->GetUnitType();

					if (abs(iCount) > iIndex)
					{
						// ȫ��ͬɫ����,�����ж�;
						if ( 5 == abs(iCount) )
						{
							if (iCount < 0)
							{
								//CStdString str = _T("��ʤ");
								return - 1;
							}
							else
							{
								//CStdString str = _T("��ʤ");
								return 1;
							}
						}
						continue;
					}
					else
					{
						// �����ڲ�ͬɫ������ֱ���ж���һ��;
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			int iCount = 0; // ͳ���������б�ӵĺ�;
			for (int iIndex = 0; iIndex < 5; iIndex++ )
			{
				if (NULL != m_pArrUnit)
				{
					if ( (i+iIndex >= 15) || (j-iIndex < 0) )
					{
						break;
					}
					iCount = iCount + m_pArrUnit[i+iIndex][j-iIndex]->GetUnitType();

					if (abs(iCount) > iIndex)
					{
						// ȫ��ͬɫ����,�����ж�;
						if ( 5 == abs(iCount) )
						{
							if (iCount < 0)
							{
								//CStdString str = _T("��ʤ");
								return - 1;
							}
							else
							{
								//CStdString str = _T("��ʤ");
								return 1;
							}
						}
						continue;
					}
					else
					{
						// �����ڲ�ͬɫ������ֱ���ж���һ��;
						break;
					}
				}
			}
		}
	}

	return 0;
}
