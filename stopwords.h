#include "stdafx.hpp"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
using namespace boost::algorithm;
using namespace std;


///
/// \brief listTheWords get stopwordlist.txt
///         and save in stopw string
///
string listTheWords()
{
    string stopw, s;
    ifstream ifs ("StopWordList.txt");
    while(!ifs.eof())
    {
        ifs >> s;
        stopw += " " + s;
    }
    ifs.close();
    return stopw;
}

void stv()
{
    vector<string> swv;
    auto s = listTheWords();
    split(swv, s, is_any_of("\n"));
}
