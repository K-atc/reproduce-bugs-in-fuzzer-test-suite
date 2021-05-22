TARGET := reproducer
TARGET_NOASAN := $(TARGET).noasan
PROJECT_ROOT_DIR := ../..
INPUT_DIR := $(PROJECT_ROOT_DIR)/input/sqlite-2016-11-14

EXTLIB_DIR := $(PROJECT_ROOT_DIR)/fuzzer-test-suite/sqlite-2016-11-14
EXTLIB_LIB := $(EXTLIB_DIR)/sqlite3.o
FUZZER_TEST_SUITE_TARGET_CC := $(PROJECT_ROOT_DIR)/fuzzer-test-suite/sqlite-2016-11-14/ossfuzz.c

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

$(INPUT_DIR):
	mkdir -p $@

input: $(INPUT_DIR)
	( \
		echo "00000000: 2043 5245 4154 4520 2074 6162 6c65 2020"; \
		echo "00000010: 2020 2020 2020 ba20 2028 4156 4550 4f49"; \
		echo "00000020: 4e54 2049 4e54 2055 4e49 5155 4520 554e"; \
		echo "00000030: 4951 5545 0020 2020 2020 2020 2020 4352"; \
	) | xxd -r > $(INPUT_DIR)/minimize
	/bin/echo -ne "CREATE table \xff(AVEPOINT INT UNIQUE UNIQUE" > $(INPUT_DIR)/minimize.no-space
	/bin/echo -ne "CREATE table \xff(AVEPOINT INT UNIQUE" > $(INPUT_DIR)/minimize.no-space.trim-unique
	/bin/echo -ne "CREATE table \xff(AVEPOINT INT" > $(INPUT_DIR)/minimize.no-space.trim-unique.trim-unique
	/bin/echo -ne "CREATE table \xff(AVEPOINT" > $(INPUT_DIR)/minimize.no-space.trim-unique.trim-unique.trim-int

check-input: input
	find $(INPUT_DIR)/* | xargs -n1 ./$(TARGET)

reproduce: $(TARGET)
	./$(TARGET) ../../fuzzer-test-suite/sqlite-2016-11-14/crash-0adc497ccfcc1a4d5e031b735c599df0cae3f4eb # => Does not reproduce a bug
	./$(TARGET) ../../fuzzer-test-suite/sqlite-2016-11-14/crash-1066e42866aad3a04e6851dc494ad54bc31b9f78