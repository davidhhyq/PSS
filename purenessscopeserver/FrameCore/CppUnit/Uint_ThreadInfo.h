#ifndef UNIT_THREADINFO_H
#define UNIT_THREADINFO_H

#ifdef _CPPUNIT_TEST

#include "Unit_Common.h"
#include "ThreadInfo.h"

class CUnit_ThreadInfo : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(CUnit_ThreadInfo);
    CPPUNIT_TEST(Test_ThreadInfo);
    CPPUNIT_TEST_SUITE_END();

public:
    CUnit_ThreadInfo();

    virtual ~CUnit_ThreadInfo();

    CUnit_ThreadInfo(const CUnit_ThreadInfo& ar);

    CUnit_ThreadInfo& operator = (const CUnit_ThreadInfo& ar)
    {
        if (this != &ar)
        {
            ACE_UNUSED_ARG(ar);
        }

        return *this;
    }

    virtual void setUp(void);

    virtual void tearDown(void);

    void Test_ThreadInfo(void);

private:
    CThreadInfo* m_pThreadInfo;
};

#endif

#endif
