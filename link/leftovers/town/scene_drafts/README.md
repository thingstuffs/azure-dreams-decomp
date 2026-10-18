# Writing-room scene drafts

The 25 eight-byte descriptors at TOWN offset `0x564A0` select writing-room drafts,
not the shipped modules' dialogue banks. The supplied static investigation finds
only `S_flgtst` reaches this table and no shipped US or JP module calls it. Runtime
CD-read confirmation is still open. The draft images' linked address `0x80700000`
does not establish that retail loads them there.

For each record the generator reads the descriptor, derives the file offset from
the user's ISO9660 TOWN extent, and uses the matched loader's count rule:
`sector_count = first_word >> 23`, `length = sector_count * 2048`. The masked load
address must be `0x16000`. References: `src/slus/w_8003E758.c` case 6,
`src/town/func_800C374C.c`, and the supplied report Q3. Descriptor locations,
byte lengths and SHA-256 values are in `placements.json`; no descriptor bytes,
script bytes or dialogue are included. Records 7 and 8 overlap by a sector; the
physical denominator uses their union.

Decision 52 admits zero-base alternate scene builds as static build evidence,
with runtime placement unproven. For A (`0x834800`), B (`0x83A800`) and C
(`0x844000`), only a prefix ending at the last existing MATCH row inside a bounded
known unit is mapped. This is not a claim of complete historical image extents.
The report identifies 24 twins, but its per-twin extent/relocation table is absent
from B13. No relocation-normalized equality or shared TU is asserted from prose.
LL4 owns any existing hand-copy consolidation; these sources are untouched.

The 25 descriptors bound 163,840 union bytes. Generated receipts give the union
for all evidenced prefixes as well. Do not include modules 3/4 or module 50's
adjacent message banks: the supplied report leaves their retail loading open.
