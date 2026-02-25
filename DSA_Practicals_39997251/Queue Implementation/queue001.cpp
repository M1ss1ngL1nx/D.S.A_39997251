#include<iostream>
using namespace std;
#include<queue>
#include<string>
int main(){
	queue<string> country;
	
	country.push("Angola");
	country.push("Bohm");
	country.push("Fealla");
	country.push("Reznikov");
	country.push("Wembley");
	
	cout<<country.empty()<<"\n";
	cout<<country.size()<<"\n";
	cout<<country.front()<<"\n";
	cout<<country.back()<<"\n";
	
	country.push("Pandora");
	country.pop();
	
	cout<<country.front()<<"\n";
	cout<<country.back()<<"\n";
	//cout<<country;
}
