# Symbols and naming conventions

The readable name, stable row ID and linked address symbol serve different
purposes. `config/names.tsv` records function/global aliases and their evidence;
build preprocessing lowers those aliases to canonical `func_`/`D_` symbols.
Renaming a file does not replace a row ID. Use the
[source resolver](SOURCE_LAYOUT.md) to find a definition.

## Choosing a name

* Preserve an original developer identifier when the disc proves its spelling.
* Coin new function and global names in snake_case, without a binary prefix.
  The directory supplies that context. Types use PascalCase; macros use
  UPPER_SNAKE_CASE. Names must remain unique within each link.
* Describe the supported role. Do not turn a table-slot number or randomizer
  patch-site label into an unsupported claim about the whole function.
* Keep `unk_XX` or an explicit uncertainty when field meaning remains unknown.
  A readable hypothesis should be documented and revisable.

These rules follow [decisions 61 and 63](evidence/r97_decisions.md), including
the exception for proven developer/script names. Old camelCase proposals in
historical notes are not the convention for newly coined names.

## Names present on the disc

Assertion strings identify source files including `lshop.c`, `main.c`,
`player.c`, `c_server.c` and memory-card UI files. The
[assertion catalogue](evidence/konami_assertion_sites.md) records sites and
copies. Keep a filename's exact spelling when a complete TU supports it;
do not rename an inferred mixed group solely from one asserted function.

Debug expression strings preserve identifiers such as `OSETDT`, `ost_w`,
`osel_w`, `cdhd_cnt`, `ov_work.kind` and `gsw->check_sum`. They prove the text,
while an owning module or full type layout may remain inferred. The per-row
[evidence index](EVIDENCE.md) points to the machine-readable records.

## Script numbers and dispatch

The symbol dump uses 36-byte records: a 32-byte name followed by a little-endian
32-bit value. Earlier notes parsed the fields in the wrong order and assigned
each name the preceding value. The current interpretation is **call number n
selects entry n**, with no added offset. The
[call-table investigation](evidence/script_call_table_20260908.md) preserves
that correction and its evidence.

Use `include/script_symbols.h` and the current `ledger/evidence/` records when
interpreting script constants. `S_`/`FNO_` dispatch names, flags, scene steps and
variable-table indices are distinct families. Replace a literal only after
identifying the accessor or dispatch operation that consumes it. Identical
numbers from different families do not establish equivalent meanings.

Resident function-pointer tables similarly establish slot/handler identity.
Read a handler and its callers before giving the slot a semantic opcode name.
The [randomizer address evidence](evidence/adrando-findings.md) supplies verified
data-table facts and patch-site roles, with the same distinction between a
site's use and the surrounding function's full purpose.

## Proving a rename

Review the evidence for the meaning, then check object bytes, symbols,
relocations and the affected retail window or executable image. Alias lowering
does not waive the build check. A member rename in a shared header reaches all
of its users. [RENAME_PROOF.md](RENAME_PROOF.md) explains the proof boundaries;
[TYPE_CONSOLIDATION.md](TYPE_CONSOLIDATION.md) covers shared declarations.

The current alias table and generated status supersede old tables of names
or naming counts in research journals. Evidence records remain dated history.
