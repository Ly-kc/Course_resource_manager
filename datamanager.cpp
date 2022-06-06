#include"datamanager.h"
#include"json/json.h"
#include<fstream>
#include<QDebug>
#include<QDir>
#include<QFile>

using std::string;

const string glob_dir="C:\\Users\\win\\Desktop\\suibian";

const QString time_format="yyyy/MM/dd HH:mm:ss";

bool rmv_file(QString file_path){
    if(!QFileInfo::exists(file_path)) return 0;
    qDebug()<<file_path;
    QFileInfo fi(file_path);
    QString cur_dir=fi.absolutePath();
    QDir().remove(file_path);
    QDir().rmpath(cur_dir);
    return 1;
}

bool copy_file(QString from_path,QString to_dir,QString fname){
    QString to_path=to_dir+fname;
    if(from_path==to_path) return 0;//same path
    if(!QFileInfo::exists(from_path)) return 0;//source not exist
    qDebug()<<from_path;
    QDir().mkpath(to_dir);
    if( QDir().exists(to_path)) QDir().remove(to_path);//same name exists
    QFile::copy(from_path,to_path);
    return 1;
}

bool move_file(QString from_path,QString to_dir,QString fname){
    return copy_file(from_path,to_dir,fname) && rmv_file(from_path);
}

CourseFile::CourseFile(std::string _subject, std::string _type, std::string _name,
                       int _prior,int _freq,QDateTime _time):
                       subject(_subject),type(_type),name(_name),
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

//construct cfm from json file
CourseFileManager::CourseFileManager(){
    std::ifstream ifs("course_info.json");
    Json::Reader ipt;
    Json::Value course_list;
    ipt.parse(ifs,course_list);
    for(auto cur:course_list){
        courses.push_back(CourseFile(
            cur["subject"].asString(),
            cur["type"].asString(),
            cur["name"].asString(),
            cur["prior"].asInt(),
            cur["freq"].asInt(),
            QDateTime::fromString(QString::fromStdString(cur["time"].asString()),time_format)
        ));
    }
}

void CourseFileManager::add_file(QString file_path,CourseFile cf){
    cf.upd_time();
    if(move_file(file_path,cf.get_dir(),cf.get_name()))
        courses.push_back(cf);
}

void CourseFileManager::erase_file(CourseFile cf){
    if(rmv_file(cf.get_path()))
        courses.erase(std::remove(courses.begin(),courses.end(),cf),courses.end());
}

//return a list of coursefiles using filt (returns ture defaultly)
vector<CourseFile> CourseFileManager::filter_file(std::function<bool(CourseFile)> filt){
    vector<CourseFile> ret;
    copy_if(courses.begin(),courses.end(),std::back_inserter(ret),filt);
    return ret;
}

//apply func to all files satisfying filt (returns ture defaultly)
void CourseFileManager::transform_file(std::function<CourseFile(CourseFile)> func,
                                       std::function<bool(CourseFile)> filt){
    for(CourseFile&cf:courses)if(filt(cf)){
        QString pre_path=cf.get_path();
        cf=func(cf);
        cf.upd_time();
//        qDebug()<<pre_path<<' '<<QFileInfo::exists(pre_path);
        qDebug()<<move_file(pre_path,cf.get_dir(),cf.get_name());
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
