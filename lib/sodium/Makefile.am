all-local:
	@if [ ! -f ./libsodium-$(SODIUM_VERSION)/lib/libsodium.a ]; then \
		tar -zxf ./libsodium-$(SODIUM_VERSION).tar.gz && \
			cd ./libsodium-$(SODIUM_VERSION) && \
			./configure --prefix=`pwd` && \
			make && \
			make install; \
	fi;

clean-local:
	cd ./libsodium-$(SODIUM_VERSION) && \
		make clean

uninstall-local:
	cd ./libsodium-$(SODIUM_VERSION) && \
		make uninstall
