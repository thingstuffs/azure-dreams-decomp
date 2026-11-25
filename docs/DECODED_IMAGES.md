Decoded executable images
=========================

`config/decoded/*.json` registers decoded instruction coordinates separately
from physical disc offsets. `tools/decoded_images.py rows` exports their stable
`decoded/<image>/<function>` identities. The physical row database and link graph
are unchanged. Their checks validate this additional registry and source layout.
Never split a raw floor row using an address observed after decompression.

Exact recompression
-------------------

The resident decoder (`src/engine/graphics/decompress_lz.c`) uses LSB-first,
interleaved flags: 0 literal; 10 long reference or zero terminator; 11 short
reference with two count bits. `tools/decoded/lz.py` reproduces its encoder with
greedy longest matches, nearest ties, a 4095-byte history and a fresh dictionary
per stream. Short matches cover distances 1..256 and lengths 2..5; long matches
cover distances 1..4095, lengths 3..17 or an explicit count up to 256. A stream
may split an instruction word; concatenation must not add alignment.

The nearest-tie policy reproduces all four identified code streams exactly.
Selecting the oldest tie changes the compressed bytes. Each production build
checks the length and SHA-256 of the regenerated streams against retail. There is no token recipe,
embedded retail payload, masked relocation or fallback to an imported stream.

`make decoded-images` compiles complete C TUs at their attributed lineage
and links the whole decoded image. Each new TU registers every emitted text
and data section. A placement can select complete function sections from an existing
home TU. Each placement has its own link namespace and explicit bindings
for references beyond its selected sections. Imported decoded gaps are
separate `.incbin` sections. Every function and the full image must match
retail before recompression. The regenerated streams replace their exact
physical ranges in `build/decoded/disc/`, which has the ordinary disc layout.
`tools/build/container_check.py` also consumes these streams when composing the
standard disc containers. Nothing writes the extracted retail inputs.

The menu cache owns 421 C functions, 54,116 decoded text bytes
and 920 bytes of C-emitted tables. The full image is 60,192 bytes at
0x80016000. The 5,156 imported bytes comprise 3,052 bytes of code, 2,001 bytes
of text, 91 bytes of alignment and 12 data bytes with unproved owners.
The two regenerated compressed streams occupy 28,662 bytes in the disc
container. Registry validation checks the registered function count and the text, data, import and stream byte totals. Headers,
resource tails and the rest of the container remain imported assets. A full
DUNGEON comparison checks every byte of the completed container.

Census and provenance
---------------------

`python3 tools/decoded/census.py --root . --output build/compressed-census.json`
scans all four retail containers for bounded resource-command streams and every
CD-sector start, then tests all four instruction alignments. The current layout
contains four code-bearing streams in two cache sets:

| Container offsets | Decoded sizes | Status |
| --- | --- | --- |
| DUNGEON 0x4A3014, 0x4A7014 | 30,096 + 30,096 | Live menu cache. The resident decoder writes it at 0x80016000 and resident code calls into it. |
| DUNGEON 0xF824, 0x13824 | 33,474 + 28,150 | Legacy cache inside the second town-engine region. Both streams recompress exactly; executable signatures are strong, but current-game loader reachability and C ownership remain unproved. |

The legacy resource has TWO upload commands whose offsets are relative to the
resource base at 0xF800. Its second output begins at byte 33,474, halfway through
an instruction word. Counting only aligned starts or only data offset 20 misses
this set. Signature evidence does not create function rows or prove reachability.
The census is bounded by these asset layouts; arbitrarily unaligned/headerless
streams and other packing formats remain outside its exhaustion claim.

The current image producer accepts a single terminating command-5 upload with
data offset 20. It rejects the legacy multi-command resource contract; extending
that contract requires validating the resource base and every header in its
list, rather than treating the second command's offset as header-relative.
The codec and census already handle both legacy streams and their split word.

Reuse and validation
--------------------

Add a manifest with independently established source commands, stream hashes,
decoded VMA/extent, complete TU functions, explicit import bindings and evidence.
`placement` identifies a reuse of a home source. A function's `symbol` gives
the emitted home symbol and its `name` gives the decoded entry identity.
`bindings` supplies the placement's relocation targets by emitted symbol.
References to other exports of the same placement resolve at their registered
decoded addresses. The linker discards unselected sections and requires
all relocations from the selected sections to resolve.
New TUs can register a complete emitted `.rodata` or `.data` section by
name, address and size. Those sections take part in the whole-image byte
comparison and are counted separately from text in the proof. The linked pointer tables are checked with their relocations applied.
`trim_end_padding` explicitly permits removing the GNU assembler's zero end
padding from an owned section. The check preserves its symbols and relocations.
Imported bytes can begin immediately after an unaligned data extent.
`proof_mode: recompress` is the normal path. `decoded-only` is available when a
later encoder policy is not yet known and explicitly leaves the compressed blob
as an imported asset. Never count decoded bytes as physical row coverage.

Run `python3 tools/decoded_images.py check`, `make decoded-images`, and
`bash tools/lanes/prove_scope.sh <changed paths>`. The scope tool selects
decoded images for their registered sources. Changes to a project header
under `include/` or `src/` select every decoded image. Paths outside those
directories also select every decoded image.
The same command verifies the affected ordinary images.

`tools/decoded/genuine.py` needs the genuine assembler and a short scratch
path. A unit can record `genuine_asflags: ["-0"]` when the retail instructions
omit the assembler's signed division checks. The actor selector, party
selector and command panel use this flag because plain `-G0` adds a 36-byte
division guard to each shade routine.

`tools/tests/test_decoded_images.py` checks coordinate confusion, overlaps,
malformed inputs, resource-relative offsets, split alignment, scope selection,
whole-TU extents and regenerated-container identity.

Tools that inspect the loaded menu code use decoded offsets and check the
section hashes in `config/decoded` first.
