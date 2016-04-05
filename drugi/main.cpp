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

namespace TP
{
    template <class T>
    using Array = std::pair <std::pair <T, T>, std::pair <int, int> >;

    template <class T>
    T getFirst(Array<T> &a)
    {
        return a.first.first;
    }

    template <class T>
    T& getLast(Array<T> &a)
    {
        return a.first.second;
    }

    template <class T>
    int &getSize(Array<T> &a)
    {
        return a.second.first;
    }

    template <class T>
    int &getCapacity(Array<T> &a)
    {
        return a.second.second;
    }

    template <class T>
    auto back(Array<T> &array) -> typename std::remove_reference<decltype (*TP::getFirst(array))>::type
    {
        auto it = getLast(array);
        it--;
        return *it;
    }

    template <class T>
    Array<T> createArray(int n)
    {
        T first, last;
        try
        {
            auto elements = new typename std::remove_reference<decltype (*first)>::type [n];
            first = elements;
            last = first;
            return { { first, last }, { 0, n } };
        }
        catch(std::bad_alloc &e)
        {
            throw;
        }
    }

    template <class T>
    Array<T> createArray(T first, T last)
    {
        int size = 0;
        T it = first;
        while (it != last)
        {
            size++;
            it++;
        }
        return { { first, last }, { size, size } };
    }

    template <class T>
    bool empty(Array <T> array)
    {
        return getSize(array) == 0;
    }

    template <class T>
    bool contains(Array<T> array, const typename std::remove_reference<decltype(getFirst(array) [0])>::type &element)
    {
        auto it = getFirst(array);

        while (it != getLast(array))
        {
            if (*it == element)
                return true;
            it++;
        }

        return false;
    }

    template <class T>
    bool push_back(Array<T> &array, const typename std::remove_reference<decltype(getFirst(array) [0])>::type &element)
    {
        *getLast(array) = element;
        getLast(array)++;
        getSize(array)++;
        return true;
    }

    template <class T>
    void print(Array<T> &array)
    {
        if (empty(array))
            return;
        auto first = getFirst<T>(array);
        std::cout << *(first++);
        while (first != getLast(array))
        {
            std::cout << ", " << *first;
            first++;
        }
    }

    template <class T>
    void pop_back(Array<T> &array)
    {
        if (empty<T>(array))
            return;
        getSize(array)--;
        getLast(array)--;
    }

    template <class T>
    bool kick(Array<T> &array, T where)
    {
        auto prev = where;
        while (where != getLast(array))
        {
            std::swap (*where, *prev);
            prev = where;
            where++;
        }
        return true;
    }

    template <class T>
    void kill(Array<T> &array)
    {
        delete[] getFirst(array);
    }
}

template <class Numeric>
int divNum(Numeric number)
{
	if (number < 0)
		number *= -1;
    int count = 0;
    for (int i = 1; i <= number; i++)
        count += ((number % i) == 0);
    return count;
}

template <class Numeric>
int divSum(Numeric number)
{
    int ret = 0;
    for (int i = 1; i <= number; i++)
        if (number % i == 0)
            ret += i;
    return ret;
}

template <class Numeric>
bool perfect(Numeric number)
{
    return (2 * number == divSum(number));
}

template <typename T>
void modify (TP::Array<T> &array)
{
    if (TP::empty(array))
        return;

    bool changed = true;
    int pivot;
    auto it = TP::getFirst(array);
    while (changed)
    {
        changed = false;

        it = TP::getFirst(array);
        pivot = divNum(*it);
        for (; it != TP::getLast(array); it++)
        {
            auto itt = it;
            itt++;

            pivot = divNum (*it);

            changed = false;
            for (; itt != TP::getLast(array); itt++)
            {
                if (divNum (*itt) == divNum (*it))
                {
                    changed = true;
                    break;
                }
            }

            if (changed)
                break;
        }

        if (changed)
        {
            it = TP::getFirst(array);

            bool changed1 = true;
            while (changed1)
            {
                changed1 = false;

                for (; it != TP::getLast(array); it++)
                    if (divNum(*it) == pivot)
                    {
                        TP::kick(array, it);
                        TP::pop_back(array);
                        changed1 = true;
                        break;
                    }
            }

            while (!TP::empty(array) && divNum (TP::back(array)) == pivot)
                TP::pop_back(array);
        }
    }

    std::sort(TP::getFirst(array), TP::getLast(array), [] (typename std::remove_reference <decltype (*it)>::type x, typename std::remove_reference <decltype (*it)>::type y) -> bool
                                                        {
                                                            if (divSum(x) != divSum(y))
                                                                return divSum(x) < divSum(y);
                                                            else
                                                                return x > y;
                                                        });
}

template <typename T>
auto Izdvajanje(T first, T &last, int &n) -> typename std::remove_reference<decltype(first [0])>::type*
{
    T it = first;

    try
    {
        auto mod = TP::createArray(first, last);
        auto arr = TP::createArray<typename std::remove_reference<decltype(first [0])>::type*>((int)TP::getSize(mod));

        for (; it != last; it++)
            if (perfect(*it) && !TP::contains(arr, *it))
                TP::push_back(arr, *it);

        modify(mod);

        first = TP::getFirst(mod);
        last = TP::getLast(mod);

        n = TP::getSize(arr);

        last = TP::getLast(mod);

        return TP::getFirst(arr);
    }
    catch (...)
    {
        throw std::domain_error ("Nedovoljno memorije!");
        return nullptr;
    }
}


int main()
{
    int elements [10000];
    int n = 0;

    std::cout << "Unesite brojeve: ";

    std::cin >> elements [n++];
    while (elements [n - 1] != -1)
        std::cin >> elements [n++];
    n--;

    try
    {
        auto b = elements;
        auto e = elements + n;
        auto asd = Izdvajanje(b, e, n);

        if (asd != nullptr)
        {
            std::cout << "Modificirani kontejner: ";
            auto ptr = asd;
            std::cout << *(b++);
            while (b != e)
            {
                std::cout << ", " << *b;
                b++;
            }

            std::cout << std::endl;

        }
        if (n != 0)
        {
            std::cout << "Savrseni brojevi: ";
            auto ptr = asd;
            std::cout << *(ptr++);
            for (int i = 1; i < n; i++, ptr++)
                std::cout << ", " << *ptr;
        }

        delete[] asd;
    }
    catch (std::domain_error e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
/*
5
1 1 1 -1

T
T
F
T
*/








