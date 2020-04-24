#include <Transaction.h>
#include <Account.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using::testing::Return;
using::testing::AtLeast;

class MockAccount: public Account{
public:
    MockAccount(int id, int balance):Account(id, balance){}
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
};

class MockTransaction: public Transaction{
public:
    MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

TEST(Account, GetBalance){
    MockAccount acc(0,100);
    EXPECT_CALL(acc, GetBalance()).WillOnce(Return(50));
    int x = acc.GetBalance();
}

TEST(Account, ChangeBalance){
    MockAccount acc(0, 100);
    
    EXPECT_THROW(acc.ChangeBalance(50), std::runtime_error);
    acc.Lock();
    acc.ChangeBalance(50);
    
    EXPECT_EQ(acc.GetBalance(), 150);
    
}

TEST(Account, Lock){
    MockAccount acc(0, 100);
    
    acc.Lock();
    
    EXPECT_CALL(acc, Lock()).Times(1);
    
    EXPECT_THROW(acc.Lock(), std::runtime_error);
    
}

TEST(Account, Unlock){
    MockAccount acc(0, 100);
    
    EXPECT_CALL(acc, Unlock()).Times(1);
}

TEST(Transaction, SaveToDataBase){
    MockAccount f_acc(0, 200);
    MockAccount t_acc(1, 300);
    MockTransaction tr;
    EXPECT_CALL(tr, SaveToDataBase(f_acc, t_acc, 150)).Times(1);
}
