#pragma once
#ifndef STACKPAC
#define STACKPAC

template<class T, int r>
class STACK
{
private:
	T st[r];
	int r;

public:
	void clearStack()
	{
		r = 0;
	}
	bool emptyStack()
	{
		return (r == 0) ? true : false;
	}
	bool fullStack()
	{
		return (r == n) ? true : false;
	}
	void pushStack(T x)
	{
		st[r] = x;
		r++;
	}
	T popStack()
	{
		r--;
		return st[r];
	}
};
#endif