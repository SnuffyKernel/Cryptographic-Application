#include <node.h>
#include "md5.h"
#define NODE_MODULE_VERSION 114

using namespace v8;

void md5(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	String::Utf8Value inputText(isolate, args[0]);
	std::string text(*inputText);
	String::Utf8Value inputSymbolHash(isolate, args[1]);
	std::string symbolHash(*inputSymbolHash);
	bool file = args[2]->BooleanValue(isolate);

	std::string encryptedString = md5hash_to_string(MD5(&text[0], text.size()), symbolHash, file);

	Local<Value> encryptedValue = String::NewFromUtf8(isolate, encryptedString.c_str()).ToLocalChecked();

	args.GetReturnValue().Set(encryptedValue);
}

void Initialize(Local<Object> exports) {
	NODE_SET_METHOD(exports, "md5", md5);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
