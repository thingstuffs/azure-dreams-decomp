Decoded executable images
=========================

`config/decoded/*.json` registers decoded instruction coordinates separately
from physical disc offsets. `tools/decoded_images.py rows` exports their stable
`decoded/<image>/<function>` identities. The physical row database and link graph
are unchanged. Their checks validate this additional registry and source layout.
Never split a raw floor row using an address observed after decompression.

Implemented path A: exact recompression
--------------------------------------

The resident decoder (`src/engine/graphics/decompress_lz.c`) uses LSB-first,
interleaved flags: 0 literal; 10 long reference or zero terminator; 11 short
reference with two count bits. `tools/decoded/lz.py` reproduces its encoder with
greedy longest matches, nearest ties, a 4095-byte history and a fresh dictionary
per stream. Short matches cover distances 1..256 and lengths 2..5; long matches
cover distances 1..4095, lengths 3..17 or an explicit count up to 256. A stream
may split an instruction word; concatenation must not add alignment.

The nearest-tie policy reproduces all four discovered code streams exactly;
oldest ties do not. This is a measured per-stream result, not an assertion about
all compressed graphics assets. Every production build still verifies length
and SHA-256 of each regenerated stream against retail. There is no token recipe,
embedded retail payload, masked relocation or fallback to an imported stream.

`make decoded-images` compiles complete C TUs at their attributed lineage,
verifies that every emitted text section has an explicitly registered extent,
rejects unowned TU data, and links the whole decoded image. Imported decoded
gaps are separate `.incbin` sections. Every function and the full image must
match retail before recompression. The regenerated streams replace their exact
physical ranges in `build/decoded/disc/`, which has the ordinary disc layout.
`tools/build/container_check.py` also consumes these streams when composing the
standard disc containers. Nothing writes the extracted retail inputs.

Four nested live callees were added after native registration exposed them,
including a 177-call callback. The original eleven requested functions remain
individually exact. The menu cache owns fifteen C functions / 1,320 decoded text bytes. Its full
image is 60,192 bytes at 0x80016000; 58,872 bytes remain explicit imported decoded
gaps. The two regenerated compressed streams total 28,662 physical bytes, but
those bytes are NOT 28,662 bytes of matched C coverage. Headers, resource tails
and the rest of the container remain imported assets. A full DUNGEON container
comparison checks that the splice changes no physical byte.

Census and provenance
---------------------

`python3 tools/decoded/census.py --root . --output build/compressed-census.json`
scans all four retail containers for bounded resource-command streams and every
CD-sector start, then tests all four instruction alignments. The current layout
contains four code-bearing streams in two cache sets:

| Container offsets | Decoded sizes | Status |
| --- | --- | --- |
| DUNGEON 0x4A3014, 0x4A7014 | 30,096 + 30,096 | Live menu cache; native decompressor write and calls independently witnessed. Production C and recompression integrated. |
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
`proof_mode: recompress` is the normal path. `decoded-only` is available when a
later encoder policy is not yet known and explicitly leaves the compressed blob
as an imported asset. Never count decoded bytes as physical row coverage.

Run `python3 tools/decoded_images.py check`, `make decoded-images`, and
`bash tools/lanes/prove_scope.sh <changed paths>`. The scope tool includes decoded
images for their C/header dependencies and all build-authority changes. The
ordinary raw-image proof remains in force. Independent genuine-ASPSX proof is
available through `tools/decoded/genuine.py` (explicit private work and short
scratch paths). `tools/tests/test_decoded_images.py` tests coordinate confusion,
overlap, malformed inputs, resource-relative offsets, split alignment, scope
selection, whole-TU extent rejection and exact regenerated-container identity.

Native adapters must use decoded offsets and verify the loaded code identity.
The retained lane adapter requires the nominal VMA and all fifteen complete C
section hashes before selecting the menu bank, ahead of stale CD load labels.
The production decoded registry is the source of these identities; the native
runtime remains a separately delivered private adapter.
