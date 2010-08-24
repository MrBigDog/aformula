/*
  Copyright (C) 2010  Charles Pence <charles@charlespence.net>
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/// @file llvmformula.h
/// @brief Definition of the @c LLVMFormula class.

#ifndef LLVMFORMULA_H__
#define LLVMFORMULA_H__

#include "jitformula.h"
#include "codegenerator.h"

// Forward declarations for LLVM
namespace llvm
{
class Module;
class ModuleProvider;
class FunctionPassManager;
class ExecutionEngine;
class Constant;
};

// Can't forward-declare this one, it's a template
#include <llvm/Support/IRBuilder.h>


namespace AFormula
{

namespace Private
{

/// @brief LLVM formula-compiling backend.
///
/// This backend uses the LLVM library to compile our parsed expressions
/// into machine code.
class LLVMFormula : public JITFormula, public CodeGenerator
{
public:
	/// @brief Constructor.
	///
	/// The constructor creates all of the LLVM context necessary to
	/// compile formulas.
	LLVMFormula ();

	/// @brief Destructor.
	virtual ~LLVMFormula ();

	virtual void *emit (NumberExprAST *);
	virtual void *emit (VariableExprAST *);
	virtual void *emit (UnaryMinusExprAST *);
	virtual void *emit (BinaryExprAST *);
	virtual void *emit (CallExprAST *);
	
protected:
	virtual bool buildFunction ();

private:
	/// @brief High-level container for all LLVM objects.
	llvm::Module *module;
	/// @brief Pointer to an @c llvm::ExistingModuleProvider bound to @c module.
 	llvm::ModuleProvider *MP;
	/// @brief Builder which is responsible for code insertion.
	llvm::IRBuilder<> *builder;
	/// @brief Function-level optimization manager.
	llvm::FunctionPassManager *FPM;
	/// @brief Engine which converts LLVM IR into machine code.
	llvm::ExecutionEngine *engine;

	/// @brief Get an LLVM GlobalVariable which shadows the given double
	/// pointer.
	llvm::Constant *getGlobalVariableFor (double *ptr);
};

};
};

#endif /* LLVMFORMULA_H__ */

// Local Variables:
// mode: c++
// End:
