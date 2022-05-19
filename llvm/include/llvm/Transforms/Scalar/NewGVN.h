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


namespace llvm {

class Function;
class DominatorTree;
class AssumptionCache;
class TargetLibraryInfo;
class MemorySSA;
class AAResults;
class DataLayout;

class NewGVNPass : public PassInfoMixin<NewGVNPass> {
public:
  /// Run the pass over the function.
  PreservedAnalyses run(Function &F, AnalysisManager<Function> &AM);
};


class NewGVNExtractor {
  public:
    std::unique_ptr<std::vector<std::vector<Instruction *>>> extract(Function &F, DominatorTree *DT, AssumptionCache *AC,
         TargetLibraryInfo *TLI, llvm::AAResults *AA, MemorySSA *MSSA,
         const DataLayout &DL);
};

} // end namespace llvm

#endif // LLVM_TRANSFORMS_SCALAR_NEWGVN_H

