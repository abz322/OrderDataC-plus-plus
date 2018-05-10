
#include<iostream>
#include <string>

using namespace std;

#ifndef class_Order_H
#define class_Order_H
#pragma once

class class_Order
{
public:

	void setOrder(string, string, int, double);
	string getDomain();
	string getEmail();
	int getOrderNumber();
	double getOrderValue();

private:
	string domain;
	string emailAddress;
	int orderNumber;
	double orderValue;
};

#endif