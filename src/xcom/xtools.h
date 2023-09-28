#ifndef XTOOLS_H
#define XTOOLS_H

#include <string>
#include <vector>
#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif 

XCOM_API std::string getDirData(std::string path);

XCOM_API std::vector<std::string> getDirLists(std::string dirs);

#endif //XTOOLS_H

