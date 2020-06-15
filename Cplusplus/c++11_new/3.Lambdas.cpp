#include <iostream>
#include <vector>
using namespace std;


int main()
{
    vector<int> vi {5,28,50,83,70,590,245,59,24};
    int x = 30;
    int y = 100;
    vi.erase(
    remove_if(vi.begin(),vi.end(),[x,y](int n){return x <n && n<y;}),
    vi.end()
    );
    for(auto i : vi)
        cout<<i<<endl;
    return 0;
}