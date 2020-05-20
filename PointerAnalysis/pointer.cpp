#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include <bits/stdc++.h>
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CFG.h"

/*
idx - IN
idx+1 - OUT
*/
using namespace llvm;

namespace
{
	class pointer {
		private:
			std::vector<std::map<Value *, std::set<Value*>>> pointersPerInst;
			std::map<Instruction *,int> idxToInst;
			std::vector<std::set<Value *>> oldSet;
			std::set<Value *> newSet;
			int index;
			
		public:
			
			void run(Function *);
			bool performAnalysis(BasicBlock::iterator, Instruction *, BasicBlock *);
			void findValues(Value *, int, std::map<Value *, std::set<Value*>>);
			void printPointersAndPointee(int);
			void printSet(std::set<Value *>);
	};

	void pointer::printPointersAndPointee(int indx) {
		std::map<Value *, std::set<Value*>> ptMap = pointersPerInst[indx];
		for(auto it : ptMap) {
			auto itPointer = it.first;
			errs()<<itPointer->getName()<<" -> ";
			for(auto itPointee : ptMap[itPointer]) {
				errs()<<itPointee->getName()<<", ";
			}
			errs()<<"\n";
		}
	}//pointer::printPointersAndPointee

	void pointer::printSet(std::set<Value*> ptSet) {
		errs()<<"\n";
		for(auto itVal : ptSet)
			errs()<<itVal->getName()<<", ";
		errs()<<"\n";
	}//pointer::printSet
	
	/*
	* run - function to iterate through basic blocks and instructions
	* repeat until converged
	*/
	void pointer::run(Function *fp) {
		bool changed;
		BasicBlock *bp;
		Instruction *ip;
		//inserting two sets in oldSet		
		std::set<Value *> oldSet1, oldSet2;
		oldSet.push_back(oldSet1);
		oldSet.push_back(oldSet2);
		bool firstTime = true;
		int it = 1;


		do {
			index = 0;
			changed = false;
			int inst_num = 0;
			
			errs()<<"------------------------------------iteration-"<<it<<"----------------------------\n";
			for(auto bb = fp->begin(); bb != fp->end(); bb++) {
				bp = &(*bb);
				for(auto ii = bp->begin(); ii != bp->end(); ii++) {
					ip = &(*ii);

					if(firstTime) {
						std::map<Value *, std::set<Value*>> inMap, outMap;
						pointersPerInst.push_back(inMap);	//push InMap
						pointersPerInst.push_back(outMap);	//push OutMap

						idxToInst.insert(std::pair<Instruction *,int>(ip,index));
					}
					errs()<<"Instruction"<<inst_num<<"\n";
					if(performAnalysis(ii,ip,bp)) {
						changed = true;
					}

/*-------------------------------printing values---------------------------*/
					
					errs()<<"----------------------In set-------------------------\n";
					printPointersAndPointee(index*2);
					errs()<<"----------------------Out set-------------------------\n";
					printPointersAndPointee(index*2 + 1);
					index ++;
					inst_num++;

				}
			}
			if(firstTime) {
				firstTime = false;
			}
			it++;
		} while(changed);
	}//pointer::run

