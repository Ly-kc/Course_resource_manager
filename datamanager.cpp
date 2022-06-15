#include"datamanager.h"
#include"addfiledialog.h"
#include"json/json.h"
#include<fstream>
#include<QDebug>
#include<QDir>
#include<QFile>
#include<QFileSystemWatcher>
#include<QUrl>
#include<QDesktopServices>
#ifndef qout
#define qout qDebug()
#endif
using std::string;
const string glob_dir="D:\\University\\term0";
const string trans_dir="D:\\University\\trans";
const QString time_format="yyyy/MM/dd HH:mm:ss";
bool rmv_file(QString file_path,bool rmv_dir){
    if(!QFileInfo::exists(file_path)) return 0;
    //qDebug()<<file_path;
    QFileInfo fi(file_path);
    QString cur_dir=fi.absolutePath();
    if(!QDir().remove(file_path)) return 0;
    if(rmv_dir) QDir().rmpath(cur_dir);
    return 1;
}
int copy_file(QString from_path,QString to_dir,QString fname){
    QString to_path=to_dir+fname;
    if(from_path==to_path) return 2;//same path
    if(!QFileInfo::exists(from_path)) return 0;//source not exist
    //qDebug()<<from_path;
    QDir().mkpath(to_dir);
    if( QDir().exists(to_path)) QDir().remove(to_path);//same name exists
    return QFile::copy(from_path,to_path);
}
bool move_file(QString from_path,QString to_dir,QString fname,bool rmv_dir){
    int cp=copy_file(from_path,to_dir,fname);
    if(cp==2) return 1;
    return cp && rmv_file(from_path,rmv_dir);
}
CourseFile::CourseFile(std::string _subject, std::string _type, std::string _name,
                       int _prior,int _freq,QDateTime _time):
                       subject(_subject),type(_type),name(_name),
                       prior(_prior),freq(_freq),time(_time){}
CourseFile::CourseFile(QString _subject, QString _type, QString _name,
                       int _prior,int _freq,QDateTime _time):
                       subject(_subject.toStdString()),type(_type.toStdString()),name(_name.toStdString()),
                       prior(_prior),freq(_freq),time(_time){}
QString   CourseFile::get_subject()const{return QString::fromStdString(subject);}
QString   CourseFile::get_type()const   {return QString::fromStdString(type);}
QString   CourseFile::get_name()const   {return QString::fromStdString(name);}
int       CourseFile::get_prior()const  {return prior;}
int       CourseFile::get_freq()const   {return freq;}
QDateTime CourseFile::get_time()const   {return time;}
QString   CourseFile::get_dir()const    {return QString::fromStdString(glob_dir+"\\"+subject+"\\"+type+"\\");}
QString   CourseFile::get_path()const   {return QString::fromStdString(glob_dir+"\\"+subject+"\\"+type+"\\"+name);}
void CourseFile::upd_time(){time=QDateTime::currentDateTime();}
void CourseFile::set_subject(QString new_subject){subject=new_subject.toStdString();}
void CourseFile::set_type(QString new_type)      {type=new_type.toStdString();}
void CourseFile::set_name(QString new_name)      {name=new_name.toStdString();}
void CourseFile::set_prior(int new_prior)        {prior=new_prior;}
void CourseFile::set_freq(int new_freq)          {freq=new_freq;}

bool operator == (const CourseFile&cf0,const CourseFile&cf1){
    return cf0.get_path()==cf1.get_path();
}
QDebug operator << (QDebug qd,CourseFile cf){
    qd<<QString::fromStdString(cf.subject)<<' ';
    qd<<QString::fromStdString(cf.type)<<' ';
    qd<<QString::fromStdString(cf.name)<<' ';
    qd<<cf.prior<<' '<<cf.freq<<' ';
    qd<<cf.time.toString(time_format);
    return qd;
}

CourseFile retrieve(QString path){
    auto fi=QFileInfo(path);
    auto name=fi.fileName();
    auto dir=fi.absoluteDir();
    auto type=dir.dirName();
    dir.cdUp();
    auto subject=dir.dirName();
    return CourseFile(subject,type,name);
}

//construct cfm from json file
CourseFileManager::CourseFileManager(){
    std::ifstream ifs("course_info.json");
    Json::Reader ipt;
    Json::Value course_list;
    ipt.parse(ifs,course_list);
    for(auto cur:course_list){
        auto cf=CourseFile(
            cur["subject"].asString(),
            cur["type"].asString(),
            cur["name"].asString(),
            cur["prior"].asInt(),
            cur["freq"].asInt(),
            QDateTime::fromString(QString::fromStdString(cur["time"].asString()),time_format)
        );
        courses.push_back(cf);
    }
    check_files();
}

