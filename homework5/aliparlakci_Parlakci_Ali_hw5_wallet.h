#ifndef _WALLET_H
#define _WALLET_H

#include <string>
#include <sstream>

using namespace std;

struct Money
{
    string currency;
    double amount;
    Money() : currency(""), amount(0){};
    Money(string c, double a) : currency(c), amount(a){};
};

class Wallet
{
public:
    Wallet();
    Wallet(const Wallet& original);
    ~Wallet();
    string tostring() const;
    Wallet operator+(const Wallet& rhs) const;
    Wallet operator+(const Money& rhs) const;
    Wallet operator-(const Money& rhs) const;
    const Wallet& operator=(const Wallet& rhs);
    const Wallet& operator+=(const Wallet& rhs);
    bool operator==(const Wallet& rhs) const;
    bool operator>=(const Money& rhs) const;
private:
    Money *master;
    int lenght;
};

bool operator<=(const Money& lhs, const Wallet& rhs);
ostream &operator<<(ostream &lhs, const Wallet &rhs);
bool operator==(const Money& lhs, const Money& rhs);

#endif