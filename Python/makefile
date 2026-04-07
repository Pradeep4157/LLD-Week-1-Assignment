# Makefile for Python SOLID principles examples

.PHONY: run-all run-1 run-2 run-3 build-docker run-docker clean

# Run all Python programs
run-all:
	@echo "Running all Python programs..."
	@echo "Program 1 (03_notify_dip_ocp):"
	@python3 03_notify_dip_ocp.py
	@echo "\nProgram 2 (02_media_lsp_isp):"
	@python3 02_media_lsp_isp.py
	@echo "\nProgram 3 (01_invoice_srp_ocp):"
	@python3 01_invoice_srp_ocp.py

# Run individual programs
run-1:
	@echo "Running 03_notify_dip_ocp.py:"
	@python3 03_notify_dip_ocp.py

run-2:
	@echo "Running 02_media_lsp_isp.py:"
	@python3 02_media_lsp_isp.py

run-3:
	@echo "Running 01_invoice_srp_ocp.py:"
	@python3 01_invoice_srp_ocp.py

# Docker targets
build-docker:
	docker build -t python-lld-assignment .

run-docker: build-docker
	docker run --rm python-lld-assignment

# Clean up (if needed for any temporary files)
clean:
	find . -type f -name "*.pyc" -delete
	find . -type d -name "__pycache__" -delete