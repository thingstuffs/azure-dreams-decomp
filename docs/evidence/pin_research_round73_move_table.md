# Round 73 harvest: MOVE TABLE from the four-model wave (2026-09-23)

Source: every `base/out` pair with fewer pin sites in `out/` across the lanes under
`work/native_lane/` named `r73_*` / `r74_*` that had `last_message.txt` when the harvest looked
(02:50-03:40 UTC): **50 rows, 110 pin sites removed**.  Pin counts are
`pin_census.sites_of(base) - sites_of(out)` on the lane's own `base/<id>.c` and `out/<id>.c`.
Where one row mixes moves the pins are SPLIT macro by macro and every entry says so.

| lanes read | model | rows | pins |
|---|---|---|---|
| r73_astra_a1 / a2 / h1 / h2, r74_astra_a1 / a2 / a4 | astra | 19 | 45 |
| r73_opus_a1 / s1 / a2 / s2 | claude-opus-5-5 | 16 | 38 |
| r73_luna6_a2 / a6 / s1 / s3 (a1, a3-a5, a7, a8 finished with no out) | gpt-6-luna | 8 | 15 |
| r73_sol6_a1 / a7 / a8, r74_sol6v3_a1 / a2 (a2-a6, h1-h3 no out) | gpt-6-sol | 7 | 12 |

NOT read (no `last_message.txt` yet): r73_opus_a3 / a4 / h1 / s3, r73_luna6_s2 / s4-s6, r74_astra_a3 / a5-a8 /
pre1 / pre2, r74_sol6v3_a3 / a4.  The earlier harvest's `r73_h_t101_*` / `r73_h_t102_*` / `r73_h_t71_*` are
gen_drive lanes (09-22), not model lanes.

The rule sentences are quoted from each lane's `REPORT.md` (`**Generator rule:**` under the row).
"Owner" results are gen_drive runs of the owning generator on the lane's PRE-landing text
(`--base-from <lane> --only <id>`, lanes `work/native_lane/r73_h_probe_*` and `r73_h_probe2_*`).

