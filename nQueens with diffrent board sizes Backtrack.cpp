#include <iostream>
using namespace std;

class cnode
{
public:

	char** x;
	cnode* pnext;
	int row = 0;
};
class clist
{
public:
	cnode* phead;
	cnode* ptail;
	clist()
	{
		phead = NULL;
		ptail = NULL;
	}
	~clist()
	{
		cnode* ptrav;
		ptrav = phead;
		while (ptrav != NULL)
		{
			phead = phead->pnext;
			delete ptrav;
			ptrav = phead;
		}
	}
	void attach(cnode* pnn)
	{
		if (phead == NULL)
		{
			phead = pnn;
			ptail = pnn;
		}
		else
		{
			ptail->pnext = pnn;
			ptail = pnn;
		}
	}
};
class cstack
{
public:
	cnode* phead;
	cstack()
	{
		phead = NULL;
	}
	~cstack()
	{
		cnode* ptrav;
		ptrav = phead;
		while (ptrav != NULL)
		{
			phead = phead->pnext;
			delete ptrav;
			ptrav = phead;
		}
	}

	void push(cnode* pnn)
	{
		pnn->pnext = phead;
		phead = pnn;
	}
	cnode* pop()
	{
		cnode* ptrav;
		ptrav = phead;
		phead = ptrav->pnext;
		ptrav->pnext = NULL;
		return ptrav;
	}
};
cnode* createinit(int board)
{
	cnode* pnn = new cnode;
	pnn->pnext = NULL;
	pnn->row = 0;
	pnn->x = new char* [board];
	for (int k = 0; k < board; k++)
	{
		pnn->x[k] = new char[board];
	}
	int c = 0;
	int r = 0;
	for (r = 0; r < board; r++)
	{
		for (c = 0; c < board; c++)
		{
			pnn->x[r][c] = ' ';
		}

	}
	return pnn;
}
int isFinallyOk(cnode* pnn, int board)
{
	int ct = 0;
	if (pnn->row == board)return 1; return 0;
}

void copy(cnode* pcurr, cnode* pnn, int board)
{
	for (int r = 0; r < board; r++)
	{
		for (int c = 0; c < board; c++)
		{
			pnn->x[r][c] = pcurr->x[r][c];
		}
	}
	pnn->row = pcurr->row;
}


int isgood(cnode* pnn, int board)
{
	int flag = 1;


	for (int row = 0; row < board; row++)
	{
		for (int col = 0; col < board; col++)
		{
			if (pnn->x[row][col] == 'Q')
			{
				int c = col;
				for (int r = 0; r < board; r++)
				{
					if (pnn->x[r][c] == 'Q' && r != row)
					{
						return 0;
					}
				}


				int r = row;

				for (c = 0; c < board; c++)
				{
					if (pnn->x[r][c] == 'Q' && col != c)
					{
						return 0;
					}
				}

				c = col + 1;
				for (r = row + 1; r < board && c < board; r++)
				{
					if (pnn->x[r][c] == 'Q')
					{
						return 0;
					}
					c++;
				}

				c = col - 1;

				for (r = row - 1; r >= 0 && c >= 0; r--)
				{
					if (pnn->x[r][c] == 'Q')
					{
						return 0;
					}
					c--;
				}

				c = col + 1;

				for (r = row - 1; r >= 0 && c < board; r--)
				{
					if (pnn->x[r][c] == 'Q')
					{
						return 0;
					}
					c++;
				}

				c = col - 1;

				for (r = row + 1; r < board && c >= 0; r++)
				{
					if (pnn->x[r][c] == 'Q')
					{
						return 0;
					}
					c--;
				}

			}
		}
	}

	return 1;


}
void expandchildren(cnode* pcurr, cstack& s, int board)
{
	int a;
	int b;
	cnode* pnn;

	for (int c = 0; c < board; c++)
	{
		pnn = new cnode;
		pnn->pnext = NULL;
		pnn = createinit(board);
		copy(pcurr, pnn, board);

		pnn->x[pnn->row][c] = 'Q';
		pnn->row++;

		a = isgood(pnn, board);
		if (a == 1)
		{
			s.push(pnn);
		}
		else
		{
			for (int k = 0; k < board; k++)
			{
				delete pnn->x[k];
			}
			delete pnn->x;
		}

	}

}
void display(cnode* pnn, int board)
{
	for (int r = 0; r < board; r++)
	{
		for (int c = 0; c < board; c++)
		{
			cout << pnn->x[r][c] << ",";
		}
		cout << endl;
	}
}
void main()
{
	cstack s;
	cnode* pnn;
	cnode* pcurr;
	int board;
	cout << "Chess Board = X*X, please enter the x size: \n";
	cin >> board;
	int ct = 0;
	pnn = createinit(board);

	s.push(pnn);
	while (s.phead != NULL)
	{
		pcurr = s.pop();
		if (isFinallyOk(pcurr, board))
		{
			ct++;
			//display(pcurr, board);
			cout << "Solution " << ct << endl;
			for (int k = 0; k < board; k++)
			{
				delete pcurr->x[k];
			}
			delete pcurr->x;
		}
		else
		{
			expandchildren(pcurr, s, board);
		}

	}
}