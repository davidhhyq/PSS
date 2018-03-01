#include "BuffPacketManager.h"

CBuffPacketManager::CBuffPacketManager(void)
{
    //默认为主机序
    m_blSortType = false;
}

CBuffPacketManager::~CBuffPacketManager(void)
{
    OUR_DEBUG((LM_ERROR, "[CBuffPacketManager::~CBuffPacketManager].\n"));
    //Close();
}

IBuffPacket* CBuffPacketManager::Create()
{
    ACE_Guard<ACE_Recursive_Thread_Mutex> WGuard(m_ThreadWriteLock);
    IBuffPacket* pBuffPacket = dynamic_cast<IBuffPacket*>(m_objHashBuffPacketList.Pop());
    return pBuffPacket;
}

bool CBuffPacketManager::Delete(IBuffPacket* pBuffPacket)
{
    ACE_Guard<ACE_Recursive_Thread_Mutex> WGuard(m_ThreadWriteLock);
    CBuffPacket* pBuff = dynamic_cast<CBuffPacket*>(pBuffPacket);

    if(NULL == pBuff)
    {
        return false;
    }

    pBuff->Clear();
    pBuff->SetNetSort(m_blSortType);

    char szPacketID[10] = {'\0'};
    sprintf_safe(szPacketID, 10, "%d", pBuff->GetBuffID());
    bool blState = m_objHashBuffPacketList.Push(szPacketID, pBuff);

    if(false == blState)
    {
        OUR_DEBUG((LM_INFO, "[CBuffPacketManager::Delete]szPacketID=%s(0x%08x).\n", szPacketID, pBuff));
    }
    else
    {
        //OUR_DEBUG((LM_INFO, "[CBuffPacketManager::Delete]szPacketID=%s(0x%08x) nPos=%d.\n", szPacketID, pBuff, nPos));
    }

    return true;
}

void CBuffPacketManager::Close()
{
    //清理所有已存在的指针
    m_objHashBuffPacketList.Close();
}

void CBuffPacketManager::Init(uint32 u4PacketCount, uint32 u4MaxBuffSize, bool blByteOrder)
{
    Close();

    //初始化Hash表
    m_objBuffPacketList.Init(u4PacketCount);
    m_objHashBuffPacketList.Init((int32)u4PacketCount);

    uint32 u4Size = m_objHashBuffPacketList.Get_Count();

    for(uint32 i = 0; i < u4Size; i++)
    {
        CBuffPacket* pBuffPacket = m_objBuffPacketList.GetObject(i);

        if(NULL != pBuffPacket)
        {
            //设置BuffPacket默认字序
            pBuffPacket->Init(DEFINE_PACKET_SIZE, u4MaxBuffSize);
            pBuffPacket->SetNetSort(blByteOrder);
            pBuffPacket->SetBuffID(i);

            char szPacketID[10] = {'\0'};
            sprintf_safe(szPacketID, 10, "%d", i);

            //添加到Hash数组里面
            int32 nHashPos = m_objHashBuffPacketList.Add_Hash_Data(szPacketID, pBuffPacket);

            if(-1 != nHashPos)
            {
                pBuffPacket->SetHashID(i);
            }
        }
    }

    //设定当前对象池的字序
    m_blSortType = blByteOrder;

}

uint32 CBuffPacketManager::GetBuffPacketUsedCount()
{
    return (uint32)m_objHashBuffPacketList.Get_Count() - m_objHashBuffPacketList.Get_Used_Count();
}

uint32 CBuffPacketManager::GetBuffPacketFreeCount()
{
    return (uint32)m_objHashBuffPacketList.Get_Used_Count();
}

