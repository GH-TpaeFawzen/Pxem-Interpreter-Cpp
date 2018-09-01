#include<iostream>
#include<fstream>
#include<stack>
#include<string>
#include<cstdlib>
using namespace std;

//This is a class designed for Pxem.
class PxemStack{
	private:
		stack<int> stk;
		//int temporal;	//Temporal Region
		//bool temb;	//Whether the region is used or not
	protected:
		/*
		PxemStack(stack<int> s){
			temporal=0;
			temb=false;
			this.stk=s;
		}
		stack<int> lifeend(){
			return this.stack;
		}
		*/
	public:
		/*
		PxemStack(){
			temporal=0;
			temb=false;
		}
		*/
		void push(int i){
			stk.push(i);
		}
		int pop(){
			if(empty()){
				throw "Runtime Error! You tried to pop although stack is empty!";
			}
			int tmp = stk.top();
			stk.pop();
			return tmp;
		}
		bool empty(){
			return stk.empty();
		}
		size_t size(){
			return stk.size();
		}
		
		void push(string s){
			//cout << s.size() << endl;
			//cout << s[0] << endl;
			for(int i=s.size()-1; i>=0; i--){
				//cout << s[i] << endl;
				push((int)s[i]);
			}
		}
		void push(PxemStack stack){
			string s="";
			while(!stack.empty()){
				s=s+char(stack.pop());
			}
			push(s);
		}
		
		void print(){
			stack<int> tmp = stk;
			while(!tmp.empty()){
				cout << (int)tmp.top() << ' ';
				tmp.pop();
			}
			cout << endl;
		}
};

string extractor(string s);
void run(string proc, string fcon, bool d);
void run(string proc, string fcon);
PxemStack miniRun(string proc, string fcon, PxemStack stk, bool d);
PxemStack miniRun(string fcon, PxemStack stk, bool d);
int GetRandom(int min,int max);
bool isDot(char c);
bool isLBraket(char c);
bool isRBraket(char c);

int main(int argc, char* argv[]){
	try{
		if(argc!=2&&argc!=3){
			throw "WRONG USAGE! You must use in this format!: ";
		}
	}catch(const char* e){
		cerr << e <<  argv[0] << " [OPTIONS] FileName" << endl;
		cerr << "Options:\n\t-d\tRun in debug mode" << endl;
		return -1;
	}
	
	string fname = (argc==2)?(argv[1]):(argv[2]);
	string opt = (argc==3)?(argv[1]):"";
	
	static ifstream fin(fname);
	

	try{
		if(!fin.is_open()){
			throw "Error! No such file does exist!";
		}
	}catch(const char* e){
		cerr << e << endl;
		return -2;
	}
	
	try{
		if(fname.rfind(".pxe")==string::npos&&fname.rfind(".pxem")==string::npos){
			throw "Error! That's not .pxe nor .pxem file!";
		}
		else if(fname.rfind(".pxe")!=fname.length()-4&&fname.rfind(".pxem")!=fname.length()-5){
			throw "Error! That's not .pxe nor .pxem file!";
		}
	}catch(const char* e){
		cerr << e << endl;
		return -3;
	}
	
	//1.Run fname.
	//3.If you get ".d" command, stop running.
	//4.If you get ".a" command before getting either ".w", ".x", ".y", ".z", that's error.
	//5.If you didn't get ".a" command after getting those commands above, that's also an error.
	
	/*
	string cont;
	fin >> cont;
	//cout << cont << endl;
	*/
	
	string proc=extractor(fname);
	string fcon;
	fin >> fcon;
	
	//cout << proc << endl;
	
	try{
		if(opt=="-d"){
			run(proc, fcon, true);
		}else{
			run(proc, fcon);
		}
	}catch(const char* e){
		cerr << e << endl;
		return -4;
	}
	
	return 0;
}

string extractor(string s){
	size_t pos;
	//If you are using Windows
	pos=s.rfind('\\');
	//cout << pos << ' ';
	s=s.substr(pos+1, s.size()-pos-1);
	//If not
	pos=s.rfind('/');
	//cout << pos << endl;
	s=s.substr(pos+1, s.size()-pos-1);
	return s;
}

void run(string proc, string fcon, bool d){
	PxemStack stk;
	miniRun(proc, fcon, stk, d);
}

void run(string proc, string fcon){
	run(proc, fcon, false);
}

