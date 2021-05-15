TARGET := reproducer
TARGET_NOASAN := $(TARGET).noasan
PROJECT_ROOT_DIR := ../..
INPUT_DIR := $(PROJECT_ROOT_DIR)/input/woff2-2016-05-06
CRASH_INPUT := $(PROJECT_ROOT_DIR)/fuzzer-test-suite/woff2-2016-05-06/crash-696cb49b6d7f63e153a6605f00aceb0d7738971a

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

$(INPUT_DIR)/OpenSans.woff:
	curl -o $@ $$(curl -s -A "Mozilla/5.0 (Windows NT 6.3; WOW64; Trident/7.0; Touch; .NET4.0E; .NET4.0C; .NET CLR 3.5.30729; .NET CLR 2.0.50727; .NET CLR 3.0.30729; Tablet PC 2.0; rv:11.0) like Gecko" https://fonts.googleapis.com/css?family=Open+Sans | grep -o https.*[.]woff)

input: $(INPUT_DIR) $(INPUT_DIR)/OpenSans.woff
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 774f 4632 0001 0000 0000 f0cc/00000000: 774f 4632 0001 0000 0010 0000/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).length-1000
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 774f 4632 0001 0000 0000 f0cc/00000000: 774f 4632 0001 0000 0000 1000/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).length-100000
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 774f 4632 0001 0000 0000 f0cc/00000000: 774f 4632 0001 0000 0000 0010/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).length-10000000
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 774f 4632 0001 0000 0000 f0cc/00000000: 774f 4632 0001 0000 0000 00CC/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).length-cc000000
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 774f 4632 0001 0000 0000 f0cc/00000000: 774f 4632 0001 0000 0000 10CC/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).length-cc100000
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 774f 4632 0001 0000 0000 f0cc/00000000: 774f 4632 0001 0000 0000 E0CC/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).length-cce00000
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 774f 4632 0001 0000 0000 f0cc/00000000: 774f 4632 0001 0000 0000 EECC/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).length-ccee0000
	xxd $(CRASH_INPUT) | sed -e 's/00000000: 774f 4632 0001 0000 0000 f0cc/00000000: 774f 4632 0001 0000 0000 F0CC/' | xxd -r > $(INPUT_DIR)/$(notdir $(CRASH_INPUT)).length-ccf00000
	
	xxd $(INPUT_DIR)/OpenSans.woff | sed -e 's/00000000: 774f 4646 0001 0000 .... ..../00000000: 774f 4632 0001 0000 0000 F0CC/' | xxd -r > $(INPUT_DIR)/OpenSans.woff.length-ccf00000
	xxd $(INPUT_DIR)/OpenSans.woff.length-ccf00000 | sed -e 's/00000010: 0000 69d0 .... ..../00000010: 0000 69d0 00 00 F0 69/' | xxd -r > $(INPUT_DIR)/OpenSans.woff.length-ccf00000.totalCompressedSize-69f00000

reproduce: $(TARGET)
	./$(TARGET) $(CRASH_INPUT)