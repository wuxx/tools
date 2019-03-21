#!/bin/bash

sudo docker container exec -it myghost /bin/bash

sudo docker container ls -all

sudo docker run --name myghost -p 8080:2368 -d ghost

sudo docker container start myghost

sudo docker container stop  myghost
