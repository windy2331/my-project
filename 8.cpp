
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
using namespace std;
#define N 9
int jc[N+1]={1,1,2,6,24,120,720,5040,40320,362880};
typedef struct data
{
    int area[N];
    int hash;
    int step;
	int pos;
}Node;
 
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
 

int kangtuo(int area[N])
{
    int i,j;
    int sum=0;
    for( i=0;i<N;i++)
    {
        int nmin=0;
        for(j=i+1;j<N;j++)
        {
            if(area[i]>area[j])
			{
                nmin++;
			}
        }
        sum+=(nmin*jc[N-i-1]);
 
    }
 
    return sum;
}
 

void swap(int *area,int i,int j)
{
    int t=area[i];
    area[i]=area[j];
    area[j]=t;
}
 

void printA(int * area)
{
    int i,j;
    for (i=0;i<N;i++)
    {
        if(i%3==0)
        cout<<"\n";
        cout<<area[i]<<" ";
    }
    cout<<endl;
}

void copyA(int src[N],int target[N])
{
    int i;
    for(i=0;i<N;i++)
    {
        target[i]=src[i];
    }
 
}

int bfs(int area[N],int sHash,int eHash)
{
    if(sHash==eHash)
        return 0;
    int i,j;
    queue<Node> q;
    set<int> setHash;
    Node now,next;
    copyA(area,now.area);
    int pos=0;
    for (i=0;i<N;i++)
    {
        if(area[i]==0)
		{
            break;
		}
        pos++;
    }
    now.hash=sHash;
    now.step=0;
    next.step=0;
    now.pos=pos;
    q.push(now);
    setHash.insert(now.hash);
 
    while(!q.empty())
    {
        now=q.front();
        q.pop();
        for (i=0;i<4;i++)
        {
            int offsetX=0,offsetY=0;
            offsetX=(now.pos%3+dir[i][0]);
            offsetY=(now.pos/3+dir[i][1]);
            if(offsetX>=0&&offsetX<3&&offsetY<3&&offsetY>=0)
            {
                copyA(now.area,next.area);
                next.step=now.step;
                next.step++;
                swap(next.area,now.pos,offsetY*3+offsetX);
                next.hash=kangtuo(next.area);
                next.pos=(offsetY*3+offsetX);
                int begin=setHash.size();
                setHash.insert(next.hash);
                int end=setHash.size();
                if(next.hash==eHash)
				{
                    return next.step;
                }
                if(end>begin)
                {
                    q.push(next);
                }
            }
        }
    }
    return -1;
}
int inversion(int area[N])
{
    int sum=0;
    for(int i=0;i<N;++i)
    {
        for(int j=i+1;j<N;++j)
        {
            if(area[j]<area[i]&&area[j]!=0)
            {
                sum++;
            }
        }
    }
 
    return sum;
 
}
int main(int argc, char **argv)
{
    int i,j;
    string s="123456780";
    string t="120345678";
    int is[N],it[N];
    for (i=0;i<9;i++)
    {
        if (s.at(i)>='0'&&s.at(i)<='8')
        {
            is[i]=s.at(i)-'0';
        }else
        {
            is[i]=0;
        }
        if (t.at(i)>='0'&&t.at(i)<='8')
        {
            it[i]=t.at(i)-'0';
        }else
        {
            it[i]=0;
        }
    }
    int sHash,eHash;
    sHash=kangtuo(is);
    eHash=kangtuo(it);
    int inver1=inversion(is);
    int inver2=inversion(it);
    if((inver1+inver2)%2==0)
    {
        int step=bfs(is,sHash,eHash);
        cout<<step<<endl;
    }
    else
    {
        cout<<"无法到达目标状态"<<endl;
    }
    return 0;
}
