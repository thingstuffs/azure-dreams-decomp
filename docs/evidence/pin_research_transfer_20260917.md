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

The adaptive follow-up is recorded in `B51_SITE_MAP.md`.  Full pass dumps put
the remaining address substitution in the first CSE pass: initial RTL loads
byte 0 through the completed base pseudo, but CSE replaces that exact-register
address with its higher-cost equivalent `lo_sum(high,symbol)`; offsets 1 and 2
remain based on the pseudo.  Delayed/embedded assignments, ordinary register
hints, typed aggregates, pointer aliases, variable reuse, embedded stores, and
neighbor-cursor shapes did not change that choice.  No zero-pin exact candidate
was found.  A partial control at 2.95.2 removes both `ASM_REG` bindings and
`ASM_KEEP(global)`, retaining only `ASM_KEEP(page)`, and scores total 1; this is
measured pin reduction but not landable.  The next source experiment is a
genuine pre-load basic-block/clobber shape recovered from an original owner or
sibling pattern, because CSE resets equivalences at basic-block boundaries.

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

## Post-round-39 follow-up boundary

The `town/func_80878974` table entry above is a negative only for the round-39
callback-table spelling and tested cells. It is not a permanent negative for the
row. A separate round-40 candidate uses a whole 52-byte struct copy with ASPSX
2.40, is zero-pin and exact, has landed through the round-40 record-copy sweep,
and passed semantic review of the ordinary copy, three-argument logger call, and
nonvolatile table. Its full TOWN window and SLUS gates now pass, making it a
resolved individual repair. Its mechanism is distinct from the split-address exemplar,
so it is not an independent positive transfer control here. Round 40 owns its
source/candidate hashes, overlapping-global port-debt record, census update, and
publication receipts.

## Appendix: `town/func_800B51B8` (`func_800B2918`) site map

Retail is 19 words / 76 bytes:

| word | instruction | source/role |
|---:|---|---|
| 0 | `addiu sp,sp,-32` | 3-byte local plus saved RA frame |
| 1 | `lui v0,0x8009` | high page of `D_80089268`; `$v0` dies when the call returns |
| 2 | `sw ra,24(sp)` | save RA while the completed table base is not ready/selected |
| 3 | `addiu a2,v0,-0x6d98` | completed `D_80089268` base; `$a2` stays live as call arg 2 |
| 4 | `lb v1,0(a2)` | signed first table byte; `$v1` later becomes local-array address |
| 5 | `lb a0,1(a2)` | signed second table byte and call arg 0 |
| 6 | `lb a1,2(a2)` | signed third table byte and call arg 1 |
| 7 | `sb v1,16(sp)` | `values[0]` |
| 8 | `sb a0,17(sp)` | `values[1]` |
| 9 | `sb a1,18(sp)` | `values[2]` |
| 10 | `jal get_player_homerank` | actual helper is `s32 get_player_homerank(void)` |
| 11 | `nop` | call delay slot |
| 12 | `addiu v1,sp,16` | address of `values` |
| 13 | `addu v1,v1,v0` | helper result indexes the three bytes |
| 14 | `lbu v0,0(v1)` | selected byte, zero-extended return |
| 15 | `lw ra,24(sp)` | epilogue |
| 16 | `addiu sp,sp,32` | epilogue |
| 17 | `jr ra` | return |
| 18 | `nop` | return delay slot |

### Semantic audit

The helper is really `s32 get_player_homerank(void)` and ignores incoming
arguments. This row deliberately uses an old-style no-prototype declaration and
passes the second byte, third byte, and table base anyway; retail proves those
argument moves are part of the original call sequence. Replacing the declaration
with `(void)` would be semantically valid for the callee but would delete retail
instructions, so it is not a source repair for this row.

The row returns one of three signed table bytes as `u8`. Its two callers declare
an `s32` return and either forward it or store it in an `s32` field. The ABI return
in `$v0` is compatible and the explicit `u8` return explains the retail `lbu`.
`D_80089268` is ordinary table data, not MMIO.

### Rubber duck before probes

The zero-pin symbolic candidate at 2.95.2 is 19 words and differs at only words 2
and 4. It emits:

```text
1  lui   v0,0x8009
2  lb    v1,-0x6d98(v0)
3  addiu a2,v0,-0x6d98
4  sw    ra,24(sp)
```

