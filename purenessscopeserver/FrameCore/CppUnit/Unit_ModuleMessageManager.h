#ifndef _UNIT_MODULEMESSAGEMANAGER_H
#define _UNIT_MODULEMESSAGEMANAGER_H

#ifdef _CPPUNIT_TEST

#include "Unit_Common.h"
#include "ModuleMessageManager.h"

class CUnit_ModuleMessageManager : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(CUnit_ModuleMessageManager);
    CPPUNIT_TEST(Test_SendModuleMessage);
    CPPUNIT_TEST(Test_SendFrameMessage);
    CPPUNIT_TEST_SUITE_END();

public:
    CUnit_ModuleMessageManager();

    virtual ~CUnit_ModuleMessageManager();

    CUnit_ModuleMessageManager(const CUnit_ModuleMessageManager& ar);

    CUnit_ModuleMessageManager& operator = (const CUnit_ModuleMessageManager& ar)
    {
        if (this != &ar)
        {
            ACE_UNUSED_ARG(ar);
        }

        return *this;
    }

    virtual void setUp(void);

    virtual void tearDown(void);

    void Test_SendModuleMessage(void);  //����ģ������ݷ���

    void Test_SendFrameMessage(void);   //������Ϣ����

private:
    CModuleMessageManager* m_pModuleMessageManager;
};

#endif

#endif