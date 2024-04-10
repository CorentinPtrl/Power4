FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update

RUN apt-get install -y \
    build-essential \
    cmake \
    git \
    libssl-dev \
    libuv1-dev \
    libcsfml-dev \
    libsfml-dev \
    libpq-dev

WORKDIR /app

COPY . .

RUN cmake .

RUN make

EXPOSE 8080

ENTRYPOINT ["./PowerServer/PowerServer"]
