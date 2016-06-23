NanoChat
=====

NanoChat is a peer to peer chat application that can be used inside command line. It is totally server-less
and every NanoChat peer can discover other peers in the same subnet without having the network address of them in advance.

How to use
-----

Call `nanochat` with desired arguments. In order to see the list of available arguments, use `--help` argument as follows:

```
NanoChat help
-------------
Avaliable flags:
    Help:          -h --help
    Host IP:       -H --host {host IP}
    Broadcast IP:  -B --broadcast {broadcast IP}
    RPC Port:      -P --port {port}
    Verbose:       -v --verbose
    Secure:        -s --secure
    Discoverable:  -d --discoverable
```

In order to see available command inside NanoChat use `/help` command as follows:

```shell
$ nanochat --discoverable
NanoChat shell was started.
>> /help
Available commands:
  /help                prints this text
  /ping                prints pong
  /quit                quit nanochat console
  /connect host port   connect to remote client
  /attach room         attach to room
  /probe               find available peers
  /list                list available peers
>>
```

Installation
-----

NanoChat uses [GNU Autotools](https://en.wikipedia.org/wiki/GNU_Build_System). So you need to have them installed in
your system. Also it needs [GCC](https://en.wikipedia.org/wiki/GNU_Compiler_Collection),
[GNU Make](https://www.google.co.uk/?ion=1&espv=2#q=gnu%20make) and
[GNU Readline](https://en.wikipedia.org/wiki/GNU_Readline) library.

After making sure that your system has required dependencies, clone the repo and follow installation steps:

```
$ git clone https://github.com/hamidreza-s/NanoChat.git
$ cd NanoChat
$ autoreconf -i
$ ./configure
$ make && make install
...
=============================================================
|            NanoChat was successfully installed 
-------------------------------------------------------------
| NanoChat was installed in /usr/local/bin directory. 
| Just type 'nanochat --help' there to get started.
=============================================================
```

Now `nanochat` executable file is accessible shell path.

Contribution
-----

Comments, contributions and patches are greatly appreciated.

License
-----
The MIT License (MIT).
