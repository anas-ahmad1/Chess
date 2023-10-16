#include <cstdio>
#include <iostream>
#include <string>
#include "myconsole.h"
#include "mygraphics.h"
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <time.h>
using namespace std;

bool whiteturn(char Pieces[8][8], int startcolumn, int startrow)
{
	char w = Pieces[startrow][startcolumn];

	if (w == 'P' || w == 'R' || w == 'B' || w == 'N' || w == 'Q' || w == 'K')
	{
		return true;
	}
	return false;
}

bool blackturn(char Pieces[8][8], int startcolumn, int startrow)
{
	char b = Pieces[startrow][startcolumn];

	if (b == 'p' || b == 'r' || b == 'b' || b == 'n' || b == 'q' || b == 'k')
	{
		return true;
	}
	return false;
}

bool whitekill(char Pieces[8][8], int row,int col)		//DONE
{
	if (Pieces[row][col] == 'P' || Pieces[row][col] == 'R' || Pieces[row][col] == 'B' || Pieces[row][col] == 'N' || Pieces[row][col] == 'Q')
	{
		return true;
	}
	return false;
}

bool blackkill(char Pieces[8][8], int row,int col)		//Done
{
	if (Pieces[row][col] == 'p' || Pieces[row][col] == 'r' || Pieces[row][col] == 'b' || Pieces[row][col] == 'n' || Pieces[row][col] == 'q')
	{
		return true;
	}
	return false;
}


bool blackrookvalid(char Pieces[][8],int row,int col)
{
	char a=Pieces[row][col];
	if(a=='p' || a=='r' || a=='n' || a=='b' || a=='q' || a=='k')
		return true;
	return false;
}

bool blackrookmovement(char Pieces[8][8], int realinput[4])		//Killing, Blocking, Simple moves
{
	int startcolumn = realinput[0];
	int startrow = realinput[1];
	int endcolumn = realinput[2];
	int endrow = realinput[3];
	if (Pieces[endrow][endcolumn] == ' ' || whitekill(Pieces, endrow,endcolumn)==true)
	{
		if (startrow < endrow && startcolumn == endcolumn)		//Down
		{
			for (int i = startrow + 1; i <= endrow; i++)
			{
				if (Pieces[i][startcolumn] != ' ' && (whitekill(Pieces, i,endcolumn)==true)&& i!=endrow)
					return false;
				 if(blackrookvalid(Pieces,i,endcolumn)==true)
					return false;
			}
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';

		}
		if (startrow > endrow && startcolumn == endcolumn)		//Row
		{
			for (int i = startrow - 1; i >= endrow; i--)
			{
				if (Pieces[i][startcolumn] != ' ' && (whitekill(Pieces, i,endcolumn)==true)&& i!=endrow)
					return false;
				if(blackrookvalid(Pieces,i,endcolumn)==true)
					return false;
			}
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';

		}
		if (startcolumn < endcolumn && startrow == endrow)		//Right	
		{
			for (int i = startcolumn + 1; i <= endcolumn; i++)
			{
				if (Pieces[startrow][i] != ' ' && (whitekill(Pieces,endrow,i)==true)&& i!=endcolumn)
					return false;
				if(blackrookvalid(Pieces,endrow,i)==true)
					return false;
			}
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';

		}

		if (startcolumn > endcolumn && startrow == endrow)		//Left
		{
			for (int i = startcolumn - 1; i >= endcolumn; i--)
			{
				if (Pieces[startrow][i] != ' ' && (whitekill(Pieces, endrow,i)==true)&& i!=endcolumn)
					return false;
				if(blackrookvalid(Pieces,endrow,i)==true)
					return false;
			}
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';

		}
	}
	else if(blackrookvalid(Pieces,endrow,endcolumn)==true)
		return false;
	return true;
}

bool whiterookvalid(char Pieces[][8],int row,int col)
{
	char a=Pieces[row][col];
	if(a=='P' || a=='R' || a=='N' || a=='B' || a=='Q' || a=='K')
		return true;
	return false;
}

bool whiterookmovement(char Pieces[8][8], int realinput[4])		//Killing, Blocking, Simple moves
{
	int startcolumn = realinput[0];
	int startrow = realinput[1];
	int endcolumn = realinput[2];
	int endrow = realinput[3];
	if (Pieces[endrow][endcolumn] == ' ' || blackkill(Pieces, endrow,endcolumn)==true)
	{
		if (startrow < endrow && startcolumn == endcolumn)		//Down
		{
			for (int i = startrow + 1; i <= endrow; i++)
			{
				 if (Pieces[i][startcolumn] != ' ' && (blackkill(Pieces, i,endcolumn)==true) && i!=endrow)
					return false;
				 if(whiterookvalid(Pieces,i,endcolumn)==true)
					return false;
			}
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';

		}
		if (startrow > endrow && startcolumn == endcolumn)		//Up
		{
			for (int i = startrow - 1; i >= endrow; i--)
			{
				if (Pieces[i][startcolumn] != ' ' && (blackkill(Pieces, i,endcolumn)==true) && i!=endrow)
					return false;
				if(whiterookvalid(Pieces,i,endcolumn)==true)
					return false;
			}
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';

		}
		if (startcolumn < endcolumn && startrow == endrow)		//Right
		{
			for (int i = startcolumn + 1; i <= endcolumn; i++)
			{
				if (Pieces[startrow][i] != ' ' && (blackkill(Pieces, endrow,i)==true) && i!=endcolumn)
					return false;
				if(whiterookvalid(Pieces,endrow,i)==true)
					return false;
			}
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';

		}

		if (startcolumn > endcolumn && startrow == endrow)		//Left
		{
			for (int i = startcolumn - 1; i >= endcolumn; i--)
			{
				if (Pieces[startrow][i] != ' ' && (blackkill(Pieces, endrow,i)==true) && i!=endcolumn)
					return false;
				if(whiterookvalid(Pieces,endrow,i)==true)
					return false;
			}
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';
		}
	}
	else if(whiterookvalid(Pieces,endrow,endcolumn)==true)
		return false;
	return true;
}

