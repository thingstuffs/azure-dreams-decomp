#!/usr/bin/env python3
"""Asm preprocessor: translate splat's custom `.shiftjis "..."` directive into
raw `.byte` sequences so GNU as can assemble it. Reads stdin, writes stdout."""
import sys, re

for line in sys.stdin:
    m = re.match(r'(\s*)\.shiftjis\s+"(.*)"\s*$', line)
    if m:
        indent, text = m.group(1), m.group(2)
        data = text.encode("shift_jis")
        sys.stdout.write(indent + ".byte " + ", ".join(f"0x{b:02x}" for b in data) + "\n")
    else:
        sys.stdout.write(line)
