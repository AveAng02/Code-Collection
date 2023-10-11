
#include<bits/stdc++.h>
#include <stack>

#define error(x) cerr<<#x<<" = "<<x<<'\n'

using namespace std;

set<char> stateSet;
map<char,vector<vector<char>>> Map;

bool depthFirstSearch(char c, char org, char last, map<char,vector<vector<char>>> &Map)
{
    bool rtake = false;
    for(auto i : Map[c])
    {
        bool take = true;
        for(auto j : i)
        {
            if(j == c) 
                break;
            if(!take) 
                break;
            if(!(j>='A'&&j<='Z') && j!='e')
            {
                stateSet.insert(j);
                break;
            }
            else if(j == 'e')
            {
                if(org == c || c == last)
                stateSet.insert(j);
                rtake = true;
                break;
            }
            else
            {
                take = depthFirstSearch(j,org,i[i.size()-1],Map);
                rtake |= take;
            }
        }
    }
    return rtake;
}

map<int,map<char,set<pair<deque<char>,deque<char>>>>> f;
map<int,vector<pair<int,char>>> g;
int num = -1;

void depthFirstSearch2(char c, char way, int last, pair<deque<char>,deque<char>> current)
{
    map<char,set<pair<deque<char>,deque<char>>>> Map2;
    int rep = -2;

    if(last != -1)
    {
        for(auto i : g[last])
        {
            if(i.second == way)
            {
                rep = i.first;
                Map2 = f[i.first];
            }
        }
    }

    Map2[c].insert(current);
    int count = 10;
    while(count--)
    {
        for(auto i : Map2)
        {
            for(auto j : i.second)
            {
                if(!j.second.empty())
                {
                    if(j.second.front()>='A'&&j.second.front()<='Z')
                    {
                        for(auto k : Map[j.second.front()])
                        {
                            deque<char> st,emp;
                            for(auto t : k) st.push_back(t);
                            Map2[j.second.front()].insert({emp,st});
                        }
                    }
                }
            }
        }
    }

    for(auto i : f)
    {
        if(i.second == Map2){
            g[last].push_back({i.first,way});
            return;
        }
    }

    if(rep == -2)
    {
        f[++num] = Map2;
        if(last != -1)
        g[last].push_back({num,way});
    }

    else
        f[rep] = Map2;

    int cc = num;
    for(auto i : Map2)
    {
        for(auto j : i.second)
        {
            if(!j.second.empty())
            {
                j.first.push_back(j.second.front());
                j.second.pop_front();
                depthFirstSearch2(i.first,j.first.back(),cc,j);
            }
        }
    }
}

