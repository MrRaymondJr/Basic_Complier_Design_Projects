#include<iostream>
#include<cctype>
#include "STACKPAC.h"
using namespace std;

int main()
{
	  // Predictive Parsing Table
	int predParse[5][8] = { { 1, 0, 0, 0, 0, 1, 0, 0 },
							{ 0, 2, 3, 0, 0, 1, 9, 9 },
							{ 4, 0, 0, 0, 0, 4, 0, 0 },
							{ 0, 9, 9, 5, 6, 0, 9, 9 },
							{ 7, 0, 0, 0, 0, 8, 0, 0 } };
	  /* TQ=[1], +TQ=[2], -TQ=[3], FR=[4], *FR=[5], /FR=[6],
	      i=[7], (E)=[8], [lambda]=[9], [empty]=[0] */

	  // Initalize
	STACK<char, 10> POST;
	STACK<char, 10> TEMP;

	char cont;

	  // Loops for each input string
	do
	{
		  // Initialize
		POST.clearStack();
		TEMP.clearStack();

		char input, display;
		char st = NULL; 
		int row, column, cell;
		bool Fail = false;

		  /* Expession ends with '&' cause $ is a part of input string,
		      and therefore needs to be read.*/
		cout << "Enter a postfix expression with '&' at the end: ";
		cin >> input;
		POST.pushStack('$');
		POST.pushStack('E');


		  // Loops for each char in input
		while (input != '&')
		{
			cout << "Input: " << input << endl;
			  // Loops until current input = current stack
			do {

				st = POST.popStack();

				  // If a match is found
				if (st == input)
				{
					  // Puts current POST stack into TEMP
					while (!POST.emptyStack())
					{
						display = POST.popStack();
						TEMP.pushStack(display);
					}  // End inner while loop
					cout << "Current Stack: ";

					  /* Displays TEMP stack and returns
					      info back into POST stack */
					while (!TEMP.emptyStack())
					{
						display = TEMP.popStack();
						cout << display;
						POST.pushStack(display);
					}  // End inner while loop
					cout << endl;
				}  // End if statement
				else
				{
					  // Switch statement finds row of predParse
					switch (st)
					{
					case 'E':
						row = 0;
						break;
					case 'Q':
						row = 1;
						break;
					case 'T':
						row = 2;
						break;
					case'R':
						row = 3;
						break;
					case'F':
						row = 4;
						break;
					default:
						Fail = true;
					} // End row switch

					  // Switch statement finds column of predParse
					switch (input)
					{
					case 'i':
						column = 0;
						break;
					case '+':
						column = 1;
						break;
					case '-':
						column = 2;
						break;
					case'*':
						column = 3;
						break;
					case'/':
						column = 4;
						break;
					case'(':
						column = 5;
						break;
					case')':
						column = 6;
						break;
					case'$':
						column = 7;
						break;
					default:
						Fail = true;
					} // End column switch

					  /* If the row or column info didn't belong
					      to the table, then break this loop */
					if (Fail)
						break;

					  // Uses row and column to find specific cell info
					cell = predParse[row][column];

					  /* Switch statement takes the cell info and completes
					      the actions that cell normally does */
					switch (cell)
					{
					case 0:  // [Empty]
						Fail = true;
						break;
					case 1:  // TQ
						POST.pushStack('Q');
						POST.pushStack('T');
						break;
					case 2:  // +TQ
						POST.pushStack('Q');
						POST.pushStack('T');
						POST.pushStack('+');
						break;
					case 3:  // -TQ
						POST.pushStack('Q');
						POST.pushStack('T');
						POST.pushStack('-');
						break;
					case 4:  // FR
						POST.pushStack('R');
						POST.pushStack('F');
						break;
					case 5:  // *FR
						POST.pushStack('R');
						POST.pushStack('F');
						POST.pushStack('*');
						break;
					case 6:  // /FR
						POST.pushStack('R');
						POST.pushStack('F');
						POST.pushStack('/');
						break;
					case 7:  // I
						POST.pushStack('i');
						break;
					case 8:  // (E)
						POST.pushStack(')');
						POST.pushStack('E');
						POST.pushStack('(');
					case 9:  // [lambda]
						break;
					} // End cell switch

				}  // End outer else

				   /* If the cell info is empty,
				       then break this loop */
				if (Fail)
					break;

				// Loops till input = stack
			} while (st != input);  // End do while loop

		      /* If info was wrong or cell was empty,
				  then break this input string */
			if (Fail)
				break;
			else  // Moves to next char in input string
				cin >> input;

			// Loops for the whole input string
		} // End while loop

		  // If the input string failed
		if (Fail)
		{
			cout << "Input string failed!" << endl;
			while (input != '&')  // Clears cin
				cin >> input;
		}  // End if
		else
			cout << "Input string successful!" << endl;

		  // Checks if user wants to enter another input string
		cout << endl << "Continue(y/n)? ";
		cin >> cont;
		cout << endl;

	} while ((tolower(cont) == 'y'));  // End do while loop

	system("pause");
	return 0;

} // End main

/**/