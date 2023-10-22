#include <node.h>
#include "protection.h"
#define NODE_MODULE_VERSION 114

using namespace v8;

void Protection(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	String::Utf8Value inputBack(isolate, args[0]);
	string powershell(*inputBack);

	protection(powershell);
}

void Back(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	string cript = back();

	Local<Value> criptValue = String::NewFromUtf8(isolate, cript.c_str()).ToLocalChecked();

	args.GetReturnValue().Set(criptValue);
}

void Initialize(Local<Object> exports) {
	NODE_SET_METHOD(exports, "protection", Protection);
	NODE_SET_METHOD(exports, "back", Back);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