	/*
	* performAnalysis - calculate the IN and OUT per instruction	
	*/
	bool pointer::performAnalysis(BasicBlock::iterator ii, Instruction *ip, BasicBlock *bp) {

		bool changed = false;
		std::map<Value *, std::set<Value*>> tempIn,tempOut;
		Instruction *tip;

		/*----------------------------calculate IN---------------------------*/
		if(ii == bp->begin()) {
//errs()<<"This is bb "<<bp->getName()<<"\n";
			//first instruction
			for(BasicBlock *pred : predecessors(bp)) {
				auto tii = pred->end();
				tii--;
				tip = &(*tii);
			
				if(idxToInst.find(tip) != idxToInst.end()) {
					int idx = idxToInst[tip];
					idx = idx*2;
					auto predOut = pointersPerInst[idx+1];

/*errs()<<"Predecessors "<<pred->getName()<<"idx = "<<idx<<"\n";
printPointersAndPointee(idx+1);
errs()<<"Done\n";*/
					//iterate through the keys
					for(auto it : predOut) {
						Value *key = it.first;
					
						if(tempIn.find(key) == tempIn.end()) {
							std::set<Value *> pointees;
							tempIn.insert(std::pair<Value *, std::set<Value*>>(key,pointees));
						}

						std::set<Value *> pointee = it.second;
						for(auto itVal : pointee)
							tempIn[key].insert(itVal);
					}
				}
			}
			
		} else {
			//fetch the previous instruction
			ii--;
			tip = &(*(ii));
			int idx = idxToInst.find(tip)->second;
			idx = idx*2;
			auto predOut = pointersPerInst[idx+1];
			//iterate through the keys
			for(auto it : predOut) {
				Value *key = it.first;
					
				if(tempIn.find(key) == tempIn.end()) {
					std::set<Value *> pointees;
					tempIn.insert(std::pair<Value *, std::set<Value*>>(key,pointees));
				}

				std::set<Value *> pointee = it.second;
				for(auto itVal : pointee)
					tempIn[key].insert(itVal);
			}

		}
		/*----------------------------calculate IN over---------------------------*/


		/*----------------------------calculate OUT---------------------------*/
		tempOut = tempIn;	//copy IN into OUT (for only those elements which are live in OUTla)
		if(isa<StoreInst>(ip)) {
			//L.H.S
			if(ip->getOperand(1)->getType()->isPointerTy()) {
				if(ip->getOperand(1)->getType()->getContainedType(0)->isPointerTy()) {
					/*if(isa<Instruction>(ip->getOperand(1))) {					
						tip = (Instruction *)ip->getOperand(1);
						if(isa<GetElementPtrInst>(tip)) {
							errs()<<"Prerona in the right dir\n";
						}
					}*/
					findValues(ip->getOperand(1), 1, tempIn);
					//R.H.S
					findValues(ip->getOperand(0), 0, tempIn);

					for(auto itVal : oldSet[1]) {
						if(tempOut.find(itVal) == tempOut.end()) {
							//create an entry
							std::set<Value *> pointees;
							tempOut.insert(std::pair<Value *, std::set<Value*>>(itVal,pointees));
						}
						
						if(oldSet[1].size() == 1 && oldSet[0].size() == 1) {
							tempOut[itVal].clear();
							
						}
						for(auto itVals : oldSet[0]) {
							tempOut[itVal].insert(itVals);
						}
						
					}
				} 
			}
		} 

		/*----------------------------calculate OUT over---------------------------*/


		/*----------------------------check if tempIn and tempOut are equal---------------------------*/
		if(pointersPerInst[index*2] != tempIn || pointersPerInst[index*2+1] != tempOut) {
			changed = true;
			//copy the sets
			pointersPerInst[index*2] = tempIn;
			pointersPerInst[index*2+1] = tempOut;
		}
		/*----------------------------checking over---------------------------*/
		/*----------------------------free up---------------------------*/
		oldSet[0].clear();
		oldSet[1].clear();


		return changed;
	}//pointer::performAnalysis

	/*
	* findValues : finds out the actual variable/s it is pointing to
	*/
	void pointer::findValues(Value *op, int idx, std::map<Value *, std::set<Value*>> tempIn) {
		Instruction *ip;
		
		if(isa<GlobalVariable>(op)) {
			oldSet[idx].insert(op);
		} else if(isa<Instruction>(op)) { 
			ip= (Instruction *)(op);
			if(isa<AllocaInst>(ip)) {	//temporary variables fall in this category
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
						} else if(isa<LoadInst>(ip)) {//pointer arithmetic not valid, hence not considering other instructions (for pointer arithmetic use gep)
							st.push(ip->getOperand(0));
						} 
					} else if(isa<GlobalVariable>(op)) {
						oldSet[idx].insert(op);
					}
					ind++;
				
				} while(!st.empty());

				//add things to the oldset according to the indirection
				while(ind > 1) {
					for(auto itVal : oldSet[idx]) {
						if(tempIn.find(itVal) != tempIn.end()) {
							for(auto it : tempIn.find(itVal)->second)
								newSet.insert(it);
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

