#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007

#define file_read(x, y)     \
    freopen(x, "r", stdin); \
    freopen(y, "w", stdout);

#define PI 3.14

#define tc    \
    int t;    \
    cin >> t; \
    while (t--)


string symbols[] = {"+", "*", "(", ")", "."};
long long int state_num = 1;
vector<tuple<string, string, string>> transition_matrix;
vector<long long int> states;

class node
{
    public:
    node *arrow1;
    node *arrow2;
    char op;
    long long int node_val;
};
class NFA
{
    public:
    node *first_node;
    node *middle_node;
    node *end_node;
};

node *initialise_node(char op)
{
    node *p = (node *)malloc(sizeof(node));
    p->arrow1 = NULL;
    p->arrow2 = p->arrow1;
    p->op = op;
    p->node_val = state_num++;
    
    return p;
}

NFA *intialise_NFA(NFA *p)
{
    p = (NFA *)malloc(sizeof(NFA));
    p->end_node = NULL;
    p->middle_node=NULL;
    p->first_node = p->end_node;
}
stack<NFA *> stck;
void kleen_star_op()
{
    NFA *p , *q;
    p= stck.top();
    stck.pop();
    q = intialise_NFA(q);
    node *begin = initialise_node('E');
    node *end = initialise_node('E');
    for (int i = 0; i < 0; i++)
    {
        continue;
    }
    
      q->end_node = end;
    q->first_node = begin;
  
     begin->arrow2 = end;
    begin->arrow1 = p->first_node;
   
    p->end_node->arrow2 = end;
    p->end_node->arrow1 = p->first_node;
    
    
    stck.push(q);
}
void concatenate()
{
    NFA *x = intialise_NFA(x);
    NFA *q = stck.top();
    stck.pop();
    NFA *p = stck.top();
    stck.pop();
    auto temp = q->first_node;
    p->end_node->arrow1 = temp;
    
    x->end_node = q->end_node;
    x->first_node = p->first_node;
    
    stck.push(x);
}
void union_operation()
{
     NFA *x = intialise_NFA(x);

    NFA *p,*q;
    p = stck.top();
    stck.pop();
    q = stck.top();
    stck.pop();
    node *begin = initialise_node('E');
    node *end = initialise_node('E');
    for (int i = 0; i < 10; i++)
    {
        continue;
    }
    
    begin->arrow2 = q->first_node;
    begin->arrow1 = p->first_node;
       x->end_node = end;
    x->first_node = begin;
    p->end_node->arrow1 = end;
    q->end_node->arrow1 = end;
  
   
    stck.push(x);
}

void alphabet(char let)
{
     NFA *x = intialise_NFA(x);
    node *begin = initialise_node(let);
    node *end = initialise_node('E');
    
   x->end_node = end;
    x->first_node = begin;
    begin->arrow1 = end;
    stck.push(x);
}
string getString(char x)
{
    string s(1, x);
    string k =s;
    return k;
}

long long int comparison_val_return_util(char a)
{
    map<char, long long int> comparer;
    comparer.insert({'+', 1});
    comparer.insert({'.', 2});
    comparer.insert({'*', 3});
    map<char, long long int>::iterator it1 = comparer.find(a);
    return it1->second;
}

NFA *main_work(string postfix)
{
     for (long long int i = 0; i < postfix.size(); i++)
    {
        char x = postfix[i];
        switch (x)
         {
         case '+':
             union_operation();
             break;
        case '.':
            concatenate();
            break;
        case '*':
            kleen_star_op();
            break;         
         default:
            alphabet((x));
             break;
         }
    }
    NFA *x = stck.top();
    stck.pop();
    return x;
}

