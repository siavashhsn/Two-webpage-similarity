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


void get_source_txt(string url, vector<string>& surl){
    string s;
    ifstream ifs (url + ".txt");
    while(!ifs.eof())
    {
        ifs >> s;
        surl.push_back(s);
    }
    ifs.close();
}

void r_tags(string url1,string url2)
{
    vector<string> surl1, surl2;
    get_source_txt(url1, surl1);
    get_source_txt(url2, surl2);

    regex script{"<script*</script>"};
    regex stylesheet{"<stylesheet*</stylesheet>"};
    regex html_tags{"</?[[:w:]]+[^>]*>"};


}
