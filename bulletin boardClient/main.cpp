#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

// �|�[�g�ԍ�
const unsigned short SERVERPORT = 8888;

// ����M���郁�b�Z�[�W�̍ő�l
const unsigned int MESSAGELENGTH = 1024;

int main()
{
    char Hp = 0;
    char Attack = 0;
    char Magic = 0;

    int ret;
    // WinSock�̏�����	WinSock2.2
    WSADATA wsaData;
    ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    // if (ret == SOCKET_ERROR)
    if (ret != 0)
    {
        /*
            �G���[����
        */
    }

    // �\�P�b�g�f�B�X�N���v�^
    SOCKET sock;

    // UDP�\�P�b�g�쐬
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // �ڑ���T�[�o��IP�A�h���X����͂�����
    std::string serverIpAddress;
    std::cout << "Input Server IPv4 address :";
    std::cin >> serverIpAddress;

    while (true)
    {
        // �ڑ���T�[�o�̃\�P�b�g�A�h���X���i�[
        SOCKADDR_IN toAddr;
        const int tolen = sizeof(toAddr);
        memset(&toAddr, 0, sizeof(toAddr));
        toAddr.sin_family = AF_INET;
        toAddr.sin_port = htons(SERVERPORT);
        inet_pton(AF_INET, serverIpAddress.c_str(), &toAddr.sin_addr.s_addr);

        char message[MESSAGELENGTH];	// �T�[�o���ƃT�C�Y�����킹�邱��
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
                    �G���[����
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
            �G���[����
        */
    }

    // WinSock�̏I������
    ret = WSACleanup();
    //if (ret == SOCKET_ERROR)
    if (ret != 0)
    {
        /*
            �G���[����
        */
    }

    return 0;
}