| # | move | pins | rows | models (rows) | owner today | verdict | recurs |
|---|---|---|---|---|---|---|---|
| 1 | read-modify-write / statement granularity: `v++; LV = v;` folded (`LV = v + 1`, `v = LV++`, store after the load), scalarised field blocks folded to compound updates, a temp read only once written at its use | 19 | 8 | astra 2, opus 2, sol 2, luna 2 | t100_rmwfold (refuses both probes: "no scalarised read-modify-write"), t94 | detector gap -> **BUILT t107_incstore** (the increment spelling, 7 pins / 3 rows) | r67 D, r71 D+E, r72 #5 (t100) - **all four rounds** |
| 2 | a dead local's / dead PARAMETER's storage reused for a later value (the merge), incl. same-register block masks merged | 18 | 10 | astra 8, opus 1, luna 1 | t66, t93, t101, t87/t90 | t66 DETECTOR BUG (binary `&` read as address-of) -> **t66 extended (T66_BINARY_AND)**; dead-parameter reuse for call results/constants NOT built | r67 B, r71 B, r72 #1 - **all four rounds** |
| 3 | pinned parameter copies dropped, the parameter read directly (plus a statement permutation) | 14 | 5 | astra 2, opus 2, sol 1 | t69_prologue (d26 on the exemplar), t42 | menu gap (no statement move) -> **BUILT t103_dropsink** | new as a family (t69 since r31) |
| 4 | page value / page run spelled as symbols - every page of the run at once, a field access folded to its own symbol | 9 | 4 | opus 3, astra 1 | t29, t86 (d1), t59, t92, t97 | detector gap (unpinned second page) -> **BUILT t104_pagejoint** | r67 A, r71 C, r72 #3 - **all four rounds** |
| 5 | control-flow reshapes (one-offs): return block out of line, `i < n` guard, return per arm, exit test before the advance + `return 0`, if-ladder -> switch, zero defs on branch paths | 9 | 6 | astra 2, opus 2, luna 1, sol 1 | t73 (switch: miss), t48, t50 | one-offs - NOT BUILT | `$0` zero local: r67 I, r71 #9 |
| 6 | a FILE-SCOPE global register variable (`register T v ASM_REG("$n");` outside any function) made a local of its one user | 6 | 4 | **all four models, one row each** | none (no generator reads file scope) | new move -> **BUILT t108_globalreg** + **t106_nmpromote** (the NON_MATCHING-arm spelling) | new |
| 7 | the first statement of an if-arm hoisted above the branch (dup head / pure copy) | 5 | 4 | astra 3, opus 1 | t67 (hoist_tail only), t82 (sinks) | new move (t82's inverse) -> **BUILT t105_headhoist** | inverse of r67 F / r72 #9 |
| 8 | a pinned local declared at another width (or retyped in place) | 5 | 4 | astra 3, luna 1 | t37 (miss d5; "no pinned integer local" on a `register u16`) | t37 detector note - NOT BUILT | r71 #7, r72 #4 |
| 9 | m2c's signed pow2 division written back as `/ 0x1000`, inlined per consumer | 4 | 2 | opus 2 | t17_divpow2 (eligible on 1, miss) | menu gap (needs forward substitution) - NOT BUILT | new |
| 10 | parameter width changed with its locals (t98 shape) | 4 | 1 | opus 1 | t98_paramcell (miss) | menu gap - NOT BUILT (1 row) | r72 #2 |
| 11 | early-return inversion: the inactive flag returns first, barriers go | 4 | 2 | luna 2 | t105/t48 (refuse) | new - NOT BUILT (2 rows, one model) | new |
| 12 | value staged through a fresh local (before abs, `offset = i * 2`, a second carrier) | 3 | 3 | astra 2, sol 1 | t89, t91, t94 | one-offs - NOT BUILT | r71 #8, r72 #12 |
| 13 | shared carrier + `goto tail` -> one call per path | 2 | 1 | opus 1 | **t102_gotojoin reproduces 1 of 2** | stale sweep -> **t102 re-swept** | r67 F, r72 #9 |
| 14 | a symbol read as an absolute memory operand (via a staged pointer) | 2 | 1 | astra 1 | t99 (d4) | detector gap - NOT BUILT (1 row) | r72 #10 |
| 15 | a void function returns its last local (`$2` pin + keep) | 2 | 1 | opus 1 | t75 (refuses) | NOT BUILT (1 row) | - |
| 16 | a parameter passed to an unprototyped callee | 2 | 1 | opus 1 | t8 (refuses: not a PASSTHRU site) | NOT BUILT (1 row) | t8 family |
| 17 | `static __inline__` helper recovered | 1 | 1 | sol 1 (and inside astra's 81336AC0) | none | NOT BUILT (search space) | r67 G, r71, r72 #12 - **all four rounds** |
| 18 | shift pair written as the `(s16)` cast | 1 | 1 | astra 1 | t94 (inverse), t88 | one-off | inverse of r71 #4 |

Per model (pins / rows): astra 45 / 19, claude-opus-5-5 38 / 16, gpt-6-luna 15 / 8, gpt-6-sol 12 / 7.
Moves 3, 4, 9, 13 and 15-16 are opus-heavy (whole-function rewrites of small town/main rows); moves 2 and 7
are astra-heavy (bigger dungeon rows, one lifetime lever at a time); luna's wins are small local spellings
(1 x same-register merge, 2 x early-return inversion, 1 x file-scope carrier); sol's are the increment fold,
the switch and the file-scope carrier.

## Rows and splits

| row | lane | pins | split |
|---|---|---|---|
| dungeon/func_800995D0 | r73_astra_a1 | 1 | #12 |
| dungeon/func_80099EE4 | r73_astra_a1 | 1 | #18 |
| town/func_80819B14 | r73_astra_a1 | 2 | #14 |
| town/func_8032CE94 | r73_astra_a2 | 4 | #6 1 (file-scope `dispatch_result` $2), #3 3 (forwarded-argument copies + keep) |
| town/func_8032FD1C | r73_astra_a2 | 1 | #12 |
| dungeon/func_8009BEB8 | r73_astra_h1 | 2 | #5 |
| dungeon/func_80BC1528 | r73_astra_h1 | 7 | #3 3 (saved_value/saved_duration keeps + $22), #2 4 (host on `rounded_step_z`; saved_offset keeps + effect $18) |
| dungeon/func_800A172C | r73_astra_h2 | 1 | #8 |
| dungeon/func_80DE9000 | r73_astra_h2 | 2 | #7 1, #2 1 (dead parameter hosts the call results) |
| dungeon/func_81336AC0 | r74_astra_a1 | 4 | #4 (per-arm symbols through an inline helper for the shared tail) |
| dungeon/func_813385D8 | r74_astra_a1 | 4 | #1 |
| dungeon/func_80D68308 | r74_astra_a2 | 1 | #1 (the SPLIT direction) |
| dungeon/func_80D91070 | r74_astra_a2 | 2 | #8 1, #2 1 |
| dungeon/func_80FB1000 | r74_astra_a2 | 3 | #7 1 (narrow snapshot before the branch), #2 2 (dead parameters host the alloc code) |
| dungeon/func_80FB4C24 | r74_astra_a2 | 2 | #8 |
| dungeon/func_80FF3000 | r74_astra_a2 | 3 | #7 1, #2 2 |
| dungeon/func_80283F70 | r74_astra_a4 | 2 | #2 |
| dungeon/func_8028484C | r74_astra_a4 | 1 | #2 |
| dungeon/func_8028B18C | r74_astra_a4 | 2 | #2 1, #5 1 |
| dungeon/func_819A6800 | r73_opus_a1 | 4 | #2 2 (the two `$6` values merged), #3 2 (`self = param` copy dropped via `SELF`) |
| dungeon/func_819C04E8 | r73_opus_a1 | 2 | #7 |
| dungeon/func_819C0A6C | r73_opus_a1 | 4 | #3 |
| main/func_8000FB48 | r73_opus_a1 | 1 | #5 |
| town/func_80092AB0 | r73_opus_s1 | 2 | #4 |
| town/func_80097514, town/func_800977F8 | r73_opus_s1 | 2 + 2 | #9 |
| town/func_80098C08 | r73_opus_s1 | 2 | #4 1, #5 1 (return per arm) |
| town/func_8009A688 | r73_opus_s1 | 2 | #13 |
| dungeon/func_8187B8B0 | r73_opus_a2 | 4 | #10 |
| dungeon/func_81888810 | r73_opus_a2 | 2 | #1 (and the `% 32` idiom) |
| dungeon/func_81934C5C | r73_opus_a2 | 4 | #1 |
| main/func_80012848 | r73_opus_s2 | 1 | #6 (NON_MATCHING arm promoted) |
| main/func_800206C8 | r73_opus_s2 | 2 | #15 |
| town/func_8008E4F8 | r73_opus_s2 | 2 | #16 |
| town/func_8008E778 | r73_opus_s2 | 2 | #4 |
| dungeon/func_81327AE0, dungeon/func_81845068 | r73_luna6_a2 | 2 + 2 | #1, #2 |
| dungeon/func_81988C1C | r73_luna6_a6 | 2 | #5 |
| town/func_80956E6C | r73_luna6_s1 | 1 | #8 |
| town/func_8032BD34 | r73_luna6_s3 | 2 | #6 |
| town/func_8046A828 | r73_luna6_s3 | 2 | #1 |
| town/func_8046AAC4, town/func_804B8B48 | r73_luna6_s3 | 2 + 2 | #11 |
| town/func_8080C650 | r73_sol6_a1 | 1 | #12 |
| dungeon/func_80F89A94, dungeon/func_81875B38 | r73_sol6_a7 | 2 + 1 | #5 (switch), #17 |
| dungeon/func_80D3B9B0 | r73_sol6_a8 | 3 | #1 |
| town/func_800BE540, town/func_800C1D6C | r74_sol6v3_a1 | 1 + 2 | #1, #6 |
| town/func_80095984 | r74_sol6v3_a2 | 2 | #3 |

## The lanes' rules, per built move

**#1 (t107_incstore).**  gpt-6-sol, `func_80D3B9B0`: "APPEARS when a post-incremented narrow field is
written back before a call or when a field is loaded into a temporary only for an immediate comparison.
RESOLVES by storing the increment expression to the field and comparing the field directly in the
condition".  astra, `func_813385D8`: "APPEARS: keeps separate an unsigned counter load from a signed
conversion, and removal introduces a second signed memory load while a phase pin holds the increment late.
RESOLVES: express the genuine counter update at the load/store boundary, retaining the old value".  opus,
`func_81934C5C`: "rewrite the pinned block as compound `field += expr` statements in the sibling's order".
gpt-6-sol v3, `func_800BE540`: "folding the increment and placing each real store in its arm".

**#2 (t66 extension).**  gpt-6-luna, `func_81845068`: "APPEARS when identical fixed register masks are
declared in separate blocks and initialized to the same constant at their use sites. RESOLVES by lifting
one ordinary scalar to function scope".  opus, `func_819A6800`: "APPEARS: two ASM_REG pins with the SAME
register on values in different blocks of one function -> RESOLVES: merge them into one variable".  astra,
`func_80FF3000`: "reuse the consumed parameters for the actual allocation code and null-result value".
MEASURED: t66 refused `func_81845068` `address-taken` - its test read the ONE character before `&`, so
`(LOAD_U32(prim) & tag_mask)` was an address-of.  Fixed behind `T66_BINARY_AND` (default on);
`func_819A6800` stays `decl-unparsed` (a two-line initialised `register` declaration).  The dead-PARAMETER
reuse (astra, 5 rows) is not on any menu (t101/t66 pair locals only) - the next build in this family.

**#3 (t103_dropsink).**  opus, `func_819C0A6C`: "APPEARS: callee-saved ASM_REG pins on stack-argument copies
whose erase residue is a pure rotation of the $s-sequence among values with equal refs. RESOLVES: move the
last use of the values that should rank lower past the last use of the values that should rank higher (a
permutation of independent stores in one block), so live_length decides the order".  astra,
`func_80BC1528`: "keep the parameter in its long-lived role, host the short arithmetic on an already
multi-assigned later temporary".  gpt-6-sol v3, `func_80095984`: "using the parameter in the first call and
assigning the long lived alias at its first actual post-call use".

**#4 (t104_pagejoint).**  opus, `func_80092AB0`: "replace every page+offset in the same statement run with
the symbol (the t86 rule applied to all pages in the run, not just the kept one)".  Measured: t29 admits only
PINNED pages (`literal-def-not-pinned` on `callback_page`) and names the page, not the field symbol, in a
struct view; t86's best is listing distance 1.

**#6 (t108_globalreg, t106_nmpromote).**  gpt-6-sol v3, `func_800C1D6C`: "APPEARS when a file-scope `ASM_REG`
variable is used only by one function to hold a dispatch field. RESOLVES by declaring the value inside that
function in the scored arm and re-censusing nearby keeps".  opus, `func_80012848`: "`register T *p
ASM_REG("$2")` at file scope, reused for page constants ... RESOLVES: replace it with `&symbol` /
`symbol[index]` (the NON_MATCHING arm is often already this)".  gpt-6-luna, `func_8032BD34`: "removing those
register variables, passing the original argument directly, and merging the return values through a normal
local".  astra, `func_8032CE94`: "Make the result local/direct, name the returned object symbol".
15 rows of the pinned tree carry such a declaration; no generator read file scope.

**#7 (t105_headhoist).**  opus, `func_819C04E8`: "APPEARS: the same assignment written in both arms of an if
(or in one arm plus the fall-through) next to a pinned/kept copy of it. RESOLVES: hoist the common assignment
above the branch".  astra, `func_80DE9000`: "place the useful narrow copy just before the branch".

## Generators: exemplar checks and sweeps (staged, NOT landed)

| generator | built / extended | exemplar check (rows reproduced) | sweep lane | eligible | exact | pins |
|---|---|---|---|---|---|---|
| t66_sameregmerge | extended (T66_BINARY_AND) | 1/1 (81845068: 1 of the lane's 2 pins) | r73_h_t66_sameregmerge | 52 | 4 | 8 |
| t102_gotojoin | unchanged, re-swept on the 195 rows changed since its 09-22 sweep | 1/1 (8009A688: 1 of 2) | r73_h_t102_resweep | 148 | 8 | 8 |
| t103_dropsink | built | 1/2 (819C0A6C 4 of 4; 80BC1528 d14) | r73_h_t103_dropsink | 341 | 1 | 1 |
| t104_pagejoint | built | 1/1 eligible (80092AB0 2 of 2) | r73_h_t104_pagejoint | 36 | 0 | 0 |
| t105_headhoist | built | 2/2 (819C04E8 2 of 2, 80DE9000 1 of 1 hoist pin) | r73_h_t105_headhoist | 190 | 1 | 1 |
| t106_nmpromote | built | 1/1 (80012848 1 of 1) | r73_h_t106_nmpromote | 20 | 1 * | 1 |
| t107_incstore | built | 2/2 (813385D8 4 of 4, 80D3B9B0 2 of its 2 increment pins) | r73_h_t107_incstore | 34 | 1 * | 4 |
| t108_globalreg | built | 2/3 (800C1D6C 2 of 2, 8032BD34 1 of 2; 8032CE94 d4) | r73_h_t108_globalreg | 13 | 2 * | 3 |

\* the exact rows are the EXEMPLARS themselves (their lanes are not landed yet): t106 `main/func_80012848`,
t107 `dungeon/func_813385D8`, t108 `town/func_800C1D6C` and `town/func_8032BD34` - land the model lane's
candidate first (the luna lane removes 2 pins on 8032BD34 where t108 removes 1); the staged copies then
refuse on `base_sha`.  `dungeon/func_819611CC` is staged by BOTH t66 and t102 (1 pin each).
New pins beyond the lanes: t66 8 + t102 8 + t103 1 + t105 1 = 18 (17 distinct after the 819611CC overlap).

## Harvest 2 (Opus lanes, 2026-09-23)

Source: the lanes under `work/native_lane/` named `r73_opus_*` / `r74_*` that had `last_message.txt` at ~04:30Z and
were NOT read by harvest 1: r73_opus_a3 / a4 / a5 / a6 / s3 / s4 / s5 / s6 / s7 / s10 (claude-opus-5-5), r74_astra_a3 /
a5 / a7 / a8 / pre1 (astra), r74_sol6v3_a3 / a4 (gpt-6-sol) - **59 rows, 120 pin sites removed** (opus 74 / 38 rows,
astra 43 / 18, sol 3 / 3), `pin_census.sites_of(base) - sites_of(out)` per row.  r73_opus_h1 finished with no out/.
Not read (running when the harvest looked): r73_opus_a7 / a8 / s8 / s9 / s11-s15, r74_astra_a6 / pre2 - of these
a7, s8, s9, s11-s13, s15 and pre2 finished before the dedupe step (their out/ rows were used for the dedupe only;
their moves are for a third pass).  Rows mixing moves are split
macro by macro; a row can appear under two moves.  Owner results are gen_drive runs of the owning generator on the
lane's PRE-landing text (`--base-from <lane> --only <id>`, lanes `work/native_lane/r73_h2_<gen>_check`).

| # | move | pins | rows | models (rows) | owner today (measured) | verdict |
|---|---|---|---|---|---|---|
| H2 | parameter GROUP declared at the consumer's width, carriers folded or retyped (t84/t98 family, signature change) | 18 | 7 | opus 6, astra 1 | t98 miss (d2 8132B4C8, d20 8132E83C, d62 80FF9000; refuses 80E0D090/818F33BC); t84, t36 refuse or miss | **BUILT t110_paramfold** 4/7 |
| H3 | parameter used directly instead of a (pinned) local copy - REG_EQUIV halves its priority - plus a second move per row | 14 | 7 | opus 6, astra 1 | t69_prologue eligible on 6, exact on 0 ("no candidate exact"); refuses 80F3610C | compound (dup tail / `state++` / switch inline / lifetime split) - NOT BUILT; next = t69 composed with t102/t107 |
| H7 | a dead parameter / dead local hosts a later constant or value (harvest-1 "next build") | 12 | 10 | astra 8, opus 2 | none | **BUILT t112_deadhost** 1/4 (the 5 harvest-1 astra rows + 81059F68 b) |
| H8 | locals retyped narrow (s16 roll / u8 flag / u16 raw copy), with a guarded-modulus restructure | 11 | 5 | astra 3, opus 2 | t37 miss (d6 800C68F8, d3 800C85AC, d2 80AC7A30) | compound - NOT BUILT |
| H13 | control-flow reshapes: return inside the success arm (jump.c block swap), counted retry loop, do->goto loop, state switch | 11 | 5 | opus 3, astra 2 | t41 miss on 81326794 | one-offs - NOT BUILT |
| H12 | page / table spelled as the symbol (`SYM[i].f`, `SYM[off >> 1]`, drop the second `&SYM` region, pointer at first load) | 10 | 7 | opus 5, sol 2 | t104 refuses 81339F68 / 80BEE4EC | t86/t104 detector gaps, 7 spellings - NOT BUILT |
| H1 | a `void` function returns the pointer it leaves in `$v0` (`$2` pin + keep) | 7 (+2 h1) | 3 (+1 h1) | opus 2 (+1), astra 1 | t75 refuses (non-void only) | **BUILT t109_voidret** 4/4 |
| H4 | the join tail duplicated at the goto site / into both arms (raises refs before jump2 cross-jumps it back) | 7 | 6 | opus 3, astra 3 | t102 miss (d10/d7/d12), t82 miss / refuses 8028BAA4 | compound with H3, needs a priority screen - NOT BUILT |
| H16 | statement staging one-offs (loop-invariant set moved to its use, `for` update order, shifts through a scratch, pointer-deref read) | 7 | 7 | opus 4, astra 2, sol 1 | - | one-offs |
| H6 | surplus call arguments dropped to the callee's arity as the tree settles it (definition / majority prototype) | 5 | 3 | opus 3 | t76 refuses "no call with pinned fake arguments" | **BUILT t113_sibarity** 1/3 |
| H5 | `p = base + K; ASM_KEEP(p)` -> `p = base; p = (T)((u8 *)p + K)` / `base += K; p = base` | 4 | 3 | opus 3 | none | **BUILT t111_selfadd** 3/3 |
| H9 | do/goto-next loop -> `for (; i < N; i++)` with `continue` | 4 | 2 | opus 2 | t50 refuses "no counted do-while" | NOT BUILT: census over rows() = 27 pinned rows with a goto to the loop-tail label, 0 with a pin at the goto |
| H10 | `x = f() & M; x -= K; x = (s16)x;` folded into one expression | 3 | 2 | opus 2 | - | NOT BUILT: census 2 pinned rows |
| H11 | libgpu OT link as a `P_TAG` bitfield, masks local to the link block | 3 | 2 | opus 2 | - | NOT BUILT (2 rows, one lane) |
| H15 | `static __inline__` helper recovered | 3 | 2 | astra 1, opus 1 | - | search space (all rounds) |
| H14 | `x < 0` -> `x & 0x80000000` | 1 | 1 | opus 1 | - | one-off |

**The lanes' rules, per built move.**
**H1 (t109).**  opus, `func_81813774`: "APPEARS: a leaf `void` function whose pinned text is `register T *x
ASM_REG("$2") = param; ASM_KEEP(x);`, with the body storing through x (listing: a leading `move $2,$4`). RESOLVES: make
the function return the parameter (`return param;`, return type `T *`)."  opus, `func_8000FD60`: "give the function a
pointer return type and `return` the object that is held in `$sN`."  astra, `func_8067F5C4`: "test the natural
original-buffer return so result liveness preserves the copy and excludes `$v0` from the terminal address."
**H2 (t110).**  opus, `func_8132E83C`: "declare that stack parameter (and its siblings the row already narrows through
`sN held = param` locals) with the narrow type of the field it is added to (`s16`/`u16`). Fold the redundant held
locals."  opus, `func_8132B4C8`: "declare that parameter, and the sibling scalar parameters, as s16/u16 (the t84
narrow-parameter family), and use the parameter directly."  opus, `func_80FF9000`: "declare the parameters s32 and the
copies s16 (t84 narrow-param family, other direction)."  astra, `func_818F33BC`: "recover signed narrow
parameter/local interfaces and cast both operands at the actual HI destination sum".
**H5 (t111).**  opus, `func_8102F674`: "`p = base; p = p + K;` (the self-referential SET blocks the cse equivalence).
The same move applies to sibling rows dungeon/func_809753B0 and dungeon/func_80AC5958".  opus, `func_80285464`:
"rewrite as `p += k; q = (T *)p;` (or `q = p; q += k;`) when p is dead or reassigned before its next use."
**H6 (t113).**  opus, `func_80BEE4EC`: "call with the arity used elsewhere in the same TU and store through the symbol
(t76_arity + t86_symaddr jointly)."  opus, `func_80D40744`: "callee arity from a sibling TU's prototype removes keeps
on arguments cse would constant-fold."
**H7 (t112).**  astra, `func_80FF3000` (harvest 1): "reuse the consumed parameters for the actual allocation code and
null-result value".  opus, `func_81059F68`: "host `p` on an already multi-set local of the right register class (not
a fresh single-set local). The move defeats `birthing_insn_p`."  astra, `func_80087054`: "reuse that scalar for a
later real expression of compatible type".
**H3 (not built).**  opus, `func_80FB176C`: "use the parameters directly; the REG_EQUIV doubling halves their global
priority."  opus, `func_81031F30`: "write the tail out again at the goto site (a duplicated statement block, which
cross-jump merges) to add refs before flow. Screen the result with the priority formula."

### Harvest-2 generators: exemplar checks and sweeps (staged, NOT landed)

| generator | exemplar check (`r73_h2_<gen>_check`) | sweep lane | eligible | exact | pins |
|---|---|---|---|---|---|
| t109_voidret | 4/4 (81813774 2/2, 800206C8 2/2, 8000FD60 2/2 via the caller of the inlined helper, 8067F5C4 3/3) | r73_h2_t109_voidret | 526 | 0 | 0 |
| t110_paramfold | 4/7 (8132B4C8 2/2, 8132E83C 2/2, 80FF9000 2/2, 80FE1000 2/2; misses 80E0D090 d18, 80B9D094 d16, 818F33BC d6 - each needs its second move) | r73_h2_t110_paramfold | 208 | 9 (8 after dedupe) | 12 (10 after dedupe) |
| t111_selfadd | 3/3 (8102F674 1/1, 809753B0 1/1, 80285464 2/2 joint); sibling 80AC5958 already landed (only its page pin is left) | r73_h2_t111_selfadd | 44 | 4 | 4 |
| t112_deadhost | 1/4 (80283F70 2/2; 80FB1000 d16, 80FF3000 d19, 81059F68 d18) | r73_h2_t112_deadhost | 790 | 7 | 7 |
| t113_sibarity | 1/3 (80D40744 1 of 2 - the dropped-argument keep; 80BEE4EC d13 needs the symbol store, 80DE6884 d40 the aggregate copy) | r73_h2_t113_sibarity | 316 | 24 | 34 |

t109 finds no row beyond its exemplars (the four are landed or staged by their lanes); t112's exacts include a
five-row family (`base_gain`/`base_amount <- 0x8004` into a dead `$3` local, 818A4828 and siblings) and one uglier
spelling (town/func_800A5DA8: a colour constant hosted on a dead pointer parameter - a spelling trade).  t113's
arity index is the callee's own DEFINITION when a row defines it, else the strict-majority typed prototype; its
first sweep took ANY declared arity (26 rows, including minority prototypes such as `func_800498A0` at 2 of 4), so
the lane was re-swept `--fresh` with the tightened index.  The remaining zero-argument calls (`func_800352FC`,
`func_800A6D30`, `func_80069EF8`) go to callees whose own definition is `(void)` and byte-exact: the owner's PASSTHRU
ruling (09-22) makes those legitimate, but the file-local prototype is rewritten, so review them with the signature
changes.  t109, t110 and t113 change signatures: `info["signature_change"]` in the journals names the function for
the landing review.
Recorded, not staged (feedback-record-refused-evidence): the first t113 sweep found two rows byte-exact at a
MINORITY-prototype arity that the strict-majority rule now holds back - town/func_800A7E6C 3 -> 0 pins
(`func_80033CD8` 3 -> 2 arguments; typed prototypes 2 x2, K&R x22, no definition) and town/func_8046F730 5 -> 3
(`func_80019880` 1 -> 0; prototypes 0 x1, 2 x1, K&R x3).  Listing-exact but byte-inexact (rerun in the check lanes
after the sweeps, still misses - an assembler-level residue, not a gate misreport): t109 dungeon/func_80CC2828;
t112 dungeon/func_80088964, func_80CC2828, func_81323F78, slus/w_8004FAA4.
Dedupe (a model lane already holds an out/ candidate with <= the staged pin count): removed
r73_h2_t110_paramfold `dungeon/func_800B6B0C` (r73_opus_s12 holds it at 0 pins).

## Harvest 3 (late lanes, 2026-09-23)

Source: the lanes under `work/native_lane/` that finished after harvest 2 - r73_opus_a7 / a8 / s8 / s9 / s11-s27 / p1-p7
(claude-opus-5-5; s8 and p1 finished with no out/), r74_astra_a6 (astra), r74_sol6v3_b1-b6 (gpt-6-sol; b1 no out/),
r75_astra_p1-p6 (astra) - plus r74_astra_a7 / a8, which harvest 2 had already read (their 9 rows / 13 pins are re-listed
because their moves are the two largest families below).  r73_opus_s7 / s10 were harvest 2's and are not re-counted.
**126 rows, 227 pin sites removed** (`pin_census.sites_of(base) - sites_of(out)`); new beyond harvest 2: 117 rows /
214 pins.  One PRIMARY move per row (no macro split this time - the late rows mostly mix two moves; the row's second
move is named in the notes); the rule sentences are quoted from each lane's `REPORT.md`.  "Owner" results are gen_drive
runs of the owning generator on the lane's PRE-landing text (`--base-from <lane> --only <id>`, lanes
`work/native_lane/r73_h3_<gen>_check`).

| # | move | pins | rows | models (rows) | owner today (measured) | verdict |
|---|---|---|---|---|---|---|
| H3-1 | a value HOSTED / staged on an existing local that is dead there (a store's source, a parenthesised operand, a quotient back into its numerator, disjoint pointer roles merged) | 43 | 25 | astra 16, opus 9 | t112_deadhost 0/10 (misses d4-d202, refuses 7FFEA9D4), t87_lifetimemerge 0/5 eligible (refuses 6 "no consecutive-lifetime pair") | harvest 2's H7 continued (t112 was built for it and measures 0/10 here) -> **BUILT t117_stagehost** 3/7 |
| H3-2 | one local per role: a variable reused for unrelated values split (the short role ranks high, the long one keeps its $s) | 28 | 13 | opus 10, astra 3 | t89_lifetimesplit 0/5 (eligible on all five, miss) | compound (each row also needs a symbol / abs / width move) - NOT BUILT |
| H3-3 | conditional negate written as `abs()` INTO THE STORE (`field = abs(field)`) or from the copy's source, the freed temp re-hosted | 24 | 9 | opus 9 | t16 0/7 (6 miss, 1 refuses), t91 0/7 (5 miss, 2 refuse) | **t91 EXTENDED (T91_INLINE)** 3/3 of the simple rows; p2/p4/p5/p7 rows are compound |
| H3-4 | carrier local folded: `t = C; F = t;` -> `F = C;`, `t op= K; F = t;` -> `F op= K;`, the field re-read at its use, `h = x; USE(h)` -> `USE(x); h = x;` | 18 | 8 | opus 8 | t107_incstore / t100 (increments only), none for the rest | **BUILT t115_carrierfold** 3/7 |
| H3-5 | symbol / aggregate / typed-access spellings (one-word aggregate copy + symbol, typed computed-goto index, `((s16 *)&T)[i]`, constant-address read) | 18 | 12 | astra 6, sol 4, opus 2 | t86/t104 (not re-measured) | 8 spellings, <= 2 rows each - NOT BUILT (b6 80E9D000/80EA3000 are clone twins) |
| H3-6 | goto loop -> real loop (do/while, `for` + continue, indexed by the counter) | 16 | 8 | opus 5, astra 3 | t44_doloop_greedy 1/6 checked (81959E04 exact; 813284E4, 8096DB20 not run); t41/t41b/t41c/t50 refuse "no do-while/while loop" | t44 already covers the plain shape; the misses need a second move (invariant shortened, cursor -> index) - NOT BUILT |
| H3-7 | callee arity from the definition / sibling prototype (+ symbol store) | 15 | 6 | opus 3, astra 2, sol 1 | t113_sibarity 1/6 (800B4298 exact; 809F7320 d4, 800900F4 d3, 8009F8EC d15; refuses 3 "no call above a declared arity") | t113 stands; the refused three are callees with no typed prototype anywhere |
| H3-8 | parameters used directly vs local copies (REG_EQUIV doubling), incl. the spilled `$t` variable beside a volatile stack local | 14 | 6 | opus 4, astra 2 | t69_prologue 0/3 (miss) | compound (2^n screen + second move) - NOT BUILT; census: 42 pinned rows carry an `ASM_REG("$8".."$15"/"$24"/"$25")` and a `volatile` |
| H3-9 | control-flow one-offs (return at the barrier label, `status = K` at the first of two labels, early-return inversion, tail per case, void + drop returns) | 13 | 11 | opus 7, sol 2, astra 2 | - | one-offs - NOT BUILT (census: a barrier between two adjacent labels on 1 pinned row, dungeon/func_8008AFEC; a barrier right after a label on 11) |
| H3-10 | parameter declared at its narrow width, the register copy dropped (t84/t110 family) | 11 | 8 | opus 6, sol 2 | t110_paramfold 2/6 checked (80FB7000, 80FC3000 exact; s26 twins miss d22; 8009EF28 refused) - 3/7 with harvest 2's 800B6B0C; t84 refuses all 6 "no pinned s32 copy of an s32 parameter" | t110 stands (the s26 twins are s32->s16 on a flags parameter used as `& 3`) |
| H3-11 | inline helper / widened multiset temp | 7 | 5 | opus 4, sol 1 | - | search space - NOT BUILT |
| H3-12 | statement permutation | 5 | 4 | opus 4 | t72_stmtperm refuses 3/3 "no pin inside a run of simple statements" | t72 detector gap (the pin sits on a declaration) - NOT BUILT |
| H3-13 | `void` function returns its `$2` pointer / parameter | 7 | 3 | opus 2, astra 1 | t109_voidret refuses 80476EA0 and 800A2988 "no pointer parameter or pinned pointer copy in a void function" | t109 extension candidate (a `= &SYM` initialiser; a scalar parameter): 2 rows - NOT BUILT |
| H3-14 | `p = base + K` self-add / hoist (t111) | 4 | 4 | opus 4 | t111_selfadd 1/3 (80B91054 exact; 800ACC98 d14; 8081C978 refused) | t111 stands |
| H3-15 | `register zero ASM_REG("$0")` -> the literal (`x != 0`) | 1 | 1 | opus 1 | none | **BUILT t114_zeroreg** 1/1 (census: 10 pinned rows) |
| H3-16 | stale pin whose NON_MATCHING arm is already exact (the pin at FILE scope) | 1 | 1 | opus 1 | t106_nmpromote refused "no pin in a matching arm" | **t106 EXTENDED (T106_ANYARM)** 1/1 - the NON_MATCHING census |
| H3-17 | P_TAG `addr:24` bitfield for the OT link (+ harvest-2 s3 rows) | 1 (+3) | 1 (+2) | opus | none | **BUILT t116_ptaglink** 0/3 - NOT SWEPT |
| H3-18 | signed magic division -> `/ 10` | 1 | 1 | opus 1 | t17_divpow2 (pow2 only) | one-off |

**The lanes' rules, per built / extended move.**
**H3-1 (t117).**  astra, `func_8081FCE0`: "APPEARS: a fence separates a pointer-sized store producer from a later scalar
producer, and a compatible local already carries the later value. RESOLVES: host the earlier real store value on that
local too, so its overwrite has the required output/anti edges".  astra, `func_80087054`: "reuse that scalar for a later
real expression of compatible type, and retain only variants whose scheduler ready list loses the birthing boost".
opus, `func_7FFEA9D4`: "host a later, disjoint-lifetime value that already lives in that register (here the post-loop
pointer) on the same variable".  opus, `func_800A8698`: "host the pinned value on an earlier single-block temporary that
already sits in the same register (the unk_14 update), and write the arithmetic in place (`x -= a; x /= b`)".  astra,
`func_81856800`: "Merge the equivalent pointer scopes and reuse the disjoint short role in its existing saved pointer".
**H3-2 (not built).**  opus, `func_8199AAD4`: "give each role its own local. global.c then ranks the short-lived role
high and lets the long-lived one reuse its callee-saved register".  opus, `func_80E8F178`: "give the second life its own
local initialised with the whole expression (`y = b - K`), so the first life dies once".
**H3-3 (t91 T91_INLINE).**  opus, `func_810AF0B4`: "`field = abs(field)` inline stores (t91-style), then re-host any
other use of the freed abs temporary on a same-typed local that already owns the right register (scan all in-scope
locals)".  opus, `func_809CB224`: "`base->f = abs(base->f)` in place; then, if a block-local temp elsewhere loses its
global status, host it in an existing global local of the same kind".  opus, `func_8008EFF8`: "`r = abs(<x's source
expression>)`, with no staging local".
**H3-4 (t115).**  opus, `func_81892C5C`: "APPEARS: `t = C; field = t; KEEP(t); ...; t |= K; field = t`. RESOLVES: `field
= C; ...; field |= K`."  opus, `func_800C0848`: "APPEARS as a keep between `x = load; y = x; f(y)`. RESOLVES as `f(x); y =
x;`."  opus, `func_818B7264`: "store from x first, then copy to the home."  opus, `func_800BF718`: "`field += K;` (or
`-=`) after the other stores".  opus, `func_81886800`: "read the field again in each consumer (`G += F; w = F + (F >>
k)`)".
**H3-15 (t114).**  opus, `func_80096134`: "APPEARS: `register T zero ASM_REG("$0")` used as a comparison operand.
RESOLVES: the literal comparison (`x != 0`)."
**H3-16 (t106 T106_ANYARM).**  opus, `func_819AE2AC`: "APPEARS: a row with `#ifndef NON_MATCHING` pin arms whose `#else`
arm is plain C. RESOLVES: compile the `#else` arm as the scored arm first; if it is exact, move it into the scored arm
and keep the preprocessor structure."
**H3-17 (t116).**  opus, `func_818D4800`: "rewrite the link as a 24-bit `addr` bitfield copy (P_TAG setaddr/getaddr), so
the mask's pre-combine reference count rises. If the pointer still outranks it, drop that pointer's duplicated arm
reads."

### Harvest-3 generators: exemplar checks and sweeps (staged, NOT landed)

| generator | built / extended | exemplar check | sweep lane | eligible | exact | pins | top refusal |
|---|---|---|---|---|---|---|---|
| t106_nmpromote | extended (T106_ANYARM: a split whose matching arm holds no pin is promoted too - the pin can be the orphaned file-scope register block) | 1/1 (819AE2AC 1/1, `nm:2`) | r73_h3_t106_nmpromote | 57 | 0 | 0 | "no NON_MATCHING split inside a function" 852 |
| t91_absfresh | extended (T91_INLINE: abs into the sole store / from the copy's source, re-host variant; listing-exact candidates ranked first) | 3/3 (810AF0B4 1/1 via `inline-joint-host=target`, 809CB224 1 of its 1 abs pin via `host=action_status`, 8008EFF8 1/1) | r73_h3_t91_absfresh | 54 | 5 | 5 | "no conditional negate with a single producing assignment" 857 |
| t114_zeroreg | built | 1/1 (80096134 `zero:fold`) | r73_h3_t114_zeroreg | 8 | 2 (1 after dedupe) | 2 (1) | "no `register ... ASM_REG("$0")` local" 903 |
| t115_carrierfold | built | 3/7 (81892C5C 1/1, 818B7264 1/1, 800C0848 1/1; 81886800 d11 needs typed direct parameters, 800C30E4 d14 needs t108, 800BF718 d3, 800B6D90 refused) | r73_h3_t115_carrierfold | 778 | 12 | 16 | 766 miss / 132 refused "no pinned carrier local with a store/re-read/use-first rewrite" |
| t116_ptaglink | built | 0/3 (818D4800 d30, 81910EC0 d4, 8182121C d24) | - (not swept) | - | - | - | - |
| t117_stagehost | built | 3/7 (8081FCE0 1/1 `SCHED_BARRIER:value<-rhs`, 80087054 1/1 `KEEP_NV:initial_state<-rhs`, 7FFEA9D4 1/1; 80094C70 d4, 8009DB44 d2, 80813368 d34, 80615500 refused) | r73_h3_t117_stagehost | 683 | 34 | 34 | 649 miss / 227 refused "no fence/keep with a dead local to stage a neighbouring value on" |
| clone_transfer | run over the 209 base/out rows of every r73_opus_* / r74_* / r75_* lane | - | r73_h3_clones | 38 siblings | 3 | 6 | 22 refused (hunk context does not align) |

Exact rows: t91 dungeon/func_80B452F8, 80B6F204, 80F0B2A8 (`host=action_state`), 80C412B4 (`host=move_kind`), 80D91070
(`host=action_counters`) - all the RE-HOST variant: the negate's temp goes into the store and its other role is renamed
to an existing local (a spelling trade).  t114 dungeon/func_800969CC (`return (void *)zero` -> the literal).  t115
town/func_8081AB48 (2 -> 0), dungeon/func_8009AE44, 800B5448, 80EDF000 / 80EF1000 (twins), 8184B130, 818B6AFC, 81917004
(3 -> 0), 8196096C, 8197CEC0, slus/w_8003D0F0 (10 -> 8), slus/w_80041284.  Clones: dungeon/func_8188E3A0 4 -> 2 (from
81888810, r73_opus_a2), dungeon/func_80BE5BA8 4 -> 1 (from 80BDFBA8, r74_astra_a3), dungeon/func_812A85D4 5 -> 4 (from
809A1A8C, r73_opus_a7).  t117 (34 rows, one pin each; the host is named in the step): town/func_800C0538,
800CF814, 80468560, 8046BD98, 8046C280, 8080DAB8, 8081FF68, 809534F8; dungeon/func_80088FA0, 800AAF90, 800AB7F0,
800C5448, 8028906C, 80921B2C, 80AC55DC, 80C96F24, 80CC266C, 80CE7A1C, 80CE9758, 81087818, 813236DC, 8132B8AC,
81339D2C, 8181B3E8, 8185D488, 818632E4, 818694D4, 81892C5C, 818B6AFC, 81917004, 81977584, 8197C800; slus/w_8003E39C,
w_80055ADC - 20 at a fence (the store's source staged on the local assigned next), 14 at a keep / register pin (a
later computed value staged on the pinned local after its last read).  dungeon/func_818B6AFC and func_81917004 are
staged by BOTH t115 and t117 (81917004: t115 3 -> 0 beats t117 3 -> 2; 818B6AFC one pin each, different pins) - land
one, re-sweep the other.  Several t117 rows (80088FA0, 800AAF90, 800C5448, 818632E4, 81892C5C, 8081FF68) are rows a
model lane solved partly tonight: t117 takes a further pin off the landed text.
**t44 re-sweep** (it reproduced 81959E04 above): r73_h3_t44_doloop_greedy, 95 eligible, 1 exact -
dungeon/func_81912154 21 -> 19 (`doloop:scan_distances`).
**Already landed.**  The orchestrator's landing loop took the r73_h3 lanes while this harvest ran (src/ byte-identical to
the staged copy at ~07:35Z): t91 80B452F8 / 80B6F204 / 80C412B4 / 80D91070 / 80F0B2A8, t114 800969CC, and the check-lane
copies of model-lane rows (t110 80FB7000 / 80FC3000, t114 80096134, t115 800C0848 / 818B7264, t91 8008EFF8).  The
remaining out/ copies of those rows refuse on `base_sha`.
**The NON_MATCHING census (T106_ANYARM).**  99 pinned rows mention NON_MATCHING; 59 have a split inside a function body
(57 promotable, 2 "no promotion removes a pin"), 40 only at file scope or in a non-body block.  Promoting every body
split (jointly and singly, raw asm spelled as the pin macros, orphaned file-scope register blocks dropped) is exact on
**none** beyond the exemplar - which had already landed when the sweep ran.  Nearest: town/func_80096134 d2 (t114 took
it), town/func_8032C8B8 d3, town/func_8009F654 / func_8032BD34 d7.  The "cheapest win" is spent.
**Dedupe** (a model lane holds an out/ candidate with <= the staged pin count): removed r73_h3_t114_zeroreg
town/func_80096134 (r73_opus_s20 holds it at 0).
**Not built.**  H3-2 (role split; t89 0/5 - every row also needs a symbol, abs or width move), H3-8 (2^n direct/copy
screen; t69 0/3), H3-5 / H3-9 / H3-11 (spellings and one-offs, <= 2 rows each), H3-12 (t72 refuses on a pin that sits
on a declaration - a detector note), H3-13 (t109 extension: 2 rows).  t116 is built and tested but reproduced none of its
three exemplars (the lanes also moved the masks into the link block / dropped duplicated arm reads), so it was not swept.
Naming: the t91 exemplar re-check after the ranking fix is in `r73_h3_t91_absfresh_check2` (the first check lane holds
the pre-extension misses).
