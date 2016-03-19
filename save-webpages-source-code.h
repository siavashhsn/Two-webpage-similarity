#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

string data;

size_t writeCallback(char* buf, size_t size, size_t nmemb){
    for(size_t c= 0; c<size*nmemb;c++)
    {
        data.push_back(buf[c]);
    }
    return size*nmemb;
}

void sws(const string *s)
{
    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, s);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);


    string ss = *s + ".txt";
    curl_easy_perform(curl);
    ofstream wtf (/*ss.c_str()*/"/home/siavash/Desktop/url1_contant.txt");
    wtf << data;
    wtf.close();
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}
