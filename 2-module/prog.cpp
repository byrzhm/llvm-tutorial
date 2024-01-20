#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

class SimpleLLVM {
public:
  SimpleLLVM() { moduleInit(); }

  void exec(const std::string &program) {
    // 1. Parse the program
    // auto ast = parser->parse(program);

    // 2. Compile to LLVM IR
    // compile(ast);

    module->print(llvm::outs(), nullptr);

    // 3. Save module IR to file
    saveModuleToFile("./output.ll");
  }

private:
  void moduleInit() {
    ctx = std::make_unique<llvm::LLVMContext>();
    module = std::make_unique<llvm::Module>("main", *ctx);
    builder = std::make_unique<llvm::IRBuilder<>>(*ctx);
  }

  void saveModuleToFile(const std::string &filename) {
    std::error_code ec;
    llvm::raw_fd_ostream out(filename, ec);
    module->print(out, nullptr);
  }

  /**
   * Global LLVM context.
   * It owns and manages the core "global" data of LLVM's core infrastructure,
   * including the type and constant uniquing tables.
   */
  std::unique_ptr<llvm::LLVMContext> ctx;

  /**
   * A module instance is used to store all the information related to an
   * LLVM module. Modules are the top level container of all other LLVM
   * Intermediate Representation (IR) objects. Each module directly contains a
   * list of globals variables, a list of functions, a list of libraries (or
   * other modules) this module depends on, a symbol table, and various data
   * about the target's characteristics.
   *
   * A module maintains a GlobalList object that is used to hold all constant
   * references to GlobalValue objects that reside in the module. When a
   * global variable is destroyed, it should have no entries in the GlobalList.
   * The main container class for the LLVM Intermediate Representation.
   */
  std::unique_ptr<llvm::Module> module;

  /**
   * The IRBuilder class simplifies the process of building LLVM instructions.
   */
  std::unique_ptr<llvm::IRBuilder<>> builder;
};

int main() {
  SimpleLLVM llvm;
  llvm.exec("42");
  return 0;
}