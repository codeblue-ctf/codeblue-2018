FROM ubuntu:18.04

RUN set -x && \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y openjdk-8-jre-headless socat curl && \
    useradd -m user && \
    chown root:root -R /home/user && \
    apt-get clean && rm -rf /var/cache/apt/archives/* /var/lib/apt/lists/*

ADD App.jar /home/user/App.jar
ADD libJNITest.so /usr/lib/
ADD send_flag /

USER user
WORKDIR /home/user

EXPOSE 11111
CMD ["socat", "tcp-listen:11111,reuseaddr", "exec:'java -Xms32M -Xmx32M -jar /home/user/App.jar'"]
