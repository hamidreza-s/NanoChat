NanoChat
=====

NanoChat is a **discoverable**, **peer to peer** and **end to end encrypted** chat application
that can be used inside command line. It is totally server-less
and every peer can discover other peers in the same subnet without having the network address
of them in advance.

It can be compiled and works on both **Linux** and **OSX** system platforms.

How to use
-----

Call `nanochat` with desired flags. In order to see the list of available flags,
use `--help` as follows:

```
NanoChat help
-------------
Avaliable flags:
    Help:          -h --help
    Host IP:       -H --host {host IP}
    Broadcast IP:  -B --broadcast {broadcast IP}
    RPC Port:      -P --port {port}
    Discoverable:  -d --discoverable
    Secure:        -s --secure
```

- `--host {host IP}` flag is used to specify the network interface IP which you want to use. By default
it is selected by NanoChat.
- `--broadcast {broadcast IP}` flag is used to specify the network interface broadcast IP
which you want to use. By default it is selected by NanoChat.
- `--port` flag is used to specify the RPC port which is listening to answer chat requests after creating
the requested chat room. Its default value is `1991`.
- `--discoverable` flas is used to let NanoChat to be disovered by other peers, otherwise it doesn't
answer to discovery packet and remains hidden from others.
- `--secure` flags is used to make NanoChat secure for end to end message encryption with
asymmetric/public-key cryptography.

-----

In order to see available commands inside NanoChat use `/help` command as follows:

```shell
$ nanochat --discoverable
NanoChat shell was started.
>> /help
Available commands:
  /help                    prints this text
  /probe                   find online peers
  /list peers              list online peers
  /list rooms              list availabe rooms
  /connect {host} {port}   connect to remote client
  /attach {room}           attach to room
  /quit                    quit nanochat console
>> ...
```

- `/probe` command discovers the subnet for other online NanoChat peers.
- `/list peers` command list discovered online peers' host and port address.
- `/list rooms` command list available rooms.
- `/connect {host} {port}` command connects you to other peers.
- `/attach {room}` command is used to enter to a created room by other peers.
- `/quit` command closes the NanoChat console.

Installation
-----

NanoChat uses [GNU Autotools](https://en.wikipedia.org/wiki/GNU_Build_System). So you need to have them installed in
your system. Also it needs [GCC](https://en.wikipedia.org/wiki/GNU_Compiler_Collection)
or [Clang](https://en.wikipedia.org/wiki/Clang),
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

Now `nanochat` executable file is accessible in the path of your shell.

How it works
-----

My main purpose for writing NanoChat is learning things, so I think it is
good to know for you how it works and what tools and protocols it uses.

- For discovering other online peers in the same subnet it uses raw UDP broadcasting.
- For inter-node communication it uses some [nanomsg library](http://nanomsg.org) scalibility protocols,
for instance REQREP protocol for RPC and PAIR for one to one chat.
- For user's input/output multiplexing it uses [select](https://en.wikipedia.org/wiki/Select_(Unix))
POSIX-compliant syscall.
- For storing user's information it uses [Vedis](https://vedis.symisc.net) embedded datastore engine.
- For line-editing and history capabilities of commands it
uses [GNU Readline](https://en.wikipedia.org/wiki/GNU_Readline).

Contribution
-----

Comments, contributions and patches are greatly appreciated.

License
-----
The MIT License (MIT).
