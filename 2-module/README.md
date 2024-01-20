```bash
llvm-config --cxxflags
# -I/usr/lib/llvm-14/include -std=c++14   -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS

clang++ -o prog `llvm-config --cxxflags -ldflags --system-libs --libs core` main.cpp
```