#ifndef STACK_H
#define STACK_H

#include<vector>
#include<stack>
#include<functional>

class output_stack{
	private:
		std::stack<float> _stack;
	public:
		void push(float value){_stack.push(value);}
		float pop(){float f = _stack.top(); _stack.pop(); return f;}
};

class interpreter{
	private:
		std::vector<std::function<void(output_stack& os)>> _ilist;
		int stack_point;
	public:
		void add_instruction(std::function <void(output_stack& os)> op) {_ilist.push_back(op);}
		void add_instruction(float val){_ilist.push_back([val](output_stack& os){os.push(val);});}
		float exec(){output_stack s; if (_ilist.size() == 0) return 0; for (auto &fn:_ilist) {fn(s);} return s.pop();}
	};

#endif
