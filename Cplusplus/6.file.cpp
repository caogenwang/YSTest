#include <iostream>
#include <fstream>
using namespace std;

// int main()
// {
//     // ofstream outfile("test.txt");
//     // outfile<<"hello word!"<<endl;
//     // outfile.close();
    
//     string s;
//     // ifstream infile("test.txt");
//     ifstream infile;
//     infile.open("test.txt");
//     if (infile)
//     {
//         while(infile>>s){
//         cout<<s<<endl;
//         }
//     }
//     else
//     {
//         cout<<"Failed open!"<<endl;
//     }
    
//     infile.close();
//     return 0;
// }
std::istream& get(std::istream& in)
{
    int val;
    while (in>>val,!in.eof())
    {
        if(in.bad())
            throw std::runtime_error("IO stream corrupted");
        if (in.fail())
        {
            std::cerr << "bad data,try again"<<endl;
            in.clear();
            in.ignore(200,'\n');
            continue;
        }
        std::cout<<"input data:"<<val<<endl;
    }
    in.clear();
    return in;
}

int main()
{
    string s;
    string filename;
    cin>>filename;

    ifstream infile(filename.c_str());
    while (getline(infile,s))
    {
        cout<<s<<endl;
    }
    infile.close();
    if(!infile)
    {
        return -1;
    }

    // double dval;
    // get(cin);
    // cin>>dval;
    // cout<<dval<<endl;
    return 0;
}