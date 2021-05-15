TARGET := reproducer
TARGET_NOASAN := $(TARGET).noasan

LIBXML2_DIR_NAME := libxml2
LIBXML2_LIB_DIR := $(LIBXML2_DIR_NAME)/.libs
LIBXML2_LIB_ORIG := $(LIBXML2_LIB_DIR)/libxml2.a
FUZZER_TEST_SUITE_TARGET_CC := ../../fuzzer-test-suite/libxml2-v2.9.2/target.cc

MAKE_GCC_OLD := docker run --rm -it -u $(shell id -u ${USER}):$(shell id -g ${USER}) -v $(PWD)/../..:/app --workdir /app/src/libxml2-v2.9.2/$(LIBXML2_DIR_NAME) gcc:5.3 make
# MAKE_CLANG := docker run --rm -it -u $(shell id -u ${USER}):$(shell id -g ${USER}) -v $(PWD)/../..:/app --workdir /app/src/libxml2-v2.9.2/$(LIBXML2_DIR_NAME) silkeh/clang:7 make
### NOTE: libxml requires gcc

CFLAGS := -g
CFLAGS_ASAN := $(CFLAGS) -fsanitize=address
# CFLAGS_ASAN := $(CFLAGS) -fsanitize=address -fsanitize=array-bounds,bool,builtin,enum,float-divide-by-zero,function,integer-divide-by-zero,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,unreachable,vla-bound,vptr
CFLAGS_NOASAN := $(CFLAGS)

all: $(TARGET) $(TARGET_NOASAN)
	@

clean:
	rm -f $(TARGET) $(TARGET_NOASAN) $(LIBXML2_LIB_ORIG)

$(LIBXML2_LIB_ORIG):
	cd $(LIBXML2_DIR_NAME) && git clean -dfx
	cd $(LIBXML2_DIR_NAME) && git checkout -f v2.9.2
	cd $(LIBXML2_DIR_NAME) && ./autogen.sh
	cd $(LIBXML2_DIR_NAME) && ./configure \
		--without-python --with-threads=no \
		--with-zlib=no --with-lzma=no
	cd $(LIBXML2_DIR_NAME) && $(MAKE_GCC_OLD) CFLAGS="$(CFLAGS) -fPIC" -j $(nproc)

define build_main
	$(CXX) $(1) -I $(LIBXML2_DIR_NAME)/include \
		$< $(FUZZER_TEST_SUITE_TARGET_CC) \
		$(LIBXML2_LIB_ORIG) \
		-static-libasan \
		-o $@
endef

$(TARGET): ../main.cpp $(LIBXML2_LIB_ORIG)
	$(call build_main,$(CFLAGS_ASAN))

$(TARGET_NOASAN): ../main.cpp $(LIBXML2_LIB_ORIG)
	$(call build_main,$(CFLAGS_NOASAN))


reproduce: $(TARGET)
	./$(TARGET) ../../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28

reproduce-in-docker: $(TARGET)
	docker run --rm -it -v $(PWD)/../..:/app --workdir /app/src/libxml2-v2.9.2 ubuntu:18.04 ./reproducer ../../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28