#pragma once

#include <unordered_map>
#include <functional>
#include <muduo/net/TcpConnection.h>

#include "usermodel.h"
#include "json.hpp"

using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

// 处理消息的回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp time)>;

// 业务类：使用单例模式
class ChatService
{
public:
    static ChatService *instance();
    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);
    // 处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);

private:
    // 构造函数私有化
    ChatService();

    // 存储消息id和其对应的业务处理方法
    std::unordered_map<int, MsgHandler> _msgHandlerMap;

    // 数据操作类对象
    UserModel _userModel;
};
