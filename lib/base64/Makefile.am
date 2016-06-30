all-local:
	@if [ ! -f ./base64-$(BASE64_VERSION)/lib/libbase64.a ]; then \
		tar -zxf ./base64-$(BASE64_VERSION).tar.gz && \
			cd ./base64-$(BASE64_VERSION)/src && \
			gcc -c base64.c  -I../include && \
			ar -cvq libbase64.a base64.o && \
			cd .. && \
			mkdir -p lib && \
			mv src/libbase64.a lib/libbase64.a; \
	fi;

clean-local:
	rm -f ./base64-$(BASE64_VERSION)/src/base64.o

uninstall-local:
	rm -rf ./base64-$(BASE64_VERSION)
