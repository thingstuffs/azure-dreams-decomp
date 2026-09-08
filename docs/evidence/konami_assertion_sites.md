# Konami / Sony assertion sites left on the Azure Dreams disc

*Static catalogue, drafted 2026-08-27. Companion data: `docs/konami_assertion_sites.csv`
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
| `c_server.c` (Sony libcard) | 43 | 51 | MAIN.BIN, two different revisions |
| `main.c` | 7 | 270 | TOWN.BIN game overlays |
| `lshop.c` | 4 | 40 | TOWN.BIN game overlays |
| `sn_main.c` | 4 | 21 | TOWN.BIN devkit blob |
| `tobjs.c` | 4 | 8 | TOWN.BIN devkit blob |
| `card_win.c` | 3 | 3 | MAIN.BIN devkit module |
| `cardslot.c` | 3 | 3 | MAIN.BIN devkit module |
| `memory.c` | 2 | 4 | MAIN.BIN devkit module (+ a code-only copy in TOWN.BIN) |
| `card_mes.c`, `card_opt.c`, `cardbk.c`, `cardinfo.c`, `cardsme.c` | 1 each | 1 each | MAIN.BIN devkit module |
| `player.c` | 1 | 4 | TOWN.BIN game overlays |
| `flgtst.c` | 1 | 2 | TOWN.BIN devkit blob |
| *(expressions with no file attribution)* | 10 | 47 | see §3.3 |

### 0.1 CSV column key

`docs/konami_assertion_sites.csv`, one row per **site copy** (458 rows):

| column | meaning |
|---|---|
| `container` | `TOWN.BIN` / `MAIN.BIN` |
| `chunk_pool_foff` | file offset of the format string this site points at (identifies the chunk's `.rdata` pool) |
| `site_foff` / `site_vram` | file offset and runtime address of the `jal`/`jalr` |
| `derived_base` | `site_vram − site_foff` for this chunk, derived per §1.3 |
| `source_file` | `__FILE__` for `assert`/`mark`; the inferred owner for `expr` (blank when unattributed) |
| `line` | `__LINE__`, exact; blank for `expr` |
| `kind` | `assert` / `mark` / `expr` |
| `expression_or_null` | the printed expression's source text (`expr` rows only) |
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

| kind | format string | `$a0` | `$a1` | `$a2` | `$a1 − $a0` |
|---|---|---|---|---|---|
| `assert` | `Assertion failed: file "%s", line %d\n` | format | `__FILE__` | `__LINE__` | `0x28` |
| `mark` | `mark: %s line %d\n` | format | `__FILE__` | `__LINE__` | `0x14` |
| `expr` | `%s = %d\n` / `%s = %x\n` | format | the expression's **source text** | its runtime value | varies |

The fixed `$a1 − $a0` delta for `assert`/`mark` falls out of the layout the compiler emits:
the format string is 38 (resp. 19) bytes, padded to 4, and the `__FILE__` literal is placed
immediately after it in the same `.rdata` block.

### 1.2 Finding the call, not the string

The resident `printf` is the BIOS `A(3Fh)` thunk at **`0x80069F18`** (`li $t2,0xA0; jr $t2;
li $t1,0x3F`; `config/slus_006.14.symbols.txt` names it, and the disassembly confirms it —
it is the only such thunk in the whole image). Scanning for `jal 0x80069F18` finds the 24
PSY-Q library sites inside SLUS and the 24 sites of MAIN.BIN's shipped libcard module — and
**zero in TOWN.BIN**. All 66 MAIN.BIN sites are direct `jal`s: the 24 shipped ones to
`0x80069F18`, the 42 devkit ones to that image's own `printf` at `0x8007C040`.

390 of TOWN.BIN's 392 sites are `jalr` — the town overlays reach `printf` **indirectly**,
through a resident service table (the two exceptions are the code-only copy of the MAIN.BIN
devkit module, §6):

```
lw    $v0, 0x20($a1)       ; overlay work block -> resident service vtable
lw    $v0, 0x168($v0)      ; slot 0x168 = printf
lui   $a0, %hi(fmt)
addiu $a0, $a0, %lo(fmt)
lui   $a1, %hi(file)
addiu $a1, $a1, %lo(file)
jalr  $v0
li    $a2, 65              ; __LINE__            (delay slot)
...                        ; then slot 0x174 = exit, called with $a0 = 1
```

so the scan is over **every `jal` and `jalr`** in each container, with a small MIPS interpreter
walking back up to 48 instructions (resetting at `jr`, clobbering caller-saved registers at each
intervening call, and executing the delay slot) to recover constant `$a0`/`$a1`/`$a2`. In the
devkit blob the vtable slots are `0x64` (printf) and `0x70` (exit) instead.

### 1.3 Self-calibrating the load base

Overlay chunks load at many different addresses, so no table is trusted. For every candidate
site the base is *derived*: `base = $a0 − foff(format string)`, tested against three filters —

1. `base % 0x800 == 0` (chunks are sector-aligned and load addresses are 0x800-aligned),
2. the string at `$a1 − base` must be a printable C identifier / filename ending in `.c`,
3. the format-string copy must be within 0x200000 of the site (same chunk).

Each format-string copy then takes the majority base of the sites that point at it, and every
other debug string in the same pool inherits it. **66 distinct chunk bases** come out. They are
listed in §5. 99 of the located sites sit in a function for which the repo already records a
`true_name`; the derived base reproduces it on **62** of them, and of the 37 that differ, **25**
are the MAIN.BIN module-boundary error documented in §8 and **12** are TOWN devkit-blob sites
where the repo's `true_name` is only the synthetic `file + 0x80080000` label (i.e. no proven base
existed there and this document supplies one). For the remaining ~54 town chunks the repo has no
proven base at all.