bool bishopvalidation(char Pieces[8][8], int realinput[4])		//Killing, Blocking, Simple moves
{
	int startcolumn = realinput[0];
	int startrow = realinput[1];
	int endcolumn = realinput[2];
	int endrow = realinput[3];

	if (startrow > endrow && startcolumn < endcolumn)	//right up
	{
		for (int i = startrow, j = startcolumn; i > endrow; i--, j++)
		{
			if (Pieces[i - 1][j + 1] != ' ' && ((i-1)!=endrow && (j+1)!=endcolumn))
				return false;
		}
	}
	if (startrow < endrow && startcolumn < endcolumn)	//right down
	{
		for (int i = startrow, j = startcolumn; i < endrow; i++, j++)
		{
			if (Pieces[i + 1][j + 1] != ' ' && ((i+1)!=endrow && (j+1)!=endcolumn))
			{
				return false;
			}
		}
	}
	if (startrow > endrow && startcolumn > endcolumn)	//left up
	{
		for (int i = startrow, j = startcolumn; i > endrow; i--, j--)
		{
			if (Pieces[i - 1][j - 1] != ' ' && ((i-1)!=endrow && (j-1)!=endcolumn))
				return false;
		}
	}
	if (startrow < endrow && startcolumn > endcolumn)	//left down
	{
		for (int i = startrow, j = startcolumn; i < endrow; i++, j--)
		{
			if (Pieces[i + 1][j - 1] != ' ' && ((i+1)!=endrow && (j-1)!=endcolumn))
				return false;
		}
	}
	return true;
}

bool whitebishopmovement(char Pieces[8][8], int realinput[4])		//Killing, Blocking, Simple moves
{
	int startcolumn = realinput[0];
	int startrow = realinput[1];
	int endcolumn = realinput[2];
	int endrow = realinput[3];
	bool bishopvalid = true;
	bishopvalid = bishopvalidation(Pieces, realinput);

	if (Pieces[endrow][endcolumn] == ' ' || blackkill(Pieces, endrow,endcolumn)==true)
	{
		if (bishopvalid == true)
		{
			for (int i = 1; i < 8; i++)
			{
				if (endcolumn == startcolumn + i && endrow == startrow + i)		//RIGHT DOWN
				{
					Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
					Pieces[startrow][startcolumn] = ' ';
					return true;
				}
				if (endcolumn == startcolumn - i && endrow == startrow - i)		//LEFT UP
				{
					Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
					Pieces[startrow][startcolumn] = ' ';
					return true;
				}
				if (endcolumn == startcolumn + i && endrow == startrow - i)		//RIGHT UP
				{
					Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
					Pieces[startrow][startcolumn] = ' ';
					return true;
				}
				if (endcolumn == startcolumn - i && endrow == startrow + i)		//LEFT DOWN
				{
					Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
					Pieces[startrow][startcolumn] = ' ';
					return true;
				}
			}
		}
	}
	return false;
}

bool blackbishopmovement(char Pieces[8][8], int realinput[4])		//Killing, Blocking, Simple moves
{
	int startcolumn = realinput[0];
	int startrow = realinput[1];
	int endcolumn = realinput[2];
	int endrow = realinput[3];
	bool bishopvalid = true;
	bishopvalid = bishopvalidation(Pieces, realinput);

	if (Pieces[endrow][endcolumn] == ' ' || whitekill(Pieces, endrow,endcolumn)==true)
	{
		if (bishopvalid == true)
		{
			for (int i = 1; i < 8; i++)
			{
				if (endcolumn == startcolumn + i && endrow == startrow + i)
				{
					Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
					Pieces[startrow][startcolumn] = ' ';
					return true;
				}
				if (endcolumn == startcolumn - i && endrow == startrow - i)
				{
					Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
					Pieces[startrow][startcolumn] = ' ';
					return true;
				}
				if (endcolumn == startcolumn + i && endrow == startrow - i)
				{
					Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
					Pieces[startrow][startcolumn] = ' ';
					return true;
				}
				if (endcolumn == startcolumn - i && endrow == startrow + i)
				{
					Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
					Pieces[startrow][startcolumn] = ' ';
					return true;
				}
			}
		}
	}
	return false;
}

bool whitequeenmovement(char Pieces[8][8], int realinput[4])	//Killing, Blocking, Simple moves
{
	int startcolumn = realinput[0];
	int startrow = realinput[1];
	int endcolumn = realinput[2];
	int endrow = realinput[3];
	if (whitebishopmovement(Pieces, realinput) == true || whiterookmovement(Pieces, realinput) == true)
	{
		return true;
	}
	return false;
}

bool blackqueenmovement(char Pieces[8][8], int realinput[4])	//Killing, Blocking, Simple moves
{
	int startcolumn = realinput[0];
	int startrow = realinput[1];
	int endcolumn = realinput[2];
	int endrow = realinput[3];
	if (blackbishopmovement(Pieces, realinput) == true || blackrookmovement(Pieces, realinput) == true)
	{
		return true;
	}
	return false;
}

bool whiteknightmovement(char Pieces[8][8], int realinput[4])		//Killing, Blocking, Simple moves
{
	int startcolumn = realinput[0];
	int startrow = realinput[1];
	int endcolumn = realinput[2];
	int endrow = realinput[3];
	bool kill = false;
	kill = blackkill(Pieces, endrow,endcolumn);
	if (Pieces[endrow][endcolumn] == ' ' || kill == true)
	{
		for (int i = 1; i < 8; i++)
		{
			if (endcolumn == startcolumn + i && endrow == startrow + (i + 1))
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;

			}
			if (endcolumn == startcolumn + i && endrow == startrow - (i + 1))
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			if (endcolumn == startcolumn - i && endrow == startrow + (i + 1))
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			if (endcolumn == startcolumn - i && endrow == startrow - (i + 1))
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			if (endcolumn == startcolumn + (i + 1) && endrow == startrow + i)
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			if (endcolumn == startcolumn + (i + 1) && endrow == startrow - i)
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			if (endcolumn == startcolumn - (i + 1) && endrow == startrow + i)
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			if (endcolumn == startcolumn - (i + 1) && endrow == startrow - i)
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
		}
	}
	return false;
}

bool blackknightmovement(char Pieces[8][8], int realinput[4])		//Killing, Blocking, Simple moves
{
	int startcolumn = realinput[0];
	int startrow = realinput[1];
	int endcolumn = realinput[2];
	int endrow = realinput[3];
	bool kill = false;
	kill = whitekill(Pieces, endrow,endcolumn);
	if (Pieces[endrow][endcolumn] == ' ' || kill == true)
	{
		for (int i = 1; i < 8; i++)
		{
			if (endcolumn == startcolumn + i && endrow == startrow + (i + 1))
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;

			}
			if (endcolumn == startcolumn + i && endrow == startrow - (i + 1))
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			if (endcolumn == startcolumn - i && endrow == startrow + (i + 1))
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			if (endcolumn == startcolumn - i && endrow == startrow - (i + 1))
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			if (endcolumn == startcolumn + (i + 1) && endrow == startrow + i)
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			if (endcolumn == startcolumn + (i + 1) && endrow == startrow - i)
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			if (endcolumn == startcolumn - (i + 1) && endrow == startrow + i)
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			if (endcolumn == startcolumn - (i + 1) && endrow == startrow - i)
			{
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
		}
	}
	return false;
}

