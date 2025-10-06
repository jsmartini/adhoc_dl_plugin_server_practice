# Plugin Server Practice

This is a basic server hypervisor that can load servers from
.so dynamic libraries built with makefiles. 

I wanted to practice .so development and plugin patterns.
Specifically, I wanted to practice how ffmpeg structures their codebase with function tables.

To run the echo server:

1. Build the echo server

   ```> cd echo_server && make all && cd .. ```

2. Build the core server:
    
   ```> make all ```

3. Run the echo server from the core server:

  ```>  ./server echo_server/lib/echo_server.so```

4. Connect via telnet

   ```>  telnet localhost 7777 ```