### 1.4 Containing function and dedup

The containing function is bounded by the previous `jr $ra` + delay slot, refined to the last
`addiu $sp,$sp,-N` at or before the site (which stops the search walking into an `.rdata` pool).
Where the sweep in `overlays/*/overlay_first_pass_results.json` has a record at that exact file
offset the sizes agree on **99 of 99** checks.

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
* **Copy counts are of shipped code, not of source.** 54 copies of `main.c:40` are 54 re-links
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

DUNGEON.BIN (27.8 MB) and OVMOVIE.BIN (3.1 MB) contain **zero** `Assertion failed`, zero
`%s = %`, zero `mark:` and zero `<name>.c` strings. Either those modules were built with
assertions disabled or their debug build never shipped.

The resident `SLUS_006.14` has 24 `jal printf` sites, all inside PSY-Q libraries
(`SPU:T/O`, libapi `intr.c`, libcd, libgte's matrix-stack errors, libgpu's `GPU timeout`) —
no Konami assertion, no `.c` file name. They are already catalogued in
`port/docs/report_console.md` §5.1. The three RCS `$Id$` stamps that date those libraries are
at SLUS file `0x6AC8` / `0x6D78` / `0x6EFC` (`intr.c,v 1.76`, `bios.c,v 1.86`, `sys.c,v 1.129`);
there is no `$Id$` anywhere in the four containers.

## 3. Distinct sites, by source file

`copies` = how many linked copies of that one source assertion exist on the disc.
`decomp status` is the state of the containing function in the first-pass sweep;
"MATCH (as dedup rep)" means this copy was retired into a cluster whose representative
byte-matched.

### 3.1 TOWN.BIN — Konami's town/shop code

#### `main.c` — 7 distinct sites, 270 copies

Canonical chunk: TOWN.BIN pool/base `0x7FC27000`.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| — | expr | `((u_long)p - (u_long)ost_w)/ sizeof(OSETDT)` | `func_80472D04` | `0x80019D04` | MATCH (as dedup rep) | 54 |  |
| — | expr | `((u_long)pp - (u_long)osel_w)/ sizeof(OSETDT*)` | `func_80472D04` | `0x80019D04` | MATCH (as dedup rep) | 54 |  |
| — | expr | `cdhd_cnt` | `func_80472D04` | `0x80019D04` | MATCH (as dedup rep) | 54 |  |
| 39 | assert | — | `func_806D29EC` | `0x800161EC` | MATCH (as dedup rep) | 7 | chunk 0x7F9C3800 |
| 40 | assert | — | `func_804721A4` | `0x800191A4` | MATCH (as dedup rep) | 47 |  |
| 54 | assert | — | `func_806D2AB0` | `0x800162B0` | MATCH | 7 | chunk 0x7F9C3800 |
| 55 | assert | — | `func_80472278` | `0x80019278` | MATCH (as dedup rep) | 47 |  |

#### `lshop.c` — 4 distinct sites, 40 copies

Canonical chunk: TOWN.BIN pool/base `0x7FC27000`.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 65 | assert | — | `func_80471AC4` | `0x80018AC4` | MATCH (as dedup rep) | 10 |  |
| 113 | assert | — | `func_80471CD0` | `0x80018CD0` | MATCH (as dedup rep) | 10 |  |
| 118 | assert | — | `func_80471CD0` | `0x80018CD0` | MATCH (as dedup rep) | 10 |  |
| 128 | assert | — | `func_80471E70` | `0x80018E70` | MATCH (as dedup rep) | 10 |  |

#### `player.c` — 1 distinct site, 4 copies

Canonical chunk: TOWN.BIN pool/base `0x7FC27000`.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 64 | assert | — | `func_804732A4` | `0x8001A2A4` | MATCH (as dedup rep) | 4 |  |

#### `tobjs.c` — 4 distinct sites, 8 copies

Canonical chunk: TOWN.BIN pool/base `0x7FF01000`.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 75 | assert | — | `func_808816E0` | `0x80700EE0` | not-in-sweep | 4 | chunk 0x7FEFF800 |
| 89 | assert | — | `func_808802A0` | `0x807012A0` | not-in-sweep | 2 |  |
| 225 | assert | — | `func_808B85F8` | `0x00003DF8` | not-in-sweep | 1 | chunk 0xFF7CB800 |
| 226 | assert | — | `func_80878A80` | `0x80702A80` | not-in-sweep | 1 | chunk 0x7FF0A000 |