bool blackkingmovement(char Pieces[8][8], int realinput[4])		//Killing, Blocking, Simple moves
{
	int startcolumn = realinput[0];
	int startrow = realinput[1];
	int endcolumn = realinput[2];
	int endrow = realinput[3];
	bool kill = false;
	kill = whitekill(Pieces, endrow,endcolumn);
	if (Pieces[endrow][endcolumn] == ' ' || kill == true)
	{
		if (startcolumn == endcolumn && ((startrow == endrow + 1) || (startrow == endrow - 1)))
		{
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';
			return true;
		}
		else if (startcolumn == endcolumn + 1 && ((startrow == endrow) || (startrow == endrow + 1) || (startrow == endrow - 1)))
		{
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';
			return true;
		}
		else if (startcolumn == endcolumn - 1 && ((startrow == endrow) || (startrow == endrow + 1) || (startrow == endrow - 1)))
		{
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';
			return true;
		}

	}
	else return false;
}

bool whitekingmovement(char Pieces[8][8], int realinput[4])		//Killing, Blocking, Simple moves
{
	int startcolumn = realinput[0];
	int startrow = realinput[1];
	int endcolumn = realinput[2];
	int endrow = realinput[3];
	bool kill = false;
	kill = blackkill(Pieces, endrow,endcolumn);
	if (Pieces[endrow][endcolumn] == ' ' || kill == true)
	{
		if (startcolumn == endcolumn && ((startrow == endrow + 1) || (startrow == endrow - 1)))
		{
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';
			return true;
		}
		else if (startcolumn == endcolumn + 1 && ((startrow == endrow) || (startrow == endrow + 1) || (startrow == endrow - 1)))
		{
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';
			return true;
		}
		else if (startcolumn == endcolumn - 1 && ((startrow == endrow) || (startrow == endrow + 1) || (startrow == endrow - 1)))
		{
			Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
			Pieces[startrow][startcolumn] = ' ';
			return true;
		}
	}
	else return false;

}

bool blackpawnkill(char Pieces[8][8], int row,int col)		//Killing, Blocking, Simple moves
{
	if (Pieces[row+1][col-1] == 'P' || Pieces[row+1][col-1] == 'R' || Pieces[row+1][col-1] == 'B' || Pieces[row+1][col-1] == 'N' || Pieces[row+1][col-1] == 'Q')
	{
		return true;
	}
	if (Pieces[row+1][col+1] == 'P' || Pieces[row+1][col+1] == 'R' || Pieces[row+1][col+1] == 'B' || Pieces[row+1][col+1] == 'N' || Pieces[row+1][col+1] == 'Q')
	{
		return true;
	}
	return false;
}

