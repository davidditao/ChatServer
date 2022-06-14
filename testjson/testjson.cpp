#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// 1. 数据序列化
string serialize01()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "lisi";
    js["msg"] = "hello!";

    // cout<<js<<endl;
    string sendBuf = js.dump();
    // cout<<sendBuf.c_str()<<endl;
    return sendBuf;
}

// 2. 序列化更复杂的数据
string serialize02()
{
    json js;
    js["id"] = "zhang san";
    // 添加数组
    js["name"] = {1, 2, 3, 4, 5};

    // js["msg"]["zhang san"] = "hello lisi";
    // js["msg"]["lisi"] = "hello zhang san";
    js["msg"] = {{"zhang san", "hello lisi"}, {"lisi", "hello zhang san"}};
    // cout<<js<<endl;
    string sendBuf = js.dump();
    // cout<<sendBuf.c_str()<<endl;
    return sendBuf;
}

// 3. 序列化容器
string serialize03()
{
    json js;

    // vector
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    js["vector"] = vec;

    // map
    map<int, string> m;
    m.insert({1, "a"});
    m.insert({2, "b"});
    m.insert({3, "c"});

    js["map"] = m;

    // cout<<js<<endl;
    string sendBuf = js.dump();
    // cout<<sendBuf.c_str()<<endl;
    return sendBuf;
}

// 4. 反序列化
void deserialize01(string recvBuf)
{
    json jsbuf = json::parse(recvBuf);
    cout << jsbuf["msg_type"] << endl;
    cout << jsbuf["from"] << endl;
    cout << jsbuf["to"] << endl;
    cout << jsbuf["msg"] << endl;
}

void deserialize02(string recvBuf)
{
    json jsbuf = json::parse(recvBuf);
    cout << jsbuf["id"] << endl;

    auto arr = jsbuf["name"];
    for (int a : arr)
    {
        cout << a << " ";
    }
    cout << endl;

    auto msgjs = jsbuf["msg"];
    cout << msgjs["zhang san"] << endl;
    cout << msgjs["lisi"] << endl;
}

void deserialize03(string recvBuf)
{
    json jsbuf = json::parse(recvBuf);

    vector<int> vec = jsbuf["vector"];
    for (int &v : vec)
    {
        cout << v << " ";
    }
    cout << endl;

    map<int, string> m = jsbuf["map"];
    for (auto p : m)
    {
        cout << p.first << " " << p.second << endl;
    }
}

int main()
{
    string recvBuf;
    // recvBuf = serialize01();
    // deserialize01(recvBuf);

    // recvBuf = serialize02();
    // deserialize02(recvBuf);

    recvBuf = serialize03();
    deserialize03(recvBuf);

    return 0;
}