#### `sn_main.c` — 4 distinct sites, 21 copies

Canonical chunk: TOWN.BIN pool/base `0x7FF01000`.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| — | expr | `ov_work.kind` | `func_80880194` | `0x80701194` | not-in-sweep | 7 |  |
| — | expr | `p->kind` | `func_80880194` | `0x80701194` | not-in-sweep | 7 |  |
| 47 | mark | — | `func_80878974` | `0x80702974` | MATCH | 2 | chunk 0x7FF0A000 |
| 48 | mark | — | `func_80880194` | `0x80701194` | not-in-sweep | 5 |  |

#### `flgtst.c` — 1 distinct site, 2 copies

Canonical chunk: TOWN.BIN pool/base `0x7FF01000`.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 201 | mark | — | `func_8087FEF0` | `0x80700EF0` | MATCH | 2 |  |

### 3.2 MAIN.BIN — Sony's libcard and Konami's card menu

See §6 for the two-image split and §4.3 for the two `c_server.c` revisions.

### 3.3 Expressions with no file attribution

These are `%s = %d\n` / `%s = %x\n` blocks whose `.rdata` block is not immediately preceded by a
`[assert fmt][__FILE__]` pair, so the object file that owns them cannot be named from the
bytes alone. They are still exact source text, and their containing functions are pinned.

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| — | expr | `(int)gsw->check_sum` | `func_8001AF98` | `0x80401F98` | MATCH | 2 | chunk 0x80197000 |
| — | expr | `head` | `func_80471544` | `0x80018544` | not-in-sweep | 6 |  |
| — | expr | `kind` | `func_80877FEC` | `0x80701FEC` | MATCH | 8 | chunk 0x7FF0A000 |
| — | expr | `mode` | `func_80877FEC` | `0x80701FEC` | MATCH | 8 | chunk 0x7FF0A000 |
| — | expr | `ptr[n].vx` | `func_80471544` | `0x80018544` | not-in-sweep | 6 |  |
| — | expr | `ptr[n].vy` | `func_80471544` | `0x80018544` | not-in-sweep | 6 |  |
| — | expr | `s0[0]` | `func_803301B8` | `0x8001A9B8` | MATCH | 1 | chunk 0x7FD6A800 |
| — | expr | `s1[0]` | `func_803301B8` | `0x8001A9B8` | MATCH | 1 | chunk 0x7FD6A800 |
| — | expr | `s[0]` | `func_803301B8` | `0x8001A9B8` | MATCH | 1 | chunk 0x7FD6A800 |
| — | expr | `sno` | `func_80877FEC` | `0x80701FEC` | MATCH | 8 | chunk 0x7FF0A000 |

Each block's `.rdata` neighbours are recorded in the CSV `notes` column
(`pool-neighbours before:… after:…`). What can be said about each:

* `head` / `ptr[n].vx` / `ptr[n].vy` — the block sits immediately **before** `lshop.c`'s
  `[assert fmt][lshop.c]` pair and its function sits immediately before `lshop.c`'s functions.
  It is **not** `lshop.c` itself: the TOWN.BIN `0x7FD6A800` chunk links `lshop.c` (same
  assert lines 65/113/118/128) with no `head`/`ptr[n]` strings at all, which an identical
  object file could not do. ⇒ a separate, unnamed object that precedes `lshop.o` in 6 overlays.
* `s0[0]` / `s1[0]` / `s[0]` — one copy only (TOWN.BIN `0x7FD6A800`, function
  `func_803301B8` @ `0x8001A9B8`). Sits between `main.o`'s expression function and
  `player.o`'s. `port/docs/report_console.md` §5.3 lists them under `lshop.c`; that was a
  proximity guess and the block layout does not support it.
* `kind` / `mode` / `sno` — devkit blob. In the TOWN.BIN `0x7FF01000` chunk this block is
  `[%s = %d\n][kind][mode][sno][mark fmt][flgtst.c]` and the containing function sits
  immediately before `flgtst.c:201`'s. ⇒ **probably `flgtst.c`** (inferred, not proven; two of
  the nine devkit chunks carry the block without any `flgtst.c` string).
* `(int)gsw->check_sum` — `%s = %x\n`, MAIN.BIN devkit module, `func_80401F98`. `gsw` is a
  Konami save-work struct, so this is not `c_server.c` despite sitting in its pool tail.

## 4. The implied source map

This is the payoff: each row below is a **function whose C body provably spans the given source
lines**. Function order within a chunk follows object-file link order, and within an object file
it follows source order, so the assertions also fix the *relative* position of the objects.

### 4.1 A town scene overlay, front to back (TOWN.BIN chunk `0x7FC27000`, pool `0x3EF020`)

