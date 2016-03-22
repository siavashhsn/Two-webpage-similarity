#include "stdafx.hpp"
#include <regex>
#include <string>
#include <unordered_map>
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
        ss+=" "+s;
    }
    ifs.close();
    return ss;
}

void r_tags()
{
    cout << endl << "*******************r-tags******************" << endl;
    string surl1, result1, surl2;
    surl1=get_source_txt("url1");
    surl2=get_source_txt("url2");

    regex parenthesis("[^[:alpha:]]")       //to remove non-alphanumeric characters
        , rss("\\s")                        //to remove \s
        , _script("<script(.*?)</script>")  //to remove <script> tags and stuff between them
        , stylesheet{"<style(.*?)</style>"} //to remove <style> tags and stuff between them
        , html_tags{"</?(.|\n)*?>"};        //to remove html tags

    surl1 = regex_replace(surl1, rss, " ");
    surl1 = regex_replace(surl1, _script, " ");
    surl1 = regex_replace(surl1, stylesheet, " ");
    surl1 = regex_replace(surl1, html_tags, " ");
    surl1 = regex_replace(surl1, parenthesis, " ");
    wToFile("url1s.txt", surl1);

    surl2 = regex_replace(surl2, rss, " ");
    surl2 = regex_replace(surl2, _script, " ");
    surl2 = regex_replace(surl2, stylesheet, " ");
    surl2 = regex_replace(surl2, html_tags, " ");
    surl2 = regex_replace(surl2, parenthesis, " ");
    wToFile("url2s.txt", surl2);
}
