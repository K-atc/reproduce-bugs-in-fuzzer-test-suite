TARGET := reproducer
TARGET_NOASAN := $(TARGET).noasan

EXTLIB_DIR_NAME := libxml2
EXTLIB_LIB := $(EXTLIB_DIR_NAME)/.libs/libxml2.a
FUZZER_TEST_SUITE_TARGET_CC := ../../fuzzer-test-suite/libxml2-v2.9.2/target.cc

DOCKER_RUN_PREFIX := docker run --rm -it -u $(shell id -u ${USER}):$(shell id -g ${USER}) -v $(PWD)/../..:/app
CXX_GCC_74 := $(DOCKER_RUN_PREFIX) --workdir /app/src/libxml2-v2.9.2 gcc:7.4 g++
CXX_GCC_84 := $(DOCKER_RUN_PREFIX) --workdir /app/src/libxml2-v2.9.2 gcc:8.4 g++
MAKE_GCC_OLD := $(DOCKER_RUN_PREFIX) --workdir /app/src/libxml2-v2.9.2/$(EXTLIB_DIR_NAME) gcc:5.3 make
### NOTE: libxml requires gcc

CC := clang
CXX := clang++
# CXX := $(CXX_GCC_84)
CFLAGS := -g -O2
CFLAGS_ASAN := $(CFLAGS) -fsanitize=address
CFLAGS_NOASAN := $(CFLAGS)
# MAKE := $(MAKE_GCC_OLD)

all: $(TARGET) $(TARGET_NOASAN)
	@

clean:
	rm -f $(TARGET) $(TARGET_NOASAN) $(EXTLIB_LIB)

$(EXTLIB_LIB):
	cd $(EXTLIB_DIR_NAME) && git clean -dfx
	cd $(EXTLIB_DIR_NAME) && git checkout -f v2.9.2
	cd $(EXTLIB_DIR_NAME) && ./autogen.sh
	cd $(EXTLIB_DIR_NAME) && CC=$(CC) CFLAGS="$(CFLAGS)" ./configure \
		--without-python --with-threads=no \
		--with-zlib=no --with-lzma=no
	cd $(EXTLIB_DIR_NAME) && $(MAKE) CFLAGS="$(CFLAGS) -fPIC" -j $(nproc)

define build_main
	$(CXX) $(1) \
		$(FUZZER_TEST_SUITE_TARGET_CC) $^ \
		-I $(EXTLIB_DIR_NAME)/include \
		-o $@
endef

$(TARGET): ../main.cpp $(EXTLIB_LIB)
	$(call build_main,$(CFLAGS_ASAN))
	nm $@ | grep asan > /dev/null

$(TARGET_NOASAN): ../main.cpp $(EXTLIB_LIB)
	$(call build_main,$(CFLAGS_NOASAN))
	nm $@ | grep xmlReadMemory


reproduce: $(TARGET)
	./$(TARGET) ../../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28
	./$(TARGET) ../../fuzzer-test-suite/libxml2-v2.9.2/crash-d8960e21ca40ea5dc60ad655000842376d4178a1
	./$(TARGET) ../../fuzzer-test-suite/libxml2-v2.9.2/leak-bdbb2857b7a086f003db1c418e1d124181341fb1
	./$(TARGET) ../../fuzzer-test-suite/libxml2-v2.9.2/uaf-1153fbf466b9474e6e3c48c72e86a4726b449ef7

reproduce-in-docker: $(TARGET)
	$(DOCKER_RUN_PREFIX) --workdir /app/src/libxml2-v2.9.2 ubuntu:18.04 ./reproducer ../../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28