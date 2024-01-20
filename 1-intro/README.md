## tools

clang++\
llc: llvm compiler\
lli: llvm interpreter\
llvm-as: llvm assembler\
llvm-dis: llvm disassembler

如果使用其它版本则需要在后面加上版本号，如clang++-17

---

```bash
clang++ -S -emit-llvm test.cpp
clang++ -o test test.cpp

# lli 解释执行 .ll 文件
# lli test.ll <-> clang++ -o test test.cpp && ./test

llvm-as test.ll # generate LLVM bitcode
llvm-dis test.bc -o test-2.ll

clang++ -S test.ll # llc test.ll
```