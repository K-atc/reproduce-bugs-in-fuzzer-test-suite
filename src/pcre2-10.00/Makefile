TARGET := reproducer
TARGET_NOASAN := $(TARGET).noasan
PROJECT_ROOT_DIR_REL := ../..
PROJECT_ROOT_DIR := $$(realpath $(PROJECT_ROOT_DIR_REL))
CRASH_INPUT := $(PROJECT_ROOT_DIR_REL)/input/pcre2-10.00/crash-235641cefe524570bf0df6a3b3722535ce2dbbf7 
INPUT_DIR := $(PROJECT_ROOT_DIR_REL)/input/pcre2-10.00

EXTLIB_DIR_NAME := pcre2
EXTLIB_LIB := $(EXTLIB_DIR_NAME)/.libs/*.a
FUZZER_TEST_SUITE_TARGET_CC := $(PROJECT_ROOT_DIR)/fuzzer-test-suite/pcre2-10.00/target.cc

CXX := clang++
CFLAGS := -g
CXXFLAGS := $(CFLAGS)
CFLAGS_ASAN := $(CFLAGS) -fsanitize=address
CFLAGS_NOASAN := $(CFLAGS)

all: $(TARGET) $(TARGET_NOASAN)
	@

clean:
	rm -f $(TARGET) $(TARGET_NOASAN) $(EXTLIB_LIB)

$(EXTLIB_LIB): $(EXTLIB_DIR_NAME)
	cd $(EXTLIB_DIR_NAME) && ./autogen.sh
	cd $(EXTLIB_DIR_NAME) && CCLD="$(CXX) $(CXXFLAGS)" ./configure \
		--disable-shared --enable-never-backslash-C \
		--with-match-limit=1000 --with-match-limit-recursion=1000 
	cd $(EXTLIB_DIR_NAME) && make -j

$(EXTLIB_DIR_NAME):
	svn co -r183 svn://vcs.exim.org/pcre2/code/trunk $@

define build_main
	$(CXX) $(1) \
		$(EXTLIB_LIB) $(FUZZER_TEST_SUITE_TARGET_CC) $^ \
		-I $(EXTLIB_DIR_NAME)/src \
		-Wl,--whole-archive \
		-Wl,-no-whole-archive \
		-o $@
endef

$(TARGET): ../main.cpp $(EXTLIB_LIB)
	$(call build_main,$(CFLAGS_ASAN))
	nm $@ | grep asan > /dev/null

$(TARGET_NOASAN): ../main.cpp $(EXTLIB_LIB)
	$(call build_main,$(CFLAGS_NOASAN))
	nm $@ | grep $(EXTLIB_DIR_NAME) > /dev/null

$(INPUT_DIR):
	mkdir -p $@

input: $(INPUT_DIR)
	@

check-input: input
	find $(INPUT_DIR)/* | xargs -n1 ./$(TARGET)

reproduce:
	ASAN_OPTIONS=strip_path_prefix=$(PROJECT_ROOT_DIR)/ ./$(TARGET) $(CRASH_INPUT)