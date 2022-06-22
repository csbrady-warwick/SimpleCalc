#include "stack.h"
#include <iostream>
#include <cmath>
#include <map>
#include <string>

int main(int argc, char** argv){

	std::map<std::string, std::function<void(output_stack &os)>> fnmap;
	fnmap["+"] = [](output_stack &os){os.push(os.pop() + os.pop());};
	fnmap["-"] = [](output_stack &os){os.push(-os.pop() + os.pop());};
	fnmap["x"] = [](output_stack &os){os.push(os.pop() * os.pop());};
	fnmap["/"] = [](output_stack &os){float d =os.pop(), n=os.pop(); os.push(n/d);};
	fnmap["pi"] = [](output_stack &os){os.push(3.14159);};
	fnmap["sin"] =[](output_stack &os){os.push(sin(os.pop()));};

	interpreter i;
	if (argc == 1){
		std::cout << "Must have input an expression made of of floating point numbers combined with operators listed in fnmap separated by spaces\n";
		exit(1);
	}
	for (int j=1; j<argc; ++j){
		try{
			float val = std::stof(argv[j]);
			i.add_instruction(val);
		} catch(...) {
			i.add_instruction(fnmap[argv[j]]);
		}
	}

	std::cout << i.exec() << "\n";
}
