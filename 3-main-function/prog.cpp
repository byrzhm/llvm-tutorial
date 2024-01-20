#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

class SimpleLLVM {
public:
  SimpleLLVM() { moduleInit(); }

  void exec(const std::string &program) {
    // 1. Parse the program
    // auto ast = parser->parse(program);

    // 2. Compile to LLVM IR
    // compile(ast);
    compile();

    module->print(llvm::outs(), nullptr);

    // 3. Save module IR to file
    saveModuleToFile("./output.ll");
  }

private:
  void moduleInit() {
    ctx = std::make_unique<llvm::LLVMContext>();
    module = std::make_unique<llvm::Module>("test", *ctx);
    builder = std::make_unique<llvm::IRBuilder<>>(*ctx);
  }

  void saveModuleToFile(const std::string &filename) {
    std::error_code ec;
    llvm::raw_fd_ostream out(filename, ec);
    module->print(out, nullptr);
  }

  void compile(/* TODO: ast */) {
    // 1. Create a function signature
    fn = createFunction("main",
                        llvm::FunctionType::get(builder->getInt32Ty(), false));

    // 2. Compile main function body
    auto result = gen(/* ast */);

    // 3. Cast to i32 to return from main
    auto i32Result =
        builder->CreateIntCast(result, builder->getInt32Ty(), true);

    builder->CreateRet(i32Result);
  }

  llvm::Value *gen(/* TODO: ast */) { return builder->getInt32(42); }

  llvm::Function *createFunction(const std::string &fnName,
                                 llvm::FunctionType *fnType) {
    auto fn = module->getFunction(fnName);
    if (fn == nullptr) {
      fn = createFunctionPrototype(fnName, fnType);
    }

    createFunctionBlock(fn);
    return fn;
  }

  llvm::Function *createFunctionPrototype(const std::string &fnName,
                                          llvm::FunctionType *fnType) {
    auto fn = llvm::Function::Create(fnType, llvm::Function::ExternalLinkage,
                                     fnName, module.get());
    verifyFunction(*fn);
    return fn;
  }

  void createFunctionBlock(llvm::Function *fn) {
    auto entry = createBasicBlock("entry", fn);
    builder->SetInsertPoint(entry);
  }

  /**
   * Create a basic block. If the `fn` is passed, the block is automatically
   * inserted into the function. Otherwise, the basic block should later be
   * inserted into the function manually, via
   * fn->getBasicBlockList().push_back(block).
   */
  llvm::BasicBlock *createBasicBlock(const std::string &name,
                                     llvm::Function *fn = nullptr) {
    return llvm::BasicBlock::Create(*ctx, name, fn);
  }

  llvm::Function *fn;

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