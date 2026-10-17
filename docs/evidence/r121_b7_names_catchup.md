# r121 B7: names catch-up for twins2 relink rows

The twins2 rows landed by B4 (and B6) were generated and proven at a base that predates the B3 name pass (4,650 aliases,
`config/names.tsv`). B3 renamed the shared-header declarations and the donor rows; the twins kept the pre-names spellings. A full
window gate at B6 (`bf7d31466`) failed 291 of 2,826 windows. B7 repairs them mechanically; after it the same gate is 2,826 of 2,826 MATCH.

| class | windows | cause | repair |
|---|---:|---|---|
| undeclared identifier | 283 (+142 masked behind them) | `#define func_OLD func_NEW` relied on the header declaring `func_OLD`; the header now declares the alias of `func_OLD` | 425 files: `#define <alias(OLD)> func_NEW` (first operand only) |
| extent short by 4 or 8 B | 8 (+34 masked) | the twin calls resident functions by raw name, so the header's real prototype (for example `s16` return, which adds the sign-extension pair) no longer applies and the call compiles as implicit `int` | 37 files: the resident symbols the donor now spells by alias are re-spelled by alias in the twin (header-declared ones only; the twin's own `extern` lines and its own function names are untouched) |
| `.rodata` of a switch table discarded at link | 8 | `config/overlays/dungeon.rowbase.jsonl`: the twins2 lane promoted whole images solved -> proven; B3's split `rest` regions kept `solved`, so the rowbase mini-link (which derives the local jump-table placement) was never used for these rows | 28 `rest` regions promoted with `tools/rowbase.py promote` (every row in each region is a twins2 row that recompiles byte-exact there) |

Tools: `work/native_lane/_r120/b7/tools/` (`names_catchup.py`, `alias_catchup.py`, `fixpoint.py`, `extent_loop.py`). Report:
`work/native_lane/_r120/b7/REPORT.md`.
