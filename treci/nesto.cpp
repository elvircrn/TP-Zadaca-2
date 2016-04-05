#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

int getSize (int number)
{
	int ret = 0;
	if (number == 0)
		return 1;
	while (number)
	{
		number /= 10;
		ret++;
	}
	return ret;
}

int calc (vector <int> v)
{
	if (v.size() == 1)
		return -1;
	int ret = __gcd (v [0], v [1]);

	for (int x : v)
		cout << v << ' ';
	cout << endl;


	if (v.size() > 2)
	{
		for (int i = 2; i < v.size(); i++)
			ret = __gcd (ret, v [i]);
	}

	return ret;
}

int number, lower, upper, maximum = -1;

int get(int number, int x, int y)
{
	stringstream ss;
	ss << number;
	string str = ss.str();
	ss.clear();
    string extr = str.substr(x, y - x + 1);
	stringstream ss1;
	ss1 << extr;
	int asd;
	ss1 >> asd;
	return asd;
}

int main()
{
	cin >> number >> lower >> upper;
	
	int size = getSize(number);

	for (int i = 0; i < (1<<size); i++)
	{
		vector <int> v;
		bool valid = true;
		int pivot = 0;
		for (int j = 0; j < size; j++)
		{
			if ((1<<pivot) & i == (1<<j) & i)
				continue;
			else
			{
				int cand = get (number, pivot, j);
				if (cand < lower || upper < cand)
				{
					valid = false;
					break;
				}
				v.push_back(get (number, pivot, j));
			}

			if (valid)
				maximum = max (maximum, calc(v));
		}

		maximum = max (maximum, calc(v));
	}

	cout << maximum;
	
	
	return 0;
}


