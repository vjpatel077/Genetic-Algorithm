#include<bits/stdc++.h>
using namespace std;

const int gen=100;

//Taking Genetic class for storing population
class Genetic{
	public:
		string genome; 
		float total_time;
		int discount;
		Genetic(){
			total_time=0;
			discount=0;
		}
		friend bool ValueCmp(Genetic const &a,Genetic const& b);
		void output();
};

bool ValueCmp(Genetic const& a, Genetic const& b){
    return a.total_time>b.total_time;
}
void Genetic:: output(){
	cout<<this->genome<<"\t"<<this->total_time<<"\t\t"<<this->discount<<endl;
}

string Crossover(string const& a,string const& b){//single crossover
	
	if(a.length()<=2)
		return a;
	else{
		int half=a.length()/2;
		string temp=a;
		for(int i=0;i<a.length();i++){
			if(i>half)
				temp[i]=b[i];
		}
		return temp;
	}
	
}

int rand_func(int limit){
	int random_int = (rand()%limit);
	return random_int;
}

string mutation(string a){
	int x=a.length();	
	int no= (rand()%x);//index generate where mutation need to happen
	unsigned srand(time(NULL));
	float r =(float) rand() / static_cast<float>(RAND_MAX); //generate the randomn value probability between 0 and 1
	if(r>=0.50){
		if(a[no]==0)
			a[no]=1;
		else
			a[no]=0;
	} 
	return a;
}

int main(){
	
	//variable Defined
	int n,shop_no,discount,counter=0,k,random;
	string shop_name,s;
	float shopping_time,time1=0;
	
	//Considerable Database size and time input
	cout<<"Enter the size of testing Database : ";	cin>>n;
	int limit=pow(2,n); //limit=problem space size which can be the 2's power of n(database)
	Genetic g[limit]; //Array of object
	cout<<"Enter the Maximum time : "; cin>>shopping_time;//fitness_limit or max_time_limit
	
	//file opening not test
	ifstream in("database.txt");	//read mode
	if(!in){ 
		cout<<"Failed";
		return EXIT_FAILURE;
	}
	
	string next_gen[2],offspring[2];
	int prev=0;
	
	//parent generate
	for(k=0;k<gen;k++){
			//Generation and fitness value initialization 
	    for(int i=1;i<limit;i++){	
	    	counter++;
	    	random=rand_func(limit);
	        bitset<10> chromosome(random);//change bit size when you change database size
	        s=chromosome.to_string();//binary number converted in string
	        g[i-1].genome= s;
	        reverse(s.begin(),s.end());
	        in.seekg(0,ios::beg);
	        //Fitness value is generated 
	        for(int j=0;j<n;j++){
	        	in>>shop_no>>shop_name>>time1>>discount;
	        	if(s[j]=='1'){
	        		g[i-1].total_time+=time1;
	        		g[i-1].discount+=discount;
				}
			}
			if(g[i-1].total_time>shopping_time) g[i-1].total_time=0;
	    }
	    sort(g, g+limit, ValueCmp); //sorted in descending order respective of time
	    	
	    if(g[0].discount<=prev) break; //convergence condition
	    
	    next_gen[0]=g[0].genome; //Initial population
	    next_gen[1]=g[1].genome; //Initial population
	    
		prev=g[0].discount;
			    
			    //offspring generate
	    for(int j=0;j<(counter/2)-1;j++){ 
	    	
	    	offspring[0]=g[0].genome; //selecting population
	    	offspring[1]=g[1].genome; //selecting population
	    	
	    	offspring[0]=Crossover(offspring[0],offspring[1]);
			offspring[1]=Crossover(offspring[1],offspring[0]);
		
			offspring[0]=mutation(offspring[0]);
			offspring[1]=mutation(offspring[1]);
			
			if(offspring[0]!="000000000"){
				next_gen[0]=offspring[0];
	    		next_gen[1]=offspring[1];
			}
		
		}
		g[0].genome=next_gen[0];
		g[1].genome=next_gen[1];
		sort(g, g+limit, ValueCmp);
	}
	
	cout<<"\nAt Generation : "<<k<<" we have found optimal soultion .";
	string ans=next_gen[0]; //best fittest genome or optimal solution
	cout<<"\n\nVisting store are : ";

	reverse(ans.begin(),ans.end()); 
	in.seekg(0,ios::beg);
	for(int i=0;i<n;i++){
		in>>shop_no>>shop_name>>time1>>discount;
		if(ans[i]=='1')
			cout<<shop_name<<endl;
	}

	return 0;
}

