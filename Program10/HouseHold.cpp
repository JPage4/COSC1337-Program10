#include "HouseHold.h"

HouseHold::HouseHold(int IDnumber, double householdIncome, int householdMembers, string usState)
{
	id = IDnumber;
	annualIncome = householdIncome;
	members = householdMembers;
	state = usState;
}

void HouseHold::setId(int IDnumber)
{
	id = IDnumber;
}

void HouseHold::setAnnualIncome(double householdIncome)
{
	annualIncome = householdIncome;
}

void HouseHold::setMembers(int householdMembers)
{
	members = householdMembers;
}

void HouseHold::setState(string usState)
{
	state = usState;
}


int HouseHold::getId()
{
	return id;
}

double HouseHold::getAnnualIncome()
{
	return annualIncome;
}

int HouseHold::getMembers()
{
	return members;
}

string HouseHold::getState()
{
	return state;
}