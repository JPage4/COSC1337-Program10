#ifndef INVENTORY_H
#define INVENTORY_H
#include <string>
using namespace std;

class HouseHold
{
private:
	int id;
	double annualIncome;
	int members;
	string state;

public:
	HouseHold(int, double, int, string);
	void setId(int);
	void setAnnualIncome(double);
	void setMembers(int);
	void setState(string);

	int getId();
	double getAnnualIncome();
	int getMembers();
	string getState();
};

#endif

