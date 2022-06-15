#pragma once

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;

class ChatServer
{
public:
    // 初始化聊天服务器对象
    ChatServer(EventLoop *loop, const InetAddress &listenAddr, const string &nameArg);

    // 启动服务
    void start();

private:
    // 连接相关回调
    void onConnection(const TcpConnectionPtr& conn);
    // 读写相关回调
    void onMessage(const TcpConnectionPtr& conn, Buffer *buffer, Timestamp receiveTime);

    TcpServer _server;  
    EventLoop *_loop;   // 事件循环
};
