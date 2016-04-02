#include "stdafx.hpp"
#include "removestuff.h"
#include "save-webpages-source-code.h"
using namespace std;

int main()
{
    string    url1  //= "https://en.wikipedia.org/wiki/Boost_(C%2B%2B_libraries)"
            , url2; //= "https://en.wikipedia.org/wiki/Regular_expression";

    cout << "Please insert two urls!" << endl;
    cout << "url 1: "; cin >> url1;
    cout << "url 2: "; cin >> url2;
    sws(url1, "url1.txt");
    sws(url2, "url2.txt");
    r_tags();

    return 0;
}