| true vram | nominal name | pins | object file |
|---|---|---|---|
| `0x80018544` | `func_80471544` | `head`, `ptr[n].vx`, `ptr[n].vy` | unnamed (§3.3) |
| `0x80018AC4` | `func_80471AC4` | **`lshop.c:65`** | `lshop.o` |
| `0x80018CD0` | `func_80471CD0` | **`lshop.c:113`, `lshop.c:118`** | `lshop.o` |
| `0x80018E70` | `func_80471E70` | **`lshop.c:128`** | `lshop.o` |
| `0x800191A4` | `func_804721A4` | **`main.c:40`** | `main.o` |
| `0x80019278` | `func_80472278` | **`main.c:55`** | `main.o` |
| `0x80019D04` | `func_80472D04` | `ost_w` / `osel_w` / `cdhd_cnt` expressions | `main.o` |
| `0x8001A2A4` | `func_804732A4` | **`player.c:64`** | `player.o` |

The same shape, with the same line numbers, repeats across the other 53 town chunks, though
most carry only the `main.o` subset — see the `files` column of §5. Chunk `0x7FD6A800`
(pool `0x2AB834`) is the other full one; it additionally carries the `s0[0]`/`s1[0]`/`s[0]`
function between `main.o`'s expression function and `player.o`'s.

What this says about the sources:

* **`lshop.c` is a small file.** All four of its assertions land in lines 65–128, in three
  consecutive functions, and it is linked ahead of `main.o` and `player.o` in every town
  overlay that carries it. A function containing line 65 sits roughly 50 lines in, i.e.
  `lshop.c` opens with one or two functions before it.
* **`main.c`'s first two assertions are at lines 39/40 and 54/55** — the very top of the file,
  and the two functions are adjacent (`0x191A4` → `0x19278`, 0xD4 bytes apart). Note the
  **two revisions**: 47 chunks carry lines **40 / 55**, 7 chunks carry **39 / 54** — one line
  was inserted (or removed) above them between two builds. Everything else about the two
  revisions matches, including the expression triple further down.
