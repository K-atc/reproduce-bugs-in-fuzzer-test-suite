TARGET := c-ares-CVE-2016-5180 libxml2-v2.9.2 openssl-1.0.1f woff2-2016-05-06 re2-2014-12-09

.PHONY: all

all: $(TARGET)
	@

$(TARGET): 
	make --directory=src/$@