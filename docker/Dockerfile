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
    && apt-get install -y software-properties-common\
    && add-apt-repository ppa:ubuntu-toolchain-r/test \
    && apt-get install -y \
    gcc-11 \
    g++-11 \
    make \
    pkg-config \
    python3 \
    python3-pip \
    && mkdir "/conan" \
    && pip3 install --upgrade --no-cache pip \
    && pip3 install --no-cache -q conan==2.0.1 \
    && chmod -R 777 "/conan" \
    && pip3 install --no-cache cmake==3.25.2 \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 10 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 10 \
    && apt-get remove -y software-properties-common \
    && apt-get clean \
    && apt-get autoremove -y \
    && apt-get autoremove --purge -y
