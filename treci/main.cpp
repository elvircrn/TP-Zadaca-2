#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <cctype>
#include <utility>
#include <type_traits>
#include <stdexcept>
#include <iomanip>

int sentinel (int **matrix, int i, int j) {
    if (i < 0 || j < 0)
        return 0;
    else
        return matrix [i] [j];
}

int NewtonovBinomniKoeficijent(int n, int k)
{
	int a = 1, b = 1;
	std::vector <int> brojnik, nazivnik;

    for (int i = n - k + 1; i <= n; i++)
		brojnik.push_back(i);
	for (int i = 2; i <= k; i++)
		nazivnik.push_back(i);

	bool found = false;
	for (int i = 0; i < brojnik.size(); i++)
	{
		found = false;
		for (int j = 0; j < nazivnik.size(); j++)
		{
			if (std::__gcd(brojnik [i], nazivnik [j]) != 1)
			{
				int x = std::__gcd(brojnik [i], nazivnik [j]);
				found = true;

				brojnik [i] /= x;
				nazivnik [j] /= x;
			}
		}

		if (!found)
			break;
	}

	for (int x : brojnik)
		a *= x;

	for (int x : nazivnik)
		b *= x;

	return a / b;
}

int PascalovTrougao(int n, int k)
{
    n--; k--;
    if(n < 0 || k < 0 || n < k)
        throw std::domain_error("Neispravni parametri!");

    int row = n + 5;
    int column = k + 5;

    int **dp(new int* [row]);
    for (int i = 0; i < row; i++)
        dp [i] = new int [column];

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= k; j++)
            dp [i] [j] = (i == 0 && j == 0) + sentinel(dp, i - 1, j - 1) + sentinel (dp, i - 1, j);

    int sol = dp [n] [k];

    for (int i = 0; i < row; i++)
        delete[] dp [i];
    delete[] dp;

    return sol;
}

template <class T>
auto Izmijeni3DKontejner (T &elements,
                          typename std::remove_reference <decltype (elements [0] [0] [0])>::type Fun (int m, int n),
                          int p = 0, int q = 0) -> typename std::remove_reference <decltype (elements [0] [0] [0])>::type
{
    bool found = false;
    for (auto &x : elements)
        for (auto &y : x)
            for (auto &z : y)
                if (z == Fun(p, q))
                {
                    z = z * z;
                    found = true;
                }

    if (found)
        return Fun(p, q);
    else
        throw std::range_error("Nije pronadjen broj!");
}

template <class T>
void print(T &elements)
{
    bool found = false;
    for (auto &x : elements)
    {
        for (auto &y : x)
        {
            for (auto &z : y)
            {
                std::cout << std::left << std::setw(5) << z;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

int main()
{
    int n, m, p, pp, qq;

    std::cout << "Unesite dimenzije 3D kontejnera: ";
    std::cin >> n >> m >> p;

    int v [3] [3] [3];
    //std::vector <std::vector <std::vector <int> > > v (n, std::vector <std::vector<int> > (m, std::vector <int>(p)));

    std::cout << "Unesite elemente: ";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < p; k++)
                std::cin >> v [i] [j] [k];

    std::cout << "Unesite brojeve p i q: ";
    std::cin >> pp >> qq;


    try
    {
        Izmijeni3DKontejner (v, PascalovTrougao, pp, qq);
        std::cout << "Kontejner nakon zamjene broja " << PascalovTrougao (pp, qq)
                  << " brojem " << PascalovTrougao (pp, qq) * PascalovTrougao (pp, qq)
                  << " glasi: " << std::endl;

        print(v);
    }
    catch (std::domain_error de)
    {
        std::cout << de.what() << std::endl;
    }
    catch (std::range_error re)
    {
        std::cout << re.what() << std::endl;
    }

    return 0;
}



/*
3 3 3
1 2 3 4 5 6 7 8 9 9 8 7 6 5 4 3 2 1 1 2 3 4 5 6 7 8 9
6 2
*/






















