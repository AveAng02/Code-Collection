
#include <iostream>
#include <thread>
#include <stdexcept>


class BankAccount
{
public:

    BankAccount()
    : amount(0.0f)
    {}

    void deposit(float value);
    void withdrawl(float value);
    void showBalance();

private:

    float amount;
};

void BankAccount::deposit(float value)
{
    amount += value;
}

void BankAccount::withdrawl(float value)
{
    if(value > amount)
    {
        throw std::underflow_error("Balance not enough!");
        return;
    }

    amount -= value;
}

void BankAccount::showBalance()
{
    std::cout << "Balance: " << amount << std::endl;
}



int main()
{
    BankAccount newAccount;



    return 0;
}





