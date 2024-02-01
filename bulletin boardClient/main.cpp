#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

// ポート番号
const unsigned short SERVERPORT = 8888;

// 送受信するメッセージの最大値
const unsigned int MESSAGELENGTH = 1024;

int main()
{
    char Hp = 0;
    char Attack = 0;
    char Magic = 0;

    int ret;
    // WinSockの初期化	WinSock2.2
    WSADATA wsaData;
    ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    // if (ret == SOCKET_ERROR)
    if (ret != 0)
    {
        /*
            エラー処理
        */
    }

    // ソケットディスクリプタ
    SOCKET sock;

    // UDPソケット作成
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // 接続先サーバのIPアドレスを入力させる
    std::string serverIpAddress;
    std::cout << "Input Server IPv4 address :";
    std::cin >> serverIpAddress;

    while (true)
    {
        // 接続先サーバのソケットアドレス情報格納
        SOCKADDR_IN toAddr;
        const int tolen = sizeof(toAddr);
        memset(&toAddr, 0, sizeof(toAddr));
        toAddr.sin_family = AF_INET;
        toAddr.sin_port = htons(SERVERPORT);
        inet_pton(AF_INET, serverIpAddress.c_str(), &toAddr.sin_addr.s_addr);

        char message[MESSAGELENGTH];	// サーバ側とサイズを合わせること
        SOCKADDR_IN fromAddr;
        int fromlen = sizeof(fromAddr);
        std::cout << "Input message:";
        std::cin >> message;
        //for (int i = 0; i < 3; i++)
        {
            message[0] = Hp;
            message[1] = Attack;
            message[2] = Magic;
            ret = sendto(sock, message, MESSAGELENGTH, 0, (SOCKADDR*)&toAddr, tolen);
            if (ret == SOCKET_ERROR)
            {
                /*
                    エラー処理
                */
            }
        }

        ret = recvfrom(sock, message, MESSAGELENGTH, 0, (SOCKADDR*)&fromAddr, &fromlen);
        if (ret == SOCKET_ERROR)
        {

        }
        else
        {
            std::cout << message << std::endl;
        }
    }

    ret = closesocket(sock);
    if (ret == SOCKET_ERROR)
    {
        /*
            エラー処理
        */
    }

    // WinSockの終了処理
    ret = WSACleanup();
    //if (ret == SOCKET_ERROR)
    if (ret != 0)
    {
        /*
            エラー処理
        */
    }

    return 0;
}