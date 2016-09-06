#include "Parser.h"
#include <QDateTime>
#include <QDebug>

Parser::Parser(void)
	:m_bIsEnd(false)
{
	for (int i = 0;i<4;i++)
	{
		for (int j=0;j<4;j++)
		{
			m_iArray[i][j] = 0;
		}
	}
}


Parser::~Parser(void)
{
}
int Parser::GetNum()
{
	int n = qrand()%3;
//	qDebug()<<n;
	return n*2;
}
void Parser::printfNum()
{
	for (int i = 0;i<4;i++)
	{
		for (int j = 0;j<4;j++)
		{
			cout<<m_iArray[i][j]<<"\t";
		}
		cout<<endl;
		cout<<"\n"<<endl;
	}
}
bool Parser::CheckPoint(int i,int j,int m,int n)
{
	if ((abs(i-m) == 1 && j == n) || (abs(j-n) == 1 && i == m))
	{
		return true;
	}
	return false;
}
void Parser::MoveNumber(int i,int j,int m,int n)
{
	if (!CheckPoint(i,j,m,n))
	{
		return;
	}
	int sourNum = m_iArray[i][j];
	int destNum = m_iArray[m][n];
	if (sourNum == 0)
	{
		return;
	}
	else if (destNum == 0)
	{
		m_iArray[m][n] = sourNum;
		m_iArray[i][j] = GetNum();
	}
	else if (sourNum == destNum)
	{
		m_iArray[i][j] = 0;
		m_iArray[m][n] = destNum<<1;
		m_iArray[i][j] = GetNum();
	}
	printfNum();
}

/*
2 4 2 4
4 2 4 2
2 4 2 4
4 2 4 2

*/

bool Parser::CheckIsEnd()
{
	for (int i = 0;i<4;i++)
	{
		for (int j = 0;j<4;j++)
		{
			int num = m_iArray[i][j];
			if (num == 0)
			{
				return false;
			}
			if ((i>0&&i<3) && ((num==m_iArray[i-1][j])||(num==m_iArray[i+1][j])))
			{
				return false;
			}
			if ((j>0&&j<3) && ((num==m_iArray[i][j-1])||(num==m_iArray[i][j+1])))
			{
				return false;
			}
		}
	}
	return true;
}
void Parser::Start()
{
	while(!m_bIsEnd)
	{
		int i,j,m,n;
		cin>>i>>j>>m>>n;
		MoveNumber(i,j,m,n);
		CheckIsEnd();
	}
	qDebug()<<"Finished";
}

void Parser::Init()
{
	qsrand(QDateTime::currentDateTime().toTime_t());

	for (int i = 0;i<4;i++)
	{
		for (int j = 0;j<4;j++)
		{
			int n = GetNum();
			m_iArray[i][j] = n;
			cout<<n<<"\t";
		}
		cout<<endl;
		cout<<"\n"<<endl;
	}
}
void ReverseQList(QList<int> &listNum)
{
	std::list<int> ll = listNum.toStdList();
	ll.reverse();
	listNum.clear();
	foreach(int i,ll)
	{
		listNum<<i;
	}
}

void MergeList(QList<int> &nums)
{
	for (int i = 0;i<nums.size()-1;i++)
	{
		if (nums[i] == nums[i+1])
		{
			nums[i] = nums[i]<<1;
			nums[i+1] = 0;
		}
	}
	nums.removeAll(0);
}

void Parser::MoveLeft(int k)
{
	//Left k line<------
	QList<int> nums;
	for (int i = 0;i<4;i++)
	{
		nums<<m_iArray[k][i];
	}
	nums.removeAll(0);
	MergeList(nums);
	while(nums.size()<4)
	{
		nums<<0;
	}
	for (int i = 0;i<4;i++)
	{
		m_iArray[k][i] = nums.at(i);
	}
}


void Parser::MoveRight(int k)
{
	Init();
	QList<int> nums;
	for (int i = 0;i<4;i++)
	{
		nums<<m_iArray[k][i];
	}
	qint64 ss = QDateTime::currentMSecsSinceEpoch();
	bool en = CheckIsEnd();
	qint64 ee = QDateTime::currentMSecsSinceEpoch();
	qDebug()<<ee-ss;
	nums.removeAll(0);
	ReverseQList(nums);
	MergeList(nums);
	while(nums.size()<4)
	{
		nums<<0;
	}
	ReverseQList(nums);
	for (int i = 0;i<4;i++)
	{
		m_iArray[k][i] = nums.at(i);
	}
}

void Parser::MoveUp(int k)
{
	QList<int> nums;
	for (int i = 0;i<4;i++)
	{
		nums<<m_iArray[i][k];
	}
	nums.removeAll(0);

	MergeList(nums);
	while(nums.size()<4)
	{
		nums<<0;
	}
	for (int i = 0;i<4;i++)
	{
		m_iArray[i][k] = nums.at(i);
	}
}

void Parser::MoveDown(int k)
{
	QList<int> nums;
	for (int i = 0;i<4;i++)
	{
		nums<<m_iArray[i][k];
	}
	nums.removeAll(0);
	ReverseQList(nums);
	MergeList(nums);
	while(nums.size()<4)
	{
		nums<<0;
	}
	ReverseQList(nums);
	for (int i = 0;i<4;i++)
	{
		m_iArray[i][k] = nums.at(i);
	}
}
