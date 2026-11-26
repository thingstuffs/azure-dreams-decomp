# Explicit stale image intervals

`intervals.json` records 22 disjoint ranges totaling 26,196 bytes. The
DUNGEON ranges include ten exact TOWN copies (20,108 bytes), four formatter
interiors (3,584 bytes) and three formatter build identifiers (216 bytes).
TOWN has a 372-byte fragment from MAIN. Four more TOWN ranges totaling 1,916
bytes are listed as indexed entries only: they are compiled C data of the
scene images they sit in (owner unresolved) and carry no class in the coverage
ledger. The entries carry physical offsets, lengths and SHA-256 values.

The coverage ledger checks the exact comparison ranges and the formatter hashes. The physical roots already include all these bytes. The interval
index counts them once and leaves runtime loading to the bank evidence.
