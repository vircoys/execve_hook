all:
	gcc preload_execve.c -fPIC -shared -o preload_execve.so
	sudo cp preload_execve.so /tmp/preload_execve.so
	sudo touch /etc/ld.so.preload
	sudo sh -c "echo /tmp/preload_execve.so > /etc/ld.so.preload"

clean:
	rm -f preload_execve.so
	sudo rm -f /etc/ld.so.preload
	sudo rm -f /tmp/preload_execve.so

test:
	sh test.sh
