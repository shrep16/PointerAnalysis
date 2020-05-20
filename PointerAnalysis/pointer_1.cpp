#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include <bits/stdc++.h>
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CFG.h"


using namespace llvm;

namespace
{
	class pointer {
		private:
			std::map<BasicBlock *, std::map<Value *, std::set<Value*>>> pointersPerBB;
			std::vector<std::set<Value *>> oldSet;
			std::set<Value *> newSet;
			bool firstTime;
		public:
			//void analyse(Function *);
			void run(Function *);
			bool performAnalysis(BasicBlock *);
			void findValues(Value *, int, BasicBlock *);
	};

	/*void pointer::analyse(Function *fp) {
		BasicBlock *bp;
		Instruction *ip;
		for(auto bb = fp->begin(); bb != fp->end(); bb++) {
			bp = &(*bb);
			errs()<<"Basic block "<<bp->getName()<<"\n";
			for(auto ii = bp->begin(); ii != bp->end(); ii++) {
				ip = &(*ii);
				if(isa<StoreInst>(ip)) {
					errs()<<ip->getOperand(1)->getName()<<" = "<<ip->getOperand(0)->getName()<<"\n";
					/*//*/RHS
					if(ip->getOperand(0)->getType()->getContainedType(0)->isPointerTy())
						errs()<<"pointer -"<<ip->getOperand(0)->getName()<<"\n";
					//LHS
					if(ip->getOperand(1)->getType()->getContainedType(0)->isPointerTy())
						errs()<<"pointer -"<<ip->getOperand(1)->getName()<<"\n";*/

					/*if(ip->getOperand(1)->getType()->isPointerTy())
						if(ip->getOperand(1)->getType()->getContainedType(0)->isPointerTy())
							errs()<<"pointers type-"<<ip->getOperand(1)->getName()<<"\n";

					if(ip->getOperand(0)->getType()->isPointerTy())
						if(ip->getOperand(0)->getType()->getContainedType(0)->isPointerTy())
							errs()<<"pointer type-"<<ip->getOperand(0)->getName()<<"\n";
					
				}
			}
			
		}
	}//pointer::analyse*/

	/*
	* run - function to iterate through basic blocks
	* repeat until converged
	*/
	void pointer::run(Function *fp) {
		bool changed;
		BasicBlock *bp;
		//inserting two sets in oldSet		
		std::set<Value *> oldSet1, oldSet2;
		oldSet.push_back(oldSet1);
		oldSet.push_back(oldSet2);
		
		do {
			changed = false;
			if(firstTime)
				firstTime = false;
			for(auto bb = fp->begin(); bb != fp->end(); bb++) {
				bp = &(*bb);
				if(performAnalysis(bp)) {
					changed = true;
				}
			}
		} while(changed);
	}//pointer::run

	bool pointer::performAnalysis(BasicBlock *bp) {
		Instruction *ip;
		bool changed = false;
		std::set<Value *> curSet;
		for(auto ii = bp->begin(); ii != bp->end(); ii++) {
			ip = &(*ii);
			if(isa<StoreInst>(ip)) {

				//L.H.S
				if(ip->getOperand(1)->getType()->isPointerTy()) {
					if(ip->getOperand(1)->getType()->getContainedType(0)->isPointerTy()) {

						if(pointersPerBB.find(bp) == pointersPerBB.end()) {
							//make entry 
							std::map<Value *, std::set<Value *>> bbEntry;
							pointersPerBB.insert(std::pair<BasicBlock *, std::map<Value *, std::set<Value *>>>(bp, bbEntry));
						}

						findValues(ip->getOperand(1),1,bp);
						
						//R.H.S
						findValues(ip->getOperand(0),0,bp);
						
						//append the values to LHS
						for(auto itVal : oldSet[1]) {
							std::map<Value *, std::set<Value*>> pSet = pointersPerBB.find(bp)->second;
							if(pSet.find(itVal) != pSet.end())
								curSet = pointersPerBB.find(bp)->second.find(itVal)->second;
							/*else {
								
								curSet = NULL;
							}*/
								

							if(curSet.empty()) {
								changed = true;
								std::set<Value *> tempSet;

								for (auto cpVal : oldSet[0])
									tempSet.insert(cpVal);

								pointersPerBB.find(bp)->second.insert(std::pair<Value *, std::set<Value *>>(itVal, tempSet));
							}else if(oldSet[0] != curSet) {//check whether elements getting inserted to the right place
								changed = true;
								if(oldSet[1].size()>1) {
									for(auto cpVal : oldSet[0])
										curSet.insert(cpVal);
									
								} else {
									curSet = oldSet[0]; //copy the set as it is
								}
							}  
						}

					}

					//erase oldSet values;
					oldSet[1].clear();
					oldSet[0].clear();
				}

				
			}
		}
		return changed;
	}//pointer::performAnalysis


	void pointer::findValues(Value *op, int idx, BasicBlock *bp) {
		Instruction *ip;
		
		if(isa<GlobalVariable>(op)) {
			oldSet[idx].insert(op);
		} else if(isa<Instruction>(op)) {
			ip= (Instruction *)(op);
			if(isa<AllocaInst>(ip)) {
				oldSet[idx].insert(op);
			} else {
				//find level of indirection
				int ind = 0;
				std::stack<Value *> st;
				st.push(op);
				do {
					op = st.top();
					st.pop();
					if(isa<Instruction>(op)) {
						ip= (Instruction *)(op);
						if(isa<AllocaInst>(ip)) {
							//stack should also be empty
							oldSet[idx].insert(op);
						} else if(isa<LoadInst>(ip)) {
							st.push(ip->getOperand(1));
						}
					} else if(isa<GlobalVariable>(op)) {
						oldSet[idx].insert(op);
					}
					ind++;
				
				} while(!st.empty());

				//add things to the oldset according to the indirection
				while(ind > 0) {
					for(auto itVal : oldSet[idx]) {
						
						auto opMap = pointersPerBB.find(bp)->second;
						if(opMap.find(op) != opMap.end() && firstTime) {//check the validity
							for(auto it : opMap.find(op)->second)
								newSet.insert(it);
						} else {
							for(BasicBlock *pred : predecessors(bp)) {
								opMap = pointersPerBB.find(pred)->second;
								if(opMap.find(op) != opMap.end()) {
									for(auto it : opMap.find(op)->second)
										newSet.insert(it);
								}
							}
						}					
					}

					ind--;
					oldSet[idx] = newSet; //copy
					newSet.clear();
				}
			}
		}
	}//pointer::findValues

	class pointerAnalysis:public FunctionPass
	{
		public:
			static char ID;
			pointerAnalysis():FunctionPass(ID){}

			bool runOnFunction(Function &F) override{
				pointer obj;
				obj.run(&F);
				return false;
			}
	};
}//end namespace


char pointerAnalysis::ID = 0;
static RegisterPass<pointerAnalysis> X("pointer","Pointer analysis pass", false, false); 

