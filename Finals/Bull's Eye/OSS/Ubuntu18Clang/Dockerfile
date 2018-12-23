FROM ubuntu:18.04
#Still for building
#TODO remove gdbserver, socat and launch only once. And set flag.
RUN apt-get update && apt-get -y upgrade
RUN apt-get install -y gdbserver socat gcc g++ clang
#TODO create user and put oss to home dir.
EXPOSE 4444
RUN useradd -m pwn
USER pwn
WORKDIR /home/pwn
COPY ./oss.cpp /home/pwn/oss.cpp
RUN clang++ oss.cpp -o oss
#COPY ./oss /home/pwn/oss
CMD /usr/bin/socat TCP-LISTEN:4444,reuseaddr,fork EXEC:/home/pwn/oss
#docker run -p 4444:4444 oss-ubuntu18-clang
