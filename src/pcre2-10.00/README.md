pcre2-10.00
====


Reproduce result
----
```
$ make reproduce
ASAN_OPTIONS=strip_path_prefix=$(realpath ../..)/ ./reproducer $(realpath ../..)/input/pcre2-10.00/crash-235641cefe524570bf0df6a3b3722535ce2dbbf7
[*] main: Size of file ../../input/pcre2-10.00/crash-235641cefe524570bf0df6a3b3722535ce2dbbf7: 0x14
=================================================================
==30544==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7fffffffd9a0 at pc 0x00000044878c bp 0x7fffffffd950 sp 0x7fffffffd100
WRITE of size 64 at 0x7fffffffd9a0 thread T0
    #0 0x44878b in __interceptor_regcomp.part.291 /home/tomori/bin/llvm-project/compiler-rt/lib/asan/../sanitizer_common/sanitizer_common_interceptors.inc:7804
    #1 0x4f9e82 in LLVMFuzzerTestOneInput fuzzer-test-suite/pcre2-10.00/target.cc:15:12
    #2 0x4f9b19 in main src/pcre2-10.00/../main.cpp:42:5
    #3 0x7ffff6a99bf6 in __libc_start_main /build/glibc-S9d2JN/glibc-2.27/csu/../csu/libc-start.c:310
    #4 0x41c1f9 in _start (src/pcre2-10.00/reproducer+0x41c1f9)

Address 0x7fffffffd9a0 is located in stack of thread T0 at offset 64 in frame
    #0 0x4f9c3f in LLVMFuzzerTestOneInput fuzzer-test-suite/pcre2-10.00/target.cc:9

  This frame has 5 object(s):
    [32, 64) 'preg' (line 11)
    [96, 128) 'str' (line 12) <== Memory access at offset 64 partially underflows this variable
    [160, 161) 'ref.tmp' (line 12)
    [176, 208) 'pat' (line 13)
    [240, 280) 'pmatch' (line 16)
```