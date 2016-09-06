#pragma once
#include <QObject>
#include <iostream>
using namespace std;
struct NumberCell
{
	int num;
	int upNum;
	int downNum;
	int leftNum;
	int rightNum;
	bool CheckCanMove()
	{
		if (num != upNum && num!= downNum && num!=leftNum && num !=rightNum)
		{
			return false;
		}
		return true;
	}
};
class Parser : public QObject
{
	Q_OBJECT
private:
	int m_iArray[4][4];
	bool m_bIsEnd;
public:
	Parser(void);
	~Parser(void);
	int GetNum();
	void printfNum();
	bool CheckPoint(int i,int j,int m,int n);
	void MoveNumber(int i,int j,int m,int n);
	bool CheckIsEnd();
	void Start();
	void Init();

	void MoveLeft(int k);
	void MoveRight(int k);
	void MoveUp(int k);
	void MoveDown(int k);
};

