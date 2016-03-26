#include "stdafx.hpp"
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


///**
// * @brief v_Stopw   listTheWords get stopwordlist.txt
// *                  and save in stopw string
// * @param stopw
// */
//void v_Stopw(unordered_map<string, size_t>& stopw)
//{
//    string s;
//    ifstream ifs ("StopWordList.txt");
//    while(!ifs.eof())
//    {
//        ifs >> s;
//        if(s != "\n" && s != " ")
//            stopw.insert({s,0});
//    }
//    ifs.close();
//}


/**
 * @brief r_stopw function to remove stop words from source codes text
 */
unordered_map<string, size_t> r_stopw()
{
    unordered_map<string, size_t> sm;
    string s;
    ifstream ifs ("StopWordList.txt");
    while(!ifs.eof())
    {
        ifs >> s;
        if(s != "\n" && s != " ")
            sm.insert({s,0});
    }
    ifs.close();
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
    string urls[2];

    unordered_map<string, size_t> murl1, murl2, sw;
    urls[0]=get_source_txt("url1");
    urls[1]=get_source_txt("url2");

    regex re[5];
    re[0]="<script(.*?)</script>";   //to remove <script> tags and stuff between them
    re[1]="<style(.*?)</style>";     //to remove <style> tags and stuff between them
    re[2]="</?(.|\n)*?>";            //to remove html tags
    re[3]="[^[:alpha:]]";            //to remove non-alphanumeric characters
    re[4]="\\s+";                    //to remove \s

    for (int i=0; i<2; i++) {
        for (int j=0; j<5; j++) {
            urls[i] = regex_replace(urls[i], re[j], " ");
        }
        if(i==0)
            wToFile("url1s.txt", urls[0]);
        else
            wToFile("url2s.txt", urls[1]);
    }

    s = (char *) malloc(i_max+1);
    FILE *u1 = fopen("url1s.txt", "r");
    stemfile(u1, murl1);
    FILE *u2 = fopen("url2s.txt", "r");
    stemfile(u2, murl2);
    free(s);

    //sw = r_stopw();
//    for(auto& i:sw)
//    {
//        auto ss=murl1.find(i.first);
//        if(murl1.end() != ss)
//            murl1.erase(i.first);
//        ss=murl2.find(i.first);
//        if(murl2.end() != ss)
//            murl2.erase(i.first);
//    }

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


