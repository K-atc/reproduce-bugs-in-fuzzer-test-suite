TARGET := reproducer
TARGET_NOASAN := $(TARGET).noasan

LIBXML2_DIR_NAME := libxml2
LIBXML2_LIB_DIR := $(LIBXML2_DIR_NAME)/.libs
LIBXML2_LIB_ORIG := $(LIBXML2_LIB_DIR)/libxml2.a
LIBXML2_LIB_ASAN := $(LIBXML2_LIB_DIR)/libxml2-asan.a
LIBXML2_LIB_NOASAN := $(LIBXML2_LIB_DIR)/libxml2-noasan.a
FUZZER_TEST_SUITE_TARGET_CC := ../../fuzzer-test-suite/libxml2-v2.9.2/target.cc

CFLAGS := -g
CFLAGS_ASAN := $(CFLAGS) -fno-omit-frame-pointer -fsanitize=address -fsanitize-address-use-after-scope
CFLAGS_NOASAN := $(CFLAGS)

all: $(TARGET)
	@

clean:
	rm -f $(TARGET) $(TARGET_NOASAN) $(LIBXML2_LIB_ASAN) $(LIBXML2_LIB_NOASAN)

define build_lib
	cd $(LIBXML2_DIR_NAME) && git clean -dfx
	cd $(LIBXML2_DIR_NAME) && git checkout -f v2.9.2
	cd $(LIBXML2_DIR_NAME) && ./autogen.sh
	cd $(LIBXML2_DIR_NAME) && CCLD="$(CC) $(1)" ./configure \
		--without-python --with-threads=no \
		--with-zlib=no --with-lzma=no
	cd $(LIBXML2_DIR_NAME) && make -j $(nproc)
	mv $(LIBXML2_LIB_ORIG) $@
	ls $@
endef

define build_main
	$(CXX) $(1) -I $(LIBXML2_DIR_NAME)/include \
		-c $(FUZZER_TEST_SUITE_TARGET_CC) \
		-o $(FUZZER_TEST_SUITE_TARGET_CC).o
	$(CXX) $(1) \
		$< $(FUZZER_TEST_SUITE_TARGET_CC).o \
		$(2) \
		-o $@
endef

$(LIBXML2_LIB_ASAN): 
	$(call build_lib,$(CFLAGS_ASAN))

$(LIBXML2_LIB_DIR)/$(LIBXML2_LIB_NOASAN_NAME): 
	$(call build_lib,$(CFLAGS_NOASAN))

$(TARGET): main.cpp $(LIBXML2_LIB_ASAN)
	$(call build_main,$(CFLAGS_ASAN),$(LIBXML2_LIB_ASAN))

$(TARGET_NOASAN): main.cpp $(LIBXML2_LIB_NOASAN)
	$(call build_main,$(CFLAGS_NOASAN),$(LIBXML2_LIB_NOASAN))


reproduce: $(TARGET)
	./$(TARGET) ../../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28