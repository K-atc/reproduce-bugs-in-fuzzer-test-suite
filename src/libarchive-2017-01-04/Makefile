TARGET := reproducer
TARGET_NOASAN := $(TARGET).noasan

EXTLIB_DIR_NAME := libarchive
EXTLIB_LIB_DIR := $(EXTLIB_DIR_NAME)/.libs
EXTLIB_LIB_ORIG := $(EXTLIB_LIB_DIR)/libarchive.a
EXTLIB_LIB_ASAN := $(EXTLIB_LIB_DIR)/libarchive-asan.a
EXTLIB_LIB_NOASAN := $(EXTLIB_LIB_DIR)/libarchive-noasan.a
FUZZER_TEST_SUITE_TARGET_CC := ../../fuzzer-test-suite/libarchive-2017-01-04/libarchive_fuzzer.cc

CFLAGS := -g
CFLAGS_ASAN := $(CFLAGS) -fsanitize=address
CFLAGS_NOASAN := $(CFLAGS)

all: $(TARGET)
	@

clean:
	rm -f $(TARGET) $(TARGET_NOASAN) $(EXTLIB_LIB_ASAN) $(EXTLIB_LIB_NOASAN)

define build_lib
	cd $(EXTLIB_DIR_NAME) && git clean -dfx
	cd $(EXTLIB_DIR_NAME) && git checkout -f 51d7afd3644fdad725dd8faa7606b864fd125f88
	cd $(EXTLIB_DIR_NAME)/build && ./autogen.sh
	cd $(EXTLIB_DIR_NAME) && CC=$(CC) CFLAGS="$(1)" ./configure --disable-shared --without-nettle
	cd $(EXTLIB_DIR_NAME) && make -j $(nproc)
	mv $(EXTLIB_LIB_ORIG) $@
	ls $@
endef

define build_main
	$(CXX) $(1) -I $(EXTLIB_DIR_NAME)/include \
		-c $(FUZZER_TEST_SUITE_TARGET_CC) \
		-o $(FUZZER_TEST_SUITE_TARGET_CC).o
	$(CXX) $(1) \
		$< $(FUZZER_TEST_SUITE_TARGET_CC).o \
		$(2) \
		-o $@
endef

$(EXTLIB_LIB_ASAN): 
	$(call build_lib,$(CFLAGS_ASAN))

$(EXTLIB_LIB_DIR)/$(EXTLIB_LIB_NOASAN_NAME): 
	$(call build_lib,$(CFLAGS_NOASAN))

$(TARGET): ../main.cpp $(EXTLIB_LIB_ASAN)
	$(call build_main,$(CFLAGS_ASAN),$(EXTLIB_LIB_ASAN))

$(TARGET_NOASAN): ../main.cpp $(EXTLIB_LIB_NOASAN)
	$(call build_main,$(CFLAGS_NOASAN),$(EXTLIB_LIB_NOASAN))


reproduce: $(TARGET)
	./$(TARGET) ../../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28