//
//  OrderDataC++.cpp
//  
//
//  Created by Abdassami Alvi on 01/06/2015.
//
//


#include<stdio.h>
#include<iostream>
#include <fstream>
#include <string>
#include <regex>
#include "class_Order.h"

using namespace std;

class_Order* order = NULL;
int a = 0;

void order_data(){
	//Two streams are used to read in the "orderdata" file, one is to process the data and the other is to figure out the order list length
	ifstream orderFileLength("orderdata");
	ifstream orderData("orderdata");
	string line = "";

	//A regular expression that is used to find the pattern email_address:number_of_orders:total_order_value in each line
	regex pattern("[[:w:]]+@[[:w:]\-?.]+.([[:w:]]{2,3}[[:s:]]*)\\:[[:s:][:d:]]+\\:[[:d:][:s:].]*[[:d:]]+");
	//This regular expression is used mathc email addresses
	regex emailPattern("[[:w:]]+@[[:w:]\-?.]+.([[:w:]]{2,3}[[:s:]]*)");

	int i = 0;
	string domain;
	string email;
	int orderNumber;
	double orderValue;
	string delimiter = ":";
	size_t pos = 0;
	string token;
	string dom;
	string delimiterDom = "@";
	size_t posDom = 0;
	std::string::size_type sz;

	//This is used to find the length of the order list
	if (orderFileLength.is_open())
	{
		while (getline(orderFileLength, line))
		{
			if (regex_match(line, pattern))
			{
				a++;
			}
		}
		order = new class_Order[a];
		orderFileLength.close();
	}

	//This section of code searches through the file line by line to see if an order pattern is available, which then splits the line by ':' and '@' to store each section of the order
	if (orderData.is_open())
	{
		while (getline(orderData, line))
		{
			if (regex_match(line, pattern))
			{
				while ((pos = line.find(delimiter)) != std::string::npos) {
					//The parts are then checked upon to see if it matches an email address pattern
					token = line.substr(0, pos);
					if (regex_match(token, emailPattern))
					{
						//If true then any whitespaces are removed and the email is stored in the placeholder
						token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
						email = token;
						dom = token;

						//The email is then further split by the @ symbol to retreve and store the domain name
						while ((posDom = dom.find(delimiterDom)) != std::string::npos) {
							dom.erase(0, posDom + delimiterDom.length());
						}
						domain = dom;
					}
					else
					{
						//If there is no email pattern match then the part is an Order Number and is stored in its respective placeholder
						orderNumber = std::stoi(token);
					}
					line.erase(0, pos + delimiter.length());
				}
				//This line of code is accessed on the last part of the line and is therefore an Order Value and is stored in its respective placeholder with whitespaces removed
				line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
				orderValue = std::stod(line, &sz);

				//The placeholders are used to store the order in an instance of the class object
				order[i].setOrder(domain, email, orderNumber, orderValue);
				i++;
			}
		}
		orderData.close();
	}
}

void sort_orders(){
	string tDom;
	string tEma;
	int tOrn;
	double tOrv;
	//This sort goes through the order list and sorts it by domain name and then by email if order domains match
	for (int i = 0; i <= a - 1; i++)
	{
		for (int j = i + 1; j <= a - 1; j++)
		{
			if (order[i].getDomain() > order[j].getDomain())
			{
				tDom = order[i].getDomain();
				tEma = order[i].getEmail();
				tOrn = order[i].getOrderNumber();
				tOrv = order[i].getOrderValue();
				order[i].setOrder(order[j].getDomain(), order[j].getEmail(), order[j].getOrderNumber(), order[j].getOrderValue());
				order[j].setOrder(tDom, tEma, tOrn, tOrv);
			}
			if (order[i].getDomain() == order[j].getDomain())
			{
				if (order[i].getEmail() > order[j].getEmail())
				{
					tDom = order[i].getDomain();
					tEma = order[i].getEmail();
					tOrn = order[i].getOrderNumber();
					tOrv = order[i].getOrderValue();

					order[i].setOrder(order[j].getDomain(), order[j].getEmail(), order[j].getOrderNumber(), order[j].getOrderValue());
					order[j].setOrder(tDom, tEma, tOrn, tOrv);
				}
			}
		}
	}
}

void produce_report(){
	string tblDomain = "";
	//This loop goes through the length of the order list and prints it out with a header if one is not available
	for (int i = 0; i < a; i++)
	{
		if (tblDomain == "" || order[i].getDomain() != tblDomain)
		{
			cout << "\n";
			tblDomain = order[i].getDomain();
			cout << "Orders from: " << order[i].getDomain() << "\n\n" << order[i].getEmail() << " " << order[i].getOrderNumber() << " " << order[i].getOrderValue() << "\n";
		}
		else if (order[i].getDomain() == tblDomain)
		{
			cout << order[i].getEmail() << " " << order[i].getOrderNumber() << " " << order[i].getOrderValue() << "\n";
		}
	}
	cin.get();
}

int main(void){
	order_data(); 
	sort_orders();
	produce_report();
	return 0;
}