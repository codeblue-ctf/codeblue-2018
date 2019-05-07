FROM ubuntu:18.04
RUN apt-get update && apt-get -y upgrade
RUN apt-get install -y default-jre socat
RUN useradd -m pwn
COPY ./CbJava.class /home/pwn/
COPY ./libCbNative.so /home/pwn/
WORKDIR /home/pwn/
USER pwn
#CMD LD_LIBRARY_PATH=. java CbJava
CMD LD_LIBRARY_PATH=. socat TCP-LISTEN:4444,reuseaddr,fork EXEC:'java CbJava'
