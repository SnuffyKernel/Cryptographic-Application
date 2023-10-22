#include <node.h>
#include "vigener.h"
#define NODE_MODULE_VERSION 114

using namespace v8;

void Vigener(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	String::Utf8Value inputLetter(isolate, args[0]);
	string letter(*inputLetter);
	String::Utf8Value inputKey(isolate, args[1]);
	string key(*inputKey);
	String::Utf8Value inputText(isolate, args[2]);
	string text(*inputText);
	bool code = args[3]->BooleanValue(isolate);
	bool file = args[4]->BooleanValue(isolate);

	string encryptedString = new_text(letter, key, text, code, file);

	Local<Value> encryptedValue = String::NewFromUtf8(isolate, encryptedString.c_str()).ToLocalChecked();

	args.GetReturnValue().Set(encryptedValue);
}

void Initialize(Local<Object> exports) {
	NODE_SET_METHOD(exports, "vigener", Vigener);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
