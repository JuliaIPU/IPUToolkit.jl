#include "jlcxx/jlcxx.hpp"
#include "jlcxx/stl.hpp"
#include <iostream>
#include <functional>
#include <cstdio>
#include <vector>

#include <poplar/Graph.hpp>
#include <poplar/ArrayRef.hpp>
#include <poplar/StringRef.hpp>

#include "gen_headers.hpp"

using namespace poplar;

template <>
struct jlcxx::IsMirroredType<poplar::VariableRef> : std::false_type
{
};

template <>
struct jlcxx::IsMirroredType<poplar::TypeTraits> : std::false_type
{
};

template <>
struct jlcxx::IsMirroredType<poplar::ProfileValue::Storage> : std::false_type
{
};
template <>
struct jlcxx::IsMirroredType<poplar::VertexEdgeInfo::StorageInfo> : std::false_type
{
};

template <>
struct jlcxx::IsMirroredType<poplar::FieldData::SizeT> : std::false_type
{
};

template <typename T>
jlcxx::ArrayRef<T, 1> poplarToJlcxx(poplar::ArrayRef<T> arr)
{
  return jlcxx::ArrayRef<T, 1>((T *)arr.data(), (std::size_t)arr.size());
}

template <typename T>
poplar::ArrayRef<T> jlcxxToPoplar(jlcxx::ArrayRef<T> arr)
{
  return poplar::ArrayRef<T>(arr.data(), arr.size());
}

namespace jlcxx {
  #include "gen_inherit.cpp"
  //template<> struct SuperType<poplar::program::Execute> { typedef poplar::program::Program type; };
}