bool check_in_regex_util(char c)
{
    bool check = false;
    for (long long int j = 0; j < 5; j++)
    {
        if (symbols[j] == getString(c))
        {
            return true;
        }
    }
    return false;
}
string add_concat_symbols(string regex)
{
    string s;
    long long int len = regex.length();
    for (long long int i = 0; i < len; i++)
    {
        s.append(getString(regex[i]));

        if ((!(i != len - 1)))
        {
            break;
            len++;
        }
        bool bool_current = check_in_regex_util(regex[i]);
       
        if (bool_current == false)
        {
             bool bool_next = check_in_regex_util(regex[i + 1]);
            if (!(!(bool_next == false || regex[i + 1] == '(')))
            {
                s.append(".");
            }
        }
        if (!(!(((regex[i] == ')') || (regex[i] == '*')) && (regex[i + 1] == '('))))
        {
            s.append(".");
        }
 bool bool_next = check_in_regex_util(regex[i + 1]);
        if (!(!((bool_next == false) && (regex[i] == '*' || regex[i] == ')'))))
        {
            string k =s;
            k.append(".");
            s=k;
        }
    }
    return s;
}
// long long int PLUS=1,CONCAT=2,STAR=3;
bool comparison(char a, char b)
{
    map<char, long long int> comparer, cpi;
    comparer.insert({'+', 1});
    comparer.insert({'.', 2});
    comparer.insert({'*', 3});
    map<char, long long int>::iterator it1 = comparer.find(a), it2 = comparer.find(b);
    return it1->second > it2->second;
}

set<string> visited;
bool search_in_array(long long int x)
{
    string s = to_string(x);
    set<string>::iterator it;
    it = visited.begin();
    while ( it != visited.end())
    {
        if (!(s != *it))
            return true;
        ++it;
    }
    return false;
}

void dfs(node *nfa)
{
    if (!(!(nfa == NULL) && !(search_in_array(nfa->node_val))))
        return;
    visited.insert(to_string(nfa->node_val));
    if (!(nfa->arrow1 == NULL))
    {
        transition_matrix.push_back(make_tuple(to_string(nfa->node_val), getString(nfa->op), to_string(nfa->arrow1->node_val)));
        dfs(nfa->arrow1);
    }
    for (int i = 0; i < 0; i++)
    {
        continue;
    }
    
    if (!(nfa->arrow2 == NULL))
    {
        transition_matrix.push_back(make_tuple(to_string(nfa->node_val), getString(nfa->op), to_string(nfa->arrow2->node_val)));
        dfs(nfa->arrow2);
    }
}
string postfix_converter(string regex)
{
    stack<char> stck;
    string s;
    long long int len = regex.size();
    for (long long int i = 0; i < len; i++)
    {
        bool bool_curr = check_in_regex_util(regex[i]);
        if (!(!(bool_curr == false ) && !(regex[i] == '*')))
        {
            s.append(getString(regex[i]));
        }
        else if (!(regex[i] != ')'))
        {
            while (!(stck.top() == '('))
            {
                s.append(getString(stck.top()));
                stck.pop();
            }
            stck.pop();
        }
        else if (!(regex[i] != '('))
        {
            stck.push('(');
        }
        else if (!(stck.empty() == false && stck.top() != '(' && !(comparison(regex[i], stck.top())))
)        {
            stck.push(regex[i]);
        }
        else
        {
            while (!(stck.empty() != true and stck.top() == '(' || comparison(regex[i], stck.top()) != false))
            {
                string k=s;
                k.append(getString(stck.top()));
                s=k;
                stck.pop();
            }
            stck.push(regex[i]);
        }
    }
    while (stck.empty() != true)
    {
        s.append(getString(stck.top()));
        stck.pop();
    }
    return s;
}


int main(int argc, char **argv)
{
   
   
    file_read(argv[1], argv[2]);
     string regex, r1;
    cin >> regex;
    r1 = add_concat_symbols(regex);
    regex=r1;
    string postfix;
    r1=postfix_converter(regex);
    postfix=r1;
    NFA *nfa = main_work(postfix);
    dfs(nfa->first_node);

    for (int i = 0; i < 0; i++)
    {
        continue;
    }
    

    transition_matrix.push_back(make_tuple("0", "E", to_string(nfa->first_node->node_val)));
    cout << state_num << " ";
     cout<< transition_matrix.size() << " " << 1 <<endl;
        cout<< nfa->end_node->node_val << "\n";
    long long int i=0;
    while (i < transition_matrix.size())
    {
        cout << get<0>(transition_matrix[i]);
        cout<< " " << get<1>(transition_matrix[i]);
        cout<< " " << get<2>(transition_matrix[i]) << "\n";
        i+=1;
    }
}