bool blackpawnmovement(char Pieces[8][8], int realinput[4])		//Killing, Blocking, Simple moves
{
	int startcolumn = realinput[0];
	int startrow = realinput[1];
	int endcolumn = realinput[2];
	int endrow = realinput[3];
	bool kill = false;
	kill = blackpawnkill(Pieces, startrow,startcolumn);
	if (Pieces[endrow][endcolumn] == ' ')
	{
		if (startcolumn == endcolumn) {
			if (endrow - startrow == 1) {
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			else if (endrow - startrow == 2 && startrow == 1) {
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
		}
	}
	else if(kill == true)
	{
		Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
		Pieces[startrow][startcolumn] = ' ';
		return true;
	}
	else return false;
}

bool whitepawnkill(char Pieces[8][8], int row,int col)		//Killing, Blocking, Simple moves
{
	if (Pieces[row-1][col-1] == 'p' || Pieces[row-1][col-1] == 'r' || Pieces[row-1][col-1] == 'b' || Pieces[row-1][col-1] == 'n' || Pieces[row-1][col-1] == 'q')
	{
		return true;
	}
	if (Pieces[row-1][col+1] == 'p' || Pieces[row-1][col+1] == 'r' || Pieces[row-1][col+1] == 'b' || Pieces[row-1][col+1] == 'n' || Pieces[row-1][col+1] == 'q')
	{
		return true;
	}
	return false;
}

bool whitepawnmovement(char Pieces[8][8], int realinput[4])		//Killing, Blocking, Simple moves
{
	int startcolumn = realinput[0];
	int startrow = realinput[1];
	int endcolumn = realinput[2];
	int endrow = realinput[3];
	bool kill = false;
	kill = whitepawnkill(Pieces,startrow,startcolumn);
	if (Pieces[endrow][endcolumn] == ' ')
	{
		if (startcolumn == endcolumn) {
			if (endrow - startrow == -1) {
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
			else if (endrow - startrow == -2 && startrow == 6) {
				Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
				Pieces[startrow][startcolumn] = ' ';
				return true;
			}
		}
	}
	else if(kill==true)
	{
		Pieces[endrow][endcolumn] = Pieces[startrow][startcolumn];
		Pieces[startrow][startcolumn] = ' ';
		return true;
	}
	else return false;
}

bool inputvalidation(string input, int realinput[4])
{
	//string input converted into integer
	//starting column
	if (input[0] == 'a') realinput[0] = 0;
	else    if (input[0] == 'b') realinput[0] = 1;
	else    if (input[0] == 'c') realinput[0] = 2;
	else    if (input[0] == 'd') realinput[0] = 3;
	else    if (input[0] == 'e') realinput[0] = 4;
	else    if (input[0] == 'f') realinput[0] = 5;
	else    if (input[0] == 'g') realinput[0] = 6;
	else    if (input[0] == 'h') realinput[0] = 7;
	else return false;

	if (input[1] == '1') realinput[1] = 7;
	else    if (input[1] == '2') realinput[1] = 6;
	else    if (input[1] == '3') realinput[1] = 5;
	else    if (input[1] == '4') realinput[1] = 4;
	else    if (input[1] == '5') realinput[1] = 3;
	else    if (input[1] == '6') realinput[1] = 2;
	else    if (input[1] == '7') realinput[1] = 1;
	else    if (input[1] == '8') realinput[1] = 0;
	else return false;

	if (input[2] != ' ')
		return false;

	if (input[3] == 'a') realinput[2] = 0;
	else    if (input[3] == 'b') realinput[2] = 1;
	else    if (input[3] == 'c') realinput[2] = 2;
	else    if (input[3] == 'd') realinput[2] = 3;
	else    if (input[3] == 'e') realinput[2] = 4;
	else    if (input[3] == 'f') realinput[2] = 5;
	else    if (input[3] == 'g') realinput[2] = 6;
	else    if (input[3] == 'h') realinput[2] = 7;
	else return false;

	if (input[4] == '1') realinput[3] = 7;
	else if (input[4] == '2') realinput[3] = 6;
	else if (input[4] == '3') realinput[3] = 5;
	else    if (input[4] == '4') realinput[3] = 4;
	else    if (input[4] == '5') realinput[3] = 3;
	else    if (input[4] == '6') realinput[3] = 2;
	else    if (input[4] == '7') realinput[3] = 1;
	else    if (input[4] == '8') realinput[3] = 0;
	else return false;

	return true;
}

char pawnPossiblePaths(int i, int j, char Pieces[][8],char symbol)
{
	char king;
	if (symbol == 'b')
	{
		king = 'K';
		if (Pieces[i + 1][j - 1] == king || Pieces[i + 1][j + 1] == king)
		{
			return king;
		}
	}
	else if (symbol == 'w')
	{
		king = 'k';
		if (Pieces[i - 1][j - 1] == king || Pieces[i - 1][j + 1] == king)
		{
			return king;
		}
	}
}

char bishopPossiblePaths(int i, int j, char Pieces[][8], char symbol)
{
	char king;
	if (symbol == 'b')
		king = 'K';
	else if (symbol == 'w')
		king = 'k';

	for (int a = i, b = j; a > -1 && b > -1; a--, b--)		//Left up path
	{
		if (Pieces[a - 1][b - 1] == king)
		{
			return king;
		}
		else if (Pieces[a - 1][b - 1] != ' ')
		{
			break;
		}
	}
	for (int a = i, b = j; a<8 && b>-1; a++, b--)		//Left down path
	{
		if (Pieces[a + 1][b - 1] == king)
		{
			return king;
		}
		else if (Pieces[a + 1][b - 1] != ' ')
		{

			break;
		}
	}
	for (int a = i, b = j; a > -1 && b < 8; a--, b++)		//Right up path
	{
		if (Pieces[a - 1][b + 1] == king)
		{
			return king;
		}
		else if (Pieces[a - 1][b + 1] != ' ')
		{
			break;
		}
	}
	for (int a = i, b = j; a < 8 && b < 8; a++, b++)		//Right down path
	{
		if (Pieces[a + 1][b + 1] == king)
		{
			return king;
		}
		else if (Pieces[a + 1][b + 1] != ' ')
		{
			break;
		}
	}
}

char rookPossiblePaths(int i, int j, char Pieces[][8], char symbol)
{
	char king;
	if (symbol == 'b')
		king = 'K';
	else if (symbol == 'w')
		king = 'k';
	for (int a = i, b = j; b < 8; b++)	//Right
	{
		if (Pieces[a][b + 1] == king)
			return king;
		else if (Pieces[a][b + 1] != ' ')
			break;
	}

	for (int a = i, b = j; b > -1; b--)	//Left
	{
		if (Pieces[a][b - 1] == king)
			return king;
		else if (Pieces[a][b - 1] != ' ')
			break;
	}

	for (int a = i, b = j; a > -1; a--)	//Up
	{
		if (Pieces[a - 1][b] == king)
			return king;
		else if (Pieces[a - 1][b] != ' ')
			break;
	}

	for (int a = i, b = j; a < 8; a++)	//Down
	{
		if (Pieces[a + 1][b] == king)
			return king;
		else if (Pieces[a + 1][b] != ' ')
			break;
	}
	return 'a';
}

char queenPossiblePaths(int i, int j, char Pieces[][8], char symbol)
{
	char inpath;
	inpath=bishopPossiblePaths(i, j, Pieces,symbol);
	if(inpath=='K' || inpath=='k')
	{
		
	}
	else
	{
		inpath=rookPossiblePaths(i, j, Pieces,symbol);
	}
	return inpath;
}

char knightPossiblePaths(int i, int j, char Pieces[][8], char symbol)
{
	char king;
	char whichking;
	if (symbol == 'b')
		king = 'K';
	else if (symbol == 'w')
		king = 'k';

		if (Pieces[i-1][j + 2] == king)		//1 UP 2 RIGHT
			return king;

		if (Pieces[i-2][j + 1] == king)		//2 UP 1 RIGHT
			return king;

		if (Pieces[i-1][j-2] == king)		//1 UP 2 LEFT
			return king;

		if (Pieces[i-2][j-1] == king)		//2 UP 1 LEFT
			return king;

		if (Pieces[i+1][j+2] == king)		//1 down 2 right
			return king;

		if (Pieces[i+2][j+1] == king)		//2 down 1 right
			return king;

		if (Pieces[i+1][j-2] == king)		//1 down 2 left
			return king;

		if (Pieces[i+2][j-1] == king)		//2 down 1 left
			return king;
}

char confirmCheck(char Pieces[][8])
{
	char piece;
	char symbol;
	char inpath='a';
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			piece = Pieces[i][j];
			if (piece == 'P' || piece == 'B' || piece == 'R' || piece == 'N' || piece == 'Q')
			{
				symbol = 'w';
			}
			else if (piece == 'p' || piece == 'b' || piece == 'r' || piece == 'n' || piece == 'q')
			{
				symbol = 'b';
			}

			if (piece == 'p' || piece == 'P')
			{
				inpath = pawnPossiblePaths(i, j, Pieces, symbol);
				if(inpath=='K' || inpath=='k')
				{
					break;
				}
			}
			else if (piece == 'b' || piece == 'B')
			{
				inpath = bishopPossiblePaths(i, j, Pieces, symbol);
				if(inpath=='K' || inpath=='k')
				{
					break;
				}
			}
			else if (piece == 'r' || piece == 'R')
			{
				inpath = rookPossiblePaths(i, j, Pieces, symbol);
				if(inpath=='K' || inpath=='k')
				{
					break;
				}
			}
			else if (piece == 'n' || piece == 'N')
			{
				inpath = knightPossiblePaths(i, j, Pieces, symbol);
				if(inpath=='K' || inpath=='k')
				{
					break;
				}
			}
			else if (piece == 'q' || piece == 'Q')
			{
				inpath = queenPossiblePaths(i, j, Pieces, symbol);
				if(inpath=='K' || inpath=='k')
				{
					break;
				}
			}
		}
		if(inpath=='K' || inpath=='k')
		{
			break;
		}
	}
	return inpath;
}

void drawcoordinates()
{
	COLORREF lightbrown = RGB(163,103,23);
	COLORREF darkbrown = RGB(106,33,7);
	COLORREF black = RGB(00,00,00);
	COLORREF white = RGB(255,255,255);
	COLORREF peach = RGB(243,189,47);
	char num[3];

	int y=70;
	int x=650;
	for(int i=8;i>0;i--)
	{
		num1(i,num);
		myDrawTextWithFont(x,y,20,num,peach,black);
		y=y+48;
	}

	y=450;
	x=270;

	char chr[2];
	for(int i=1;i<9;i++)
	{
		if(i==1)
		{
			chr[0]='a';
			chr[1]='\0';
		}
		else if(i==2)
		{
			chr[0]='b';
			chr[1]='\0';
		}
		else if(i==3)
		{
			chr[0]='c';
			chr[1]='\0';
		}
		else if(i==4)
		{
			chr[0]='d';
			chr[1]='\0';
		}
		else if(i==5)
		{
			chr[0]='e';
			chr[1]='\0';
		}
		else if(i==6)
		{
			chr[0]='f';
			chr[1]='\0';
		}
		else if(i==7)
		{
			chr[0]='g';
			chr[1]='\0';
		}
		else if(i==8)
		{
			chr[0]='h';
			chr[1]='\0';
		}

		myDrawTextWithFont(x,y,20,chr,peach,black);
		x=x+48;
	}
}

void drawboard(char Pieces[][8])
{
	COLORREF lightbrown = RGB(163,103,23);
	COLORREF darkbrown = RGB(106,33,7);

	int x=250,y=60,count=0;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(count%2==0)
			{
				myRect(x,y,x+48,y+48,lightbrown,lightbrown);
			}
			else
			{
				myRect(x,y,x+48,y+48,darkbrown,darkbrown);
			}
			x=x+48;
			count++;
		}
		count++;
		x=250;
		y=y+48;
	}
	drawcoordinates();
}

