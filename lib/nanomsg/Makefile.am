all-local:
	@if [ ! -f ./nanomsg-$(NANOMSG_VERSION)/lib/libnanomsg.a ]; then \
		echo "installing nanomsg static library ..." \
		tar xf ./nanomsg-$(NANOMSG_VERSION).tar.gz && \
			cd ./nanomsg-$(NANOMSG_VERSION) && \
			./configure --prefix=`pwd` && \
			make && \
			make install; \
	fi;


clean-local:
	cd ./nanomsg-$(NANOMSG_VERSION) && \
		make clean

uninstall-local:
	cd ./nanomsg-$(NANOMSG_VERSION) && \
		make uninstall
