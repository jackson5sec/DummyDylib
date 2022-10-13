## Installing

Visual Studio Community Edition with Windows SDK


### Build/Usage
```
// g++ -fPIC -dynamiclib -arch arm64 dylib.cpp -o dummydylib_arm64.dylib
// g++ -fPIC -dynamiclib -arch x86_64 dylib.cpp -o dummydylib_x64.dylib
```
Threaded Dylib that can be used as a payload for DYLD_INSERT_LIBRARIES and OSX Dylib Hijack's

Log output to /tmp/dylib.log with user context, processID, path, and processname
```
Output example:
PATH: /Users/user/repos/dylibharness/test.bin
USERNAME: user
PID: 85534
EUID: 501
UID: 501
GID: 20
```

