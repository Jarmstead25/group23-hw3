//code for transaction struct here
#include <string>
#include "transaction.h"

using std::string;

string transaction::transaction_info()
{
	string info = "Transaction #: " + std::to_string(transaction_number) + "\n";

	info += "Customer: \n";
	string cust = customer.person_info();
	info += cust;
	if (cust.empty() || cust[cust.size() - 1] != '\n')
		info += "\n";

	info += "Product: \n";
	string prod = purchased_item.product_info();
	info += prod;
	if (prod.empty() || prod[prod.size() - 1] != '\n')
		info += "\n";

	info += "Quantity: " + std::to_string(quantity) + "\n";
	return info;
}
