
#include <assert.h>
#include <iostream>
#include "v8util.h"
#include <v8.h>

v8::Handle<v8::Context> 
createContext (v8::Isolate *isolate);

int 
main (int argc, char *argv[]) {
	v8::V8::SetFlagsFromCommandLine(&argc, argv, true);
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	{
		v8::HandleScope scope(isolate);
		v8::Handle<v8::Context> context = createContext(isolate);

		if (context.IsEmpty()) {
      fprintf(stderr, "Error creating context\n");
      return 1;
    }

    context->Enter();

    
    /**
     * `strtocstr(const v8::String::Utf8Value &str)` test
     */

    v8::Local<v8::String> str = v8::String::New("v8util-test-string");
    v8::String::Utf8Value utfstr(str);
    assert(NULL != v8util::strtocstr(utfstr));
    

    /**
     * `print(const v8::String::Utf8Value &str)` test
     */

   	// v8util::print(utfstr); // commented out to keep stdout clean; uncomment to test


   	/**
     * `readjs(const char *file)` test
     */

    v8::Local<v8::String> basic_js = v8util::readjs("./test/basic.js");
    v8::String::Utf8Value basic_jsutf(basic_js);
    const char *basic_cstrjs = v8util::strtocstr(basic_jsutf);
    assert(NULL != v8util::strtocstr(basic_jsutf));


    /**
     * `evaljs(const char *name, const char *source, bool print_result = false)` test
     */

    v8::Local<v8::Value> basic_value = v8util::evaljs("v8util", basic_cstrjs);
    assert(!basic_value.IsEmpty());

    // if (basic_value->IsObject()) {
    //     v8::String::Utf8Value ustr(basic_value->ToObject()->Get(v8::String::New("foo")));
    //     const char *cstr = v8util::strtocstr(ustr);
    //     printf("%s\n", cstr);
    //     puts("object");
    // }
    
    
    /**
     * `exception(v8::TryCatch *trycatch)` test
     */

    v8::Local<v8::String> exception_js = v8util::readjs("./test/exception.js");
    v8::String::Utf8Value exception_jsutf(exception_js);
    const char *exception_cstrjs = v8util::strtocstr(exception_jsutf);
    assert(NULL != v8util::strtocstr(exception_jsutf));
    v8::Handle<v8::Value> exception_value = v8util::evaljs("v8util", exception_cstrjs);
    assert(exception_value.IsEmpty());

    context->Exit();

	}

	v8::V8::Dispose();

    printf("\n  \e[32m\u2713 \e[90mok\e[0m\n\n");

	return 0;
}


v8::Handle<v8::Context> 
createContext (v8::Isolate *isolate) {
	v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();

	return v8::Context::New(isolate, NULL, global);
}