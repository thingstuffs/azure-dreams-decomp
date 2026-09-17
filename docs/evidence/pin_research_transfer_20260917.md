> Research checkpoint, 2026-09-17. Experiment paths below are relative to
> `work/native_lane/r39_split_family`. This snapshot preserves findings and unresolved
> next experiments; ongoing lane work may add newer results.

# Split-address family transfer

## Scope

The current ledger has 6,767 rows.  Filtering to an attributed `2.6.3` or
`2.7.2` head cell, size at most 256 bytes, at least one live `pin_census` site,
and at least one `volatile` occurrence leaves 32 rows.  Source review reduces
that to eight rows with a live volatile object or dereference; the remainder
use `volatile` only in explicit asm or comments.  The scored cohort below tests
the three rows with ordinary symbol/table access, one direct-table row, and one
absolute-address negative control.  A single 344-byte, one-pin bounds-table row
was added after the small cohort had no second clean member.

Every candidate is under this directory, has zero `sites_of()` pins, and was
verified with `tools.verify.verify(..., include_root=ROOT/include)`.  No source,
config, ledger, shared-toolchain, or build-root file was changed.

## Exact exemplar repair (the cohort's only exact positive)

`dungeon/func_81811388` becomes ordinary C:

```c
s32 func_80026388(s32 input_value, s32 target, s32 lookup_index)
{
    return func_80049DE8(target, input_value, D_800294F8[lookup_index]);
}
```

Base source SHA-256 before landing:
`ea1ab4d234ba70a50284417d5a2a29088815f6225fc1813e8c644cd623fbb074`.
Candidate SHA-256:
`8e5e3e8709fea8dc720408d5139f4e7bf6c2f7beff134e7b54bf2dd4f3c36415`.
The landed spelling has SHA-256
`0cbca3cba8b36063bad36020fae7ef2973f5b31f18afb0435faaddbabe9c07ae`
(prototype argument names and comment differ, code does not).  After landing,
the row records stock `2.7.2-cdk`; a fresh `tools/verify.py` run is exact
14/14, `sites_of()` is empty, and `landing_refusal` returns `None`.

| config | result | words | aligned total |
|---|---|---:|---:|
| 2.7.2 | no match, `li-expansion` | 13/14 | 6 |
| 2.7.2-cdk | exact | 14/14 | 0 |
| 2.8.0 | exact | 14/14 | 0 |
| 2.8.1 | exact | 14/14 | 0 |
| 2.95.2 | exact | 14/14 | 0 |

This is specifically a compiler RTL address-form difference.  Plain 2.7.2
combines the access before allocation into one scheduled expression:

```text
(mem:QI (plus:SI (reg a2) (symbol_ref "D_800294F8")))
```

Its assembly therefore has the assembler macro
`lbu $a2,D_800294F8($a2)` and only 13 words.  The CDK family instead creates
separate `high(symbol_ref)` and `lo_sum(high,symbol_ref)` pseudos in initial
RTL.  Local allocation gives the short address quantities `$v1`, preserves
the input in `$v0`, adds the index, and emits the retail `lui/addiu/addu/lbu`
sequence.  This is visible before assembly; it is not a maspsx expansion or a
scheduler flag effect.

The volatile qualifier is the decisive source difference, not pin erasure by
itself.  Erasing only `ASM_REG("$2")` while retaining `volatile u8 *table`
stays at total 5 in every stock cell: the input becomes `$v1` and the address
quantity wins `$v0`.  Removing the qualifier collapses the volatile QI load
quantity; at CDK's split-address RTL the address quantities take `$v1` and the
input naturally remains `$v0`.  Changing the function from `void` to `s32` is
byte-neutral because the helper result already returns in `$v0`.

The return type is semantically required.  All three same-image callers declare
the function `s32`, assign the result, and store or forward it:
`func_8181140C.c`, `func_81811508.c`, and `func_818115B8.c`.  The table is
ordinary RAM lookup data, not MMIO or synchronization state: neighboring code
uses its nine bytes to compute selection/buffer widths, and one neighboring TU
already declares it nonvolatile.  The positive candidate therefore removes an
artificial qualifier rather than weakening observable I/O.

