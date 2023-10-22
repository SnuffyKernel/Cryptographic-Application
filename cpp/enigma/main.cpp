#include <node.h>
#include "enigma.h"
#define NODE_MODULE_VERSION 114

using namespace v8;

void Enigma(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	String::Utf8Value inputAlf(isolate, args[0]);
	string alf(*inputAlf);
	String::Utf8Value inputRot1(isolate, args[1]);
	string rot1(*inputRot1);
	String::Utf8Value inputRot2(isolate, args[2]);
	string rot2(*inputRot2);
	String::Utf8Value inputRot3(isolate, args[3]);
	string rot3(*inputRot3);
	String::Utf8Value inputReflector(isolate, args[4]);
	string reflector(*inputReflector);
	String::Utf8Value inputText(isolate, args[5]);
	string text(*inputText);
	bool file = args[6]->BooleanValue(isolate);

	string encryptedString = enigma(alf, rot1, rot2, rot3, reflector, text, file);

	Local<Value> encryptedValue = String::NewFromUtf8(isolate, encryptedString.c_str()).ToLocalChecked();

	args.GetReturnValue().Set(encryptedValue);
}

void Initialize(Local<Object> exports) {
	NODE_SET_METHOD(exports, "enigma", Enigma);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
