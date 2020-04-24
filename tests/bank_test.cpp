#include <Transaction.h>
#include <Account.h>
#include <gtest/gtest.h>
#include <gtest/gmock.h>

using::testing::Return;
using::testing::AtLeast;

class MockAccount: public Account{
public:
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
};

class MockTransaction: public Transaction{
public:
    MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
}

TEST(Account, GetBalance){
    MockAccount acc(0,100);
    
    EXPECT_CALL(acc, GetBalance()).WillOnce(Return(100));
}

TEST(Account, ChangeBalance){
    MockAccount acc(0, 100);
    
    acc.ChangeBalance(50);
    
    EXPECT_EQ(acc.GetBalance(), 150);
    
    acc.Lock();
    EXPECT_THROW(acc.ChangeBalance(50), std::runtime_error("at first lock the account"));
}

TEST(Account, Lock){
    MockAccount acc(0, 100);
    
    acc.Lock();
    
    EXPECT_EQ(acc.is_locked_, true);
    
    EXPECT_THROW(acc.Lock(), std::runtime_error("already locked"));
    
}

TEST(Account, Unlock){
    MockAccount acc(0, 100);
    
    acc.Unlock();
    
    EXPECT_EQ(acc.is_locked_, false);
}

TEST(Transaction, SaveToDataBase){
    MockAccount f_acc(0, 200);
    MockAccount t_acc(1, 300);
    EXPECT_CALL(f_acc, SaveToDataBase(f_acc, t_acc, 150)).Times(AtLeast(1));
}
