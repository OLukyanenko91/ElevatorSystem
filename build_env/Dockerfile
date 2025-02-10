FROM nvcr.io/nvidia/l4t-base:r32.5.0

WORKDIR /

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/fmtlib/fmt.git /tmp/fmt && \
    mkdir /tmp/fmt/build && \
    cd /tmp/fmt/build && \
    cmake .. && \
    make -j$(nproc) && \
    make install

RUN rm -rf /tmp/fmt

CMD ["bash"]

