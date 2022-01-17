FROM ubuntu
MAINTAINER codeinquisitor
RUN apt update
RUN apt install -y build-essential
RUN apt install -y wget
RUN mkdir sqlite-install
RUN cd sqlite-install && wget https://www.sqlite.org/2022/sqlite-autoconf-3370200.tar.gz
RUN cd sqlite-install && tar xvfz sqlite-autoconf-3370200.tar.gz
RUN cd sqlite-install/sqlite-autoconf-3370200 && ./configure --prefix=/usr/local
RUN cd sqlite-install/sqlite-autoconf-3370200 && make
RUN cd sqlite-install/sqlite-autoconf-3370200 && make install
