FROM gcc:latest

RUN apt-get update \
    && apt-get install -y cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY ./CMakeLists.txt ./
COPY ./app/ ./app/
COPY ./core/ ./core/

RUN cmake -B build && cmake --build build -t clawnetd

EXPOSE 3000

CMD ["stdbuf", "-oL", "./build/bin/clawnetd", "--ip", "0.0.0.0", "--port", "3000"]
