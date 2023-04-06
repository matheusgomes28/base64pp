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
    && add-apt-repository ppa:savoury1/llvm-defaults-13 \
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
    shellcheck \
    clang-format-13 \
    clang-tidy-13 \
    && mkdir "/conan" \
    && pip3 install --upgrade --no-cache --ignore-installed pip \
    && pip3 install --no-cache -q --ignore-installed conan>=2 \
    && chmod -R 777 "/conan" \
    && pip3 install --no-cache --ignore-installed cmake==3.25.2 \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 10 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 10 \
    && update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-11 10 \
    && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-13 10 \
    && update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-13 10 \
    && update-alternatives --install /usr/bin/run-clang-tidy run-clang-tidy /usr/bin/run-clang-tidy-13 10 \
    && cd ~ \
    && wget https://github.com/linux-test-project/lcov/releases/download/v1.15/lcov-1.15.tar.gz \
    && tar xzf lcov-1.15.tar.gz \
    && cd lcov-1.15 && make install \
    && cd ~ && rm -rf lcov-1.15 && rm lcov-1.15.tar.gz \
    && wget https://doxygen.nl/files/doxygen-1.9.6.src.tar.gz \
    && tar xzf doxygen-1.9.6.src.tar.gz \
    && cd doxygen-1.9.6 \
    && mkdir build && cd build \
    && cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr .. \
    && cmake --build . \
    && cmake --install . \
    && cd ~ && rm doxygen-1.9.6.src.tar.gz && rm -rf doxygen-1.9.6 \
    && apt-get remove -y software-properties-common wget bison flex \
    && apt-get clean \
    && apt-get autoremove -y \
    && apt-get autoremove --purge -y \
    && rm -rf /var/lib/apt/lists/*
