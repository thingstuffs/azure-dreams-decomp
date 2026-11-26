# Konami / Sony assertion sites left on the Azure Dreams disc

*Static catalogue, drafted 2026-08-27. Companion data: `docs/evidence/konami_assertion_sites.csv`
(one row per site **copy**). Inputs: `bin/Azure Dreams.bin`, `baserom/slus_006.14`,
`overlays/{town,main}/overlay_first_pass_results.json`. Nothing here was run; every claim is
derived from the retail bytes.*

PSY-Q's `assert()` macro compiles to a plain `printf` of the **source file name and line
number** of the call site. Konami shipped a debug build of several modules, so those `printf`s
— and their `__FILE__` / `__LINE__` arguments — are still on the disc. **Every one of them is a
fixed point on the original source file: a function whose C body provably contains line N of
`<file>.c`.** That makes this a partial source map, which is the reason to keep it.

## 0. Headline numbers

| | |
|---|---|
| call sites located (copies) | **458** |
| distinct sites after dedup | **89** |
| distinct Konami/Sony source files named | **15** |
| independently derived overlay load bases | **66** |
| containers with sites | TOWN.BIN (392 copies), MAIN.BIN (66). DUNGEON.BIN and OVMOVIE.BIN: **zero** |

Distinct sites per source file:

| file | distinct | copies | where |
|---|---|---|---|
| `MAIN.BIN+0x25d028/11` (Sony libcard) | 43 | 51 | MAIN.BIN, two different revisions |
| `TOWN.BIN+0x2ab88c/7` | 7 | 270 | TOWN.BIN game overlays |
| `TOWN.BIN+0x2ab85c/8` | 4 | 40 | TOWN.BIN game overlays |
| `TOWN.BIN+0x7f88e8/10` | 4 | 21 | TOWN.BIN devkit blob |
| `TOWN.BIN+0x7f891c/8` | 4 | 8 | TOWN.BIN devkit blob |
| `MAIN.BIN+0x269620/11` | 3 | 3 | MAIN.BIN devkit module |
| `MAIN.BIN+0x2697cc/11` | 3 | 3 | MAIN.BIN devkit module |
| `MAIN.BIN+0x269894/9` | 2 | 4 | MAIN.BIN devkit module (+ a code-only copy in TOWN.BIN) |
| `MAIN.BIN+0x269570/11`, `MAIN.BIN+0x2695c8/11`, `MAIN.BIN+0x269654/9`, `MAIN.BIN+0x269760/11`, `MAIN.BIN+0x269800/10` | 1 each | 1 each | MAIN.BIN devkit module |
| `TOWN.BIN+0x2ab958/9` | 1 | 4 | TOWN.BIN game overlays |
| `TOWN.BIN+0x7ffb44/9` | 1 | 2 | TOWN.BIN devkit blob |
| *(expressions with no file attribution)* | 10 | 47 | see §3.3 |

### 0.1 CSV column key

`docs/evidence/konami_assertion_sites.csv`, one row per **site copy** (458 rows):

Text locations give the container, byte offset and length including the terminator.
Each distinct string has one representative location so copies retain their grouping.

| column | meaning |
|---|---|
| `container` | `TOWN.BIN` / `MAIN.BIN` |
| `chunk_pool_foff` | file offset of the format string this site points at (identifies the chunk's `.rdata` pool) |
| `site_foff` / `site_vram` | file offset and runtime address of the `jal`/`jalr` |
| `derived_base` | `site_vram − site_foff` for this chunk, derived per §1.3 |
| `source_file` | Representative disc location of the source filename, or of the inferred owner for an expression. Blank when unattributed. |
| `line` | `__LINE__`, exact; blank for `expr` |
| `kind` | `assert` / `mark` / `expr` |
| `expression_or_null` | Representative disc location of the printed expression for expression rows. |
| `containing_function` | the repo's **nominal** `func_XXXXXXXX` label |
| `containing_func_foff` / `_vram` / `_size` | its file offset, **true** vram (from `derived_base`), and byte size |
| `func_status` | first-pass sweep result: `MATCH`, `dup:MATCH` (retired into a matched dedup cluster), `not-in-sweep` |
| `true_name` | the repo's recorded true name, where it has one |
| `distinct_id` | `D001`…`D089`; rows sharing one are copies of the same source assertion |
| `attribution` | `direct` / `same-function` / `rdata-block-before` / `unattributed` |
| `notes` | base caveats and the `.rdata` pool neighbours used for attribution |

## 1. Method

### 1.1 The three macros

Three PSY-Q-style debug macros are present. Each is a single `printf`, so each call site is a
recognisable 3-argument setup:

| Kind | Format purpose | Additional arguments |
|---|---|---|
| Assertion | Report the source and line of a failed check | Source name and line number |
| Trace | Mark a source location | Source name and line number |
| Expression | Report the value of a developer expression | Expression location and value |

The source name immediately follows the format's aligned storage.
The original values are available from the catalogue's disc locations.

### 1.2 Finding the diagnostic calls

The resident diagnostic entry at `0x80069F18` is the BIOS wrapper named
`printf` in the executable symbol list. A direct call scan found 24 PSY-Q
library sites in SLUS and 24 shipped libcard sites in MAIN.BIN. The other
42 MAIN.BIN sites call the development image's entry at `0x8007C040`.

Town overlays call through service slot `0x168`. The service table pointer
is at offset `0x20` of the overlay work block. Assertions then call exit
through slot `0x174` with status one. This accounts for 390 of the 392
TOWN.BIN sites. The two direct calls belong to the code-only copy of
the MAIN.BIN development module (§6). The town development tools use
service slots `0x64` and `0x70` for diagnostics and exit.

The scan visits direct and indirect calls. It follows constant arguments
across up to 48 preceding instructions, accounting for return boundaries,
caller-saved registers and the call delay slot. This recovers the format,
the source or expression address, and the line number when present.

### 1.3 Self-calibrating the load base

For each candidate format copy, subtract its file offset from the
recovered runtime format address. The candidate base must be a multiple
of 0x800. The source address minus the base must identify a printable
C filename. The format copy must be within 0x200000 bytes of the call.

Each format-string copy then takes the majority base of the sites that point at it, and every
other debug string in the same pool inherits it. **66 distinct chunk bases** come out. They are
listed in §5. 99 of the located sites sit in a function for which the repo already records a
`true_name`; the derived base reproduces it on **62** of them, and of the 37 that differ, **25**
are the MAIN.BIN module-boundary error documented in §8 and **12** are TOWN devkit-blob sites
where the repo's `true_name` is only the synthetic `file + 0x80080000` label (i.e. no proven base
existed there and this document supplies one). For the remaining ~54 town chunks the repo has no
proven base at all.

