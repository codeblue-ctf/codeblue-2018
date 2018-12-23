FROM ubuntu:16.04
#Still for building
#TODO remove gdbserver, socat and launch only once. And set flag.
RUN apt-get update && apt-get -y upgrade
RUN apt-get install -y gdbserver socat gcc g++
#TODO create user and put oss to home dir.
EXPOSE 4444
RUN useradd -m pwn
USER pwn
WORKDIR /home/pwn
COPY ./oss.cpp /home/pwn/oss.cpp
RUN g++ oss.cpp -o oss -std=c++11
#COPY ./oss /home/pwn/oss
CMD /usr/bin/socat TCP-LISTEN:4444,reuseaddr,fork EXEC:/home/pwn/oss
#docker run -p 4444:4444 oss-ubuntu14 
