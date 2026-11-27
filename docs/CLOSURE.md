# The ownership check

This page says what the one number the check prints means, what it counts, what it cannot see and how its files
change. The tool is `tools/lint/closure.py`. It runs after the landing's full `make check` and today only reports: it
never fails a landing (the constant `GATING` in the tool says so, and flipping it is a reviewed one-line change).

## The number

    HEADLINE game code without C: <H> B (physical <p>, C-data bodies <q>, decoded <d>) | unknown <u> | open hits <h>

**H is the number of bytes of this game's code, on the disc or inside a decoded image, that no compiled C function
emits.** It is the sum of:

- *physical*: bytes of the program files (MAIN, TOWN, DUNGEON, OVMOVIE and the executable) that a line calls
  `own:code`, outside every region line (so a foreign program that shares a file is not counted);
- *C-data bodies*: bytes that the build emits as C data (an array) but that hold a function body, acknowledged one by
  one with a `code_in_c_data` line, outside every region line;
- *decoded*: bytes of decoded images (the compressed menu code) that a decoded line calls `own:code`, counted in
  decoded bytes.

H goes down only when C lands over code (a function is written and placed), and goes up only when a line is added.
Every added line is printed in the report. The older menu cache is another program's stream and is not in H.

## What the tool checks

Every byte of the five program files and of each decoded image is exactly one of:

