#include <bits/stdc++.h>

using namespace std;

int main(){

    int max=1e9, x;
    cin>>x;
    vector<vector<int>>graf(x,vector<int>(x,max));

    for(int i=0;i<x;i++)
    {
        for(int j=0;j<x;j++)
        {
            cin>>graf[i][j];
        }
    }
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<x;j++)
        {
            for(int k=0;k<x;k++)
            {
                if(graf[j][i]!=max&&graf[i][k]!=max)
                {
                    graf[j][k]=min(graf[j][k],graf[j][i]+graf[i][k]);
                }
            }
        }
    }
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<x;j++)
        {
            cout<<graf[i][j]<<" ";
        }
        cout<<endl;
    }
}