#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "address.h"
#include "credit_card.h"
#include "person.h"
#include "product.h"
#include "store.h"
#include "transaction.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::string;

const int MAX_ITEMS = 100;

bool read_line(ifstream& file, string& line)
{
	if (!getline(file, line))
		return false;
	if (!line.empty() && line[line.size() - 1] == '\r')
		line.erase(line.size() - 1);
	return true;
}

int main()
{
	Store store1;

	Person people[MAX_ITEMS];
	credit_card cards[MAX_ITEMS];
	string card_owners[MAX_ITEMS];
	product products[MAX_ITEMS];
	int num_people = 0;
	int num_cards = 0;
	int num_prods = 0;
	string line;


	ifstream people_file("people.txt");
	if (!people_file)
	{
		cout << "Error: could not open people.txt" << endl;
		return 1;
	}
	read_line(people_file, line);
	num_people = std::atoi(line.c_str());
	if (num_people > MAX_ITEMS)
		num_people = MAX_ITEMS;
	for (int i = 0; i < num_people; i++)
	{
		string name, phone;
		address addr;
		read_line(people_file, name);
		read_line(people_file, phone);
		read_line(people_file, addr.address_line1);
		read_line(people_file, addr.address_line2);
		read_line(people_file, addr.city);
		read_line(people_file, addr.state);
		read_line(people_file, addr.zip);

		people[i].name(name);
		people[i].phone(phone);
		people[i].person_address(addr);
	}
	people_file.close();

	ifstream card_file("credit_card.txt");
	if (!card_file)
	{
		cout << "Error: could not open credit_card.txt" << endl;
		return 1;
	}
	read_line(card_file, line);
	num_cards = std::atoi(line.c_str());
	if (num_cards > MAX_ITEMS)
		num_cards = MAX_ITEMS;
	for (int i = 0; i < num_cards; i++)
	{
		read_line(card_file, card_owners[i]);
		read_line(card_file, line);
		cards[i].cc_number = std::atoi(line.c_str());
		read_line(card_file, line);
		cards[i].limit = std::atof(line.c_str());
		read_line(card_file, line);
		cards[i].current_balance = std::atof(line.c_str());
	}
	card_file.close();


	ifstream product_file("products.txt");
	if (!product_file)
	{
		cout << "Error: could not open products.txt" << endl;
		return 1;
	}
	read_line(product_file, line);
	num_prods = std::atoi(line.c_str());
	if (num_prods > MAX_ITEMS)
		num_prods = MAX_ITEMS;
	for (int i = 0; i < num_prods; i++)
	{
		read_line(product_file, products[i].name);
		read_line(product_file, products[i].description);
		read_line(product_file, line);
		products[i].price = std::atof(line.c_str());
	}
	product_file.close();

	
	for (int i = 0; i < num_people; i++)
	{
		for (int j = 0; j < num_cards; j++)
		{
			if (card_owners[j] == people[i].name())
			{
				people[i].person_credit_card(cards[j]);
				break;
			}
		}
		store1.add_customer(people[i]);
	}
	for (int i = 0; i < num_prods; i++)
		store1.add_product(products[i]);

	cout << "Store info: " << endl << endl;
	cout << store1.store_info() << endl << endl;


	std::srand((unsigned) std::time(0));
	int num_transactions = 11 + std::rand() % 89;

	for (int i = 0; i < num_transactions; i++)
	{
		int cust_index = std::rand() % store1.num_customers();
		int prod_index = std::rand() % store1.num_products();
		int quantity = 1 + std::rand() % 10;


		Person customer = store1.get_customer(cust_index);
		product item = store1.get_product(prod_index);

		store1.make_purchase(customer, item, quantity);
	}


	cout << "Store info: " << endl << endl;
	cout << store1.store_info() << endl << endl;
}
