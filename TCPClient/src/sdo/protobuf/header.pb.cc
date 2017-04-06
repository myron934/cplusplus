// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: header.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "header.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace sdo {
namespace protobuf {
class headerDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<header> {
} _header_default_instance_;

namespace protobuf_header_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];

}  // namespace

const ::google::protobuf::uint32 TableStruct::offsets[] = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(header, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(header, method_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(header, package_type_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(header, sequence_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(header, body_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(header, code_),
};

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, -1, sizeof(header)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_header_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "header.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

}  // namespace

void TableStruct::Shutdown() {
  _header_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _header_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] = {
      "\n\014header.proto\022\014sdo.protobuf\"\252\001\n\006header\022"
      "\016\n\006method\030\001 \001(\t\0227\n\014package_type\030\002 \001(\0162!."
      "sdo.protobuf.header.PACKAGE_TYPE\022\020\n\010sequ"
      "ence\030\003 \001(\005\022\014\n\004body\030\004 \001(\t\022\014\n\004code\030\005 \001(\005\")"
      "\n\014PACKAGE_TYPE\022\013\n\007REQUEST\020\000\022\014\n\010RESPONSE\020"
      "\001b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 209);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "header.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&TableStruct::Shutdown);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_header_2eproto

const ::google::protobuf::EnumDescriptor* header_PACKAGE_TYPE_descriptor() {
  protobuf_header_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_header_2eproto::file_level_enum_descriptors[0];
}
bool header_PACKAGE_TYPE_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const header_PACKAGE_TYPE header::REQUEST;
const header_PACKAGE_TYPE header::RESPONSE;
const header_PACKAGE_TYPE header::PACKAGE_TYPE_MIN;
const header_PACKAGE_TYPE header::PACKAGE_TYPE_MAX;
const int header::PACKAGE_TYPE_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int header::kMethodFieldNumber;
const int header::kPackageTypeFieldNumber;
const int header::kSequenceFieldNumber;
const int header::kBodyFieldNumber;
const int header::kCodeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

header::header()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_header_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:sdo.protobuf.header)
}
header::header(const header& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  method_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.method().size() > 0) {
    method_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.method_);
  }
  body_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.body().size() > 0) {
    body_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.body_);
  }
  ::memcpy(&package_type_, &from.package_type_,
    reinterpret_cast<char*>(&code_) -
    reinterpret_cast<char*>(&package_type_) + sizeof(code_));
  // @@protoc_insertion_point(copy_constructor:sdo.protobuf.header)
}

void header::SharedCtor() {
  method_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  body_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&package_type_, 0, reinterpret_cast<char*>(&code_) -
    reinterpret_cast<char*>(&package_type_) + sizeof(code_));
  _cached_size_ = 0;
}

header::~header() {
  // @@protoc_insertion_point(destructor:sdo.protobuf.header)
  SharedDtor();
}

void header::SharedDtor() {
  method_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  body_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void header::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* header::descriptor() {
  protobuf_header_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_header_2eproto::file_level_metadata[0].descriptor;
}

const header& header::default_instance() {
  protobuf_header_2eproto::InitDefaults();
  return *internal_default_instance();
}

header* header::New(::google::protobuf::Arena* arena) const {
  header* n = new header;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void header::Clear() {
// @@protoc_insertion_point(message_clear_start:sdo.protobuf.header)
  method_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  body_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&package_type_, 0, reinterpret_cast<char*>(&code_) -
    reinterpret_cast<char*>(&package_type_) + sizeof(code_));
}

bool header::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:sdo.protobuf.header)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string method = 1;
      case 1: {
        if (tag == 10u) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_method()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->method().data(), this->method().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "sdo.protobuf.header.method"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .sdo.protobuf.header.PACKAGE_TYPE package_type = 2;
      case 2: {
        if (tag == 16u) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          set_package_type(static_cast< ::sdo::protobuf::header_PACKAGE_TYPE >(value));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 sequence = 3;
      case 3: {
        if (tag == 24u) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &sequence_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string body = 4;
      case 4: {
        if (tag == 34u) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_body()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->body().data(), this->body().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "sdo.protobuf.header.body"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 code = 5;
      case 5: {
        if (tag == 40u) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &code_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:sdo.protobuf.header)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:sdo.protobuf.header)
  return false;
#undef DO_
}

void header::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:sdo.protobuf.header)
  // string method = 1;
  if (this->method().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->method().data(), this->method().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "sdo.protobuf.header.method");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->method(), output);
  }

  // .sdo.protobuf.header.PACKAGE_TYPE package_type = 2;
  if (this->package_type() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->package_type(), output);
  }

  // int32 sequence = 3;
  if (this->sequence() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->sequence(), output);
  }

  // string body = 4;
  if (this->body().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->body().data(), this->body().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "sdo.protobuf.header.body");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->body(), output);
  }

  // int32 code = 5;
  if (this->code() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->code(), output);
  }

  // @@protoc_insertion_point(serialize_end:sdo.protobuf.header)
}

::google::protobuf::uint8* header::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic;  // Unused
  // @@protoc_insertion_point(serialize_to_array_start:sdo.protobuf.header)
  // string method = 1;
  if (this->method().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->method().data(), this->method().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "sdo.protobuf.header.method");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->method(), target);
  }

  // .sdo.protobuf.header.PACKAGE_TYPE package_type = 2;
  if (this->package_type() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->package_type(), target);
  }

  // int32 sequence = 3;
  if (this->sequence() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->sequence(), target);
  }

  // string body = 4;
  if (this->body().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->body().data(), this->body().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "sdo.protobuf.header.body");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->body(), target);
  }

  // int32 code = 5;
  if (this->code() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->code(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:sdo.protobuf.header)
  return target;
}

