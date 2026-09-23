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