Retail emits:

```text
1  lui   v0,0x8009
2  sw    ra,24(sp)
3  addiu a2,v0,-0x6d98
4  lb    v1,0(a2)
```

The compiler has combined the first use of `global` back into a direct symbol
load. That load depends only on the page-high quantity, becomes ready before the
completed-base `addiu`, and wins the scheduler slot occupied by the retail RA
store. The two mismatches are one decision chain, not two independent
register/scheduler problems.

The original source condition that would make retail natural is: the first byte
expression must consume the assigned `global` value, so combine cannot legally
respell it as an independent direct symbol access. Then the load is not ready
until after the `addiu`; the independent RA save can occupy word 2. The first
probes therefore change definition/use structure, not flags:

1. delay the pointer definition and embed it in the first load:
   `first = *(global = D_80089268);`;
2. compare a separate assignment statement (`global = D_80089268;`) to prove
   whether embedding, rather than declaration order, is the lever;
3. try a typed three-byte aggregate only if the assignment forms still fold;
4. measure existing-pin subsets at 2.95.2 as controls, without adding any new
   scaffolding.

Current pinned source is exact at both recorded `2.7.2-G0` and `2.95.2 -G0`;
changing cell alone does not remove any of its four pins.

### Measurements after the map

No tested natural spelling reached exact. At `2.95.2 -G0`, all of these stay at
the same 19-word, total-2 residue shown above:

- declaration initialization, separate assignment, and embedded pointer
  assignment;
- ordinary `register`, sized-array, pointer-to-array, and typed-struct forms;
- local pointer aliases (`s8 **`) and an enclosing aggregate rooted at the
  neighboring `D_8008925C` symbol;
- reusing `first` for the helper result, embedding value assignments in the
  volatile stores, direct first store, and spelling the call's third argument
  directly as `D_80089268`;
- a redundant identity guard that CSE removes.

Reusing the pointer after the call shortens the function to 18 words. Shifted
cursor forms add an address adjustment and score 6/8. A full-address literal
expands to 25 words. Volatile-pointee and volatile-first-load controls also
expand (25 and 21 words); they are diagnostic only and are not valid repairs for
ordinary RAM.

The pass dumps locate the first wrong decision precisely. Initial RTL has:

```text
high(symbol_ref D_80089268) -> r82
lo_sum(r82, symbol_ref D_80089268) -> r81
mem(r81) -> first byte
```

The first `cse` dump has already rewritten only byte 0 to
`mem(lo_sum(r82,symbol_ref))`. Bytes 1 and 2 remain `mem(r81+1/2)`. GCC 2.95.2's
`cse.c:find_best_addr` explains the asymmetry: on RISC targets, equal
`ADDRESS_COST` candidates prefer the expression with higher `rtx_cost` because
it may eliminate more instructions. The symbol `lo_sum` wins for the exact
offset-zero address; substituting it inside the offset accesses is not cheaper.
Combine later folds sign extension, and sched2 places the now-ready direct load
before the RA save. Declaration/pseudo numbering cannot affect this choice.

The existing pins confirm the same ownership. At 2.95.2, erasing only
`ASM_KEEP(global)` leaves a one-word addressing substitution: scheduling and all
registers match, but byte 0 is `lb v1,-0x6d98(v0)` instead of `lb v1,0(a2)`.
Erasing both hard-register bindings plus that keep has the same total 1 while
retaining only `ASM_KEEP(page)` (candidate SHA-256
`aad1caf00ef84dbf44075d00f131f8b98888e68b8990d6110d4216329f42307b`).
This is real reduction from four pins to one, but it is not exact and is not a
landing candidate.

The next causal experiment should target initial-CSE reachability, not another
type spelling or compiler sweep: recover whether the original macro/control flow
placed a genuine basic-block boundary or clobbering use between formation of the
table base and byte 0. CSE resets register equivalences at basic-block starts; a
source shape whose boundary is removed only after initial CSE could retain
`mem(r81)` and then let scheduling produce the RA-save slot naturally. The tested
null/identity guards either remain as real code or preserve the equivalence, so
the next probe needs evidence from the original data owner or sibling source
pattern rather than a synthetic guard.
