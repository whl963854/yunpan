#pragma warning (disable:4996)
#ifndef XTOOLS_CPP
#define XTOOLS_CPP

#include "xtools.h" 
#include <io.h>


using namespace std;

//获取目录下文件并且返回文件名和大小拼接的字符串
std::string getDirData(std::string path)
{
    std::string data = "";
    //存储文件信息
    _finddata_t file;
    std::string dirpath = path + "/*.*";
    //目录上下文
    intptr_t dir = _findfirst(dirpath.c_str(), &file);
    if (dir < 0)
        return data;
    do
    {
        //读到文件夹跳过
        if (file.attrib & _A_SUBDIR) continue;
        char buf[1024] = { 0 };
        sprintf(buf, "%s,%u;", file.name, file.size);
        data += buf;
    } while (_findnext(dir, &file) == 0);

    //去掉结尾 ;
    if (!data.empty())
    {
        data = data.substr(0, data.size() - 1);
    }
    return data;
}

std::vector<std::string > getDirLists(std::string dirs)
{
    std::string temp = "";
    std::vector<std::string>ans;
    for (auto c : dirs)
    {
        temp += c;
        if (c == ';')
        {
            ans.emplace_back(temp);
            temp = "";
        }
    }
    return ans;
}

#endif //XTOOLS_CPP