* **`main.c`'s object-set code is much further down.** The `((u_long)p - (u_long)ost_w)/
  sizeof(OSETDT)` / `osel_w` / `cdhd_cnt` triple is in a single function ~0xA90 bytes past
  `main.c:55`'s, i.e. several hundred source lines later. `OSETDT`, `ost_w`, `osel_w` is an
  object-set table with a parallel pointer array; `cdhd_cnt` is a CD-header counter.
* **`player.c` is linked last** and its one assertion is at line 64.
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
| `0x80700BC4` | `func_8087FBC4` | `kind`, `mode`, `sno` | probably `flgtst.o` |
| `0x80700EF0` | `func_8087FEF0` | **`flgtst.c:201`** (`mark`) | `flgtst.o` |
| `0x80701194` | `func_80880194` | **`sn_main.c:48`** (`mark`), `p->kind`, `ov_work.kind` | `sn_main.o` |
| `0x807012A0` | `func_808802A0` | **`tobjs.c:89`** | `tobjs.o` |

`sn_main.c` also appears with `mark` at **line 47** (chunk `0x7FF0A000`), and `tobjs.c` with
asserts at **lines 75, 89, 225, 226** across the nine devkit chunks — so `tobjs.c` is at least
226 lines long and has assertion clusters at both ends. `ov_work.kind` is the overlay work-block
kind field; it and `p->kind` are printed from inside the very function that `mark`s
`sn_main.c:47/48`, which is the one *proven* expression-to-file attribution in the whole set.

### 4.3 MAIN.BIN — `c_server.c` (Sony libcard), two revisions

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
Bases `0xFF7Bxxxx` / `0xFF7Cxxxx` mean the object is **unrelocated** (its `lui` fields are still `0x0000`), so
the "vram" is really a section-relative offset; `0x9FECxxxx` is a KSEG1 (`0xA07xxxxx`) link.

| container | string-pool foff | derived load base | pool vram | files | site copies | repo `true_name` agrees |
|---|---|---|---|---|---|---|
| MAIN.BIN | `0x25D000` | `0x7FDC3000` | `0x80020000` | c_server.c | 24 | yes (24 fns) |
| MAIN.BIN | `0x269004` | `0x80197000` | `0x80400004` | c_server.c, card_mes.c, card_opt.c, card_win.c, cardbk.c, cardinfo.c, cardslot.c, cardsme.c, memory.c | 42 | 13 fns yes; 3 fns (25 sites) carry a wrong `true_name` — §8.4 |
| TOWN.BIN | `0x26986C`\* | `0x80197000` | `0x8040086C` | memory.c | 2 | n/a |
| TOWN.BIN | `0x2AB834` | `0x7FD6A800` | `0x80016034` | lshop.c, main.c, player.c | 13 | yes (13 fns) |
| TOWN.BIN | `0x3E816C` | `0x7FC31000` | `0x8001916C` | main.c | 8 | yes (3 fns) |
| TOWN.BIN | `0x3EF020` | `0x7FC27000` | `0x80016020` | lshop.c, main.c, player.c | 13 | n/a |
| TOWN.BIN | `0x3F613C` | `0x7FC21000` | `0x8001713C` | main.c | 8 | n/a |
| TOWN.BIN | `0x3FA93C` | `0x7FC1C800` | `0x8001713C` | main.c | 8 | n/a |
| TOWN.BIN | `0x3FE024` | `0x7FC18000` | `0x80016024` | main.c | 5 | n/a |
| TOWN.BIN | `0x400020` | `0x7FC16000` | `0x80016020` | lshop.c, main.c | 12 | n/a |
| TOWN.BIN | `0x43781C` | `0x7FBDE800` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x45081C` | `0x7FBC5800` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x45801C` | `0x7FBBE000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x4700F4` | `0x7FBA6000` | `0x800160F4` | main.c | 5 | n/a |
| TOWN.BIN | `0x48001C` | `0x7FB96000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x48E01C` | `0x7FB88000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x49E81C` | `0x7FB77800` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x4CF86C` | `0x7FB46800` | `0x8001606C` | main.c | 5 | n/a |
| TOWN.BIN | `0x4D901C` | `0x7FB3D000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x4F901C` | `0x7FB1D000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x51E020` | `0x7FAF8000` | `0x80016020` | lshop.c, main.c | 9 | n/a |
| TOWN.BIN | `0x552028` | `0x7FAC4000` | `0x80016028` | main.c, player.c | 6 | n/a |
| TOWN.BIN | `0x581020` | `0x7FA95000` | `0x80016020` | lshop.c, main.c | 9 | n/a |
| TOWN.BIN | `0x594820` | `0x7FA81800` | `0x80016020` | lshop.c, main.c | 9 | n/a |
| TOWN.BIN | `0x5B201C` | `0x7FA64000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x5C701C` | `0x7FA4F000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x5DB824` | `0x7FA3A800` | `0x80016024` | main.c | 5 | n/a |
| TOWN.BIN | `0x5FF020` | `0x7FA17000` | `0x80016020` | lshop.c, main.c | 9 | n/a |
| TOWN.BIN | `0x617020` | `0x7F9FF000` | `0x80016020` | lshop.c, main.c | 9 | n/a |
| TOWN.BIN | `0x62901C` | `0x7F9ED000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x645020` | `0x7F9D1000` | `0x80016020` | lshop.c, main.c | 9 | n/a |
| TOWN.BIN | `0x64901C` | `0x7F9CD000` | `0x8001601C` | main.c | 2 | n/a |
| TOWN.BIN | `0x64B01C` | `0x7F9CB000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x64D01C` | `0x7F9C9000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x64F01C` | `0x7F9C7000` | `0x8001601C` | main.c | 8 | n/a |
| TOWN.BIN | `0x65101C` | `0x7F9C5000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x652948` | `0x7F9C3800` | `0x80016148` | main.c | 5 | yes (4 fns) |
| TOWN.BIN | `0x654038` | `0x7F9C2000` | `0x80016038` | main.c, player.c | 6 | n/a |
| TOWN.BIN | `0x65783C` | `0x7F9BE800` | `0x8001603C` | main.c | 8 | n/a |
| TOWN.BIN | `0x65B01C` | `0x7F9BB000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x67181C` | `0x7F9A4800` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x68DBE4` | `0x7F989000` | `0x80016BE4` | lshop.c, main.c | 9 | n/a |
| TOWN.BIN | `0x6AA01C` | `0x7F96C000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x6CC81C` | `0x7F949800` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x6E181C` | `0x7F934800` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x6EFF5C` | `0x7F926800` | `0x8001675C` | main.c | 5 | n/a |
| TOWN.BIN | `0x6F481C` | `0x7F921800` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x6F701C` | `0x7F91F000` | `0x8001601C` | main.c | 5 | n/a |
| TOWN.BIN | `0x6FDB58` | `0x7F918800` | `0x80016358` | main.c | 5 | n/a |
| TOWN.BIN | `0x705138` | `0x7F911000` | `0x80016138` | main.c | 5 | n/a |
| TOWN.BIN | `0x71A138` | `0x7F8FC000` | `0x80016138` | main.c | 5 | n/a |
| TOWN.BIN | `0x7F7FCC` | `0x7FF0A000` | `0x80701FCC` | sn_main.c, tobjs.c | 7 | yes (3 fns) |
| TOWN.BIN | `0x7FFB10` | `0x7FF01000` | `0x80700B10` | flgtst.c, sn_main.c, tobjs.c | 8 | no — repo has only the synthetic base |
| TOWN.BIN | `0x800F44` | `0x7FEFF800` | `0x80700744` | sn_main.c, tobjs.c | 7 | n/a |
| TOWN.BIN | `0x802FB4` | `0x7FEFD800` | `0x807007B4` | tobjs.c | 4 | no — repo has only the synthetic base |
| TOWN.BIN | `0x832944` | `0x9FECD800` | `0xA0700144` | sn_main.c | 3 | no — repo has only the synthetic base |
| TOWN.BIN | `0x837CB0` | `0xFF7CB800` | `0x000034B0` | sn_main.c, tobjs.c | 7 | n/a |
| TOWN.BIN | `0x839100` | `0x9FEC7000` | `0xA0700100` | flgtst.c, sn_main.c, tobjs.c | 8 | no — repo has only the synthetic base |
| TOWN.BIN | `0x83AE30` | `0xFF7C5800` | `0x00000630` | sn_main.c, tobjs.c | 7 | n/a |
| TOWN.BIN | `0x844710` | `0xFF7BC000` | `0x00000710` | tobjs.c | 4 | n/a |
| TOWN.BIN | `0x8CD084` | `0x7F749000` | `0x80016084` | main.c | 2 | n/a |
| TOWN.BIN | `0x8CE084` | `0x7F748000` | `0x80016084` | main.c | 8 | n/a |
| TOWN.BIN | `0x8CF080` | `0x7F747000` | `0x80016080` | main.c | 2 | n/a |
| TOWN.BIN | `0x8D0080` | `0x7F746000` | `0x80016080` | main.c | 5 | no — repo has only the synthetic base |
| TOWN.BIN | `0x8D1080` | `0x7F745000` | `0x80016080` | main.c | 8 | n/a |
| TOWN.BIN | `0x8D2144` | `0x7F744000` | `0x80016144` | main.c | 5 | n/a |

