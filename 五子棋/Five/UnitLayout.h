#pragma once

#define	PNG_NONE				_T("")						// ��ͼ;
#define	PNG_BLACK_NORMAL		_T("black_normal.png")		// ��ͨ����;
#define	PNG_WHITE_NORMAL		_T("white_normal.png")		// ��ͨ����;
#define	PNG_BLACK_CLICKED		_T("black_click.png")		// ���µĺ���;
#define	PNG_WHITE_CLICKED		_T("white_click.png")		// ���µİ���;
#define	PNG_UNIT_HOVER			_T("unit_hover.png")		// ����ʮ�ֲ�;

enum UnitType
{
	E_BLACK	= -1,		// ��;
	E_NONE	= 0,		// ��;
	E_WHITE	= 1			// ��;
};

// ���ӵ�Ԫ��;
class CUnitLayout: public CLabelUI
{
public:
	CUnitLayout();
	~CUnitLayout();

	virtual void DoEvent(TEventUI& event);

public:
	void SetUnitIndex(int iUnitIndex);
	void Begin();		// ��ʼ;
	//int Validate();		// ��֤

	int GetUnitType();

private:
	int	m_iUnitIndex;	// ��¼����;
};

