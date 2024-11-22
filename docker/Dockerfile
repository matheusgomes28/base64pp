# Version: 0.13

# Base ubuntu 18.04
FROM ubuntu:bionic-20230530

# Environment variables needed for the
# build system
ENV CONAN_USER_HOME="/conan"
ENV TZ=Europe/London
ENV DEBIAN_FRONTEND="noninteractive"

# Identify the maintainer of an image
LABEL maintainer="matheusgarcia28@gmail.com"

# Install system tools
RUN apt-get update \
    && apt-get install -y --no-install-recommends --no-install-suggests software-properties-common\
    && add-apt-repository ppa:ubuntu-toolchain-r/test \
    && apt-get install -y --no-install-recommends --no-install-suggests \
        curl \
        git \
        gcc-11 \
        g++-11 \
        make \
        pkg-config \
        python3 \
        python3-pip \
        python3-setuptools \
        graphviz \
        flex \
        bison \
        shellcheck \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 10 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 10 \
    && update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-11 10 \
    && apt-get remove -y software-properties-common bison flex \
    && apt-get clean \
    && apt-get autoremove -y \
    && apt-get autoremove --purge -y \
    && rm -rf /var/lib/apt/lists/* \
    && rm -rf /usr/lib/gcc/x86_64-linux-gnu/7*

# Install the LLVM 17 tools
RUN apt-get update \
    && apt-get install -y --no-install-recommends --no-install-suggests software-properties-common\
    && add-apt-repository ppa:ubuntu-toolchain-r/test \
    && add-apt-repository ppa:savoury1/llvm-defaults-17 \
    && apt-get install -y --no-install-recommends --no-install-suggests \
        clang-format-17 \
        clang-tidy-17 \
        clang-tools-17 \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-17 10 \
    && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-17 10 \
    && update-alternatives --install /usr/bin/clang-scan-deps clang-scan-deps /usr/bin/clang-scan-deps-17 10 \
    && update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-17 10 \
    && update-alternatives --install /usr/bin/run-clang-tidy run-clang-tidy /usr/bin/run-clang-tidy-17 10 \
    && apt-get remove -y software-properties-common \
    && apt-get clean \
    && apt-get autoremove -y \
    && apt-get autoremove --purge -y \
    && rm -rf /var/lib/apt/lists/*

# Upgrade pip
RUN pip3 install --upgrade --no-cache --ignore-installed pip

# Install Conan dependencies
RUN pip3 install --no-cache --ignore-installed cmake==3.28 \
    && pip3 install --no-cache -q --ignore-installed ninja==1.11.1 \
    && update-alternatives --install /usr/bin/ninja ninja /usr/local/bin/ninja 10 \
    && mkdir "/conan" \
    && pip3 install --no-cache -q --ignore-installed conan==2.0.17 \
    && chmod -R 777 "/conan"

# Build LCov
RUN apt-get update \
    && apt-get install -y --no-install-recommends --no-install-suggests \
        wget \
    && cd ~ \
    && wget https://github.com/linux-test-project/lcov/releases/download/v1.15/lcov-1.15.tar.gz \
    && tar xzf lcov-1.15.tar.gz \
    && cd lcov-1.15 && make install \
    && cd ~ && rm -rf lcov-1.15 && rm lcov-1.15.tar.gz \
    && apt-get remove -y wget \
    && apt-get clean \
    && apt-get autoremove -y \
    && apt-get autoremove --purge -y \
    && rm -rf /var/lib/apt/lists/*

# Build Doxygen
RUN apt-get update \
    && apt-get install -y --no-install-recommends --no-install-suggests \
        bison \
        wget \
        flex \
    && cd ~ \
    && wget https://doxygen.nl/files/doxygen-1.9.6.src.tar.gz \
    && tar xzf doxygen-1.9.6.src.tar.gz \
    && cd doxygen-1.9.6 \
    && mkdir build && cd build \
    && cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr .. \
    && cmake --build . \
    && cmake --install . \
    && cd ~ && rm doxygen-1.9.6.src.tar.gz && rm -rf doxygen-1.9.6 \
    && apt-get remove -y \
        bison \
        flex \
        wget \
    && apt-get clean \
    && apt-get autoremove -y \
    && apt-get autoremove --purge -y \
    && rm -rf /var/lib/apt/lists/*

# # install build dependencies 
# RUN apt-get update \
#     && apt-get install -y --no-install-recommends --no-install-suggests software-properties-common\
#     && add-apt-repository ppa:ubuntu-toolchain-r/test \
#     && add-apt-repository ppa:savoury1/llvm-defaults-17 \
#     && apt-get install -y --no-install-recommends --no-install-suggests \
#     curl \
#     git \
#     gcc-11 \
#     g++-11 \
#     make \
#     pkg-config \
#     python3 \
#     python3-pip \
#     python3-setuptools \
#     graphviz \
#     wget \
#     flex \
#     bison \
#     shellcheck \
#     clang-format-17 \
#     clang-tidy-17 \
#     clang-tools-17 \
#     && mkdir "/conan" \
#     && pip3 install --upgrade --no-cache --ignore-installed pip \
#     && pip3 install --no-cache -q --ignore-installed conan==2.0.17 \
#     && chmod -R 777 "/conan" \
#     && pip3 install --no-cache -q --ignore-installed ninja==1.11.1 \
#     && pip3 install --no-cache --ignore-installed cmake==3.28 \
#     && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 10 \
#     && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 10 \
#     && update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-11 10 \
#     && update-alternatives --install /usr/bin/ninja ninja /usr/local/bin/ninja 10 \
#     && wget https://doxygen.nl/files/doxygen-1.9.6.src.tar.gz \
#     && tar xzf doxygen-1.9.6.src.tar.gz \
#     && cd doxygen-1.9.6 \
#     && mkdir build && cd build \
#     && cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr .. \
#     && cmake --build . \
#     && cmake --install . \
#     && cd ~ && rm doxygen-1.9.6.src.tar.gz && rm -rf doxygen-1.9.6 \
#     && apt-get remove -y software-properties-common wget bison flex \
#     && apt-get clean \
#     && apt-get autoremove -y \
#     && apt-get autoremove --purge -y \
#     && rm -rf /var/lib/apt/lists/* \
#     && rm -rf /usr/lib/gcc/x86_64-linux-gnu/7*