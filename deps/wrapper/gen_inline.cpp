// poplar::layout::Vector__EnumDecl
mod.add_bits<poplar::layout::Vector>("LayoutVector", jlcxx::julia_type("CppEnum"));
// poplar::layout::VectorList__EnumDecl
mod.add_bits<poplar::layout::VectorList>("LayoutVectorList", jlcxx::julia_type("CppEnum"));
// std::string__StructDecl
auto JLStringRef = mod.add_type<poplar::StringRef>("StringRef");
// poplar::OptionFlags__ClassDecl
auto JLOptionFlags = mod.add_type<poplar::OptionFlags>("OptionFlags");
// poplar::OptionFlags::iterator__ClassDecl
auto JLOptionFlagsiterator = mod.add_type<poplar::OptionFlags::iterator>("OptionFlagsiterator");
// poplar::GlobalExchangeFlow__StructDecl
auto JLGlobalExchangeFlow = mod.add_type<poplar::GlobalExchangeFlow>("GlobalExchangeFlow");
// poplar::GlobalExchangeConstraint__StructDecl
auto JLGlobalExchangeConstraint = mod.add_type<poplar::GlobalExchangeConstraint>("GlobalExchangeConstraint");
// poplar::IpuLinkConfiguration__EnumDecl
mod.add_bits<poplar::IpuLinkConfiguration>("PoplarIpuLinkConfiguration", jlcxx::julia_type("CppEnum"));
// poplar::IpuLinkTopology__EnumDecl
mod.add_bits<poplar::IpuLinkTopology>("PoplarIpuLinkTopology", jlcxx::julia_type("CppEnum"));
// poplar::TargetType__EnumDecl
mod.add_bits<poplar::TargetType>("PoplarTargetType", jlcxx::julia_type("CppEnum"));
// poplar::Type__ClassDecl
auto JLType = mod.add_type<poplar::Type>("Type_");
// poplar::Target__ClassDecl
auto JLTarget = mod.add_type<poplar::Target>("Target");
// poplar::Device__ClassDecl
auto JLDevice = mod.add_type<poplar::Device>("Device");
// poplar::DeviceManager__ClassDecl
auto JLDeviceManager = mod.add_type<poplar::DeviceManager>("DeviceManager");
// poplar::Executable__ClassDecl
auto JLExecutable = mod.add_type<poplar::Executable>("Executable");
// poplar::CodeletFileType__EnumDecl
mod.add_bits<poplar::CodeletFileType>("PoplarCodeletFileType", jlcxx::julia_type("CppEnum"));
// poplar::DataStreamType__EnumDecl
mod.add_bits<poplar::DataStreamType>("PoplarDataStreamType", jlcxx::julia_type("CppEnum"));
// poplar::ReplicatedStreamMode__EnumDecl
mod.add_bits<poplar::ReplicatedStreamMode>("PoplarReplicatedStreamMode", jlcxx::julia_type("CppEnum"));
// poplar::DataStream__ClassDecl
auto JLDataStream = mod.add_type<poplar::DataStream>("DataStream");
// poplar::RemoteBuffer__ClassDecl
auto JLRemoteBuffer = mod.add_type<poplar::RemoteBuffer>("RemoteBuffer");
// poplar::ProfileValue__ClassDecl
auto JLProfileValue = mod.add_type<poplar::ProfileValue>("ProfileValue");
// poplar::ProfileValue::Type__EnumDecl
mod.add_bits<poplar::ProfileValue::Type>("ProfileValueType", jlcxx::julia_type("CppEnum"));
// poplar::ProfileValue::Storage__StructDecl
auto JLProfileValueStorage = mod.add_type<poplar::ProfileValue::Storage>("ProfileValueStorage");
// poplar::SerializationFormat__EnumDecl
mod.add_bits<poplar::SerializationFormat>("PoplarSerializationFormat", jlcxx::julia_type("CppEnum"));
// poplar::SourceLocation__ClassDecl
auto JLSourceLocation = mod.add_type<poplar::SourceLocation>("SourceLocation");
// poplar::DebugSerializationFormat__EnumDecl
mod.add_bits<poplar::DebugSerializationFormat>("PoplarDebugSerializationFormat", jlcxx::julia_type("CppEnum"));
// poplar::DebugInfo__ClassDecl
auto JLDebugInfo = mod.add_type<poplar::DebugInfo>("DebugInfo");
// poplar::DebugNameAndId__ClassDecl
auto JLDebugNameAndId = mod.add_type<poplar::DebugNameAndId>("DebugNameAndId");
// poplar::DebugContext__ClassDecl
auto JLDebugContext = mod.add_type<poplar::DebugContext>("DebugContext");
// poplar::FunctionBufferMappingType__EnumDecl
mod.add_bits<poplar::FunctionBufferMappingType>("PoplarFunctionBufferMappingType", jlcxx::julia_type("CppEnum"));
// poplar::VertexRef__ClassDecl
auto JLVertexRef = mod.add_type<poplar::VertexRef>("VertexRef");
// poplar::FieldRef__ClassDecl
auto JLFieldRef = mod.add_type<poplar::FieldRef>("FieldRef");
// poplar::ComputeSet__ClassDecl
auto JLComputeSet = mod.add_type<poplar::ComputeSet>("ComputeSet");
// poplar::Function__ClassDecl
auto JLFunction = mod.add_type<poplar::Function>("Function");
// poplar::FunctionBuffer__ClassDecl
auto JLFunctionBuffer = mod.add_type<poplar::FunctionBuffer>("FunctionBuffer");
// poplar::HostFunction__ClassDecl
auto JLHostFunction = mod.add_type<poplar::HostFunction>("HostFunction");
// poplar::ErrorCode__EnumDecl
mod.add_bits<poplar::ErrorCode>("PoplarErrorCode", jlcxx::julia_type("CppEnum"));
// poplar::ErrorLocation__StructDecl
auto JLErrorLocation = mod.add_type<poplar::ErrorLocation>("ErrorLocation");
// poplar::poplar_error__StructDecl
auto JLPoplar_error = mod.add_type<poplar::poplar_error>("Poplar_error");
// poplar::graph_program_compilation_error__StructDecl
auto JLGraph_program_compilation_error = mod.add_type<poplar::graph_program_compilation_error>("Graph_program_compilation_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::graph_object_creation_error__StructDecl
auto JLGraph_object_creation_error = mod.add_type<poplar::graph_object_creation_error>("Graph_object_creation_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::graph_object_load_error__StructDecl
auto JLGraph_object_load_error = mod.add_type<poplar::graph_object_load_error>("Graph_object_load_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::no_environment__StructDecl
auto JLNo_environment = mod.add_type<poplar::no_environment>("No_environment", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::unknown_vertex_type__StructDecl
auto JLUnknown_vertex_type = mod.add_type<poplar::unknown_vertex_type>("Unknown_vertex_type", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::unknown_field__StructDecl
auto JLUnknown_field = mod.add_type<poplar::unknown_field>("Unknown_field", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::control_program_error__StructDecl
auto JLControl_program_error = mod.add_type<poplar::control_program_error>("Control_program_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::type_error__StructDecl
auto JLType_error = mod.add_type<poplar::type_error>("Type_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::index_error__StructDecl
auto JLIndex_error = mod.add_type<poplar::index_error>("Index_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::no_size_specified__StructDecl
auto JLNo_size_specified = mod.add_type<poplar::no_size_specified>("No_size_specified", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::graph_connection_error__StructDecl
auto JLGraph_connection_error = mod.add_type<poplar::graph_connection_error>("Graph_connection_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::graph_cycle_error__StructDecl
auto JLGraph_cycle_error = mod.add_type<poplar::graph_cycle_error>("Graph_cycle_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::graph_recursion_error__StructDecl
auto JLGraph_recursion_error = mod.add_type<poplar::graph_recursion_error>("Graph_recursion_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::graph_replication_error__StructDecl
auto JLGraph_replication_error = mod.add_type<poplar::graph_replication_error>("Graph_replication_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::profiling_disabled__StructDecl
auto JLProfiling_disabled = mod.add_type<poplar::profiling_disabled>("Profiling_disabled", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::missing_profile_data__StructDecl
auto JLMissing_profile_data = mod.add_type<poplar::missing_profile_data>("Missing_profile_data", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::missing_graph_profile__StructDecl
auto JLMissing_graph_profile = mod.add_type<poplar::missing_graph_profile>("Missing_graph_profile", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::missing_perf_estimate__StructDecl
auto JLMissing_perf_estimate = mod.add_type<poplar::missing_perf_estimate>("Missing_perf_estimate", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::invalid_tile_mapping__StructDecl
auto JLInvalid_tile_mapping = mod.add_type<poplar::invalid_tile_mapping>("Invalid_tile_mapping", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::tensor_creation_error__StructDecl
auto JLTensor_creation_error = mod.add_type<poplar::tensor_creation_error>("Tensor_creation_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::tensor_io_state_error__StructDecl
auto JLTensor_io_state_error = mod.add_type<poplar::tensor_io_state_error>("Tensor_io_state_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::tensor_metadata_error__StructDecl
auto JLTensor_metadata_error = mod.add_type<poplar::tensor_metadata_error>("Tensor_metadata_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::stream_connection_error__StructDecl
auto JLStream_connection_error = mod.add_type<poplar::stream_connection_error>("Stream_connection_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::overflow_error__StructDecl
auto JLOverflow_error = mod.add_type<poplar::overflow_error>("Overflow_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::memory_elem_constraints_error__StructDecl
auto JLMemory_elem_constraints_error = mod.add_type<poplar::memory_elem_constraints_error>("Memory_elem_constraints_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::graph_memory_allocation_error__StructDecl
auto JLGraph_memory_allocation_error = mod.add_type<poplar::graph_memory_allocation_error>("Graph_memory_allocation_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::stream_memory_allocation_error__StructDecl
auto JLStream_memory_allocation_error = mod.add_type<poplar::stream_memory_allocation_error>("Stream_memory_allocation_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::invalid_machine_model__StructDecl
auto JLInvalid_machine_model = mod.add_type<poplar::invalid_machine_model>("Invalid_machine_model", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::invalid_option__StructDecl
auto JLInvalid_option = mod.add_type<poplar::invalid_option>("Invalid_option", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::link_error__StructDecl
auto JLLink_error = mod.add_type<poplar::link_error>("Link_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::runtime_error__StructDecl
auto JLRuntime_error = mod.add_type<poplar::runtime_error>("Runtime_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::runtime_error::ErrorInfo__StructDecl
auto JLRuntime_errorErrorInfo = mod.add_type<poplar::runtime_error::ErrorInfo>("Runtime_errorErrorInfo");
// poplar::application_runtime_error__StructDecl
auto JLApplication_runtime_error = mod.add_type<poplar::application_runtime_error>("Application_runtime_error", jlcxx::julia_base_type<poplar::runtime_error>());
// poplar::system_runtime_error__StructDecl
auto JLSystem_runtime_error = mod.add_type<poplar::system_runtime_error>("System_runtime_error", jlcxx::julia_base_type<poplar::runtime_error>());
// poplar::RecoveryAction__EnumDecl
mod.add_bits<poplar::RecoveryAction>("PoplarRecoveryAction", jlcxx::julia_type("CppEnum"));
// poplar::recoverable_runtime_error__StructDecl
auto JLRecoverable_runtime_error = mod.add_type<poplar::recoverable_runtime_error>("Recoverable_runtime_error", jlcxx::julia_base_type<poplar::system_runtime_error>());
// poplar::unrecoverable_runtime_error__StructDecl
auto JLUnrecoverable_runtime_error = mod.add_type<poplar::unrecoverable_runtime_error>("Unrecoverable_runtime_error", jlcxx::julia_base_type<poplar::system_runtime_error>());
// poplar::unknown_runtime_error__StructDecl
auto JLUnknown_runtime_error = mod.add_type<poplar::unknown_runtime_error>("Unknown_runtime_error", jlcxx::julia_base_type<poplar::system_runtime_error>());
// poplar::symbol_error__StructDecl
auto JLSymbol_error = mod.add_type<poplar::symbol_error>("Symbol_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::file_load_error__StructDecl
auto JLFile_load_error = mod.add_type<poplar::file_load_error>("File_load_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::parse_error__StructDecl
auto JLParse_error = mod.add_type<poplar::parse_error>("Parse_error", jlcxx::julia_base_type<poplar::poplar_error>());
// poplar::VertexEdgeInfo__StructDecl
auto JLVertexEdgeInfo = mod.add_type<poplar::VertexEdgeInfo>("VertexEdgeInfo");
// poplar::VertexEdgeInfo::StorageInfo__StructDecl
auto JLVertexEdgeInfoStorageInfo = mod.add_type<poplar::VertexEdgeInfo::StorageInfo>("VertexEdgeInfoStorageInfo");
// poplar::VertexPerfEstimate__StructDecl
mod.map_type<poplar::VertexPerfEstimate>("VertexPerfEstimate");
// poplar::PrintTensorFmt__ClassDecl
auto JLPrintTensorFmt = mod.add_type<poplar::PrintTensorFmt>("PrintTensorFmt");
// poplar::PrintTensorFmt::FloatFormat__EnumDecl
mod.add_bits<poplar::PrintTensorFmt::FloatFormat>("PrintTensorFmtFloatFormat", jlcxx::julia_type("CppEnum"));
// poplar::SyncType__EnumDecl
mod.add_bits<poplar::SyncType>("PoplarSyncType", jlcxx::julia_type("CppEnum"));
// poplar::TypeTraits__StructDecl
auto JLTypeTraits = mod.add_type<poplar::TypeTraits>("TypeTraits");
// poplar::UpsampleMethod__EnumDecl
mod.add_bits<poplar::UpsampleMethod>("PoplarUpsampleMethod", jlcxx::julia_type("CppEnum"));
// poplar::Tensor__ClassDecl
auto JLTensor = mod.add_type<poplar::Tensor>("Tensor");
// poplar::program::Program__ClassDecl
auto JLProgramProgram = mod.add_type<poplar::program::Program>("ProgramProgram");
// poplar::program::Execute__ClassDecl
auto JLProgramExecute = mod.add_type<poplar::program::Execute>("ProgramExecute", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::Sequence__ClassDecl
auto JLProgramSequence = mod.add_type<poplar::program::Sequence>("ProgramSequence", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::Repeat__ClassDecl
auto JLProgramRepeat = mod.add_type<poplar::program::Repeat>("ProgramRepeat", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::RepeatWhileFalse__ClassDecl
auto JLProgramRepeatWhileFalse = mod.add_type<poplar::program::RepeatWhileFalse>("ProgramRepeatWhileFalse", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::RepeatWhileTrue__ClassDecl
auto JLProgramRepeatWhileTrue = mod.add_type<poplar::program::RepeatWhileTrue>("ProgramRepeatWhileTrue", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::Loop__ClassDecl
auto JLProgramLoop = mod.add_type<poplar::program::Loop>("ProgramLoop", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::If__ClassDecl
auto JLProgramIf = mod.add_type<poplar::program::If>("ProgramIf", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::Switch__ClassDecl
auto JLProgramSwitch = mod.add_type<poplar::program::Switch>("ProgramSwitch", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::Copy__ClassDecl
auto JLProgramCopy = mod.add_type<poplar::program::Copy>("ProgramCopy", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::CrossReplicaCopy__ClassDecl
auto JLProgramCrossReplicaCopy = mod.add_type<poplar::program::CrossReplicaCopy>("ProgramCrossReplicaCopy", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::WriteUndef__ClassDecl
auto JLProgramWriteUndef = mod.add_type<poplar::program::WriteUndef>("ProgramWriteUndef", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::AssumeEqualAcrossReplicas__ClassDecl
auto JLProgramAssumeEqualAcrossReplicas = mod.add_type<poplar::program::AssumeEqualAcrossReplicas>("ProgramAssumeEqualAcrossReplicas", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::Block__ClassDecl
auto JLProgramBlock = mod.add_type<poplar::program::Block>("ProgramBlock", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::Sync__ClassDecl
auto JLProgramSync = mod.add_type<poplar::program::Sync>("ProgramSync", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::Call__ClassDecl
auto JLProgramCall = mod.add_type<poplar::program::Call>("ProgramCall", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::PrintTensor__ClassDecl
auto JLProgramPrintTensor = mod.add_type<poplar::program::PrintTensor>("ProgramPrintTensor", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::ErrorProgram__ClassDecl
auto JLProgramErrorProgram = mod.add_type<poplar::program::ErrorProgram>("ProgramErrorProgram", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::Abort__ClassDecl
auto JLProgramAbort = mod.add_type<poplar::program::Abort>("ProgramAbort", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::program::AbortOnCondition__ClassDecl
auto JLProgramAbortOnCondition = mod.add_type<poplar::program::AbortOnCondition>("ProgramAbortOnCondition", jlcxx::julia_base_type<poplar::program::Program>());
// poplar::TensorCloneMethod__EnumDecl
mod.add_bits<poplar::TensorCloneMethod>("PoplarTensorCloneMethod", jlcxx::julia_type("CppEnum"));
// poplar::TensorCloneDuplicationMethod__EnumDecl
mod.add_bits<poplar::TensorCloneDuplicationMethod>("PoplarTensorCloneDuplicationMethod", jlcxx::julia_type("CppEnum"));
// poplar::TensorRearranger__ClassDecl
auto JLTensorRearranger = mod.add_type<poplar::TensorRearranger>("TensorRearranger");
// poplar::VariableMappingMethod__EnumDecl
mod.add_bits<poplar::VariableMappingMethod>("PoplarVariableMappingMethod", jlcxx::julia_type("CppEnum"));
// poplar::VariableRef__ClassDecl
auto JLVariableRef = mod.add_type<poplar::VariableRef>("VariableRef");
// poplar::VariableInterval__StructDecl
auto JLVariableInterval = mod.add_type<poplar::VariableInterval>("VariableInterval");
// poplar::FieldData__ClassDecl
auto JLFieldData = mod.add_type<poplar::FieldData>("FieldData");
// poplar::FieldData::SizeT__StructDecl
auto JLFieldDataSizeT = mod.add_type<poplar::FieldData::SizeT>("FieldDataSizeT");
// poplar::replication_factor__StructDecl
auto JLReplication_factor = mod.add_type<poplar::replication_factor>("Replication_factor");
// poplar::Graph__ClassDecl
auto JLGraph = mod.add_type<poplar::Graph>("Graph");
// poplar::Graph::ConnectionDesc__ClassDecl
auto JLGraphConnectionDesc = mod.add_type<poplar::Graph::ConnectionDesc>("GraphConnectionDesc");
// poplar::HostCallback__ClassDecl
auto JLHostCallback = mod.add_type<poplar::HostCallback>("HostCallback");
// poplar::HostCallbackHandle__ClassDecl
auto JLHostCallbackHandle = mod.add_type<poplar::HostCallbackHandle>("HostCallbackHandle");
// poplar::Module__ClassDecl
auto JLModule = mod.add_type<poplar::Module>("Module");
// poplar::RuntimeOptions__ClassDecl
auto JLRuntimeOptions = mod.add_type<poplar::RuntimeOptions>("RuntimeOptions");
// poplar::StreamCallbackBase__ClassDecl
auto JLStreamCallbackBase = mod.add_type<poplar::StreamCallbackBase>("StreamCallbackBase");
// poplar::StreamCallbackBase::Result__EnumDecl
mod.add_bits<poplar::StreamCallbackBase::Result>("StreamCallbackBaseResult", jlcxx::julia_type("CppEnum"));
// poplar::StreamCallback__ClassDecl
auto JLStreamCallback = mod.add_type<poplar::StreamCallback>("StreamCallback", jlcxx::julia_base_type<poplar::StreamCallbackBase>());
// poplar::StreamCallbackWithMetadata__ClassDecl
auto JLStreamCallbackWithMetadata = mod.add_type<poplar::StreamCallbackWithMetadata>("StreamCallbackWithMetadata", jlcxx::julia_base_type<poplar::StreamCallback>());
// poplar::ResumableStreamCallback__ClassDecl
auto JLResumableStreamCallback = mod.add_type<poplar::ResumableStreamCallback>("ResumableStreamCallback", jlcxx::julia_base_type<poplar::StreamCallback>());
// poplar::LegacyStreamCallback__ClassDecl
auto JLLegacyStreamCallback = mod.add_type<poplar::LegacyStreamCallback>("LegacyStreamCallback", jlcxx::julia_base_type<poplar::StreamCallback>());
// poplar::StreamCallbackHandle__ClassDecl
auto JLStreamCallbackHandle = mod.add_type<poplar::StreamCallbackHandle>("StreamCallbackHandle");
// poplar::Engine__ClassDecl
auto JLEngine = mod.add_type<poplar::Engine>("Engine");
// poplar::Engine::TimerTimePoint__ClassDecl
auto JLEngineTimerTimePoint = mod.add_type<poplar::Engine::TimerTimePoint>("EngineTimerTimePoint");
// poplar::FloatingPointBehaviour__StructDecl
auto JLFloatingPointBehaviour = mod.add_type<poplar::FloatingPointBehaviour>("FloatingPointBehaviour");
// poplar::IPUModel__StructDecl
auto JLIPUModel = mod.add_type<poplar::IPUModel>("IPUModel");
// poplar::IPUModel::RelativeSyncDelayType__EnumDecl
mod.add_bits<poplar::IPUModel::RelativeSyncDelayType>("IPUModelRelativeSyncDelayType", jlcxx::julia_type("CppEnum"));
// poplar::layout::Vector::NotAVector__EnumConstantDecl
mod.set_const("LayoutVectorLayoutNotAVector", poplar::layout::Vector::NotAVector);
// poplar::layout::Vector::Span__EnumConstantDecl
mod.set_const("LayoutVectorLayoutSpan", poplar::layout::Vector::Span);
// poplar::layout::Vector::ShortSpan__EnumConstantDecl
mod.set_const("LayoutVectorLayoutShortSpan", poplar::layout::Vector::ShortSpan);
// poplar::layout::Vector::OnePtr__EnumConstantDecl
mod.set_const("LayoutVectorLayoutOnePtr", poplar::layout::Vector::OnePtr);
// poplar::layout::Vector::ScaledPtr32__EnumConstantDecl
mod.set_const("LayoutVectorLayoutScaledPtr32", poplar::layout::Vector::ScaledPtr32);
// poplar::layout::Vector::ScaledPtr64__EnumConstantDecl
mod.set_const("LayoutVectorLayoutScaledPtr64", poplar::layout::Vector::ScaledPtr64);
// poplar::layout::Vector::ScaledPtr128__EnumConstantDecl
mod.set_const("LayoutVectorLayoutScaledPtr128", poplar::layout::Vector::ScaledPtr128);
// poplar::layout::to_string(const Vector)__FunctionDecl
{ using namespace poplar::layout;
mod.method("LayoutTo_String", [](const Vector a) {return poplar::layout::to_string(a);} ); }
// poplar::layout::VectorList::NotAVector__EnumConstantDecl
mod.set_const("LayoutVectorListLayoutNotAVector", poplar::layout::VectorList::NotAVector);
// poplar::layout::VectorList::OnePtr__EnumConstantDecl
mod.set_const("LayoutVectorListLayoutOnePtr", poplar::layout::VectorList::OnePtr);
// poplar::layout::VectorList::ScaledPtr32__EnumConstantDecl
mod.set_const("LayoutVectorListLayoutScaledPtr32", poplar::layout::VectorList::ScaledPtr32);
// poplar::layout::VectorList::ScaledPtr64__EnumConstantDecl
mod.set_const("LayoutVectorListLayoutScaledPtr64", poplar::layout::VectorList::ScaledPtr64);
// poplar::layout::VectorList::ScaledPtr128__EnumConstantDecl
mod.set_const("LayoutVectorListLayoutScaledPtr128", poplar::layout::VectorList::ScaledPtr128);
// poplar::layout::VectorList::DeltaN__EnumConstantDecl
mod.set_const("LayoutVectorListLayoutDeltaN", poplar::layout::VectorList::DeltaN);
// poplar::layout::VectorList::DeltaNElements__EnumConstantDecl
mod.set_const("LayoutVectorListLayoutDeltaNElements", poplar::layout::VectorList::DeltaNElements);
// poplar::layout::to_string(const VectorList)__FunctionDecl
{ using namespace poplar::layout;
mod.method("LayoutTo_String", [](const VectorList a) {return poplar::layout::to_string(a);} ); }
// std::string::StringRef(const StringRef &)__CXXConstructor
{ using namespace poplar;
JLStringRef.constructor<const StringRef &>();
}
// std::string::StringRef(const std::string &)__CXXConstructor
{ using namespace poplar;
JLStringRef.constructor<const std::string &>();
}
// std::string::StringRef(const char *, std::size_t)__CXXConstructor
{ using namespace poplar;
JLStringRef.constructor<const char *, std::size_t>();
}
// std::string::StringRef(const char *)__CXXConstructor
{ using namespace poplar;
JLStringRef.constructor<const char *>();
}
// std::string::cloneAsString()__CXXMethod
{ using namespace poplar;
JLStringRef.method("StringRefCloneAsString", [](poplar::StringRef& cl) {return cl.cloneAsString();});
}
// poplar::OptionFlags::iterator::iterator(const iterator &)__CXXConstructor
{ using namespace poplar;
JLOptionFlagsiterator.constructor<const iterator &>();
}
// poplar::OptionFlags::OptionFlags(const OptionFlags &)__CXXConstructor
{ using namespace poplar;
JLOptionFlags.constructor<const OptionFlags &>();
}
// poplar::OptionFlags::set(StringRef, StringRef)__CXXMethod
{ using namespace poplar;
JLOptionFlags.method("OptionFlagsSet", [](poplar::OptionFlags& cl, StringRef a, StringRef b) {return cl.set(a, b);});
}
// poplar::OptionFlags::at(StringRef)__CXXMethod
{ using namespace poplar;
JLOptionFlags.method("OptionFlagsAt", [](poplar::OptionFlags& cl, StringRef a) {return cl.at(a);});
}
// poplar::OptionFlags::find(const StringRef)__CXXMethod
{ using namespace poplar;
JLOptionFlags.method("OptionFlagsFind", [](poplar::OptionFlags& cl, const StringRef a) {return cl.find(a);});
}
// poplar::OptionFlags::size()__CXXMethod
{ using namespace poplar;
JLOptionFlags.method("OptionFlagsSize", [](poplar::OptionFlags& cl) {return cl.size();});
}
// poplar::OptionFlags::clear()__CXXMethod
{ using namespace poplar;
JLOptionFlags.method("OptionFlagsClear", [](poplar::OptionFlags& cl) {return cl.clear();});
}
// poplar::OptionFlags::begin()__CXXMethod
{ using namespace poplar;
JLOptionFlags.method("OptionFlagsBegin", [](poplar::OptionFlags& cl) {return cl.begin();});
}
// poplar::OptionFlags::end()__CXXMethod
{ using namespace poplar;
JLOptionFlags.method("OptionFlagsEnd", [](poplar::OptionFlags& cl) {return cl.end();});
}
// poplar::getAsProfileValue(const OptionFlags &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarGetAsProfileValue", [](const OptionFlags & a) {return poplar::getAsProfileValue(a);} ); }
// poplar::readJSON(StringRef, OptionFlags &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarReadJSON", [](StringRef a, OptionFlags & b) {return poplar::readJSON(a, b);} ); }
// poplar::readJSONFromEnv(StringRef, OptionFlags &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarReadJSONFromEnv", [](StringRef a, OptionFlags & b) {return poplar::readJSONFromEnv(a, b);} ); }
// poplar::GlobalExchangeFlow::GlobalExchangeFlow(unsigned int, unsigned int)__CXXConstructor
{ using namespace poplar;
JLGlobalExchangeFlow.constructor<unsigned int, unsigned int>();
}
// poplar::GlobalExchangeConstraint::GlobalExchangeConstraint(double, ArrayRef<GlobalExchangeFlow>)__CXXConstructor
{ using namespace poplar;
JLGlobalExchangeConstraint.constructor<double, jlcxx::ArrayRef<GlobalExchangeFlow>>();
}
// poplar::IpuLinkConfiguration::Default__EnumConstantDecl
mod.set_const("PoplarIpuLinkConfigurationPoplarDefault", poplar::IpuLinkConfiguration::Default);
// poplar::IpuLinkConfiguration::SlidingWindow__EnumConstantDecl
mod.set_const("PoplarIpuLinkConfigurationPoplarSlidingWindow", poplar::IpuLinkConfiguration::SlidingWindow);
// poplar::IpuLinkConfiguration::BarleyTwist__EnumConstantDecl
mod.set_const("PoplarIpuLinkConfigurationPoplarBarleyTwist", poplar::IpuLinkConfiguration::BarleyTwist);
// poplar::IpuLinkTopology::Mesh__EnumConstantDecl
mod.set_const("PoplarIpuLinkTopologyPoplarMesh", poplar::IpuLinkTopology::Mesh);
// poplar::IpuLinkTopology::Torus__EnumConstantDecl
mod.set_const("PoplarIpuLinkTopologyPoplarTorus", poplar::IpuLinkTopology::Torus);
// poplar::IpuLinkTopology::Line__EnumConstantDecl
mod.set_const("PoplarIpuLinkTopologyPoplarLine", poplar::IpuLinkTopology::Line);
// poplar::TargetType::IPU__EnumConstantDecl
mod.set_const("PoplarTargetTypePoplarIPU", poplar::TargetType::IPU);
// poplar::TargetType::IPU_MODEL__EnumConstantDecl
mod.set_const("PoplarTargetTypePoplarIPU_MODEL", poplar::TargetType::IPU_MODEL);
// poplar::TargetType::CPU__EnumConstantDecl
mod.set_const("PoplarTargetTypePoplarCPU", poplar::TargetType::CPU);
// poplar::Type::Type(const Type &)__CXXConstructor
{ using namespace poplar;
JLType.constructor<const Type &>();
}
// poplar::Type::toString()__CXXMethod
{ using namespace poplar;
JLType.method("TypeToString", [](poplar::Type& cl) {return cl.toString();});
}
// poplar::Type::hash()__CXXMethod
{ using namespace poplar;
JLType.method("TypeHash", [](poplar::Type& cl) {return cl.hash();});
}
// poplar::Type::isFloatingPoint()__CXXMethod
{ using namespace poplar;
JLType.method("TypeIsFloatingPoint", [](poplar::Type& cl) {return cl.isFloatingPoint();});
}
// poplar::Type::requiresMetadata()__CXXMethod
{ using namespace poplar;
JLType.method("TypeRequiresMetadata", [](poplar::Type& cl) {return cl.requiresMetadata();});
}
// poplar::Target::Target(const Target &)__CXXConstructor
{ using namespace poplar;
JLTarget.constructor<const Target &>();
}
// poplar::Target::hash()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetHash", [](poplar::Target& cl) {return cl.hash();});
}
// poplar::Target::getTargetType()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetTargetType", [](poplar::Target& cl) {return cl.getTargetType();});
}
// poplar::Target::getTargetSystemString()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetTargetSystemString", [](poplar::Target& cl) {return cl.getTargetSystemString();});
}
// poplar::Target::getTargetArchString()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetTargetArchString", [](poplar::Target& cl) {return cl.getTargetArchString();});
}
// poplar::Target::getNumIPUs()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetNumIPUs", [](poplar::Target& cl) {return cl.getNumIPUs();});
}
// poplar::Target::getTilesPerIPU()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetTilesPerIPU", [](poplar::Target& cl) {return cl.getTilesPerIPU();});
}
// poplar::Target::getNumWorkerContexts()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetNumWorkerContexts", [](poplar::Target& cl) {return cl.getNumWorkerContexts();});
}
// poplar::Target::getBytesPerTile()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetBytesPerTile", [](poplar::Target& cl) {return cl.getBytesPerTile();});
}
// poplar::Target::getExchangeBytesPerCycle()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetExchangeBytesPerCycle", [](poplar::Target& cl) {return cl.getExchangeBytesPerCycle();});
}
// poplar::Target::getMemcpyBytesPerCycle()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetMemcpyBytesPerCycle", [](poplar::Target& cl) {return cl.getMemcpyBytesPerCycle();});
}
// poplar::Target::getMinIPUSyncDelay()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetMinIPUSyncDelay", [](poplar::Target& cl) {return cl.getMinIPUSyncDelay();});
}
// poplar::Target::getGlobalSyncCycles()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetGlobalSyncCycles", [](poplar::Target& cl) {return cl.getGlobalSyncCycles();});
}
// poplar::Target::getMemoryElementOffsets()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetMemoryElementOffsets", [](poplar::Target& cl) {return cl.getMemoryElementOffsets();});
}
// poplar::Target::getInterleavedMemoryElementIndex()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetInterleavedMemoryElementIndex", [](poplar::Target& cl) {return cl.getInterleavedMemoryElementIndex();});
}
// poplar::Target::getNumStrideBits()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetNumStrideBits", [](poplar::Target& cl) {return cl.getNumStrideBits();});
}
// poplar::Target::getDataPathWidth()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetDataPathWidth", [](poplar::Target& cl) {return cl.getDataPathWidth();});
}
// poplar::Target::getFp8ConvUnitMaxPipelineDepth()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetFp8ConvUnitMaxPipelineDepth", [](poplar::Target& cl) {return cl.getFp8ConvUnitMaxPipelineDepth();});
}
// poplar::Target::getFp16ConvUnitMaxPipelineDepth()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetFp16ConvUnitMaxPipelineDepth", [](poplar::Target& cl) {return cl.getFp16ConvUnitMaxPipelineDepth();});
}
// poplar::Target::getFp32ConvUnitMaxPipelineDepth()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetFp32ConvUnitMaxPipelineDepth", [](poplar::Target& cl) {return cl.getFp32ConvUnitMaxPipelineDepth();});
}
// poplar::Target::getFp8ConvUnitInputLoadElemsPerCycle()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetFp8ConvUnitInputLoadElemsPerCycle", [](poplar::Target& cl) {return cl.getFp8ConvUnitInputLoadElemsPerCycle();});
}
// poplar::Target::getFp16ConvUnitInputLoadElemsPerCycle()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetFp16ConvUnitInputLoadElemsPerCycle", [](poplar::Target& cl) {return cl.getFp16ConvUnitInputLoadElemsPerCycle();});
}
// poplar::Target::getFp32ConvUnitInputLoadElemsPerCycle()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetFp32ConvUnitInputLoadElemsPerCycle", [](poplar::Target& cl) {return cl.getFp32ConvUnitInputLoadElemsPerCycle();});
}
// poplar::Target::getFp16InFp16OutConvUnitsPerTile()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetFp16InFp16OutConvUnitsPerTile", [](poplar::Target& cl) {return cl.getFp16InFp16OutConvUnitsPerTile();});
}
// poplar::Target::getFp16InFp32OutConvUnitsPerTile()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetFp16InFp32OutConvUnitsPerTile", [](poplar::Target& cl) {return cl.getFp16InFp32OutConvUnitsPerTile();});
}
// poplar::Target::getFp32InFp32OutConvUnitsPerTile()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetFp32InFp32OutConvUnitsPerTile", [](poplar::Target& cl) {return cl.getFp32InFp32OutConvUnitsPerTile();});
}
// poplar::Target::getFp8InFp16OutConvUnitsPerTile()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetFp8InFp16OutConvUnitsPerTile", [](poplar::Target& cl) {return cl.getFp8InFp16OutConvUnitsPerTile();});
}
// poplar::Target::getConvUnitCoeffLoadBytesPerCycle()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetConvUnitCoeffLoadBytesPerCycle", [](poplar::Target& cl) {return cl.getConvUnitCoeffLoadBytesPerCycle();});
}
// poplar::Target::getRptCountMax()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetRptCountMax", [](poplar::Target& cl) {return cl.getRptCountMax();});
}
// poplar::Target::supportsExchangeBusSharing()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetSupportsExchangeBusSharing", [](poplar::Target& cl) {return cl.supportsExchangeBusSharing();});
}
// poplar::Target::getTilesPerSharedExchangeBus()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetTilesPerSharedExchangeBus", [](poplar::Target& cl) {return cl.getTilesPerSharedExchangeBus();});
}
// poplar::Target::getNumTiles()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetNumTiles", [](poplar::Target& cl) {return cl.getNumTiles();});
}
// poplar::Target::getMemoryBytes()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetMemoryBytes", [](poplar::Target& cl) {return cl.getMemoryBytes();});
}
// poplar::Target::getFloatVectorWidth()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetFloatVectorWidth", [](poplar::Target& cl) {return cl.getFloatVectorWidth();});
}
// poplar::Target::getHalfVectorWidth()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetHalfVectorWidth", [](poplar::Target& cl) {return cl.getHalfVectorWidth();});
}
// poplar::Target::getQuarterVectorWidth()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetQuarterVectorWidth", [](poplar::Target& cl) {return cl.getQuarterVectorWidth();});
}
// poplar::Target::getVectorWidth(const poplar::Type &)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetVectorWidth", [](poplar::Target& cl, const poplar::Type & a) {return cl.getVectorWidth(a);});
}
// poplar::Target::getWeightsPerConvUnit(const Type &)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetWeightsPerConvUnit", [](poplar::Target& cl, const Type & a) {return cl.getWeightsPerConvUnit(a);});
}
// poplar::Target::getConvUnitInputLoadElemsPerCycle(const Type &)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetConvUnitInputLoadElemsPerCycle", [](poplar::Target& cl, const Type & a) {return cl.getConvUnitInputLoadElemsPerCycle(a);});
}
// poplar::Target::getConvUnitMaxPipelineDepth(const Type &)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetConvUnitMaxPipelineDepth", [](poplar::Target& cl, const Type & a) {return cl.getConvUnitMaxPipelineDepth(a);});
}
// poplar::Target::getNumConvUnits(const Type &, const Type &)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetNumConvUnits", [](poplar::Target& cl, const Type & a, const Type & b) {return cl.getNumConvUnits(a, b);});
}
// poplar::Target::getMaxIPUSyncDelay()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetMaxIPUSyncDelay", [](poplar::Target& cl) {return cl.getMaxIPUSyncDelay();});
}
// poplar::Target::getTileClockFrequency()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetTileClockFrequency", [](poplar::Target& cl) {return cl.getTileClockFrequency();});
}
// poplar::Target::getNumTilesPerXBContext()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetNumTilesPerXBContext", [](poplar::Target& cl) {return cl.getNumTilesPerXBContext();});
}
// poplar::Target::getNumContextsPerXB()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetNumContextsPerXB", [](poplar::Target& cl) {return cl.getNumContextsPerXB();});
}
// poplar::Target::getTileHostExchangeXB(unsigned int)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetTileHostExchangeXB", [](poplar::Target& cl, unsigned int a) {return cl.getTileHostExchangeXB(a);});
}
// poplar::Target::getTileHostExchangeContext(unsigned int)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetTileHostExchangeContext", [](poplar::Target& cl, unsigned int a) {return cl.getTileHostExchangeContext(a);});
}
// poplar::Target::getTileHostExchangeContextPosition(unsigned int)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetTileHostExchangeContextPosition", [](poplar::Target& cl, unsigned int a) {return cl.getTileHostExchangeContextPosition(a);});
}
// poplar::Target::getTypeSize(const Type &)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetTypeSize", [](poplar::Target& cl, const Type & a) {return cl.getTypeSize(a);});
}
// poplar::Target::getAtomicStoreGranularity()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetAtomicStoreGranularity", [](poplar::Target& cl) {return cl.getAtomicStoreGranularity();});
}
// poplar::Target::makeFpIctlValue(bool, bool, bool, bool, bool)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetMakeFpIctlValue", [](poplar::Target& cl, bool a, bool b, bool c, bool d, bool e) {return cl.makeFpIctlValue(a, b, c, d, e);});
}
// poplar::Target::getFpIctlRegIndex()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetFpIctlRegIndex", [](poplar::Target& cl) {return cl.getFpIctlRegIndex();});
}
// poplar::Target::getDbgDataRegIndex()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetDbgDataRegIndex", [](poplar::Target& cl) {return cl.getDbgDataRegIndex();});
}
// poplar::Target::getIpuLinkConfiguration()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetIpuLinkConfiguration", [](poplar::Target& cl) {return cl.getIpuLinkConfiguration();});
}
// poplar::Target::getIpuLinkTopology()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetIpuLinkTopology", [](poplar::Target& cl) {return cl.getIpuLinkTopology();});
}
// poplar::Target::getIpuLinkDomainSize()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetIpuLinkDomainSize", [](poplar::Target& cl) {return cl.getIpuLinkDomainSize();});
}
// poplar::Target::getInstanceSize()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetInstanceSize", [](poplar::Target& cl) {return cl.getInstanceSize();});
}
// poplar::Target::getGatewayMode()__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetGatewayMode", [](poplar::Target& cl) {return cl.getGatewayMode();});
}
// poplar::Target::createVirtualTarget(unsigned int, unsigned int)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetCreateVirtualTarget", [](poplar::Target& cl, unsigned int a, unsigned int b) {return cl.createVirtualTarget(a, b);});
}
// poplar::Target::createCPUTarget(bool, unsigned int)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetCreateCPUTarget", [](poplar::Target& cl) {return cl.createCPUTarget();});
JLTarget.method("TargetCreateCPUTarget", [](poplar::Target& cl, bool a) {return cl.createCPUTarget(a);});
JLTarget.method("TargetCreateCPUTarget", [](poplar::Target& cl, bool a, unsigned int b) {return cl.createCPUTarget(a, b);});
}
// poplar::Target::createIPUTarget(StringRef, const OptionFlags &)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetCreateIPUTarget", [](poplar::Target& cl, StringRef a) {return cl.createIPUTarget(a);});
JLTarget.method("TargetCreateIPUTarget", [](poplar::Target& cl, StringRef a, const OptionFlags & b) {return cl.createIPUTarget(a, b);});
}
// poplar::Target::createIPUTarget(unsigned int, StringRef, const OptionFlags &)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetCreateIPUTarget", [](poplar::Target& cl, unsigned int a, StringRef b) {return cl.createIPUTarget(a, b);});
JLTarget.method("TargetCreateIPUTarget", [](poplar::Target& cl, unsigned int a, StringRef b, const OptionFlags & c) {return cl.createIPUTarget(a, b, c);});
}
// poplar::Target::createIPUTarget(unsigned int, unsigned int, StringRef, const OptionFlags &)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetCreateIPUTarget", [](poplar::Target& cl, unsigned int a, unsigned int b, StringRef c) {return cl.createIPUTarget(a, b, c);});
JLTarget.method("TargetCreateIPUTarget", [](poplar::Target& cl, unsigned int a, unsigned int b, StringRef c, const OptionFlags & d) {return cl.createIPUTarget(a, b, c, d);});
}
// poplar::Target::getTypeLimitsMaxAs<>(const Type &)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetTypeLimitsMaxAs<>", [](poplar::Target& cl, const Type & a) {return cl.getTypeLimitsMaxAs<>(a);});
}
// poplar::Target::getTypeLimitsLowestAs<>(const Type &)__CXXMethod
{ using namespace poplar;
JLTarget.method("TargetGetTypeLimitsLowestAs<>", [](poplar::Target& cl, const Type & a) {return cl.getTypeLimitsLowestAs<>(a);});
}
// poplar::copyDeviceHalfToFloat(const Target &, const void *, float *, std::size_t)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarCopyDeviceHalfToFloat", [](const Target & a, const void * b, float * c, std::size_t d) {return poplar::copyDeviceHalfToFloat(a, b, c, d);} ); }
// poplar::copyFloatToDeviceHalf(const Target &, const float *, void *, std::size_t)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarCopyFloatToDeviceHalf", [](const Target & a, const float * b, void * c, std::size_t d) {return poplar::copyFloatToDeviceHalf(a, b, c, d);} ); }
// poplar::copyDeviceHalfToDouble(const Target &, const void *, double *, std::size_t)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarCopyDeviceHalfToDouble", [](const Target & a, const void * b, double * c, std::size_t d) {return poplar::copyDeviceHalfToDouble(a, b, c, d);} ); }
// poplar::copyDoubleToDeviceHalf(const Target &, const double *, void *, std::size_t)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarCopyDoubleToDeviceHalf", [](const Target & a, const double * b, void * c, std::size_t d) {return poplar::copyDoubleToDeviceHalf(a, b, c, d);} ); }
// poplar::Device::getId()__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceGetId", [](poplar::Device& cl) {return cl.getId();});
}
// poplar::Device::getTarget()__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceGetTarget", [](poplar::Device& cl) {return cl.getTarget();});
}
// poplar::Device::attach()__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceAttach", [](poplar::Device& cl) {return cl.attach();});
}
// poplar::Device::isAttached()__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceIsAttached", [](poplar::Device& cl) {return cl.isAttached();});
}
// poplar::Device::detach()__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceDetach", [](poplar::Device& cl) {return cl.detach();});
}
// poplar::Device::getDriverVersion(unsigned int &, unsigned int &, unsigned int &)__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceGetDriverVersion", [](poplar::Device& cl, unsigned int & a, unsigned int & b, unsigned int & c) {return cl.getDriverVersion(a, b, c);});
}
// poplar::Device::supportsRemoteBuffers()__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceSupportsRemoteBuffers", [](poplar::Device& cl) {return cl.supportsRemoteBuffers();});
}
// poplar::Device::hasGateway()__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceHasGateway", [](poplar::Device& cl) {return cl.hasGateway();});
}
// poplar::Device::getAttributes()__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceGetAttributes", [](poplar::Device& cl) {return cl.getAttributes();});
}
// poplar::Device::getNumaTopology()__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceGetNumaTopology", [](poplar::Device& cl) {return cl.getNumaTopology();});
}
// poplar::Device::getNumaNodesUsedForIPUs()__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceGetNumaNodesUsedForIPUs", [](poplar::Device& cl) {return cl.getNumaNodesUsedForIPUs();});
}
// poplar::Device::getDriverIDs()__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceGetDriverIDs", [](poplar::Device& cl) {return cl.getDriverIDs();});
}
// poplar::Device::reset()__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceReset", [](poplar::Device& cl) {return cl.reset();});
}
// poplar::Device::createVirtualDevice(unsigned int)__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceCreateVirtualDevice", [](poplar::Device& cl, unsigned int a) {return cl.createVirtualDevice(a);});
}
// poplar::Device::createCPUDevice(unsigned int)__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceCreateCPUDevice", [](poplar::Device& cl) {return cl.createCPUDevice();});
JLDevice.method("DeviceCreateCPUDevice", [](poplar::Device& cl, unsigned int a) {return cl.createCPUDevice(a);});
}
// poplar::Device::createSimulatorDevice(const Target &, const OptionFlags &)__CXXMethod
{ using namespace poplar;
JLDevice.method("DeviceCreateSimulatorDevice", [](poplar::Device& cl, const Target & a) {return cl.createSimulatorDevice(a);});
JLDevice.method("DeviceCreateSimulatorDevice", [](poplar::Device& cl, const Target & a, const OptionFlags & b) {return cl.createSimulatorDevice(a, b);});
}
// poplar::DeviceManager::DeviceManager(const DeviceManager &)__CXXConstructor
{ using namespace poplar;
JLDeviceManager.constructor<const DeviceManager &>();
}
// poplar::DeviceManager::getNumDevices()__CXXMethod
{ using namespace poplar;
JLDeviceManager.method("DeviceManagerGetNumDevices", [](poplar::DeviceManager& cl) {return cl.getNumDevices();});
}
// poplar::DeviceManager::getDevice(unsigned int, const OptionFlags &)__CXXMethod
{ using namespace poplar;
JLDeviceManager.method("DeviceManagerGetDevice", [](poplar::DeviceManager& cl, unsigned int a) {return cl.getDevice(a);});
JLDeviceManager.method("DeviceManagerGetDevice", [](poplar::DeviceManager& cl, unsigned int a, const OptionFlags & b) {return cl.getDevice(a, b);});
}
// poplar::DeviceManager::getChildDeviceIds(unsigned int, unsigned int)__CXXMethod
{ using namespace poplar;
JLDeviceManager.method("DeviceManagerGetChildDeviceIds", [](poplar::DeviceManager& cl, unsigned int a) {return cl.getChildDeviceIds(a);});
JLDeviceManager.method("DeviceManagerGetChildDeviceIds", [](poplar::DeviceManager& cl, unsigned int a, unsigned int b) {return cl.getChildDeviceIds(a, b);});
}
// poplar::DeviceManager::createDeviceManager()__CXXMethod
{ using namespace poplar;
JLDeviceManager.method("DeviceManagerCreateDeviceManager", [](poplar::DeviceManager& cl) {return cl.createDeviceManager();});
}
// poplar::CodeletFileType::PreprocessedAsmSource__EnumConstantDecl
mod.set_const("PoplarCodeletFileTypePoplarPreprocessedAsmSource", poplar::CodeletFileType::PreprocessedAsmSource);
// poplar::CodeletFileType::AsmSource__EnumConstantDecl
mod.set_const("PoplarCodeletFileTypePoplarAsmSource", poplar::CodeletFileType::AsmSource);
// poplar::CodeletFileType::CSource__EnumConstantDecl
mod.set_const("PoplarCodeletFileTypePoplarCSource", poplar::CodeletFileType::CSource);
// poplar::CodeletFileType::CppSource__EnumConstantDecl
mod.set_const("PoplarCodeletFileTypePoplarCppSource", poplar::CodeletFileType::CppSource);
// poplar::CodeletFileType::IrSource__EnumConstantDecl
mod.set_const("PoplarCodeletFileTypePoplarIrSource", poplar::CodeletFileType::IrSource);
// poplar::CodeletFileType::Object__EnumConstantDecl
mod.set_const("PoplarCodeletFileTypePoplarObject", poplar::CodeletFileType::Object);
// poplar::CodeletFileType::Auto__EnumConstantDecl
mod.set_const("PoplarCodeletFileTypePoplarAuto", poplar::CodeletFileType::Auto);
// poplar::getCodeletFileType(const char *)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarGetCodeletFileType", [](const char * a) {return poplar::getCodeletFileType(a);} ); }
// poplar::getExtensionFromFileType(CodeletFileType)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarGetExtensionFromFileType", [](CodeletFileType a) {return poplar::getExtensionFromFileType(a);} ); }
// poplar::getLanguageOption(CodeletFileType)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarGetLanguageOption", [](CodeletFileType a) {return poplar::getLanguageOption(a);} ); }
// poplar::DataStreamType::HostToDeviceFIFO__EnumConstantDecl
mod.set_const("PoplarDataStreamTypePoplarHostToDeviceFIFO", poplar::DataStreamType::HostToDeviceFIFO);
// poplar::DataStreamType::DeviceToHostFIFO__EnumConstantDecl
mod.set_const("PoplarDataStreamTypePoplarDeviceToHostFIFO", poplar::DataStreamType::DeviceToHostFIFO);
// poplar::DataStreamType::HostToDeviceBuffer__EnumConstantDecl
mod.set_const("PoplarDataStreamTypePoplarHostToDeviceBuffer", poplar::DataStreamType::HostToDeviceBuffer);
// poplar::DataStreamType::DeviceToHostBuffer__EnumConstantDecl
mod.set_const("PoplarDataStreamTypePoplarDeviceToHostBuffer", poplar::DataStreamType::DeviceToHostBuffer);
// poplar::isDeviceToHost(DataStreamType)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarIsDeviceToHost", [](DataStreamType a) {return poplar::isDeviceToHost(a);} ); }
// poplar::isHostToDevice(DataStreamType)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarIsHostToDevice", [](DataStreamType a) {return poplar::isHostToDevice(a);} ); }
// poplar::isRemoteBuffer(DataStreamType)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarIsRemoteBuffer", [](DataStreamType a) {return poplar::isRemoteBuffer(a);} ); }
// poplar::ReplicatedStreamMode::REPLICATE__EnumConstantDecl
mod.set_const("PoplarReplicatedStreamModePoplarREPLICATE", poplar::ReplicatedStreamMode::REPLICATE);
// poplar::ReplicatedStreamMode::BROADCAST__EnumConstantDecl
mod.set_const("PoplarReplicatedStreamModePoplarBROADCAST", poplar::ReplicatedStreamMode::BROADCAST);
// poplar::DataStream::DataStream(const DataStream &)__CXXConstructor
{ using namespace poplar;
JLDataStream.constructor<const DataStream &>();
}
// poplar::DataStream::handle()__CXXMethod
{ using namespace poplar;
JLDataStream.method("DataStreamHandle", [](poplar::DataStream& cl) {return cl.handle();});
}
// poplar::DataStream::numElements()__CXXMethod
{ using namespace poplar;
JLDataStream.method("DataStreamNumElements", [](poplar::DataStream& cl) {return cl.numElements();});
}
// poplar::DataStream::replicationFactor()__CXXMethod
{ using namespace poplar;
JLDataStream.method("DataStreamReplicationFactor", [](poplar::DataStream& cl) {return cl.replicationFactor();});
}
// poplar::DataStream::replicatedMode()__CXXMethod
{ using namespace poplar;
JLDataStream.method("DataStreamReplicatedMode", [](poplar::DataStream& cl) {return cl.replicatedMode();});
}
// poplar::DataStream::type()__CXXMethod
{ using namespace poplar;
JLDataStream.method("DataStreamType", [](poplar::DataStream& cl) {return cl.type();});
}
// poplar::DataStream::elementType()__CXXMethod
{ using namespace poplar;
JLDataStream.method("DataStreamElementType", [](poplar::DataStream& cl) {return cl.elementType();});
}
// poplar::RemoteBuffer::RemoteBuffer(const RemoteBuffer &)__CXXConstructor
{ using namespace poplar;
JLRemoteBuffer.constructor<const RemoteBuffer &>();
}
// poplar::RemoteBuffer::handle()__CXXMethod
{ using namespace poplar;
JLRemoteBuffer.method("RemoteBufferHandle", [](poplar::RemoteBuffer& cl) {return cl.handle();});
}
// poplar::RemoteBuffer::getIpuToHostStream()__CXXMethod
{ using namespace poplar;
JLRemoteBuffer.method("RemoteBufferGetIpuToHostStream", [](poplar::RemoteBuffer& cl) {return cl.getIpuToHostStream();});
}
// poplar::RemoteBuffer::getHostToIpuStream()__CXXMethod
{ using namespace poplar;
JLRemoteBuffer.method("RemoteBufferGetHostToIpuStream", [](poplar::RemoteBuffer& cl) {return cl.getHostToIpuStream();});
}
// poplar::RemoteBuffer::numElements()__CXXMethod
{ using namespace poplar;
JLRemoteBuffer.method("RemoteBufferNumElements", [](poplar::RemoteBuffer& cl) {return cl.numElements();});
}
// poplar::RemoteBuffer::getRepeats()__CXXMethod
{ using namespace poplar;
JLRemoteBuffer.method("RemoteBufferGetRepeats", [](poplar::RemoteBuffer& cl) {return cl.getRepeats();});
}
// poplar::RemoteBuffer::elementType()__CXXMethod
{ using namespace poplar;
JLRemoteBuffer.method("RemoteBufferElementType", [](poplar::RemoteBuffer& cl) {return cl.elementType();});
}
// poplar::RemoteBuffer::isRearrangeOnHost()__CXXMethod
{ using namespace poplar;
JLRemoteBuffer.method("RemoteBufferIsRearrangeOnHost", [](poplar::RemoteBuffer& cl) {return cl.isRearrangeOnHost();});
}
// poplar::RemoteBuffer::isOptimisedForMemory()__CXXMethod
{ using namespace poplar;
JLRemoteBuffer.method("RemoteBufferIsOptimisedForMemory", [](poplar::RemoteBuffer& cl) {return cl.isOptimisedForMemory();});
}
// poplar::ProfileValue::Type::BOOL___EnumConstantDecl
mod.set_const("ProfileValueTypeProfileValueBOOL_", poplar::ProfileValue::Type::BOOL_);
// poplar::ProfileValue::Type::STRING__EnumConstantDecl
mod.set_const("ProfileValueTypeProfileValueSTRING", poplar::ProfileValue::Type::STRING);
// poplar::ProfileValue::Type::NUMBER__EnumConstantDecl
mod.set_const("ProfileValueTypeProfileValueNUMBER", poplar::ProfileValue::Type::NUMBER);
// poplar::ProfileValue::Type::VECTOR__EnumConstantDecl
mod.set_const("ProfileValueTypeProfileValueVECTOR", poplar::ProfileValue::Type::VECTOR);
// poplar::ProfileValue::Type::MAP__EnumConstantDecl
mod.set_const("ProfileValueTypeProfileValueMAP", poplar::ProfileValue::Type::MAP);
// poplar::ProfileValue::type()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueType", [](poplar::ProfileValue& cl) {return cl.type();});
}
// poplar::ProfileValue::asString()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueAsString", [](poplar::ProfileValue& cl) {return cl.asString();});
}
// poplar::ProfileValue::asBool()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueAsBool", [](poplar::ProfileValue& cl) {return cl.asBool();});
}
// poplar::ProfileValue::asInt()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueAsInt", [](poplar::ProfileValue& cl) {return cl.asInt();});
}
// poplar::ProfileValue::asUint()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueAsUint", [](poplar::ProfileValue& cl) {return cl.asUint();});
}
// poplar::ProfileValue::asDouble()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueAsDouble", [](poplar::ProfileValue& cl) {return cl.asDouble();});
}
// poplar::ProfileValue::getOrNull(StringRef)__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueGetOrNull", [](poplar::ProfileValue& cl, StringRef a) {return cl.getOrNull(a);});
}
// poplar::ProfileValue::asMap()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueAsMap", [](poplar::ProfileValue& cl) {return cl.asMap();});
}
// poplar::ProfileValue::asVector()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueAsVector", [](poplar::ProfileValue& cl) {return cl.asVector();});
}
// poplar::ProfileValue::toUintVector()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueToUintVector", [](poplar::ProfileValue& cl) {return cl.toUintVector();});
}
// poplar::ProfileValue::size()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueSize", [](poplar::ProfileValue& cl) {return cl.size();});
}
// poplar::ProfileValue::sumDouble()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueSumDouble", [](poplar::ProfileValue& cl) {return cl.sumDouble();});
}
// poplar::ProfileValue::sumInt()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueSumInt", [](poplar::ProfileValue& cl) {return cl.sumInt();});
}
// poplar::ProfileValue::sumUint()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueSumUint", [](poplar::ProfileValue& cl) {return cl.sumUint();});
}
// poplar::ProfileValue::sum2DInt()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueSum2DInt", [](poplar::ProfileValue& cl) {return cl.sum2DInt();});
}
// poplar::ProfileValue::sum2DUint()__CXXMethod
{ using namespace poplar;
JLProfileValue.method("ProfileValueSum2DUint", [](poplar::ProfileValue& cl) {return cl.sum2DUint();});
}
// poplar::ProfileValue::ProfileValue(String)__CXXConstructor
{ using namespace poplar;
JLProfileValue.constructor<String>();
}
// poplar::ProfileValue::ProfileValue(Vector)__CXXConstructor
{ using namespace poplar;
JLProfileValue.constructor<Vector>();
}
// poplar::ProfileValue::ProfileValue(Map)__CXXConstructor
{ using namespace poplar;
JLProfileValue.constructor<Map>();
}
// poplar::ProfileValue::ProfileValue(Number)__CXXConstructor
{ using namespace poplar;
JLProfileValue.constructor<Number>();
}
// poplar::ProfileValue::ProfileValue(Boolean)__CXXConstructor
{ using namespace poplar;
JLProfileValue.constructor<Boolean>();
}
// poplar::ProfileValue::ProfileValue(const char *)__CXXConstructor
{ using namespace poplar;
JLProfileValue.constructor<const char *>();
}
// poplar::ProfileValue::ProfileValue(const ProfileValue &)__CXXConstructor
{ using namespace poplar;
JLProfileValue.constructor<const ProfileValue &>();
}
// poplar::SerializationFormat::Binary__EnumConstantDecl
mod.set_const("PoplarSerializationFormatPoplarBinary", poplar::SerializationFormat::Binary);
// poplar::SerializationFormat::JSON__EnumConstantDecl
mod.set_const("PoplarSerializationFormatPoplarJSON", poplar::SerializationFormat::JSON);
// poplar::SourceLocation::SourceLocation(const char *, const char *, unsigned int)__CXXConstructor
{ using namespace poplar;
JLSourceLocation.constructor<const char *, const char *, unsigned int>();
}
// poplar::SourceLocation::getFunctionName()__CXXMethod
{ using namespace poplar;
JLSourceLocation.method("SourceLocationGetFunctionName", [](poplar::SourceLocation& cl) {return cl.getFunctionName();});
}
// poplar::SourceLocation::getFileName()__CXXMethod
{ using namespace poplar;
JLSourceLocation.method("SourceLocationGetFileName", [](poplar::SourceLocation& cl) {return cl.getFileName();});
}
// poplar::SourceLocation::getLineNumber()__CXXMethod
{ using namespace poplar;
JLSourceLocation.method("SourceLocationGetLineNumber", [](poplar::SourceLocation& cl) {return cl.getLineNumber();});
}
// poplar::SourceLocation::isValid()__CXXMethod
{ using namespace poplar;
JLSourceLocation.method("SourceLocationIsValid", [](poplar::SourceLocation& cl) {return cl.isValid();});
}
// poplar::SourceLocation::Current(const char *, const char *, unsigned int)__CXXMethod
{ using namespace poplar;
JLSourceLocation.method("SourceLocationCurrent", [](poplar::SourceLocation& cl) {return cl.Current();});
JLSourceLocation.method("SourceLocationCurrent", [](poplar::SourceLocation& cl, const char * a) {return cl.Current(a);});
JLSourceLocation.method("SourceLocationCurrent", [](poplar::SourceLocation& cl, const char * a, const char * b) {return cl.Current(a, b);});
JLSourceLocation.method("SourceLocationCurrent", [](poplar::SourceLocation& cl, const char * a, const char * b, unsigned int c) {return cl.Current(a, b, c);});
}
// poplar::DebugSerializationFormat::JSON__EnumConstantDecl
mod.set_const("PoplarDebugSerializationFormatPoplarJSON", poplar::DebugSerializationFormat::JSON);
// poplar::DebugSerializationFormat::CBOR__EnumConstantDecl
mod.set_const("PoplarDebugSerializationFormatPoplarCBOR", poplar::DebugSerializationFormat::CBOR);
// poplar::DebugInfo::DebugInfo(const DebugContext &, std::string)__CXXConstructor
{ using namespace poplar;
JLDebugInfo.constructor<const DebugContext &, std::string>();
}
// poplar::DebugInfo::getId()__CXXMethod
{ using namespace poplar;
JLDebugInfo.method("DebugInfoGetId", [](poplar::DebugInfo& cl) {return cl.getId();});
}
// poplar::DebugInfo::getPathName()__CXXMethod
{ using namespace poplar;
JLDebugInfo.method("DebugInfoGetPathName", [](poplar::DebugInfo& cl) {return cl.getPathName();});
}
// poplar::DebugInfo::initializeStreamer(const std::string &, const DebugSerializationFormat &)__CXXMethod
{ using namespace poplar;
JLDebugInfo.method("DebugInfoInitializeStreamer", [](poplar::DebugInfo& cl, const std::string & a) {return cl.initializeStreamer(a);});
JLDebugInfo.method("DebugInfoInitializeStreamer", [](poplar::DebugInfo& cl, const std::string & a, const DebugSerializationFormat & b) {return cl.initializeStreamer(a, b);});
}
// poplar::DebugInfo::closeStreamer()__CXXMethod
{ using namespace poplar;
JLDebugInfo.method("DebugInfoCloseStreamer", [](poplar::DebugInfo& cl) {return cl.closeStreamer();});
}
// poplar::DebugInfo::setValue(std::string, ProfileValue)__CXXMethod
{ using namespace poplar;
JLDebugInfo.method("DebugInfoSetValue", [](poplar::DebugInfo& cl, std::string a, ProfileValue b) {return cl.setValue(a, b);});
}
// poplar::DebugNameAndId::DebugNameAndId(std::string, DebugId, std::string)__CXXConstructor
{ using namespace poplar;
JLDebugNameAndId.constructor<std::string>();
JLDebugNameAndId.constructor<std::string, DebugId>();
JLDebugNameAndId.constructor<std::string, DebugId, std::string>();
}
// poplar::DebugNameAndId::DebugNameAndId(const char *)__CXXConstructor
{ using namespace poplar;
JLDebugNameAndId.constructor<const char *>();
}
// poplar::DebugNameAndId::DebugNameAndId(DebugId)__CXXConstructor
{ using namespace poplar;
JLDebugNameAndId.constructor<DebugId>();
}
// poplar::DebugNameAndId::DebugNameAndId(const DebugInfo &, std::string)__CXXConstructor
{ using namespace poplar;
JLDebugNameAndId.constructor<const DebugInfo &>();
JLDebugNameAndId.constructor<const DebugInfo &, std::string>();
}
// poplar::DebugNameAndId::DebugNameAndId(const DebugNameAndId &, StringRef)__CXXConstructor
{ using namespace poplar;
JLDebugNameAndId.constructor<const DebugNameAndId &>();
JLDebugNameAndId.constructor<const DebugNameAndId &, StringRef>();
}
// poplar::DebugNameAndId::getPathName()__CXXMethod
{ using namespace poplar;
JLDebugNameAndId.method("DebugNameAndIdGetPathName", [](poplar::DebugNameAndId& cl) {return cl.getPathName();});
}
// poplar::DebugContext::getPathName()__CXXMethod
{ using namespace poplar;
JLDebugContext.method("DebugContextGetPathName", [](poplar::DebugContext& cl) {return cl.getPathName();});
}
// poplar::FunctionBufferMappingType::REMOTE__EnumConstantDecl
mod.set_const("PoplarFunctionBufferMappingTypePoplarREMOTE", poplar::FunctionBufferMappingType::REMOTE);
// poplar::VertexRef::getId()__CXXMethod
{ using namespace poplar;
JLVertexRef.method("VertexRefGetId", [](poplar::VertexRef& cl) {return cl.getId();});
}
// poplar::FieldRef::isIndexed()__CXXMethod
{ using namespace poplar;
JLFieldRef.method("FieldRefIsIndexed", [](poplar::FieldRef& cl) {return cl.isIndexed();});
}
// poplar::FieldRef::getIndex()__CXXMethod
{ using namespace poplar;
JLFieldRef.method("FieldRefGetIndex", [](poplar::FieldRef& cl) {return cl.getIndex();});
}
// poplar::ComputeSet::ComputeSet(unsigned int)__CXXConstructor
{ using namespace poplar;
JLComputeSet.constructor<unsigned int>();
}
// poplar::ComputeSet::getId()__CXXMethod
{ using namespace poplar;
JLComputeSet.method("ComputeSetGetId", [](poplar::ComputeSet& cl) {return cl.getId();});
}
// poplar::Function::Function(unsigned int)__CXXConstructor
{ using namespace poplar;
JLFunction.constructor<unsigned int>();
}
// poplar::Function::getId()__CXXMethod
{ using namespace poplar;
JLFunction.method("FunctionGetId", [](poplar::Function& cl) {return cl.getId();});
}
// poplar::FunctionBuffer::FunctionBuffer(unsigned int)__CXXConstructor
{ using namespace poplar;
JLFunctionBuffer.constructor<unsigned int>();
}
// poplar::FunctionBuffer::getId()__CXXMethod
{ using namespace poplar;
JLFunctionBuffer.method("FunctionBufferGetId", [](poplar::FunctionBuffer& cl) {return cl.getId();});
}
// poplar::HostFunction::HostFunction(unsigned int)__CXXConstructor
{ using namespace poplar;
JLHostFunction.constructor<unsigned int>();
}
// poplar::HostFunction::getId()__CXXMethod
{ using namespace poplar;
JLHostFunction.method("HostFunctionGetId", [](poplar::HostFunction& cl) {return cl.getId();});
}
// poplar::ErrorCode::NONE__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarNONE", poplar::ErrorCode::NONE);
// poplar::ErrorCode::UNKNOWN__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarUNKNOWN", poplar::ErrorCode::UNKNOWN);
// poplar::ErrorCode::TRAP__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarTRAP", poplar::ErrorCode::TRAP);
// poplar::ErrorCode::FLOATING_POINT_INVALID_OPERATION__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarFLOATING_POINT_INVALID_OPERATION", poplar::ErrorCode::FLOATING_POINT_INVALID_OPERATION);
// poplar::ErrorCode::FLOATING_POINT_DIVIDE_BY_ZERO__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarFLOATING_POINT_DIVIDE_BY_ZERO", poplar::ErrorCode::FLOATING_POINT_DIVIDE_BY_ZERO);
// poplar::ErrorCode::FLOATING_POINT_OVERFLOW__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarFLOATING_POINT_OVERFLOW", poplar::ErrorCode::FLOATING_POINT_OVERFLOW);
// poplar::ErrorCode::TILE_MEMORY_BANK_CONFLICT__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarTILE_MEMORY_BANK_CONFLICT", poplar::ErrorCode::TILE_MEMORY_BANK_CONFLICT);
// poplar::ErrorCode::INVALID_EXCHANGE_CONFIGURATION__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarINVALID_EXCHANGE_CONFIGURATION", poplar::ErrorCode::INVALID_EXCHANGE_CONFIGURATION);
// poplar::ErrorCode::INVALID_ADDRESS__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarINVALID_ADDRESS", poplar::ErrorCode::INVALID_ADDRESS);
// poplar::ErrorCode::INVALID_OPERAND__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarINVALID_OPERAND", poplar::ErrorCode::INVALID_OPERAND);
// poplar::ErrorCode::INVALID_PROGRAM_COUNTER__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarINVALID_PROGRAM_COUNTER", poplar::ErrorCode::INVALID_PROGRAM_COUNTER);
// poplar::ErrorCode::INVALID_INSTRUCTION__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarINVALID_INSTRUCTION", poplar::ErrorCode::INVALID_INSTRUCTION);
// poplar::ErrorCode::EXCHANGE_ERROR__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarEXCHANGE_ERROR", poplar::ErrorCode::EXCHANGE_ERROR);
// poplar::ErrorCode::MEMORY_ERROR__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarMEMORY_ERROR", poplar::ErrorCode::MEMORY_ERROR);
// poplar::ErrorCode::IPUSOFTERR__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarIPUSOFTERR", poplar::ErrorCode::IPUSOFTERR);
// poplar::ErrorCode::LINK_DOWN__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarLINK_DOWN", poplar::ErrorCode::LINK_DOWN);
// poplar::ErrorCode::HOST_LINK_DOWN__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarHOST_LINK_DOWN", poplar::ErrorCode::HOST_LINK_DOWN);
// poplar::ErrorCode::HOST_SYNC_TIMEOUT__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarHOST_SYNC_TIMEOUT", poplar::ErrorCode::HOST_SYNC_TIMEOUT);
// poplar::ErrorCode::IPU_MEMORY_FAILURE__EnumConstantDecl
mod.set_const("PoplarErrorCodePoplarIPU_MEMORY_FAILURE", poplar::ErrorCode::IPU_MEMORY_FAILURE);
// poplar::errorCodeToString(ErrorCode)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarErrorCodeToString", [](ErrorCode a) {return poplar::errorCodeToString(a);} ); }
// poplar::errorCodeFromString(StringRef)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarErrorCodeFromString", [](StringRef a) {return poplar::errorCodeFromString(a);} ); }
// poplar::ErrorLocation::getTile()__CXXMethod
{ using namespace poplar;
JLErrorLocation.method("ErrorLocationGetTile", [](poplar::ErrorLocation& cl) {return cl.getTile();});
}
// poplar::ErrorLocation::ErrorLocation(const ErrorLocation &)__CXXConstructor
{ using namespace poplar;
JLErrorLocation.constructor<const ErrorLocation &>();
}
// poplar::poplar_error::poplar_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLPoplar_error.constructor<const std::string &>();
}
// poplar::poplar_error::poplar_error(const char *)__CXXConstructor
{ using namespace poplar;
JLPoplar_error.constructor<const char *>();
}
// poplar::poplar_error::attachSourceLocation(const DebugContext &)__CXXMethod
{ using namespace poplar;
JLPoplar_error.method("Poplar_errorAttachSourceLocation", [](poplar::poplar_error& cl, const DebugContext & a) {return cl.attachSourceLocation(a);});
}
// poplar::poplar_error::what()__CXXMethod
{ using namespace poplar;
JLPoplar_error.method("Poplar_errorWhat", [](poplar::poplar_error& cl) {return cl.what();});
}
// poplar::graph_program_compilation_error::graph_program_compilation_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLGraph_program_compilation_error.constructor<const std::string &>();
}
// poplar::graph_program_compilation_error::graph_program_compilation_error(const char *)__CXXConstructor
{ using namespace poplar;
JLGraph_program_compilation_error.constructor<const char *>();
}
// poplar::graph_object_creation_error::graph_object_creation_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLGraph_object_creation_error.constructor<const std::string &>();
}
// poplar::graph_object_creation_error::graph_object_creation_error(const char *)__CXXConstructor
{ using namespace poplar;
JLGraph_object_creation_error.constructor<const char *>();
}
// poplar::graph_object_load_error::graph_object_load_error(const std::string &, const std::string &)__CXXConstructor
{ using namespace poplar;
JLGraph_object_load_error.constructor<const std::string &, const std::string &>();
}
// poplar::no_environment::no_environment(const std::string &)__CXXConstructor
{ using namespace poplar;
JLNo_environment.constructor<const std::string &>();
}
// poplar::no_environment::no_environment(const char *)__CXXConstructor
{ using namespace poplar;
JLNo_environment.constructor<const char *>();
}
// poplar::unknown_vertex_type::unknown_vertex_type(const std::string &)__CXXConstructor
{ using namespace poplar;
JLUnknown_vertex_type.constructor<const std::string &>();
}
// poplar::unknown_field::unknown_field(const std::string &)__CXXConstructor
{ using namespace poplar;
JLUnknown_field.constructor<const std::string &>();
}
// poplar::unknown_field::unknown_field(const char *)__CXXConstructor
{ using namespace poplar;
JLUnknown_field.constructor<const char *>();
}
// poplar::unknown_field::unknown_field(const std::string &, const std::string &)__CXXConstructor
{ using namespace poplar;
JLUnknown_field.constructor<const std::string &, const std::string &>();
}
// poplar::control_program_error::control_program_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLControl_program_error.constructor<const std::string &>();
}
// poplar::type_error::type_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLType_error.constructor<const std::string &>();
}
// poplar::type_error::type_error(const char *)__CXXConstructor
{ using namespace poplar;
JLType_error.constructor<const char *>();
}
// poplar::index_error::index_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLIndex_error.constructor<const std::string &>();
}
// poplar::index_error::index_error(const char *)__CXXConstructor
{ using namespace poplar;
JLIndex_error.constructor<const char *>();
}
// poplar::index_error::index_error(const std::string &, std::size_t)__CXXConstructor
{ using namespace poplar;
JLIndex_error.constructor<const std::string &, std::size_t>();
}
// poplar::no_size_specified::no_size_specified(const std::string &)__CXXConstructor
{ using namespace poplar;
JLNo_size_specified.constructor<const std::string &>();
}
// poplar::no_size_specified::no_size_specified(const char *)__CXXConstructor
{ using namespace poplar;
JLNo_size_specified.constructor<const char *>();
}
// poplar::no_size_specified::no_size_specified(const std::string &, const std::string &)__CXXConstructor
{ using namespace poplar;
JLNo_size_specified.constructor<const std::string &, const std::string &>();
}
// poplar::graph_connection_error::graph_connection_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLGraph_connection_error.constructor<const std::string &>();
}
// poplar::graph_connection_error::graph_connection_error(const char *)__CXXConstructor
{ using namespace poplar;
JLGraph_connection_error.constructor<const char *>();
}
// poplar::graph_cycle_error::graph_cycle_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLGraph_cycle_error.constructor<const std::string &>();
}
// poplar::graph_cycle_error::graph_cycle_error(const char *)__CXXConstructor
{ using namespace poplar;
JLGraph_cycle_error.constructor<const char *>();
}
// poplar::graph_recursion_error::graph_recursion_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLGraph_recursion_error.constructor<const std::string &>();
}
// poplar::graph_recursion_error::graph_recursion_error(const char *)__CXXConstructor
{ using namespace poplar;
JLGraph_recursion_error.constructor<const char *>();
}
// poplar::graph_replication_error::graph_replication_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLGraph_replication_error.constructor<const std::string &>();
}
// poplar::graph_replication_error::graph_replication_error(const char *)__CXXConstructor
{ using namespace poplar;
JLGraph_replication_error.constructor<const char *>();
}
// poplar::missing_graph_profile::missing_graph_profile(const std::string &)__CXXConstructor
{ using namespace poplar;
JLMissing_graph_profile.constructor<const std::string &>();
}
// poplar::missing_graph_profile::missing_graph_profile(const char *)__CXXConstructor
{ using namespace poplar;
JLMissing_graph_profile.constructor<const char *>();
}
// poplar::missing_perf_estimate::missing_perf_estimate(const std::string &)__CXXConstructor
{ using namespace poplar;
JLMissing_perf_estimate.constructor<const std::string &>();
}
// poplar::invalid_tile_mapping::invalid_tile_mapping(const std::string &)__CXXConstructor
{ using namespace poplar;
JLInvalid_tile_mapping.constructor<const std::string &>();
}
// poplar::invalid_tile_mapping::invalid_tile_mapping(const char *)__CXXConstructor
{ using namespace poplar;
JLInvalid_tile_mapping.constructor<const char *>();
}
// poplar::tensor_creation_error::tensor_creation_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLTensor_creation_error.constructor<const std::string &>();
}
// poplar::tensor_creation_error::tensor_creation_error(const char *)__CXXConstructor
{ using namespace poplar;
JLTensor_creation_error.constructor<const char *>();
}
// poplar::tensor_io_state_error::tensor_io_state_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLTensor_io_state_error.constructor<const std::string &>();
}
// poplar::tensor_io_state_error::tensor_io_state_error(const char *)__CXXConstructor
{ using namespace poplar;
JLTensor_io_state_error.constructor<const char *>();
}
// poplar::tensor_metadata_error::tensor_metadata_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLTensor_metadata_error.constructor<const std::string &>();
}
// poplar::tensor_metadata_error::tensor_metadata_error(const char *)__CXXConstructor
{ using namespace poplar;
JLTensor_metadata_error.constructor<const char *>();
}
// poplar::stream_connection_error::stream_connection_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLStream_connection_error.constructor<const std::string &>();
}
// poplar::stream_connection_error::stream_connection_error(const char *)__CXXConstructor
{ using namespace poplar;
JLStream_connection_error.constructor<const char *>();
}
// poplar::overflow_error::overflow_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLOverflow_error.constructor<const std::string &>();
}
// poplar::overflow_error::overflow_error(const char *)__CXXConstructor
{ using namespace poplar;
JLOverflow_error.constructor<const char *>();
}
// poplar::memory_elem_constraints_error::memory_elem_constraints_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLMemory_elem_constraints_error.constructor<const std::string &>();
}
// poplar::memory_elem_constraints_error::memory_elem_constraints_error(const char *)__CXXConstructor
{ using namespace poplar;
JLMemory_elem_constraints_error.constructor<const char *>();
}
// poplar::graph_memory_allocation_error::graph_memory_allocation_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLGraph_memory_allocation_error.constructor<const std::string &>();
}
// poplar::graph_memory_allocation_error::graph_memory_allocation_error(const char *)__CXXConstructor
{ using namespace poplar;
JLGraph_memory_allocation_error.constructor<const char *>();
}
// poplar::stream_memory_allocation_error::stream_memory_allocation_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLStream_memory_allocation_error.constructor<const std::string &>();
}
// poplar::stream_memory_allocation_error::stream_memory_allocation_error(const char *)__CXXConstructor
{ using namespace poplar;
JLStream_memory_allocation_error.constructor<const char *>();
}
// poplar::invalid_machine_model::invalid_machine_model(const std::string &)__CXXConstructor
{ using namespace poplar;
JLInvalid_machine_model.constructor<const std::string &>();
}
// poplar::invalid_machine_model::invalid_machine_model(const char *)__CXXConstructor
{ using namespace poplar;
JLInvalid_machine_model.constructor<const char *>();
}
// poplar::invalid_option::invalid_option(const std::string &)__CXXConstructor
{ using namespace poplar;
JLInvalid_option.constructor<const std::string &>();
}
// poplar::invalid_option::invalid_option(const char *)__CXXConstructor
{ using namespace poplar;
JLInvalid_option.constructor<const char *>();
}
// poplar::link_error::link_error(const std::string &, const std::string &)__CXXConstructor
{ using namespace poplar;
JLLink_error.constructor<const std::string &>();
JLLink_error.constructor<const std::string &, const std::string &>();
}
// poplar::link_error::link_error(const char *, const char *)__CXXConstructor
{ using namespace poplar;
JLLink_error.constructor<const char *>();
JLLink_error.constructor<const char *, const char *>();
}
// poplar::runtime_error::runtime_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLRuntime_error.constructor<const std::string &>();
}
// poplar::runtime_error::runtime_error(const char *)__CXXConstructor
{ using namespace poplar;
JLRuntime_error.constructor<const char *>();
}
// poplar::application_runtime_error::application_runtime_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLApplication_runtime_error.constructor<const std::string &>();
}
// poplar::application_runtime_error::application_runtime_error(const char *)__CXXConstructor
{ using namespace poplar;
JLApplication_runtime_error.constructor<const char *>();
}
// poplar::system_runtime_error::system_runtime_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLSystem_runtime_error.constructor<const std::string &>();
}
// poplar::system_runtime_error::system_runtime_error(const char *)__CXXConstructor
{ using namespace poplar;
JLSystem_runtime_error.constructor<const char *>();
}
// poplar::RecoveryAction::IPU_RESET__EnumConstantDecl
mod.set_const("PoplarRecoveryActionPoplarIPU_RESET", poplar::RecoveryAction::IPU_RESET);
// poplar::RecoveryAction::LINK_RESET__EnumConstantDecl
mod.set_const("PoplarRecoveryActionPoplarLINK_RESET", poplar::RecoveryAction::LINK_RESET);
// poplar::RecoveryAction::PARTITION_RESET__EnumConstantDecl
mod.set_const("PoplarRecoveryActionPoplarPARTITION_RESET", poplar::RecoveryAction::PARTITION_RESET);
// poplar::RecoveryAction::FULL_RESET__EnumConstantDecl
mod.set_const("PoplarRecoveryActionPoplarFULL_RESET", poplar::RecoveryAction::FULL_RESET);
// poplar::recoverable_runtime_error::getRecoveryAction()__CXXMethod
{ using namespace poplar;
JLRecoverable_runtime_error.method("Recoverable_runtime_errorGetRecoveryAction", [](poplar::recoverable_runtime_error& cl) {return cl.getRecoveryAction();});
}
// poplar::recoverable_runtime_error::recoverable_runtime_error(RecoveryAction, const std::string &)__CXXConstructor
{ using namespace poplar;
JLRecoverable_runtime_error.constructor<RecoveryAction, const std::string &>();
}
// poplar::recoverable_runtime_error::recoverable_runtime_error(RecoveryAction, const char *)__CXXConstructor
{ using namespace poplar;
JLRecoverable_runtime_error.constructor<RecoveryAction, const char *>();
}
// poplar::unrecoverable_runtime_error::unrecoverable_runtime_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLUnrecoverable_runtime_error.constructor<const std::string &>();
}
// poplar::unrecoverable_runtime_error::unrecoverable_runtime_error(const char *)__CXXConstructor
{ using namespace poplar;
JLUnrecoverable_runtime_error.constructor<const char *>();
}
// poplar::unknown_runtime_error::unknown_runtime_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLUnknown_runtime_error.constructor<const std::string &>();
}
// poplar::unknown_runtime_error::unknown_runtime_error(const char *)__CXXConstructor
{ using namespace poplar;
JLUnknown_runtime_error.constructor<const char *>();
}
// poplar::symbol_error::symbol_error(const std::string &, const unsigned int)__CXXConstructor
{ using namespace poplar;
JLSymbol_error.constructor<const std::string &, const unsigned int>();
}
// poplar::file_load_error::file_load_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLFile_load_error.constructor<const std::string &>();
}
// poplar::parse_error::parse_error(const std::string &)__CXXConstructor
{ using namespace poplar;
JLParse_error.constructor<const std::string &>();
}
// poplar::parse_error::parse_error(const char *)__CXXConstructor
{ using namespace poplar;
JLParse_error.constructor<const char *>();
}
// poplar::PrintTensorFmt::FloatFormat::Auto__EnumConstantDecl
mod.set_const("PrintTensorFmtFloatFormatPrintTensorFmtAuto", poplar::PrintTensorFmt::FloatFormat::Auto);
// poplar::PrintTensorFmt::FloatFormat::Fixed__EnumConstantDecl
mod.set_const("PrintTensorFmtFloatFormatPrintTensorFmtFixed", poplar::PrintTensorFmt::FloatFormat::Fixed);
// poplar::PrintTensorFmt::FloatFormat::Scientific__EnumConstantDecl
mod.set_const("PrintTensorFmtFloatFormatPrintTensorFmtScientific", poplar::PrintTensorFmt::FloatFormat::Scientific);
// poplar::PrintTensorFmt::FloatFormat::None__EnumConstantDecl
mod.set_const("PrintTensorFmtFloatFormatPrintTensorFmtNone", poplar::PrintTensorFmt::FloatFormat::None);
// poplar::PrintTensorFmt::PrintTensorFmt(unsigned int, unsigned int, unsigned int, unsigned int, FloatFormat, char, char, char)__CXXConstructor
{ using namespace poplar;
JLPrintTensorFmt.constructor<unsigned int>();
JLPrintTensorFmt.constructor<unsigned int, unsigned int>();
JLPrintTensorFmt.constructor<unsigned int, unsigned int, unsigned int>();
JLPrintTensorFmt.constructor<unsigned int, unsigned int, unsigned int, unsigned int>();
JLPrintTensorFmt.constructor<unsigned int, unsigned int, unsigned int, unsigned int, FloatFormat>();
JLPrintTensorFmt.constructor<unsigned int, unsigned int, unsigned int, unsigned int, FloatFormat, char>();
JLPrintTensorFmt.constructor<unsigned int, unsigned int, unsigned int, unsigned int, FloatFormat, char, char>();
JLPrintTensorFmt.constructor<unsigned int, unsigned int, unsigned int, unsigned int, FloatFormat, char, char, char>();
}
// poplar::PrintTensorFmt::disableFormatting()__CXXMethod
{ using namespace poplar;
JLPrintTensorFmt.method("PrintTensorFmtDisableFormatting", [](poplar::PrintTensorFmt& cl) {return cl.disableFormatting();});
}
// poplar::PrintTensorFmt::PrintTensorFmt(const PrintTensorFmt &)__CXXConstructor
{ using namespace poplar;
JLPrintTensorFmt.constructor<const PrintTensorFmt &>();
}
// poplar::SyncType::INTERNAL__EnumConstantDecl
mod.set_const("PoplarSyncTypePoplarINTERNAL", poplar::SyncType::INTERNAL);
// poplar::SyncType::EXTERNAL__EnumConstantDecl
mod.set_const("PoplarSyncTypePoplarEXTERNAL", poplar::SyncType::EXTERNAL);
// poplar::SyncType::GLOBAL__EnumConstantDecl
mod.set_const("PoplarSyncTypePoplarGLOBAL", poplar::SyncType::GLOBAL);
// poplar::TypeTraits::isSimpleType()__CXXMethod
{ using namespace poplar;
JLTypeTraits.method("TypeTraitsIsSimpleType", [](poplar::TypeTraits& cl) {return cl.isSimpleType();});
}
// poplar::TypeTraits::make<>()__CXXMethod
{ using namespace poplar;
JLTypeTraits.method("TypeTraitsMake<>", [](poplar::TypeTraits& cl) {return cl.make<>();});
}
// poplar::TypeTraits::isSimpleType<>()__CXXMethod
{ using namespace poplar;
JLTypeTraits.method("TypeTraitsIsSimpleType<>", [](poplar::TypeTraits& cl) {return cl.isSimpleType<>();});
}
// poplar::TypeTraits::requiresMetadata<>()__CXXMethod
{ using namespace poplar;
JLTypeTraits.method("TypeTraitsRequiresMetadata<>", [](poplar::TypeTraits& cl) {return cl.requiresMetadata<>();});
}
// poplar::UpsampleMethod::REPEAT__EnumConstantDecl
mod.set_const("PoplarUpsampleMethodPoplarREPEAT", poplar::UpsampleMethod::REPEAT);
// poplar::Tensor::Tensor(const Tensor &)__CXXConstructor
{ using namespace poplar;
JLTensor.constructor<const Tensor &>();
}
// poplar::Tensor::elementType()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorElementType", [](poplar::Tensor& cl) {return cl.elementType();});
}
// poplar::Tensor::slice(std::size_t, std::size_t, unsigned int)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorSlice", [](poplar::Tensor& cl, std::size_t a, std::size_t b, unsigned int c) {return cl.slice(a, b, c);});
}
// poplar::Tensor::slice(std::size_t, std::size_t)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorSlice", [](poplar::Tensor& cl, std::size_t a, std::size_t b) {return cl.slice(a, b);});
}
// poplar::Tensor::slice(const Interval &, unsigned int)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorSlice", [](poplar::Tensor& cl, const Interval & a) {return cl.slice(a);});
JLTensor.method("TensorSlice", [](poplar::Tensor& cl, const Interval & a, unsigned int b) {return cl.slice(a, b);});
}
// poplar::Tensor::slice(ArrayRef<std::size_t>, ArrayRef<std::size_t>)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorSlice", [](poplar::Tensor& cl, jlcxx::ArrayRef<std::size_t> a, jlcxx::ArrayRef<std::size_t> b) {return cl.slice(jlcxxToPoplar(a), jlcxxToPoplar(b));});
}
// poplar::Tensor::slices(ArrayRef<Interval>, unsigned int)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorSlices", [](poplar::Tensor& cl, jlcxx::ArrayRef<Interval> a) {return cl.slices(jlcxxToPoplar(a));});
JLTensor.method("TensorSlices", [](poplar::Tensor& cl, jlcxx::ArrayRef<Interval> a, unsigned int b) {return cl.slices(jlcxxToPoplar(a), b);});
}
// poplar::Tensor::slices(const std::vector<std::vector<Interval>> &, unsigned int)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorSlices", [](poplar::Tensor& cl, const std::vector<std::vector<Interval>> & a) {return cl.slices(a);});
JLTensor.method("TensorSlices", [](poplar::Tensor& cl, const std::vector<std::vector<Interval>> & a, unsigned int b) {return cl.slices(a, b);});
}
// poplar::Tensor::slices(const poplar::ArrayRef<unsigned int> &, unsigned int)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorSlices", [](poplar::Tensor& cl, const poplar::ArrayRef<unsigned int> & a) {return cl.slices(a);});
JLTensor.method("TensorSlices", [](poplar::Tensor& cl, const poplar::ArrayRef<unsigned int> & a, unsigned int b) {return cl.slices(a, b);});
}
// poplar::Tensor::index(ArrayRef<std::size_t>)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorIndex", [](poplar::Tensor& cl, jlcxx::ArrayRef<std::size_t> a) {return cl.index(jlcxxToPoplar(a));});
}
// poplar::Tensor::flatten()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorFlatten", [](poplar::Tensor& cl) {return cl.flatten();});
}
// poplar::Tensor::flatten(unsigned int, unsigned int)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorFlatten", [](poplar::Tensor& cl, unsigned int a, unsigned int b) {return cl.flatten(a, b);});
}
// poplar::Tensor::reshape(ArrayRef<std::size_t>)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorReshape", [](poplar::Tensor& cl, jlcxx::ArrayRef<std::size_t> a) {return cl.reshape(jlcxxToPoplar(a));});
}
// poplar::Tensor::dimShuffle(ArrayRef<unsigned int>)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorDimShuffle", [](poplar::Tensor& cl, jlcxx::ArrayRef<unsigned int> a) {return cl.dimShuffle(jlcxxToPoplar(a));});
}
// poplar::Tensor::dimShufflePartial(ArrayRef<unsigned int>, ArrayRef<unsigned int>)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorDimShufflePartial", [](poplar::Tensor& cl, jlcxx::ArrayRef<unsigned int> a, jlcxx::ArrayRef<unsigned int> b) {return cl.dimShufflePartial(jlcxxToPoplar(a), jlcxxToPoplar(b));});
}
// poplar::Tensor::dimRoll(unsigned int, unsigned int)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorDimRoll", [](poplar::Tensor& cl, unsigned int a) {return cl.dimRoll(a);});
JLTensor.method("TensorDimRoll", [](poplar::Tensor& cl, unsigned int a, unsigned int b) {return cl.dimRoll(a, b);});
}
// poplar::Tensor::reshapePartial(unsigned int, unsigned int, ArrayRef<std::size_t>)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorReshapePartial", [](poplar::Tensor& cl, unsigned int a, unsigned int b, jlcxx::ArrayRef<std::size_t> c) {return cl.reshapePartial(a, b, jlcxxToPoplar(c));});
}
// poplar::Tensor::expand(ArrayRef<std::size_t>)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorExpand", [](poplar::Tensor& cl, jlcxx::ArrayRef<std::size_t> a) {return cl.expand(jlcxxToPoplar(a));});
}
// poplar::Tensor::squeeze(ArrayRef<std::size_t>)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorSqueeze", [](poplar::Tensor& cl, jlcxx::ArrayRef<std::size_t> a) {return cl.squeeze(jlcxxToPoplar(a));});
}
// poplar::Tensor::transpose()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorTranspose", [](poplar::Tensor& cl) {return cl.transpose();});
}
// poplar::Tensor::subSample(unsigned int, unsigned int)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorSubSample", [](poplar::Tensor& cl, unsigned int a, unsigned int b) {return cl.subSample(a, b);});
}
// poplar::Tensor::upsample(unsigned int, unsigned int, UpsampleMethod)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorUpsample", [](poplar::Tensor& cl, unsigned int a, unsigned int b, UpsampleMethod c) {return cl.upsample(a, b, c);});
}
// poplar::Tensor::broadcast(unsigned int, unsigned int)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorBroadcast", [](poplar::Tensor& cl, unsigned int a, unsigned int b) {return cl.broadcast(a, b);});
}
// poplar::Tensor::reinterpret(const Type &)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorReinterpret", [](poplar::Tensor& cl, const Type & a) {return cl.reinterpret(a);});
}
// poplar::Tensor::reverse(unsigned int)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorReverse", [](poplar::Tensor& cl, unsigned int a) {return cl.reverse(a);});
}
// poplar::Tensor::numElements()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorNumElements", [](poplar::Tensor& cl) {return cl.numElements();});
}
// poplar::Tensor::dim(unsigned int)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorDim", [](poplar::Tensor& cl, unsigned int a) {return cl.dim(a);});
}
// poplar::Tensor::shape()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorShape", [](poplar::Tensor& cl) {return cl.shape();});
}
// poplar::Tensor::rank()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorRank", [](poplar::Tensor& cl) {return cl.rank();});
}
// poplar::Tensor::isContiguous()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorIsContiguous", [](poplar::Tensor& cl) {return cl.isContiguous();});
}
// poplar::Tensor::containsAliases()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorContainsAliases", [](poplar::Tensor& cl) {return cl.containsAliases();});
}
// poplar::Tensor::containsConstant()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorContainsConstant", [](poplar::Tensor& cl) {return cl.containsConstant();});
}
// poplar::Tensor::isParallelWriteable()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorIsParallelWriteable", [](poplar::Tensor& cl) {return cl.isParallelWriteable();});
}
// poplar::Tensor::getContiguousRegions()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorGetContiguousRegions", [](poplar::Tensor& cl) {return cl.getContiguousRegions();});
}
// poplar::Tensor::getVarRegions()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorGetVarRegions", [](poplar::Tensor& cl) {return cl.getVarRegions();});
}
// poplar::Tensor::intersectsWith(const Tensor &)__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorIntersectsWith", [](poplar::Tensor& cl, const Tensor & a) {return cl.intersectsWith(a);});
}
// poplar::Tensor::shapeToString()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorShapeToString", [](poplar::Tensor& cl) {return cl.shapeToString();});
}
// poplar::Tensor::dump()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorDump", [](poplar::Tensor& cl) {return cl.dump();});
}
// poplar::Tensor::dumpRegions()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorDumpRegions", [](poplar::Tensor& cl) {return cl.dumpRegions();});
}
// poplar::Tensor::getVarStr()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorGetVarStr", [](poplar::Tensor& cl) {return cl.getVarStr();});
}
// poplar::Tensor::getDebugStr()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorGetDebugStr", [](poplar::Tensor& cl) {return cl.getDebugStr();});
}
// poplar::Tensor::valid()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorValid", [](poplar::Tensor& cl) {return cl.valid();});
}
// poplar::Tensor::getMetadata()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorGetMetadata", [](poplar::Tensor& cl) {return cl.getMetadata();});
}
// poplar::Tensor::hasMetadata()__CXXMethod
{ using namespace poplar;
JLTensor.method("TensorHasMetadata", [](poplar::Tensor& cl) {return cl.hasMetadata();});
}
// poplar::concat(ArrayRef<Tensor>, unsigned int)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarConcat", [](jlcxx::ArrayRef<Tensor> a, unsigned int b) {return poplar::concat(jlcxxToPoplar(a), b);} ); }
// poplar::concat(const Tensor &, const Tensor &, unsigned int)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarConcat", [](const Tensor & a, const Tensor & b, unsigned int c) {return poplar::concat(a, b, c);} ); }
// poplar::append(const Tensor &, const Tensor &, unsigned int)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarAppend", [](const Tensor & a, const Tensor & b, unsigned int c) {return poplar::append(a, b, c);} ); }
// poplar::append(const Tensor &, const Tensor &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarAppend", [](const Tensor & a, const Tensor & b) {return poplar::append(a, b);} ); }
// poplar::program::Program::Program(const Program &)__CXXConstructor
{ using namespace poplar::program;
JLProgramProgram.constructor<const Program &>();
}
// poplar::program::Program::isEmpty()__CXXMethod
{ using namespace poplar::program;
JLProgramProgram.method("ProgramProgramIsEmpty", [](poplar::program::Program& cl) {return cl.isEmpty();});
}
// poplar::program::Execute::Execute(ComputeSet, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramExecute.constructor<ComputeSet>();
JLProgramExecute.constructor<ComputeSet, const DebugContext &>();
}
// poplar::program::Execute::Execute(ComputeSet, Tensor, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramExecute.constructor<ComputeSet, Tensor>();
JLProgramExecute.constructor<ComputeSet, Tensor, const DebugContext &>();
}
// poplar::program::Sequence::add(const Program &)__CXXMethod
{ using namespace poplar::program;
JLProgramSequence.method("ProgramSequenceAdd", [](poplar::program::Sequence& cl, const Program & a) {return cl.add(a);});
}
// poplar::program::Repeat::Repeat(unsigned int, const Program &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramRepeat.constructor<unsigned int, const Program &>();
JLProgramRepeat.constructor<unsigned int, const Program &, const DebugContext &>();
}
// poplar::program::RepeatWhileFalse::RepeatWhileFalse(const Program &, Tensor, const Program &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramRepeatWhileFalse.constructor<const Program &, Tensor, const Program &>();
JLProgramRepeatWhileFalse.constructor<const Program &, Tensor, const Program &, const DebugContext &>();
}
// poplar::program::RepeatWhileTrue::RepeatWhileTrue(const Program &, Tensor, const Program &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramRepeatWhileTrue.constructor<const Program &, Tensor, const Program &>();
JLProgramRepeatWhileTrue.constructor<const Program &, Tensor, const Program &, const DebugContext &>();
}
// poplar::program::Loop::Loop(const Program &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramLoop.constructor<const Program &>();
JLProgramLoop.constructor<const Program &, const DebugContext &>();
}
// poplar::program::If::If(Tensor, const Program &, const Program &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramIf.constructor<Tensor, const Program &, const Program &>();
JLProgramIf.constructor<Tensor, const Program &, const Program &, const DebugContext &>();
}
// poplar::program::Switch::Switch(Tensor, const std::vector<std::pair<std::int32_t, Program>> &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramSwitch.constructor<Tensor, const std::vector<std::pair<std::int32_t, Program>> &>();
JLProgramSwitch.constructor<Tensor, const std::vector<std::pair<std::int32_t, Program>> &, const DebugContext &>();
}
// poplar::program::Switch::Switch(Tensor, const std::vector<std::pair<std::int32_t, Program>> &, const Program &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramSwitch.constructor<Tensor, const std::vector<std::pair<std::int32_t, Program>> &, const Program &>();
JLProgramSwitch.constructor<Tensor, const std::vector<std::pair<std::int32_t, Program>> &, const Program &, const DebugContext &>();
}
// poplar::program::Switch::Switch(Tensor, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramSwitch.constructor<Tensor>();
JLProgramSwitch.constructor<Tensor, const DebugContext &>();
}
// poplar::program::Switch::Switch(Tensor, const Program &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramSwitch.constructor<Tensor, const Program &>();
JLProgramSwitch.constructor<Tensor, const Program &, const DebugContext &>();
}
// poplar::program::Switch::add(std::int32_t, const Program &)__CXXMethod
{ using namespace poplar::program;
JLProgramSwitch.method("ProgramSwitchAdd", [](poplar::program::Switch& cl, std::int32_t a, const Program & b) {return cl.add(a, b);});
}
// poplar::program::Switch::switchWithBoundsChecking(Tensor, const std::vector<std::pair<std::int32_t, Program>> &, const DebugContext &)__CXXMethod
{ using namespace poplar::program;
JLProgramSwitch.method("ProgramSwitchSwitchWithBoundsChecking", [](poplar::program::Switch& cl, Tensor a, const std::vector<std::pair<std::int32_t, Program>> & b) {return cl.switchWithBoundsChecking(a, b);});
JLProgramSwitch.method("ProgramSwitchSwitchWithBoundsChecking", [](poplar::program::Switch& cl, Tensor a, const std::vector<std::pair<std::int32_t, Program>> & b, const DebugContext & c) {return cl.switchWithBoundsChecking(a, b, c);});
}
// poplar::program::Switch::switchWithUnreachableDefault(Tensor, const DebugContext &)__CXXMethod
{ using namespace poplar::program;
JLProgramSwitch.method("ProgramSwitchSwitchWithUnreachableDefault", [](poplar::program::Switch& cl, Tensor a) {return cl.switchWithUnreachableDefault(a);});
JLProgramSwitch.method("ProgramSwitchSwitchWithUnreachableDefault", [](poplar::program::Switch& cl, Tensor a, const DebugContext & b) {return cl.switchWithUnreachableDefault(a, b);});
}
// poplar::program::Copy::Copy(Tensor, Tensor, bool, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramCopy.constructor<Tensor, Tensor>();
JLProgramCopy.constructor<Tensor, Tensor, bool>();
JLProgramCopy.constructor<Tensor, Tensor, bool, const DebugContext &>();
}
// poplar::program::Copy::Copy(const DataStream &, Tensor, bool, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramCopy.constructor<const DataStream &, Tensor>();
JLProgramCopy.constructor<const DataStream &, Tensor, bool>();
JLProgramCopy.constructor<const DataStream &, Tensor, bool, const DebugContext &>();
}
// poplar::program::Copy::Copy(Tensor, const DataStream &, bool, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramCopy.constructor<Tensor, const DataStream &>();
JLProgramCopy.constructor<Tensor, const DataStream &, bool>();
JLProgramCopy.constructor<Tensor, const DataStream &, bool, const DebugContext &>();
}
// poplar::program::Copy::Copy(const RemoteBuffer &, Tensor, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramCopy.constructor<const RemoteBuffer &, Tensor>();
JLProgramCopy.constructor<const RemoteBuffer &, Tensor, const DebugContext &>();
}
// poplar::program::Copy::Copy(const RemoteBuffer &, Tensor, Tensor, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramCopy.constructor<const RemoteBuffer &, Tensor, Tensor>();
JLProgramCopy.constructor<const RemoteBuffer &, Tensor, Tensor, const DebugContext &>();
}
// poplar::program::Copy::Copy(Tensor, const RemoteBuffer &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramCopy.constructor<Tensor, const RemoteBuffer &>();
JLProgramCopy.constructor<Tensor, const RemoteBuffer &, const DebugContext &>();
}
// poplar::program::Copy::Copy(Tensor, const RemoteBuffer &, Tensor, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramCopy.constructor<Tensor, const RemoteBuffer &, Tensor>();
JLProgramCopy.constructor<Tensor, const RemoteBuffer &, Tensor, const DebugContext &>();
}
// poplar::program::Copy::Copy(const FunctionBuffer &, const Function &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramCopy.constructor<const FunctionBuffer &, const Function &>();
JLProgramCopy.constructor<const FunctionBuffer &, const Function &, const DebugContext &>();
}
// poplar::program::CrossReplicaCopy::CrossReplicaCopy(Tensor, Tensor, std::map<unsigned int, unsigned int>, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramCrossReplicaCopy.constructor<Tensor, Tensor, std::map<unsigned int, unsigned int>>();
JLProgramCrossReplicaCopy.constructor<Tensor, Tensor, std::map<unsigned int, unsigned int>, const DebugContext &>();
}
// poplar::program::WriteUndef::WriteUndef(Tensor, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramWriteUndef.constructor<Tensor>();
JLProgramWriteUndef.constructor<Tensor, const DebugContext &>();
}
// poplar::program::AssumeEqualAcrossReplicas::AssumeEqualAcrossReplicas(Tensor, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramAssumeEqualAcrossReplicas.constructor<Tensor>();
JLProgramAssumeEqualAcrossReplicas.constructor<Tensor, const DebugContext &>();
}
// poplar::program::Block::Block(const Program &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramBlock.constructor<const Program &>();
JLProgramBlock.constructor<const Program &, const DebugContext &>();
}
// poplar::program::Sync::Sync(SyncType, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramSync.constructor<SyncType>();
JLProgramSync.constructor<SyncType, const DebugContext &>();
}
// poplar::program::Call::Call(Function, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramCall.constructor<Function>();
JLProgramCall.constructor<Function, const DebugContext &>();
}
// poplar::program::Call::Call(HostFunction, ArrayRef<Tensor>, ArrayRef<Tensor>, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramCall.constructor<HostFunction, jlcxx::ArrayRef<Tensor>, jlcxx::ArrayRef<Tensor>>();
JLProgramCall.constructor<HostFunction, jlcxx::ArrayRef<Tensor>, jlcxx::ArrayRef<Tensor>, const DebugContext &>();
}
// poplar::program::PrintTensor::PrintTensor(Tensor, const PrintTensorFmt &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramPrintTensor.constructor<Tensor, const PrintTensorFmt &>();
JLProgramPrintTensor.constructor<Tensor, const PrintTensorFmt &, const DebugContext &>();
}
// poplar::program::PrintTensor::PrintTensor(StringRef, Tensor, const PrintTensorFmt &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramPrintTensor.constructor<StringRef, Tensor, const PrintTensorFmt &>();
JLProgramPrintTensor.constructor<StringRef, Tensor, const PrintTensorFmt &, const DebugContext &>();
}
// poplar::program::PrintTensor::PrintTensor(Tensor, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramPrintTensor.constructor<Tensor>();
JLProgramPrintTensor.constructor<Tensor, const DebugContext &>();
}
// poplar::program::PrintTensor::PrintTensor(StringRef, Tensor, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramPrintTensor.constructor<StringRef, Tensor>();
JLProgramPrintTensor.constructor<StringRef, Tensor, const DebugContext &>();
}
// poplar::program::ErrorProgram::ErrorProgram(StringRef, Tensor, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramErrorProgram.constructor<StringRef, Tensor>();
JLProgramErrorProgram.constructor<StringRef, Tensor, const DebugContext &>();
}
// poplar::program::Abort::Abort(const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramAbort.constructor<const DebugContext &>();
}
// poplar::program::Abort::Abort(const std::string &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramAbort.constructor<const std::string &>();
JLProgramAbort.constructor<const std::string &, const DebugContext &>();
}
// poplar::program::AbortOnCondition::AbortOnCondition(Tensor, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramAbortOnCondition.constructor<Tensor>();
JLProgramAbortOnCondition.constructor<Tensor, const DebugContext &>();
}
// poplar::program::AbortOnCondition::AbortOnCondition(Tensor, const std::string &, const DebugContext &)__CXXConstructor
{ using namespace poplar::program;
JLProgramAbortOnCondition.constructor<Tensor, const std::string &>();
JLProgramAbortOnCondition.constructor<Tensor, const std::string &, const DebugContext &>();
}
// poplar::TensorCloneMethod::PRESERVE_ORDER_AND_ALIASES__EnumConstantDecl
mod.set_const("PoplarTensorCloneMethodPoplarPRESERVE_ORDER_AND_ALIASES", poplar::TensorCloneMethod::PRESERVE_ORDER_AND_ALIASES);
// poplar::TensorCloneMethod::CREATE_NEW_ORDER__EnumConstantDecl
mod.set_const("PoplarTensorCloneMethodPoplarCREATE_NEW_ORDER", poplar::TensorCloneMethod::CREATE_NEW_ORDER);
// poplar::TensorCloneMethod::PRESERVE_ORDER_UNLESS_ALIASES__EnumConstantDecl
mod.set_const("PoplarTensorCloneMethodPoplarPRESERVE_ORDER_UNLESS_ALIASES", poplar::TensorCloneMethod::PRESERVE_ORDER_UNLESS_ALIASES);
// poplar::TensorCloneMethod::GATHER_AND_PRESERVE_TILE_ORDER_AND_ALIASES__EnumConstantDecl
mod.set_const("PoplarTensorCloneMethodPoplarGATHER_AND_PRESERVE_TILE_ORDER_AND_ALIASES", poplar::TensorCloneMethod::GATHER_AND_PRESERVE_TILE_ORDER_AND_ALIASES);
// poplar::TensorCloneDuplicationMethod::DUPLICATE_BY_OUTER_DIMENSION__EnumConstantDecl
mod.set_const("PoplarTensorCloneDuplicationMethodPoplarDUPLICATE_BY_OUTER_DIMENSION", poplar::TensorCloneDuplicationMethod::DUPLICATE_BY_OUTER_DIMENSION);
// poplar::TensorCloneDuplicationMethod::DUPLICATE_BY_TILE_CONTIGUOUS_REGION__EnumConstantDecl
mod.set_const("PoplarTensorCloneDuplicationMethodPoplarDUPLICATE_BY_TILE_CONTIGUOUS_REGION", poplar::TensorCloneDuplicationMethod::DUPLICATE_BY_TILE_CONTIGUOUS_REGION);
// poplar::TensorRearranger::TensorRearranger(const TensorRearranger &)__CXXConstructor
{ using namespace poplar;
JLTensorRearranger.constructor<const TensorRearranger &>();
}
// poplar::TensorRearranger::rearrange(const Tensor &)__CXXMethod
{ using namespace poplar;
JLTensorRearranger.method("TensorRearrangerRearrange", [](poplar::TensorRearranger& cl, const Tensor & a) {return cl.rearrange(a);});
}
// poplar::TensorRearranger::undoRearrangement(const Tensor &)__CXXMethod
{ using namespace poplar;
JLTensorRearranger.method("TensorRearrangerUndoRearrangement", [](poplar::TensorRearranger& cl, const Tensor & a) {return cl.undoRearrangement(a);});
}
// poplar::TensorRearranger::rearrange(ArrayRef<Interval>)__CXXMethod
{ using namespace poplar;
JLTensorRearranger.method("TensorRearrangerRearrange", [](poplar::TensorRearranger& cl, jlcxx::ArrayRef<Interval> a) {return cl.rearrange(jlcxxToPoplar(a));});
}
// poplar::TensorRearranger::undoRearrangement(ArrayRef<Interval>)__CXXMethod
{ using namespace poplar;
JLTensorRearranger.method("TensorRearrangerUndoRearrangement", [](poplar::TensorRearranger& cl, jlcxx::ArrayRef<Interval> a) {return cl.undoRearrangement(jlcxxToPoplar(a));});
}
// poplar::TensorRearranger::valid()__CXXMethod
{ using namespace poplar;
JLTensorRearranger.method("TensorRearrangerValid", [](poplar::TensorRearranger& cl) {return cl.valid();});
}
// poplar::VariableMappingMethod::NONE__EnumConstantDecl
mod.set_const("PoplarVariableMappingMethodPoplarNONE", poplar::VariableMappingMethod::NONE);
// poplar::VariableMappingMethod::LINEAR__EnumConstantDecl
mod.set_const("PoplarVariableMappingMethodPoplarLINEAR", poplar::VariableMappingMethod::LINEAR);
// poplar::VariableRef::VariableRef(unsigned int)__CXXConstructor
{ using namespace poplar;
JLVariableRef.constructor<unsigned int>();
}
// poplar::VariableRef::VariableRef(const VariableRef &)__CXXConstructor
{ using namespace poplar;
JLVariableRef.constructor<const VariableRef &>();
}
// poplar::VariableRef::hash()__CXXMethod
{ using namespace poplar;
JLVariableRef.method("VariableRefHash", [](poplar::VariableRef& cl) {return cl.hash();});
}
// poplar::VariableInterval::VariableInterval(VariableRef, Interval)__CXXConstructor
{ using namespace poplar;
JLVariableInterval.constructor<VariableRef, Interval>();
}
// poplar::VariableInterval::VariableInterval(const VariableInterval &)__CXXConstructor
{ using namespace poplar;
JLVariableInterval.constructor<const VariableInterval &>();
}
// poplar::FieldData::rank()__CXXMethod
{ using namespace poplar;
JLFieldData.method("FieldDataRank", [](poplar::FieldData& cl) {return cl.rank();});
}
// poplar::FieldData::size()__CXXMethod
{ using namespace poplar;
JLFieldData.method("FieldDataSize", [](poplar::FieldData& cl) {return cl.size();});
}
// poplar::FieldData::getSizeAtIndex(std::size_t)__CXXMethod
{ using namespace poplar;
JLFieldData.method("FieldDataGetSizeAtIndex", [](poplar::FieldData& cl, std::size_t a) {return cl.getSizeAtIndex(a);});
}
// poplar::FieldData::getProfilerVectorLayout(std::size_t)__CXXMethod
{ using namespace poplar;
JLFieldData.method("FieldDataGetProfilerVectorLayout", [](poplar::FieldData& cl, std::size_t a) {return cl.getProfilerVectorLayout(a);});
}
// poplar::FieldData::getProfilerVectorListLayout()__CXXMethod
{ using namespace poplar;
JLFieldData.method("FieldDataGetProfilerVectorListLayout", [](poplar::FieldData& cl) {return cl.getProfilerVectorListLayout();});
}
// poplar::FieldData::name()__CXXMethod
{ using namespace poplar;
JLFieldData.method("FieldDataName", [](poplar::FieldData& cl) {return cl.name();});
}
// poplar::replication_factor::replication_factor(unsigned int)__CXXConstructor
{ using namespace poplar;
JLReplication_factor.constructor<unsigned int>();
}
// poplar::versionString()__FunctionDecl
{ using namespace poplar;
mod.method("PoplarVersionString", []() {return poplar::versionString();} ); }
// poplar::packageHash()__FunctionDecl
{ using namespace poplar;
mod.method("PoplarPackageHash", []() {return poplar::packageHash();} ); }
// poplar::Graph::Graph(const Target &, replication_factor)__CXXConstructor
{ using namespace poplar;
JLGraph.constructor<const Target &>();
JLGraph.constructor<const Target &, replication_factor>();
}
// poplar::Graph::Graph(const Device &, replication_factor)__CXXConstructor
{ using namespace poplar;
JLGraph.constructor<const Device &>();
JLGraph.constructor<const Device &, replication_factor>();
}
// poplar::Graph::getTarget()__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetTarget", [](poplar::Graph& cl) {return cl.getTarget();});
}
// poplar::Graph::addCodelets(StringRef, CodeletFileType, StringRef, StringRef)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddCodelets", [](poplar::Graph& cl, StringRef a) {return cl.addCodelets(a);});
JLGraph.method("GraphAddCodelets", [](poplar::Graph& cl, StringRef a, CodeletFileType b) {return cl.addCodelets(a, b);});
JLGraph.method("GraphAddCodelets", [](poplar::Graph& cl, StringRef a, CodeletFileType b, StringRef c) {return cl.addCodelets(a, b, c);});
JLGraph.method("GraphAddCodelets", [](poplar::Graph& cl, StringRef a, CodeletFileType b, StringRef c, StringRef d) {return cl.addCodelets(a, b, c, d);});
}
// poplar::Graph::addCodelets(ArrayRef<std::string>, StringRef, StringRef)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddCodelets", [](poplar::Graph& cl, ArrayRef<std::string> a) {return cl.addCodelets(a);});
JLGraph.method("GraphAddCodelets", [](poplar::Graph& cl, ArrayRef<std::string> a, StringRef b) {return cl.addCodelets(a, b);});
JLGraph.method("GraphAddCodelets", [](poplar::Graph& cl, ArrayRef<std::string> a, StringRef b, StringRef c) {return cl.addCodelets(a, b, c);});
}
// poplar::Graph::addCodelets(std::stringstream &, StringRef, CodeletFileType, StringRef)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddCodelets", [](poplar::Graph& cl, std::stringstream & a) {return cl.addCodelets(a);});
JLGraph.method("GraphAddCodelets", [](poplar::Graph& cl, std::stringstream & a, StringRef b) {return cl.addCodelets(a, b);});
JLGraph.method("GraphAddCodelets", [](poplar::Graph& cl, std::stringstream & a, StringRef b, CodeletFileType c) {return cl.addCodelets(a, b, c);});
JLGraph.method("GraphAddCodelets", [](poplar::Graph& cl, std::stringstream & a, StringRef b, CodeletFileType c, StringRef d) {return cl.addCodelets(a, b, c, d);});
}
// poplar::Graph::ConnectionDesc::ConnectionDesc(StringRef, Tensor)__CXXConstructor
{ using namespace poplar;
JLGraphConnectionDesc.constructor<StringRef, Tensor>();
}
// poplar::Graph::ConnectionDesc::ConnectionDesc(StringRef, ArrayRef<Tensor>)__CXXConstructor
{ using namespace poplar;
JLGraphConnectionDesc.constructor<StringRef, jlcxx::ArrayRef<Tensor>>();
}
// poplar::Graph::addVertex(ComputeSet, StringRef)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddVertex", [](poplar::Graph& cl, ComputeSet a, StringRef b) {return cl.addVertex(a, b);});
}
// poplar::Graph::addVertex(ComputeSet, StringRef, ArrayRef<ConnectionDesc>)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddVertex", [](poplar::Graph& cl, ComputeSet a, StringRef b, jlcxx::ArrayRef<ConnectionDesc> c) {return cl.addVertex(a, b, jlcxxToPoplar(c));});
}
// poplar::Graph::addExternalExchangeVertex(ComputeSet, StringRef, unsigned int, bool, bool)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddExternalExchangeVertex", [](poplar::Graph& cl, ComputeSet a, StringRef b, unsigned int c, bool d, bool e) {return cl.addExternalExchangeVertex(a, b, c, d, e);});
}
// poplar::Graph::addVariable(const Type &, ArrayRef<std::size_t>, const DebugContext &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddVariable", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b) {return cl.addVariable(a, jlcxxToPoplar(b));});
JLGraph.method("GraphAddVariable", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, const DebugContext & c) {return cl.addVariable(a, jlcxxToPoplar(b), c);});
}
// poplar::Graph::addVariable(const Type &, const Tensor &, ArrayRef<std::size_t>, const DebugContext &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddVariable", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c) {return cl.addVariable(a, b, jlcxxToPoplar(c));});
JLGraph.method("GraphAddVariable", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, const DebugContext & d) {return cl.addVariable(a, b, jlcxxToPoplar(c), d);});
}
// poplar::Graph::addVariable(const Type &, ArrayRef<std::size_t>, VariableMappingMethod, const DebugContext &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddVariable", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, VariableMappingMethod c) {return cl.addVariable(a, jlcxxToPoplar(b), c);});
JLGraph.method("GraphAddVariable", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, VariableMappingMethod c, const DebugContext & d) {return cl.addVariable(a, jlcxxToPoplar(b), c, d);});
}
// poplar::Graph::addVariable(const Type &, const Tensor &, ArrayRef<std::size_t>, VariableMappingMethod, const DebugContext &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddVariable", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, VariableMappingMethod d) {return cl.addVariable(a, b, jlcxxToPoplar(c), d);});
JLGraph.method("GraphAddVariable", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, VariableMappingMethod d, const DebugContext & e) {return cl.addVariable(a, b, jlcxxToPoplar(c), d, e);});
}
// poplar::Graph::addExternalVariable(const Type &, ArrayRef<std::size_t>, StringRef, const DebugContext &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddExternalVariable", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, StringRef c) {return cl.addExternalVariable(a, jlcxxToPoplar(b), c);});
JLGraph.method("GraphAddExternalVariable", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, StringRef c, const DebugContext & d) {return cl.addExternalVariable(a, jlcxxToPoplar(b), c, d);});
}
// poplar::Graph::addConstant(const Type &, const Tensor &, ArrayRef<std::size_t>, ArrayRef<T>, const DebugContext &)__FunctionTemplate
{ using namespace poplar;
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, jlcxx::ArrayRef<unsigned int> d) {return cl.addConstant(a, b, jlcxxToPoplar(c), jlcxxToPoplar(d));});
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, jlcxx::ArrayRef<unsigned int> d, const DebugContext & e) {return cl.addConstant(a, b, jlcxxToPoplar(c), jlcxxToPoplar(d), e);});
}{ using namespace poplar;
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, jlcxx::ArrayRef<int> d) {return cl.addConstant(a, b, jlcxxToPoplar(c), jlcxxToPoplar(d));});
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, jlcxx::ArrayRef<int> d, const DebugContext & e) {return cl.addConstant(a, b, jlcxxToPoplar(c), jlcxxToPoplar(d), e);});
}{ using namespace poplar;
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, jlcxx::ArrayRef<long> d) {return cl.addConstant(a, b, jlcxxToPoplar(c), jlcxxToPoplar(d));});
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, jlcxx::ArrayRef<long> d, const DebugContext & e) {return cl.addConstant(a, b, jlcxxToPoplar(c), jlcxxToPoplar(d), e);});
}{ using namespace poplar;
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, jlcxx::ArrayRef<float> d) {return cl.addConstant(a, b, jlcxxToPoplar(c), jlcxxToPoplar(d));});
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, jlcxx::ArrayRef<float> d, const DebugContext & e) {return cl.addConstant(a, b, jlcxxToPoplar(c), jlcxxToPoplar(d), e);});
}{ using namespace poplar;
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, jlcxx::ArrayRef<double> d) {return cl.addConstant(a, b, jlcxxToPoplar(c), jlcxxToPoplar(d));});
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, jlcxx::ArrayRef<double> d, const DebugContext & e) {return cl.addConstant(a, b, jlcxxToPoplar(c), jlcxxToPoplar(d), e);});
}
// poplar::Graph::addConstant(const Type &, ArrayRef<std::size_t>, ArrayRef<T>, const DebugContext &)__FunctionTemplate
{ using namespace poplar;
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, jlcxx::ArrayRef<unsigned int> c) {return cl.addConstant(a, jlcxxToPoplar(b), jlcxxToPoplar(c));});
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, jlcxx::ArrayRef<unsigned int> c, const DebugContext & d) {return cl.addConstant(a, jlcxxToPoplar(b), jlcxxToPoplar(c), d);});
}{ using namespace poplar;
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, jlcxx::ArrayRef<int> c) {return cl.addConstant(a, jlcxxToPoplar(b), jlcxxToPoplar(c));});
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, jlcxx::ArrayRef<int> c, const DebugContext & d) {return cl.addConstant(a, jlcxxToPoplar(b), jlcxxToPoplar(c), d);});
}{ using namespace poplar;
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, jlcxx::ArrayRef<long> c) {return cl.addConstant(a, jlcxxToPoplar(b), jlcxxToPoplar(c));});
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, jlcxx::ArrayRef<long> c, const DebugContext & d) {return cl.addConstant(a, jlcxxToPoplar(b), jlcxxToPoplar(c), d);});
}{ using namespace poplar;
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, jlcxx::ArrayRef<float> c) {return cl.addConstant(a, jlcxxToPoplar(b), jlcxxToPoplar(c));});
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, jlcxx::ArrayRef<float> c, const DebugContext & d) {return cl.addConstant(a, jlcxxToPoplar(b), jlcxxToPoplar(c), d);});
}{ using namespace poplar;
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, jlcxx::ArrayRef<double> c) {return cl.addConstant(a, jlcxxToPoplar(b), jlcxxToPoplar(c));});
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, jlcxx::ArrayRef<double> c, const DebugContext & d) {return cl.addConstant(a, jlcxxToPoplar(b), jlcxxToPoplar(c), d);});
}
// poplar::Graph::addConstant(const Type &, ArrayRef<std::size_t>, const void *, const TypeTraits &, bool, const DebugContext &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, const void * c, const TypeTraits & d, bool e) {return cl.addConstant(a, jlcxxToPoplar(b), c, d, e);});
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, const void * c, const TypeTraits & d, bool e, const DebugContext & f) {return cl.addConstant(a, jlcxxToPoplar(b), c, d, e, f);});
}
// poplar::Graph::addConstant(const Type &, const Tensor &, ArrayRef<std::size_t>, const void *, const TypeTraits &, bool, const DebugContext &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, const void * d, const TypeTraits & e, bool f) {return cl.addConstant(a, b, jlcxxToPoplar(c), d, e, f);});
JLGraph.method("GraphAddConstant", [](poplar::Graph& cl, const Type & a, const Tensor & b, jlcxx::ArrayRef<std::size_t> c, const void * d, const TypeTraits & e, bool f, const DebugContext & g) {return cl.addConstant(a, b, jlcxxToPoplar(c), d, e, f, g);});
}
// poplar::Graph::addConstantHalf(const Type &, ArrayRef<std::size_t>, uint16_t, const DebugContext &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddConstantHalf", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, uint16_t c) {return cl.addConstantHalf(a, jlcxxToPoplar(b), c);});
JLGraph.method("GraphAddConstantHalf", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, uint16_t c, const DebugContext & d) {return cl.addConstantHalf(a, jlcxxToPoplar(b), c, d);});
}
// poplar::Graph::addConstantHalf(const Type &, ArrayRef<std::size_t>, const uint16_t *, const DebugContext &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddConstantHalf", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, const uint16_t * c) {return cl.addConstantHalf(a, jlcxxToPoplar(b), c);});
JLGraph.method("GraphAddConstantHalf", [](poplar::Graph& cl, const Type & a, jlcxx::ArrayRef<std::size_t> b, const uint16_t * c, const DebugContext & d) {return cl.addConstantHalf(a, jlcxxToPoplar(b), c, d);});
}
// poplar::Graph::clone(const Type &, const Tensor &, const DebugContext &, TensorCloneMethod)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphClone", [](poplar::Graph& cl, const Type & a, const Tensor & b) {return cl.clone(a, b);});
JLGraph.method("GraphClone", [](poplar::Graph& cl, const Type & a, const Tensor & b, const DebugContext & c) {return cl.clone(a, b, c);});
JLGraph.method("GraphClone", [](poplar::Graph& cl, const Type & a, const Tensor & b, const DebugContext & c, TensorCloneMethod d) {return cl.clone(a, b, c, d);});
}
// poplar::Graph::clone(const Type &, const Tensor &, const Tensor &, const DebugContext &, TensorCloneMethod)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphClone", [](poplar::Graph& cl, const Type & a, const Tensor & b, const Tensor & c) {return cl.clone(a, b, c);});
JLGraph.method("GraphClone", [](poplar::Graph& cl, const Type & a, const Tensor & b, const Tensor & c, const DebugContext & d) {return cl.clone(a, b, c, d);});
JLGraph.method("GraphClone", [](poplar::Graph& cl, const Type & a, const Tensor & b, const Tensor & c, const DebugContext & d, TensorCloneMethod e) {return cl.clone(a, b, c, d, e);});
}
// poplar::Graph::cloneN(const Type &, const Tensor &, std::size_t, const DebugContext &, TensorCloneMethod, TensorCloneDuplicationMethod)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Type & a, const Tensor & b, std::size_t c) {return cl.cloneN(a, b, c);});
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Type & a, const Tensor & b, std::size_t c, const DebugContext & d) {return cl.cloneN(a, b, c, d);});
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Type & a, const Tensor & b, std::size_t c, const DebugContext & d, TensorCloneMethod e) {return cl.cloneN(a, b, c, d, e);});
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Type & a, const Tensor & b, std::size_t c, const DebugContext & d, TensorCloneMethod e, TensorCloneDuplicationMethod f) {return cl.cloneN(a, b, c, d, e, f);});
}
// poplar::Graph::cloneN(const Type &, const Tensor &, const Tensor &, std::size_t, const DebugContext &, TensorCloneMethod, TensorCloneDuplicationMethod)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Type & a, const Tensor & b, const Tensor & c, std::size_t d) {return cl.cloneN(a, b, c, d);});
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Type & a, const Tensor & b, const Tensor & c, std::size_t d, const DebugContext & e) {return cl.cloneN(a, b, c, d, e);});
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Type & a, const Tensor & b, const Tensor & c, std::size_t d, const DebugContext & e, TensorCloneMethod f) {return cl.cloneN(a, b, c, d, e, f);});
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Type & a, const Tensor & b, const Tensor & c, std::size_t d, const DebugContext & e, TensorCloneMethod f, TensorCloneDuplicationMethod g) {return cl.cloneN(a, b, c, d, e, f, g);});
}
// poplar::Graph::clone(const Tensor &, const DebugContext &, TensorCloneMethod)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphClone", [](poplar::Graph& cl, const Tensor & a) {return cl.clone(a);});
JLGraph.method("GraphClone", [](poplar::Graph& cl, const Tensor & a, const DebugContext & b) {return cl.clone(a, b);});
JLGraph.method("GraphClone", [](poplar::Graph& cl, const Tensor & a, const DebugContext & b, TensorCloneMethod c) {return cl.clone(a, b, c);});
}
// poplar::Graph::clone(const Tensor &, const Tensor &, const DebugContext &, TensorCloneMethod)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphClone", [](poplar::Graph& cl, const Tensor & a, const Tensor & b) {return cl.clone(a, b);});
JLGraph.method("GraphClone", [](poplar::Graph& cl, const Tensor & a, const Tensor & b, const DebugContext & c) {return cl.clone(a, b, c);});
JLGraph.method("GraphClone", [](poplar::Graph& cl, const Tensor & a, const Tensor & b, const DebugContext & c, TensorCloneMethod d) {return cl.clone(a, b, c, d);});
}
// poplar::Graph::cloneN(const Tensor &, std::size_t, const DebugContext &, TensorCloneMethod, TensorCloneDuplicationMethod)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Tensor & a, std::size_t b) {return cl.cloneN(a, b);});
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Tensor & a, std::size_t b, const DebugContext & c) {return cl.cloneN(a, b, c);});
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Tensor & a, std::size_t b, const DebugContext & c, TensorCloneMethod d) {return cl.cloneN(a, b, c, d);});
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Tensor & a, std::size_t b, const DebugContext & c, TensorCloneMethod d, TensorCloneDuplicationMethod e) {return cl.cloneN(a, b, c, d, e);});
}
// poplar::Graph::cloneN(const Tensor &, const Tensor &, std::size_t, const DebugContext &, TensorCloneMethod, TensorCloneDuplicationMethod)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Tensor & a, const Tensor & b, std::size_t c) {return cl.cloneN(a, b, c);});
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Tensor & a, const Tensor & b, std::size_t c, const DebugContext & d) {return cl.cloneN(a, b, c, d);});
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Tensor & a, const Tensor & b, std::size_t c, const DebugContext & d, TensorCloneMethod e) {return cl.cloneN(a, b, c, d, e);});
JLGraph.method("GraphCloneN", [](poplar::Graph& cl, const Tensor & a, const Tensor & b, std::size_t c, const DebugContext & d, TensorCloneMethod e, TensorCloneDuplicationMethod f) {return cl.cloneN(a, b, c, d, e, f);});
}
// poplar::Graph::connect(FieldRef, const Tensor &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphConnect", [](poplar::Graph& cl, FieldRef a, const Tensor & b) {return cl.connect(a, b);});
}
// poplar::Graph::connect(FieldRef, T, typename std::enable_if<TypeTraits::isSimpleType<T>()>::type *)__FunctionTemplate
{ using namespace poplar;
JLGraph.method("GraphConnect", [](poplar::Graph& cl, FieldRef a, jlcxx::StrictlyTypedNumber<unsigned int> b) {return cl.connect(a, b.value);});
}{ using namespace poplar;
JLGraph.method("GraphConnect", [](poplar::Graph& cl, FieldRef a, jlcxx::StrictlyTypedNumber<int> b) {return cl.connect(a, b.value);});
}{ using namespace poplar;
JLGraph.method("GraphConnect", [](poplar::Graph& cl, FieldRef a, jlcxx::StrictlyTypedNumber<long> b) {return cl.connect(a, b.value);});
}{ using namespace poplar;
JLGraph.method("GraphConnect", [](poplar::Graph& cl, FieldRef a, jlcxx::StrictlyTypedNumber<float> b) {return cl.connect(a, b.value);});
}{ using namespace poplar;
JLGraph.method("GraphConnect", [](poplar::Graph& cl, FieldRef a, jlcxx::StrictlyTypedNumber<double> b) {return cl.connect(a, b.value);});
}
// poplar::Graph::connect(FieldRef, ArrayRef<Tensor>)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphConnect", [](poplar::Graph& cl, FieldRef a, jlcxx::ArrayRef<Tensor> b) {return cl.connect(a, jlcxxToPoplar(b));});
}
// poplar::Graph::setPerfEstimate(const VertexRef &, std::uint64_t, std::uint64_t)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphSetPerfEstimate", [](poplar::Graph& cl, const VertexRef & a, std::uint64_t b) {return cl.setPerfEstimate(a, b);});
JLGraph.method("GraphSetPerfEstimate", [](poplar::Graph& cl, const VertexRef & a, std::uint64_t b, std::uint64_t c) {return cl.setPerfEstimate(a, b, c);});
}
// poplar::Graph::setPerfEstimate(const VertexRef &, const VertexPerfEstimate &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphSetPerfEstimate", [](poplar::Graph& cl, const VertexRef & a, const VertexPerfEstimate & b) {return cl.setPerfEstimate(a, b);});
}
// poplar::Graph::getPerfEstimate(const VertexRef &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetPerfEstimate", [](poplar::Graph& cl, const VertexRef & a) {return cl.getPerfEstimate(a);});
}
// poplar::Graph::registerPerfEstimator(StringRef, PerfEstimateFunc)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphRegisterPerfEstimator", [](poplar::Graph& cl, StringRef a, PerfEstimateFunc b) {return cl.registerPerfEstimator(a, b);});
}
// poplar::Graph::getNumVertices()__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetNumVertices", [](poplar::Graph& cl) {return cl.getNumVertices();});
}
// poplar::Graph::addComputeSet(const DebugContext &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddComputeSet", [](poplar::Graph& cl) {return cl.addComputeSet();});
JLGraph.method("GraphAddComputeSet", [](poplar::Graph& cl, const DebugContext & a) {return cl.addComputeSet(a);});
}
// poplar::Graph::setFieldSize(FieldRef, std::size_t)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphSetFieldSize", [](poplar::Graph& cl, FieldRef a, std::size_t b) {return cl.setFieldSize(a, b);});
}
// poplar::Graph::getFieldSize(FieldRef)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetFieldSize", [](poplar::Graph& cl, FieldRef a) {return cl.getFieldSize(a);});
}
// poplar::Graph::getMaxFieldDim(StringRef, StringRef, unsigned int)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetMaxFieldDim", [](poplar::Graph& cl, StringRef a, StringRef b, unsigned int c) {return cl.getMaxFieldDim(a, b, c);});
}
// poplar::Graph::getMaxVertexFieldValue(StringRef, StringRef)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetMaxVertexFieldValue", [](poplar::Graph& cl, StringRef a, StringRef b) {return cl.getMaxVertexFieldValue(a, b);});
}
// poplar::Graph::setInitialValueHalf(FieldRef, uint16_t)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphSetInitialValueHalf", [](poplar::Graph& cl, FieldRef a, uint16_t b) {return cl.setInitialValueHalf(a, b);});
}
// poplar::Graph::setInitialValue(FieldRef, ArrayRef<T>)__FunctionTemplate
{ using namespace poplar;
JLGraph.method("GraphSetInitialValue", [](poplar::Graph& cl, FieldRef a, jlcxx::ArrayRef<unsigned int> b) {return cl.setInitialValue(a, jlcxxToPoplar(b));});
}{ using namespace poplar;
JLGraph.method("GraphSetInitialValue", [](poplar::Graph& cl, FieldRef a, jlcxx::ArrayRef<int> b) {return cl.setInitialValue(a, jlcxxToPoplar(b));});
}{ using namespace poplar;
JLGraph.method("GraphSetInitialValue", [](poplar::Graph& cl, FieldRef a, jlcxx::ArrayRef<long> b) {return cl.setInitialValue(a, jlcxxToPoplar(b));});
}{ using namespace poplar;
JLGraph.method("GraphSetInitialValue", [](poplar::Graph& cl, FieldRef a, jlcxx::ArrayRef<float> b) {return cl.setInitialValue(a, jlcxxToPoplar(b));});
}{ using namespace poplar;
JLGraph.method("GraphSetInitialValue", [](poplar::Graph& cl, FieldRef a, jlcxx::ArrayRef<double> b) {return cl.setInitialValue(a, jlcxxToPoplar(b));});
}
// poplar::Graph::setInitialValueHalf(FieldRef, ArrayRef<uint16_t>)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphSetInitialValueHalf", [](poplar::Graph& cl, FieldRef a, jlcxx::ArrayRef<uint16_t> b) {return cl.setInitialValueHalf(a, jlcxxToPoplar(b));});
}
// poplar::Graph::setInitialValue(const Tensor &, const std::map<unsigned int, unsigned int> &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphSetInitialValue", [](poplar::Graph& cl, const Tensor & a, const std::map<unsigned int, unsigned int> & b) {return cl.setInitialValue(a, b);});
}
// poplar::Graph::setInitialValue(const Tensor &, ArrayRef<T>)__FunctionTemplate
{ using namespace poplar;
JLGraph.method("GraphSetInitialValue", [](poplar::Graph& cl, const Tensor & a, jlcxx::ArrayRef<unsigned int> b) {return cl.setInitialValue(a, jlcxxToPoplar(b));});
}{ using namespace poplar;
JLGraph.method("GraphSetInitialValue", [](poplar::Graph& cl, const Tensor & a, jlcxx::ArrayRef<int> b) {return cl.setInitialValue(a, jlcxxToPoplar(b));});
}{ using namespace poplar;
JLGraph.method("GraphSetInitialValue", [](poplar::Graph& cl, const Tensor & a, jlcxx::ArrayRef<long> b) {return cl.setInitialValue(a, jlcxxToPoplar(b));});
}{ using namespace poplar;
JLGraph.method("GraphSetInitialValue", [](poplar::Graph& cl, const Tensor & a, jlcxx::ArrayRef<float> b) {return cl.setInitialValue(a, jlcxxToPoplar(b));});
}{ using namespace poplar;
JLGraph.method("GraphSetInitialValue", [](poplar::Graph& cl, const Tensor & a, jlcxx::ArrayRef<double> b) {return cl.setInitialValue(a, jlcxxToPoplar(b));});
}
// poplar::Graph::setInitialValueHalf(const Tensor &, uint16_t)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphSetInitialValueHalf", [](poplar::Graph& cl, const Tensor & a, uint16_t b) {return cl.setInitialValueHalf(a, b);});
}
// poplar::Graph::setInitialValueHalf(const Tensor &, ArrayRef<uint16_t>)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphSetInitialValueHalf", [](poplar::Graph& cl, const Tensor & a, jlcxx::ArrayRef<uint16_t> b) {return cl.setInitialValueHalf(a, jlcxxToPoplar(b));});
}
// poplar::Graph::createHostWrite(StringRef, const Tensor &, bool)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphCreateHostWrite", [](poplar::Graph& cl, StringRef a, const Tensor & b) {return cl.createHostWrite(a, b);});
JLGraph.method("GraphCreateHostWrite", [](poplar::Graph& cl, StringRef a, const Tensor & b, bool c) {return cl.createHostWrite(a, b, c);});
}
// poplar::Graph::createHostRead(StringRef, const Tensor &, bool)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphCreateHostRead", [](poplar::Graph& cl, StringRef a, const Tensor & b) {return cl.createHostRead(a, b);});
JLGraph.method("GraphCreateHostRead", [](poplar::Graph& cl, StringRef a, const Tensor & b, bool c) {return cl.createHostRead(a, b, c);});
}
// poplar::Graph::addHostToDeviceFIFO(StringRef, const Type &, std::size_t, ReplicatedStreamMode, const OptionFlags &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddHostToDeviceFIFO", [](poplar::Graph& cl, StringRef a, const Type & b, std::size_t c) {return cl.addHostToDeviceFIFO(a, b, c);});
JLGraph.method("GraphAddHostToDeviceFIFO", [](poplar::Graph& cl, StringRef a, const Type & b, std::size_t c, ReplicatedStreamMode d) {return cl.addHostToDeviceFIFO(a, b, c, d);});
JLGraph.method("GraphAddHostToDeviceFIFO", [](poplar::Graph& cl, StringRef a, const Type & b, std::size_t c, ReplicatedStreamMode d, const OptionFlags & e) {return cl.addHostToDeviceFIFO(a, b, c, d, e);});
}
// poplar::Graph::addDeviceToHostFIFO(StringRef, const Type &, std::size_t, const OptionFlags &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddDeviceToHostFIFO", [](poplar::Graph& cl, StringRef a, const Type & b, std::size_t c) {return cl.addDeviceToHostFIFO(a, b, c);});
JLGraph.method("GraphAddDeviceToHostFIFO", [](poplar::Graph& cl, StringRef a, const Type & b, std::size_t c, const OptionFlags & d) {return cl.addDeviceToHostFIFO(a, b, c, d);});
}
// poplar::Graph::addRemoteBuffer(StringRef, const Type &, std::size_t, std::size_t, bool, bool)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddRemoteBuffer", [](poplar::Graph& cl, StringRef a, const Type & b, std::size_t c) {return cl.addRemoteBuffer(a, b, c);});
JLGraph.method("GraphAddRemoteBuffer", [](poplar::Graph& cl, StringRef a, const Type & b, std::size_t c, std::size_t d) {return cl.addRemoteBuffer(a, b, c, d);});
JLGraph.method("GraphAddRemoteBuffer", [](poplar::Graph& cl, StringRef a, const Type & b, std::size_t c, std::size_t d, bool e) {return cl.addRemoteBuffer(a, b, c, d, e);});
JLGraph.method("GraphAddRemoteBuffer", [](poplar::Graph& cl, StringRef a, const Type & b, std::size_t c, std::size_t d, bool e, bool f) {return cl.addRemoteBuffer(a, b, c, d, e, f);});
}
// poplar::Graph::setTileMapping(VertexRef, unsigned int)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphSetTileMapping", [](poplar::Graph& cl, VertexRef a, unsigned int b) {return cl.setTileMapping(a, b);});
}
// poplar::Graph::setTileMapping(const Tensor &, unsigned int)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphSetTileMapping", [](poplar::Graph& cl, const Tensor & a, unsigned int b) {return cl.setTileMapping(a, b);});
}
// poplar::Graph::getTileMapping(const Tensor &, bool, bool)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetTileMapping", [](poplar::Graph& cl, const Tensor & a) {return cl.getTileMapping(a);});
JLGraph.method("GraphGetTileMapping", [](poplar::Graph& cl, const Tensor & a, bool b) {return cl.getTileMapping(a, b);});
JLGraph.method("GraphGetTileMapping", [](poplar::Graph& cl, const Tensor & a, bool b, bool c) {return cl.getTileMapping(a, b, c);});
}
// poplar::Graph::getTileMapping(const Tensor &, bool *, bool)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetTileMapping", [](poplar::Graph& cl, const Tensor & a, bool * b) {return cl.getTileMapping(a, b);});
JLGraph.method("GraphGetTileMapping", [](poplar::Graph& cl, const Tensor & a, bool * b, bool c) {return cl.getTileMapping(a, b, c);});
}
// poplar::Graph::getVariableTileMapping(const Tensor &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetVariableTileMapping", [](poplar::Graph& cl, const Tensor & a) {return cl.getVariableTileMapping(a);});
}
// poplar::Graph::setTileMapping(const Tensor &, const TileToTensorMapping &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphSetTileMapping", [](poplar::Graph& cl, const Tensor & a, const TileToTensorMapping & b) {return cl.setTileMapping(a, b);});
}
// poplar::Graph::getVariable(VariableRef)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetVariable", [](poplar::Graph& cl, VariableRef a) {return cl.getVariable(a);});
}
// poplar::Graph::isConstant(VariableRef)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphIsConstant", [](poplar::Graph& cl, VariableRef a) {return cl.isConstant(a);});
}
// poplar::Graph::getSortedContiguousRegions(const Tensor &, ArrayRef<Interval>, bool, std::vector<std::size_t> *)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetSortedContiguousRegions", [](poplar::Graph& cl, const Tensor & a, jlcxx::ArrayRef<Interval> b) {return cl.getSortedContiguousRegions(a, jlcxxToPoplar(b));});
JLGraph.method("GraphGetSortedContiguousRegions", [](poplar::Graph& cl, const Tensor & a, jlcxx::ArrayRef<Interval> b, bool c) {return cl.getSortedContiguousRegions(a, jlcxxToPoplar(b), c);});
JLGraph.method("GraphGetSortedContiguousRegions", [](poplar::Graph& cl, const Tensor & a, jlcxx::ArrayRef<Interval> b, bool c, std::vector<std::size_t> * d) {return cl.getSortedContiguousRegions(a, jlcxxToPoplar(b), c, d);});
}
// poplar::Graph::reorderToSimplify(Tensor *, ArrayRef<Tensor *>, bool)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphReorderToSimplify", [](poplar::Graph& cl, Tensor * a, jlcxx::ArrayRef<Tensor *> b) {return cl.reorderToSimplify(a, jlcxxToPoplar(b));});
JLGraph.method("GraphReorderToSimplify", [](poplar::Graph& cl, Tensor * a, jlcxx::ArrayRef<Tensor *> b, bool c) {return cl.reorderToSimplify(a, jlcxxToPoplar(b), c);});
}
// poplar::Graph::getSimplifyingRearranger(const Tensor &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetSimplifyingRearranger", [](poplar::Graph& cl, const Tensor & a) {return cl.getSimplifyingRearranger(a);});
}
// poplar::Graph::findUnbroadcastTensor(const Tensor &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphFindUnbroadcastTensor", [](poplar::Graph& cl, const Tensor & a) {return cl.findUnbroadcastTensor(a);});
}
// poplar::Graph::createVirtualGraph(unsigned int)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphCreateVirtualGraph", [](poplar::Graph& cl, unsigned int a) {return cl.createVirtualGraph(a);});
}
// poplar::Graph::createVirtualGraph(unsigned int, unsigned int)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphCreateVirtualGraph", [](poplar::Graph& cl, unsigned int a, unsigned int b) {return cl.createVirtualGraph(a, b);});
}
// poplar::Graph::createVirtualGraph(const std::vector<unsigned int> &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphCreateVirtualGraph", [](poplar::Graph& cl, const std::vector<unsigned int> & a) {return cl.createVirtualGraph(a);});
}
// poplar::Graph::getTopLevelGraph()__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetTopLevelGraph", [](poplar::Graph& cl) {return cl.getTopLevelGraph();});
}
// poplar::Graph::getReplicationFactor()__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetReplicationFactor", [](poplar::Graph& cl) {return cl.getReplicationFactor();});
}
// poplar::Graph::addReplicationIndexConstant(const DebugContext &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddReplicationIndexConstant", [](poplar::Graph& cl) {return cl.addReplicationIndexConstant();});
JLGraph.method("GraphAddReplicationIndexConstant", [](poplar::Graph& cl, const DebugContext & a) {return cl.addReplicationIndexConstant(a);});
}
// poplar::Graph::addFunction(const program::Program &)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddFunction", [](poplar::Graph& cl, const program::Program & a) {return cl.addFunction(a);});
}
// poplar::Graph::addFunctionBuffer(const Function &, FunctionBufferMappingType)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddFunctionBuffer", [](poplar::Graph& cl, const Function & a, FunctionBufferMappingType b) {return cl.addFunctionBuffer(a, b);});
}
// poplar::Graph::addHostFunction(StringRef, ArrayRef<HostFunctionArgument>, ArrayRef<HostFunctionArgument>)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphAddHostFunction", [](poplar::Graph& cl, StringRef a, jlcxx::ArrayRef<HostFunctionArgument> b, jlcxx::ArrayRef<HostFunctionArgument> c) {return cl.addHostFunction(a, jlcxxToPoplar(b), jlcxxToPoplar(c));});
}
// poplar::Graph::convertTileToTopLevelGraphTile(unsigned int)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphConvertTileToTopLevelGraphTile", [](poplar::Graph& cl, unsigned int a) {return cl.convertTileToTopLevelGraphTile(a);});
}
// poplar::Graph::convertTopLevelGraphTileToTile(unsigned int)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphConvertTopLevelGraphTileToTile", [](poplar::Graph& cl, unsigned int a) {return cl.convertTopLevelGraphTileToTile(a);});
}
// poplar::Graph::convertVirtualTileToPhysicalTile(unsigned int)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphConvertVirtualTileToPhysicalTile", [](poplar::Graph& cl, unsigned int a) {return cl.convertVirtualTileToPhysicalTile(a);});
}
// poplar::Graph::convertPhysicalTileToVirtualTile(unsigned int)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphConvertPhysicalTileToVirtualTile", [](poplar::Graph& cl, unsigned int a) {return cl.convertPhysicalTileToVirtualTile(a);});
}
// poplar::Graph::convertPhysicalTileToVirtualTile(unsigned int, unsigned int)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphConvertPhysicalTileToVirtualTile", [](poplar::Graph& cl, unsigned int a, unsigned int b) {return cl.convertPhysicalTileToVirtualTile(a, b);});
}
// poplar::Graph::hasCodelet(StringRef)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphHasCodelet", [](poplar::Graph& cl, StringRef a) {return cl.hasCodelet(a);});
}
// poplar::Graph::getMaxVertexFieldValueAs<>(StringRef, StringRef)__CXXMethod
{ using namespace poplar;
JLGraph.method("GraphGetMaxVertexFieldValueAs<>", [](poplar::Graph& cl, StringRef a, StringRef b) {return cl.getMaxVertexFieldValueAs<>(a, b);});
}
// poplar::RuntimeOptions::RuntimeOptions(const OptionFlags &)__CXXConstructor
{ using namespace poplar;
JLRuntimeOptions.constructor<const OptionFlags &>();
}
// poplar::RuntimeOptions::RuntimeOptions(const RuntimeOptions &)__CXXConstructor
{ using namespace poplar;
JLRuntimeOptions.constructor<const RuntimeOptions &>();
}
// poplar::StreamCallbackBase::Result::Success__EnumConstantDecl
mod.set_const("StreamCallbackBaseResultStreamCallbackBaseSuccess", poplar::StreamCallbackBase::Result::Success);
// poplar::StreamCallbackBase::Result::NotAvailable__EnumConstantDecl
mod.set_const("StreamCallbackBaseResultStreamCallbackBaseNotAvailable", poplar::StreamCallbackBase::Result::NotAvailable);
// poplar::StreamCallbackBase::complete()__CXXMethod
{ using namespace poplar;
JLStreamCallbackBase.method("StreamCallbackBaseComplete", [](poplar::StreamCallbackBase& cl) {return cl.complete();});
}
// poplar::StreamCallbackBase::invalidatePrefetched()__CXXMethod
{ using namespace poplar;
JLStreamCallbackBase.method("StreamCallbackBaseInvalidatePrefetched", [](poplar::StreamCallbackBase& cl) {return cl.invalidatePrefetched();});
}
// poplar::StreamCallback::prefetch(void *)__CXXMethod
{ using namespace poplar;
JLStreamCallback.method("StreamCallbackPrefetch", [](poplar::StreamCallback& cl, void * a) {return cl.prefetch(a);});
}
// poplar::StreamCallback::fetch(void *)__CXXMethod
{ using namespace poplar;
JLStreamCallback.method("StreamCallbackFetch", [](poplar::StreamCallback& cl, void * a) {return cl.fetch(a);});
}
// poplar::StreamCallbackWithMetadata::getMetadata()__CXXMethod
{ using namespace poplar;
JLStreamCallbackWithMetadata.method("StreamCallbackWithMetadataGetMetadata", [](poplar::StreamCallbackWithMetadata& cl) {return cl.getMetadata();});
}
// poplar::ResumableStreamCallback::notify()__CXXMethod
{ using namespace poplar;
JLResumableStreamCallback.method("ResumableStreamCallbackNotify", [](poplar::ResumableStreamCallback& cl) {return cl.notify();});
}
// poplar::ResumableStreamCallback::isAwaiting()__CXXMethod
{ using namespace poplar;
JLResumableStreamCallback.method("ResumableStreamCallbackIsAwaiting", [](poplar::ResumableStreamCallback& cl) {return cl.isAwaiting();});
}
// poplar::LegacyStreamCallback::prefetch(void *)__CXXMethod
{ using namespace poplar;
JLLegacyStreamCallback.method("LegacyStreamCallbackPrefetch", [](poplar::LegacyStreamCallback& cl, void * a) {return cl.prefetch(a);});
}
// poplar::LegacyStreamCallback::invalidatePrefetched()__CXXMethod
{ using namespace poplar;
JLLegacyStreamCallback.method("LegacyStreamCallbackInvalidatePrefetched", [](poplar::LegacyStreamCallback& cl) {return cl.invalidatePrefetched();});
}
// poplar::LegacyStreamCallback::complete()__CXXMethod
{ using namespace poplar;
JLLegacyStreamCallback.method("LegacyStreamCallbackComplete", [](poplar::LegacyStreamCallback& cl) {return cl.complete();});
}
// poplar::Engine::Engine(const Graph &, ArrayRef<program::Program>, const OptionFlags &, ProgressFunc, const DebugContext &)__CXXConstructor
{ using namespace poplar;
JLEngine.constructor<const Graph &, ArrayRef<program::Program>>();
JLEngine.constructor<const Graph &, ArrayRef<program::Program>, const OptionFlags &>();
JLEngine.constructor<const Graph &, ArrayRef<program::Program>, const OptionFlags &, ProgressFunc>();
JLEngine.constructor<const Graph &, ArrayRef<program::Program>, const OptionFlags &, ProgressFunc, const DebugContext &>();
}
// poplar::Engine::Engine(const Graph &, program::Program, const OptionFlags &, ProgressFunc, const DebugContext &)__CXXConstructor
{ using namespace poplar;
JLEngine.constructor<const Graph &, program::Program>();
JLEngine.constructor<const Graph &, program::Program, const OptionFlags &>();
JLEngine.constructor<const Graph &, program::Program, const OptionFlags &, ProgressFunc>();
JLEngine.constructor<const Graph &, program::Program, const OptionFlags &, ProgressFunc, const DebugContext &>();
}
// poplar::Engine::Engine(const Executable &, const OptionFlags &)__CXXConstructor
{ using namespace poplar;
JLEngine.constructor<const Executable &>();
JLEngine.constructor<const Executable &, const OptionFlags &>();
}
// poplar::Engine::prepare(const Device &)__CXXMethod
{ using namespace poplar;
JLEngine.method("EnginePrepare", [](poplar::Engine& cl, const Device & a) {return cl.prepare(a);});
}
// poplar::Engine::prepare(const Device &, const RuntimeOptions &)__CXXMethod
{ using namespace poplar;
JLEngine.method("EnginePrepare", [](poplar::Engine& cl, const Device & a, const RuntimeOptions & b) {return cl.prepare(a, b);});
}
// poplar::Engine::deploy()__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineDeploy", [](poplar::Engine& cl) {return cl.deploy();});
}
// poplar::Engine::load(const Device &)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineLoad", [](poplar::Engine& cl, const Device & a) {return cl.load(a);});
}
// poplar::Engine::run(unsigned int, const std::string &)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineRun", [](poplar::Engine& cl) {return cl.run();});
JLEngine.method("EngineRun", [](poplar::Engine& cl, unsigned int a) {return cl.run(a);});
JLEngine.method("EngineRun", [](poplar::Engine& cl, unsigned int a, const std::string & b) {return cl.run(a, b);});
}
// poplar::Engine::stop()__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineStop", [](poplar::Engine& cl) {return cl.stop();});
}
// poplar::Engine::run(unsigned int, const std::string &, const RuntimeOptions &)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineRun", [](poplar::Engine& cl, unsigned int a, const std::string & b, const RuntimeOptions & c) {return cl.run(a, b, c);});
}
// poplar::Engine::loadAndRun(const Device &, unsigned int)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineLoadAndRun", [](poplar::Engine& cl, const Device & a) {return cl.loadAndRun(a);});
JLEngine.method("EngineLoadAndRun", [](poplar::Engine& cl, const Device & a, unsigned int b) {return cl.loadAndRun(a, b);});
}
// poplar::Engine::getTimeStamp()__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineGetTimeStamp", [](poplar::Engine& cl) {return cl.getTimeStamp();});
}
// poplar::Engine::reportTiming(const TimerTimePoint &, const TimerTimePoint &)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineReportTiming", [](poplar::Engine& cl, const TimerTimePoint & a, const TimerTimePoint & b) {return cl.reportTiming(a, b);});
}
// poplar::Engine::resetExecutionProfile()__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineResetExecutionProfile", [](poplar::Engine& cl) {return cl.resetExecutionProfile();});
}
// poplar::Engine::disableExecutionProfiling()__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineDisableExecutionProfiling", [](poplar::Engine& cl) {return cl.disableExecutionProfiling();});
}
// poplar::Engine::enableExecutionProfiling()__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineEnableExecutionProfiling", [](poplar::Engine& cl) {return cl.enableExecutionProfiling();});
}
// poplar::Engine::readTensor(StringRef, void *, void *)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineReadTensor", [](poplar::Engine& cl, StringRef a, void * b, void * c) {return cl.readTensor(a, b, c);});
}
// poplar::Engine::readTensor(StringRef, gccs::ArrayRef<T>)__FunctionTemplate
{ using namespace poplar;
JLEngine.method("EngineReadTensor", [](poplar::Engine& cl, StringRef a, gccs::ArrayRef<unsigned int> b) {return cl.readTensor(a, b);});
}{ using namespace poplar;
JLEngine.method("EngineReadTensor", [](poplar::Engine& cl, StringRef a, gccs::ArrayRef<int> b) {return cl.readTensor(a, b);});
}{ using namespace poplar;
JLEngine.method("EngineReadTensor", [](poplar::Engine& cl, StringRef a, gccs::ArrayRef<long> b) {return cl.readTensor(a, b);});
}{ using namespace poplar;
JLEngine.method("EngineReadTensor", [](poplar::Engine& cl, StringRef a, gccs::ArrayRef<float> b) {return cl.readTensor(a, b);});
}
// poplar::Engine::writeTensor(StringRef, const void *, const void *)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineWriteTensor", [](poplar::Engine& cl, StringRef a, const void * b, const void * c) {return cl.writeTensor(a, b, c);});
}
// poplar::Engine::writeTensor(StringRef, ArrayRef<T>)__FunctionTemplate
{ using namespace poplar;
JLEngine.method("EngineWriteTensor", [](poplar::Engine& cl, StringRef a, jlcxx::ArrayRef<unsigned int> b) {return cl.writeTensor(a, jlcxxToPoplar(b));});
}{ using namespace poplar;
JLEngine.method("EngineWriteTensor", [](poplar::Engine& cl, StringRef a, jlcxx::ArrayRef<int> b) {return cl.writeTensor(a, jlcxxToPoplar(b));});
}{ using namespace poplar;
JLEngine.method("EngineWriteTensor", [](poplar::Engine& cl, StringRef a, jlcxx::ArrayRef<long> b) {return cl.writeTensor(a, jlcxxToPoplar(b));});
}{ using namespace poplar;
JLEngine.method("EngineWriteTensor", [](poplar::Engine& cl, StringRef a, jlcxx::ArrayRef<float> b) {return cl.writeTensor(a, jlcxxToPoplar(b));});
}
// poplar::Engine::connectStream(StringRef, void *, void *)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineConnectStream", [](poplar::Engine& cl, StringRef a, void * b, void * c) {return cl.connectStream(a, b, c);});
}
// poplar::Engine::connectStream(StringRef, const gccs::ArrayRef<T> &)__FunctionTemplate
{ using namespace poplar;
JLEngine.method("EngineConnectStream", [](poplar::Engine& cl, StringRef a, const gccs::ArrayRef<unsigned int> & b) {return cl.connectStream(a, b);});
}{ using namespace poplar;
JLEngine.method("EngineConnectStream", [](poplar::Engine& cl, StringRef a, const gccs::ArrayRef<int> & b) {return cl.connectStream(a, b);});
}{ using namespace poplar;
JLEngine.method("EngineConnectStream", [](poplar::Engine& cl, StringRef a, const gccs::ArrayRef<long> & b) {return cl.connectStream(a, b);});
}{ using namespace poplar;
JLEngine.method("EngineConnectStream", [](poplar::Engine& cl, StringRef a, const gccs::ArrayRef<float> & b) {return cl.connectStream(a, b);});
}
// poplar::Engine::connectStream(StringRef, void *)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineConnectStream", [](poplar::Engine& cl, StringRef a, void * b) {return cl.connectStream(a, b);});
}
// poplar::Engine::copyFromRemoteBuffer(StringRef, void *, uint64_t, unsigned int)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineCopyFromRemoteBuffer", [](poplar::Engine& cl, StringRef a, void * b, uint64_t c) {return cl.copyFromRemoteBuffer(a, b, c);});
JLEngine.method("EngineCopyFromRemoteBuffer", [](poplar::Engine& cl, StringRef a, void * b, uint64_t c, unsigned int d) {return cl.copyFromRemoteBuffer(a, b, c, d);});
}
// poplar::Engine::copyFromRemoteBuffer(StringRef, gccs::ArrayRef<T>, uint64_t, unsigned int)__FunctionTemplate
{ using namespace poplar;
JLEngine.method("EngineCopyFromRemoteBuffer", [](poplar::Engine& cl, StringRef a, gccs::ArrayRef<unsigned int> b, uint64_t c) {return cl.copyFromRemoteBuffer(a, b, c);});
JLEngine.method("EngineCopyFromRemoteBuffer", [](poplar::Engine& cl, StringRef a, gccs::ArrayRef<unsigned int> b, uint64_t c, unsigned int d) {return cl.copyFromRemoteBuffer(a, b, c, d);});
}{ using namespace poplar;
JLEngine.method("EngineCopyFromRemoteBuffer", [](poplar::Engine& cl, StringRef a, gccs::ArrayRef<int> b, uint64_t c) {return cl.copyFromRemoteBuffer(a, b, c);});
JLEngine.method("EngineCopyFromRemoteBuffer", [](poplar::Engine& cl, StringRef a, gccs::ArrayRef<int> b, uint64_t c, unsigned int d) {return cl.copyFromRemoteBuffer(a, b, c, d);});
}{ using namespace poplar;
JLEngine.method("EngineCopyFromRemoteBuffer", [](poplar::Engine& cl, StringRef a, gccs::ArrayRef<long> b, uint64_t c) {return cl.copyFromRemoteBuffer(a, b, c);});
JLEngine.method("EngineCopyFromRemoteBuffer", [](poplar::Engine& cl, StringRef a, gccs::ArrayRef<long> b, uint64_t c, unsigned int d) {return cl.copyFromRemoteBuffer(a, b, c, d);});
}{ using namespace poplar;
JLEngine.method("EngineCopyFromRemoteBuffer", [](poplar::Engine& cl, StringRef a, gccs::ArrayRef<float> b, uint64_t c) {return cl.copyFromRemoteBuffer(a, b, c);});
JLEngine.method("EngineCopyFromRemoteBuffer", [](poplar::Engine& cl, StringRef a, gccs::ArrayRef<float> b, uint64_t c, unsigned int d) {return cl.copyFromRemoteBuffer(a, b, c, d);});
}
// poplar::Engine::copyToRemoteBuffer(void *, StringRef, uint64_t, unsigned int)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineCopyToRemoteBuffer", [](poplar::Engine& cl, void * a, StringRef b, uint64_t c) {return cl.copyToRemoteBuffer(a, b, c);});
JLEngine.method("EngineCopyToRemoteBuffer", [](poplar::Engine& cl, void * a, StringRef b, uint64_t c, unsigned int d) {return cl.copyToRemoteBuffer(a, b, c, d);});
}
// poplar::Engine::copyToRemoteBuffer(ArrayRef<T>, StringRef, uint64_t, unsigned int)__FunctionTemplate
{ using namespace poplar;
JLEngine.method("EngineCopyToRemoteBuffer", [](poplar::Engine& cl, jlcxx::ArrayRef<unsigned int> a, StringRef b, uint64_t c) {return cl.copyToRemoteBuffer(jlcxxToPoplar(a), b, c);});
JLEngine.method("EngineCopyToRemoteBuffer", [](poplar::Engine& cl, jlcxx::ArrayRef<unsigned int> a, StringRef b, uint64_t c, unsigned int d) {return cl.copyToRemoteBuffer(jlcxxToPoplar(a), b, c, d);});
}{ using namespace poplar;
JLEngine.method("EngineCopyToRemoteBuffer", [](poplar::Engine& cl, jlcxx::ArrayRef<int> a, StringRef b, uint64_t c) {return cl.copyToRemoteBuffer(jlcxxToPoplar(a), b, c);});
JLEngine.method("EngineCopyToRemoteBuffer", [](poplar::Engine& cl, jlcxx::ArrayRef<int> a, StringRef b, uint64_t c, unsigned int d) {return cl.copyToRemoteBuffer(jlcxxToPoplar(a), b, c, d);});
}{ using namespace poplar;
JLEngine.method("EngineCopyToRemoteBuffer", [](poplar::Engine& cl, jlcxx::ArrayRef<long> a, StringRef b, uint64_t c) {return cl.copyToRemoteBuffer(jlcxxToPoplar(a), b, c);});
JLEngine.method("EngineCopyToRemoteBuffer", [](poplar::Engine& cl, jlcxx::ArrayRef<long> a, StringRef b, uint64_t c, unsigned int d) {return cl.copyToRemoteBuffer(jlcxxToPoplar(a), b, c, d);});
}{ using namespace poplar;
JLEngine.method("EngineCopyToRemoteBuffer", [](poplar::Engine& cl, jlcxx::ArrayRef<float> a, StringRef b, uint64_t c) {return cl.copyToRemoteBuffer(jlcxxToPoplar(a), b, c);});
JLEngine.method("EngineCopyToRemoteBuffer", [](poplar::Engine& cl, jlcxx::ArrayRef<float> a, StringRef b, uint64_t c, unsigned int d) {return cl.copyToRemoteBuffer(jlcxxToPoplar(a), b, c, d);});
}{ using namespace poplar;
JLEngine.method("EngineCopyToRemoteBuffer", [](poplar::Engine& cl, jlcxx::ArrayRef<double> a, StringRef b, uint64_t c) {return cl.copyToRemoteBuffer(jlcxxToPoplar(a), b, c);});
JLEngine.method("EngineCopyToRemoteBuffer", [](poplar::Engine& cl, jlcxx::ArrayRef<double> a, StringRef b, uint64_t c, unsigned int d) {return cl.copyToRemoteBuffer(jlcxxToPoplar(a), b, c, d);});
}
// poplar::Engine::listStreams()__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineListStreams", [](poplar::Engine& cl) {return cl.listStreams();});
}
// poplar::Engine::getEngineOptions()__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineGetEngineOptions", [](poplar::Engine& cl) {return cl.getEngineOptions();});
}
// poplar::Engine::insertSimulatedError(ErrorCode, const ErrorLocation &)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineInsertSimulatedError", [](poplar::Engine& cl, ErrorCode a, const ErrorLocation & b) {return cl.insertSimulatedError(a, b);});
}
// poplar::Engine::eraseSimulatedError(const ErrorLocation &)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineEraseSimulatedError", [](poplar::Engine& cl, const ErrorLocation & a) {return cl.eraseSimulatedError(a);});
}
// poplar::Engine::clearSimulatedErrors()__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineClearSimulatedErrors", [](poplar::Engine& cl) {return cl.clearSimulatedErrors();});
}
// poplar::Engine::getSimulatedErrorLocations(unsigned int, unsigned int)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineGetSimulatedErrorLocations", [](poplar::Engine& cl, unsigned int a) {return cl.getSimulatedErrorLocations(a);});
JLEngine.method("EngineGetSimulatedErrorLocations", [](poplar::Engine& cl, unsigned int a, unsigned int b) {return cl.getSimulatedErrorLocations(a, b);});
}
// poplar::Engine::getSimulatedErrorLocations(StringRef, unsigned int)__CXXMethod
{ using namespace poplar;
JLEngine.method("EngineGetSimulatedErrorLocations", [](poplar::Engine& cl, StringRef a) {return cl.getSimulatedErrorLocations(a);});
JLEngine.method("EngineGetSimulatedErrorLocations", [](poplar::Engine& cl, StringRef a, unsigned int b) {return cl.getSimulatedErrorLocations(a, b);});
}
// poplar::compileGraph(const Graph &, ArrayRef<program::Program>, const OptionFlags &, ProgressFunc, const DebugContext &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarCompileGraph", [](const Graph & a, ArrayRef<program::Program> b, const OptionFlags & c, ProgressFunc d, const DebugContext & e) {return poplar::compileGraph(a, b, c, d, e);} ); }
// poplar::compileGraph(const Graph &, ArrayRef<program::Program>, bool, const OptionFlags &, ProgressFunc, const DebugContext &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarCompileGraph", [](const Graph & a, ArrayRef<program::Program> b, bool c, const OptionFlags & d, ProgressFunc e, const DebugContext & f) {return poplar::compileGraph(a, b, c, d, e, f);} ); }
// poplar::compileModule(const Graph &, program::Program, const OptionFlags &, ProgressFunc, const DebugContext &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarCompileModule", [](const Graph & a, program::Program b, const OptionFlags & c, ProgressFunc d, const DebugContext & e) {return poplar::compileModule(a, b, c, d, e);} ); }
// poplar::compileModule(const Graph &, program::Program, const Preallocations &, const OptionFlags &, ProgressFunc, const DebugContext &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarCompileModule", [](const Graph & a, program::Program b, const Preallocations & c, const OptionFlags & d, ProgressFunc e, const DebugContext & f) {return poplar::compileModule(a, b, c, d, e, f);} ); }
// poplar::compileGraph(const Graph &, ArrayRef<program::Program>, const Preallocations &, const OptionFlags &, ProgressFunc, const DebugContext &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarCompileGraph", [](const Graph & a, ArrayRef<program::Program> b, const Preallocations & c, const OptionFlags & d, ProgressFunc e, const DebugContext & f) {return poplar::compileGraph(a, b, c, d, e, f);} ); }
// poplar::compileGraph(const Graph &, ArrayRef<program::Program>, const Preallocations &, bool, const OptionFlags &, ProgressFunc, const DebugContext &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarCompileGraph", [](const Graph & a, ArrayRef<program::Program> b, const Preallocations & c, bool d, const OptionFlags & e, ProgressFunc f, const DebugContext & g) {return poplar::compileGraph(a, b, c, d, e, f, g);} ); }
// poplar::FloatingPointBehaviour::FloatingPointBehaviour(bool, bool, bool, bool, bool)__CXXConstructor
{ using namespace poplar;
JLFloatingPointBehaviour.constructor<bool, bool, bool, bool, bool>();
}
// poplar::setFloatingPointBehaviour(poplar::Graph &, poplar::program::Sequence &, const FloatingPointBehaviour &, const DebugContext &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarSetFloatingPointBehaviour", [](poplar::Graph & a, poplar::program::Sequence & b, const FloatingPointBehaviour & c, const DebugContext & d) {return poplar::setFloatingPointBehaviour(a, b, c, d);} ); }
// poplar::setFloatingPointBehaviour(poplar::Graph &, poplar::program::Sequence &, const poplar::Tensor &, const DebugContext &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarSetFloatingPointBehaviour", [](poplar::Graph & a, poplar::program::Sequence & b, const poplar::Tensor & c, const DebugContext & d) {return poplar::setFloatingPointBehaviour(a, b, c, d);} ); }
// poplar::setStochasticRounding(poplar::Graph &, poplar::program::Sequence &, bool, const DebugContext &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarSetStochasticRounding", [](poplar::Graph & a, poplar::program::Sequence & b, bool c, const DebugContext & d) {return poplar::setStochasticRounding(a, b, c, d);} ); }
// poplar::getAndModifyFloatingPointBehaviour(poplar::Graph &, poplar::program::Sequence &, const FloatingPointBehaviour &, const FloatingPointBehaviour &, const DebugContext &)__FunctionDecl
{ using namespace poplar;
mod.method("PoplarGetAndModifyFloatingPointBehaviour", [](poplar::Graph & a, poplar::program::Sequence & b, const FloatingPointBehaviour & c, const FloatingPointBehaviour & d, const DebugContext & e) {return poplar::getAndModifyFloatingPointBehaviour(a, b, c, d, e);} ); }
// poplar::IPUModel::IPUModel(const char *)__CXXConstructor
{ using namespace poplar;
JLIPUModel.constructor<const char *>();
}
// poplar::IPUModel::RelativeSyncDelayType::AUTO__EnumConstantDecl
mod.set_const("IPUModelRelativeSyncDelayTypeIPUModelAUTO", poplar::IPUModel::RelativeSyncDelayType::AUTO);
// poplar::IPUModel::RelativeSyncDelayType::NO_DELAY__EnumConstantDecl
mod.set_const("IPUModelRelativeSyncDelayTypeIPUModelNO_DELAY", poplar::IPUModel::RelativeSyncDelayType::NO_DELAY);
// poplar::IPUModel::createDevice(OptionFlags, bool, unsigned int)__CXXMethod
{ using namespace poplar;
JLIPUModel.method("IPUModelCreateDevice", [](poplar::IPUModel& cl) {return cl.createDevice();});
JLIPUModel.method("IPUModelCreateDevice", [](poplar::IPUModel& cl, OptionFlags a) {return cl.createDevice(a);});
JLIPUModel.method("IPUModelCreateDevice", [](poplar::IPUModel& cl, OptionFlags a, bool b) {return cl.createDevice(a, b);});
JLIPUModel.method("IPUModelCreateDevice", [](poplar::IPUModel& cl, OptionFlags a, bool b, unsigned int c) {return cl.createDevice(a, b, c);});
}
// popops::abs(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsAbs", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::abs(a, b, c, d, e);} ); }
// popops::absInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsAbsInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::absInPlace(a, b, c, d, e);} ); }
// popops::absWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsAbsWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::absWithOutput(a, b, c, d, e, f);} ); }
// popops::inv(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsInv", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::inv(a, b, c, d, e);} ); }
// popops::invInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsInvInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::invInPlace(a, b, c, d, e);} ); }
// popops::invWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsInvWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::invWithOutput(a, b, c, d, e, f);} ); }
// popops::logicalNot(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLogicalNot", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::logicalNot(a, b, c, d, e);} ); }
// popops::logicalNotInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLogicalNotInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::logicalNotInPlace(a, b, c, d, e);} ); }
// popops::logicalNotWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLogicalNotWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::logicalNotWithOutput(a, b, c, d, e, f);} ); }
// popops::neg(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsNeg", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::neg(a, b, c, d, e);} ); }
// popops::negInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsNegInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::negInPlace(a, b, c, d, e);} ); }
// popops::negWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsNegWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::negWithOutput(a, b, c, d, e, f);} ); }
// popops::signum(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSignum", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::signum(a, b, c, d, e);} ); }
// popops::signumInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSignumInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::signumInPlace(a, b, c, d, e);} ); }
// popops::signumWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSignumWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::signumWithOutput(a, b, c, d, e, f);} ); }
// popops::isFinite(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsIsFinite", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::isFinite(a, b, c, d, e);} ); }
// popops::isFiniteWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsIsFiniteWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::isFiniteWithOutput(a, b, c, d, e, f);} ); }
// popops::checkTypes<>(poplar::Type, float)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCheckTypes<>", [](poplar::Type a, float b) {return popops::checkTypes<>(a, b);} ); }
// popops::checkTypes<>(poplar::Type, double)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCheckTypes<>", [](poplar::Type a, double b) {return popops::checkTypes<>(a, b);} ); }
// popops::bitwiseNot(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseNot", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::bitwiseNot(a, b, c, d, e);} ); }
// popops::bitwiseNotInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseNotInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::bitwiseNotInPlace(a, b, c, d, e);} ); }
// popops::bitwiseNotWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseNotWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::bitwiseNotWithOutput(a, b, c, d, e, f);} ); }
// popops::countLeadingZeros(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCountLeadingZeros", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::countLeadingZeros(a, b, c, d, e);} ); }
// popops::countLeadingZerosInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCountLeadingZerosInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::countLeadingZerosInPlace(a, b, c, d, e);} ); }
// popops::countLeadingZerosWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCountLeadingZerosWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::countLeadingZerosWithOutput(a, b, c, d, e, f);} ); }
// popops::popcount(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsPopcount", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::popcount(a, b, c, d, e);} ); }
// popops::popcountInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsPopcountInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::popcountInPlace(a, b, c, d, e);} ); }
// popops::popcountWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsPopcountWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::popcountWithOutput(a, b, c, d, e, f);} ); }
// popops::ceil(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCeil", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::ceil(a, b, c, d, e);} ); }
// popops::ceilInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCeilInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::ceilInPlace(a, b, c, d, e);} ); }
// popops::ceilWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCeilWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::ceilWithOutput(a, b, c, d, e, f);} ); }
// popops::floor(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsFloor", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::floor(a, b, c, d, e);} ); }
// popops::floorInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsFloorInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::floorInPlace(a, b, c, d, e);} ); }
// popops::floorWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsFloorWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::floorWithOutput(a, b, c, d, e, f);} ); }
// popops::round(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsRound", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::round(a, b, c, d, e);} ); }
// popops::roundInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsRoundInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::roundInPlace(a, b, c, d, e);} ); }
// popops::roundWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsRoundWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::roundWithOutput(a, b, c, d, e, f);} ); }
// popops::nearbyint(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsNearbyint", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::nearbyint(a, b, c, d, e);} ); }
// popops::nearbyintInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsNearbyintInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::nearbyintInPlace(a, b, c, d, e);} ); }
// popops::nearbyintWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsNearbyintWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::nearbyintWithOutput(a, b, c, d, e, f);} ); }
// popops::cbrt(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCbrt", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::cbrt(a, b, c, d, e);} ); }
// popops::cbrtInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCbrtInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::cbrtInPlace(a, b, c, d, e);} ); }
// popops::cbrtWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCbrtWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::cbrtWithOutput(a, b, c, d, e, f);} ); }
// popops::exp(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsExp", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::exp(a, b, c, d, e);} ); }
// popops::expInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsExpInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::expInPlace(a, b, c, d, e);} ); }
// popops::expWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsExpWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::expWithOutput(a, b, c, d, e, f);} ); }
// popops::exp2(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsExp2", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::exp2(a, b, c, d, e);} ); }
// popops::exp2InPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsExp2InPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::exp2InPlace(a, b, c, d, e);} ); }
// popops::exp2WithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsExp2WithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::exp2WithOutput(a, b, c, d, e, f);} ); }
// popops::expm1(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsExpm1", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::expm1(a, b, c, d, e);} ); }
// popops::expm1InPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsExpm1InPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::expm1InPlace(a, b, c, d, e);} ); }
// popops::expm1WithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsExpm1WithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::expm1WithOutput(a, b, c, d, e, f);} ); }
// popops::log(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLog", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::log(a, b, c, d, e);} ); }
// popops::logInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLogInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::logInPlace(a, b, c, d, e);} ); }
// popops::logWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLogWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::logWithOutput(a, b, c, d, e, f);} ); }
// popops::log1p(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLog1P", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::log1p(a, b, c, d, e);} ); }
// popops::log1pInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLog1PInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::log1pInPlace(a, b, c, d, e);} ); }
// popops::log1pWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLog1PWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::log1pWithOutput(a, b, c, d, e, f);} ); }
// popops::sqrt(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSqrt", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::sqrt(a, b, c, d, e);} ); }
// popops::sqrtInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSqrtInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::sqrtInPlace(a, b, c, d, e);} ); }
// popops::sqrtWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSqrtWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::sqrtWithOutput(a, b, c, d, e, f);} ); }
// popops::square(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSquare", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::square(a, b, c, d, e);} ); }
// popops::squareInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSquareInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::squareInPlace(a, b, c, d, e);} ); }
// popops::squareWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSquareWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::squareWithOutput(a, b, c, d, e, f);} ); }
// popops::rsqrt(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsRsqrt", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::rsqrt(a, b, c, d, e);} ); }
// popops::rsqrtInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsRsqrtInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::rsqrtInPlace(a, b, c, d, e);} ); }
// popops::rsqrtWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsRsqrtWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::rsqrtWithOutput(a, b, c, d, e, f);} ); }
// popops::sigmoid(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSigmoid", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::sigmoid(a, b, c, d, e);} ); }
// popops::sigmoidInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSigmoidInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::sigmoidInPlace(a, b, c, d, e);} ); }
// popops::sigmoidWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSigmoidWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::sigmoidWithOutput(a, b, c, d, e, f);} ); }
// popops::asin(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsAsin", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::asin(a, b, c, d, e);} ); }
// popops::asinInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsAsinInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::asinInPlace(a, b, c, d, e);} ); }
// popops::asinWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsAsinWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::asinWithOutput(a, b, c, d, e, f);} ); }
// popops::cos(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCos", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::cos(a, b, c, d, e);} ); }
// popops::cosInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCosInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::cosInPlace(a, b, c, d, e);} ); }
// popops::cosWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsCosWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::cosWithOutput(a, b, c, d, e, f);} ); }
// popops::sin(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSin", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::sin(a, b, c, d, e);} ); }
// popops::sinInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSinInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::sinInPlace(a, b, c, d, e);} ); }
// popops::sinWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSinWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::sinWithOutput(a, b, c, d, e, f);} ); }
// popops::tan(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsTan", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::tan(a, b, c, d, e);} ); }
// popops::tanInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsTanInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::tanInPlace(a, b, c, d, e);} ); }
// popops::tanWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsTanWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::tanWithOutput(a, b, c, d, e, f);} ); }
// popops::tanh(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsTanh", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::tanh(a, b, c, d, e);} ); }
// popops::tanhInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsTanhInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::tanhInPlace(a, b, c, d, e);} ); }
// popops::tanhWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsTanhWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::tanhWithOutput(a, b, c, d, e, f);} ); }
// popops::varianceToInvStdDev(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::Type, const poplar::DebugContext &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsVarianceToInvStdDev", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, const poplar::Type e, std::string f) {return popops::varianceToInvStdDev(a, b, c, d, e, f);} ); }
// popops::varianceToInvStdDev(poplar::Graph &, const poplar::Tensor &, const float, poplar::program::Sequence &, const poplar::Type, const poplar::DebugContext &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsVarianceToInvStdDev", [](poplar::Graph & a, const poplar::Tensor & b, const float c, poplar::program::Sequence & d, const poplar::Type e, std::string f) {return popops::varianceToInvStdDev(a, b, c, d, e, f);} ); }
// popops::invStdDevToVariance(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::Type, const poplar::DebugContext &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsInvStdDevToVariance", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, const poplar::Type e, std::string f) {return popops::invStdDevToVariance(a, b, c, d, e, f);} ); }
// popops::invStdDevToVariance(poplar::Graph &, const poplar::Tensor &, const float, poplar::program::Sequence &, const poplar::Type, const poplar::DebugContext &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsInvStdDevToVariance", [](poplar::Graph & a, const poplar::Tensor & b, const float c, poplar::program::Sequence & d, const poplar::Type e, std::string f) {return popops::invStdDevToVariance(a, b, c, d, e, f);} ); }
// popops::geluErf(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsGeluErf", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::geluErf(a, b, c, d, e);} ); }
// popops::geluErfInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsGeluErfInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::geluErfInPlace(a, b, c, d, e);} ); }
// popops::geluErfWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsGeluErfWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::geluErfWithOutput(a, b, c, d, e, f);} ); }
// popops::erf(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsErf", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::erf(a, b, c, d, e);} ); }
// popops::erfInPlace(poplar::Graph &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsErfInPlace", [](poplar::Graph & a, const poplar::Tensor & b, poplar::program::Sequence & c, std::string d, const poplar::OptionFlags & e) {return popops::erfInPlace(a, b, c, d, e);} ); }
// popops::erfWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsErfWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::erfWithOutput(a, b, c, d, e, f);} ); }
// popops::add(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsAdd", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::add(a, b, c, d, e, f);} ); }
// popops::addInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsAddInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::addInPlace(a, b, c, d, e, f);} ); }
// popops::addWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsAddWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::addWithOutput(a, b, c, d, e, f, g);} ); }
// popops::sub(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSub", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::sub(a, b, c, d, e, f);} ); }
// popops::subInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSubInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::subInPlace(a, b, c, d, e, f);} ); }
// popops::subWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSubWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::subWithOutput(a, b, c, d, e, f, g);} ); }
// popops::mul(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsMul", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::mul(a, b, c, d, e, f);} ); }
// popops::mulInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsMulInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::mulInPlace(a, b, c, d, e, f);} ); }
// popops::mulWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsMulWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::mulWithOutput(a, b, c, d, e, f, g);} ); }
// popops::div(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsDiv", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::div(a, b, c, d, e, f);} ); }
// popops::divInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsDivInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::divInPlace(a, b, c, d, e, f);} ); }
// popops::divWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsDivWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::divWithOutput(a, b, c, d, e, f, g);} ); }
// popops::pow(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsPow", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::pow(a, b, c, d, e, f);} ); }
// popops::powInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsPowInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::powInPlace(a, b, c, d, e, f);} ); }
// popops::powWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsPowWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::powWithOutput(a, b, c, d, e, f, g);} ); }
// popops::rem(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsRem", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::rem(a, b, c, d, e, f);} ); }
// popops::remInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsRemInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::remInPlace(a, b, c, d, e, f);} ); }
// popops::remWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsRemWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::remWithOutput(a, b, c, d, e, f, g);} ); }
// popops::bitwiseAnd(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseAnd", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::bitwiseAnd(a, b, c, d, e, f);} ); }
// popops::bitwiseAndInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseAndInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::bitwiseAndInPlace(a, b, c, d, e, f);} ); }
// popops::bitwiseAndWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseAndWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::bitwiseAndWithOutput(a, b, c, d, e, f, g);} ); }
// popops::bitwiseOr(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseOr", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::bitwiseOr(a, b, c, d, e, f);} ); }
// popops::bitwiseOrInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseOrInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::bitwiseOrInPlace(a, b, c, d, e, f);} ); }
// popops::bitwiseOrWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseOrWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::bitwiseOrWithOutput(a, b, c, d, e, f, g);} ); }
// popops::bitwiseXor(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseXor", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::bitwiseXor(a, b, c, d, e, f);} ); }
// popops::bitwiseXorInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseXorInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::bitwiseXorInPlace(a, b, c, d, e, f);} ); }
// popops::bitwiseXorWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseXorWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::bitwiseXorWithOutput(a, b, c, d, e, f, g);} ); }
// popops::bitwiseXnor(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseXnor", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::bitwiseXnor(a, b, c, d, e, f);} ); }
// popops::bitwiseXnorInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseXnorInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::bitwiseXnorInPlace(a, b, c, d, e, f);} ); }
// popops::bitwiseXnorWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsBitwiseXnorWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::bitwiseXnorWithOutput(a, b, c, d, e, f, g);} ); }
// popops::shiftLeft(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsShiftLeft", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::shiftLeft(a, b, c, d, e, f);} ); }
// popops::shiftLeftInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsShiftLeftInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::shiftLeftInPlace(a, b, c, d, e, f);} ); }
// popops::shiftLeftWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsShiftLeftWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::shiftLeftWithOutput(a, b, c, d, e, f, g);} ); }
// popops::shiftRight(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsShiftRight", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::shiftRight(a, b, c, d, e, f);} ); }
// popops::shiftRightInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsShiftRightInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::shiftRightInPlace(a, b, c, d, e, f);} ); }
// popops::shiftRightWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsShiftRightWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::shiftRightWithOutput(a, b, c, d, e, f, g);} ); }
// popops::shiftRightSignExtend(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsShiftRightSignExtend", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::shiftRightSignExtend(a, b, c, d, e, f);} ); }
// popops::shiftRightSignExtendInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsShiftRightSignExtendInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::shiftRightSignExtendInPlace(a, b, c, d, e, f);} ); }
// popops::shiftRightSignExtendWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsShiftRightSignExtendWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::shiftRightSignExtendWithOutput(a, b, c, d, e, f, g);} ); }
// popops::logicalAnd(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLogicalAnd", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::logicalAnd(a, b, c, d, e, f);} ); }
// popops::logicalAndInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLogicalAndInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::logicalAndInPlace(a, b, c, d, e, f);} ); }
// popops::logicalAndWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLogicalAndWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::logicalAndWithOutput(a, b, c, d, e, f, g);} ); }
// popops::logicalOr(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLogicalOr", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::logicalOr(a, b, c, d, e, f);} ); }
// popops::logicalOrInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLogicalOrInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::logicalOrInPlace(a, b, c, d, e, f);} ); }
// popops::logicalOrWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLogicalOrWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::logicalOrWithOutput(a, b, c, d, e, f, g);} ); }
// popops::eq(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsEq", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::eq(a, b, c, d, e, f);} ); }
// popops::eqInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsEqInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::eqInPlace(a, b, c, d, e, f);} ); }
// popops::eqWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsEqWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::eqWithOutput(a, b, c, d, e, f, g);} ); }
// popops::neq(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsNeq", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::neq(a, b, c, d, e, f);} ); }
// popops::neqInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsNeqInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::neqInPlace(a, b, c, d, e, f);} ); }
// popops::neqWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsNeqWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::neqWithOutput(a, b, c, d, e, f, g);} ); }
// popops::gteq(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsGteq", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::gteq(a, b, c, d, e, f);} ); }
// popops::gteqInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsGteqInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::gteqInPlace(a, b, c, d, e, f);} ); }
// popops::gteqWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsGteqWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::gteqWithOutput(a, b, c, d, e, f, g);} ); }
// popops::gt(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsGt", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::gt(a, b, c, d, e, f);} ); }
// popops::gtInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsGtInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::gtInPlace(a, b, c, d, e, f);} ); }
// popops::gtWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsGtWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::gtWithOutput(a, b, c, d, e, f, g);} ); }
// popops::lteq(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLteq", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::lteq(a, b, c, d, e, f);} ); }
// popops::lteqInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLteqInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::lteqInPlace(a, b, c, d, e, f);} ); }
// popops::lteqWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLteqWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::lteqWithOutput(a, b, c, d, e, f, g);} ); }
// popops::lt(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLt", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::lt(a, b, c, d, e, f);} ); }
// popops::ltInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLtInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::ltInPlace(a, b, c, d, e, f);} ); }
// popops::ltWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsLtWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::ltWithOutput(a, b, c, d, e, f, g);} ); }
// popops::max(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsMax", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::max(a, b, c, d, e, f);} ); }
// popops::maxInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsMaxInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::maxInPlace(a, b, c, d, e, f);} ); }
// popops::maxWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsMaxWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::maxWithOutput(a, b, c, d, e, f, g);} ); }
// popops::min(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsMin", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::min(a, b, c, d, e, f);} ); }
// popops::minInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsMinInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::minInPlace(a, b, c, d, e, f);} ); }
// popops::minWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsMinWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::minWithOutput(a, b, c, d, e, f, g);} ); }
// popops::atan2(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsAtan2", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::atan2(a, b, c, d, e, f);} ); }
// popops::atan2InPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsAtan2InPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::atan2InPlace(a, b, c, d, e, f);} ); }
// popops::atan2WithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsAtan2WithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::atan2WithOutput(a, b, c, d, e, f, g);} ); }
// popops::invStdDevToVariance(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsInvStdDevToVariance", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::invStdDevToVariance(a, b, c, d, e, f);} ); }
// popops::invStdDevToVarianceInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsInvStdDevToVarianceInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::invStdDevToVarianceInPlace(a, b, c, d, e, f);} ); }
// popops::invStdDevToVarianceWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsInvStdDevToVarianceWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::invStdDevToVarianceWithOutput(a, b, c, d, e, f, g);} ); }
// popops::varianceToInvStdDev(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsVarianceToInvStdDev", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::varianceToInvStdDev(a, b, c, d, e, f);} ); }
// popops::varianceToInvStdDevInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsVarianceToInvStdDevInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, poplar::program::Sequence & d, std::string e, const poplar::OptionFlags & f) {return popops::varianceToInvStdDevInPlace(a, b, c, d, e, f);} ); }
// popops::varianceToInvStdDevWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsVarianceToInvStdDevWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::varianceToInvStdDevWithOutput(a, b, c, d, e, f, g);} ); }
// popops::select(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSelect", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::select(a, b, c, d, e, f, g);} ); }
// popops::selectInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSelectInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::selectInPlace(a, b, c, d, e, f, g);} ); }
// popops::selectWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsSelectWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, const poplar::Tensor & e, poplar::program::Sequence & f, std::string g, const poplar::OptionFlags & h) {return popops::selectWithOutput(a, b, c, d, e, f, g, h);} ); }
// popops::clamp(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsClamp", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::clamp(a, b, c, d, e, f, g);} ); }
// popops::clampInPlace(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsClampInPlace", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, poplar::program::Sequence & e, std::string f, const poplar::OptionFlags & g) {return popops::clampInPlace(a, b, c, d, e, f, g);} ); }
// popops::clampWithOutput(poplar::Graph &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, const poplar::Tensor &, poplar::program::Sequence &, const poplar::DebugContext &, const poplar::OptionFlags &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsClampWithOutput", [](poplar::Graph & a, const poplar::Tensor & b, const poplar::Tensor & c, const poplar::Tensor & d, const poplar::Tensor & e, poplar::program::Sequence & f, std::string g, const poplar::OptionFlags & h) {return popops::clampWithOutput(a, b, c, d, e, f, g, h);} ); }
// popops::addCodelets(poplar::Graph &)__FunctionDecl
{ using namespace popops;
mod.method("PopopsAddCodelets", [](poplar::Graph & a) {return popops::addCodelets(a);} ); }
