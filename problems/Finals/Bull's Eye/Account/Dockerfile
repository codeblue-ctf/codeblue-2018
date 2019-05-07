FROM ubuntu:18.04
MAINTAINER ShiftCrops <simiyu@shift-crops.net>

RUN apt update && apt upgrade -y && apt install -y curl

COPY send_flag /
COPY account /usr/bin

USER 1000

EXPOSE 4296
ENTRYPOINT account