1. **compiled C**, read from the build itself (and since v6 only compiler output: see "Assembler in C units" below). The build writes a cover list into each image's origin file: which bytes
   a compiled object emits, and which of those are a whole function (an input section `.text.<name>` of a C object
   that holds a FUNC symbol of the section's size at offset 0). Every other byte of a C object is C data. Assembled
   units count as assembly and retail imports as nothing. The tool reads cover lists only through the full
   `build/check.json`, which binds each origin file and each decoded proof by sha256;
2. **a line** of `config/closure/<file>.tsv` (a large file is split into numbered parts): `own:code`, `own:vendor`,
   `own:stream:<image>`, `own:data`, `own:padding` or `own:untyped`;
3. **zero**: a run of at least 16 zero bytes between word boundaries (automatic; a shorter run is an ordinary byte).

A byte in none of these, or in two lines, is **unknown**. An `own:` line over compiled C is refused. Region lines
(`region:other:<program>`, `region:stale:<file>:<k>`, `region:unreached:<family>`) say whose program a byte belongs to;
they may lie over anything and never hide a byte from ownership. Disc files that are not program files (movies, the
system file, the licence data) have one whole-file line each in `disc_files.tsv`, by size and sha1; sectors that no file
names are not covered.

## Lines

Five tab-separated columns: `start end class evidence sha256` (hex offsets, end exclusive, sorted). The hash is the
sha256 of the bytes in the extent, so a moved or edited range makes the line stale. An extent under 16 bytes never
carries a digest of its own bytes (the reader refuses one): its column is `w<offset>+<length>:<sha256>`, the digest of
an enclosing window of at least 16 bytes inside the same file, which the check recomputes. A change of any byte in the
window, the extent's own bytes included, is detected; a line moved inside an unchanged window is not, and a change
outside the window is not seen by that line. Evidence is a tracked path, or
`path#key` with the key present in that file. A work label in the evidence text is refused. A line is added as a whole
line (an edit is a removal and an addition) and the report lists every line added and removed against HEAD (a batch
root compares with its root commit). No flag accepts, tightens, rewrites or baselines a line, and no argument names a
base.

Class tests: `own:padding` is one fill value ending on an alignment boundary it is shorter than; `own:data` lies on
bytes the census map calls data; `own:vendor` lies on assembled SDK bytes of the build or inside the extent of the SDK
object record its evidence names, and calls no compiled game function; `own:stream:<image>` equals a registered
compressed stream (`config/decoded` or `config/closure/streams.tsv`) by extent, source hash, decoded length and command;
`region:other` stays out of load regions with load evidence (a load record is load evidence only when it records a
retail load, at a base inside the retail RAM: a record that says link evidence only, or a linked base only, or sits
above the retail RAM or in the kernel area, is not); `region:stale:<file>:0` is word for word the named program file at
the same offsets (checked at run time against the disc's program files; the line holds offsets and sizes only).
Compiled functions are counted one per `.text.<name>` member of a module object: the check reads the member extents from
the image link map (`build/.state/link/<image>/image.map`, whose sections must tile exactly the code ranges of the
cover list; its linker script is bound by the origin file) and leaves a chunk whole when they do not.

## The detector

Bytes that no compiled function emits (C data, `own:data`, `own:padding`, `own:untyped`) are scanned for code:

- **D1** a `jr ra` word with the valid words behind it (a run of paired identical words, or six or more words with fewer
  than three distinct instructions besides the return and zero, is a table, not a hit); **D2** a stack frame that saves
  the return address with no return in reach; **D3** a call from compiled code that lands in data, or inside another
  function's body (reported once per entry point, with its call-site count). A call target is mapped through the chunk of
  the image that is loaded at that address (a whole-file image has several load deltas); an address no chunk is loaded
  at is not judged. A call from the executable into the engine images' load range, and a mid-body call whose target is a
  function start of another program at that address, are counted as calls to other programs and not judged. A call site
  inside a region line is closed by it. **D4** a word that points exactly at the start of a D1 or D2 body; **D6** a compressed
  stream with a code signature that starts inside `own:data`; **D7** in another program's region, a body whose calls all
  land on starts of this executable.
- **D8** (report only): a body without a return word, six or more valid words ending in a jump (`j`, or `jr` on a register
  other than `$31`) with a grounded load or store (a base register that is the stack or global pointer, an argument
  register not yet written, or an address built in the run); the tail-call endings D1 cannot see.
- **D5** (16 valid words with loads or stores and a branch or call) and **D3B** (an image with compiled code in which no
  local call lands on a function start) are listed and counted and not open, with two exceptions: a D5 run that contains a
  call landing on a function start of the build, and a D5 run that lies in no image of its file **and** has register dataflow (at least two loads or stores through a base the run
  grounds, see D8; a dense run without it is listed as `no_image_ungrounded` and is not open) (reported as the class
  `code_fragment_in_no_image`: function-shaped, no entry, no return, nothing loads it). A run in which 40 % or more of the
  halfwords carry a Shift-JIS lead byte is text and not a D5 hit unless it holds such a call.
- The SDK startup entry's call to the game's `main` is the one named exception to "vendor code calls no game function".

An open hit is closed by an acknowledgement line `ack:<rule>:<verdict>` with the hit's exact extent and hash
(`data`, `other_program`, `code_in_c_data`, `cross_image_call`, `midbody_entry`, ...), or by a region line over it. An
acknowledgement that matches no hit is stale and refused.

## Assembler in C units

"Compiled C" must mean compiler output. A function whose body is assembler text inside a `.c` file (a file-scope
`asm` block with directives around an include of bytes, or word lines) builds the same object shape as a compiled
function, so an object cannot tell them apart, and the landing's debt scan did not see an `asm` keyword spelled through
a token-pasting macro. `tools/lint/closure_asm.py` closes this on the source side: it reads the macro-expanded text
(`gcc -E`, the same expansion the object cache key binds) of **every unit of the build plan** and classifies each
assembler use:

- (a) a symbol-rename suffix on a declaration, `... __asm__("name")`, with no operands and a bare symbol or register
  name: allowed;
- (b) an `asm` statement inside a function body whose template holds instructions only (the GTE templates of
  `include/common.h` and the stack-switch templates of `include/slus/spadstk.h`): allowed when its string contains no
  token that starts with a dot (no directive: no section, include, incbin, word, byte, ent, end, size, set) **and** its
  exact text is a row `template` of `config/asm_templates.tsv` (30 rows today, none with a directive);
- (c) everything else is refused, and the build fails for that unit with the file and line: any file-scope assembler
  block, a directive inside a template, a template text that is not listed, a section attribute naming a code section
  (`.text...`) that is not listed. The two file-scope lines every unit carries (`.include "include/labels.inc"`, bound by
  the sha256 of that file) and two `.size name, N` lines of tables placed in code sections are listed by exact text.

The check runs from the Makefile (`make`, `make check`, the landing's build and check): for every unit on every run,
cached or not, over the overlay recipes (modules and the movie overlay included), the executable's recipes and the
decoded images' units. It reads no object and no cache entry, changes no built byte and is not an object cache key input.
Run it alone with `python3 tools/lint/closure_asm.py check [--census OUT.json] [--root DIR] [--templates FILE] [--no-memo]` (a full walk is 60 to 80 s at 4 processes on a quiet box; a memo in `build/.state/asm_check_memo.json` skips a unit whose key is unchanged and takes a no-change run to about 4 s; the key binds the checker file, the templates file, `include/labels.inc`, the unit's route, compiler version, flags and include path, its sources, every file its recipe lists as a dependency, the names of the files under `include/` and in each source's directory; a refusal is never stored; `--no-memo` reads and writes nothing; the decoded images' units have no recipe and are always checked); `--write-templates`
rewrites the list from the tree (a reviewer reads the diff; a new template is a visible landing change). What it does
not see: assembler that gcc itself emits for a legitimate template with operands (the operand constraints are not
read), and a template that is listed but later changes meaning because an included file changes (only the labels file
is hash-bound). `INCLUDE_ASM` and `INCLUDE_RODATA` are gone from the headers; the two file-scope `.include` lines of
`include/include_asm.h` stay because every unit's assembly carries them and removing them re-keys every object.

## What a landing prints

The landing prints, uncut and after the summary lines (`HEADLINE`, `LINES`, `FILE`, `FINDINGS`):

- `TOOLFILES` (also printed by `land_make` from git, outside the tool): the changed tool files and changed rule
  constants (`REPORT_ONLY_RULES`, `GATING`, ...) in this landing; the closure unit tests run in the landing's test list;
- every added, changed (same extent, other class, evidence or hash) and removed exception line in full (`ADDED`,
  `CHANGED`, `REMOVED`), every added or removed `streams.tsv` row (`STREAMROW`) and ruling row (`RULING`);
- `GAINED`: when an `own:code` line is removed or the headline falls, the compiled functions that lie over the removed
  lines (decoded functions by name), with a marker `UNMATCHED` when the headline falls and no compiled function lies
  over a removed line;
- every load-record change (`LOADREGION added/removed`), every link document whose content changed (`LINKDOC`), the two
  SDK ledgers' hashes and every added, changed or removed row (`LEDGER`);
- every added, changed or removed row of `config/asm_templates.tsv` (`TEMPLATE`) and `config/closure_rulings.tsv` (`RULING`), in full;
- every refusal-class line in full (`REFUSAL ...`), and the step prints its exit code and `ownership check: REFUSALS
  (report-only)` when the exit code is not 0 or a refusal-class line was printed.

## Declared classes and what tests them

A declared line can be true or false. These tests refuse what a machine can tell (all report-only like the rest):

- `region:unreached`: the evidence must be `config/closure_rulings.tsv#<ruling id>` and the id a row of that file;
- a region line of any kind in a decoded image (this build's own code) is refused;
- `ack:<rule>:data` over a run with a return word needs a reason after `#` from `jump_table, command_table,
  coordinate_table, text_words, coincidental_words`, is counted on its own `ACKDATA` line, and is refused whatever the
  reason over a run that has the shape of a function (a frame word with a saved return, a restored return before a
  return word, two calls to known function starts);
- `own:stream`: at least 0x40 compressed bytes with a recompression proof (a decoded manifest), 0x200 without one (a
  `streams.tsv` row), and a decoded size of at least half the compressed size;
- `own:vendor`: the SDK object record it cites (`ledger/sdk_objects.jsonl`, `ledger/coverage_residue.jsonl`) must not
  have been added or changed in the landing;
- load evidence that held at the base and no longer does (a demoted or removed load record) is a refusal-class line with
  the record itself, and so is a region line over such a range.

No machine test tells whether a `region:other` line over a fragment in no image is true, or whether a ruling row says
what it claims: the landing prints every such line and row in full, and the reviewer decides.

## What the number does not cover

- Code fragments of fewer than 16 words with no return, frame, call or pointer reaching them.
- Code reached only from other images, and pointers computed at run time.
- Sectors that no disc file names, and the bytes of the other disc files (not word-scanned).
- Which function a bound address names in each image (placement bindings): the check counts the bytes the build emits
  as C and cannot tell whether the C names the right callee.
- A false but well-formed added line (a function called "data" or "other program"): the machine tests narrow this and the
  printed list of added lines is what a reviewer reads.
- Compiled sections that carry code but not a FUNC symbol of the section's size count as C data and show up as hits (the
  first run found three such cases, 1,324 bytes).
- Whether the first exception files are right: they were imported once from the census map, the build and a short
  evidence table, and nobody has read them line by line. After that every change is a per-line diff.