\* the TOWN.BIN row for pool `0x26986C` is MAIN.BIN's pool: TOWN.BIN carries a code-only copy
of that module, so its two sites are resolved against MAIN.BIN's identical string pool (§6).

## 6. MAIN.BIN — Sony's `c_server.c` and Konami's card menu

MAIN.BIN carries **two** independent link images:

| file range | link base | evidence | reached at runtime |
|---|---|---|---|
| `0x25D000`–`0x269000` | `0x80020000` (`base = 0x7FDC3000`) | 327 of the region's `jal`s target `0x8002xxxx`; the port's boot loadmap records `0x80020000 +0xC000 <- MAIN.BIN+0x25D000` | **yes** |
| `0x269000`–`0x275800` | `0x80400000` (`base = 0x80197000`) | 348 `jal`s target `0x8040xxxx`, `lui 0x8040/0x8041` dominate, and `0x269000 + 0x80197000 = 0x80400000` exactly | no — `0x80400000` is outside retail's 2 MB |

The second image is a **devkit (8 MB DTL-H2000) build** of the memory-card front end: it links
its own copy of Sony's `c_server.c` (an older revision, §4.3) plus Konami's eight card-menu
files. `overlays/main/overlay_first_pass_results.json` already knows this base
(`load_base: 0x80197000`, `base_confidence: derived`) but puts the boundary at file `0x26A0F0`;
the assertion sites prove it starts at file `0x269000` (see §8.4).

### 6.1 Per-file tables

#### `c_server.c` — shipped copy (MAIN.BIN `0x25D000`, loads at `0x80020000`)

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

#### `c_server.c` — devkit copy (MAIN.BIN `0x269000`, linked at `0x80400000`)

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| — | expr | `card_first_flg` | `func_80019E34` | `0x80400E34` | MATCH | 1 |  |
| — | expr | `cnt` | `func_8001AB30` | `0x80401B30` | MATCH | 2 |  |
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

#### `card_mes.c`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 665 | assert | — | `func_8001BF84` | `0x80402F84` | MATCH | 1 |  |

#### `card_opt.c`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 337 | assert | — | `func_8001CBC4` | `0x80403BC4` | MATCH | 1 |  |

#### `card_win.c`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 299 | assert | — | `func_8001D364` | `0x80404364` | MATCH | 1 |  |
| 300 | assert | — | `func_8001D364` | `0x80404364` | MATCH | 1 |  |
| 303 | assert | — | `func_8001D364` | `0x80404364` | MATCH | 1 |  |

#### `cardbk.c`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 378 | assert | — | `func_8001DC84` | `0x80404C84` | MATCH | 1 |  |

#### `cardinfo.c`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 416 | assert | — | `func_8001E7F0` | `0x804057F0` | MATCH | 1 |  |

#### `cardslot.c`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 310 | assert | — | `func_800206C8` | `0x804076C8` | MATCH | 1 |  |
| 331 | assert | — | `func_800207D4` | `0x804077D4` | MATCH | 1 |  |
| 339 | assert | — | `func_80020830` | `0x80407830` | MATCH | 1 |  |

#### `cardsme.c`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 238 | assert | — | `func_80020C10` | `0x80407C10` | MATCH | 1 |  |

#### `memory.c`

| line | kind | expression | containing function (nominal) | true vram | decomp status | copies | note |
|---|---|---|---|---|---|---|---|
| 371 | assert | — | `func_800213FC` | `0x804083FC` | MATCH (as dedup rep) | 2 |  |
| 387 | assert | — | `func_800214DC` | `0x804084DC` | MATCH (as dedup rep) | 2 |  |


`memory.c`'s two assertions also exist as a **code-only copy in TOWN.BIN** at file `0x2713FC` /
`0x2714DC` — byte-identical to MAIN.BIN's, hence the same `0x80400000` link — but TOWN.BIN does
not carry that image's `.rdata`, so those two rows' base is carried over from MAIN.BIN and is
flagged `cross-container (rdata absent from TOWN.BIN)` in the CSV.

