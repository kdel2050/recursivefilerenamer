
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <map>
#include <random>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

    vector<string> files;



    std::string Recursive(std::string folder) {

    std::string search_path = folder + "/*.*";

    WIN32_FIND_DATA fd;

    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
    std::string tmp;
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (!(!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, ".."))) {
                    tmp = folder + "\\";
                    tmp = tmp + fd.cFileName;
                    Recursive(tmp);
                }
            }
            else {
                std::string FinalFilePath = folder + "\\" + fd.cFileName;
                files.push_back(FinalFilePath);
            }

        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return folder;
}

bool has_suffix(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}




static const char alphanum[] =
"0123456789-"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char genRandom()  // Random string generator function.
{

    return alphanum[rand() % stringLength];
}


int main(){
    try
    {

        std::string folder = "";
        std::string startExt = ".";
        std::string finalExt = ".";

        cout<<"Please give full path to operate with renaming:"<<endl;
        cin>>folder;
        cout<<"Please give current (start) extension with the dot:"<<endl;
        cin>>startExt;
        cout<<"Please give final extension with the dot:"<<endl;
        cin>>finalExt;

        Recursive(folder);

        std::string t;
        std::string t_new;


        while (!files.empty()) {
            t = files.back();
            if (has_suffix(t, startExt)) {

                //cout << "FINAL PATH : " << t << endl;

                std::string Str;


                for(unsigned int i = 0; i < 21; ++i)
                {
                    Str += genRandom();
                }

                t_new = (Str + finalExt).c_str();

                const char* s = t.c_str();

                const char* s_new = (folder + "\\" + t_new).c_str();

                //cout<<s<<endl;
                //cout<<s_new<<endl;

                rename(s,s_new);

                cout<<"Renaming "<<s<<" completed"<<endl;

                t.clear();
            }
            files.pop_back();
        }

        cout<<"Press any key to exit"<<endl;
        getch();
    }
    catch (...)
    {
        cout<<"Error happened please check....."<<endl;
        exit(-1);
    }

return 0;
}





/*
std::string random_string(std::size_t length)
{
    const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < length; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}
*/




/*
It uses standard c++ functionality. No need to include any third party library in code.

Only send directory path as parameter. It will revert you every files path present in that folder and its sub folder.

Further that, if you need to sort any specific type file (i.e. .txt or .jpg), pass extension, it will print all the files path which having respective extension.
*/
