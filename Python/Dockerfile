FROM python:3.11-slim

WORKDIR /app

# Copy the Python source files
COPY 01_invoice_srp_ocp.py .
COPY 02_media_lsp_isp.py .
COPY 03_notify_dip_ocp.py .

# Default command to run all programs
CMD echo "Running Program 1 (03_notify_dip_ocp):" && \
    python 03_notify_dip_ocp.py && \
    echo "\nRunning Program 2 (02_media_lsp_isp):" && \
    python 02_media_lsp_isp.py && \
    echo "\nRunning Program 3 (01_invoice_srp_ocp):" && \
    python 01_invoice_srp_ocp.py