#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::vector;

struct contactNode
{
    int number;
    string name;
    contactNode *next;
    contactNode() : next(NULL){};
    contactNode(int n, string s) : number(n), name(s), next(NULL){};
};

struct Query
{
    string type, name;
    int number;
};

int polyHash(int a, int b, int p, int x)
{
    return (a * x + b) % p;
}

vector<Query> read_queries()
{
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string> &result)
{
    for (int i = 0; i < result.size(); i++)
    {
        if (i == result.size() - 1)
            cout << result[i];
        else
            cout << result[i] << std::endl;
    }
}

void push(contactNode **head_ref, int number, string name)
{
    contactNode *new_node = new contactNode();
    new_node->number = number;
    new_node->name = name;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void removeFirstNode(contactNode **head_ref)
{
    contactNode *temp = *head_ref;
    if ((*head_ref)->next != 0)
        *head_ref = (*head_ref)->next;
    else
        *head_ref = new contactNode();
    delete temp;
}

vector<string> process_queries(const vector<Query> &queries)
{
    int n = queries.size();
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    int m = rand() / 100000;
    vector<contactNode *> contacts(m, new contactNode());
    int a = rand() % 100;
    int b = rand() % 100;
    int p = rand() % 100;

    for (size_t i = 0; i < n; ++i)
    {
        int hash = polyHash(a, b, p, queries[i].number) % m;
        contactNode *node = contacts[hash];
        if (queries[i].type == "add")
        {
            bool was_founded = false;
            while (node != nullptr)
            {
                if (node->number == queries[i].number)
                {
                    node->name = queries[i].name;
                    was_founded = true;
                    break;
                }
                node = node->next;
            }
            // otherwise, just add it
            if (!was_founded)
            {
                push(&contacts[hash], queries[i].number, queries[i].name);
            }
        }
        else if (queries[i].type == "del")
        {
            if (node->number == queries[i].number)
            {
                removeFirstNode(&contacts[hash]);
            }
            else
                while (node->next != nullptr)
                {
                    if (node->next->number == queries[i].number)
                    {
                        node->next = node->next->next;
                        break;
                    }
                    node = node->next;
                }
        }
        else
        {
            string response = "not found";
            while (node != nullptr)
            {
                if (node->number == queries[i].number)
                {
                    response = node->name;
                    break;
                }
                node = node->next;
            }
            result.push_back(response);
        }
    }
    return result;
}

int main()
{
    write_responses(process_queries(read_queries()));
    return 0;
}
