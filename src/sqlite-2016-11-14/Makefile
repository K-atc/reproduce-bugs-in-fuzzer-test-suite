TARGET := reproducer
TARGET_NOASAN := $(TARGET).noasan

EXTLIB_DIR := ../../fuzzer-test-suite/sqlite-2016-11-14
EXTLIB_LIB := $(EXTLIB_DIR)/sqlite3.o
FUZZER_TEST_SUITE_TARGET_CC := ../../fuzzer-test-suite/sqlite-2016-11-14/ossfuzz.c

CFLAGS := -g
CFLAGS_ASAN := $(CFLAGS) -fsanitize=address

all: $(TARGET) $(TARGET_NOASAN)
	@

clean:
	rm -f $(TARGET) $(TARGET_NOASAN) $(EXTLIB_LIB)

EXTLIB_LIB: $(subst .o,.c,$(EXTLIB_LIB))
	$(CC) $(CFLAGS) -c $^ -o $(EXTLIB_LIB)

define build_main
	sed -ie 's/^int LLVMFuzzerTestOneInput/extern \"C\" int LLVMFuzzerTestOneInput/' $(FUZZER_TEST_SUITE_TARGET_CC)
	$(CXX) $(1) -I $(EXTLIB_DIR) \
		$< $(FUZZER_TEST_SUITE_TARGET_CC) \
		$(EXTLIB_LIB) \
		-ldl -pthread \
		-static-libasan \
		-o $@
endef

$(TARGET): ../main.cpp $(EXTLIB_LIB)
	$(call build_main,$(CFLAGS_ASAN))

$(TARGET_NOASAN): ../main.cpp $(EXTLIB_LIB)
	$(call build_main,$(CFLAGS))


reproduce: $(TARGET)
	./$(TARGET) ../../fuzzer-test-suite/sqlite-2016-11-14/crash-0adc497ccfcc1a4d5e031b735c599df0cae3f4eb # => Does not reproduce a bug
	./$(TARGET) ../../fuzzer-test-suite/sqlite-2016-11-14/crash-1066e42866aad3a04e6851dc494ad54bc31b9f78