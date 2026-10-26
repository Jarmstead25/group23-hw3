//code for store class here
#include <iostream>
#include <string>
#include "store.h"

using std::string;
using std::cout;

static const int MAX_ITEMS = 100;


static string with_newline(const string& s)
{
	if (s.empty() || s[s.size() - 1] != '\n')
		return s + "\n";
	return s;
}


Store::Store()
{
	num_customers_ = 0;
	num_products_ = 0;
	num_transactions_ = 0;
}


void Store::num_customers(int customer_count) { num_customers_ = customer_count; }
int Store::num_customers() { return num_customers_; }

void Store::num_products(int product_count) { num_products_ = product_count; }
int Store::num_products() { return num_products_; }

void Store::num_transactions(int transaction_count) { num_transactions_ = transaction_count; }
int Store::num_transactions() { return num_transactions_; }


bool Store::add_customer(Person customer)
{
	if (num_customers_ >= MAX_ITEMS)
		return false;
	customers_[num_customers_] = customer;
	num_customers_++;
	return true;
}


bool Store::update_customer(int index, Person customer)
{
	if (index < 0 || index >= num_customers_)
		return false;
	if (find_customer(customer) != index)
		return false;
	customers_[index] = customer;
	return true;
}

Person Store::get_customer(int index)
{
	if (index < 0 || index >= num_customers_)
		return Person();
	return customers_[index];
}


bool Store::add_product(product item)
{
	if (num_products_ >= MAX_ITEMS)
		return false;
	products_[num_products_] = item;
	num_products_++;
	return true;
}


product Store::get_product(int index)
{
	if (index < 0 || index >= num_products_)
		return product();
	return products_[index];
}


bool Store::add_transaction(transaction ntransaction)
{
	if (num_transactions_ >= MAX_ITEMS)
		return false;
	transactions_[num_transactions_] = ntransaction;
	num_transactions_++;
	return true;
}


transaction Store::get_transaction(int index)
{
	if (index < 0 || index >= num_transactions_)
		return transaction();
	return transactions_[index];
}


int Store::find_customer(Person cust)
{
	for (int i = 0; i < num_customers_; i++)
	{
		if (customers_[i].name() == cust.name() &&
			customers_[i].phone() == cust.phone() &&
			customers_[i].person_credit_card().cc_number ==
				cust.person_credit_card().cc_number)
		{
			return i;
		}
	}
	return -1;
}


bool Store::make_purchase(Person customer, product item, int amount)
{
	bool success = false;
	int index = find_customer(customer);

	if (index != -1 && amount > 0 && num_transactions_ < MAX_ITEMS)
	{
	
		Person current = customers_[index];
		credit_card card = current.person_credit_card();

		if (card.make_purchase(item.price * amount))
		{
			current.person_credit_card(card);
			update_customer(index, current);

			transaction t;
			t.transaction_number = num_transactions_ + 1;
			t.customer = current;
			t.purchased_item = item;
			t.quantity = amount;
			add_transaction(t);

			cout << "Successful transaction!" << "\n";
			cout << "Transaction Details: " << "\n";
			cout << with_newline(t.transaction_info());
			success = true;
		}
	}

	if (!success)
	{
		cout << "Unsuccessful transaction!" << "\n";
		cout << "Transaction Details: " << "\n";
		cout << "Person: " << with_newline(customer.person_info());
		cout << "Product: " << "\n" << with_newline(item.product_info());
		cout << "Purchase Quantity: " << amount << "\n";
	}
	return success;
}


string Store::product_info()
{
	string info = "Products: \n";
	for (int i = 0; i < num_products_; i++)
		info += with_newline(products_[i].product_info());
	return info;
}


string Store::transaction_info()
{
	string info = "All Transactions: \n";
	for (int i = 0; i < num_transactions_; i++)
		info += with_newline(transactions_[i].transaction_info());
	return info;
}


string Store::customer_info()
{
	string info = "Customers: \n";
	for (int i = 0; i < num_customers_; i++)
		info += with_newline(customers_[i].person_info());
	return info;
}

string Store::store_info()
{
	return customer_info() + product_info() + transaction_info();
}


string Store::purchase_history(Person customer)
{
	string history;
	for (int i = 0; i < num_transactions_; i++)
	{
		Person c = transactions_[i].customer;
		if (c.name() == customer.name() &&
			c.phone() == customer.phone() &&
			c.person_credit_card().cc_number ==
				customer.person_credit_card().cc_number)
		{
			history += with_newline(transactions_[i].transaction_info());
		}
	}
	return history;
}
