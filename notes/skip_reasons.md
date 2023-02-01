skip_empty_classdecl: skips class declarations without a body

insufficient_access: element is private private or protected

constructor_missing_class: skips constructors which don't belong to a "normal" class/struct

ostream_blacklist: skips if arguments contain ostreams as they can't be copied which messes with cxxwrap

istream_blacklist: skips if arguments contain istreams as they can't be copied which messes with cxxwrap

rvalue_unsupported: skips if arguments contain rvalue references as they aren't supported by cxxwrap

unique_ptr_blacklist: skips if arguments contain a unique_pointer as they aren't supported by cxxwrap

default_constructor: skips if the contructor is the default constructor (no arguments) because cxxwrap automatically generates it

deleted_method: skips deleted methods (`func(int i) = delete;`)

operator_unsupported: skips if this method is overloading an operator 

getimpl_blacklist: skips functions named "getImpl" or "getPImpl" as those return incomplete classes in poplar libraries which are unsupported in cxxwrap

calls_deleted_function: skips functions which attempt to call deleted functions (currently hardcoded)

unsupported_template: skips functions with templated arguments that aren't of type ArrayRef<T>

skip_compiler_definitions: skips compiler definitions

header_blacklisted: header has been explicitly blacklisted

not_allowed_namespace: namespace of node isn't in the whitelist

fieldata_size_blacklist: workaround to a specific function (poplar::FieldData::SizeT::size) being defined the same way twice(?)

expr_blacklisted: explicitly blacklist poplar expressions due to them using unsupported c++ features

equivalent_device_type_blacklist: explicitly blacklist poplar `equivalent_device_type` as it's using unsupported c++ features 

getdevices_blacklist: explicitly blacklists the `getDevices` function as it returns a vector of incomplete classes