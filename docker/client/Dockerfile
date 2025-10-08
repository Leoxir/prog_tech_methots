# Stage 1: build with Qt dev
FROM debian:12-slim AS build

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential g++ qtbase5-dev qtbase5-dev-tools qt5-qmake pkg-config ca-certificates \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . /src

# Use qmake if .pro exists, otherwise try to compile all .cpp with Qt pkg-config
RUN if [ -f client.pro ]; then \
      qmake client.pro || true; \
      make -j$(nproc) || true; \
    else \
      CPP_FILES="$(find . -name '*.cpp' | tr '\n' ' ')"; \
      if [ -n "$CPP_FILES" ]; then \
        g++ -std=c++11 -O2 -pthread -o /client_app $CPP_FILES `pkg-config --cflags --libs Qt5Core Qt5Gui Qt5Widgets Qt5Network 2>/dev/null` || true; \
      fi; \
    fi

# Try common binary names
RUN if [ -f ./client_app ]; then cp ./client_app /client_app; fi || true
RUN if [ -f ./client ]; then cp ./client /client_app; fi || true

# Stage 2: minimal runtime
FROM debian:12-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    libqt5core5a libqt5gui5 libqt5widgets5 libqt5network5 \
    libxcb1 libx11-6 libfontconfig1 libglib2.0-0 libxcb-xinerama0 libxcb-xkb1 ca-certificates \
  && rm -rf /var/lib/apt/lists/*

ENV QT_QPA_PLATFORM=xcb
WORKDIR /app
COPY --from=build /client_app /app/client_app

ENTRYPOINT ["/app/client_app"]