### 1.4 Containing function and dedup

The original scan bounded functions using the previous return and its
delay slot, then refined the entry to the last stack allocation. In all
eight copies associated with `TOWN.BIN+0x7f891c/8`, the compiler places
the flag address and value loads before stack allocation. The old
refinement therefore recorded entries eight bytes late. All eight were
outside the 99 exact-offset size checks.

The 2026-10-15 r121 audit moves the entries to the preceding return
boundary and keeps the original ends. The recorded scan ranges contain
direct calls to every corrected entry and none to the stack allocation.
The loaded flag value reaches the assertion branch unchanged. Five corrected starts are existing MATCH rows;
the other three remain unregistered physical copies. The reproducible, fail-closed check is
`python3 tools/assertion_boundaries.py --check`, with exact extents and reference-scan ranges
in `docs/evidence/tobjs_assertion_boundaries.json`. `--apply` repairs the historical data
idempotently. This does not authorize rounding other assertion offsets down to a containing
row: genuine composite rows still require a separate extent audit.

Copies are collapsed on the semantic tuple `(kind, source file, line)` for `assert`/`mark` and
`(source file, expression text)` for `expr` — that is the identity of the assertion *in the
original source*. The containing functions were cross-checked with a relocation-masked SHA-1
(j/jal targets and `%hi`/`%lo` immediates zeroed), which is also how a copy that the sweep
retired into a dedup cluster is resolved back to the representative's decomp name.

### 1.5 Caveats

* **Line numbers are exact; expression attribution is not.** `__LINE__` is a compile-time
  constant in the instruction stream. The source file an *expression* string belongs to has to be
  inferred from `.rdata` block adjacency, and is only asserted here when the block is immediately
  preceded by that file's `[assert fmt][__FILE__]` pair, or when the same function also carries an
  `assert`/`mark` of that file. Everything else is left unattributed (§3.3).
* **Nominal vs true names.** `containing_function` in the CSV is the repo's nominal
  `func_<foff + synthetic base>` label (`0x80080000` for TOWN, `0x7FDB0000` for MAIN). The
  *true* vram is the separate `containing_func_vram` column, computed from the derived base.
* **Copy counts are of shipped code, not of source.** 54 copies of `TOWN.BIN+0x2ab88c/7:40` are 54 re-links
  of one object file into 54 overlay chunks, not 54 assertions.
* Four findings correct `port/docs/report_console.md` §5; see §8.

## 2. Where the sites are

| region | container / file range | link base | chunks | site copies | distinct | shipped? |
|---|---|---|---|---|---|---|
| Town scene / shop / story overlays | TOWN.BIN, pools `0x2AB834`–`0x8D2144` | 54 different bases, all mapping the pool into `0x8001xxxx` | 54 | 335 | 18 | **yes** |
| Devkit tool blob | TOWN.BIN `0x7F7FCC`–`0x844CE4` | `0x80700000`, `0xA0700000`, and 3 *unrelocated* objects | 9 | 55 | 12 | no |
| libcard card server | MAIN.BIN `0x25D000`–`0x269000` | `0x80020000` | 1 | 24 | 24 | **yes** (loaded at boot) |
| Memory-card front end | MAIN.BIN `0x269000`–`0x275800` | `0x80400000` | 1 | 42 | 40 | no — devkit-only address |
| " (code-only copy) | TOWN.BIN `0x2713FC`–`0x271560` | `0x80400000` | 1 | 2 | 2 | no |
| DUNGEON.BIN | — | — | 0 | 0 | 0 | — |
| OVMOVIE.BIN | — | — | 0 | 0 | 0 | — |

The scan found no diagnostic formats or source filenames in DUNGEON.BIN
(27.8 MB) or OVMOVIE.BIN (3.1 MB).

The resident executable has 24 direct diagnostic calls in PSY-Q
libraries and no Konami assertion sites. The library build stamps are
at executable file offsets `0x6AC8`, `0x6D78` and `0x6EFC`.
See `port/docs/report_console.md` §5.1 for the original scan.

## 3. Distinct sites, by source file

`copies` = how many linked copies of that one source assertion exist on the disc.
`decomp status` is the state of the containing function in the first-pass sweep;
"MATCH (as dedup rep)" means this copy was retired into a cluster whose representative
byte-matched.

### 3.1 TOWN.BIN — Konami's town/shop code

#### `TOWN.BIN+0x2ab88c/7` — 7 distinct sites, 270 copies

Canonical chunk: TOWN.BIN pool/base `0x7FC27000`.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| — | expr | `TOWN.BIN+0x2ab8a0/44` | `func_80472D04` | `0x80019D04` | MATCH (as dedup rep) | 54 |  |
| — | expr | `TOWN.BIN+0x2ab8cc/47` | `func_80472D04` | `0x80019D04` | MATCH (as dedup rep) | 54 |  |
| — | expr | `TOWN.BIN+0x2ab8fc/9` | `func_80472D04` | `0x80019D04` | MATCH (as dedup rep) | 54 |  |
| 39 | assert | — | `func_806D29EC` | `0x800161EC` | MATCH (as dedup rep) | 7 | chunk 0x7F9C3800 |
| 40 | assert | — | `func_804721A4` | `0x800191A4` | MATCH (as dedup rep) | 47 |  |
| 54 | assert | — | `func_806D2AB0` | `0x800162B0` | MATCH | 7 | chunk 0x7F9C3800 |
| 55 | assert | — | `func_80472278` | `0x80019278` | MATCH (as dedup rep) | 47 |  |

#### `TOWN.BIN+0x2ab85c/8` — 4 distinct sites, 40 copies

Canonical chunk: TOWN.BIN pool/base `0x7FC27000`.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 65 | assert | — | `func_80471AC4` | `0x80018AC4` | MATCH (as dedup rep) | 10 |  |
| 113 | assert | — | `func_80471CD0` | `0x80018CD0` | MATCH (as dedup rep) | 10 |  |
| 118 | assert | — | `func_80471CD0` | `0x80018CD0` | MATCH (as dedup rep) | 10 |  |
| 128 | assert | — | `func_80471E70` | `0x80018E70` | MATCH (as dedup rep) | 10 |  |

#### `TOWN.BIN+0x2ab958/9` — 1 distinct site, 4 copies

Canonical chunk: TOWN.BIN pool/base `0x7FC27000`.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 64 | assert | — | `func_804732A4` | `0x8001A2A4` | MATCH (as dedup rep) | 4 |  |

#### `TOWN.BIN+0x7f891c/8` — 4 distinct sites, 8 copies

