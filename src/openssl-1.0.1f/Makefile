TARGET := reproducer
TARGET_NOASAN := $(TARGET).noasan
PROJECT_ROOT_DIR := ../..
INPUT_DIR := $(PROJECT_ROOT_DIR)/input/openssl-1.0.1f
CRASH_INPUT := $(PROJECT_ROOT_DIR)/fuzzer-test-suite/openssl-1.0.1f/leak-268f0e85f4bc45cbaf4d257222b830eac18977f3

EXTLIB_DIR_NAME := openssl
LIBXML2_LIB_DIR := $(EXTLIB_DIR_NAME)
EXTLIB_LIB := $(LIBXML2_LIB_DIR)/libssl.a $(LIBXML2_LIB_DIR)/libcrypto.a
FUZZER_TEST_SUITE_TARGET_CC := $(PROJECT_ROOT_DIR)/fuzzer-test-suite/openssl-1.0.1f/target.cc

CFLAGS := -g
CFLAGS_ASAN := $(CFLAGS) -fsanitize=address
CFLAGS_NOASAN := $(CFLAGS)
ASAN_OPTIONS := ASAN_OPTIONS=symbolize=1

all: $(TARGET) $(TARGET_NOASAN)
	@

clean:
	rm -f $(TARGET) $(TARGET_NOASAN) $(EXTLIB_LIB)

$(EXTLIB_LIB):
	cd $(EXTLIB_DIR_NAME) && git checkout -f OpenSSL_1_0_1f 
	cd $(EXTLIB_DIR_NAME) && CC=$(CC) CFLAGS="$(CFLAGS)" ./config && make clean && make

runtime/:
	ln -s $(PROJECT_ROOT_DIR)/fuzzer-test-suite/openssl-1.0.1f/runtime .

define build_main
	$(CXX) $(1) -I $(EXTLIB_DIR_NAME)/include \
		$< $(FUZZER_TEST_SUITE_TARGET_CC) \
		$(EXTLIB_LIB) \
		-ldl \
		-static-libasan \
		-o $@
endef

$(TARGET): ../main.cpp $(EXTLIB_LIB) runtime/
	$(call build_main,$(CFLAGS_ASAN))

$(TARGET_NOASAN): ../main.cpp $(EXTLIB_LIB) runtime/
	$(call build_main,$(CFLAGS_NOASAN))

$(INPUT_DIR):
	mkdir -p $@xxd


input: $(INPUT_DIR)
	( \
		echo "00000000: 1603 0000 0301 0000 1603 0000 dcad ff00"; \
		echo "00000010: 0000 0000 0000 0000 0000 0000 0000 0000"; \
		echo "00000020: 0000 0000 0000 0000 0000 0000 0000 0000"; \
		echo "00000030: 0000 0006 0000 0000 0000 0000 0f0f 0000"; \
		echo "00000040: 000e 0028 0000 0000 0000 0000 0000 0000"; \
		echo "00000050: 0000 0000 0000 0000 0000 0000 0000 0000"; \
		echo "00000060: 0000 0000 0000 0000 0000 0000 0000 0000"; \
		echo "00000070: 0000 0000 0000 0000 0000 0000 0000 0000"; \
		echo "00000080: 0000 0000 0000 0000 0000 0000 0000 0000"; \
		echo "00000090: 0000 0000 0000 0000 0000 0000 0000 0000"; \
		echo "000000a0: 0000 0000 0000 0000 0000 0000 0000 0000"; \
		echo "000000b0: 0000 0000 0000 0000 0000 0000 0000 0000"; \
		echo "000000c0: 0000 0000 0000 0000 0000 0000 0000 0000"; \
		echo "000000d0: 0000 0000 0000 0000 0000 0000 0000 0000"; \
		echo "000000e0: 0000 0000 0000 0000 0000 0000 0000 0000"; \
		echo "000000f0: 0000 0000 0000 0000 0000 0000 0000 0000"; \
	 ) | xxd -r > $(INPUT_DIR)/minimum

	xxd $(CRASH_INPUT) | sed -n 1,2p | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).until-offset-1f
	xxd $(CRASH_INPUT) | sed -n 1,3p | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).until-offset-2f
	xxd $(CRASH_INPUT) | sed -n 1,4p | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).until-offset-3f
	xxd $(CRASH_INPUT) | sed -n 1,6p | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).until-offset-5f
	xxd $(CRASH_INPUT) | sed -n 1,8p | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).until-offset-7f
	xxd $(CRASH_INPUT) | sed -n 1,10p | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).until-offset-9f
	xxd $(CRASH_INPUT) | sed -n 1,12p | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).until-offset-bf
	xxd $(CRASH_INPUT) | sed -n 1,14p | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).until-offset-df
	xxd $(CRASH_INPUT) | sed -n 1,15p | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).until-offset-ef

	# xxd $(CRASH_INPUT) | sed -e 's/00000000: 1603 0f00 0301/00000000: 1603 0f20 0001/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).offset-03-2000
	# xxd $(CRASH_INPUT) | sed -e 's/00000000: 1603 0f00 0301 0000 1603/00000000: 1603 0f00 0301 2000 0003/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).offset-06-200000
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 1603 0f00 0301 0000 1603 0700 dcad 29ad/00000000: 1603 0f00 0301 0000 1603 0700 0020 29ad/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).offset-0c-0020
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 1603 0f00 0301 0000 1603 0700 dcad 29ad/00000000: 1603 0f00 0301 0000 1603 0700 dcad 0020/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).offset-0e-0020
	xxd $(CRASH_INPUT) | sed -e 's/00000010: adad/00000010: 0020/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).offset-10-0020
	xxd $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).offset-0c-0020 | sed -e 's/00000010: adad/00000010: 0020/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).offset-0c-0020.offset-10-0020
	xxd $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).offset-0e-0020 | sed -e 's/00000010: adad/00000010: 0020/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).offset-0e-0020.offset-10-0020

check-input: input
	find $(INPUT_DIR)/* | xargs -n1 ./$(TARGET)

reproduce: $(TARGET)
	$(ASAN_OPTIONS) ./$(TARGET) $(CRASH_INPUT)