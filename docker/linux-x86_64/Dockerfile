FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

RUN apt-get update && apt-get install -y \
    cmake \
    ninja-build \
    g++ \
    python3-pip \
    zip \
    curl \
    git \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install --no-cache-dir "conan>=2.0,<3"

WORKDIR /workspace
CMD ["/bin/bash"]
