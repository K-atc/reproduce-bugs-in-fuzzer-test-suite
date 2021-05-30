TARGET := reproducer
TARGET_NOASAN := $(TARGET).noasan
PROJECT_ROOT_DIR := ../..
INPUT_DIR := $(PROJECT_ROOT_DIR)/input/woff2-2016-05-06
CRASH_INPUT := $(PROJECT_ROOT_DIR)/fuzzer-test-suite/woff2-2016-05-06/crash-696cb49b6d7f63e153a6605f00aceb0d7738971a
NORMAL_WOFF2_FILE := $(INPUT_DIR)/Roboto-Regular.woff2

EXTLIB_DIR_NAME := woff2
EXTDEPLIB_DIR_NAME := brotli
EXTLIB_LIB_DIR := $(EXTLIB_DIR_NAME)/.libs

WOFF_SRC_FILES := font.cc normalize.cc transform.cc woff2_common.cc woff2_dec.cc woff2_enc.cc glyph.cc table_tags.cc variable_length.cc woff2_out.cc
EXTLIB_OBJ := $(subst .cc,.o,$(WOFF_SRC_FILES))
BROTIL_DEC_C := bit_reader.c decode.c dictionary.c huffman.c state.c
### NOTE: Do not include `dictionary.cc` to avoid multiple definitions
BROTIL_ENC_CC := backward_references.cc compress_fragment_two_pass.cc entropy_encode.cc static_dict.cc block_splitter.cc histogram.cc streams.cc brotli_bit_stream.cc encode.cc literal_cost.cc utf8_util.cc compress_fragment.cc encode_parallel.cc metablock.cc
EXTDEPLIB_OBJ_DEC := $(subst .c,.o,$(BROTIL_DEC_C))
EXTDEPLIB_OBJ_ENC := $(subst .cc,.o,$(BROTIL_ENC_CC))
EXTDEPLIB_OBJ := $(EXTDEPLIB_OBJ_DEC) $(EXTDEPLIB_OBJ_ENC)
FUZZER_TEST_SUITE_TARGET_CC := $(PROJECT_ROOT_DIR)/fuzzer-test-suite/woff2-2016-05-06/target.cc

CFLAGS := -g
CXXFLAGS := $(CFLAGS)
CFLAGS_ASAN := $(CFLAGS) -fsanitize=address

all: $(TARGET) $(TARGET_NOASAN)
	@

clean:
	rm -f $(TARGET) $(TARGET_NOASAN) *.o

define setup_extdeplib
	cd $(EXTDEPLIB_DIR_NAME) && git checkout -f 3a9032ba8733532a6cd6727970bade7f7c0e2f52
endef

define build_main
	$(CXX) $(1) -I $(EXTLIB_DIR_NAME)/src \
		$^ $(FUZZER_TEST_SUITE_TARGET_CC) \
		-static-libasan \
		-o $@
endef

$(EXTLIB_OBJ): $(addprefix $(EXTLIB_DIR_NAME)/src/,$(WOFF_SRC_FILES))
	cd $(EXTLIB_DIR_NAME) && git checkout -f 9476664fd6931ea6ec532c94b816d8fbbe3aed90
	$(CXX) $(CXXFLAGS) -std=c++11 -I $(EXTDEPLIB_DIR_NAME)/dec -I $(EXTDEPLIB_DIR_NAME)/enc -c $^

$(EXTDEPLIB_OBJ_DEC): $(addprefix $(EXTDEPLIB_DIR_NAME)/dec/,$(BROTIL_DEC_C))
	$(call setup_extdeplib)
	$(CXX) $(CXXFLAGS) -c $^

$(EXTDEPLIB_OBJ_ENC): $(addprefix $(EXTDEPLIB_DIR_NAME)/enc/,$(BROTIL_ENC_CC))
	$(call setup_extdeplib)
	$(CXX) $(CXXFLAGS) -c $^

$(TARGET): ../main.cpp $(EXTLIB_OBJ) $(EXTDEPLIB_OBJ)
	$(call build_main,$(CFLAGS_ASAN),$(EXTLIB_OBJ))