void triUp(int x,int y,COLORREF clr,int size)
{
	for(int i=-size;i<size;i++)
	{
		myLine(x,y-10,x+i,y,clr);
	}
}

void drawPawn(int x,int y,char player)
{
	COLORREF clr = RGB(255,255,255);
	if(player=='P')
	{
		clr = RGB(255,255,255);
	}
	else if(player=='p')
	{
		clr = RGB(00,00,00);
	}

	myRect(x,y,x+20,y+5,clr,clr);
	myRect(x+7,y-15,x+12,y,clr,clr);
	triUp(x+10,y,clr,10);
	myEllipse(x+4,y-25,x+14,y-15,clr,clr);

}

void drawRook(int x,int y,char player)
{
	COLORREF clr = RGB(255,255,255);
	if(player=='R')
	{
		clr = RGB(255,255,255);
	}
	else if(player=='r')
	{
		clr = RGB(00,00,00);
	}
	myRect(x,y,x+20,y+5,clr,clr);
	myRect(x+5,y-15,x+14,y,clr,clr);
	myRect(x+2,y-22,x+5,y-15,clr,clr);
	myRect(x+14,y-22,x+17,y-15,clr,clr);
	myRect(x+8,y-22,x+11,y-15,clr,clr);
}

void drawKnight(int x,int y,char player)
{
	COLORREF clr = RGB(255,255,255);
	COLORREF eyeclr = RGB(0,0,0);
	if(player=='N')
	{
		clr = RGB(255,255,255);
		eyeclr = RGB(0,0,0);
	}
	else if(player=='n')
	{
		clr = RGB(00,00,00);
		eyeclr = RGB(255,255,255);;
	}

	myRect(x,y-20,x+20,y-10,clr,clr);
	myRect(x,y+2,x+30,y+7,clr,clr);
	myRect(x+17,y-10,x+20,y+2,clr,clr);
	myEllipse(x,y-25,x+20,y-20,clr,clr);
	myEllipse(x+18,y+5,x+25,y-20,clr,clr);
	myEllipse(x+3,y-19,x+7,y-15,eyeclr,eyeclr);
}

void drawBishop(int x,int y,char player)
{
	COLORREF clr = RGB(255,255,255);
	if(player=='B')
	{
		clr = RGB(255,255,255);
	}
	else if(player=='b')
	{
		clr = RGB(00,00,00);
	}
	myRect(x,y,x+20,y+5,clr,clr);
	myRect(x+9,y-20,x+13,y,clr,clr);
	myEllipse(x+3,y-26,x+17,y-14,clr,clr);
	//myRect(x+10,y-30,x+12,y-26,clr,clr);
}

void drawKing(int x,int y,char player)
{
	COLORREF clr = RGB(255,255,255);
	if(player=='K')
	{
		clr = RGB(255,255,255);
	}
	else if(player=='k')
	{
		clr = RGB(00,00,00);
	}
	myRect(x,y-2,x+20,y+5,clr,clr);
	myRect(x+7,y-20,x+14,y,clr,clr);
	myRect(x+5,y-25,x+16,y-18,clr,clr);
	myRect(x+10,y-32,x+12,y-25,clr,clr);
	myRect(x+7,y-30,x+15,y-29,clr,clr);

}

void drawQueen(int x,int y,char player)
{
	COLORREF clr = RGB(255,255,255);
	if(player=='Q')
	{
		clr = RGB(255,255,255);
	}
	else if(player=='q')
	{
		clr = RGB(00,00,00);
	}
	myRect(x,y-2,x+20,y+5,clr,clr);
	myRect(x+7,y-20,x+14,y,clr,clr);
	myRect(x+5,y-23,x+16,y-14,clr,clr);
	triUp(x+10,y-20,clr,6);
	myRect(x+10,y-32,x+12,y-25,clr,clr);
}

void printboard(char Pieces[8][8],int xcord[],int ycord[])
{
	system("CLS");
	drawboard(Pieces);
	for (int i=0;i<8;i++) 
	{
		for (int j=0;j<8;j++) 
		{
			if(Pieces[i][j]=='P')
			{
				drawPawn(xcord[j],ycord[i],'P');
			}
			else if(Pieces[i][j]=='p')
			{
				drawPawn(xcord[j],ycord[i],'p');
			}
			else if(Pieces[i][j]=='R')
			{
				drawRook(xcord[j],ycord[i],'R');
			}
			else if(Pieces[i][j]=='r')
			{
				drawRook(xcord[j],ycord[i],'r');
			}
			else if(Pieces[i][j]=='B')
			{
				drawBishop(xcord[j],ycord[i],'B');
			}
			else if(Pieces[i][j]=='b')
			{
				drawBishop(xcord[j],ycord[i],'b');
			}
			else if(Pieces[i][j]=='N')
			{
				drawKnight(xcord[j],ycord[i],'N');
			}
			else if(Pieces[i][j]=='n')
			{
				drawKnight(xcord[j],ycord[i],'n');
			}
			else if(Pieces[i][j]=='Q')
			{
				drawQueen(xcord[j],ycord[i],'Q');
			}
			else if(Pieces[i][j]=='q')
			{
				drawQueen(xcord[j],ycord[i],'q');
			}
			else if(Pieces[i][j]=='K')
			{
				drawKing(xcord[j],ycord[i],'K');
			}
			else if(Pieces[i][j]=='k')
			{
				drawKing(xcord[j],ycord[i],'k');
			}
		}
	}
}

