# Local C++ commands
run1:
	g++ -std=c++17 -o 01-invoice-src-ocp 01-invoice-src-ocp.cpp && ./01-invoice-src-ocp

run2:
	g++ -std=c++17 -o 02-media-lsp-isp 02-media-lsp-isp.cpp && ./02-media-lsp-isp

run3:
	g++ -std=c++17 -o 03-notify-dip-ocp 03-notify-dip-ocp.cpp && ./03-notify-dip-ocp

# Docker commands
build:
	docker build -t cpp-assignments .

run-docker1:
	docker rm Week1-Assignment-CPP || true
	docker run --name Week1-Assignment-CPP cpp-assignments ./01-invoice-src-ocp

run-docker2:
	docker rm Week1-Assignment-CPP || true
	docker run --name Week1-Assignment-CPP cpp-assignments ./02-media-lsp-isp

run-docker3:
	docker rm Week1-Assignment-CPP || true
	docker run --name Week1-Assignment-CPP cpp-assignments ./03-notify-dip-ocp

run-all:
	docker rm Week1-Assignment-CPP || true
	docker run --name Week1-Assignment-CPP cpp-assignments