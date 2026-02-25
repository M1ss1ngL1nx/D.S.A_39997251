#include<iostream>
using namespace std;
#include<queue>
int main(){
	int input, sum=0;
	queue<int> nums;
	
	cout<<"Please enter a numerical value to begin(input -0 to end program): ";
	while(input != -0){
		
		cin>> input;
		cout<<"\n";
		nums.push(input);
		cout<<"Again(enter -0 to end program):";	
	}
	int size = nums.size();
	
	for(int i = 0;i <= size; i++){
		sum = sum + nums.front();
		nums.pop();
	}
	cout<<"Sum of all numbers is "<<sum<<"\n";
	cout<<"Number of integers inputted is "<<size-1<<"\n";

}
