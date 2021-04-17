#include "aliparlakci_Parlakci_Ali_hw5_wallet.h"

Wallet::Wallet() : master(nullptr), lenght(0)
{
}

Wallet::Wallet(const Wallet& original)
{
	if (original.lenght > 0)
	{
		this->master = new Money[original.lenght];
		for (int i = 0; i < original.lenght; i++)
		{
			*(master+i) = *(original.master+i);
		}
		this->lenght = original.lenght;
	}
	else
	{
		this->master = nullptr;
		this->lenght = 0;
	}
}

Wallet::~Wallet()
{
    delete[] master;
}

string Wallet::tostring() const
{
    ostringstream out;

    for (int i = 0; i < lenght - 1; i++)
    {
        out << master[i].currency << " " << master[i].amount;
        out << " - ";
    }
    out << master[lenght - 1].currency << " " << master[lenght - 1].amount;
    
    return out.str();
}

Wallet Wallet::operator+(const Wallet& rhs) const
{
    Wallet result = Wallet(*this);

    for (int i = 0; i < rhs.lenght; i++)
    {
        result = result + rhs.master[i];
    }

    return result;
}

Wallet Wallet::operator+(const Money& rhs) const
{
    Wallet result = Wallet(*this);

    bool doesExist = false;
    for (int i = 0; i < (result.lenght) && !doesExist; i++)
    {
        if (result.master[i].currency == rhs.currency)
        {
            result.master[i].amount += rhs.amount;
            doesExist = true;
        }
    }

    if (!doesExist)
    {
		delete[] result.master;
        result.master = new Money[this->lenght + 1];
        result.lenght = this->lenght + 1;
        for (int i = 0; i < result.lenght - 1; i++)
        {
            result.master[i] = this->master[i];
        }
        result.master[result.lenght - 1] = rhs;
    }

    return result;

}

Wallet Wallet::operator-(const Money& rhs) const // Broken
{
    Wallet result = Wallet(*this);

    Money new_money;
    bool isExact = false;

    int number_of_items = 0;
    for (int i = 0; i < this->lenght; i++)
    {
        number_of_items++;
        Money &money_in_wallet = result.master[i];

        if (result.master[i].currency == rhs.currency)
        {
            if(money_in_wallet.amount > rhs.amount)
            {
                money_in_wallet.amount -= rhs.amount;
            }
            else if (money_in_wallet.amount == rhs.amount)
            {
                isExact = true;
                number_of_items--; // We remove the money from wallet
            }
            new_money = money_in_wallet;
        }
    }

    result.master = new Money[number_of_items];
    result.lenght = number_of_items;

    int original_index = 0;
    for (int i = 0; i < number_of_items; i++)
    {
        if (new_money.currency == this->master[original_index].currency)
        {
            if (isExact)
            {
                original_index++;
            }
            else
            {
                result.master[i] = new_money;
            }
        }
        else
        {
            result.master[i] = this->master[original_index];
        }

        original_index++;
    }

    return result;
}

const Wallet& Wallet::operator=(const Wallet& rhs)
{
	if (this->master != rhs.master)
	{
		delete[] this->master;
		this->master = new Money[rhs.lenght];
		this->lenght = rhs.lenght;

		for (int i = 0; i < this->lenght; i++)
		{
			this->master[i] = rhs.master[i];
		}
	}

    return *this;
}

const Wallet& Wallet::operator+=(const Wallet& rhs)
{
    Wallet result = Wallet(*this);

    for (int i = 0; i < rhs.lenght; i++)
    {
        result = result + rhs.master[i];
    }

    this->operator=(result);

    return *this;
}

bool Wallet::operator==(const Wallet& rhs) const
{
    if (this->lenght != rhs.lenght)
    {
        return false;
    }
    else
    {
        for(int i = 0; i < this->lenght; i++)
        {
            bool found = false;
            for(int j = 0; j < rhs.lenght && !found; j++)
            {
                found = rhs.master[j] == this->master[i] ? true : found;
            }
            
            if (!found)
            {
                return false;
            }
        }

        return true;
    }
}

bool Wallet::operator>=(const Money& rhs) const
{
    for (int i = 0; i < this->lenght; i++)
    {
        if (this->master[i].currency == rhs.currency)
        {
            if (this->master[i].amount >= rhs.amount)
            {
                return true;
            }
        }
    }

    return false;
}

bool operator<=(const Money& lhs, const Wallet& rhs)
{
    return rhs >= lhs;
}

ostream &operator<<(ostream &lhs, const Wallet &rhs)
{
    lhs << rhs.tostring();
    return lhs;
}

bool operator==(const Money& lhs, const Money& rhs)
{
    return lhs.amount == rhs.amount && rhs.currency == lhs.currency;
}