bool confirmCheckMate(char whichking,int kingrow,int kingcol,char Pieces[][8],int xcord[],int ycord[],int endR,int endC,char oldMove)
{
	int oldrow,oldcol;
	oldrow=kingrow;
	oldcol=kingcol;
	int realinput[4];
	char oldpiece;
	bool checkMate=true;
	bool valid=false;
	{
		realinput[0]=kingcol;		//Possibility to move left
		realinput[1]=kingrow;
		realinput[2]=kingcol-1;
		realinput[3]=kingrow;

		oldpiece=Pieces[kingrow][kingcol-1];

		if(whichking=='K')
			valid=whitekingmovement(Pieces,realinput);
		else
			valid=blackkingmovement(Pieces,realinput);

		printboard(Pieces,xcord,ycord);

		if(confirmCheck(Pieces)==whichking)
		{
			Pieces[kingrow][kingcol-1]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
		}
		else
		{
			Pieces[kingrow][kingcol-1]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
			checkMate=false;
		}
	}
	{
		realinput[0]=kingcol;		//Possibility to move right
		realinput[1]=kingrow;
		realinput[2]=kingcol+1;
		realinput[3]=kingrow;

		oldpiece=Pieces[kingrow][kingcol+1];

		if(whichking=='K')
			valid=whitekingmovement(Pieces,realinput);
		else
			valid=blackkingmovement(Pieces,realinput);

		if(confirmCheck(Pieces)==whichking)
		{
			Pieces[kingrow][kingcol+1]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
		}
		else
		{
			Pieces[kingrow][kingcol+1]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
			checkMate=false;
		}
	}
	{
		realinput[0]=kingcol;		//Possibility to move Up
		realinput[1]=kingrow;
		realinput[2]=kingcol;
		realinput[3]=kingrow-1;

		oldpiece=Pieces[kingrow-1][kingcol];

		if(whichking=='K')
			valid=whitekingmovement(Pieces,realinput);
		else
			valid=blackkingmovement(Pieces,realinput);

		if(confirmCheck(Pieces)==whichking)
		{
			Pieces[kingrow-1][kingcol]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
		}
		else
		{
			Pieces[kingrow-1][kingcol]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
			checkMate=false;
		}
	}
	{
		realinput[0]=kingcol;		//Possibility to move Down
		realinput[1]=kingrow;
		realinput[2]=kingcol;
		realinput[3]=kingrow+1;

		oldpiece=Pieces[kingrow+1][kingcol];

		if(whichking=='K')
			valid=whitekingmovement(Pieces,realinput);
		else
			valid=blackkingmovement(Pieces,realinput);

		if(confirmCheck(Pieces)==whichking)
		{
			Pieces[kingrow+1][kingcol]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
		}
		else
		{
			Pieces[kingrow+1][kingcol]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
			checkMate=false;
		}
	}
	{
		realinput[0]=kingcol;		//Possibility to move Right Down
		realinput[1]=kingrow;
		realinput[2]=kingcol+1;
		realinput[3]=kingrow+1;

		oldpiece=Pieces[kingrow+1][kingcol+1];

		if(whichking=='K')
			valid=whitekingmovement(Pieces,realinput);
		else
			valid=blackkingmovement(Pieces,realinput);

		if(confirmCheck(Pieces)==whichking)
		{
			Pieces[kingrow+1][kingcol+1]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
		}
		else
		{
			Pieces[kingrow+1][kingcol+1]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
			checkMate=false;
		}
	}
	{
		realinput[0]=kingcol;		//Possibility to move Left Down
		realinput[1]=kingrow;
		realinput[2]=kingcol-1;
		realinput[3]=kingrow+1;

		oldpiece=Pieces[kingrow+1][kingcol-1];

		if(whichking=='K')
			valid=whitekingmovement(Pieces,realinput);
		else
			valid=blackkingmovement(Pieces,realinput);

		if(confirmCheck(Pieces)==whichking)
		{
			Pieces[kingrow+1][kingcol-1]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
		}
		else
		{
			Pieces[kingrow+1][kingcol-1]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
			checkMate=false;
		}
	}
	{
		realinput[0]=kingcol;		//Possibility to move Right Up
		realinput[1]=kingrow;
		realinput[2]=kingcol+1;
		realinput[3]=kingrow-1;

		oldpiece=Pieces[kingrow-1][kingcol+1];

		if(whichking=='K')
			valid=whitekingmovement(Pieces,realinput);
		else
			valid=blackkingmovement(Pieces,realinput);

		if(confirmCheck(Pieces)==whichking)
		{
			Pieces[kingrow-1][kingcol+1]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
		}
		else
		{
			Pieces[kingrow-1][kingcol+1]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
			checkMate=false;
		}
	}
	{
		realinput[0]=kingcol;		//Possibility to move Left Up
		realinput[1]=kingrow;
		realinput[2]=kingcol-1;
		realinput[3]=kingrow-1;

		oldpiece=Pieces[kingrow-1][kingcol-1];

		if(whichking=='K')
			valid=whitekingmovement(Pieces,realinput);
		else
			valid=blackkingmovement(Pieces,realinput);

		if(confirmCheck(Pieces)==whichking)
		{
			Pieces[kingrow-1][kingcol-1]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
		}
		else
		{
			Pieces[kingrow-1][kingcol-1]=oldpiece;
			Pieces[kingrow][kingcol]=whichking;
			checkMate=false;
		}
	}
	if(checkMate==true)
	{
		Pieces[endR][endC]=oldMove;
	}
	return checkMate;
}

void KingCoordinates(char Pieces[][8],char king,int &kingR,int &kingC)
{
	bool found=false;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(Pieces[i][j]==king)
			{
				found=true;
				kingR=i;
				kingC=j;
				break;
			}
		}
		if(found==true)
			break;
	}
}

void savegame(int count,int kingR,int kingC, char whichkingisincheck, bool incheck, bool validturn, char Pieces[8][8],int player1timeleft,int player2timeleft,int gameMode)
{
	ofstream WriteIntVarFile("intvar.txt");		//Saving integer variables in separate file
	WriteIntVarFile<<count<<std::endl;
	WriteIntVarFile<<kingR<<std::endl;
	WriteIntVarFile<<kingC<<std::endl;
	WriteIntVarFile<<player1timeleft<<std::endl;
	WriteIntVarFile<<player2timeleft<<std::endl;
	WriteIntVarFile<<gameMode<<std::endl;
	WriteIntVarFile.close();

	ofstream BoolVarFile("boolvar.txt");		//Saving boolean variables in separate file
	BoolVarFile<<validturn<<std::endl;
	BoolVarFile<<incheck<<std::endl;
	BoolVarFile.close();

	ofstream CharVarFile("charvar.txt");		//Saving char variables in separate file
	CharVarFile<<whichkingisincheck<<std::endl;
	CharVarFile.close();

	ofstream BoardFile("board.txt");			//Saving condition of board in file
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			BoardFile<<Pieces[i][j]<<std::endl;
	BoardFile.close();
}

