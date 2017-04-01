#include "StdAfx.h"
#include "UnitLayout.h"


CUnitLayout::CUnitLayout()
{
	m_iUnitIndex = 0;
}

CUnitLayout::~CUnitLayout()
{
}

void CUnitLayout::DoEvent(TEventUI& tEvent)
{
	if (!IsEnabled())
	{
		// �����ã�����Ӧ�¼�;
		return;
	}

	switch( tEvent.Type)
	{
	case UIEVENT_MOUSEENTER:
		{
			// �������,��û�������ͼ;
			CStdString strImage = GetBkImage();
			if (0 == strImage.Compare(PNG_NONE))
			{
				SetBkImage(PNG_UNIT_HOVER);
			}
		}
		break;
	case UIEVENT_MOUSELEAVE:
		{
			// ����뿪,��������ͼƬ��ȡ��;
			CStdString strImage = GetBkImage();
			if (0 == strImage.Compare(PNG_UNIT_HOVER))
			{
				SetBkImage(PNG_NONE);
			}
		}
		break;
	case UIEVENT_BUTTONDOWN:
		{
			// ��갴��,��������ͼƬ������,ż���ú�������,������������;
			CStdString strImage = GetBkImage();
			if (0 == strImage.Compare(PNG_UNIT_HOVER))
			{
				if ( 0 == g_iUnitIndex % 2)
				{
					SetBkImage(PNG_BLACK_NORMAL);
				}
				else
				{
					SetBkImage(PNG_WHITE_NORMAL);
				}

				SetUnitIndex(++g_iUnitIndex);

				// ��֤;
				if (0 != g_pFrame->ValidateGame())
				{
					g_pFrame->EndGame();
				}
			}
		}
		break;
	default:
		{
			CLabelUI::DoEvent(tEvent);
		}
		break;
	}
}

void CUnitLayout::SetUnitIndex(int iUnitIndex)
{
	m_iUnitIndex = iUnitIndex;
}

void CUnitLayout::Begin()
{
	SetUnitIndex(0);
	SetBkImage(PNG_NONE);
}

int CUnitLayout::GetUnitType()
{
	CStdString strImage = GetBkImage();
	if (!strImage.IsEmpty())
	{
		if (strImage.Find(_T("black")) > -1)
		{
			return E_BLACK;
		}
		else if (strImage.Find(_T("white")) > -1)
		{
			return E_WHITE;
		}
	}
	/*if (m_iUnitIndex > 0)
	{
		if (0 == m_iUnitIndex % 2)
		{
			return E_BLACK;
		}
		else
		{
			return E_WHITE;
		}
	}*/

	return E_NONE;
}
