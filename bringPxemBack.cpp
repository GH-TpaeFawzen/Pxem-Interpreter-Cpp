#include<iostream>
#include<fstream>
#include<stack>
#include<string>
using namespace std;

/*
class Pxem{
	private:
		string fname;
		string fcont;
		size_t itr;
		stack tk;
		int tmp;
		
		
	public:
		Pxem(string f, string c){
			fname=extractor(f);
			fcont=c;
			
			
		}
};
*/

string extractor(string s);
int run(string fname, bool isFname);

int main(int argc, char* argv[]){
	try{
		if(argc!=2){
			throw "WRONG USAGE! You must use in this format!: ";
		}
	}catch(const char* e){
		cerr << e <<  argv[0] << " [FileName]" << endl;
		return -1;
	}
	
	//cout << argv[1] << endl;

	ifstream fin(argv[1]);

	try{
		if(!fin.is_open()){
			throw "Error! No such file does exist!";
		}
	}catch(const char* e){
		cerr << e << endl;
		return -2;
	}
	
	//cout << string(argv[1]) << endl;
	string fname = argv[1];
	
	/*
	cout << fname << endl;
	cout << fname.rfind(".pxe") << ' ' << fname.rfind(".pxem") << endl;
	cout << fname.length() << endl;
	*/
	
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
	//2.If you get ".e" command, run contents.
	//3.If you get ".d" command, stop running.
	//4.If you get ".a" command before getting either ".w", ".x", ".y", ".z", that's error.
	//5.If you didn't get ".a" command after getting those commands above, that's also an error.
	
	/*
	string cont;
	fin >> cont;
	//cout << cont << endl;
	*/
	
	return run(fname, true);
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

int run(string inp, bool isFname=false){
	string proc=(isFname)?(extractor(inp)):inp;
	try{
		size_t ptr=0;
		stack<int> stk;
		bool sawDot=false;
		while(ptr<proc.size()){
			switch(proc[ptr]){
				case '.':
					switch(proc[++ptr]){
						case 'p':
							break;
						case 'o':
							break;
						case 'n':
							break;
						case 'i':
							break;
						case '_':
							break;
						case 'c':
							break;
						case 's':
							break;
						case 'v':
							break;
						case 'f':
							break;
						case 'e':
							break;
						case 'r':
							break;
						case 'w':
							break;
						case 'x':
							break;
						case 'y':
							break;
						case 'z':
							break;
						case 'a':
							break;
						case 't':
							break;
						case 'm':
							break;
						case 'd':
							break;
						case '+':
							break;
						case '-':
							break;
						case '!':
							break;
						case '$':
							break;
						case '%':
							break;
						default:
							break;
					}
					++ptr;
					break;
				default:
					stk.push(proc[ptr]);
					++ptr;
					break;
			}
		}
	}catch(const char* e){
		cerr << e << endl;
		return -4;
	}	
	return 0;
}
