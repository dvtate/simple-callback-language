//
// Created by tate on 22-05-20.
//
#include <iostream>

#include "exec_bc_instr.hpp"
#include "vm.hpp"
#include "operators.hpp"

static void invoke(Frame& f) {
	Value v = f.eval_stack.back();
	f.eval_stack.pop_back();
	auto t = v.getType();
	if (t == Value::VType::REF) {
		Value* p = std::get<Handle<Value>>(v.v).ptr;
		if (!p) {
			std::cout <<"Cant invoke null reference...\n";
			return; // TODO: type-error, null-pointer, etc.
		}
		v = Value(*p);
	}

}


void exec_bc_instr(Frame& f, BCInstr cmd) {
	switch (cmd.instr) {
		// push id ref onto stack
		case BCInstr::OPCode::USE_ID:
			f.eval_stack.emplace_back(
					f.closure.vars[cmd.i]);
			return;

		// builtin operator
		case BCInstr::OPCode::BUILTIN_OP:
			builtin_operators[cmd.i].act(f);
			return;

		// primitive numeric lits
		case BCInstr::OPCode::I64_LIT:
			f.eval_stack.emplace_back(cmd.i);
			return;
		case BCInstr::OPCode::F64_LIT:
			f.eval_stack.emplace_back(cmd.v);
			return;

		case BCInstr::OPCode::INVOKE:
			invoke(f);
			return;


		case BCInstr::OPCode::USE_LIT:
			const Literal& lit = f.rt->vm->literals[cmd.i];
			if (lit.type == Literal::Ltype::VAL) {
				f.eval_stack.emplace_back(std::get<Value>(lit.v));
			} else {
				const auto& cd = std::get<ClosureDef>(lit.v);

				const Closure nc();
				std::unordered_map<int64_t
				// capture lexical vars
				// TODO: this is prolly expensive
				for (auto & cid : cd.capture_ids)
					this->vars[cid] = f.closure->vars[cid];

				this->body = &cd.body;

				this->id = _uid++;

			}
	}
}