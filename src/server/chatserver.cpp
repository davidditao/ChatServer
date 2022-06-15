#include "chatserver.h"
#include "chatservice.h"
#include "json.hpp"
using json = nlohmann::json;

#include <functional>

// 初始化聊天服务器对象
ChatServer::ChatServer(EventLoop *loop, const InetAddress &listenAddr, const string &nameArg)
    : _server(loop, listenAddr, nameArg),
      _loop(loop)
{
    // 注册回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置线程数量
    _server.setThreadNum(4);
}

// 启动服务
void ChatServer::start()
{
    _server.start();
}

// 连接相关回调
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    // 客户端断开连接
    if (!conn->connected())
    {
        conn->shutdown();
    }
}
// 读写相关回调
void ChatServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp receiveTime)
{
    // 将接收到的数据转为string
    string buf = buffer->retrieveAllAsString();
    // 将数据反序列化
    json js = json::parse(buf);

    /**
     * 将网络模块的代码和业务模块的代码解藕：利用回调
     * 通过 js[”msgid“] 来获取 业务处理器handle回调
     */
    // 获取事件对应的处理器
    auto msghandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    // 执行回调
    msghandler(conn, js, receiveTime);
}
