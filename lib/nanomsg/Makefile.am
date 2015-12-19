all-local:
	tar xf ./nanomsg-$(NANOMSG_VERSION).tar.gz && \
		cd ./nanomsg-$(NANOMSG_VERSION) && \
		./configure --prefix=`pwd` && \
		make && \
		make install

clean-local:
	cd ./nanomsg-$(NANOMSG_VERSION) && \
		make clean

uninstall-local:
	cd ./nanomsg-$(NANOMSG_VERSION) && \
		make uninstall
