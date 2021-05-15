TARGET := reproducer
TARGET_NOASAN := $(TARGET).noasan

LIBXML2_DIR_NAME := libxml2
LIBXML2_LIB_DIR := $(LIBXML2_DIR_NAME)/.libs
LIBXML2_LIB_ORIG := $(LIBXML2_LIB_DIR)/libxml2.a
FUZZER_TEST_SUITE_TARGET_CC := ../../fuzzer-test-suite/libxml2-v2.9.2/target.cc

CFLAGS := -g
CFLAGS_ASAN := $(CFLAGS) -fno-omit-frame-pointer -fsanitize=address -fsanitize-address-use-after-scope
CFLAGS_NOASAN := $(CFLAGS)

all: $(TARGET) $(TARGET_NOASAN)
	@

clean:
	rm -f $(TARGET) $(TARGET_NOASAN) $(LIBXML2_LIB_ORIG)

$(LIBXML2_LIB_ORIG):
	# cd $(LIBXML2_DIR_NAME) && git clean -dfx
	# cd $(LIBXML2_DIR_NAME) && git checkout -f v2.9.2
	cd $(LIBXML2_DIR_NAME) && ./autogen.sh
	cd $(LIBXML2_DIR_NAME) && CCLD="$(CC) $(CFLAGS)" ./configure \
		--without-python --with-threads=no \
		--with-zlib=no --with-lzma=no
	cd $(LIBXML2_DIR_NAME) && make -j $(nproc)

define build_main
	$(CXX) $(1) -I $(LIBXML2_DIR_NAME)/include \
		$< $(FUZZER_TEST_SUITE_TARGET_CC) \
		$(LIBXML2_LIB_ORIG) \
		-static-libasan
		-o $@
endef

$(TARGET): main.cpp $(LIBXML2_LIB_ORIG)
	$(call build_main,$(CFLAGS_ASAN))

$(TARGET_NOASAN): main.cpp $(LIBXML2_LIB_ORIG)
	$(call build_main,$(CFLAGS_NOASAN))


reproduce: $(TARGET)
	./$(TARGET) ../../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28