problem: libpoplar which is needed to interface with ipus (setup data-flow, upload codelets to ipu, ...) only offers a c++ api

projects offering binding to c++ code: Cxx.jl and CxxWrap.jl 

Cxx.jl:

* write c++ code inside of julia code
* can directly call into c++ libraries and pass values from julia
+ \+ easy to use
+ \+ doesn't need any additional setup
+ \+ allows more complex c++ snippets
- \- (big one) does not work on current julia
- \- passing values from julia to c++ can be annoying
- \- requires users to write c++ code themselves, no longer pure julia code

CxxWrap.jl: 

* bindings are defined from c++ code and compiled to shared library to be loaded by julia
* on julia side everything is pure julia
* \+ no c++ knowledge by endusers required
+ \+ clean interface for programmers
+ \+ comes with integration for various standard c++ data types
- \- every function/constant needs to be manually defined on c++ side
- \- on changes on the c++ side a (potentially huge) library needs to be recompiled
- \- a lot of modern c++ features do not integrate well

Updating cxx.jl would a lot of effort (other people have tried and failed and julia has substantially changed since the last version of cxx.jl released)

CxxWrap approach needs bindings  
Manually crafting all bindings would be both a lot of effort (lots of functions)  
~~handcrafted boring~~  
much more likely to break on updates
- Want to automatically generate c++ side of bindings  
- need (libpoplar specific) way to parse c++ headers and generate c++ bindings for them

approach: use Clang.jl (julia libclang) to parse c++ headers  (similar: https://github.com/TakekazuKATO/OpenCV.jl/blob/master/generateWrapper.jl)

process: 

- Resolve header locations of all the headers which are supposed to get parsed
- parse headers with libclang (clang.jl for julia bindings)
- iterate over the clang abstract syntax tree 
- filter out all members which dont belong to poplib namespaces
- generate the cxxwrap c++ code needed to define the binding for relevant member types (class decl, function decl, enum decl, inheritance, ...) (that's the big part)
- compile generated code (templated into handcrafted template.cpp) to shared library (to be loaded by cxxwrap) 
- shared library loadable through cxxwrap library
- small additions in handcrafted julia code (nicer ipu management)

problems/hacks:

c++ is big complex language with loads of features which aren't directly supported by cxxwrap which means a lot of functions can't be directly wrapped direcltly with cxxwrap -> generate lambdas instead of passing function directly into cxxwrap

poplar array and string types are different from julia arrays, need to be automatically converted -> convert poplar array types from and to julia arrays automatically

optional parameters aren't directly supported by cxxwrap -> generate multiple function definitions (for all possible combinations of existing/not existing optional parameters)

virtual classes(?) can't be dealocated by cxxwrap properly -> (bad) auto-applied hotfix of cxxwrap to disable calling the dealocator on those types