$(TARGET_NOASAN): ../main.cpp $(EXTLIB_OBJ) $(EXTDEPLIB_OBJ)
	$(call build_main,$(CFLAGS),$(EXTLIB_OBJ))

$(INPUT_DIR):
	mkdir -p $@

$(NORMAL_WOFF2_FILE):
	curl -o $@ -L https://github.com/FontFaceKit/roboto/raw/v1.5.1/fonts/Regular/Roboto-Regular.woff2

input: $(INPUT_DIR) $(NORMAL_WOFF2_FILE)
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 774f 4632 0001 0000 0000 f0cc/00000000: 774f 4632 0001 0000 0000 0010/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).length-00000010
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 774f 4632 0001 0000 0000 f0cc/00000000: 774f 4632 0001 0000 0000 1000/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).length-00001000
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 774f 4632 0001 0000 0000 f0cc/00000000: 774f 4632 0001 0000 0000 EE00/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).length-0000ee00
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 774f 4632 0001 0000 0000 f0cc/00000000: 774f 4632 0001 0000 0000 F000/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).length-0000f000

	@### Check if a field does not depends on bug
	@#xxd $(CRASH_INPUT) | sed -e 's/00000010: 0002 80c4 0000 f069 0002 0000/00000010: 0002 80c4 0000 f069 0001 0000/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).major-version-1
	
	@### Check which field depends on bug
	xxd $(NORMAL_WOFF2_FILE) | sed -e 's/00000040: 5409 833c 110c 0a87 dc24 86fb 730b 941e/00000040: 5409 833c 110c 0a87 dc24 8181 000b 941e/' | xxd -r > $(NORMAL_WOFF2_FILE).offset-4a-818100

	@### Check if content length is required to reproduce bug
	xxd $(CRASH_INPUT) | head -n 16 | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).trim-at-offset-0x100
	xxd $(CRASH_INPUT) | head -n 256 | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).trim-at-offset-0x1000
	xxd $(CRASH_INPUT) | head -n 512 | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).trim-at-offset-0x2000
	xxd $(CRASH_INPUT) | head -n 1024 | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).trim-at-offset-0x4000
	xxd $(CRASH_INPUT) | head -n 2048 | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).trim-at-offset-0x8000

	@### Check if content body does not matter to reproduce bug
	(xxd $(CRASH_INPUT) | head -n 3 | xxd -r; head -c 61596 /dev/urandom) > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).header-only.add-random-bytes
	
	(xxd $(CRASH_INPUT) | head -n 7 | xxd -r; head -c 61532 /dev/urandom) > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).WOFF2Header-and-TableDirectory-only.add-random-bytes
	(xxd $(CRASH_INPUT) | head -n 7 | xxd -r; xxd $(NORMAL_WOFF2_FILE) | grep -v 000000[0-6]0 | xxd -r) > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).WOFF2Header-and-TableDirectory-only.add-rest-of-normal-woff2-file

	@### Check if legitimate content body does not depends on bug
	xxd $(NORMAL_WOFF2_FILE) | sed -e 's/00000000: 774f 4632 0001 0000 .... ..../00000000: 774f 4632 0001 0000 0000 f0cc/' | xxd -r > $(NORMAL_WOFF2_FILE).length-0000f0cc
	xxd $(NORMAL_WOFF2_FILE).length-0000f0cc | sed -e 's/00000010: .... .... .... ..../00000010: 0002 80C4 0000 F069/' | xxd -r > $(NORMAL_WOFF2_FILE).length-0000f0cc.totalSfntSize-000280c4.totalCompressedSize-0000f069
	@#(cat $(NORMAL_WOFF2_FILE).length-0000f0cc.totalSfntSize-000280c4.totalCompressedSize-0000f069; head -c 62000 /dev/urandom) > $(NORMAL_WOFF2_FILE).length-0000f0cc.totalSfntSize-000280c4.totalCompressedSize-0000f069.add-bulk-data


check-input: input
	find $(INPUT_DIR)/* | xargs -n1 ./$(TARGET)

reproduce: $(TARGET)
	./$(TARGET) $(CRASH_INPUT)