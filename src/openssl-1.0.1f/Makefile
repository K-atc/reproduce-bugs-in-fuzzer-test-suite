TARGET := reproducer
TARGET_NOASAN := $(TARGET).noasan

EXTLIB_DIR_NAME := openssl
LIBXML2_LIB_DIR := $(EXTLIB_DIR_NAME)
EXTLIB_LIB := $(LIBXML2_LIB_DIR)/libssl.a $(LIBXML2_LIB_DIR)/libcrypto.a
FUZZER_TEST_SUITE_TARGET_CC := ../../fuzzer-test-suite/openssl-1.0.1f/target.cc

CFLAGS := -g
CFLAGS_ASAN := $(CFLAGS) -fsanitize=address
CFLAGS_NOASAN := $(CFLAGS)

all: $(TARGET) $(TARGET_NOASAN)
	@

clean:
	rm -f $(TARGET) $(TARGET_NOASAN) $(EXTLIB_LIB)

$(EXTLIB_LIB):
	cd $(EXTLIB_DIR_NAME) && git checkout -f OpenSSL_1_0_1f 
	cd $(EXTLIB_DIR_NAME) && CC=$(CC) CFLAGS="$(CFLAGS)" ./config && make clean && make

runtime/:
	ln -s ../../fuzzer-test-suite/openssl-1.0.1f/runtime .

define build_main
	$(CXX) $(1) -I $(EXTLIB_DIR_NAME)/include \
		$< $(FUZZER_TEST_SUITE_TARGET_CC) \
		$(EXTLIB_LIB) \
		-ldl \
		-static-libasan \
		-o $@
endef

$(TARGET): main.cpp $(EXTLIB_LIB) runtime/
	$(call build_main,$(CFLAGS_ASAN))

$(TARGET_NOASAN): main.cpp $(EXTLIB_LIB) runtime/
	$(call build_main,$(CFLAGS_NOASAN))


reproduce: $(TARGET)
	./$(TARGET) ../../fuzzer-test-suite/openssl-1.0.1f/leak-268f0e85f4bc45cbaf4d257222b830eac18977f3