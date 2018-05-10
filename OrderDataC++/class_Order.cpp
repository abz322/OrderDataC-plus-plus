#include "class_Order.h"


//The getters and setters are used to store and retrieve orders in the private variables
void class_Order::setOrder(string dom, string ema, int orn, double orv)
{
		domain = dom;
		emailAddress = ema;
		orderNumber = orn;
		orderValue = orv;
}

string class_Order::getDomain(){
	return domain;
}

string class_Order::getEmail(){
	return emailAddress;
}

int class_Order::getOrderNumber(){
	return orderNumber;
}

double class_Order::getOrderValue(){
	return orderValue;
}