JLCXX_MODULE
define_julia_module(jlcxx::Module &mod)
{


  // mod.add_type<poplar::VariableInterval>("VariableInterval");
  // Workaround!
  // This is suppposed to auto-generate but for some reason doesn't do so until it's already being used


  mod.add_type<ArrayRef<std::string>>("ArrayRefString");
  mod.add_type<ArrayRef<std::size_t>>("ArrayRefSizeT");
  mod.add_type<ArrayRef<GlobalExchangeConstraint>>("ArrayRefGlobalExchangeConstraint");
  mod.add_type<ArrayRef<program::Program>>("ArrayRefProgram");
  mod.add_type<ArrayRef<poplar::GlobalExchangeFlow>>("ArrayRefGlobalExchangeFlow");

  mod.add_type<ArrayRef<poplar::Graph::ConnectionDesc>>("ArrayRefGraphConnectionDesc");
  mod.add_type<ArrayRef<poplar::Tensor>>("ArrayRefTensor");
  mod.add_type<ArrayRef<uint16_t>>("ArrayRefU16");
  mod.add_type<ArrayRef<poplar::Tensor *>>("ArrayRefTensorPtr");
  mod.add_type<std::map<std::string, std::string>>("MapStringString");
  mod.add_type<std::map<std::string, ProfileValue>>("MapStringProfileValue");
  mod.add_type<std::map<unsigned int, unsigned int>>("MapUintUint");
  mod.add_type<std::stringstream>("StringStream");
  mod.add_type<poplar::Interval>("Interval");
  //mod.add_bits<poplar::layout::Vector>("LayoutVector", jlcxx::julia_type("CppEnum"));

  mod.add_type<ArrayRef<poplar::Interval>>("ArrayRefInterval");
  mod.add_type<ArrayRef<unsigned int>>("ArrayRefUnsignedInt");

  mod.add_type<std::pair<std::int32_t, poplar::program::Program>>("PairIntProgram");

  mod.add_type<poplar::ProgressFunc>("ProgressFunc");

  // Work around for errors like
  //    C++ exception while wrapping module Poplar: No appropriate factory for type N6poplar8ArrayRefISt5tupleIJNS_4TypeEmEEEE
  // To demangle it, use `c++filt _ZN6poplar8ArrayRefISt5tupleIJNS_4TypeEmEEEE`.
  mod.add_type<ArrayRef<std::tuple<poplar::Type, unsigned long> >>("ArrayRefTupleTypeULong");
#if __has_include(<poplar/PerfEstimateFunc.hpp>) // Poplar 2.0+
  mod.add_type<std::function<poplar::VertexPerfEstimate (poplar::VertexIntrospector const&, poplar::Target const&)>>("PerfEstimateFunc");
#endif // poplar/PerfEstimateFunc.hpp
#if __has_include(<gccs/ArrayRef.hpp>) // Poplar 2.6+
  // In newer versions of Poplar SDK `ArrayRef` is a deprecated version of `gccs::ArrayRef`,
  // we need to think about how to support this in a decent way avoiding duplication.
  mod.add_type<gccs::ArrayRef<unsigned int>>("GccsArrayRefUnsignedInt");
  mod.add_type<gccs::ArrayRef<int>>("GccsArrayRefInt");
  mod.add_type<gccs::ArrayRef<long>>("GccsArrayRefLong");
  mod.add_type<gccs::ArrayRef<float>>("GccsArrayRefFloat");
  mod.add_type<gccs::ArrayRef<double>>("GccsArrayRefDouble");
#endif // gccs/ArrayRef.hpp
#if __has_include(<poplar/Quarter.hpp>) // Poplar 2.6+
  // We're skipping the `QuarterMetadata` class completely in `build.jl`, but somehow a
  // constructor of this class slips in the wrapper, so we need to add the type here to
  // avoid the error about missing appropriate factory when precompiling the package.
  mod.add_type<poplar::QuarterMetadata>("QuarterMetadata");
#endif // poplar/Quarter.hpp

  // auto JLType = mod.add_type<poplar::Type>("Type");
  // Errors! ^ Can't be named "Type"
  #include "gen_inline.cpp"

  // Contrary to what you may expect, these numerical types (`BOOL`, `INT`, `FLOAT`, etc.)
  // aren't static enums which could be defined with, e.g.
  //    mod.set_const("BOOL", BOOL);
  // Instead, they are dynamic pointers which have to be referenced at runtime: if we
  // serialised them when compiling the Julia package, those pointers would be garbage.
  mod.method("BOOL", [&] () -> poplar::Type { return BOOL; });
  mod.method("CHAR", [&] () -> poplar::Type { return CHAR; });
  mod.method("UNSIGNED_CHAR", [&] () -> poplar::Type { return UNSIGNED_CHAR; });
  mod.method("SIGNED_CHAR", [&] () -> poplar::Type { return SIGNED_CHAR; });
  mod.method("UNSIGNED_SHORT", [&] () -> poplar::Type { return UNSIGNED_SHORT; });
  mod.method("SHORT", [&] () -> poplar::Type { return SHORT; });
  mod.method("UNSIGNED_INT", [&] () -> poplar::Type { return UNSIGNED_INT; });
  mod.method("INT", [&] () -> poplar::Type { return INT; });
  mod.method("UNSIGNED_LONG", [&] () -> poplar::Type { return UNSIGNED_LONG; });
  mod.method("LONG", [&] () -> poplar::Type { return LONG; });
  mod.method("UNSIGNED_LONGLONG", [&] () -> poplar::Type { return UNSIGNED_LONGLONG; });
  mod.method("LONGLONG", [&] () -> poplar::Type { return LONGLONG; });
  mod.method("HALF", [&] () -> poplar::Type { return HALF; });
  mod.method("FLOAT", [&] () -> poplar::Type { return FLOAT; });

  mod.method("getVersionString", [] () -> std::string { return std::string(poplar::versionString()); });

  // TODO: automate getindex
  JLVertexRef.module().set_override_module(jl_base_module);
  JLVertexRef.method("getindex", [](const VertexRef& v, std::string i) {return v[i];});
  JLVertexRef.module().unset_override_module();

  JLTensor.module().set_override_module(jl_base_module);
  JLTensor.method("getindex", [](const Tensor& v, std::size_t i) {return v[i];});
  JLTensor.module().unset_override_module();

  // Workaround: cxxwrap single inheritance doesn't seem to work for constructors??
  JLEngine.constructor<const poplar::Graph &, poplar::program::Sequence>();
  JLEngine.constructor<const poplar::Graph &, poplar::program::Sequence, poplar::OptionFlags>();

}
