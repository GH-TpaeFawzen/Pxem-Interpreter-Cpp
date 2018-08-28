#include<iostream>
#include<fstream>
#include<stack>
#include<string>
using namespace std;

string extractor(string s);
void run(string proc, bool d);
void run(string proc);

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
		/*
		void dott(){
			//This is for .t operation.
			temporal=pop();
			temb=true;
		}
		void dotm(){
			//This is for .m operation.
			if(!temb)	return;
			push(temporal);
			temb=false;
		}
		*/
		
		/*
		void dotp(){
			while(!stack.empty()){
				cout << char(stack.top());
				stack.pop();
			}
		}
		void doto(){
			cout << char(stack.top());
			stack.pop();
		}
		void dotn(){
			cout << int(stack.top());
			stack.pop();
		}
		void doti(){
			char tmp;
			cin >> tmp;
			//TBH what does that mean "If you reach to EOF, it returns -1"?
			if(cin::eof()){
				tmp = -1;
			}
			stack.push(tmp);
		}
		void dot_(){
			int tmp;
			cin >> tmp;
			stack.push(tmp);
		}
		void dotc(){
			if(stack.empty())	return;
			int tmp=stack.top();
			stack.push(tmp);
		}
		void dots(){
			if(stack.empty())	return;
			stack.pop();
		}
		void dotv(){
			size_t n=stack.size();
			int tmp[n];
			for(size_t i=0; !stack.empty(); i++){
				tmp[i]=stack.top();
				stack.pop();
			}
			for(size_t i=0; i<n; i++){
				stack.push(tmp[i]);
			}
		}
		void dotf(string f;){
			while(!f.empty()){
				stack.push(f.
			}
		}
		*/
};

int main(int argc, char* argv[]){
	try{
		if(argc!=2&&argc!=3){
			throw "WRONG USAGE! You must use in this format!: ";
		}
	}catch(const char* e){
		cerr << e <<  argv[0] << " [FileName]" << endl;
		return -1;
	}
	
	static ifstream fin(argv[1]);

	try{
		if(!fin.is_open()){
			throw "Error! No such file does exist!";
		}
	}catch(const char* e){
		cerr << e << endl;
		return -2;
	}
	
		string fname = argv[1];
	
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
	
	//cout << proc << endl;
	
	try{
		if(argc==3){
			//cout << argv[2] << endl;
			if(argv[2]=="-d"){
				run(proc, true);
			}
			else{
				run(proc);
			}
		}else{
			run(proc);
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

void run(string proc, bool d){
	PxemStack tk;	//stack
	int reg;	//Temporal Region
	bool reu=false;	//Whether reg is stored or not
	
	size_t ptr=0;	//Pointer
	string str="";	//Temporal String until it ptr reaches to order
	
	int i1, i2;
	char c1;
	
	//bool sawDot=false;
	while(ptr<proc.size()){
	
		//From Below:Debug Part
		//if(d){
			cout << ptr << endl;
			cout << str << endl;
			
			cout << proc << endl;
			for(size_t i=0; i<ptr; i++){
				cout << ' ';
			}
			cout << '^' << endl;
		//}
		//From Above:Debug Part
		
		if(proc[ptr]=='.'){
			for(size_t i=str.size(); i>0; i--){
				tk.push(str[i-1]);
			}
			str="";
			switch(proc[++ptr]){
				case 'p':
					//Outputs the entire contents of tk as string.
					while(!tk.empty()){
						cout << (char)tk.pop();
					}
					cout << endl;
					break;
				case 'o':
					//Outputs one popped valued as character.
					if(!tk.empty()){
						cout << (char)tk.pop();
					}
					break;
				case 'n':
					//Outputs one popped value as a numeral value.
					if(!tk.empty()){
						cout << (int)tk.pop();
					}
					break;
				case 'i':
					//Gets an input and push it as a character. If the data was EOF, -1 will be pushed.
					cin >> c1;
					tk.push((cin.eof())?-1:c1);
					break;
				case '_':
					//Gets an input and push it as an integer.
					
					cin >> i1;
					tk.push(i1);
					break;
				case 'c':
					//Copies popped value and pushes two of them.
					if(!tk.empty()){
						c1=tk.pop();
						tk.push(c1);
						tk.push(c1);
					}
					break;
				case 's':
					//Just throws popped value away.
					if(!tk.empty()){
						tk.pop();
					}
					break;
				case 'v':
					//Reverses the content of stack. You should not do this for too many times.
					int tmpn1=tk.size();
					char tmp4[tmpn1];
					for(size_t i=0; i<tmpn1; i++){
						tmp4[i]=tk.pop();
					}
					for(size_t i=0; i<tmpn1; i++){
						tk.push(tmp4[i]);
					}
					break;
				case 'f':
					//Pushes the content of file as string. You can use this command as many times as you'd like.
					
					break;
				case 'e':
					//Runs the content of file as Pxem code. This will be run at another process. The content of stack will be copied to new one. After it stops the content of new one will be stacked to old one.
					break;
				case 'r':
					//Pops, then generate one random number that is 0 or bigger and smaller than popped value. Generated number will be pushed.
					break;
				case 'w':
					//Pops the stack. If it is 0, skips to next to ".a".
					if(!tk.empty()){
						
					}
					break;
				case 'x':
					//Pops twice. If former-popped value ISN't smaller than latter one, skips to next to ".a".
					if(tk.size()>=2){
						
					}
					break;
				case 'y':
					//Pops twice. If former-popped value ISN'T bigger than latter one, skips to next to ".a".
					if(tk.size()>=2){
						
					}
					break;
				case 'z':
					//Pops twice. If they are equal, skips to next to ".a".
					if(tk.size()>=2){
						
					}
					break;
				case 'a':
					//Goes back to either .w, .x, .y, or .z. If no commands, that's an error.
					break;
				case 't':
					//Stores popped-value to reu, the temporal region.
					reg=tk.pop();
					break;
				case 'm':
					//Pushes the value on the temporal region. If empty, don't.
					if(reu){
						tk.push(reg);
					}
					break;
				case 'd':
					//Ends the program.
					return;
					break;
				case '+':
					//Pops twice, then pushes its sum.
					if(tk.size()>=2){
						i1=tk.pop();
						i2=tk.pop();
						tk.push(i1+i2);
					}
					break;
				case '-':
					//Pops twice, then pushes its difference(but in positive integer).
					if(tk.size()>=2){
						i1=tk.pop();
						i2=tk.pop();
						tk.push((i1>i2)?(i1-i2):(i2-i1));
					}
					break;
				case '!':
					//Pops twice, then pushes its product.
					if(tk.size()>=2){
						i1=tk.pop();
						i2=tk.pop();
						tk.push(i1*i2);
					}
					break;
				case '$':
					//Pops twice, then pushes its .
					if(tk.size()>=2){
						i1=tk.pop();
						i2=tk.pop();
						tk.push((i1>i2)?(i1/i2):(i2/i1));
					}
					break;
				case '%':
					//Pops twice, then pushes its mod.
					if(tk.size()>=2){
						i1=tk.pop();
						i2=tk.pop();
						tk.push((i1>i2)?(i1%i2):(i2%i1));
					}
					break;
				default:
					//It was NOT a command: push those characters.
					tk.push('.');
					tk.push(proc[ptr]);
					break;
			}
		}else{
			str=str+proc[ptr];
		}
		++ptr;
	}
}

void run(string proc){
	run(proc, false);
}
