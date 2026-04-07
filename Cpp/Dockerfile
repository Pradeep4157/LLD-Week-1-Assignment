FROM gcc:latest

WORKDIR /app

# Copy the C++ source files and makefile
COPY 01-invoice-src-ocp.cpp .
COPY 02-media-lsp-isp.cpp .
COPY 03-notify-dip-ocp.cpp .
COPY makefile .

# Build the C++ programs
RUN g++ -std=c++17 -o 01-invoice-src-ocp 01-invoice-src-ocp.cpp
RUN g++ -std=c++17 -o 02-media-lsp-isp 02-media-lsp-isp.cpp
RUN g++ -std=c++17 -o 03-notify-dip-ocp 03-notify-dip-ocp.cpp

# Default command to run all programs
CMD echo "Running Program 1:" && \
    ./01-invoice-src-ocp && \
    echo "\nRunning Program 2:" && \
    ./02-media-lsp-isp && \
    echo "\nRunning Program 3:" && \
    ./03-notify-dip-ocp