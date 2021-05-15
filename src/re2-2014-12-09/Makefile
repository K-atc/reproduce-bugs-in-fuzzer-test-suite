TARGET := reproducer
TARGET_NOASAN := $(TARGET).noasan
PROJECT_ROOT_DIR := ../..
CRASH_INPUT := $(PROJECT_ROOT_DIR)/fuzzer-test-suite/re2-2014-12-09/crash-a23ed2a04358b9c070c603a5af6ae2b34598664a
INPUT_DIR := $(PROJECT_ROOT_DIR)/input/re2-2014-12-09

EXTLIB_DIR_NAME := re2
LIBXML2_LIB_DIR := $(EXTLIB_DIR_NAME)/obj
EXTLIB_LIB := $(LIBXML2_LIB_DIR)/libre2.a
FUZZER_TEST_SUITE_TARGET_CC := $(PROJECT_ROOT_DIR)/fuzzer-test-suite/re2-2014-12-09/target.cc

CFLAGS := -g
CFLAGS_ASAN := $(CFLAGS) -fsanitize=address
CFLAGS_NOASAN := $(CFLAGS)

all: $(TARGET) $(TARGET_NOASAN)
	@

clean:
	rm -f $(TARGET) $(TARGET_NOASAN) $(EXTLIB_LIB)

$(EXTLIB_LIB):
	cd $(EXTLIB_DIR_NAME) && git checkout -f 499ef7eff7455ce9c9fae86111d4a77b6ac335de 
	cd $(EXTLIB_DIR_NAME) && make clean && make CC=$(CC) CFLAGS="$(CFLAGS)" -j $(nproc) obj/libre2.a

define build_main
	$(CXX) $(1) -I $(EXTLIB_DIR_NAME) \
		$< $(FUZZER_TEST_SUITE_TARGET_CC) \
		$(EXTLIB_LIB) \
		-lpthread \
		-static-libasan \
		-o $@
endef

$(TARGET): ../main.cpp $(EXTLIB_LIB)
	$(call build_main,$(CFLAGS_ASAN))

$(TARGET_NOASAN): ../main.cpp $(EXTLIB_LIB)
	$(call build_main,$(CFLAGS_NOASAN))

$(INPUT_DIR):
	mkdir -p $@

input: $(INPUT_DIR)
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 0027/00000000: 4141/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).offset-0-4141
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 0027/00000000: 4127/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).offset-0-4127

check-input: input
	find $(INPUT_DIR)/* | xargs -n1 ./$(TARGET)

reproduce: $(TARGET)
	./$(TARGET) $(CRASH_INPUT)