## 7. The devkit blob in TOWN.BIN

TOWN.BIN file `0x7F7F00`–`0x845000` (at least; the pools run from `0x7F7FCC` to `0x844730`) is not shipped game code. It holds several link images of a
Konami scene-authoring / test tool:

| pool foff | base | link address | note |
|---|---|---|---|
| `0x7F7FCC` | `0x7FF0A000` | `0x80700000` | + the `\vx035\data\sn\SENGEI00-10.BIN` path table at `0x7F877C`–`0x7F8894` |
| `0x7FFB10` | `0x7FF01000` | `0x80700000` | the most complete image: `flgtst.c`, `sn_main.c`, `tobjs.c` |
| `0x800F44` | `0x7FEFF800` | `0x80700000` | |
| `0x802FB4` | `0x7FEFD800` | `0x80700000` | `tobjs.c` only |
| `0x832944` | `0x9FECD800` | `0xA0700000` | KSEG1 (uncached) link |
| `0x837CB0` | `0xFF7CB800` | *unrelocated* | `lui $a0, 0x0000` — a raw `.obj`, never linked |
| `0x839100` | `0x9FEC7000` | `0xA0700000` | KSEG1 |
| `0x83AE30` | `0xFF7C5800` | *unrelocated* | |
| `0x844710` | `0xFF7BC000` | *unrelocated* | |

In this blob the assert idiom is `if (dbgflag) { srv->printf(fmt, file, line); srv->exit(1); }`
with the service vtable at slots `+0x64` (printf) and `+0x70` (exit), and it uses the extra
`mark: %s line %d\n` trace macro that never appears in shipped code.

A **second, separate** code island sits at TOWN.BIN `0x268000`–`0x278000` (~22 functions,
`lui 0x8040/0x8041`, `jal 0x8007C040` = its own `printf`, `jal 0x8007BEF0` = its own `exit`).
Two of its sites are the `memory.c` rows of §6.1; the rest of its `.rdata` is not in the
container.

### 7.1 Other developer strings, with locations

| string | container | file offsets |
|---|---|---|
| `\vx035\data\town\sb43s000.bin`, `\vx035\data\town\sb06.bin` | TOWN.BIN | `0x65281C`, `0x65283C` |
| `\vx035\data\sn\SENGEI00.BIN` … `SENGEI10.BIN` (11) | TOWN.BIN | `0x7F877C`–`0x7F8894` |
| `\vx035\data\town\st.bin` (6) | TOWN.BIN | `0x8CD128`, `0x8CE128`, `0x8CF124`, `0x8D0124`, `0x8D1124`, `0x8D21E8` |
| `\vx035\data\sn\mv05.bin` | TOWN.BIN | `0x8D20FC` |
| `GAME OVER` (4) | TOWN.BIN | `0x78BA94`, `0x796030`, `0x796070`, `0x7960B4` |
| `BASLUS-00614` (save file name) | MAIN.BIN | `0x264F20` → vram `0x80027F20` (shipped image) |
| `BISLPS-00001` (leftover JP save name) | MAIN.BIN | `0x271AA8` → vram `0x80408AA8` (**devkit** image) |
| `CHAN %x\n`, `CARD STATUS0/1 %x\n`, `illegal data` | MAIN.BIN | `0x269090`, `0x2690BC`/`0x2690D0`, `0x269138` (devkit image, vram `0x80400090` / `0x804000BC` / `0x804000D0` / `0x80400138`) |
| `bu10:` / `bu00:` (libcard device names) | MAIN.BIN | `0x25D074`/`0x25D07C` (shipped, `0x80020074`/`0x8002007C`) **and** `0x2690E4`/`0x2690EC` (devkit, `0x804000E4`/`0x804000EC`) |
| RCS `$Id: intr.c,v 1.76 …` / `bios.c,v 1.86` / `sys.c,v 1.129` | SLUS | `0x6AC8`, `0x6D78`, `0x6EFC` |

`\vx035` is the developer's drive/volume root; `sn` holds the `SENGEI*` scene-data files and `town` the town map data.

## 8. Corrections to `port/docs/report_console.md` §5

1. **§5.2 — the "second module at `0x8002C000`" is really at `0x80400000`.** Its addresses in
   that report are all `0x3D4000` too low: `0x8002C004` → `0x80400004`, `0x8002C02C` →
   `0x8040002C`, `0x8002C038` → `0x80400038`, `0x8002C044` → `0x80400044`, `0x8002C090` →
   `0x80400090`, `0x8002C114` → `0x80400114`, `0x8002C120` → `0x80400120`, `0x8002C138` →
   `0x80400138`, `0x8002C548`… → `0x80400548`…, `0x8002C80C` → `0x8040080C`, and
   `0x80034AA8 BISLPS-00001` → `0x80408AA8`. The module is a devkit-only image (§6); the
   report's own observation that "this second module's load was not observed" is consistent.
   `0x80027F20 BASLUS-00614` is in the shipped image and is correct as printed.