void fillInitialBoard(char Pieces[8][8])
{
	Pieces[0][0]='r';
	Pieces[0][1]='n';
	Pieces[0][2]='b';
	Pieces[0][3]='q';
	Pieces[0][4]='k';
	Pieces[0][5]='b';
	Pieces[0][6]='n';
	Pieces[0][7]='r';
	for(int i=0;i<8;i++)
	{
		Pieces[1][i]='p';
	}
	for(int i=0;i<4;i++)
		for(int j=0;j<8;j++)
			Pieces[i][j]=' ';

	for(int i=0;i<8;i++)
	{
		Pieces[6][i]='P';
	}

	Pieces[7][0]='R';
	Pieces[7][1]='N';
	Pieces[7][2]='B';
	Pieces[7][3]='Q';
	Pieces[7][4]='K';
	Pieces[7][5]='B';
	Pieces[7][6]='N';
	Pieces[7][7]='R';
}

void promotepawn(char symbol,int row, int col,char Pieces[][8])
{
	int num=0;
	while(num==0)
	{
		cout<<"--PAWN PROMOTION--"<<endl;
		cout<<"1-Queen"<<endl;
		cout<<"2-Bishop"<<endl;
		cout<<"3-Knight"<<endl;
		cout<<"4-Rook"<<endl;
		cin>>num;
		cin.ignore();
		if(num!=1 && num!=2 && num!=3 && num!=4)
			num=0;
	}
	if(num==1)
	{
		if(symbol=='p')
			Pieces[row][col]='q';
		else
			Pieces[row][col]='Q';
	}
	else if(num==2)
	{
		if(symbol=='p')
			Pieces[row][col]='b';
		else
			Pieces[row][col]='B';
	}
	else if(num==3)
	{
		if(symbol=='p')
			Pieces[row][col]='n';
		else
			Pieces[row][col]='N';
	}
	else if(num==4)
	{
		if(symbol=='p')
			Pieces[row][col]='r';
		else
			Pieces[row][col]='R';
	}
}

void pawnpromotion(int row,int col,char Pieces[][8],char symbol)
{
	if(symbol=='p' && row==7)
	{
		promotepawn(symbol,row,col,Pieces);
	}
	else if(symbol=='P' && row==0)
	{
		promotepawn(symbol,row,col,Pieces);
	}
}

