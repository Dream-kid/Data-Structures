#include<bits/stdc++.h>
using namespace std;

int ans[100],arr[100];
int cnt,val,total;

void heap12(int pos)
{
    if(pos>=cnt)
        return;
    int left = 2*pos + 1 ;
    int right = 2*pos + 2;
    int mini = pos;
    if(left<cnt&&arr[left]>arr[pos])
        mini = left;
    if(right<cnt&&arr[right]>arr[mini])
        mini = right;
    if(mini!=pos)
    {
        swap(arr[pos],arr[mini]);
        heap12(mini);
    }

}



void heap_sort()
{

    for(int i = cnt/2-1; i>=0; i--)
        heap12(i);
    for(int i=cnt-1; i>=0; i--)
    {
        swap(arr[0],arr[i]);
        cnt--;
        heap12(0);
    }
}



int main()
{
    srand(time(0));
    cnt = 7, total = 7;
    for(int i=0; i<7; i++)
    {
        arr[i] =  rand()%1000;
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    heap_sort();
    for(int i=total-1; i>=0; i--)
        cout<<arr[i]<<" ";
    cout<<endl;

}
