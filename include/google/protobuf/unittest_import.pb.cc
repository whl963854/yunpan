// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_import.proto

#include "google/protobuf/unittest_import.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace protobuf_unittest_import {
constexpr ImportMessage::ImportMessage(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : d_(0){}
struct ImportMessageDefaultTypeInternal {
  constexpr ImportMessageDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~ImportMessageDefaultTypeInternal() {}
  union {
    ImportMessage _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT ImportMessageDefaultTypeInternal _ImportMessage_default_instance_;
}  // namespace protobuf_unittest_import
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_google_2fprotobuf_2funittest_5fimport_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_google_2fprotobuf_2funittest_5fimport_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_google_2fprotobuf_2funittest_5fimport_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_google_2fprotobuf_2funittest_5fimport_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::protobuf_unittest_import::ImportMessage, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::protobuf_unittest_import::ImportMessage, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::protobuf_unittest_import::ImportMessage, d_),
  0,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, -1, sizeof(::protobuf_unittest_import::ImportMessage)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::protobuf_unittest_import::_ImportMessage_default_instance_),
};

const char descriptor_table_protodef_google_2fprotobuf_2funittest_5fimport_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n%google/protobuf/unittest_import.proto\022"
  "\030protobuf_unittest_import\032,google/protob"
  "uf/unittest_import_public.proto\"\032\n\rImpor"
  "tMessage\022\t\n\001d\030\001 \001(\005*<\n\nImportEnum\022\016\n\nIMP"
  "ORT_FOO\020\007\022\016\n\nIMPORT_BAR\020\010\022\016\n\nIMPORT_BAZ\020"
  "\t*1\n\020ImportEnumForMap\022\013\n\007UNKNOWN\020\000\022\007\n\003FO"
  "O\020\001\022\007\n\003BAR\020\002B\037\n\030com.google.protobuf.test"
  "H\001\370\001\001P\000"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_google_2fprotobuf_2funittest_5fimport_2eproto_deps[1] = {
  &::descriptor_table_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_google_2fprotobuf_2funittest_5fimport_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_google_2fprotobuf_2funittest_5fimport_2eproto = {
  false, false, 287, descriptor_table_protodef_google_2fprotobuf_2funittest_5fimport_2eproto, "google/protobuf/unittest_import.proto", 
  &descriptor_table_google_2fprotobuf_2funittest_5fimport_2eproto_once, descriptor_table_google_2fprotobuf_2funittest_5fimport_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_google_2fprotobuf_2funittest_5fimport_2eproto::offsets,
  file_level_metadata_google_2fprotobuf_2funittest_5fimport_2eproto, file_level_enum_descriptors_google_2fprotobuf_2funittest_5fimport_2eproto, file_level_service_descriptors_google_2fprotobuf_2funittest_5fimport_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_google_2fprotobuf_2funittest_5fimport_2eproto_getter() {
  return &descriptor_table_google_2fprotobuf_2funittest_5fimport_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_google_2fprotobuf_2funittest_5fimport_2eproto(&descriptor_table_google_2fprotobuf_2funittest_5fimport_2eproto);
namespace protobuf_unittest_import {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ImportEnum_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_google_2fprotobuf_2funittest_5fimport_2eproto);
  return file_level_enum_descriptors_google_2fprotobuf_2funittest_5fimport_2eproto[0];
}
bool ImportEnum_IsValid(int value) {
  switch (value) {
    case 7:
    case 8:
    case 9:
      return true;
    default:
      return false;
  }
}

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ImportEnumForMap_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_google_2fprotobuf_2funittest_5fimport_2eproto);
  return file_level_enum_descriptors_google_2fprotobuf_2funittest_5fimport_2eproto[1];
}
bool ImportEnumForMap_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class ImportMessage::_Internal {
 public:
  using HasBits = decltype(std::declval<ImportMessage>()._has_bits_);
  static void set_has_d(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

ImportMessage::ImportMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:protobuf_unittest_import.ImportMessage)
}
ImportMessage::ImportMessage(const ImportMessage& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  d_ = from.d_;
  // @@protoc_insertion_point(copy_constructor:protobuf_unittest_import.ImportMessage)
}

void ImportMessage::SharedCtor() {
d_ = 0;
}

ImportMessage::~ImportMessage() {
  // @@protoc_insertion_point(destructor:protobuf_unittest_import.ImportMessage)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void ImportMessage::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void ImportMessage::ArenaDtor(void* object) {
  ImportMessage* _this = reinterpret_cast< ImportMessage* >(object);
  (void)_this;
}
void ImportMessage::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void ImportMessage::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void ImportMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:protobuf_unittest_import.ImportMessage)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  d_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ImportMessage::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional int32 d = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_d(&has_bits);
          d_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ImportMessage::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:protobuf_unittest_import.ImportMessage)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int32 d = 1;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_d(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:protobuf_unittest_import.ImportMessage)
  return target;
}

size_t ImportMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protobuf_unittest_import.ImportMessage)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional int32 d = 1;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_d());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ImportMessage::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    ImportMessage::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ImportMessage::GetClassData() const { return &_class_data_; }

void ImportMessage::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<ImportMessage *>(to)->MergeFrom(
      static_cast<const ImportMessage &>(from));
}


void ImportMessage::MergeFrom(const ImportMessage& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:protobuf_unittest_import.ImportMessage)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_has_d()) {
    _internal_set_d(from._internal_d());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ImportMessage::CopyFrom(const ImportMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protobuf_unittest_import.ImportMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ImportMessage::IsInitialized() const {
  return true;
}

void ImportMessage::InternalSwap(ImportMessage* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(d_, other->d_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ImportMessage::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_google_2fprotobuf_2funittest_5fimport_2eproto_getter, &descriptor_table_google_2fprotobuf_2funittest_5fimport_2eproto_once,
      file_level_metadata_google_2fprotobuf_2funittest_5fimport_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace protobuf_unittest_import
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::protobuf_unittest_import::ImportMessage* Arena::CreateMaybeMessage< ::protobuf_unittest_import::ImportMessage >(Arena* arena) {
  return Arena::CreateMessageInternal< ::protobuf_unittest_import::ImportMessage >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
