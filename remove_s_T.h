#include "stdafx.hpp"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <unordered_map>
#include <regex>
using namespace boost::algorithm;
using namespace std;


///
/// \brief listTheWords get stopwordlist.txt
///         and save in stopw string
///
void v_Stopw(vector<string>& stopw)
{
    string s;
    ifstream ifs ("StopWordList.txt");
    while(!ifs.eof())
    {
        ifs >> s;
        stopw.push_back(s);
    }
    ifs.close();
}

/**
 * @brief r_stopw function to remove stop words from source codes text
 */
void r_stopw()
{
    vector<string> stopw;
    v_Stopw(stopw);
    unordered_map<string, void*> sm;
    for(auto& i:stopw)
        sm.insert({i,nullptr});
}

void wToFile(string s, string d)
{
    ofstream w (s.c_str());
    if(w.is_open())
        w << d;
    else
        cout << endl << s << "faild!!!!!!!!!!";
    w.close();
}

string get_source_txt(string url)
{
    cout << endl << "*******************get_source_txt********************" << endl;
    string s,ss;
    ifstream ifs (url + ".txt");
    while(!ifs.eof())
    {
        ifs >> s;
        ss+=s;
    }
    ifs.close();
    return ss;
}

void r_tags()
{
    cout << endl << "*******************r-tags********************" << endl;
    string surl1, result1, surl2;
    surl1=get_source_txt("url1");
    surl2=get_source_txt("url2");

    regex script{"<script*</script>"};
    regex stylesheet{"<style*</style>"};
    regex html_tags{"</?\\w+[^>]*>"};

    surl1 = regex_replace(surl1, script, string(" "));
    //wToFile("url1s.txt", surl1);
    surl1 = regex_replace(surl1, stylesheet, string(" "));
    //wToFile("url1s.txt", surl1);
    surl1 = regex_replace(surl1, html_tags, string(" "));
    wToFile("url1s.txt", surl1);

    surl2 = regex_replace(surl2, script, string(" "));
    surl2 = regex_replace(surl2, stylesheet, string(" "));
    surl2 = regex_replace(surl2, html_tags, string(" "));
    wToFile("url2s.txt", surl2);
}
