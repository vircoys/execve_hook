# 开始

- 构建动态库，以及将路径写入 `/etc/ld.so.preload` 以影响整个系统

```sh
make
```

- 测试

```sh
make test
```

- 清理

```sh
make clean
```

- 示例

```sh
vircoys@u22 ~/preload % make 
gcc preload_execve.c -fPIC -shared -o preload_execve.so
sudo cp preload_execve.so /tmp/preload_execve.so
sudo touch /etc/ld.so.preload
sudo sh -c "echo /tmp/preload_execve.so > /etc/ld.so.preload"
vircoys@u22 ~/preload % ldd /bin/bash
        linux-vdso.so.1 (0x00007ffe3832c000)
        /tmp/preload_execve.so (0x00007f5895532000)
        libtinfo.so.6 => /lib/x86_64-linux-gnu/libtinfo.so.6 (0x00007f58954e2000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f5895200000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f589569a000)
vircoys@u22 ~/preload % make test
sh test.sh
====== start hook test
!!! execve hooked: /usr/bin/python3 xxxxx_test.py
test.sh: 2: /usr/bin/python3: Success
end test
vircoys@u22 ~/preload % make clean
rm -f preload_execve.so
sudo rm -f /etc/ld.so.preload
sudo rm -f /tmp/preload_execve.so
```
