#include "jlcxx/jlcxx.hpp"
#include "jlcxx/stl.hpp"
#include <iostream>
#include <functional>
#include <cstdio>
#include <vector>

#include <poplar/DeviceManager.hpp>
#include <poplar/Device.hpp>
#include <poplar/Engine.hpp>
#include <poplar/Graph.hpp>
#include <poplar/ArrayRef.hpp>
#include <poplar/StringRef.hpp>
#include <poplar/IPUModel.hpp>


#include <popops/ElementWise.hpp>
#include <popops/codelets.hpp>

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


Device getRealIPU() {
	  DeviceManager manager = DeviceManager::createDeviceManager();

  Device device;
  bool success = false;
  // Loop over all single IPU devices on the host
  // Break the loop when an IPU is successfully acquired
  for (auto &hwDevice : manager.getDevices(poplar::TargetType::IPU, 1)) {
    device = std::move(hwDevice);
    std::cerr << "Trying to attach to IPU " << device.getId() << std::endl;
    if ((success = device.attach())) {
      std::cerr << "Attached to IPU " << device.getId() << std::endl;
      break;
    }
  }
  if (!success) {
    std::cerr << "Error attaching to device" << std::endl;
  }

  return std::move(device);	
}

namespace jlcxx {
  #include"gen_inherit.txt"
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

  mod.add_type<StringRef>("StringRef");

  mod.add_type<poplar::ProgressFunc>("ProgressFunc");

  

  // auto JLType = mod.add_type<poplar::Type>("Type");
  // Errors! ^ Can't be named "Type"
  #include"gen_inline.txt"

  mod.set_const("BOOL", BOOL);
  mod.set_const("CHAR", CHAR);
  mod.set_const("UNSIGNED_CHAR", UNSIGNED_CHAR);
  mod.set_const("SIGNED_CHAR", SIGNED_CHAR);
  mod.set_const("UNSIGNED_SHORT", UNSIGNED_SHORT);
  mod.set_const("SHORT", SHORT);
  mod.set_const("UNSIGNED_INT", UNSIGNED_INT);
  mod.set_const("INT", INT);
  mod.set_const("UNSIGNED_LONG", UNSIGNED_LONG);
  mod.set_const("LONG", LONG);
  mod.set_const("UNSIGNED_LONGLONG", UNSIGNED_LONGLONG);
  mod.set_const("LONGLONG", LONGLONG);
  mod.set_const("HALF", HALF);
  mod.set_const("FLOAT", FLOAT);


  // TODO: automate getindex
  JLVertexRef.module().set_override_module(jl_base_module);
  JLVertexRef.method("getindex", [](const VertexRef& v, std::string i) {return v[i];});
  JLVertexRef.module().unset_override_module();

  JLTensor.module().set_override_module(jl_base_module);
  JLTensor.method("getindex", [](const Tensor& v, std::size_t i) {return v[i];});
  JLTensor.module().unset_override_module();

  mod.method("getRealIPU", getRealIPU);

  // Workaround: cxxwrap single inheritance doesn't seem to work for constructors??
  JLEngine.constructor<const poplar::Graph &, poplar::program::Sequence>();
  JLEngine.constructor<const poplar::Graph &, poplar::program::Sequence, poplar::OptionFlags>();

}
