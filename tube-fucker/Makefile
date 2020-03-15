BUNDLE = tube-fucker.lv2
INSTALL_DIR = /usr/local/lib/lv2


$(BUNDLE): manifest.ttl tube-fucker.ttl tube-fucker.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp manifest.ttl tube-fucker.ttl  tube-fucker.so $(BUNDLE)

tube-fucker.so: tube-fucker.c
	gcc -shared -fPIC -DPIC tube-fucker.c `pkg-config --cflags --libs lv2-plugin` -o tube-fucker.so

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)

clean:
	rm -rf $(BUNDLE) tube-fucker.so