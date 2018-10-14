

start:
	rsync --daemon --config=./rsync.conf
	
stop:
	kill $(shell cat ./rsyncd.pid)

sync:
	sudo rsync -avzP --delete root@192.168.1.101::
	sudo rsync -avzP --delete root@192.168.1.101::sync ./
	#在html目录下执行
