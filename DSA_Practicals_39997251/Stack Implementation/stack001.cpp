#include<iostream>
#include<stack>
using namespace std;
int main(){
	stack <int> numbers;
	numbers.push(13);
	numbers.push(90);
	numbers.push(20);
	numbers.push(81);
	
	cout<<numbers.top()<<endl;
	int i;
	for(i = 0; i <= 2;i++){
		numbers.pop();
		cout<<numbers.top()<<endl;
	}
	return 0;
	
}
