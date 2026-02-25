#include<iostream>

using namespace std;
#include<queue>

int main(){
	queue<int> numbers;
//	int numbers = {1,2,3,4,5,6,7};
	
	//Insertion in an empty queue
	numbers.push(5);
	numbers.push(22);
	numbers.push(56);
	numbers.push(32);
	numbers.push(12);
	numbers.push(7);
	numbers.push(86);
	numbers.push(90);
	numbers.push(21);
	numbers.push(57);
	numbers.push(99);
	
	//Deletion in queue
	numbers.pop();
	numbers.pop();
	numbers.pop();
	//Using integer value to check whether queue is empty
	int que = numbers.empty();
	
//	conditional statements determining output of program if queue is empty or not
	if(que = 0){
		cout<<"This queue is empty.\n";
	}else{
		cout<<"This queue still has "<<numbers.size()<<" variables in it after dequeueing.\n";
	}
	//Getting position of item in back of queue
	cout<<"Final number in queue after dequeueing is "<<numbers.back()<<"\n";
	
	
	//random work
	
	int venn = 0, van = numbers.size();
	for(venn = 0; venn <= van; venn++){
        cout << numbers.front() << "\n";
        numbers.pop();
        
    }
}
