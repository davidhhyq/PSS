#ifndef _TESTCASE_H
#define _TESTCASE_H

#include "commons.h"
#include "pthread.h"

//���Ե������ݰ��շ����
bool CheckTcpPacket(_ClientInfo& objClientInfo, _ResultInfo& objResultInfo);

//���Զ�����ݰ��շ����
bool CheckMultipleTcpPacket(int nCount, _ClientInfo& objClientInfo, _ResultInfo& objResultInfo);

//���Զ�������շ������
bool CheckMultipleTcpConnect(int nCount, _ClientInfo& objClientInfo, _ResultInfo& objResultInfo);

//���ԷǷ����ݰ�ͷ������
bool CheckTcpErrorPacketHead(_ClientInfo& objClientInfo, _ResultInfo& objResultInfo);

//��������ճ��
bool CheckTcpHalfPacket(_ClientInfo& objClientInfo, _ResultInfo& objResultInfo);

//���̲߳�������
void* Thread_CheckTcpPacket();

//���Զ��̲߳���
bool CheckTcpMulipleThreadPacket(int nCount, _ClientInfo& objClientInfo, _ResultInfo& objResultInfo);

#endif