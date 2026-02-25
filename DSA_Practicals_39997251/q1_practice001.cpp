#include<iostream>
using namespace std;
int main(){
	int population = 2000;
	float roi = 0.15;
	float i=0;
	int ppl_add=population*roi;
	
do{
	population = population + ppl_add;
	i = i + 0.5;
}while(population<=2000000);

  std::cout<<"In "<<i<<" years, the population of Brofoyedur has reached "<<population;

}
