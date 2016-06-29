all-local:
	@if [ ! -f ./parson-$(PARSON_VERSION)/lib/libparson.a ]; then \
		tar -zxf ./parson-$(PARSON_VERSION).tar.gz && \
			cd ./parson-$(PARSON_VERSION)/src && \
			gcc -c parson.c  -I../include && \
			ar -cvq libparson.a parson.o && \
			cd .. && \
			mkdir -p lib && \
			mv src/libparson.a lib/libparson.a; \
	fi;

clean-local:
	rm -f ./parson-$(PARSON_VERSION)/src/parson.o

uninstall-local:
	rm -rf ./parson-$(PARSON_VERSION)
