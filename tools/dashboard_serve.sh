#!/usr/bin/env bash
# Regenerate the dashboard every 60 s and serve it on :8002 (upstream's dashboard is :8000).
cd "$(dirname "${BASH_SOURCE[0]}")/.."
mkdir -p dashboard
( while true; do python3 tools/dashboard.py >/dev/null 2>&1; sleep 60; done ) &
exec python3 -m http.server 8002 --bind 0.0.0.0 --directory dashboard
