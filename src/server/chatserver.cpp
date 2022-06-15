#include "chatserver.h"

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
}
// 读写相关回调
void ChatServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp receiveTime)
{
}
