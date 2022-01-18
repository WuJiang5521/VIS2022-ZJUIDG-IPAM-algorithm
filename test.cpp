#include <iostream>
#include "MDL_MODULE/mdl_enter.h"
#include "base/BaseDS.hpp"
#include "base/BaseAttr.hpp"

using namespace std;

int main() {
    string dir = "../data/tt/";
    vector<string> files = {
//            "20180324 德国公开赛 女单第二轮 孙颖莎vs伊藤美诚-data.json",
//            "20180526 中国香港公开赛 女单半决赛 王曼昱vs伊藤美诚-data.json",
//            "20180602 中国公开赛 女单半决赛 王曼昱vs伊藤美诚-data.json",
//            "20180610 日本公开赛 女单决赛 王曼昱vs伊藤美诚-data.json",
//            "20191005 瑞典公开赛 女单四分之一决赛 王曼昱vs伊藤美诚-data.json",
//            "20191006 瑞典公开赛 女单决赛 陈梦vs伊藤美诚-data.json",
//            "20191006 瑞典公开赛 女单半决赛 孙颖莎vs伊藤美诚-data.json",
//            "20191013 德国公开赛 女单决赛 孙颖莎vs伊藤美诚-data.json",
//            "fliter_pingpong.json"
            "20210729 东京奥运会 女单半决赛 孙颖莎vs伊藤美诚-collect_project.json",
            "20191013 德国公开赛 女单决赛 孙颖莎vs伊藤美诚-collect_project.json",
            "20191006 瑞典公开赛 女单半决赛 孙颖莎vs伊藤美诚-collect_project.json",
            "20190424 布达佩斯世乒赛 女单十六分之一决赛 孙颖莎vs伊藤美诚-collect_project.json",
            "20180324 德国公开赛 女单第二轮 孙颖莎vs伊藤美诚-collect_project.json",
    };
    BaseDS::load_file(files, FileType::TableTennis, dir);
    BaseAttr::print_values("values.dat");

//    string dir = "../data/";
//    vector<string> files = {
//            "badminton.json"
//    };
//    BaseDS::load_file(files, FileType::Badminton, dir);
//    BaseAttr::print_values("values.dat");

//    string dir = "../data/";
//    vector<string> files = {
//            "tennis.json"
//    };
//    BaseDS::load_file(files, FileType::Tennis, dir);
//    BaseAttr::print_values("values.dat");
////
    char filename[] = "temp.dat";
    BaseDS::convert_data(filename);

    char interfilename[] = "intertemp.dat";


    char *tennis_argv[] = {
                "",
                "-i",
                filename,
                "-w",
                "true",
                "-o",
                interfilename,
                "-m",
                "10",
    };
    int tennis_argc = sizeof(tennis_argv) / sizeof(char *);
    start_mdl(tennis_argc, tennis_argv);

//    char *quantitative_argv[] = {
//            "",
//            "-i",
//            "./quantitative_base.dat",
//            "-w",
//            "true"
//    };
//    int quantitative_argc = sizeof(quantitative_argv) / sizeof(char *);
//    start_mdl(quantitative_argc, quantitative_argv);

}