Canonical chunk: TOWN.BIN pool/base `0x7FF01000`.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 75 | assert | — | `func_808816D8` | `0x80700ED8` | MATCH | 4 | chunk 0x7FEFF800; two registered and two unregistered copies |
| 89 | assert | — | `func_80880298` | `0x80701298` | MATCH | 2 | one registered and one unregistered copy |
| 225 | assert | — | `func_808B85F0` | `0x00003DF0` | MATCH | 1 | object-relative address; registered link name func_80003DF0 |
| 226 | assert | — | `func_80878A78` | `0x80702A78` | MATCH | 1 | chunk 0x7FF0A000 |

#### `TOWN.BIN+0x7f88e8/10` — 4 distinct sites, 21 copies

Canonical chunk: TOWN.BIN pool/base `0x7FF01000`.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| — | expr | `TOWN.BIN+0x7f88c4/13` | `func_80880194` | `0x80701194` | not-in-sweep | 7 |  |
| — | expr | `TOWN.BIN+0x7f88bc/8` | `func_80880194` | `0x80701194` | not-in-sweep | 7 |  |
| 47 | mark | — | `func_80878974` | `0x80702974` | MATCH | 2 | chunk 0x7FF0A000 |
| 48 | mark | — | `func_80880194` | `0x80701194` | not-in-sweep | 5 |  |

#### `TOWN.BIN+0x7ffb44/9` — 1 distinct site, 2 copies

Canonical chunk: TOWN.BIN pool/base `0x7FF01000`.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 201 | mark | — | `func_8087FEF0` | `0x80700EF0` | MATCH | 2 |  |

### 3.2 MAIN.BIN — Sony's libcard and Konami's card menu

See §6 for the two-image split and §4.3 for the two `MAIN.BIN+0x25d028/11` revisions.

### 3.3 Expressions with no file attribution

The decimal and hexadecimal diagnostic expressions in this table have
no immediately preceding assertion format and source pair in their
read-only data blocks. The scan identified their containing functions.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| — | expr | `MAIN.BIN+0x269120/20` | `func_8001AF98` | `0x80401F98` | MATCH | 2 | chunk 0x80197000 |
| — | expr | `TOWN.BIN+0x3e817c/5` | `func_80471544` | `0x80018544` | not-in-sweep | 6 |  |
| — | expr | `TOWN.BIN+0x7f7fd8/5` | `func_80877FEC` | `0x80701FEC` | MATCH | 8 | chunk 0x7FF0A000 |
| — | expr | `TOWN.BIN+0x7f7fe0/5` | `func_80877FEC` | `0x80701FEC` | MATCH | 8 | chunk 0x7FF0A000 |
| — | expr | `TOWN.BIN+0x3e8184/10` | `func_80471544` | `0x80018544` | not-in-sweep | 6 |  |
| — | expr | `TOWN.BIN+0x3e8190/10` | `func_80471544` | `0x80018544` | not-in-sweep | 6 |  |
| — | expr | `TOWN.BIN+0x2ab918/6` | `func_803301B8` | `0x8001A9B8` | MATCH | 1 | chunk 0x7FD6A800 |
| — | expr | `TOWN.BIN+0x2ab920/6` | `func_803301B8` | `0x8001A9B8` | MATCH | 1 | chunk 0x7FD6A800 |
| — | expr | `TOWN.BIN+0x2ab928/5` | `func_803301B8` | `0x8001A9B8` | MATCH | 1 | chunk 0x7FD6A800 |
| — | expr | `TOWN.BIN+0x7f7fe8/4` | `func_80877FEC` | `0x80701FEC` | MATCH | 8 | chunk 0x7FF0A000 |

Each block's `.rdata` neighbours are recorded in the CSV `notes` column
(`pool-neighbours before:… after:…`). What can be said about each:

* `TOWN.BIN+0x3e817c/5` / `TOWN.BIN+0x3e8184/10` / `TOWN.BIN+0x3e8190/10` — the block sits immediately **before** `TOWN.BIN+0x2ab85c/8`'s
  `[assert fmt][TOWN.BIN+0x2ab85c/8]` pair and its function sits immediately before `TOWN.BIN+0x2ab85c/8`'s functions.
  It is **not** `TOWN.BIN+0x2ab85c/8` itself: the TOWN.BIN `0x7FD6A800` chunk links `TOWN.BIN+0x2ab85c/8` (same
  assert lines 65/113/118/128) with no corresponding expression strings at all, which an identical
  object file could not do. ⇒ a separate, unnamed object that precedes `lshop.o` in 6 overlays.
* `TOWN.BIN+0x2ab918/6` / `TOWN.BIN+0x2ab920/6` / `TOWN.BIN+0x2ab928/5` — one copy only (TOWN.BIN `0x7FD6A800`, function
  `func_803301B8` @ `0x8001A9B8`). Sits between `main.o`'s expression function and
  `player.o`'s. `port/docs/report_console.md` §5.3 lists them under `TOWN.BIN+0x2ab85c/8`; that was a
  proximity guess and the block layout does not support it.
* `TOWN.BIN+0x7f7fd8/5` / `TOWN.BIN+0x7f7fe0/5` / `TOWN.BIN+0x7f7fe8/4` — devkit blob. In the TOWN.BIN `0x7FF01000` chunk this block is
  a decimal format, three expressions, then the trace format and source name. The containing function sits
  immediately before `TOWN.BIN+0x7ffb44/9:201`'s. ⇒ **probably `TOWN.BIN+0x7ffb44/9`** (inferred, not proven; two of
  the nine devkit chunks carry the block without any `TOWN.BIN+0x7ffb44/9` string).
* `MAIN.BIN+0x269120/20` prints a Konami save-work checksum in hexadecimal from
  `func_80401F98` in the MAIN.BIN development module. It sits in the Sony libcard pool tail.

## 4. The implied source map

This is the payoff: each row below is a **function whose C body provably spans the given source
lines**. Function order within a chunk follows object-file link order, and within an object file
it follows source order, so the assertions also fix the *relative* position of the objects.

### 4.1 A town scene overlay, front to back (TOWN.BIN chunk `0x7FC27000`, pool `0x3EF020`)