int main()
{
    int i,j;
    ifstream file("grammer2.txt");

    string line;
    vector<int> fs;
    vector<vector<int>> a;
    char start;
    bool flag = 0;

    cout<<"Given Grammar is: "<<'\n';
    while(getline(file,line))
    {
        if(flag == 0) 
            start = line[0],flag = 1;

        cout<<line<<'\n';
        vector<char> temp;
        char s = line[0];

        for(i=3;i<line.size();i++)
        {
            if(line[i] == '|')
            {
                Map[s].push_back(temp);
                temp.clear();
            }
            else temp.push_back(line[i]);
        }
        Map[s].push_back(temp);
    }

    map<char,set<char>> fMap;
    for(auto i : Map)
    {
        stateSet.clear();
        depthFirstSearch(i.first,i.first,i.first,Map);
        for(auto j : stateSet) 
            fMap[i.first].insert(j);
    }

    cout<<'\n';
    cout<<"FIRST: "<<'\n';
    for(auto i : fMap)
    {
        string ans = "";
        ans += i.first;
        ans += " = {";

        for(char j : i.second)
        {
            ans += j;
            ans += ',';
        }

        ans.pop_back();
        ans+="}";
        cout<<ans<<'\n';
    }

    map<char,set<char>> gMap;
    gMap[start].insert('$');
    int count = 10;

    while(count--)
    {
        for(auto q : Map)
        {
            for(auto r : q.second)
            {
                for(i=0;i<r.size()-1;i++)
                {
                    if(r[i]>='A' && r[i]<='Z')
                    {
                        if(!(r[i+1]>='A' && r[i+1]<='Z')) gMap[r[i]].insert(r[i+1]);
                        else 
                        {
                            char temp = r[i+1];
                            int j = i+1;
                            while(temp>='A' && temp<='Z')
                            {
                                if(*fMap[temp].begin()=='e')
                                {
                                    for(auto g : fMap[temp])
                                    {
                                        if(g=='e') 
                                            continue;
                                        gMap[r[i]].insert(g);
                                    }

                                    j++;

                                    if(j<r.size())
                                    {
                                        temp = r[j];
                                        if(!(temp>='A'&&temp<='Z'))
                                        {
                                            gMap[r[i]].insert(temp);
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        for(auto g : gMap[q.first]) 
                                            gMap[r[i]].insert(g);
                                        break;
                                    }
                                }
                                else
                                {
                                    for(auto g : fMap[temp])
                                        gMap[r[i]].insert(g);
                                    break;
                                }
                            }
                        }
                    }
                }
                if(r[r.size()-1]>='A' && r[r.size()-1]<='Z')
                {
                    for(auto g : gMap[q.first]) 
                        gMap[r[i]].insert(g);
                }
            }
        }
    }

    cout<<'\n';
    cout<<"FOLLOW: "<<'\n';

    for(auto i : gMap)
    {
        string ans = "";
        ans += i.first;
        ans += " = {";
        for(char j : i.second)
        {
            ans += j;
            ans += ',';
        }
        ans.pop_back();
        ans+="}";
        cout<<ans<<'\n';
    }

    string temp = "";
    temp+='.';
    temp+=start;

    deque<char> emp;
    deque<char> state;
    state.push_back(start);

    depthFirstSearch2('!','k',-1,{emp,state});

    cout<<"\nProductions: "<<'\n';
    int cc = 1;
    set<char> action,Goto;
    map<pair<char,deque<char>>,int> pos;

    for(auto i : Map)
    {
        Goto.insert(i.first);
        for(auto j : i.second)
        {
            cout<<"r"<<cc<<": ";
            string ans = "";
            ans += i.first;
            ans+="->";
            deque<char> temp;

            for(auto k : j) 
                ans += k,temp.push_back(k);
            pos[{i.first,temp}] = cc;
            for(auto k : j)
            {
                if(k>='A'&&k<='Z') Goto.insert(k);
                else action.insert(k);
            }

            cout<<ans<<'\n';
            cc++;
        }
    }
    
    cout<<"\nGraph: "<<'\n';
    for(auto map2 : f)
    {
        cout<<'\n';
        cout<<"I";
        cout<<map2.first<<": \n";

        for(auto i : map2.second)
        {
            string ans = "";
            ans += i.first;
            ans += "->";

            for(auto j : i.second)
            {
                for(auto t : j.first) 
                    ans+=t;
                ans+='.';
                for(auto t : j.second) 
                    ans+=t;
                ans+='|';
            }
            ans.pop_back();  

            for(auto tt : ans)
            {
                if(tt == '!') 
                    cout<<start<<'\'';
                else cout<<tt;
            }
            cout<<'\n';
        }
    }
    cout<<'\n';

    cout<<"Edges: "<<'\n';
    for(auto i : g)
    {
        for(auto j : i.second)
        {
            cout<<"I"<<i.first<<" -> "<<j.second<<" -> "<<"I"<<j.first<<"\n";
        }
    }
    action.insert('$');

    cout<<"\nParsing Table:"<<'\n';
    cout<<"St.\t\tAction & Goto"<<'\n';
    int tot = f.size();
    cout<<"  \t";

    for(auto q : action) 
        cout<<q<<'\t';
    for(auto q : Goto) 
        cout<<q<<'\t';
    cout<<'\n';

    for(i=0;i<tot;i++)
    {
        cout<<"I"<<i<<'\t';
        for(auto q : action)
        {
            if(g.count(i))
            {
                int flag = 0;
                for(auto r : g[i])
                {
                    if(r.second == q)
                    {
                        flag = 1;
                        cout<<"S"<<r.first<<"\t";
                        break;
                    }
                }
                if(!flag) cout<<"-"<<'\t';
            }
            else
            {
                int flag = 0;
                for(auto r : f[i])
                {
                    if(r.first == '!')
                    {
                        if(q == '$')
                        {
                        cout<<"AC\t";
                        flag = 1;
                        }
                        else cout<<"-\t";
                    }  
                }
                if(!flag)
                {
                    for(auto r : f[i])
                    {
                        char ccc = r.first;
                        deque<char> chk = (*r.second.begin()).first;
                        int cou = 1;
                        for(auto r : gMap[ccc])
                        {
                            if(q == r)
                                cout<<"r"<<pos[{ccc,chk}]<<"\t";
                            cou++;
                        }
                    }
                }
            }
        }

        for(auto q : Goto)
        {
            if(g.count(i))
            {
                int flag = 0;
                for(auto r : g[i])
                {
                    if(r.second == q)
                    {
                        flag = 1;
                        cout<<r.first<<"\t";
                        break;
                    }
                }
                if(!flag) 
                    cout<<"-"<<'\t';
            }
            else
                cout<<"-"<<'\t';
        }
        cout<<'\n';
    }
	
	
	
	
    return 0;
}
