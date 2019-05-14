#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::cin;
using std::string;

namespace
{
const string http {"http://"};
const string https {"https://"};

struct Result
{
    string Data{};
    bool ErrorFlag{false};
};
};

Result FindUrl(const string &str)
{
    Result url{"No url"};

    if(str.empty())
      {
        url.ErrorFlag = true;
        return url;
      }
    if(str.find(http) != std::string::npos)
      {
        size_t pos = str.find(http);
        url.Data = str.substr(pos);
        return url;
      }
    else if(str.find(https) != std::string::npos) // легкое дублирование
      {                                           // пока не смог придумать решение лучше
         size_t pos = str.find(https);
         url.Data = str.substr(pos);
         return url;
      }

    url.ErrorFlag = true;
    return url;
}

int main ()
{
    cout<< "Enter file path\n> ";
    string fpath;
    cin>> fpath;
    std::ifstream file(fpath,std::ios::binary);
    cout<< endl;

    if(!file)// if cannot open file
      {
        std::cerr<< "file could not be opened for reading!" << endl;
        exit(1);
      }

    bool NoUrl{false};

    while(!file.eof())
      {
        string FileData;
        getline(file,FileData,' ');
        Result Url{FindUrl(FileData)}; // или стоило FileData и URL вынести за цикл?
        if(!Url.ErrorFlag)
          {
             cout<< Url.Data << "\n";
          }
      }

    if(NoUrl)
      {
        cout<< "No Url found" << endl;
      }
    return 0;
}
