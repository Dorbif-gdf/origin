FROM ubuntu:16.04

RUN apt-get update && \
    apt-get install -y g++

WORKDIR /app

COPY Task_1.cpp .

RUN g++ Task_1.cpp -o task1

CMD ["./hello"]