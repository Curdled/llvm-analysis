//===- NewGVN.h - Global Value Numbering Pass -------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
/// \file
/// This file provides the interface for LLVM's Global Value Numbering pass.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_SCALAR_NEWGVN_H
#define LLVM_TRANSFORMS_SCALAR_NEWGVN_H

#include "llvm/IR/PassManager.h"
#include "llvm/IR/Dominators.h"
 

namespace llvm {

class Function;
class BasicBlock;

class DominatorTree;
class AssumptionCache;
class TargetLibraryInfo;
class MemorySSA;
class AAResults;
class DataLayout;
// template<class T>
// class DomTreeNodeBas?e<T>;
// template<>
// class DomTreeNodeBase<BasicBlock, false>;
// class DomTreeNode;

class NewGVNPass : public PassInfoMixin<NewGVNPass> {
public:
  /// Run the pass over the function.
  PreservedAnalyses run(Function &F, AnalysisManager<Function> &AM);
};

struct GVNEXtractedData {
  using ClassID = unsigned int;

  using HandleTopClassT = std::function<void(Function *, ClassID)>;
  using HandleClassAssignmentT = std::function<void(Function *, ClassID, Instruction *, DomTreeNode *)>;
  using HandleDeadInstructionT = std::function<void(Instruction *)>;
  using HandleInstructionLeaderT = std::function<void(ClassID, Instruction*, unsigned)>;
  using HandleValueLeaderT = std::function<void(ClassID, Value*, unsigned)>;


  GVNEXtractedData(HandleTopClassT tc, HandleClassAssignmentT ca, HandleDeadInstructionT di, HandleInstructionLeaderT il, HandleValueLeaderT vl) 
    : handleTopClass(tc), handleClassAssignment(ca), handleDeadInstruction(di), handleInstructionLeader(il),  handleValueLeader(vl) {}


  HandleTopClassT handleTopClass;
  HandleClassAssignmentT handleClassAssignment;
  HandleDeadInstructionT handleDeadInstruction;
  HandleInstructionLeaderT handleInstructionLeader;
  HandleValueLeaderT handleValueLeader;
};

class NewGVNExtractor {
  public:
    NewGVNExtractor(std::unique_ptr<GVNEXtractedData>);
    void extract(Function &F, DominatorTree *DT, AssumptionCache *AC,
         TargetLibraryInfo *TLI, llvm::AAResults *AA, MemorySSA *MSSA,
         const DataLayout &DL);

  private: 
    std::unique_ptr<GVNEXtractedData> extractor;
};


} // end namespace llvm

#endif // LLVM_TRANSFORMS_SCALAR_NEWGVN_H

