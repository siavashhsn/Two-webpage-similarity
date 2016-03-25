#include "stdafx.hpp"
#include <map>
#include <regex>
#include <math.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

#include "porter.hpp"
using namespace std;
using namespace boost;
void sim(unordered_map<string, size_t>, unordered_map<string, size_t>);


///
/// \brief listTheWords get stopwordlist.txt
///         and save in stopw string
///
void v_Stopw(unordered_map<string, size_t>& stopw)
{
    string s;
    ifstream ifs ("StopWordList.txt");
    while(!ifs.eof())
    {
        ifs >> s;
        if(s != "\n" && s != " ")
            stopw.insert({s,0});
    }
    ifs.close();
}

/**
 * @brief r_stopw function to remove stop words from source codes text
 */
unordered_map<string, size_t> r_stopw()
{
    unordered_map<string, size_t> sm;
    v_Stopw(sm);
    return sm;
}


/**
 * @brief wToFile save changes into file
 * @param s name of the saved file
 * @param d data of the saved file
 */
void wToFile(string s, string d)
{
    ofstream w (s.c_str());
    if(w.is_open())
        w << d;
    else
        cout << endl << s << "faild!!!!!!!!!!";
    w.close();
}


/**
 * @brief get_source_txt get the saved source code
 * @param url name of the saved file
 * @return string amount of the saved file
 */
string get_source_txt(string url)
{
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






/**
 * @brief r_tags remove the html tags and scrit and stylesheet
 * @method using regular expression to replace all these unneccessary
 *         thing with space
 */
void r_tags()
{
    string surl1, surl2;
    vector<string> vurl1, vurl2;
    unordered_map<string, size_t> murl1, murl2, miurl, maurl, sw;
    surl1=get_source_txt("url1");
    surl2=get_source_txt("url2");


    regex parenthesis("[^[:alpha:]]"),       //to remove non-alphanumeric characters
          rss("\\s+"),                       //to remove \s
          _script("<script(.*?)</script>"),  //to remove <script> tags and stuff between them
          stylesheet("<style(.*?)</style>"), //to remove <style> tags and stuff between them
          html_tags("</?(.|\n)*?>");         //to remove html tags

    surl1 = regex_replace(surl1, _script, " ");
    surl1 = regex_replace(surl1, stylesheet, " ");
    surl1 = regex_replace(surl1, html_tags, " ");
    surl1 = regex_replace(surl1, parenthesis, " ");
    surl1 = regex_replace(surl1, rss, " ");
    wToFile("url1s.txt", surl1);

    surl2 = regex_replace(surl2, rss, " ");
    surl2 = regex_replace(surl2, _script, " ");
    surl2 = regex_replace(surl2, stylesheet, " ");
    surl2 = regex_replace(surl2, html_tags, " ");
    surl2 = regex_replace(surl2, parenthesis, " ");
    surl2 = regex_replace(surl2, rss, " ");
    wToFile("url2s.txt", surl2);


    s = (char *) malloc(i_max+1);
    FILE *u1 = fopen("url1s.txt", "r");
    murl1 = stemfile(u1);
    FILE *u2 = fopen("url2s.txt", "r");
    murl2 = stemfile(u2);
    free(s);

//    cout<<"\n[MURL1]"<<endl;
//    for(auto x:murl2) {
//        cout<<x.first<< " "<<x.second<<endl;
//    }
//    cout<<"\n\n[MURL2]\n"<<endl;

//    for(auto x:murl2) {
//        cout<<x.first<< " "<<x.second<<endl;
//    }

    sw = r_stopw();
    for(auto& i:sw)
    {
        auto ss=murl1.find(i.first);
        if(murl1.end() != ss)
            murl1.erase(i.first);
        ss=murl2.find(i.first);
        if(murl2.end() != ss)
            murl2.erase(i.first);
    }

    string ss;
    for(auto& i:murl1)
        ss += i.first + " ";
    wToFile("finalText1.txt", ss);

    ss = "";
    for(auto& i:murl2)
        ss += i.first + " ";
    wToFile("finalText2.txt", ss);

    if(murl1.size()>=murl2.size()){
        sim(murl2, murl1);
    }
    else{
        sim(murl1, murl2);
    }
}

void sim(unordered_map<string, size_t> murl1, unordered_map<string, size_t> murl2)
{
    vector<pair<int, int>> v;

    for(auto& i:murl1)
    {
        if(murl2.count(i.first)){
            cout << i.first << " " << i.second<< "----" << i.first << " " << murl2[i.first] << endl;
            v.push_back(make_pair(i.second, murl2[i.first]));
            murl2.erase(i.first);
        }
        else{
            cout << i.first << " " << i.second<< "----" << " NOT found!" << endl;
            v.push_back(make_pair(i.second, 0));
        }
    }

    for(auto& i:murl2){
        cout << " NOT found!" << "----" << i.first << " " << i.second << endl;
        v.push_back(make_pair(0, i.second));
    }


    //to calculate the Similarity i am using
    //the cosine similarity

    double d_d=0, d_1=0, d_2=0;
    for(auto& i:v)
    {
        d_d += i.first  * i.second;
        d_1 += i.first  * i.first;
        d_2 += i.second * i.second;
    }

    d_1=sqrt(d_1);
    d_2=sqrt(d_2);
    d_d /= d_1*d_2;
    cout << endl << "Similarity between to pages is : "  << d_d*100;
}


