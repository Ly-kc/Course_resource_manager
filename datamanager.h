﻿#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include<string>
#include<QString>
#include<algorithm>
#include<vector>
#include<QDebug>
#include<QDateTime>
#include <functional>

using std::string;
using std::vector;

class CourseFileManager;

class CourseFile{
    string subject,type,name;
    int prior,freq;
    QDateTime time;
    friend class CourseFileManager;

public:
    CourseFile(string _subject="",string _type="",string _name="",
               int _prior=0,int _freq=0,QDateTime _time=QDateTime::currentDateTime());
    QString get_subject()const;
    QString get_type()const;
    QString get_name()const;
    int get_prior()const;
    int get_freq()const;
    QDateTime get_time()const;
    QString get_path()const;
    QString get_dir()const;
    void upd_time();
    void set_subject(QString new_subject);
    void set_type(QString new_type);
    void set_name(QString new_name);
    void set_prior(int new_prior);
    void set_freq(int new_freq);
    friend bool operator == (const CourseFile&cf0,const CourseFile&cf1);
    friend QDebug operator << (QDebug qd,CourseFile cf);
};//path format : root/$subject/$type/$name

class CourseFileManager{
    vector<CourseFile> courses;
public:
    CourseFileManager();// read json file
    void add_file(QString file_path,CourseFile cf);
    void erase_file(CourseFile cf);
    vector<CourseFile> filter_file(std::function<bool(CourseFile)> filt=[](CourseFile){return true;});
    void transform_file(std::function<CourseFile(CourseFile)> func,
                        std::function<bool(CourseFile)> filt=[](CourseFile){return true;});
    ~CourseFileManager();// write json file
};

extern CourseFileManager cfm;

#endif