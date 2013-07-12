v8util
=====

utilities for v8 development

## install

Using a C package manager like [cpm](https://github.com/visionmedia/cpm) you can install v8-util into the `deps/` directory of your project

```sh
$ cpm install jwerle/v8-util
```

## building and linking in your project

Build `libv8util` with `make`. (***requires g++***)

```sh
$ make build
```

You can now link `libv8util.so` found in `out/` to your project.

```sh
$ g++ v8/out/native/libv8.dylib v8util/out/libv8util -Iv8/include -Lv8/src program.cc -o program
```

## api

### const char *v8util::strtocstr (const v8::String::Utf8Value &str)

Converts a `v8::String::Utf8Value` string to a c string

***example***

```c++
v8::Local<v8::String> str = v8::String::New("some string");
v8::String::Utf8Value utfstr(str);

assert(NULL != v8util::strtocstr(utfstr));
printf("%s\n", v8util::strtocstr(utfstr));
```

### void print (const v8::String::Utf8Value &str);

Prints a `v8::String::Utf8Value` string to stdout

***example***

```c++
v8::Local<v8::String> str = v8::String::New("another string");
v8::String::Utf8Value utfstr(str);

v8util::print(utfstr)
```

### v8::Handle<v8::String> readjs (const char *file);

Reads a JavaScript file into a a `v8::String` instance

***example***

```c++
v8::Local<v8::String> js = v8util::readjs("./path/to/file.js");
v8::String::Utf8Value utfstr(js);

const char *cstr = v8util::strtocstr(utfstr);

assert(NULL != cstr);
```

### v8::Handle<v8::Value> evaljs (const char *name, const char *source, bool print_result = false);

Evaluates JavaScript from a given string and returns the v8 representation of its return value

***example***

```c++
v8::Local<v8::String> js = v8util::readjs("./path/to/file.js");
v8::String::Utf8Value utfstr(js);

const char *cstr = v8util::strtocstr(utfstr);
v8::Handle<v8::Value> result = v8util::evaljs("v8util", cstr);

assert(!result.IsEmpty());
```

### void exception (v8::TryCatch *trycatch);

Reports an exception to stdout

***example***

```c++
v8::Local<v8::String> js = v8util::readjs("./test/exception.js");
v8::String::Utf8Value utfjs(js);

const char *cstr = v8util::strtocstr(utfjs);
bool exception_result = v8util::evaljs("v8util", cstr);

assert(false == exception_result);
```

## license

MIT