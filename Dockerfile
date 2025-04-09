FROM ubuntu:22.04 as builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y \
    software-properties-common && \
    add-apt-repository ppa:ubuntu-toolchain-r/test && \
    apt-get update && \
    apt-get install -y \
    gcc-13 \
    g++-13 \
    cmake \
    git \
    curl \
    unzip \
    tar \
    zip \
    pkg-config \
    build-essential \
    python3 \
    ca-certificates \
    libssl-dev \
    ninja-build \
    libx11-dev

COPY . /app
WORKDIR /app

RUN mkdir -p build

WORKDIR /app/build

RUN --mount=type=cache,target=/app/build \
    CC=gcc-13 CXX=g++-13 cmake .. -DCMAKE_BUILD_TYPE=Release -G Ninja

RUN --mount=type=cache,target=/app/build \
    CC=gcc-13 CXX=g++-13 CMAKE_BUILD_TYPE=Release cmake --build . --target NeuroSurvival && \
    cp -r bin /output

FROM ubuntu:22.04 AS runtime

COPY --from=builder /output /app
ENTRYPOINT ["/app/NeuroSurvival"]


