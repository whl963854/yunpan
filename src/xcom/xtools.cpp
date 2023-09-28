#pragma warning (disable:4996)
#ifndef XTOOLS_CPP
#define XTOOLS_CPP

#include "xtools.h" 
#include <io.h>


using namespace std;

//��ȡĿ¼���ļ����ҷ����ļ����ʹ�Сƴ�ӵ��ַ���
std::string getDirData(std::string path)
{
    std::string data = "";
    //�洢�ļ���Ϣ
    _finddata_t file;
    std::string dirpath = path + "/*.*";
    //Ŀ¼������
    intptr_t dir = _findfirst(dirpath.c_str(), &file);
    if (dir < 0)
        return data;
    do
    {
        //�����ļ�������
        if (file.attrib & _A_SUBDIR) continue;
        char buf[1024] = { 0 };
        sprintf(buf, "%s,%u;", file.name, file.size);
        data += buf;
    } while (_findnext(dir, &file) == 0);

    //ȥ����β ;
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

