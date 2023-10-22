#include <node.h>
#include "playfair.h"
#define NODE_MODULE_VERSION 114

using namespace v8;

void PlayFair(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	String::Utf8Value inputLetter(isolate, args[0]);
	string letter(*inputLetter);
	String::Utf8Value inputKey(isolate, args[1]);
	string key(*inputKey);
	String::Utf8Value inputText(isolate, args[2]);
	string text(*inputText);
	String::Utf8Value inputChar(isolate, args[3]);
	string character(*inputChar);
	int columns = args[4]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
	bool code = args[5]->BooleanValue(isolate);
	bool file = args[6]->BooleanValue(isolate);

	string encryptedString = encryption(letter, key, text, character, columns, code, file);

	Local<Value> encryptedValue = String::NewFromUtf8(isolate, encryptedString.c_str()).ToLocalChecked();

	args.GetReturnValue().Set(encryptedValue);
}

void Initialize(Local<Object> exports) {
	NODE_SET_METHOD(exports, "playfair", PlayFair);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
