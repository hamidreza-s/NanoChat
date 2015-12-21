all-local:
	@if [ ! -f ./vedis-$(VEDIS_VERSION)/lib/libvedis.a ]; then \
		tar -zxf ./vedis-$(VEDIS_VERSION).tar.gz && \
			cd ./vedis-$(VEDIS_VERSION)/src && \
			gcc -c vedis.c && \
			ar -cvq libvedis.a vedis.o && \
			cd .. && \
			mkdir -p lib && \
			mv src/libvedis.a lib/libvedis.a; \
	fi;

clean-local:
	rm -f ./vedis-$(VEDIS_VERSION)/src/vedis.o

uninstall-local:
	rm -rf ./vedis-$(VEDIS_VERSION)