int main()
{
	COLORREF lightbrown = RGB(163,103,23);
	COLORREF black = RGB(00,00,00);
	
	int player1timeleft=600, player2timeleft=600 ,player1timetaken,player2timetaken;
	bool timerStart=false;
	clock_t player1start,player2start;

	int gameMode,gametype,oldrow, oldcol, count=0, kingR=0, kingC=0, startcolumn, startrow, endcolumn, endrow, realinput[4], xcord[8], ycord[8];
	char oldpiece, oldpiece2, oldMove, whichkingisincheck='a';
	bool game = true, incheck=false, valid=false, validturn=false, inputvalid=false,handshakeBlack=false,handshakeWhite=false,finalHandshake=false,cancelhandshake=false;
	bool blacksurrender=false, whitesurrender=false;
	string input;

	//We have to keep track of count,kingR,kingC,whichkingisincheck,incheck,validturn,Pieces

	for(int i=260,j=95,k=0;k<8;i=i+48,j=j+48,k++)
	{
		xcord[k]=i;
		ycord[k]=j;
	}
	char Pieces[8][8] = {
	'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
	'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
	'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'

	};

	myDrawTextWithFont(230,150,200," CHESS ",black,lightbrown);
	getch();

	cout<<"Enter 1 to start new game"<<endl;
	cout<<"Enter 2 to load a game"<<endl;
	cin>>gametype;
	cin.ignore();

	if(gametype==1)
	{
		cout<<"Enter 1 to play classic mode"<<endl;
		cout<<"Enter 2 to play rapid mode"<<endl;
		cout<<"Enter 3 to play blitz mode"<<endl;
		cin>>gameMode;
		cin.ignore();

		if(gameMode==3)
		{
			player1timeleft=300, player2timeleft=300;
		}
	}
	else if(gametype==2)
	{
		string line;
		int counter=0;
		ifstream ReadIntVarFile("intvar.txt");
		while(getline (ReadIntVarFile,line))
		{
			stringstream geek(line);
			if(counter==0)
				geek>>count;
			else if(counter==1)
				geek>>kingR;
			else if(counter==2)
				geek>>kingC;
			else if(counter==3)
				geek>>player1timeleft;
			else if(counter==4)
				geek>>player2timeleft;
			else if(counter==5)
				geek>>gameMode;
			counter++;
		}
		ReadIntVarFile.close();

		counter=0;
		ifstream ReadBoolVarFile("boolvar.txt");
		while(getline (ReadBoolVarFile,line))
		{
			bool read;
			if(line=="1")
				read=true;
			else if(line=="0")
				read=false;
			if(counter==0)
				validturn=read;
			else if(counter==1)
				incheck=read;
			counter++;
		}
		ReadBoolVarFile.close();

		ifstream ReadCharVarFile("charvar.txt");
		while(getline (ReadCharVarFile,line))
		{
			whichkingisincheck=line[0];
		}
		ReadCharVarFile.close();

		int i=0,j=0;
		ifstream ReadBoardFile("board.txt");
		while(getline(ReadBoardFile,line))
		{
			Pieces[i][j]=line[0];
			j++;
			if(j==8)
			{
				i++;
				j=0;
			}
		}
		ReadBoardFile.close();
	}

	bool firstTurn=true;
	bool win=false;

	while (game == true) 
	{
		printboard(Pieces,xcord,ycord);
		if(count%2==0)
		{
			cout<<"---WHITE's TURN---"<<endl;
		}
		else if(count%2==1)
		{
			cout<<"---BLACK's TURN---"<<endl;
		}

		if(gameMode==2 || gameMode==3)
		{
			if(count%2==0)
			{
				if(firstTurn!=true)
				{
					player2timetaken=(int)(clock()-player2start)/CLOCKS_PER_SEC;
					player2timeleft=player2timeleft-player2timetaken;
					if(gameMode==2)
					{
						player2timeleft=player2timeleft+10;
					}
					cout<<"Your time left:"<<player1timeleft<<endl;
					player1start=clock();
				}
				else
				{
					cout<<"Your time left:"<<player1timeleft<<endl;
					player1start=clock();
					firstTurn=false;
				}
			}
			else if(count%2==1)
			{
				player1timetaken=(int)(clock()-player1start)/CLOCKS_PER_SEC;
				player1timeleft=player1timeleft-player1timetaken;
				if(gameMode==2)
				{
					player1timeleft=player1timeleft+10;
				}
				cout<<"Your time left:"<<player2timeleft<<endl;
				player2start=clock();
			}
		}

		if(gameMode==2 || gameMode==3)
		{
			if(player1timeleft<0)
			{
				system("CLS");
				cout<<"White ran out of time"<<endl;
				cout<<"Black wins"<<endl;
				getch();
				break;
			}
			else if(player2timeleft<0)
			{
				system("CLS");
				cout<<"Black ran out of time"<<endl;
				cout<<"White wins"<<endl;
				getch();
				break;
			}
		}

		validturn = false;
		while (validturn == false)
		{
			if(incheck==true)
			{
				KingCoordinates(Pieces,whichkingisincheck,kingR,kingC);
				if(whichkingisincheck=='k')
					cout << "Black king is in check"<<endl;
				else
					cout << "White king is in check"<<endl;
			}

			if(handshakeWhite==true)
			{
				cout<<"Player 1 offered a handshake"<<endl;
			}
			else if(handshakeBlack==true)
			{
				cout<<"Player 2 offered a handshake"<<endl;
			}
			cout << "Enter your move: \n";
			getline(cin, input);

			if(input=="surrender")
			{
				if(count%2==0)
				{
					whitesurrender=true;
					break;
				}
				else if (count%2==1)
				{
					blacksurrender=true;
					break;
				}
			}
			if(input=="handshake")
			{
				cancelhandshake=false;
				if(count%2==0)
				{
					if(handshakeBlack==true)
					{
						finalHandshake=true;
						break;
					}
					handshakeWhite=true;
				}
				else
				{
					if(handshakeWhite==true)
					{
						finalHandshake=true;
						break;
					}
					handshakeBlack=true;
				}
				break;
			}
			else
			{
				if(handshakeWhite==true || handshakeBlack==true)
					cancelhandshake=true;
			}
			if(input=="save")
			{
				cout<<"Saved"<<endl;
				cout << "Enter your move: \n";
				savegame(count,kingR,kingC,whichkingisincheck,incheck,validturn,Pieces,player1timeleft,player2timeleft,gameMode);
				getline(cin, input);
			}

			inputvalid = inputvalidation(input, realinput);
			startcolumn = realinput[0];
			startrow = realinput[1];
			endcolumn = realinput[2];
			endrow = realinput[3];

			oldMove=Pieces[endrow][endcolumn];

			if (count % 2 == 0)
			{
				if (whiteturn(Pieces, startcolumn, startrow) == false)
					validturn = false;
				else
					validturn = true;
			}
			else  if (count % 2 == 1)
			{
				if (blackturn(Pieces, startcolumn, startrow) == false)
					validturn = false;
				else 
					validturn = true;
			}
		}

		if(finalHandshake==true)
		{
			system("CLS");
			cout<<"Match drawn"<<endl;
			cout<<"Both players decided handshake"<<endl;
			break;
		}
		if(whitesurrender==true)
		{
			system("CLS");
			cout<<"White resigned"<<endl;
			cout<<"Black Wins"<<endl;
			break;
		}
		else if(blacksurrender==true)
		{
			system("CLS");
			cout<<"Black resigned"<<endl;
			cout<<"White Wins"<<endl;
			break;
		}

		if(handshakeWhite==true || handshakeBlack==true)
		{}
		else
		{
			oldrow=startrow;
			oldcol=startcolumn;
			oldpiece=Pieces[startrow][startcolumn];
			oldpiece2=Pieces[endrow][endcolumn];

			if (Pieces[startrow][startcolumn] == 'p') 
			{
				valid = blackpawnmovement(Pieces, realinput);
				if(valid==true)
				{
					pawnpromotion(endrow,endcolumn,Pieces,'p');
				}
			}
			else if (Pieces[startrow][startcolumn] == 'P') 
			{
				valid = whitepawnmovement(Pieces, realinput);
				if(valid==true)
				{
					pawnpromotion(endrow,endcolumn,Pieces,'P');
				}
			}

			if (Pieces[startrow][startcolumn] == 'r') 
			{
				valid = blackrookmovement(Pieces, realinput);
			}

			if (Pieces[startrow][startcolumn] == 'R') 
			{
				valid = whiterookmovement(Pieces, realinput);
			}

			if (Pieces[startrow][startcolumn] == 'n') 
			{
				valid = blackknightmovement(Pieces, realinput);
			}

			if (Pieces[startrow][startcolumn] == 'N') 
			{
				valid = whiteknightmovement(Pieces, realinput);
			}

			if (Pieces[startrow][startcolumn] == 'b') 
			{
				valid = blackbishopmovement(Pieces, realinput);
			}

			if (Pieces[startrow][startcolumn] == 'B') 
			{
				valid = whitebishopmovement(Pieces, realinput);
			}

			if (Pieces[startrow][startcolumn] == 'q') 
			{
				valid = blackqueenmovement(Pieces, realinput);
			}
			if (Pieces[startrow][startcolumn] == 'Q') 
			{
				valid = whitequeenmovement(Pieces, realinput);
			}

			if (Pieces[startrow][startcolumn] == 'k')
			{
				valid = blackkingmovement(Pieces, realinput);
			}
			if (Pieces[startrow][startcolumn] == 'K') 
			{
				valid = whitekingmovement(Pieces, realinput);
			}

			if(incheck==true)
			{
				if(confirmCheckMate(whichkingisincheck,kingR,kingC,Pieces,xcord,ycord,endrow,endcolumn,oldMove)==true)
				{
					printboard(Pieces,xcord,ycord);
					cout<<"CHECKMATE!!!!!"<<endl;
					if(whichkingisincheck=='K')
					{
						cout<<"Black wins"<<endl;
					}
					else
					{
						cout<<"White wins"<<endl;
					}
					getch();
					break;
				}
				if(confirmCheck(Pieces)=='K' || confirmCheck(Pieces)=='k')
				{
					count--;
					Pieces[endrow][endcolumn]=oldpiece2;
					Pieces[oldrow][oldcol]=oldpiece;
				}
			}
			//else
			//{
			//	//To check stalemate
			//	if(confirmCheckMate(whichkingisincheck,kingR,kingC,Pieces,xcord,ycord,endrow,endcolumn,oldMove)==true)
			//	{
			//		cout<<"STALEMATE!!"<<endl;
			//	}
			//}

			whichkingisincheck=confirmCheck(Pieces);
			if (whichkingisincheck == 'k' || whichkingisincheck=='K')
			{
				incheck=true;
			}
			else if(whichkingisincheck=='a')
			{
				incheck=false;
			}
		}

		if(cancelhandshake==true)
		{
			handshakeWhite=false;
			handshakeBlack=false;
		}
		if(handshakeWhite==true || handshakeBlack==true)
			valid=true;
		if(valid==true)
			count++;
	}
	getch();
	system("pause");
	return 0;

}