PxemStack miniRun(string proc, string fcon, PxemStack stk, bool d){
	PxemStack tk=stk;	//stack
	int reg;	//Temporal Region
	bool reu=false;	//Whether reg is stored or not
	
	size_t ptr=0;	//Pointer
	string str="";	//Temporal String until it ptr reaches to order
	
	int i1, i2;
	char c1;
	
	//stack<size_t> token;	//When you get .w, .x, .y, or .z but won't skip to next to .a, the ptr where it places will be stored. When you get .a later, you will go back to where this token indicates. If you get .a before .w, .x, .y, or .z, or opposite, it's an error.
	//stack<size_t> nekot;	//Where .a locates.
	
	//bool sawDot=false;
	while(ptr<proc.size()){
	
		//From Below:Debug Part
		if(d){
			cout << "Current pointer: " << ptr << endl;
			cout << "String I found so far: " << str << endl;
			cout << "Current Processing Below\n";
			cout << proc << endl;
			for(size_t i=0; i<ptr; i++){
				cout << ' ';
			}
			cout << '^' << endl;
			if(reu==true){
				cout << "Temporal Region: " << reg << endl;
			}else{
				cout << "Temporal Region is Empty" << endl;
			}
			
		}
		//From Above:Debug Part
		
		if(isDot(proc[ptr])){
			tk.push(str);
			str="";
			
			//From Below:Debug Part
			if(d){
				cout << "Current stack: ";
				tk.print();
			}
			//From Above: Debug Part
			
			switch(proc[++ptr]){
				case 'p':{
					//Outputs the entire contents of tk as string.
					
					//Below Here:Debug
					if(d){
						cout << "Here is output: ";
					}
					//Above Here:Debug
					
					while(!tk.empty()){
						cout << (char)tk.pop();
					}
					cout << endl;
					break;
				}
				case 'o':{
					//Outputs one popped valued as character.
					
					//Below Here:Debug
					if(d){
						cout << "Here is output: ";
					}
					//Above Here:Debug
					
					if(!tk.empty()){
						cout << (char)tk.pop();
					}
					break;
				}
				case 'n':{
					//Outputs one popped value as a numeral value.
					
					//Below Here:Debug
					if(d){
						cout << "Here is output: ";
					}
					//Above Here:Debug
					
					if(!tk.empty()){
						cout << (int)tk.pop();
					}
					break;
				}
				case 'i':{
					//Gets an input and push it as a character. If the data was EOF, -1 will be pushed.
					
					//Below Here:Debug
					if(d){
						cout << "Input a character: ";
					}
					//Above Here:Debug
					
					cin >> c1;
					tk.push((cin.eof())?-1:c1);
					break;
				}
				case '_':{
					//Gets an input and push it as an integer.
					
					//Below Here:Debug
					if(d){
						cout << "Input an integer: ";
					}
					//Above Here:Debug
					
					cin >> i1;
					tk.push(i1);
					break;
				}
				case 'c':{
					//Copies popped value and pushes two of them.
					if(!tk.empty()){
						c1=tk.pop();
						tk.push(c1);
						tk.push(c1);
					}
					break;
				}
				case 's':{
					//Just throws popped value away.
					if(!tk.empty()){
						tk.pop();
					}
					break;
				}
				case 'v':{
					//Reverses the content of stack. You should not do this for too many times.
					string tmp4="";
					while(!tk.empty()){
						tmp4=char(tk.pop())+tmp4;
					}
					tk.push(tmp4);
					break;
				}
				case 'f':{
					//Pushes the content of file as string. You can use this command as many times as you'd like.
					for(int i=0; i<fcon.size(); i++){
						tk.push(fcon[i]);
					}
					break;
				}
				case 'e':{
					//Runs the content of file as Pxem code. This will be run at another process. The content of stack will be copied to new one. After it stops the content of new one will be stacked to old one.
					
					//Below Here:Debug
					if(d){
						cout << "I got .e command. Below here is new execution.\n";
					}
					//Above Here:Debug
					
					PxemStack tmpTk = miniRun(fcon, tk, d);
					
					//Below Here:Debug
					if(d){
						cout << "New execution has just terminated. Here is the contents of last stack: ";
						tmpTk.print();
					}
					//Above Here:Debug
					
					tk.push(tmpTk);
					break;
				}
				case 'r':{
					//Pops, then generate one random number that is 0 or bigger and smaller than popped value. Generated number will be pushed.
					i1 = tk.pop();
					tk.push(GetRandom(0, i1-1));
					break;
				}
				case 'w':{
					//Pops the stack. If it is 0, skips to next to ".a".
					if(!tk.empty()){
						if(tk.pop()==0){
							int brak=1;	//Bracket Counter
							while(brak>0){
								if(ptr==proc.size()-1){
									throw "Runtime Error! There was no .a corresponding to .w!";
								}
								if(isDot(proc[++ptr])){
									if(isRBraket(proc[++ptr])){
										brak--;
									}else if(isLBraket(proc[++ptr])){
										brak++;
									}
								}
							}
						}
					}
					break;
				}
				case 'x':{
					//Pops twice. If former-popped value ISN't smaller than latter one, skips to next to ".a".
					if(tk.size()>=2){
						i1=tk.pop();
						i2=tk.pop();
						if(!(i1<i2)){
							int brak=1;	//Bracket Counter
							while(brak>0){
								if(ptr==proc.size()-1){
									throw "Runtime Error! There was no .a corresponding to .x!";
								}
								if(isDot(proc[++ptr])){
									if(isRBraket(proc[++ptr])){
										brak--;
									}else if(isLBraket(proc[++ptr])){
										brak++;
									}
								}
							}
						}
					}
					break;
				}
				case 'y':{
					//Pops twice. If former-popped value ISN'T bigger than latter one, skips to next to ".a".
					if(tk.size()>=2){
						i1=tk.pop();
						i2=tk.pop();
						if(!(i1>i2)){
							int brak=1;	//Bracket Counter
							while(brak>0){
								if(ptr==proc.size()-1){
									throw "Runtime Error! There was no .a corresponding to .y!";
								}
								if(isDot(proc[++ptr])){
									if(isRBraket(proc[++ptr])){
										brak--;
									}else if(isLBraket(proc[++ptr])){
										brak++;
									}
								}
							}
						}
					}
					break;
				}
				case 'z':{
					//Pops twice. If they are equal, skips to next to ".a".
					if(tk.size()>=2){
						i1=tk.pop();
						i2=tk.pop();
						if(i1==i2){
							int brak=1;	//Bracket Counter
							while(brak>0){
								if(ptr==proc.size()-1){
									throw "Runtime Error! There was no .a corresponding to .z!";
								}
								if(isDot(proc[++ptr])){
									if(isRBraket(proc[++ptr])){
										brak--;
									}else if(isLBraket(proc[++ptr])){
										brak++;
									}
								}
							}
						}
					}
					break;
				}
				case 'a':{
					//Goes back to either .w, .x, .y, or .z. If no commands, that's an error.
					int brak=1;	//Bracket Counter
					while(brak>0){
						
						//Below Here:Debug
						if(d){
							cout << "Current Pointer: " << ptr << endl;
							cout << "Current Brackets: " << brak << endl;
							cout << endl;
							cout << proc << endl;
							for(int i=0; i<ptr; i++){
								cout << ' ';
							}
							cout << '^' << endl;
						}
						//Above Here:Debug
						
						if(ptr==0){
							throw "Runtime Error! There was no .w, .x, .y, nor .z corresponding to .a!";
						}
						if(isLBraket(proc[ptr--])){
							if(isDot(proc[--ptr])){
								brak--;
							}
						}else if(isRBraket(proc[ptr--])){
							if(isDot(proc[--ptr])){
								brak++;
							}
						}else{
							ptr--;
						}
					}
					ptr--;
					break;
				}
				case 't':{
					//Stores popped-value to reu, the temporal region.
					reg=tk.pop();
					reu=true;
					break;
				}
				case 'm':{
					//Pushes the value on the temporal region. If empty, don't.
					if(reu){
						tk.push(reg);
						reu=false;
					}
					break;
				}
				case 'd':{
					//Ends the program.
					return tk;
					break;
				}
				case '+':{
					//Pops twice, then pushes its sum.
					if(tk.size()>=2){
						i1=tk.pop();
						i2=tk.pop();
						tk.push(i1+i2);
					}
					break;
				}
				case '-':{
					//Pops twice, then pushes its difference(but in positive integer).
					if(tk.size()>=2){
						i1=tk.pop();
						i2=tk.pop();
						tk.push((i1>i2)?(i1-i2):(i2-i1));
					}
					break;
				}
				case '!':{
					//Pops twice, then pushes its product.
					if(tk.size()>=2){
						i1=tk.pop();
						i2=tk.pop();
						tk.push(i1*i2);
					}
					break;
				}
				case '$':{
					//Pops twice, then pushes its quotient.
					if(tk.size()>=2){
						i1=tk.pop();
						i2=tk.pop();
						tk.push((i1>i2)?(i1/i2):(i2/i1));
					}
					break;
				}
				case '%':{
					//Pops twice, then pushes its modulo.
					if(tk.size()>=2){
						i1=tk.pop();
						i2=tk.pop();
						tk.push((i1>i2)?(i1%i2):(i2%i1));
					}
					break;
				}
				default:{
					//It was NOT a command: push those characters.
					tk.push('.');
					tk.push(proc[ptr]);
					break;
				}
			}
		}else{
			str=str+proc[ptr];
		}
		
		//Below Here:Debug
		if(d){
			cout << endl;
		}
		//Above Here:Debug
		
		++ptr;
	}
	
	return stk;
}

PxemStack miniRun(string fcon, PxemStack stk, bool d){
	//Below Here: Debug
	if(d){
		cout << "Here is the content of file: \n" << fcon << endl;
	}
	//Above Here: Debug
	
	return miniRun(fcon, fcon, stk, d);
}


int GetRandom(int min,int max){
	static int flag;
	
	if (flag == 0) {
		srand((unsigned int)time(NULL));
		flag = 1;
	}
	
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

bool isDot(char c){
	return c=='.';
}

bool isLBraket(char c){
	return (c=='w')||(c=='x')||(c=='y')||(c=='z');
}

bool isRBraket(char c){
	return c=='a';
}