size_t header::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:sdo.protobuf.header)
  size_t total_size = 0;

  // string method = 1;
  if (this->method().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->method());
  }

  // string body = 4;
  if (this->body().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->body());
  }

  // .sdo.protobuf.header.PACKAGE_TYPE package_type = 2;
  if (this->package_type() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->package_type());
  }

  // int32 sequence = 3;
  if (this->sequence() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->sequence());
  }

  // int32 code = 5;
  if (this->code() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->code());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void header::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:sdo.protobuf.header)
  GOOGLE_DCHECK_NE(&from, this);
  const header* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const header>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:sdo.protobuf.header)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:sdo.protobuf.header)
    MergeFrom(*source);
  }
}

void header::MergeFrom(const header& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:sdo.protobuf.header)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.method().size() > 0) {

    method_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.method_);
  }
  if (from.body().size() > 0) {

    body_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.body_);
  }
  if (from.package_type() != 0) {
    set_package_type(from.package_type());
  }
  if (from.sequence() != 0) {
    set_sequence(from.sequence());
  }
  if (from.code() != 0) {
    set_code(from.code());
  }
}

void header::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:sdo.protobuf.header)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void header::CopyFrom(const header& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:sdo.protobuf.header)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool header::IsInitialized() const {
  return true;
}

void header::Swap(header* other) {
  if (other == this) return;
  InternalSwap(other);
}
void header::InternalSwap(header* other) {
  method_.Swap(&other->method_);
  body_.Swap(&other->body_);
  std::swap(package_type_, other->package_type_);
  std::swap(sequence_, other->sequence_);
  std::swap(code_, other->code_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata header::GetMetadata() const {
  protobuf_header_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_header_2eproto::file_level_metadata[0];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// header

// string method = 1;
void header::clear_method() {
  method_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& header::method() const {
  // @@protoc_insertion_point(field_get:sdo.protobuf.header.method)
  return method_.GetNoArena();
}
void header::set_method(const ::std::string& value) {
  
  method_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:sdo.protobuf.header.method)
}
#if LANG_CXX11
void header::set_method(::std::string&& value) {
  
  method_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:sdo.protobuf.header.method)
}
#endif
void header::set_method(const char* value) {
  
  method_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:sdo.protobuf.header.method)
}
void header::set_method(const char* value, size_t size) {
  
  method_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:sdo.protobuf.header.method)
}
::std::string* header::mutable_method() {
  
  // @@protoc_insertion_point(field_mutable:sdo.protobuf.header.method)
  return method_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* header::release_method() {
  // @@protoc_insertion_point(field_release:sdo.protobuf.header.method)
  
  return method_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void header::set_allocated_method(::std::string* method) {
  if (method != NULL) {
    
  } else {
    
  }
  method_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), method);
  // @@protoc_insertion_point(field_set_allocated:sdo.protobuf.header.method)
}

// .sdo.protobuf.header.PACKAGE_TYPE package_type = 2;
void header::clear_package_type() {
  package_type_ = 0;
}
::sdo::protobuf::header_PACKAGE_TYPE header::package_type() const {
  // @@protoc_insertion_point(field_get:sdo.protobuf.header.package_type)
  return static_cast< ::sdo::protobuf::header_PACKAGE_TYPE >(package_type_);
}
void header::set_package_type(::sdo::protobuf::header_PACKAGE_TYPE value) {
  
  package_type_ = value;
  // @@protoc_insertion_point(field_set:sdo.protobuf.header.package_type)
}

// int32 sequence = 3;
void header::clear_sequence() {
  sequence_ = 0;
}
::google::protobuf::int32 header::sequence() const {
  // @@protoc_insertion_point(field_get:sdo.protobuf.header.sequence)
  return sequence_;
}
void header::set_sequence(::google::protobuf::int32 value) {
  
  sequence_ = value;
  // @@protoc_insertion_point(field_set:sdo.protobuf.header.sequence)
}

// string body = 4;
void header::clear_body() {
  body_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& header::body() const {
  // @@protoc_insertion_point(field_get:sdo.protobuf.header.body)
  return body_.GetNoArena();
}
void header::set_body(const ::std::string& value) {
  
  body_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:sdo.protobuf.header.body)
}
#if LANG_CXX11
void header::set_body(::std::string&& value) {
  
  body_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:sdo.protobuf.header.body)
}
#endif
void header::set_body(const char* value) {
  
  body_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:sdo.protobuf.header.body)
}
void header::set_body(const char* value, size_t size) {
  
  body_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:sdo.protobuf.header.body)
}
::std::string* header::mutable_body() {
  
  // @@protoc_insertion_point(field_mutable:sdo.protobuf.header.body)
  return body_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* header::release_body() {
  // @@protoc_insertion_point(field_release:sdo.protobuf.header.body)
  
  return body_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void header::set_allocated_body(::std::string* body) {
  if (body != NULL) {
    
  } else {
    
  }
  body_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), body);
  // @@protoc_insertion_point(field_set_allocated:sdo.protobuf.header.body)
}

// int32 code = 5;
void header::clear_code() {
  code_ = 0;
}
::google::protobuf::int32 header::code() const {
  // @@protoc_insertion_point(field_get:sdo.protobuf.header.code)
  return code_;
}
void header::set_code(::google::protobuf::int32 value) {
  
  code_ = value;
  // @@protoc_insertion_point(field_set:sdo.protobuf.header.code)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf
}  // namespace sdo

// @@protoc_insertion_point(global_scope)
