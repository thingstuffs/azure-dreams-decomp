# Physical byte coverage

The full `make check` compares the [summary table](physical_coverage.tsv)
against the census. To regenerate it, pass the linked executable and its GNU
linker map from the same build.

```sh
python3 tools/physical_census.py \
  --slus-map build_slus/build/slus_006.14.map \
  --slus-image build_slus/build/slus_006.14
```

The census checks the size and hash of each extracted container. It uses the
user's disc image at `bin/Azure Dreams.bin` or `AZURE_CLEAN_DISC` for the ISO
directory and sector reads. Use `--disc-root` to locate extracted containers
in another checkout. For SLUS, the tool checks executable equality and the
bounds of the linker's allocations against the disc executable's load header.

C ownership is the physical union of registered source rows and native
allocations. C placements are a subset of ownership. Explicit zero alignment
counts as padding. The checked asset and padding classes verify content at
recorded map or linker extents. The retail text class checks disc hash
windows, typed declarations, and the corresponding link or native module
allocations. The ledger integrity gate also checks the recorded cross-image
comparisons. `--json` includes the breakdown of imports and unclassed bytes.

Readers transfer whole sectors. A read class records that a transfer covers
an extent. Transfers can overlap each other, C allocations and separately
classified residue. The census counts each byte once, in the order of
`CLASSES`. Comparison of ISO sectors with the extracted file verifies the
extraction. The payload checks below cover specific reader bounds and fields.

## Reads derived from disc tables

The table checks use addresses and selection rules recorded in
`tools/scene_read_spans.py`. The census reads the table contents from the disc
executable or the indicated container. The tool authenticates no consumer
functions for these classes. It refuses altered coordinates, containers and
selections, and missing entries within a submitted class. The committed
summary detects removal of an entire counted class. A change to a table
address, selection rule or bound in the tool can change the derived claims.

- **Scene groups and movie overlay.** The executable supplies the group count
  table and the descriptor pointers for groups one through three. The scene
  loop's sector rule combines the initial count with the descriptor's tail.
  The first resident movie descriptor supplies the OVMOVIE extent. The check
  verifies transfer coordinates. It leaves these payloads uninterpreted.
- **Sound banks, sets and streams.** Tables at fixed executable addresses
  supply the paired effect-bank reads, the sound-mode reads and the stream
  descriptors. The bank and set checks also validate the expected destination
  mode, and the bank check bounds the channel slot. The checks read the
  descriptors and leave the transfer payloads uninterpreted.
- **Indexed sprite bundles.** Three executable table entries pair disc
  descriptors with upload destinations. The check refuses a destination or
  container mismatch and parses the upload row bounds in each payload.
- **Town texture commands and character catalog.** The executable supplies
  the texture command descriptors. The Town container supplies the character
  catalog, which selects executable descriptors and can alias a descriptor
  across IDs. The check verifies the expected Town container and destination
  for each read. It leaves the payloads uninterpreted.
- **Town setup, movie queue and default scene.** Six descriptors at fixed
  addresses in the executable and Town engine supply the setup and queue
  reads. A separate resident descriptor supplies the default scene transfer.
  The check verifies the expected containers and destinations and leaves the
  payloads uninterpreted.
- **Dungeon floor images, layouts and module reloads.** Two descriptors in
  the Dungeon container supply the module reloads and their destinations.
  The first module's track and variant tables, together with their layout
  descriptors, select the image and fixed layout reads. These checks read
  the descriptors and tables and leave the transfer payloads uninterpreted.
- **Dungeon floor chunks and Town map chunks.** The floor layout and module
  tables select the Dungeon chunks. Town variant and packed-resource tables
  select the Town chunks. The checks derive the first and continuation
  transfers from the descriptors and fixed stride. They decode each chunk
  within the read and destination limits and refuse malformed or empty
  output.

## Reads derived from formulas

**Paired sprite reads.** The Dungeon sector formula and the special
three-slot metadata transfer are specified in `tools/sprite_read_spans.py`.
Town uses two disc catalog entries and the Town sector formula in the same
tool. The check pins the whole reader routines by hash. The short Town
reservation routine uses a sixteen-byte window covering its twelve bytes
and four adjacent bytes. The hashes authenticate the reader bytes. Formula
constants are constants in the tool, not read from the hashed routines; a
changed constant with regenerated records passes. The check refuses
mismatched reader hashes and mismatched transfer coordinates, and parses
the two metadata pointer arrays and the presence of tile and palette
payloads. The Dungeon manifest can omit an individual valid pair.

**Dungeon monster banks.** Normal extents come from the loader formula and
fixed bank extents from two fixed-size loader branches. Older receipts pin
the loader and the disc windows by hash and check the first pointer against
the destination window. The placement receipts also compare loader and
resident helper bytes with the disc. Review of the older receipts is pending.
Other formula-allowed pairs can pass the older check if their first pointer
is in bounds. The registered receipts require the production view and its
entry row. The fixed reads require a registered C row matching the disc
pointer, physical offset and runtime address. The checker refuses a wrong
entry binding or transfer coordinate. It parses the entry pointer and leaves
the rest of the bank uninterpreted.

