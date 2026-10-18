# Developer data residue

The supplied report Q2 identifies these TOWN slices. `placements.json` records
lengths, hashes and extraction boundaries without any symbol names, source text
or other retail payload.

| item | extent or bound | format status |
|---|---|---|
| symbol dump | `0x80C000..0x82B914` | two validated symbol arrays; opaque inter-table region |
| scenario paths | `0x7F877C..0x7F8894` | developer path table; detailed typing pending |
| debug type information | `0x862B00..0x863900` | Psy-Q struct/type tables; detailed typing pending |
| assembler source | starts `0x82E800`, through first NUL within 16 KiB | bounded developer text fragment |
| link line | starts `0x832838`, through first NUL within 16 KiB | bounded developer text fragment |

`link/leftovers/evidence/audit.json` reconciles the full symbol extent structurally:
678 records at `0x80C000..0x811F58`, a 168-byte opaque region at
`0x811F58..0x812000`, and 2,909 records at `0x812000..0x82B914`.
All 3,587 records have a NUL-terminated identifier in a zero-filled 32-byte name
field followed by a little-endian u32 value. No names or values are exported.
The intervening 168 bytes are not claimed as padding. `tools/leftover_audit.py`
repeats the checks and hashes every exact region from the user's container.
The two text slices claim only their first NUL-terminated fragment, not every
byte of a larger source file.

These slices overlap draft footprints. Their bytes are counted once through the
physical root; a format note does not turn them into typed game data. No general
stale-image claim is inferred from a developer string elsewhere on the disc.
