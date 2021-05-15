Reproduce bugs of sqlite-2016-11-14
====

`***` is censered.

```
$ ./reproducer ../../fuzzer-test-suite/sqlite-2016-11-14/crash-1066e42866aad3a04e6851dc494ad54bc31b9f78
=================================================================
==2480==ERROR: AddressSanitizer: heap-use-after-free on address 0x60d0000004b3 at pc 0x55c369a842e3 bp 0x7ffee306e910 sp 0x7ffee306e0b8
READ of size 1 at 0x60d0000004b3 thread T0
    #0 0x55c369a842e2 in __interceptor_memcpy.part.234 (***/reproduce-bugs-in-fuzzer-test-suite/src/sqlite-2016-11-14/reproducer+0x662e2)
    #1 0x55c369b3245d in sqlite3StrAccumAppend ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:25585
    #2 0x55c369b31e4b in sqlite3VXPrintf ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:25445
    #3 0x55c369b326bf in sqlite3VMPrintf ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:25667
    #4 0x55c369b342cb in sqlite3ErrorMsg ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:27516
    #5 0x55c369bcae7a in yy_syntax_error ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:136445
    #6 0x55c369bcaf7c in sqlite3Parser ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:136605
    #7 0x55c369bcbe15 in sqlite3RunParser ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:137477
    #8 0x55c369ba2629 in sqlite3Prepare ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:114208
    #9 0x55c369ba29a9 in sqlite3LockAndPrepare ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:114299
    #10 0x55c369ba2b98 in sqlite3_prepare_v2 ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:114375
    #11 0x55c369b9c059 in sqlite3_exec ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:109705
    #12 0x55c369b2a7ba in LLVMFuzzerTestOneInput ../../fuzzer-test-suite/sqlite-2016-11-14/ossfuzz.c:78
    #13 0x55c369b2a147 in main ../main.cpp:42
    #14 0x7ff1d9f04bf6 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x21bf6)
    #15 0x55c369a2b8f9 in _start (***/reproduce-bugs-in-fuzzer-test-suite/src/sqlite-2016-11-14/reproducer+0xd8f9)

0x60d0000004b3 is located 99 bytes inside of 136-byte region [0x60d000000450,0x60d0000004d8)
freed by thread T0 here:
    #0 0x55c369ae9338 in __interceptor_free (***/reproduce-bugs-in-fuzzer-test-suite/src/sqlite-2016-11-14/reproducer+0xcb338)
    #1 0x55c369b2e7b8 in sqlite3MemFree ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:20505
    #2 0x55c369b2f5fb in sqlite3_free ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:24358
    #3 0x55c369b2f711 in sqlite3DbFree ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:24401
    #4 0x55c369b86f5a in sqlite3NestedParse ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:98638
    #5 0x55c369b8d5a4 in sqlite3CreateIndex ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:101731
    #6 0x55c369bc6c55 in yy_reduce ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:135304
    #7 0x55c369bcaf50 in sqlite3Parser ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:136530
    #8 0x55c369bcbe15 in sqlite3RunParser ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:137477
    #9 0x55c369ba2629 in sqlite3Prepare ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:114208
    #10 0x55c369ba29a9 in sqlite3LockAndPrepare ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:114299
    #11 0x55c369ba2b98 in sqlite3_prepare_v2 ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:114375
    #12 0x55c369b9c059 in sqlite3_exec ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:109705
    #13 0x55c369b2a7ba in LLVMFuzzerTestOneInput ../../fuzzer-test-suite/sqlite-2016-11-14/ossfuzz.c:78
    #14 0x55c369b2a147 in main ../main.cpp:42
    #15 0x7ff1d9f04bf6 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x21bf6)

previously allocated by thread T0 here:
    #0 0x55c369ae96d0 in __interceptor_malloc (***/reproduce-bugs-in-fuzzer-test-suite/src/sqlite-2016-11-14/reproducer+0xcb6d0)
    #1 0x55c369b2e753 in sqlite3MemMalloc ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:20478
    #2 0x55c369b2f14b in mallocWithAlarm ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:24147
    #3 0x55c369b2f1f6 in sqlite3Malloc ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:24178
    #4 0x55c369b2f9cc in dbMallocRawFinish ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:24504
    #5 0x55c369b2fb47 in sqlite3DbMallocRawNN ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:24572
    #6 0x55c369b2fb77 in sqlite3DbRealloc ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:24584
    #7 0x55c369b32214 in sqlite3StrAccumEnlarge ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:25523
    #8 0x55c369b32390 in enlargeAndAppend ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:25563
    #9 0x55c369b32418 in sqlite3StrAccumAppend ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:25581
    #10 0x55c369b3202e in sqlite3VXPrintf ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:25476
    #11 0x55c369b326bf in sqlite3VMPrintf ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:25667
    #12 0x55c369b86df2 in sqlite3NestedParse ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:98628
    #13 0x55c369b8d5a4 in sqlite3CreateIndex ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:101731
    #14 0x55c369bc6c55 in yy_reduce ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:135304
    #15 0x55c369bcaf50 in sqlite3Parser ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:136530
    #16 0x55c369bcbe15 in sqlite3RunParser ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:137477
    #17 0x55c369ba2629 in sqlite3Prepare ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:114208
    #18 0x55c369ba29a9 in sqlite3LockAndPrepare ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:114299
    #19 0x55c369ba2b98 in sqlite3_prepare_v2 ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:114375
    #20 0x55c369b9c059 in sqlite3_exec ../../fuzzer-test-suite/sqlite-2016-11-14/sqlite3.c:109705
    #21 0x55c369b2a7ba in LLVMFuzzerTestOneInput ../../fuzzer-test-suite/sqlite-2016-11-14/ossfuzz.c:78
    #22 0x55c369b2a147 in main ../main.cpp:42
    #23 0x7ff1d9f04bf6 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x21bf6)

SUMMARY: AddressSanitizer: heap-use-after-free (***/reproduce-bugs-in-fuzzer-test-suite/src/sqlite-2016-11-14/reproducer+0x662e2) in __interceptor_memcpy.part.234
Shadow bytes around the buggy address:
  0x0c1a7fff8040: 00 00 00 00 00 00 00 00 00 00 00 00 00 fa fa fa
  0x0c1a7fff8050: fa fa fa fa fa fa 00 00 00 00 00 00 00 00 00 00
  0x0c1a7fff8060: 00 00 00 00 00 00 00 00 fa fa fa fa fa fa fa fa
  0x0c1a7fff8070: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0c1a7fff8080: fd fa fa fa fa fa fa fa fa fa fd fd fd fd fd fd
=>0x0c1a7fff8090: fd fd fd fd fd fd[fd]fd fd fd fd fa fa fa fa fa
  0x0c1a7fff80a0: fa fa fa fa fd fd fd fd fd fd fd fd fd fd fd fd
  0x0c1a7fff80b0: fd fd fd fd fd fa fa fa fa fa fa fa fa fa fa fa
  0x0c1a7fff80c0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c1a7fff80d0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c1a7fff80e0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==2480==ABORTING
```