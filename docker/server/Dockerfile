# Stage 1: build with Qt dev packages
FROM debian:12-slim AS build

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential g++ qtbase5-dev qtbase5-dev-tools qt5-qmake pkg-config ca-certificates \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . /src

# If there is a .pro use qmake; otherwise try to compile all .cpp with Qt pkg-config flags
RUN if ls *.pro 1>/dev/null 2>&1 || ls server*.pro 1>/dev/null 2>&1; then \
      qmake || true; \
      make -j$(nproc) || true; \
    else \
      CPP_FILES="$(find . -name '*.cpp' | tr '\n' ' ')"; \
      if [ -n "$CPP_FILES" ]; then \
        g++ -std=c++11 -O2 -pthread -o /srv_server $CPP_FILES `pkg-config --cflags --libs Qt5Core Qt5Network Qt5Gui Qt5Widgets 2>/dev/null` || true; \
      fi; \
    fi

# Try to find common output names and copy to /srv_server
RUN if [ -f ./srv_server ]; then cp ./srv_server /srv_server; fi || true
RUN if [ -f ./server ]; then cp ./server /srv_server; fi || true
RUN if [ -f ./bin/server ]; then cp ./bin/server /srv_server; fi || true

# Stage 2: minimal runtime with required Qt libraries
FROM debian:12-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    libqt5core5a libqt5gui5 libqt5widgets5 libqt5network5 \
    libxcb1 libx11-6 libfontconfig1 libglib2.0-0 libxcb-xinerama0 libxcb-xkb1 ca-certificates \
  && rm -rf /var/lib/apt/lists/*

COPY --from=build /srv_server /usr/local/bin/server

EXPOSE 12345
ENTRYPOINT ["/usr/local/bin/server"]
