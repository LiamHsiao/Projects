#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

class Kmap
{
    public:
        int numvar;
        string dash;
        vector<int> minterms;
        vector<int> dontcares;
        string DecToBin(int x);
        string Pad(string bin);
        vector<string> getvar();
        string getvalue(string x);
        vector<string> reduce(vector<string> minterms);
        string replace_complements(string a, string b);
        vector<int> PrimeToSOP(string a, vector<string> x);
        int BinToDec(string b);
        Kmap(int a)
        {
            numvar = a;
            dash = dash.append(a, '-');
        }
        bool Gcode(string a, string b);
        bool isnPrime(string a, string b);
        bool invector(vector<string> a, string b);
        bool Vequal(vector<string> a, vector<string> b);
        bool nprime(vector<int> x, const vector<int> minterms);
        bool essenisminsop(uint8_t arr[][1024], int a, int b);
        int count(string a);
};
struct QmSolution
{
    int numVar;
    vector<string> primes;
    vector<vector<string>> minimumSops;
};
QmSolution* solveQm(int numVar, const vector<int> minterms, const vector<int> dontcares, bool verbose)
{
    QmSolution* sol = new QmSolution;
    Kmap KMAP(numVar);

    KMAP.minterms = minterms;
    vector<string> strminterms;
    for(int i=0; i<KMAP.minterms.size(); ++i)
    {
        strminterms.push_back(KMAP.Pad(KMAP.DecToBin(KMAP.minterms.at(i))));
    }


    KMAP.dontcares = dontcares;
    vector<string> strdontcares;
    for(int i=0; i<KMAP.dontcares.size(); ++i)
    {
        strdontcares.push_back(KMAP.Pad(KMAP.DecToBin(KMAP.dontcares.at(i))));
    }


    vector<string> mixminterms;
    mixminterms.resize(strminterms.size() + strdontcares.size());
    merge(strminterms.begin(), strminterms.end(), strdontcares.begin(), strdontcares.end(), mixminterms.begin());

    //find prime implicant
    vector<string> record;
    record = mixminterms;
    do
    {
        mixminterms = KMAP.reduce(mixminterms);
    }while(!KMAP.Vequal(mixminterms, KMAP.reduce(mixminterms)));


    //eliminate dontcares in prime implicant
    vector<string> PRIME;
    vector<string> temp;
    for(int i=0; i<mixminterms.size(); ++i)
    {
        switch(KMAP.nprime(KMAP.PrimeToSOP(mixminterms[i], record), minterms))
        {
            case 0:
                temp.push_back(mixminterms[i]);
                break;
            default:
                break;
        }
    }
    mixminterms.resize(temp.size());
    mixminterms = temp;


    //make binary prime implicant into letter prime implicant
    for(int i=0; i<mixminterms.size(); ++i)
    {
        PRIME.push_back(KMAP.getvalue(mixminterms[i]));
    }


    //make graph and set to -1
    const int n = pow(2, KMAP.numvar);
    uint8_t terms[1024][1024];
    for(int i=0; i<mixminterms.size(); ++i)
    {
        for(int j=0; j<n; j++)
        {
            terms[i][j] = -1;
        }
    }


    //draw map
    for(int i=0; i<mixminterms.size(); ++i)
    {
        //eliminate doncares in prime implicant
        vector<int> v = KMAP.PrimeToSOP(mixminterms[i], record);
        for(int m=0; m<v.size(); m++)
        {
            for(int n=0; n<KMAP.dontcares.size(); n++)
            {
                if(v[m] == KMAP.dontcares[n])
                {
                    v[m] = -1;
                }
            }
        }
        for(int j=0; j<v.size(); j++)
        {
            for(int k=0; k<1024; k++)
            {
                if(v[j] == k)
                {
                    terms[i][k] = 1;
                }
            }
        }
        v.clear();
    }

    //count number of implicant
    int count[1024] = {0};
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<mixminterms.size(); j++)
        {
            switch(terms[j][i])
            {
                case 1:
                    count[i]++;
                    break;
                default:
                    break;
            }
        }
    }

    //find essential prime implicant
    vector<string> ESSENTIALS;
    vector<string> essentials;
    for(int i=0; i<n; ++i)
    {
        switch(count[i])
        {
            case 1:
                for(int j=0; j<mixminterms.size(); j++)
                {
                    vector<int> v = KMAP.PrimeToSOP(mixminterms[j], record);
                    for(int m=0; m<v.size(); m++)
                    {
                        switch(v[m] == i)
                        {
                            case 1:
                                if(!KMAP.invector(ESSENTIALS, KMAP.getvalue(mixminterms[j])))
                                {
                                    ESSENTIALS.push_back(KMAP.getvalue(mixminterms[j]));
                                    essentials.push_back(mixminterms[j]);
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    v.clear();
                }
                break;
            default:
                break;
        }
    }
    
    //eliminate essential to use patric method
    for(int j=0; j<essentials.size(); j++)
    {
        vector<int> v = KMAP.PrimeToSOP(essentials[j], record);
        for(int i=0; i<n; ++i)
        {
            for(int k=0; k<v.size(); k++)
            {
                if(i == v[k])
                {
                    for(int m=0; m<1024; m++)
                    {
                        terms[m][i] = -1;
                    }
                }
            }
        }
        v.clear();
    }
    
    //if essential = minisop
    if(KMAP.essenisminsop(terms, mixminterms.size(), n))
    {
        sol->minimumSops.push_back(ESSENTIALS);
        sol->numVar = numVar;
        sol->primes = PRIME;
        return sol;
    }
    else
    {   
        vector<vector<int>> matrix;
        vector<int> row[1024];
        for(int j=0; j<mixminterms.size(); j++)
        {
            for(int k=0; k<1024; k++)
            {
                switch(terms[j][k])
                {   
                    case 1:
                        row[k].push_back(j);
                        break;
                    default:
                        break;
                }
            }
        }

        //reduced row
        for(int n=1024; n>0; n--)
        {
            if(row[n].size()>0)
            {
                matrix.push_back(row[n]);
            }
        }

        //multiply out
        int rownum = matrix.size();
        int columnnum = 1;
        for(int i=0; i<matrix.size(); ++i)
        {
            columnnum *= (matrix[i].size());
        }
        vector<vector<int>> sol_dec;
        int size = 1;
        for(int i=0; i<matrix.size(); ++i)
        {
            size *= matrix[i].size();
        }
        sol_dec.resize(size);
        for(int j=0; j<matrix.size(); j++)
        {
            for(int i=0; i<size; ++i)
            {
                int temp = size;
                for(int k=0; k<=j; k++)
                {
                    temp /= matrix[k].size();
                }
                int b = (i/temp);
                int a = b%matrix.at(j).size();
                sol_dec[i].push_back(matrix[j][a]);
            }
        }
        for(int i=0; i<pow(2, matrix.size()); ++i)
        {
            for(int j=0; j<sol_dec[i].size(); j++)
            {
                for(int k=j+1; k<sol_dec[i].size(); k++)
                {
                    if(sol_dec[i][j] == sol_dec[i][k])
                    {
                        sol_dec[i].erase(sol_dec[i].begin()+k);
                    }
                }
            }
        }
        for(int i=0; i<sol_dec.size(); ++i)
        {
            sort(sol_dec[i].begin(),sol_dec[i].end());
            sol_dec[i].erase(unique(sol_dec[i].begin(), sol_dec[i].end()), sol_dec[i].end());
        }
        
        //choose the best answer
        vector<int> sizeofrow;
        for(int i=0; i<sol_dec.size(); ++i)
        {
            sizeofrow.push_back(sol_dec[i].size());
        }
        auto min = min_element(sizeofrow.begin(), sizeofrow.end());
        int minPosition = min - sizeofrow.begin();
        vector<vector<string>> minimumSops;
        vector<string> SOP;
        for(int i=0; i<sol_dec[minPosition].size(); ++i)
        {
            SOP.push_back(KMAP.getvalue(mixminterms[sol_dec[minPosition][i]]));
  
        }
        SOP.insert(SOP.end(), ESSENTIALS.begin(), ESSENTIALS.end());
        minimumSops.push_back(SOP);
        SOP.clear();
        bool judge = 1;
        for(int j=minPosition+1; j<sizeofrow.size(); j++)
        {
            judge = 1;
            if(sizeofrow[j] == sizeofrow[minPosition])
            {
                for(int k=0; k<sol_dec[minPosition].size(); k++)
                {
                    for(int m=minPosition+1; m<j ; m++)
                    {
                        if(sol_dec[j] == sol_dec[m])
                        {
                            judge = 0;
                        }
                    }
                    if(sol_dec[j]!=sol_dec[minPosition] && j>minPosition && judge==1)
                    {
                        
                        SOP.push_back(KMAP.getvalue(mixminterms[sol_dec[j][k]]));
      
                    }
                }
                if(SOP.size()>0)
                {
                    SOP.insert(SOP.end(), ESSENTIALS.begin(), ESSENTIALS.end());
                    minimumSops.push_back(SOP);
                }
                SOP.clear();
            }
        }
        vector<string> MINSOP;
        for (int i = 0; i<sol_dec[minPosition].size(); ++i)
        {
            MINSOP.push_back(KMAP.getvalue(mixminterms[sol_dec[minPosition][i]]));
        }
        vector<string> MINSOP1;
        MINSOP1.insert(MINSOP1.end(), ESSENTIALS.begin(), ESSENTIALS.end());
        MINSOP1.insert(MINSOP1.end(), MINSOP.begin(), MINSOP.end());
        sol->minimumSops = minimumSops;
        sol->numVar = numVar;
        sol->primes = PRIME;
        return sol;
    }
}


string Kmap::DecToBin(int x)
{
    if(x == 0)
    {
        return x + "";
    }
    else if((x%2)+1 == 1)
    {
        return DecToBin(x/2) + "0";
    }
    else
    {
        return DecToBin(x/2) + "1";
    }
}
string Kmap::Pad(string x)
{
    int i = 0;
    int max = numvar - x.length();
    while(i < max)
    {
        x = "0" + x;
        ++i;    
    }
    return x;
}
vector<string> Kmap::getvar()
{
    vector<string> x;
    vector<string> letters;
    letters = {"a","b","c","d","e","f","g","h","i","j"};
    
    for(int i=0; i<this->numvar; ++i)
    {
        x.push_back(letters.at(i));
    }
    return x;
}
bool Kmap::Gcode(string a, string b)
{
    int k = 0;
    for(int i=0; i<a.length(); ++i)
    {
        if(a[i] != b[i])
        {
            k++;
        }
    }
    return(k == 1);
}
string Kmap::replace_complements(string a, string b)
{
    string x = "";
    for(int i=0; i<a.length(); ++i)
    {
        if(a[i] == b[i])
        {
            x = x + a[i];
        }
        else
        {
            x = x + "-";
        }
    }
    return x;
}
bool Kmap::invector(vector<string> a, string b)
{
    for(int i=0; i<a.size(); ++i)
    {
        switch(a.at(i).compare(b))
        {
            case 0:
                return 1;
                break;
            default:
                break;
        }
    }
    return 0;
}    
vector<string> Kmap::reduce(vector<string> min)
{
    vector<string> newmin;
    vector<int> check(min.size());

    for(int i=0; i<min.size(); ++i)
    {
        for(int j=i; j<min.size(); j++)
        {
            switch(Gcode(min.at(i), min.at(j)))
            {
                case 1:
                    check.at(i) = 1;
                    check.at(j) = 1;
                    if(!invector(newmin, replace_complements(min.at(i), min.at(j))))
                    {
                        newmin.push_back(replace_complements(min.at(i), min.at(j)));
                    }
                    break;
                default:
                    break;
            }
        }
    }
    for(int i=0; i<min.size(); ++i)
    {
        if(check.at(i)!=1 && !invector(newmin, min.at(i)))
        {
            newmin.push_back(min.at(i));
        }
    }
    return newmin;
}
string Kmap::getvalue(string a)
{
    string x = "";
    vector<string> var = this->getvar();

    if(a == dash)
    {
        return "1";
    }

    int i = 0;
    while(i<a.length())
    {
        if(a[i] != '-')
        {
            if(a[i] != '0')
            {
                x = x + var.at(i);
            }
            else
            {
                x = x + var.at(i) + "\'";
            }
        }
        ++i;
    }
    return x;
}
bool Kmap::Vequal(vector<string> a, vector<string> b)
{
    if(a.size() != b.size())
    {
        return 0;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for(int i=0; i<a.size(); ++i)
    {
        if(a.at(i) != b.at(i))
        {
            return 0;
        }
    }
    return 1;
}
bool Kmap::nprime(vector<int> x, const vector<int> minterms)
{
    for(int i=0; i<x.size(); ++i)
    {
        for(int j=0; j<minterms.size(); j++)
        {
            if(x.at(i) == minterms.at(j))
            {
                return 0;
            }
        }
    }
    return 1;
}
int Kmap::BinToDec(string b)
{
    int x = stoi(b, nullptr, 2);
    return x;
}
bool Kmap::essenisminsop(uint8_t arr[][1024], int a, int b)
{
    for(int i=0; i<a; ++i)
    {
        for(int j=0; j<b; j++)
        {
            switch(arr[i][j])
            {
                case 1:
                    return 0;
                    break;
                default:
                    break;
            }
        }
    }
    return 1;
}
bool Kmap::isnPrime(string a, string b)
{
    for(int i=0; i<a.size(); ++i)
    {
        if(!(b[i] == '-' || b[i] == a[i]))
            return 0;
    }
    return 1;
}
vector<int> Kmap::PrimeToSOP(string a, vector<string> x)
{
    vector<int> v;
    for(int i=0; i<x.size(); ++i)
    {
        switch(isnPrime(x.at(i), a))
        {
            case 1:
                v.push_back(BinToDec(x.at(i)));
                break;
            default:
                break;
        }
    }
    return v;
}
int Kmap::count(string a)
{
    int countnum = 0;
    for(int i=0; i<a.length(); ++i)
    {
        if(a[i] == '1')
        {
            ++countnum;
        }
    }
    return countnum;
}