**Dungeon floor spawn tables.** The ordinary-floor selector and sector base
are a formula reproduced in `tools/scene_read_spans.py`. The tool compares
records against that formula and compares the resulting sectors with the
extracted container. The formula is independent of the disc and the tool
currently binds neither the base nor the floor bound to the loader and its
caller. These bytes count as declared. The check leaves the spawn records
uninterpreted.

## Linked diagnostic and foreign code

**Linked diagnostic code.** The ledger records a range in a hashed
devkit-linked image. The checker follows a direct call from a registered row,
a callback table addressed by registered rows, or a linked wrapper. It
verifies the recorded entry and a return at the recorded end and refuses a
mismatched entry, image hash, duplicate coverage or overlap with compiled
allocations. More than one end can satisfy the return check. The extents
are interim evidence pending byte-matched C.

**Foreign program fragments.** The ledger gives the source extent in MAIN for
each Town fragment. The integrity gate compares the two ranges and refuses a
changed byte or an extent that disagrees with the recorded word count. The
640-byte fragment has the same file offset in Town and MAIN. This comparison
checks the recorded extent. No payload fields are parsed and the check places
no requirement on adjacent bytes.

## Residue, copy and linked classes

Each entry gives the extent source, what the census or the ledger integrity
gate compares, and the limit of that comparison. The census applies the
`CLASSES` order, so a byte already counted by an earlier class is not counted
again. The residue classes come from the active, latest, non-overlapping
records of `ledger/coverage_regions.jsonl`. For each such record that carries
`retail_sha256`, the census hashes the disc window (`hash_size` when present,
else `size`) and refuses a difference. The gate checks below add to that and
run only where the disc is present.

- **`stale_town_copy`.** Extent: ten DUNGEON records that cite
  `docs/evidence/retail_byte_ownership.json`. Checked: each record must carry
  `compare_container`, `compare_foff` and `words`, the word count must equal
  the size divided by four, and the range must equal the named TOWN range word
  for word. Limit: equality shows the bytes are a copy, and the tool does not
  test whether any code reaches them.
- **`prior_town_image`.** Extent: records that match
  `link/leftovers/stale_images/intervals.json` (container, offset, size and
  digest). The ledger currently holds no active record, so the class counts 0
  bytes. Checked, once a record exists: the match with that index and the disc
  digest. Limit: the index is a list of ranges, and the check does not parse
  their content.
- **`formatter_remnant`.** Extent: four DUNGEON records in
  `docs/evidence/retail_byte_ownership.json`. Checked: a valid
  `retail_sha256` against the disc, and, where a record carries compare fields,
  equality with the named range word for word. Limit: the target range is the
  tool's only comparison, and no call target or data reference is parsed.
- **`formatter_build_string`.** Extent: three DUNGEON records in the same
  evidence file. Checked: a valid `retail_sha256` against the disc. Limit: the
  digest fixes the bytes and the tool reads no text from them.
- **`older_dungeon_head_bank`.** Extent: nine banks recorded in
  `docs/evidence/older_dungeon_head_banks.json`, with one ledger record per
  bank (scope `bank`). Checked by
  `older_head_bank_problems` in `tools/lint/ledger_integrity.py`: each record
  spans its complete bank; each bank's entry word,
  both call targets, the resident function's body hash, the hash of the call
  sequence and each record's hash equal the disc. Limit: that no loader reaches
  these banks rests on the evidence file's stated absence of references in the
  surveyed resident code, which the tool does not test.
- **`bank_pointer_table`.** Extent: four DUNGEON records, each between a bank
  header and its first routine in `config/link/dungeon/bank_<offset>.json`.
  Checked by `bank_pointer_table_problems`: the table starts at the end of the
  header and ends at the routine, its size is a multiple of four, its hash
  equals the disc, the null slot count matches, and every other word is a
  4-aligned address inside the bank's load window. Limit: a word inside the
  window is not checked against a particular target.
- **`proven_c_copy`.** Extent: records of `ledger/instances.jsonl` whose
  result is `proven`, in the overlay containers, unless an `instance_excluded`
  region names the same range. Checked by the census: only the extent and the
  exclusion. The byte-exact compile is recorded in each instance's source hash
  and receipt and is not repeated here. The headline counts the class as
  declared, not checked.
- **`sdk_asm`.** Extent: in SLUS, linker map inputs under `build/asm/psyq/`;
  in the overlays, active `sdk_asm` records of
  `ledger/coverage_regions.jsonl` (18 records in MAIN, OVMOVIE and TOWN, citing
  `docs/evidence/r121_remnants.sdk.json`). Checked: for SLUS, the whole image
  equals the disc executable and the map bounds match its load header. For the
  overlay records the census reads the extent only and does not compare the
  disc against the digest they carry. The headline counts the class as
  declared, not checked.
- **`hand_asm`.** Extent: SLUS linker map inputs under `build/asm/` other
  than `build/asm/psyq/`. Checked: the same image equality and load-bound
  check as for `sdk_asm`. Limit: the class is assigned by input path, and the
  headline counts it as declared, not checked.
- **`linked_asset`.** Extent: SLUS linker map inputs under `build/assets/` or
  `build/module_assets/`. Checked: the same image equality and load-bound
  check, and the census refuses map inputs that overlap or fall outside the
  executable. Limit: the class is assigned by input path, the asset content is
  not interpreted, and equality with the disc does not show the source of the
  asset. The headline counts the class as checked.