| true vram | nominal name | pins | object file |
|---|---|---|---|
| `0x80018544` | `func_80471544` | `TOWN.BIN+0x3e817c/5`, `TOWN.BIN+0x3e8184/10`, `TOWN.BIN+0x3e8190/10` | unnamed (§3.3) |
| `0x80018AC4` | `func_80471AC4` | **`TOWN.BIN+0x2ab85c/8:65`** | `lshop.o` |
| `0x80018CD0` | `func_80471CD0` | **`TOWN.BIN+0x2ab85c/8:113`, `TOWN.BIN+0x2ab85c/8:118`** | `lshop.o` |
| `0x80018E70` | `func_80471E70` | **`TOWN.BIN+0x2ab85c/8:128`** | `lshop.o` |
| `0x800191A4` | `func_804721A4` | **`TOWN.BIN+0x2ab88c/7:40`** | `main.o` |
| `0x80019278` | `func_80472278` | **`TOWN.BIN+0x2ab88c/7:55`** | `main.o` |
| `0x80019D04` | `func_80472D04` | `TOWN.BIN+0x2ab8a0/44`, `TOWN.BIN+0x2ab8cc/47`, `TOWN.BIN+0x2ab8fc/9` | `main.o` |
| `0x8001A2A4` | `func_804732A4` | **`TOWN.BIN+0x2ab958/9:64`** | `player.o` |

The same shape, with the same line numbers, repeats across the other 53 town chunks, though
most carry only the `main.o` subset — see the `files` column of §5. Chunk `0x7FD6A800`
(pool `0x2AB834`) is the other full one; it additionally carries the `TOWN.BIN+0x2ab918/6`/`TOWN.BIN+0x2ab920/6`/`TOWN.BIN+0x2ab928/5`
function between `main.o`'s expression function and `player.o`'s.

What this says about the sources:

* **`TOWN.BIN+0x2ab85c/8` is a small file.** All four of its assertions land in lines 65–128, in three
  consecutive functions, and it is linked ahead of `main.o` and `player.o` in every town
  overlay that carries it. A function containing line 65 sits roughly 50 lines in, i.e.
  `TOWN.BIN+0x2ab85c/8` opens with one or two functions before it.
* **`TOWN.BIN+0x2ab88c/7`'s first two assertions are at lines 39/40 and 54/55** — the very top of the file,
  and the two functions are adjacent (`0x191A4` → `0x19278`, 0xD4 bytes apart). Note the
  **two revisions**: 47 chunks carry lines **40 / 55**, 7 chunks carry **39 / 54** — one line
  was inserted (or removed) above them between two builds. Everything else about the two
  revisions matches, including the expression triple further down.
* The object-set diagnostic function starts about 0xA90 bytes after
  the function with the line 55 assertion for `TOWN.BIN+0x2ab88c/7`.
  It reports indices into the object-set table and its parallel pointer
  array, and a CD-header count.
* **`TOWN.BIN+0x2ab958/9` is linked last** and its one assertion is at line 64.
* **The decomp's overlay windows do not correspond to these files.** The town chunks each
  contain `lshop.o` + `main.o` + `player.o` + neighbours re-linked at slightly different
  addresses; the decomp's `town_deep_t8b_*` / `town_scene_*` windows are cut on file offsets,
  not on object boundaries. The eight functions above bracket the object boundaries: the
  `lshop.o`/`main.o` split lies between the end of `func_80471E70` and the start of
  `func_804721A4`, and the `main.o`/`player.o` split between `func_80472D04`'s end and
  `func_804732A4`'s start. That is a **ready-made TU boundary set** for this overlay.

### 4.2 The devkit blob (TOWN.BIN chunk `0x7FF01000`, pool `0x7FFB10`)

| true vram | nominal name | pins | object file |
|---|---|---|---|
| `0x80700BC4` | `func_8087FBC4` | `TOWN.BIN+0x7f7fd8/5`, `TOWN.BIN+0x7f7fe0/5`, `TOWN.BIN+0x7f7fe8/4` | probably `flgtst.o` |
| `0x80700EF0` | `func_8087FEF0` | **`TOWN.BIN+0x7ffb44/9:201`** (`mark`) | `flgtst.o` |
| `0x80701194` | `func_80880194` | **`TOWN.BIN+0x7f88e8/10:48`** (`mark`), `TOWN.BIN+0x7f88bc/8`, `TOWN.BIN+0x7f88c4/13` | `sn_main.o` |
| `0x80701298` | `func_80880298` | **`TOWN.BIN+0x7f891c/8:89`** | `tobjs.o` |

`TOWN.BIN+0x7f88e8/10` also appears with `mark` at **line 47** (chunk `0x7FF0A000`), and `TOWN.BIN+0x7f891c/8` with
asserts at **lines 75, 89, 225, 226** across the nine devkit chunks — so `TOWN.BIN+0x7f891c/8` is at least
226 lines long and has assertion clusters at both ends. `TOWN.BIN+0x7f88c4/13` is the overlay work-block
kind field; it and `TOWN.BIN+0x7f88bc/8` are printed from inside the very function that `mark`s
`TOWN.BIN+0x7f88e8/10:47/48`, which is the one *proven* expression-to-file attribution in the whole set.

### 4.3 MAIN.BIN — `MAIN.BIN+0x25d028/11` (Sony libcard), two revisions

The shipped module and the devkit module contain **different revisions of the same Sony file**.
Both have exactly 24 assertion sites in two functions (an `OpenEvent`/`EnableEvent` block and its
matching close), but the line numbers are shifted — by **5** through the open block and by
**10** through the close block, i.e. the shipped revision gained 5 lines above the open block and
another 5 between the two blocks:

| | shipped copy (`0x80020000`) | devkit copy (`0x80400000`) |
|---|---|---|
| open block | `func_80020A80` — lines 185, 187, **189**, **191**, 194, 196, 198, 200, 212, 214, 216, 218, 220, 222, 224, 226 | `func_80400A10` — lines 180, 182, 184, 186, **189**, **191**, 193, 195, 207, 209, 211, 213, 215, 217, 219, 221 |
| close block | `func_80020F18` — lines **263**, **265**, **267**, 269, 271, 273, 275, 277 | `func_80400EF8` — lines 253, 255, 257, 259, 261, **263**, **265**, **267** |

Both revisions assert on every other line — the classic `if (OpenEvent(...) == 0) assert(0);`
ladder, one assertion per event handle. The bold lines are the ones the two revisions happen to
share. The shipped list reproduces `port/docs/report_console.md` §5.2 exactly (0xB9=185 …
0xE2=226, 0x107=263 … 0x115=277), which independently confirms the decode.

## 5. Derived overlay load bases

Every base below was derived from the assertion sites themselves (§1.3), independently of any
table in the repo. `pool vram` is where that chunk's debug-string pool lands at runtime.
Bases `0xFF7Bxxxx` / `0xFF7Cxxxx` mean the object is **unrelocated** (the high address fields are zero), so
the "vram" is really a section-relative offset; `0x9FECxxxx` is a KSEG1 (`0xA07xxxxx`) link.

