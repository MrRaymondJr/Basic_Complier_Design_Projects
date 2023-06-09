#include "stdafx.h"
#include<iostream>
#include<cctype>
#include<string>
#include "STACKPAC.h"
using namespace std;

int main()
{
	
	  // Pred Parse Table     100 = S, 200 = R, 300 = Non-terminal column, 400 = Acc   
	int predParse[16][11] = { { 105, 00, 00, 00, 00, 104, 00, 00, 301, 302, 303 },     // 0
							  { 00, 106, 107, 00, 00, 00, 00, 400, 00, 00, 00 },       // 1
							  { 00, 203, 203, 108, 109, 00, 203, 203, 00, 00, 00 },    // 2
							  { 00, 206, 206, 206, 206, 00, 206, 206, 00, 00, 00 },    // 3
							  { 105, 00, 00, 00, 00, 00, 00, 104, 310, 302, 303 },     // 4
							  { 00, 208, 208, 208, 208, 00, 208, 208, 00, 00, 00 },    // 5
							  { 105, 00, 00, 00, 00, 00, 00, 104, 00, 311, 303 },      // 6
							  { 105, 00, 00, 00, 00, 00, 00, 104, 00, 312, 303 },      // 7
							  { 105, 00, 00, 00, 00, 00, 00, 104, 00, 00, 313 },       // 8
							  { 105, 00, 00, 00, 00, 00, 00, 104, 00, 00, 314 },       // 9
							  { 00, 106, 107, 00, 00, 00, 115, 00, 00, 00, 00 },       // 10
							  { 00, 201, 201, 108, 109, 00, 201, 201, 00, 00, 00 },    // 11
							  { 00, 202, 202, 108, 109, 00, 202, 202, 00, 00, 00 },    // 12
							  { 00, 204, 204, 204, 204, 00, 204, 204, 00, 00, 00 },    // 13
							  { 00, 205, 205, 205, 205, 00, 205, 205, 00, 00, 00 },    // 14
							  { 00, 207, 207, 207, 207, 00, 207, 270, 00, 00, 00 } };  // 15

	STACK<char, 10> POST; // Initalize STACK 

	  // CFG Left side & Right side
	char lRn[8] = { 'E', 'E', 'E', 'T', 'T', 'T', 'F', 'F' };
	string Rn[8] = {"E+T", "E-T", "T", "T*F", "T/F", "F", "(E)", "i" };
	
	char cont = 'y';  // Loops the whole project

	do
	{
		POST.clearStack();  // Clear the stack

		  // Initialize
		char input, rCol;
		char st = NULL;
		int row, column, cell, cellType = 0, cellInt, rLength;
		bool Fail = false, Acc = false;
		string popR;

		  // Expession ends with '$' 
		cout << "Enter a postfix expression with '$' at the end: ";
		cin >> input;
		POST.pushStack(0);  // Always starts with 0


		 // Loops till Acc
		while (!Acc)
		{
			cout << "Read: " << input << endl;
			  // Loops until [a,b] = Sn or Acc
			do {

				st = POST.popStack();

				  // Row of predParse is st
				row = st;
				cout << "\tpop: " << row << endl;

				  // If the last [a,b] = rn
				if (cellType == 2)
				{
					  // Switch finds col of predParse
					switch (rCol)
					{
					case 'E':
						column = 8; break;
					case 'T':
						column = 9; break;
					case 'F':
						column = 10; break;
					default:
						Fail = true; break;
					}  // End column switch
				}  // End if
				else
				{
					  // Switch finds col of predParse
					switch (input)
					{
					case 'i':
						column = 0; break;
					case '+':
						column = 1; break;
					case '-':
						column = 2; break;
					case'*':
						column = 3; break;
					case'/':
						column = 4; break;
					case'(':
						column = 5; break;
					case')':
						column = 6; break;
					case'$':
						column = 7; break;;
					default:
						Fail = true; break;
					} // End column switch
				}  // End else

				  // If row or col bad, then break loop 
				if (Fail)
					break;

				  // Uses row and column to find cell info
				cell = predParse[row][column];
				cout << "\t  [" << row << "," << input << "] = ";
				   // Gets the 100s place of the cell
				cellType = cell / 100;
				   // Gets the 10s + 1s place of the cell
				cellInt = cell % 100;

				  // Finds the type of cell, and does req work
				switch (cellType)
				{
				case 0:  // [Empty]
					Fail = true;
					break;
				case 1:  // S
					cout << "S" << cellInt << endl;
					POST.pushStack(row);
					POST.pushStack(column);
					POST.pushStack(cellInt);
					break;
				case 2:  // R
					cout << "R" << cellInt << endl;
					POST.pushStack(row);
					  // Finds the the CFG info
					rCol = lRn[cellInt - 1];
					popR = Rn[cellInt - 1];
					  // Calculates # of items popped
					rLength = 2 * popR.length();
					  // Pops the # items from rLength
					for (int i = 1; i <= rLength; i++)
						POST.popStack();
					break;
				case 3:  // Non-Terminal
					cout << cellInt << endl;
					POST.pushStack(row);
					POST.pushStack(column);
					POST.pushStack(cellInt);
					break;
				case 4:  // Accepted
					cout << "Acc." << endl;
					Acc = true;
					break;
				} // End cell switch

				  // If  cell info  empty, break loop
				if (Fail)
					break;

			} while (cellType != 1 && cellType != 4);  // End do while loop

			  // If input string failed or Acc, break while loop 
			if (Fail || Acc)
				break;
			else  // Moves to next char in input string
				cin >> input;

		  // Loops till Acc
		} // End while loop

		  // If the input string failed
		if (Fail)
		{
			cout << endl << "Input string failed!" << endl;
			while (input != '$')  // Clears cin
				cin >> input;
		}  // End if
		else
			cout << "Input string successful!" << endl;

		  // Input if user wants another input string
		cout << "continue(y/n)? ";
		cin >> cont;

	}while (cont == 'y');  // End do while loop

	return 0;
}
/*
Enter a postfix expression with '$' at the end: (i+i)*i$
Read: (
pop: 0
[0,(] = S4
Read: i
pop: 4
[4,i] = S5
Read: +
pop: 5
[5,+] = R8
pop: 4
[4,+] = 3
pop: 3
[3,+] = R6
pop: 4
[4,+] = 2
pop: 2
[2,+] = R3
pop: 4
[4,+] = 10
pop: 10
[10,+] = S6
Read: i
pop: 6
[6,i] = S5
Read: )
pop: 5
[5,)] = R8
pop: 6
[6,)] = 3
pop: 3
[3,)] = R6
pop: 6
[6,)] = 11
pop: 11
[11,)] = R1
pop: 4
[4,)] = 10
pop: 10
[10,)] = S15
Read: *
pop: 15
[15,*] = R7
pop: 0
[0,*] = 3
pop: 3
[3,*] = R6
pop: 0
[0,*] = 2
pop: 2
[2,*] = S8
Read: i
pop: 8
[8,i] = S5
Read: $
pop: 5
[5,$] = R8
pop: 8
[8,$] = 13
pop: 13
[13,$] = R4
pop: 0
[0,$] = 2
pop: 2
[2,$] = R3
pop: 0
[0,$] = 1
pop: 1
[1,$] = Acc.
Input string successful!
continue(y/n)? y
Enter a postfix expression with '$' at the end: (i*)$
Read: (
pop: 0
[0,(] = S4
Read: i
pop: 4
[4,i] = S5
Read: *
pop: 5
[5,*] = R8
pop: 4
[4,*] = 3
pop: 3
[3,*] = R6
pop: 4
[4,*] = 2
pop: 2
[2,*] = S8
Read: )
pop: 8
[8,)] =
Input string failed!
continue(y/n)? n
Press any key to continue . . .
*/