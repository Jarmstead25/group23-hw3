#include "credit_card.h"
#include <sstream>
#include <iomanip>

bool credit_card::make_purchase(double purchase_amount)
{
    if (purchase_amount <= 0)
    {
       return false;
    }
     
    if (current_balance + purchase_amount > limit)
    {
       return false;

    }
    
    current_balance += purchase_amount;
    return true;
}

bool credit_card::make_payment(double payment_amount)
{
    if (payment_amount <= 0)
    {
        return false;
    }

    if (payment_amount > current_balance)
    {
        return false;
    }

    current_balance -= payment_amount;
    return true;
}

std::string credit_card::credit_card_info()
{
    std::ostringstream output;

    output << std::fixed << std::setprecision(2);
    output << "Credit card number: " << cc_number << "\n";
    output << "Credit Card Limit: $" << limit << "\n";
    output << "Current Balance: $" << current_balance << "\n";

    return output.str();
}

