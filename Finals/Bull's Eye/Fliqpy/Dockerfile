FROM ubuntu:16.04

RUN apt-get update && apt-get -y upgrade
RUN apt install -y socat curl
#RUN apt install -y gdb
RUN groupadd -r user && useradd -r -g user user

COPY ./send_flag /send_flag

WORKDIR /home/user/
USER user
COPY --chown=root:user . .

EXPOSE 12345
CMD ["socat", "TCP-LISTEN:12345,reuseaddr", "EXEC:/home/user/start.sh"]
#CMD ["gdb", "-q", "/home/user/easy_example"]
