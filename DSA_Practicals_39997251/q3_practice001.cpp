#include<iostream>
using namespace std;
#include<string>
int main(){
	int time, reg_mal = 500, over_mal = 750, reg_fem = 550, over_fem = 825, kinder; 
	string name, gender;
	int arr[] = {reg_mal, reg_fem, over_mal, over_fem};
	std::cout<<"Please enter your name: ";
	std::cin>>name;
	std::cout<<"Gender(in all caps): ";
	std::cin>>gender;
	std::cout<<"The amount of time worked this week alone:";
	std::cin>>time;
	std::cout<<"Please how many children do you have: ";
	std::cin>>kinder;
	
	if (time <= 40 && gender = "MALE"){
		std::cout<<"Your pay this week is "<<reg_mal<<" cedis.";
	}else if(time > 40 && gender = "MALE"){
		std::cout<<"Your pay this week is "<<over_mal<<" cedis.";
	}else if (time <= 40 && gender = "FEMALE"){
		std::cout<<"Your pay this week is "<<reg_fem<<" cedis.";
	}else if(time > 40 && gender = "FEMALE"){
		std::cout<<"Your pay this week is "<<over_fem<<" cedis.";
	}
	
	switch(arr){
		case reg_mal:
			nu_pay = reg_mal * 4;
			std::cout<<"Income Tax: "<<nu_pay *0.15<<"\n";
			std::cout<<"NHCL Tax: "<<nu_pay *0.025<<"\n";
			std::cout<<"District Tax: "<<nu_pay *0.01<<"\n";
			std::cout<<"Income Tax: "<<nu_pay *0.15<<"\n";
		break;
		
		case over_mal:
			nu_pay = over_mal * 4;
			std::cout<<"Income Tax: "<<nu_pay *0.15<<"\n";
			std::cout<<"NHCL Tax: "<<nu_pay *0.025<<"\n";
			std::cout<<"District Tax: "<<nu_pay *0.01<<"\n";
			std::cout<<"Income Tax: "<<nu_pay *0.15<<"\n";
		break;
	}
}