| container | string-pool foff | derived load base | pool vram | files | site copies | repo `true_name` agrees |
|---|---|---|---|---|---|---|
| MAIN.BIN | `0x25D000` | `0x7FDC3000` | `0x80020000` | MAIN.BIN+0x25d028/11 | 24 | yes (24 fns) |
| MAIN.BIN | `0x269004` | `0x80197000` | `0x80400004` | MAIN.BIN+0x25d028/11, MAIN.BIN+0x269570/11, MAIN.BIN+0x2695c8/11, MAIN.BIN+0x269620/11, MAIN.BIN+0x269654/9, MAIN.BIN+0x269760/11, MAIN.BIN+0x2697cc/11, MAIN.BIN+0x269800/10, MAIN.BIN+0x269894/9 | 42 | 13 fns yes; 3 fns (25 sites) carry a wrong `true_name` — §8.4 |
| TOWN.BIN | `0x26986C`\* | `0x80197000` | `0x8040086C` | MAIN.BIN+0x269894/9 | 2 | n/a |
| TOWN.BIN | `0x2AB834` | `0x7FD6A800` | `0x80016034` | TOWN.BIN+0x2ab85c/8, TOWN.BIN+0x2ab88c/7, TOWN.BIN+0x2ab958/9 | 13 | yes (13 fns) |
| TOWN.BIN | `0x3E816C` | `0x7FC31000` | `0x8001916C` | TOWN.BIN+0x2ab88c/7 | 8 | yes (3 fns) |
| TOWN.BIN | `0x3EF020` | `0x7FC27000` | `0x80016020` | TOWN.BIN+0x2ab85c/8, TOWN.BIN+0x2ab88c/7, TOWN.BIN+0x2ab958/9 | 13 | n/a |
| TOWN.BIN | `0x3F613C` | `0x7FC21000` | `0x8001713C` | TOWN.BIN+0x2ab88c/7 | 8 | n/a |
| TOWN.BIN | `0x3FA93C` | `0x7FC1C800` | `0x8001713C` | TOWN.BIN+0x2ab88c/7 | 8 | n/a |
| TOWN.BIN | `0x3FE024` | `0x7FC18000` | `0x80016024` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x400020` | `0x7FC16000` | `0x80016020` | TOWN.BIN+0x2ab85c/8, TOWN.BIN+0x2ab88c/7 | 12 | n/a |
| TOWN.BIN | `0x43781C` | `0x7FBDE800` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x45081C` | `0x7FBC5800` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x45801C` | `0x7FBBE000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x4700F4` | `0x7FBA6000` | `0x800160F4` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x48001C` | `0x7FB96000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x48E01C` | `0x7FB88000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x49E81C` | `0x7FB77800` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x4CF86C` | `0x7FB46800` | `0x8001606C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x4D901C` | `0x7FB3D000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x4F901C` | `0x7FB1D000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x51E020` | `0x7FAF8000` | `0x80016020` | TOWN.BIN+0x2ab85c/8, TOWN.BIN+0x2ab88c/7 | 9 | n/a |
| TOWN.BIN | `0x552028` | `0x7FAC4000` | `0x80016028` | TOWN.BIN+0x2ab88c/7, TOWN.BIN+0x2ab958/9 | 6 | n/a |
| TOWN.BIN | `0x581020` | `0x7FA95000` | `0x80016020` | TOWN.BIN+0x2ab85c/8, TOWN.BIN+0x2ab88c/7 | 9 | n/a |
| TOWN.BIN | `0x594820` | `0x7FA81800` | `0x80016020` | TOWN.BIN+0x2ab85c/8, TOWN.BIN+0x2ab88c/7 | 9 | n/a |
| TOWN.BIN | `0x5B201C` | `0x7FA64000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x5C701C` | `0x7FA4F000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x5DB824` | `0x7FA3A800` | `0x80016024` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x5FF020` | `0x7FA17000` | `0x80016020` | TOWN.BIN+0x2ab85c/8, TOWN.BIN+0x2ab88c/7 | 9 | n/a |
| TOWN.BIN | `0x617020` | `0x7F9FF000` | `0x80016020` | TOWN.BIN+0x2ab85c/8, TOWN.BIN+0x2ab88c/7 | 9 | n/a |
| TOWN.BIN | `0x62901C` | `0x7F9ED000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x645020` | `0x7F9D1000` | `0x80016020` | TOWN.BIN+0x2ab85c/8, TOWN.BIN+0x2ab88c/7 | 9 | n/a |
| TOWN.BIN | `0x64901C` | `0x7F9CD000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 2 | n/a |
| TOWN.BIN | `0x64B01C` | `0x7F9CB000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x64D01C` | `0x7F9C9000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x64F01C` | `0x7F9C7000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 8 | n/a |
| TOWN.BIN | `0x65101C` | `0x7F9C5000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x652948` | `0x7F9C3800` | `0x80016148` | TOWN.BIN+0x2ab88c/7 | 5 | yes (4 fns) |
| TOWN.BIN | `0x654038` | `0x7F9C2000` | `0x80016038` | TOWN.BIN+0x2ab88c/7, TOWN.BIN+0x2ab958/9 | 6 | n/a |
| TOWN.BIN | `0x65783C` | `0x7F9BE800` | `0x8001603C` | TOWN.BIN+0x2ab88c/7 | 8 | n/a |
| TOWN.BIN | `0x65B01C` | `0x7F9BB000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x67181C` | `0x7F9A4800` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x68DBE4` | `0x7F989000` | `0x80016BE4` | TOWN.BIN+0x2ab85c/8, TOWN.BIN+0x2ab88c/7 | 9 | n/a |
| TOWN.BIN | `0x6AA01C` | `0x7F96C000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x6CC81C` | `0x7F949800` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x6E181C` | `0x7F934800` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x6EFF5C` | `0x7F926800` | `0x8001675C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x6F481C` | `0x7F921800` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x6F701C` | `0x7F91F000` | `0x8001601C` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x6FDB58` | `0x7F918800` | `0x80016358` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x705138` | `0x7F911000` | `0x80016138` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x71A138` | `0x7F8FC000` | `0x80016138` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |
| TOWN.BIN | `0x7F7FCC` | `0x7FF0A000` | `0x80701FCC` | TOWN.BIN+0x7f88e8/10, TOWN.BIN+0x7f891c/8 | 7 | yes (3 fns) |
| TOWN.BIN | `0x7FFB10` | `0x7FF01000` | `0x80700B10` | TOWN.BIN+0x7ffb44/9, TOWN.BIN+0x7f88e8/10, TOWN.BIN+0x7f891c/8 | 8 | no — repo has only the synthetic base |
| TOWN.BIN | `0x800F44` | `0x7FEFF800` | `0x80700744` | TOWN.BIN+0x7f88e8/10, TOWN.BIN+0x7f891c/8 | 7 | n/a |
| TOWN.BIN | `0x802FB4` | `0x7FEFD800` | `0x807007B4` | TOWN.BIN+0x7f891c/8 | 4 | no — repo has only the synthetic base |
| TOWN.BIN | `0x832944` | `0x9FECD800` | `0xA0700144` | TOWN.BIN+0x7f88e8/10 | 3 | no — repo has only the synthetic base |
| TOWN.BIN | `0x837CB0` | `0xFF7CB800` | `0x000034B0` | TOWN.BIN+0x7f88e8/10, TOWN.BIN+0x7f891c/8 | 7 | n/a |
| TOWN.BIN | `0x839100` | `0x9FEC7000` | `0xA0700100` | TOWN.BIN+0x7ffb44/9, TOWN.BIN+0x7f88e8/10, TOWN.BIN+0x7f891c/8 | 8 | no — repo has only the synthetic base |
| TOWN.BIN | `0x83AE30` | `0xFF7C5800` | `0x00000630` | TOWN.BIN+0x7f88e8/10, TOWN.BIN+0x7f891c/8 | 7 | n/a |
| TOWN.BIN | `0x844710` | `0xFF7BC000` | `0x00000710` | TOWN.BIN+0x7f891c/8 | 4 | n/a |
| TOWN.BIN | `0x8CD084` | `0x7F749000` | `0x80016084` | TOWN.BIN+0x2ab88c/7 | 2 | n/a |
| TOWN.BIN | `0x8CE084` | `0x7F748000` | `0x80016084` | TOWN.BIN+0x2ab88c/7 | 8 | n/a |
| TOWN.BIN | `0x8CF080` | `0x7F747000` | `0x80016080` | TOWN.BIN+0x2ab88c/7 | 2 | n/a |
| TOWN.BIN | `0x8D0080` | `0x7F746000` | `0x80016080` | TOWN.BIN+0x2ab88c/7 | 5 | no — repo has only the synthetic base |
| TOWN.BIN | `0x8D1080` | `0x7F745000` | `0x80016080` | TOWN.BIN+0x2ab88c/7 | 8 | n/a |
| TOWN.BIN | `0x8D2144` | `0x7F744000` | `0x80016144` | TOWN.BIN+0x2ab88c/7 | 5 | n/a |

\* the TOWN.BIN row for pool `0x26986C` is MAIN.BIN's pool: TOWN.BIN carries a code-only copy
of that module, so its two sites are resolved against MAIN.BIN's identical string pool (§6).

## 6. MAIN.BIN — Sony's `MAIN.BIN+0x25d028/11` and Konami's card menu

MAIN.BIN carries **two** independent link images:

| file range | link base | evidence | reached at runtime |
|---|---|---|---|
| `0x25D000`–`0x269000` | `0x80020000` (`base = 0x7FDC3000`) | 327 of the region's `jal`s target `0x8002xxxx`; the port's boot loadmap records `0x80020000 +0xC000 <- MAIN.BIN+0x25D000` | **yes** |
| `0x269000`–`0x275800` | `0x80400000` (`base = 0x80197000`) | 348 `jal`s target `0x8040xxxx`, `lui 0x8040/0x8041` dominate, and `0x269000 + 0x80197000 = 0x80400000` exactly | no — `0x80400000` is outside retail's 2 MB |

The second image is a **devkit (8 MB DTL-H2000) build** of the memory-card front end: it links
its own copy of Sony's `MAIN.BIN+0x25d028/11` (an older revision, §4.3) plus Konami's eight card-menu
files. `overlays/main/overlay_first_pass_results.json` already knows this base
(`load_base: 0x80197000`, `base_confidence: derived`) but puts the boundary at file `0x26A0F0`;
the assertion sites prove it starts at file `0x269000` (see §8.4).

### 6.1 Per-file tables

#### `MAIN.BIN+0x25d028/11` — shipped copy (MAIN.BIN `0x25D000`, loads at `0x80020000`)

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 185 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 187 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 189 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 191 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 194 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 196 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 198 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 200 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 212 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 214 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 216 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 218 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 220 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 222 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 224 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 226 | assert | — | `func_8000DA80` | `0x80020A80` | MATCH | 1 |  |
| 263 | assert | — | `func_8000DF18` | `0x80020F18` | MATCH | 1 |  |
| 265 | assert | — | `func_8000DF18` | `0x80020F18` | MATCH | 1 |  |
| 267 | assert | — | `func_8000DF18` | `0x80020F18` | MATCH | 1 |  |
| 269 | assert | — | `func_8000DF18` | `0x80020F18` | MATCH | 1 |  |
| 271 | assert | — | `func_8000DF18` | `0x80020F18` | MATCH | 1 |  |
| 273 | assert | — | `func_8000DF18` | `0x80020F18` | MATCH | 1 |  |
| 275 | assert | — | `func_8000DF18` | `0x80020F18` | MATCH | 1 |  |
| 277 | assert | — | `func_8000DF18` | `0x80020F18` | MATCH | 1 |  |

#### `MAIN.BIN+0x25d028/11` — devkit copy (MAIN.BIN `0x269000`, linked at `0x80400000`)

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| — | expr | `MAIN.BIN+0x269044/15` | `func_80019E34` | `0x80400E34` | MATCH | 1 |  |
| — | expr | `MAIN.BIN+0x2690f8/4` | `func_8001AB30` | `0x80401B30` | MATCH | 2 |  |
| 180 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 182 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 184 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 186 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 189 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 191 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 193 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 195 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 207 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 209 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 211 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 213 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 215 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 217 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 219 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 221 | assert | — | `func_80019A10` | `0x80400A10` | MATCH | 1 |  |
| 253 | assert | — | `func_80019EF8` | `0x80400EF8` | MATCH | 1 |  |
| 255 | assert | — | `func_80019EF8` | `0x80400EF8` | MATCH | 1 |  |
| 257 | assert | — | `func_80019EF8` | `0x80400EF8` | MATCH | 1 |  |
| 259 | assert | — | `func_80019EF8` | `0x80400EF8` | MATCH | 1 |  |
| 261 | assert | — | `func_80019EF8` | `0x80400EF8` | MATCH | 1 |  |
| 263 | assert | — | `func_80019EF8` | `0x80400EF8` | MATCH | 1 |  |
| 265 | assert | — | `func_80019EF8` | `0x80400EF8` | MATCH | 1 |  |
| 267 | assert | — | `func_80019EF8` | `0x80400EF8` | MATCH | 1 |  |

#### `MAIN.BIN+0x269570/11`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 665 | assert | — | `func_8001BF84` | `0x80402F84` | MATCH | 1 |  |

#### `MAIN.BIN+0x2695c8/11`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 337 | assert | — | `func_8001CBC4` | `0x80403BC4` | MATCH | 1 |  |

#### `MAIN.BIN+0x269620/11`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 299 | assert | — | `func_8001D364` | `0x80404364` | MATCH | 1 |  |
| 300 | assert | — | `func_8001D364` | `0x80404364` | MATCH | 1 |  |
| 303 | assert | — | `func_8001D364` | `0x80404364` | MATCH | 1 |  |

#### `MAIN.BIN+0x269654/9`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 378 | assert | — | `func_8001DC84` | `0x80404C84` | MATCH | 1 |  |

#### `MAIN.BIN+0x269760/11`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 416 | assert | — | `func_8001E7F0` | `0x804057F0` | MATCH | 1 |  |

#### `MAIN.BIN+0x2697cc/11`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 310 | assert | — | `func_800206C8` | `0x804076C8` | MATCH | 1 |  |
| 331 | assert | — | `func_800207D4` | `0x804077D4` | MATCH | 1 |  |
| 339 | assert | — | `func_80020830` | `0x80407830` | MATCH | 1 |  |

#### `MAIN.BIN+0x269800/10`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 238 | assert | — | `func_80020C10` | `0x80407C10` | MATCH | 1 |  |

#### `MAIN.BIN+0x269894/9`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 371 | assert | — | `func_800213FC` | `0x804083FC` | MATCH (as dedup rep) | 2 |  |
| 387 | assert | — | `func_800214DC` | `0x804084DC` | MATCH (as dedup rep) | 2 |  |


`MAIN.BIN+0x269894/9`'s two assertions also exist as a **code-only copy in TOWN.BIN** at file `0x2713FC` /
`0x2714DC` — byte-identical to MAIN.BIN's, hence the same `0x80400000` link — but TOWN.BIN does
not carry that image's `.rdata`, so those two rows' base is carried over from MAIN.BIN and is
flagged `cross-container (rdata absent from TOWN.BIN)` in the CSV.

## 7. The devkit blob in TOWN.BIN

TOWN.BIN file `0x7F7F00`–`0x845000` (at least; the pools run from `0x7F7FCC` to `0x844730`) holds several link images of the town facility
scenario scripts (NPC dialogue and event scripts with native scene-setup code). Correction (2026-10-16): an earlier version of this section called the
whole range "not shipped game code" and the images a scene-authoring / test tool. The investigation in `work/native_lane/_r120/vram0/SCENES.md`
(with `work/native_lane/_r120/vram0/REPORT.md`) shows:

- The 25 images linked at `0x80700000` are the records of the scene table at TOWN `0x564A0` (25 records of 8 bytes, read by Control_CD case 6
  in `func_8003E758`). Correction to the earlier wording: static evidence says they are not loaded in retail. They are writing-room draft
  scripts (theater, archaeologist professor / library facility, clinic doctor / hospital facility) and are reached only through `S_flgtst`
  (call-table index 22, `src/town/func_800C374C.c`, table slot at TOWN `0x565C0`), which no shipped US or JP script calls: `NATIVE_IDX 22` occurs
  6 times in the drafts and 0 times in all 54 shipped modules, and nothing else references `flgtst`. The only code that reads the matching LBAs
  (a SLUS load-descriptor array at `0x800812B0..F8`) goes through `func_80053CA4`/`func_80053CD0`, which have no callers. Open: a runtime check
  (CD-read breakpoint on LBAs 7139..7413 during the theater, library and clinic scenes). Evidence: `work/native_lane/_r120/leftovers/REPORT.md`
  section Q3 and `work/native_lane/_r120/vram0/SCENES.md`.
- The zero-base images (link address 0, listed below as unrelocated) are older alternate builds of those same scenario scripts. Their text is a strict
  subset of the scene-table records and they call service slots `+0x64`/`+0x70` where retail uses `+0x68`/`+0x74`. No scene-table record, LBA or loader
  path reaches them. Each of the 25 scene-table records has such a base-0 twin (the link-at-0 images); both sets are admitted as code in the repository
  under decision 52 of `docs/evidence/r97_decisions.md`, as static evidence of the build, not of what the retail game loads.
- The pool table below is unchanged; only the "test tool" description and the "not shipped" claim are corrected.

Link images in this range:

| pool foff | base | link address | note |
|---|---|---|---|
| `0x7F7FCC` | `0x7FF0A000` | `0x80700000` | + the development scene path table at `0x7F877C`–`0x7F8894` |
| `0x7FFB10` | `0x7FF01000` | `0x80700000` | the most complete image: `TOWN.BIN+0x7ffb44/9`, `TOWN.BIN+0x7f88e8/10`, `TOWN.BIN+0x7f891c/8` |
| `0x800F44` | `0x7FEFF800` | `0x80700000` | |
| `0x802FB4` | `0x7FEFD800` | `0x80700000` | `TOWN.BIN+0x7f891c/8` only |
| `0x832944` | `0x9FECD800` | `0xA0700000` | KSEG1 (uncached) link |
| `0x837CB0` | `0xFF7CB800` | *unrelocated* | raw object with unresolved addresses |
| `0x839100` | `0x9FEC7000` | `0xA0700000` | KSEG1 |
| `0x83AE30` | `0xFF7C5800` | *unrelocated* | |
| `0x844710` | `0xFF7BC000` | *unrelocated* | |

The development assertion checks a flag, calls the diagnostic service
at slot `0x64` and exits through slot `0x70` with status one. This
image also has a source-trace format confined to the development code.

A **second, separate** code island sits at TOWN.BIN `0x268000`–`0x278000` (~22 functions,
references into the development image, with diagnostic and exit calls to `0x8007C040` and `0x8007BEF0`).
Two of its sites are the `MAIN.BIN+0x269894/9` rows of §6.1; the rest of its `.rdata` is not in the
container.

### 7.1 Other developer strings, with locations

The offsets locate the text in the original disc containers.

| Description | Container | File offsets |
|---|---|---|
| Development asset paths | TOWN | `0x65281C`, `0x65283C` |
| Scene data paths | TOWN | `0x7F877C-0x7F8894` |
| Town map data path | TOWN | `0x8CD128`, `0x8CE128`, `0x8CF124`, `0x8D0124`, `0x8D1124`, `0x8D21E8` |
| Scene movie data path | TOWN | `0x8D20FC` |
| End-of-game display message | TOWN | `0x78BA94`, `0x796030`, `0x796070`, `0x7960B4` |
| Shipped save identifier | MAIN | `0x264F20` |
| Development save identifier | MAIN | `0x271AA8` |
| Development card diagnostics | MAIN | `0x269090`, `0x2690BC`, `0x2690D0`, `0x269138` |
| Card device paths | MAIN | `0x25D074`, `0x25D07C`, `0x2690E4`, `0x2690EC` |
| Library build identifiers | SLUS | `0x6AC8`, `0x6D78`, `0x6EFC` |

## 8. Corrections to `port/docs/report_console.md` §5

1. **§5.2 — the "second module at `0x8002C000`" is really at `0x80400000`.** Its addresses in
   that report are all `0x3D4000` too low: `0x8002C004` → `0x80400004`, `0x8002C02C` →
   `0x8040002C`, `0x8002C038` → `0x80400038`, `0x8002C044` → `0x80400044`, `0x8002C090` →
   `0x80400090`, `0x8002C114` → `0x80400114`, `0x8002C120` → `0x80400120`, `0x8002C138` →
   `0x80400138`, `0x8002C548`… → `0x80400548`…, `0x8002C80C` → `0x8040080C`, and
   `0x80034AA8` → `0x80408AA8`. The module is a devkit-only image (§6); the
   report's own observation that "this second module's load was not observed" is consistent.
   `0x80027F20` is in the shipped image and is correct as printed.
2. **§5.3 — the TOWN.BIN copy counts mix two different macros.** The 76 assertion format
   copies break down as `TOWN.BIN+0x2ab88c/7` 54, `TOWN.BIN+0x2ab85c/8` 10, `TOWN.BIN+0x7f891c/8` 8, `TOWN.BIN+0x2ab958/9` 4 — `TOWN.BIN+0x7f88e8/10` (7)
   and `TOWN.BIN+0x7ffb44/9` (2) are **not** assertion file names; they belong to a third macro,
   the source trace (9 copies, devkit blob only). The report also lists `TOWN.BIN+0x2ab918/6`/`TOWN.BIN+0x2ab920/6`/`TOWN.BIN+0x2ab928/5`
   under `TOWN.BIN+0x2ab85c/8`; the `.rdata` block layout does not support that (§3.3).
3. **§5.3 — "every one of these 76 assertion sites is in a function that has not been
   decompiled yet" is no longer true.** Of the 458 located site copies, 426 sit in a function the
   first-pass sweep byte-matched (99 as the cluster representative, 327 as a retired duplicate);
   32 were classified as not covered by that sweep record. The r121 boundary correction in §1.4
   moves five of those physical sites onto existing MATCH rows (current CSV: 431 MATCH/dup:MATCH,
   27 not-in-sweep). The reason `rg '\bprintf\s*\('` finds
   nothing in `overlays/town/first_pass_matched` is that the overlays never call `printf`
   directly — they call it through a service-table `jalr` (§1.2), which m2c renders as an
   indirect call through a struct field.
4. `overlays/main/overlay_first_pass_results.json` places the `0x80197000` module boundary at
   file `0x26A0F0`; the assertion sites show it starts at `0x269000`. Three functions —
   `0x269A10`, `0x269E34`, `0x269EF8` — are therefore labelled with the wrong `true_name`
   (`func_8002CA10` / `func_8002CE34` / `func_8002CEF8`); they should be `func_80400A10` /
   `func_80400E34` / `func_80400EF8`. Their code references `0x80400004`/`0x8040002C`
   (the assert format string and `"MAIN.BIN+0x25d028/11"`), which is only reachable under the
   `0x80197000` base.

## 9. Using this when re-shaping the C

* **Treat each row of §4 as a hard constraint, not a hint.** `func_804721A4` is the function
  that contains `TOWN.BIN+0x2ab88c/7:40` — full stop. Any file-splitting plan that puts it somewhere other
  than `TOWN.BIN+0x2ab88c/7`, or that puts it in the same TU as `func_80471AC4` (which contains
  `TOWN.BIN+0x2ab85c/8:65`), is provably wrong.
* **Use the assertion lines to order functions inside a file.** Within one object file the
  compiler emits functions in source order, so `TOWN.BIN+0x2ab85c/8`'s three functions are in the order
  65 → 113/118 → 128, and a fourth `TOWN.BIN+0x2ab85c/8` function found later in the same chunk is at a
  line > 128.
* **Use them to size the gaps.** `TOWN.BIN+0x2ab88c/7:40` and `TOWN.BIN+0x2ab88c/7:55` are 15 source lines and 0xD4 bytes
  apart — that is a whole small function. The object-set diagnostic function is ~0xA90 bytes past `TOWN.BIN+0x2ab88c/7:55`,
  so several hundred lines of `TOWN.BIN+0x2ab88c/7` sit in between, across several functions.
* **Source file names and argument order.** The source locations in §0
  identify the names recorded by the original translation units. The
  overlay assertion passes the diagnostic format, source name and line
  to the service table and then exits with status one. See §1 for the
  format locations and service slots.
* **Cross-check overlay bases.** §5 gives 66 independently derived load bases. The repo can
  corroborate only a handful of them (§1.3); for the other ~60 town chunks it currently carries
  just the synthetic `file + 0x80080000` naming label. They are directly usable to raise
  `base_confidence` in `config/overlays/town_*.overlay.yaml`, and the pool vram column doubles
  as a check: every town game chunk maps its debug pool into `0x8001xxxx`, the free RAM window
  below the resident EXE at `0x8002D000`.

## 10. Unresolved

* The object file behind `TOWN.BIN+0x3e817c/5` / `TOWN.BIN+0x3e8184/10` / `TOWN.BIN+0x3e8190/10`, behind `TOWN.BIN+0x2ab918/6` / `TOWN.BIN+0x2ab920/6` / `TOWN.BIN+0x2ab928/5`,
  and (less certainly) behind `TOWN.BIN+0x7f7fd8/5` / `TOWN.BIN+0x7f7fe0/5` / `TOWN.BIN+0x7f7fe8/4` — see §3.3.
* Whether `TOWN.BIN+0x2ab88c/7` here is from a town-overlay source file or a global game source file. The
  assertions at lines 39/40 and 54/55 are near the top of a file whose object is linked into
  every town overlay, which fits a source local to each scene directory.
* The exact extent of the TOWN.BIN `0x268000`–`0x278000` code island (§7). Its `.rdata` is not
  in the container, so only the two `MAIN.BIN+0x269894/9` sites there could be resolved, and only by
  borrowing MAIN.BIN's identical string pool.
* Whether the three unrelocated `.obj` images in the devkit blob (`0x837CB0`, `0x83AE30`,
  `0x844710`) are complete objects or fragments. Their `lui` fields are zero, so their site
  "vram" values in the CSV are section-relative offsets, not addresses.
* One decimal expression format at TOWN.BIN `0x832944` (devkit blob) has no call site at all in the
  container.
