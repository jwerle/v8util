v8util
=====

utilities for v8 development

## install

Using a C package manager like [cpm](https://github.com/visionmedia/cpm) you can install v8util into the `deps/` directory of your project. It also installs to `/usr/local/include` and `/usr/local/lib` by default.

```sh
$ cpm install jwerle/v8util
```

Just link in your compilation

```sh
$ g++ -I/usr/local/include/v8 -lv8 -lv8util program.cc -o program
```

## building and linking to your project from source

Change to `v8util` root directory

```sh
$ cd v8util/
```

Install `libv8util` with `make`. (***requires g++***)

You can set the `PREFIX` variable to be whatever you would like. Defaults to `/usr/local/`

```sh
$ make install
```

You can now link `v8util` to your project


```sh
$ g++ -I/usr/local/include/v8 -lv8 -lv8util program.cc -o program
```


### node-gyp

You can include `v8util` in your node.js addon by simply including it in the "sources" array in your `binding.gyp` file

```gyp
{
	"targets": [
		{
			"target_name": "myaddon",
			"sources": [
				"deps/v8util.h", "deps/v8util.cc",
				"src/myaddon.cc"
			]
		}
	]
}
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

### void Print (const v8::String::Utf8Value &str);

Prints a `v8::String::Utf8Value` string to stdout

***example***

```c++
v8::Local<v8::String> str = v8::String::New("another string");
v8::String::Utf8Value utfstr(str);

v8util::Print(utfstr)
```

### v8::Handle\<v8::String> ReadJs (const char *file);

Reads a JavaScript file into a a `v8::String` instance

***example***

```c++
v8::Local<v8::String> js = v8util::ReadJs("./path/to/file.js");
v8::String::Utf8Value utfstr(js);

const char *cstr = v8util::strtocstr(utfstr);

assert(NULL != cstr);
```

### v8::Handle\<v8::Value> EvalJs (const char *name, const char *source, bool report_exception = true, bool print_result = false);

Evaluates JavaScript from a given string and returns the v8 representation of its return value

***example***

```c++
v8::Local<v8::String> js = v8util::ReadJs("./path/to/file.js");
v8::String::Utf8Value utfstr(js);

const char *cstr = v8util::strtocstr(utfstr);
v8::Handle<v8::Value> result = v8util::EvalJs("v8util", cstr);

assert(!result.IsEmpty());
```

### void exception (v8::TryCatch *trycatch);

Reports an exception to stdout

***example***

```c++
v8util::Exception(&trycatch);
```

### v8::Handle\<v8::Value> Compile (const char *file, bool report_exception = true, bool print_result = false)

Reads, and evaluates JavaScript from a provided file source

```js
v8::Handle<v8::Value> result = v8util::Compile("./path/to/file.js");
```


### void ThrowError (const char *message)

Throws an `Error` exception with a message

***example***

```c++
v8util::ThrowError("Error");
```

### void ThrowRangeError (const char *message)

Throws a `RangeError` exception with a message

***example***

```c++
v8util::ThrowRangeError("RangeError");
```

### void ThrowReferenceError (const char *message)

Throws a `ReferenceError` exception with a message

***example***

```c++
v8util::ThrowReferenceError("ReferenceError");
```

### void ThrowSyntaxError (const char *message)

Throws a `SyntaxError` exception with a message

***example***

```c++
v8util::ThrowSyntaxError("SyntaxError");
```

### void ThrowTypeError (const char *message)

Throws a `TypeError` exception with a message

***example***

```c++
v8util::ThrowTypeError("TypeError");
```


## license

MIT
