#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <exception>
#include <cstdio>
#include <stdexcept>
#include <complex>
#include <climits>
#include <string>
#include <sstream>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <iomanip>

std::string toString(const std::vector <int> &v)
{
    std::stringstream ss;

    ss << v [0];

    for (int i = 1; i < v.size(); i++)
        ss << ", " << v[i];

    return ss.str();
}

int getPeriod(const std::vector<int> &elements)
{
    bool found;

    for (int period = 1; period < elements.size(); period++)
    {
        found = true;
        for (int i = 0; i < elements.size(); i++)
        {
            if (elements [i] != elements [i % period])
            {
                found = false;
                break;
            }
        }
        if (found)
            return period;
    }

    return elements.size();
}

void clearPeriod(std::vector <int> &elements)
{
    int task = elements.size() - getPeriod(elements);
    while (task--)
        elements.pop_back();
}

void complement(std::vector <int> &elements)
{
    int maximum = *max_element(elements.begin(), elements.end());
    for (int &x : elements)
        x = maximum - x + 1;
}

void cleanVector(std::vector<int> &elements)
{
    if (getPeriod(elements) == elements.size())
        complement(elements);
    else
        clearPeriod(elements);
}
template <class Numeric>
int **AlocirajFragmentirano(std::vector<Numeric> &elements, int koliko_puta)
{
    int maximum;
    for (auto x : elements)
        if (x <= 0)
            throw std::domain_error("Izuzetak: Neispravan vektor!");

    if (koliko_puta <= 0)
        throw std::domain_error("Izuzetak: Neispravan broj ponavljanja!");

    int **matrix;

    try
    {
        maximum = *max_element(elements.begin(), elements.end());
        matrix = new int* [koliko_puta * elements.size()];
        for (int i = 0; i < koliko_puta * elements.size(); i++)
            matrix [i] = nullptr;

        int current_row = 0;

        try
        {
            for (int rep = 0; rep < koliko_puta; rep++)
            {
                for (int x : elements)
                {
                    matrix [current_row] = new int [x];
                    int current_index = maximum - x + 1;

                    for (int i = 0; i < x; i++)
                    {
                        //std::cout << "(" << current_row << ", " << i << "): " << current_index << std::endl;
                        matrix [current_row] [i] = current_index++;
                    }
                    current_row++;
                }
            }
        }
        catch (...)
        {
            for (int i = 0; i < koliko_puta * elements.size(); i++)
                delete[] matrix [i];
            delete[] matrix;
            throw;
        }
    }
    catch (...)
    {
        throw;
    }

    return matrix;
}
template <class Numeric>
int **AlocirajKontinualno(std::vector<Numeric> &elements, int koliko_puta)
{
    int maximum, num_elements = 0, num_rows = elements.size() * koliko_puta;
    for (int x : elements)
    {
        num_elements += x;
        if (x <= 0)
            throw std::domain_error("Izuzetak: Neispravan vektor!");
    }

    if (koliko_puta <= 0)
        throw std::domain_error("Izuzetak: Neispravan broj ponavljanja!");

    int **matrix { nullptr };

    try
    {
        maximum = *max_element(elements.begin(), elements.end());
        matrix = (new int* [num_rows]);

        try
        {
            matrix [0] = new int [num_elements * koliko_puta];

            int current_row = 1;

            for (int i = 0; i < koliko_puta; i++)
                for (int j = 0; j < elements.size(); j++, current_row++)
                    matrix [current_row] = matrix [current_row - 1] + elements [j];

            current_row = 0;

            for (int rep = 0; rep < koliko_puta; rep++)
            {
                for (int x : elements)
                {
                    int current_index = x;

                    for (int i = 0; i < x; i++)
                    {
                        //std::cout << typeid (matrix [current_row] [i]).name() << std::endl;
                        matrix [current_row] [i] = current_index--;
                    }
                    current_row++;
                }
            }

            return matrix;
        }
        catch (...)
        {
            delete[] matrix;
            throw;
        }
    }
    catch (...)
    {
        throw;
    }
}

template <class Numeric>
int **KreirajPoUvrnutomPravilu(std::vector<Numeric> &v, int koliko_puta, bool fragmentirano = true)
{
    cleanVector(v);

    try
    {
        if (fragmentirano)
        {
            return AlocirajFragmentirano(v, koliko_puta);
        }
        else
        {
            return AlocirajKontinualno(v, koliko_puta);
        }
    }
    catch (std::domain_error de)
    {
        throw de;
    }
    catch (std::bad_alloc ba)
    {
        throw ba;
    }
}

int main()
{
    int n, rep, type;

    std::cout << "Unesite broj elemenata vektora: ";
    std::cin >> n;

    std::vector <int> elements(n);

    std::cout << "Unesite elemente vektora: ";

    for (int i = 0; i < n; i++)
        std::cin >> elements [i];


    std::cout << "Unesite broj ponavljanja: ";
    std::cin >> rep;

    std::cout << "Odaberite alokaciju: 1 - fragmentirana, 0 - kontinualna: ";
    std::cin >> type;

    int **matrix;

    try
    {
        matrix = KreirajPoUvrnutomPravilu(elements, rep, type);

        std::cout << "Dinamicki alocirana matrica:" << std::endl;

        int current_row = 0;
        for (int t = 0; t < rep; t++)
        {
            for (int x : elements)
            {
                std::cout << std::left << std::setw(3) << matrix [current_row] [0];

                for (int i = 1; i < x; i++)
                    std::cout << std::left << std::setw(3) << matrix [current_row] [i];

                std::cout << std::endl;

                current_row++;
            }
        }

        if (type == 1)
        {
            for (int i = 0; i < current_row; i++)
                delete[] matrix [i];
            delete[] matrix;
        }
        else
        {
            delete [] matrix[0];
            delete [] matrix;
        }
    }
    catch (std::domain_error de)
    {
        std::cout << de.what() << std::endl;
    }
    catch (std::range_error re)
    {
        std::cout << re.what() << std::endl;
    }
    catch (std::bad_alloc ba)
    {
        std::cout << ba.what() << std::endl;
    }

    return 0;
}










