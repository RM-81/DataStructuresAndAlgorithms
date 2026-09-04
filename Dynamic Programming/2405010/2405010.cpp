#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isUpper(string input)
{
    bool upper=true;
    int length=input.length();
    for(int i=0;i<length;i++)
    {
        if((input[i]<'A')||(input[i]>'Z'))
        {
            upper=false;
            break;
        }
    }
    return upper;
}

void solve(string one, string two, int length1, int length2, int deleteCost, int insertCost, int replaceCost)
{
    vector<vector<int>> dp(length1+1,vector<int>(length2+1));
    for(int i=0;i<=length1;i++)
    {
        dp[i][0]=i*deleteCost;
    }
    for(int j=0;j<=length2;j++)
    {
        dp[0][j]=j*insertCost;
    }
    for(int i=1;i<=length1;i++)
    {
        for(int j=1;j<=length2;j++)
        {
            if(one[i-1]==two[j-1])
            {
                dp[i][j]=dp[i-1][j-1];
            }
            else
            {
                int deletion=dp[i-1][j]+deleteCost;
                int insertion=dp[i][j-1]+insertCost;
                int replace=dp[i-1][j-1]+replaceCost;
                int min=deletion;
                if(min>insertion)
                {
                    min=insertion;
                }
                if(min>replace)
                {
                    min=replace;
                }
                dp[i][j]=min;
            }
        }
    }
    cout<<"Minimum Cost : "<<dp[length1][length2]<<endl;

    cout<<"Operations: "<<endl;
    vector<string>operations;
    int i=length1;
    int j=length2;
    while((i>0)||(j>0))
    {
        if((j>0) &&  (dp[i][j]==dp[i][j-1]+insertCost))
        {
            operations.push_back("Insert "+ string(1,two[j-1]));
            j--;
        }
        else if((i>0) && (dp[i][j]==dp[i-1][j]+deleteCost))
        {
            operations.push_back("Delete "+ string(1,one[i-1]));
            i--;
        }
        else if((i>0) && (j>0) && (one[i-1]==two[j-1]) && (dp[i][j]==dp[i-1][j-1]))
        {
            operations.push_back("Match "+ string(1,one[i-1]));
            i--;
            j--;
        }
        else if((i>0) && (j>0) && (one[i-1]!=two[j-1]) && (dp[i][j]==dp[i-1][j-1]+replaceCost))
        {
            operations.push_back("Replace "+ string(1,one[i-1]) +" with "+ string(1,two[j-1]));
            i--;
            j--;
        } 
    }
    for(int i=operations.size()-1;i>=0;i--)
    {
        cout<<operations[i]<<endl;
    }
}

int main()
{
    int insertCost,deleteCost,replaceCost;
    string first,second;
    cin>>insertCost>>deleteCost>>replaceCost;
    cin>>first;
    cin>>second;
    int firstLength,secondLength;
    firstLength=first.length();
    secondLength=second.length();
    while(1)
    {
        if((firstLength<=0)||(firstLength>=5001)||(secondLength<=0)||(secondLength>=5001))
        {
            cout<<"Invalid Size. It must be from 1 to 5000. Enter sequences again: "<<endl;
            cin>>first;
            cin>>second;
            firstLength=first.length();
            secondLength=second.length();
        }
        else if(isUpper(first)==false && isUpper(second)==false)
        {
            cout<<"Invalid Format. Enter sequences again: "<<endl;
            cin>>first;
            cin>>second;
            firstLength=first.length();
            secondLength=second.length();
        }
        else if(isUpper(first)==false)
        {
            cout<<"Invalid Format. Enter sequence again: "<<endl;
            cin>>first;
            firstLength=first.length();
        }
        else if(isUpper(second)==false)
        {
            cout<<"Invalid Format. Enter sequence again: "<<endl;
            cin>>second;
            secondLength=second.length();
        }
        else
        {
            break;
        }
    }
    solve(first,second,firstLength,secondLength,deleteCost,insertCost,replaceCost);
}