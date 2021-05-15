FXIME: Seems CVE-2015-8317 is not reproduced.


How to reproduce
----
### On local environment
```shell
./reproducer ../../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28
```

### Using docker
```shell
docker run --rm -it -v $PWD/../..:/app --workdir /app/src/libxml2-v2.9.2 ubuntu:20.04 ./reproducer ../../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28
```