bool CourseFileManager::exists(CourseFile cf){
    return std::find(courses.begin(),courses.end(),cf)!=courses.end();
}

bool CourseFileManager::open_file(CourseFile cf){
    if(!exists((cf))) return 0;
    transform_file([&](CourseFile x){
        QDesktopServices::openUrl(QUrl("file:///"+cf.get_path(), QUrl::TolerantMode));
        x.set_freq(x.get_freq()+1);
        return x;
    },[&](CourseFile x){
        return x==cf;
    });
    return 1;
}

bool CourseFileManager::add_file(QString file_path,CourseFile cf){
    cf.upd_time();
    if(file_path!=cf.get_path() &&
       !move_file(file_path,cf.get_dir(),cf.get_name(),0)) return 0;//change here to alter transfer behavior
    courses.push_back(cf);
    return 1;
}

bool CourseFileManager::erase_file(CourseFile cf){
    if(!rmv_file(cf.get_path(),1)) return 0;
    courses.erase(std::remove(courses.begin(),courses.end(),cf),courses.end());
    return 1;
}

bool CourseFileManager::new_folder(QString dir_path){
    return QDir().mkpath(dir_path);
}

bool CourseFileManager::new_file(CourseFile cf){
    if(!exists(cf)){
        courses.push_back(cf);
        QDir().mkpath(cf.get_dir());
        return QFile(cf.get_path()).open(QIODevice::WriteOnly);
    }
    return 0;
}

//return a list of coursefiles using filt (returns ture defaultly)
vector<CourseFile> CourseFileManager::filter_file(std::function<bool(CourseFile)> filt){
    vector<CourseFile> ret;
    copy_if(courses.begin(),courses.end(),std::back_inserter(ret),filt);
    return ret;
}
//apply func to all files satisfying filt (returns ture defaultly)
bool CourseFileManager::transform_file(std::function<CourseFile(CourseFile)> func,
                                       std::function<bool(CourseFile)> filt){
    for(CourseFile&cf:courses)if(filt(cf)){
        cf.upd_time();
        auto new_cf=func(cf);
        if(!move_file(cf.get_path(),new_cf.get_dir(),new_cf.get_name(),1)) return 0;
        cf=new_cf;
    }
    return 1;
}

void CourseFileManager::check_files(){
    auto tmp=courses;
    for(auto cf:tmp){
        if(!QFileInfo::exists(cf.get_path()))
            courses.erase(std::remove(courses.begin(),courses.end(),cf),courses.end());
    }
}

CourseFileManager::~CourseFileManager(){
    qDebug()<<"destruction";
    std::ofstream opt("course_info.json");
    Json::Value course_list(Json::arrayValue);
    for(auto cf:courses){
        Json::Value cur;
        cur["subject"]=cf.subject;
        cur["type"]=cf.type;
        cur["name"]=cf.name;
        cur["prior"]=cf.prior;
        cur["freq"]=cf.freq;
        cur["time"]=cf.time.toString(time_format).toStdString();
        course_list.append(cur);
    }
    opt<<course_list;
}

CourseFileManager cfm;

MyWatcher::MyWatcher(QString _main_path,QString _trans_path){
    main_path=_main_path;
    trans_path=_trans_path;
//    watcher=new QFileSystemWatcher;
//    watcher->addPath(watch_path);
//    connect(watcher,&QFileSystemWatcher::directoryChanged,this,&MyWatcher::transfer_files);
}
void MyWatcher::transfer_files(){
    auto file_list=QDir(trans_path).entryInfoList(QDir::Files);
    for(auto fi:file_list){
        auto cf=get_course_file(fi.fileName());
        cfm.add_file(fi.absoluteFilePath(),cf);
    }
    auto dir_list=QDir(main_path).entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    for(auto di:dir_list){
        auto subdir_list=QDir(di.absoluteFilePath()).entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
        for(auto sdi:subdir_list){
            file_list=QDir(sdi.absoluteFilePath()).entryInfoList(QDir::Files);
            for(auto fi:file_list){
                CourseFile cf=retrieve(fi.absoluteFilePath());
                if(!cfm.exists(cf)) cfm.add_file(cf.get_path(),cf);
            }
        }
    }
    cfm.check_files();
}

MyWatcher mw(QString::fromStdString(glob_dir),QString::fromStdString(trans_dir));
