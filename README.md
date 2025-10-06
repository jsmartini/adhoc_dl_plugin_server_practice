# Plugin Server Practice

This is a basic server hypervisor that can load servers from
.so dynamic libraries built with makefiles. 

I wanted to practice .so development and plugin patterns.

To run the echo server:

1. Build the echo server

   ```console  cd echo_server && make all && cd .. ```

2. Build the core server:
    
   ```console make all ```

3. Run the echo server from the core server:

  ```console  ./server echo_server/lib/echo_server.so```

4. Connect via telnet

   ```console  telnet localhost 7777 ```