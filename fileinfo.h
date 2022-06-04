#ifndef FILEINFO_H
#define FILEINFO_H

#include<QString>

class FileInfo
{
public:
    FileInfo();
    QString file_name;
    QString subject;
    QString type;
    int frequency;
    int priority;
    QString path;
};

#endif // FILEINFO_H
