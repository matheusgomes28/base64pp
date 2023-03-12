#
# We base our image from the alpine light image
FROM ubuntu:bionic-20230301

#
# Environment variables needed for the
# build system
ENV CONAN_USER_HOME="/conan"
ENV TZ=Europe/London
ENV DEBIAN_FRONTEND="noninteractive"

#
# Identify the maintainer of an image
LABEL maintainer="matheusgarcia28@gmail.com"

# install build dependencies 
RUN apt-get update \
    && apt-get install -y --no-install-recommends --no-install-suggests software-properties-common\
    && add-apt-repository ppa:ubuntu-toolchain-r/test \
    && apt-get install -y --no-install-recommends --no-install-suggests \
    gcc-11 \
    g++-11 \
    make \
    pkg-config \
    python3 \
    python3-pip \
    python3-setuptools \
    graphviz \
    wget \
    flex \
    bison \
    && mkdir "/conan" \
    && pip3 install --upgrade --no-cache pip \
    && pip3 install --no-cache -q conan>=2 \
    && chmod -R 777 "/conan" \
    && pip3 install --no-cache cmake==3.25.2 \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 10 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 10 \
    && cd ~ \
    && wget https://doxygen.nl/files/doxygen-1.9.6.src.tar.gz \
    && tar xzf doxygen-1.9.6.src.tar.gz \
    && cd doxygen-1.9.6 \
    && mkdir build && cd build \
    && cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr .. \
    && cmake --build . \
    && cmake --install . \
    && cd ~ && rm -rf doxygen-1.9.6 \
    && apt-get remove -y software-properties-common wget bison flex \
    && apt-get clean \
    && apt-get autoremove -y \
    && apt-get autoremove --purge -y \
    && rm -rf /var/lib/apt/lists/*
