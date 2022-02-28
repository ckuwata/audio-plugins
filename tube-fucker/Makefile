.DEFAULT_GOAL := all
LINUX_BUNDLE = linux/tube-fucker.lv2
WINDOWS_BUNDLE = windows/tube-fucker.lv2


$(LINUX_BUNDLE): manifest-linux.ttl tube-fucker.ttl tube-fucker.so
	rm -rf $(LINUX_BUNDLE)
	mkdir -p $(LINUX_BUNDLE)
	cp tube-fucker.ttl  tube-fucker.so $(LINUX_BUNDLE)
	cp manifest-linux.ttl  $(LINUX_BUNDLE)/manifest.ttl

$(WINDOWS_BUNDLE): manifest-win.ttl tube-fucker.ttl tube-fucker.so
	rm -rf $(WINDOWS_BUNDLE)
	mkdir -p $(WINDOWS_BUNDLE)
	cp tube-fucker.ttl  tube-fucker.dll $(WINDOWS_BUNDLE)
	cp manifest-win.ttl  $(WINDOWS_BUNDLE)/manifest.ttl

tube-fucker.so: tube-fucker.c
	gcc -shared -fPIC -DPIC tube-fucker.c -DLV2_VERSION="1.18.2" -DHAVE_LV2=1 -I/opt/include  -o tube-fucker.so

tube-fucker.dll: tube-fucker.c
	x86_64-w64-mingw32.static-gcc  -DLV2_VERSION="1.18.2" -DHAVE_LV2=1 -I/opt/include  -std=c99 -o tube-fucker.dll  -shared  tube-fucker.c

all: $(LINUX_BUNDLE) $(WINDOWS_BUNDLE)

clean:
	rm -rf $(LINUX_BUNDLE) $(WINDOWS_BUNDLE) tube-fucker.so