## Transfer cohort

| row / candidate | best relevant result | mechanism finding |
|---|---:|---|
| `town/func_800B51B8`, direct `D_80089268`, all pins and local volatile removed | 2.95.2 `7`, 17/19 | Removing the volatile byte array deletes two retail memory operations; not the exemplar mechanism. |
| same row, retain volatile byte array | 2.95.2 `2`, 19/19 | Zero pins, but first load still folds directly off the high-page register and crosses the RA save; retail first completes the split base in `$a2`. `register` hint leaves the same residue; cursor mutation worsens it to 9. |
| `town/func_806D34CC`, nonvolatile `D_80016000`, all pins removed | `15`, 21/21 at 2.7.2 through 2.8.1 | Identical result across the split family.  The `$v1` pin owns quotient arithmetic coloring, not symbol address formation. |
| `town/func_80878974`, nonvolatile callback table, initialized zero, all pins removed | 2.7.2 `5`; CDK `39` | The residual at the attributed cell is code motion; split cells change the callee-saved hold set and frame.  Its `$zero` pin is unrelated to a table address. |
| `town/func_8009973C`, typed `D_800FE520` bounds symbol, all volatile/pin removed | 2.7.2 `28`; CDK `29` | The volatile loads and numeric-page source encoded repeated access behavior throughout the loop; changing to one ordinary symbol is a broad rewrite, not a local address split. |

The closest independent transfer is `town/func_800B51B8`: the newer family
does form the desired split base and reduces the zero-pin residue from 8 at
plain 2.7.2 to 2 at 2.95.2.  It is not an exact win.  The remaining two words
are fully attributed: generated word 2 is `lb v1,-0x6d98(v0)` where retail has
`sw ra,24(sp)`, and generated word 4 is that `sw` where retail has
`lb v1,0(a2)`.  Retail completes `addiu a2,v0,-0x6d98` before the first load;
2.95.2 folds that first use against the high-page register and schedules it
before the save.  Ordinary `register s8 *global` does not alter this combine;
pointer-increment source adds three words.  This row should remain pinned until
a natural single-base source shape is found.

No independent row reached exact.  The cohort therefore does **not** establish
a general de-volatile/de-pin repair.  It establishes the causal explanation for
the landed exemplar, two negative ownership controls, and one measured
follow-up at total 2.  For `800B51B8`, the next useful source hypothesis must
make the first byte access depend on the completed `global` base and must allow
the RA save to precede that access.  The tested cells did not resolve either
decision; the next probe should target that source/RTL cause.  The four tested
split-address cells expose the same combine shape through 2.8.1, while 2.95.2
improves scheduling/coloring to the measured total-2 residue.

## Negative controls and volatile safety

`dungeon/func_8009A288` removes its single keep and the volatile qualifiers but
keeps the numeric `0x80010000 + 0x3716` access.  It scores total 8 at both its
2.6.3 config and `2.7.2-cdk` (51/49, polarity/rematerialization), then worsens
at 2.8.x.  Because there is no `symbol_ref`, CDK has nothing to split into
`high/lo_sum`; this is the expected no-address-split control.

`town/func_8087FEF0` was deliberately not transformed.  It writes
`D_807009B0`, calls through a global callback, makes more external calls, then
rereads `D_807009B0`/`D_807009B4` and returns `D_807009B0`.  Those intervening
calls make the rereads semantically observable.  Removing volatile as a family
rewrite would be unsafe without a whole-program alias/state proof.

The bounded evidence supports a narrow probe hypothesis for future rows: try
de-volatile/de-pin at a split-address cell when a single ordinary symbol access
creates a short-lived address quantity and the object is demonstrably ordinary
RAM.  Multiple accesses may fold separately; arithmetic pins and volatile
reread contracts do not transfer.