2. **§5.3 — the TOWN.BIN copy counts mix two different macros.** The 76 `Assertion failed`
   copies break down as `main.c` 54, `lshop.c` 10, `tobjs.c` 8, `player.c` 4 — `sn_main.c` (7)
   and `flgtst.c` (2) are **not** assertion file names; they belong to a third macro,
   `mark: %s line %d\n` (9 copies, devkit blob only). The report also lists `s0[0]`/`s1[0]`/`s[0]`
   under `lshop.c`; the `.rdata` block layout does not support that (§3.3).
3. **§5.3 — "every one of these 76 assertion sites is in a function that has not been
   decompiled yet" is no longer true.** Of the 458 located site copies, 426 sit in a function the
   first-pass sweep byte-matched (99 as the cluster representative, 327 as a retired duplicate);
   32 are in functions not covered by a sweep record. The reason `rg '\bprintf\s*\('` finds
   nothing in `overlays/town/first_pass_matched` is that the overlays never call `printf`
   directly — they call it through a service-table `jalr` (§1.2), which m2c renders as an
   indirect call through a struct field.
4. `overlays/main/overlay_first_pass_results.json` places the `0x80197000` module boundary at
   file `0x26A0F0`; the assertion sites show it starts at `0x269000`. Three functions —
   `0x269A10`, `0x269E34`, `0x269EF8` — are therefore labelled with the wrong `true_name`
   (`func_8002CA10` / `func_8002CE34` / `func_8002CEF8`); they should be `func_80400A10` /
   `func_80400E34` / `func_80400EF8`. Their code references `0x80400004`/`0x8040002C`
   (the assert format string and `"c_server.c"`), which is only reachable under the
   `0x80197000` base.

## 9. Using this when re-shaping the C

* **Treat each row of §4 as a hard constraint, not a hint.** `func_804721A4` is the function
  that contains `main.c:40` — full stop. Any file-splitting plan that puts it somewhere other
  than `main.c`, or that puts it in the same TU as `func_80471AC4` (which contains
  `lshop.c:65`), is provably wrong.
* **Use the assertion lines to order functions inside a file.** Within one object file the
  compiler emits functions in source order, so `lshop.c`'s three functions are in the order
  65 → 113/118 → 128, and a fourth `lshop.c` function found later in the same chunk is at a
  line > 128.
* **Use them to size the gaps.** `main.c:40` and `main.c:55` are 15 source lines and 0xD4 bytes
  apart — that is a whole small function. The `ost_w` function is ~0xA90 bytes past `main.c:55`,
  so several hundred lines of `main.c` sit in between, across several functions.
* **Use them to name TUs.** `main.c`, `lshop.c`, `player.c`, `tobjs.c`, `sn_main.c`, `flgtst.c`
  are Konami's real file names and can be used verbatim for the recovered TUs; the card files
  (`card_mes.c`, `card_opt.c`, `card_win.c`, `cardbk.c`, `cardinfo.c`, `cardslot.c`,
  `cardsme.c`, `memory.c`) likewise, even though the copy on the disc is a devkit build.
* **Re-emit the assertions.** When a function listed here is rewritten in C, the retail bytes
  can only be reproduced by writing the assert back in. The macro is literally
  `printf("Assertion failed: file \"%s\", line %d\n", __FILE__, __LINE__)` followed by
  `exit(1)`, both dispatched through the overlay's service table — matching that function is a
  test of both the macro shape and the `__LINE__` constant, so a mismatch there is a signal the
  function has been placed at the wrong source line.
* **Cross-check overlay bases.** §5 gives 66 independently derived load bases. The repo can
  corroborate only a handful of them (§1.3); for the other ~60 town chunks it currently carries
  just the synthetic `file + 0x80080000` naming label. They are directly usable to raise
  `base_confidence` in `config/overlays/town_*.overlay.yaml`, and the pool vram column doubles
  as a check: every town game chunk maps its debug pool into `0x8001xxxx`, the free RAM window
  below the resident EXE at `0x8002D000`.

## 10. Unresolved

* The object file behind `head` / `ptr[n].vx` / `ptr[n].vy`, behind `s0[0]` / `s1[0]` / `s[0]`,
  and (less certainly) behind `kind` / `mode` / `sno` — see §3.3.
* Whether `main.c` here is the *town overlay's* `main.c` or the game's global `main.c`. The
  assertions at lines 39/40 and 54/55 are near the top of a file whose object is linked into
  every town overlay, which fits an overlay-local `main.c` per scene directory.
* The exact extent of the TOWN.BIN `0x268000`–`0x278000` code island (§7). Its `.rdata` is not
  in the container, so only the two `memory.c` sites there could be resolved, and only by
  borrowing MAIN.BIN's identical string pool.
* Whether the three unrelocated `.obj` images in the devkit blob (`0x837CB0`, `0x83AE30`,
  `0x844710`) are complete objects or fragments. Their `lui` fields are zero, so their site
  "vram" values in the CSV are section-relative offsets, not addresses.
* One `%s = %d\n` copy at TOWN.BIN `0x832944` (devkit blob) has no call site at all in the
  container.
