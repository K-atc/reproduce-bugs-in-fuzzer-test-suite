TARGET := libxml2-v2.9.2

CFLAGS := -g -O2 
CFLAGS_ASAN := -fno-omit-frame-pointer -fsanitize=address -fsanitize-address-use-after-scope

all: libxml2-v2.9.2/main.o
	./

src/libxml2-v2.9.2/libxml:
	git checkout v2.9.2

libxml2-v2.9.2/main.o: libxml2-v2.9.2/main.cpp
	$(CC) $(CFLAGS) -c $^ -o $@