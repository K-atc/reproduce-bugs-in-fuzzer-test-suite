Reproduce bugs in https://github.com/google/fuzzer-test-suite
====


Requirements
----
* LLVM 12


How to build
----
### batch build
```shell
git submodule init
git submodule update
make
```

### build a target
For example, 

```shell
cd src/openssl-1.0.1f
make
```


How to reproduce
----
### Using docker
```
$ docker run --rm -it -v $PWD:/app --workdir /app/src/openssl-1.0.1f ubuntu:20.04 ./reproducer /app/fuzzer-test-suite/openssl-1.0.1f/leak-268f0e85f4bc45c
baf4d257222b830eac18977f3

=================================================================
==1==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 32 byte(s) in 1 object(s) allocated from:
    #0 0x555a4576f690 in __interceptor_malloc (/app/src/openssl-1.0.1f/reproducer+0xf8690)
    #1 0x555a457e98f2 in CRYPTO_malloc (/app/src/openssl-1.0.1f/reproducer+0x1728f2)

Indirect leak of 32 byte(s) in 1 object(s) allocated from:
    #0 0x555a4576f690 in __interceptor_malloc (/app/src/openssl-1.0.1f/reproducer+0xf8690)
    #1 0x555a457e98f2 in CRYPTO_malloc (/app/src/openssl-1.0.1f/reproducer+0x1728f2)

SUMMARY: AddressSanitizer: 64 byte(s) leaked in 2 allocation(s).
```