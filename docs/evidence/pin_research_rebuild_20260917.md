> Research checkpoint, 2026-09-17. Experiment paths below are relative to
> `work/native_lane/r39_rebuild`. This snapshot preserves findings and unresolved
> next experiments; ongoing lane work may add newer results.

# r39 whole-function reconstruction: dungeon/func_8180B064 (sol)

This lane applies `az-wall-deconstruct` before `az-c-rebuild`, plus Steps 0–3 of `tools/learnings/hard_gap_playbook.md`. It was executed by a Sol collaboration-runtime agent. The pinned C is diagnostic evidence, not proof that its pins are necessary.

## Identity and comparison contract

The clean row database (`ledger/rows.jsonl`) maps synthetic row ID `dungeon/func_8180B064` to retail file offset `0x182B064`, size `0x6B8` (430 words), end `0x182B71C`, and true symbol `func_80026864`. The overlay result records synthetic address `0x8180B064`, so the sweep naming base is `0x7FFE0000`; the true name maps the same file bytes with load base `0x7E7FB800`. Candidate C defines `func_80026864`. All byte comparisons must therefore slice `[0x182B064,0x182B71C)` and link/label that slice at `0x80026864`; the synthetic name must not be treated as a retail address.

The recorded baseline recipe is `2.7.2-cdk-G0`. The first retail fingerprint reports one compiler-split global store and three compiler-filled call slots, yielding `cdk/2.8.x-family` and rejecting a claimed plain `2.7.2-family`. This is a lineage question, not yet a recipe change: baseline scoring remains at the row recipe, and any isolated lineage scores will be recorded separately with their C shape.

## Rubber-duck decision record before synthesis

The function initializes a render scratch area, iterates a 3x3 cell grid, constructs four packed terrain vertices for every face, projects/emits visible primitives, temporarily replaces the view transform to draw objects, then restores the transform.

The compiler decisions in the six pin clusters are:

1. In the four-vertex staging region, it must assign several simultaneously live vertex pointers, x/y halves, height values, the cell bias, and packed xy words to caller-saved registers. Pseudo creation order comes from declaration/use order; overlapping pointer and scalar lifetimes create global allocnos; assignments such as pointer-to-y reuse merge otherwise separate ranges. The retail choice requires the fourth vertex's height load/subtract to finish before independent fourth-y packed-coordinate work. The current pin changes ready-list or dependency order rather than semantics.
2. `vert3_ref_y` currently carries a vertex pointer and then the signed y value. That reuse feeds three pin sites and rotates `$t0/$t1/$t2` coloring. Retail could arise naturally from a different real reuse: a programmer may have used one scratch integer for successive indices/addresses, or four short-lived `Vert *` pointers with scalar fields read immediately, changing pseudo/LUID order without any artificial dependency.
3. `xy13` is an explicitly masked x coordinate kept separately from the final packed word. Whether it remains its own pseudo depends on an embedded assignment or declaration/use order (`xy1 = (x = v->x + cell_x) & 0xffff`) rather than on the mask spelling alone.
4. The late `vertices` keep makes the early mesh base live across unrelated object drawing. Retail's equivalent long range could come from ordinary 1997 C variable reuse: the same pointer local may later serve as the object-slot cursor, or a convenience base may remain syntactically live until a later assignment. A natural reused local can shift the callee-saved allocation without a fake use.

What would have to be true in the original source: the four vertex records were probably addressed as typed pointers or as one repeatedly reused pointer/index temporary; fields were consumed close to each pointer construction; at least one assignment was embedded in a larger expression; declaration order differed from consumption order; and a general pointer/int temporary may have been reused in the later object pass. Those ordinary idioms can create the observed allocation and scheduler dependencies without pins.

Plausible source hypotheses, to test only after the retail site map is complete:

- Four typed `Vert *v0..v3` locals, each with pointer lifetime ending after x/y/height extraction.
- One `Vert *v` convenience pointer reused successively for vertices 0–3, with fields parked in `int` locals.
- Pointer variables declared in face-index order but initialized in the retail load order.
- Embedded assignments for masked x and packed xy values, matching pseudo creation order.
- Height/bias subtraction written directly into the scratch store versus parked in a signed `int` or `s16` local.
- One general pointer reused after terrain emission as the later object cursor, naturally bridging the otherwise dead `vertices` interval.
- Declaration order intentionally different from use order, especially fourth-pointer/fourth-y versus first-height temporaries.

No candidate synthesis or score iteration starts until the complete 430-word retail register-role, access-form, live-range, and emission-order map is recorded below.

## Retail site map

The entire 430-word slice was extracted from `DUNGEON_DUNGEON.BIN` and read from `0x80026864` through `0x80026F18`; its SHA-256 is `2dbded65cef4122636038d538a719d1fa4c4d92a067333741ed3c0608038214`. The full listing is `evidence/retail_func_80026864.disasm`.

### Prologue and long-lived register roles

- Frame: `0x80`; saves `s0..s8` plus `ra`. `arg0` (`objects`) is spilled at caller slot `sp+0x80`; `arg2` (`render_params`) at `sp+0x88`; `arg1` begins in `s0` as `view_position` and that register is deliberately reused later.
- `s2`: constant scratch base `0x1F800000` from `0x800268C0` through the last object/sprite region.
- `s5`: vertex-array base loaded before the first call and held through all terrain loops (`0x800268A0`–`0x80026CFC`). It dies before object rendering; retail does not actually use it in the late object loop.
- `s3`: primitive pointer loaded at `0x80026984`; advances by `0x28` per emitted primitive and is finally written to render state at `0x80026D10`.
- `s1`: two unrelated roles. It first holds the `0x8008` page for the render-state load, then is overwritten with `prim + 3` at `0x800269E8` and advances with the primitive. This is real variable/register reuse.
- `s4`: current `Cell *`, initialized from `D_80027120 + cell_index*6` and advanced by six in the column-loop delay slot.
- `s6`: current `Face *`; `s0 = s6 + 22` gives convenient negative offsets to fields, and both advance by 24 at the face-loop back edge.
- `s7`: `cell_x`, starts at `-96`, advances by 64 after each cell.
- `s8`: `cell_y`, starts at `-96`, advances by 64 after each row.
- `t6`: `cell_index*6`, kept across calls by spilling to `sp+0x50`; advances by six per cell.
- `sp+0x44/0x48/0x4C`: column, row, and cell-index counters. `sp+0x40` holds materials; `sp+0x30..0x3C` hold saved transform halves.

Gate 0 therefore requires exactly the `0x80` frame and `s0..s8` save set. A candidate whose prologue differs cannot be used to judge vertex scheduling.

### Four-vertex extraction and live ranges (`0x800269F0`–`0x80026B28`)

Retail stages values rather than maintaining four clean pointer locals:

1. Load `i0` and `i1`; form vertex-0 pointer in `v0` and vertex-1 pointer in `t2`. Consume vertex 0 x/y into packed `v1`, store xy0, then immediately consume vertex 1 x/y; `t2` changes from the vertex-1 pointer to signed y1.
2. Load `i2`, `i3`, and `i0` again. Form pointers in `v1` (v2), `t0` (v3), and `v0` (v0-height reload). This reload is evidence that pointer lifetime is intentionally short rather than a four-pointer source array.
3. Build packed xy1 in `t1`; consume v2 x/y into `t3/t5`, v3 x into `t4`, v0 height into `v0`, cell bias into `v1`, then consume v3 y into `t0`. At this point both `t2` and `t0` have crossed from pointer roles to scalar y roles.
4. Retail completes `height0 = v0->w - cell->bias` at `0x80026A84..90` before finishing xy2/xy3. It then completes packed xy2 in `t3`, masks x3 in `t4`, stores height0, reloads `i1` to obtain height1, finishes xy3 high-half work in `t0`, and emits scratch fields in interleaved order: `xy0`, `height0`, `xy1`, `height1`, `xy2`, `height2`, `xy3`, `height3`.
5. Height pointers are independently reconstructed from `i1/i2/i3`; retail does not retain the x/y pointers for height loads. Bias is reloaded for each height. These rematerializations are source-shape evidence, not inefficiency to clean up.

This directly rejects the initial four-simultaneous-pointer hypothesis. The promising reconstruction is staged typed access plus real pointer-to-scalar reuse or separate short scopes that create the same pseudo deaths and LUID order.

### Calls, control flow, and emission order

- Initialization calls occur in strict source order: `649A0`, `64B90`, `65820`, `64BC0`, `64CF0`, `64D80`, then `65420`. Retail fills the `64B90` and `65420` call slots with scratch stores.
- Loops are lexically terrain outer row → inner cell → face chain. The face-chain back edge advances `face` and `face+22` in separate instruction/delay-slot positions. Cell cleanup follows the face block, then column counters, then row counters.
- The projection call receives four scratch vertices, four primitive output addresses, and three scratch result addresses; `t6` is spilled across it. Visibility/depth/material/emission remains inside the face loop.
- Post-terrain emission order is: publish primitive pointer; snapshot and zero transform; install new rotation; optional main object; two-entry extra-object loop; optional sprite; restore position and rotation; final `64A40` call with the last restore store in its delay slot.

### Global/access-form map

- `D_8008333C`: one `lui/addiu` base, then two initial loads (vertices/materials); later face-table access rematerializes its base near the cell branch.
- `D_80083160`: initial page in `s1` for one render-state load; later regions rematerialize a `t7` base for state loads/stores, with a final held `t7` only across the six restore stores.
- `D_80027120`: full `lui/addiu`; current-cell pointer lives in `s4`, while the scaled offset remains in `t6`; cell cleanup rematerializes the symbol base.
- `D_8002713A`: compiler-split store, `lui a0,0x8002` followed later by `sh v0,0x713a(a0)`. This is the strongest cdk/2.8.x lineage signature.
- No `%gp_rel` references and no `$at` macro stores occur in the function.

### Provenance and lineage

The fingerprint saw one compiler-split store, three compiler-filled call slots, no macro stores, no held-page `s` bases, no split `la`, no return-copy, and no gp references. It reports cdk/2.8.x-family and conflicts with a `2.7.2-family` claim. The recorded `2.7.2-cdk-G0` exact baseline remains evidence that this repository's normalized pipeline can reproduce the bytes with pins; it is not a byte-signature attribution for the original compiler.

### Feature owners before reconstruction

| Feature | Evidence | Owner | Reachable route |
|---|---|---|---|
| Frame and `s0..s8` hold set | retail prologue/epilogue | C shape + allocator | reconstruct real long-lived roles; Gate 0 first |
| Vertex pointer/scalar rotations | `v0/t0/t2` role reuse and index reloads | C shape | staged typed extraction with real local reuse |
| Height0 before y3 pack | retail order at `0x80026A84..B0`; unpinned near miss reorders four words | C shape + sched ready/LUID | change source dependence/lifetime/order; inspect scheduler dumps if stalled |
| Late `vertices` color | `s5` dies after terrain despite candidate keep near objects | C shape/allocator | reuse a real source local across phases or reconstruct the actual short death |
| `D_8002713A` split store | allocated `a0` scratch and delayed store | cc1 lineage | isolated cdk/2.8.x experiment after natural shape exists |
| Filled call slots | three retail sites | scheduler/lineage conditioned on C | compare at attributed lineage; route dump-backed pass residuals to parent instrumentation |

## Feature ownership and reconstruction iterations

### Zero-pin control and compiler-cell receipt

Removing all six pins without otherwise changing the source produces a 430-word function with the exact retail `0x80` frame and exact `s0..s8` save set. At the recorded `2.7.2-cdk-G0` recipe it scores 35 substitutions plus 20 indels, total 55. All code outside three connected differences is positionally exact: the vertex base is colored `s4` rather than retail `s5`, the strength-reduced current-cell pointer is colored `s5` rather than retail `s4`, and words 104–172 use a different ready order/coloring in the four-vertex expression region. The cell pointer increment at word 288 is the tail of the same color reversal, not a separate feature.

The zero-pin control was also compiled at all nine recognized cells. Totals were: `2.7.2-G0` 366; `2.7.2-G0` without strength reduction 331 (426 generated words); `2.7.2-G0` without scheduling 391; `2.6.3-G0` 379; `2.7.2-cdk-G0` 55; `2.8.0-G0` 57; `2.8.1-G0` 57; `2.95.2` 426; `2.91.66` 445. The recorded CDK cell is therefore still the best tested recipe for the natural source, despite the conditional 2.8-family fingerprint. A recipe reattribution is not supported at this source shape.

The `greg` dumps isolate the callee-save decision. In the pinned diagnostic, global allocation order contains pseudo 354 before pseudo 88 and dispositions map 354 to register 20 (`s4`) and 88 to register 21 (`s5`). In the zero-pin control, pseudo 88 precedes 354 and maps to `s4`, leaving 354 in `s5`. RTL insn 18 identifies pseudo 88 as the vertex-base load from `D_8008333C+8`; pseudo 354 is the loop optimizer's strength-reduced current-cell pointer. The late diagnostic use expands pseudo 88 from 33 uses across 241 LUIDs and 10 calls to 34 uses across 292 LUIDs and 12 calls. That extension lowers/reorders its allocator priority sufficiently for pseudo 354 to claim `s4` first. The reconstruction question is consequently precise: what ordinary source reuse or lifetime makes the cell induction allocno precede the vertex-base allocno without changing the emitted post-terrain code?

`alloc_trace.py` reports that the depinned file has no `ASM_REG` sites; it cannot trace this keep-style priority decision. The retained `greg`/`lreg` dumps are the evidence for this decision. Existing instrumentation was used as far as its input contract permits; no duplicate allocator instrument was built.

### Mechanism-led synthesis results

All scores below use exact `verify.py` proof at `2.7.2-cdk-G0`. None is exact, so no candidate is published in `out/`.

| Candidate | Source hypothesis | Words / frame | Score | Decision |
|---|---|---:|---:|---|
| `natural_v0` | erase all pins, preserve inherited C | 430 / `0x80` | 55 | Control; exact hold set, wrong `s4/s5` assignment and vertex region only. |
| `typed_v1` | four simultaneously live typed `Vert *` locals | 443 / `0x98` | 358 | Refuted at Gate 0; creates extra global pointer allocnos and spills. |
| `region_diag_v2` | preserve late vertex-base diagnostic, remove five region pins | 430 / `0x80` | 98 | Diagnostic only; swaps scratch/primitive roles and does not naturalize the region. |
| `reorder_v3`, `decl_v4` | initialize or declare the cell base before geometry/vertices | 430 / `0x80` | 55 | Byte-neutral; front-end declaration/assignment order alone does not reorder the two loop allocnos. |
| `cellptr_v5`, `typed_cells_v7` | explicit typed `Cell *` for indexed field accesses | 421 / `0x78` | 269 | Refuted; collapses the retail induction/hold set and loses a saved register. |
| `cells_uses_v6` | route the four bias reads through the local cell-array base | 431 / `0x80` | 194 | Refuted; changes global address rematerialization and schedule. |
| `cell_induction_v8` | explicit `Cell *cell` advanced by `cell++` | 430 / `0x80` | 224 | Refuted; compiler chooses a different hold/spill structure even at equal length. |
| `reuse_v9` | reuse the vertex-base local as late sprite-data pointer | 430 / `0x80` | 61 | Real reuse changes allocation, but perturbs the already-exact sprite region and misses the retail priority. |
| `cell_offset_v10` | make `cell_index*6` an explicit source local | 417 | 154 | Refuted; inhibits the exact loop optimizer result. |
| `signed_height_v11` | preserve signed 16-bit subtraction explicitly | 430 / `0x80` | 55 | Byte-neutral after pin removal. |
| `reuse_vert2_v12` | one real local carries index-2, vertex-2 address, then signed y2 | 430 / `0x80` | 54 | Historical intermediate; supported staged reuse by improving the original control one point. |
| `reuse_xy_v13` | one local successively carries all xy1 intermediates | 430 / `0x80` | 170 | Refuted; over-merges ranges and rotates the whole caller-save set. |
| `signed_roles_v14` | type all three pointer-to-y role locals signed | 430 / `0x80` | 54 | Byte-neutral relative to v12; signedness is not the remaining lever. |
| `vertex_u8_v15` | model the vertex base as a raw byte pointer | 430 / `0x80` | 54 | Byte-neutral relative to v12; inherited `Vert *` qualification is not constraining this decision. |
| `reuse_object_cursor_v16` | reuse vertex-base local as later two-entry object cursor | 430 / `0x80` | 63 | Real reuse reaches into the right lifetime class, but changes retail-exact object-loop `s0/s1` roles. |
| `reuse_main_entry_v17` | reuse vertex-base local for the main-object entry | 430 / `0x80` | 59 | Refuted at Gate 0: save-role signal becomes 24/23. |
| `direct_bias_v18` | express height0 subtraction directly through the cell field | 430 / `0x80` | 54 | Byte-neutral; combine reconstructs the same RTL and scheduler freedom. |

The historical v12 positive showed that real staged reuse can change this region without changing frame or length. The later v20 result below supersedes it: vertex 2 remains split while vertex 3 alone is split into pointer and signed-y locals. The broad four-pointer rewrite remains structurally wrong.

### Current result and handoffs

Result is **UNRESOLVED**, not a floor or impossibility claim. There is no exact depinned candidate yet. `split_vert3_only_v20.c` is the current 430-word, unchanged-frame best reconstruction at total 33; historical v12 remains available as an allocation contrast. Neither is copied to `out/` because `verify.py` reports non-exact.

Every reachable remaining owner has a tracked route:

- C shape / vertex region: continue from v20's supported vertex-3 split while preserving the separate vertex-2 roles. Vertex-1 splitting and embedded assignment spellings are measured negatives; success criterion remains the retail word-104–172 map with the existing frame.
- Allocator / `s4,s5`: use the retained pinned/natural `greg` and `lreg` pair to explain why pseudo 354 must precede pseudo 88. The source route must alter a real reuse/lifetime while leaving words 295–429 exact; the object-cursor/main-entry experiments show which later roles cannot be merged.
- Scheduler: the concrete residual is the cell-bias load at candidate word 122 versus retail word 137, with height0 subtraction at retail words 136–139. Read ready-list/dependency dumps only after a source hypothesis predicts this move.
- Compiler lineage: rerun CDK/2.8 comparison only when a closer natural C shape exists. Current controlled sweep favors CDK 55 over both 2.8 cells at 57.
- Assembler: no assembler-owned residue is presently visible; all 430 words exist and positional differences begin in `greg`/scheduling. Track as inactive unless an exact compiler listing fails object-byte comparison.

The machine-readable owner handoff is `HANDOFF.json`.

### Updated staged-reuse result

The copied current base has SHA-256 `3cd53e5b2929f62e310788c4f18618c6d42412929b76ee413f0be0fbe8a5ec29`; the same value is recorded in `base/dungeon/func_8180B064.c.base_sha`. The decisive later experiment is `split_vert3_only_v20.c` (source SHA-256 `b19c4e3a6480cdd2208bb6119f3326f8696a61ca846f452ee72fd0fa6da24dd3`). It keeps the inherited separate vertex-2 pointer and y locals, but splits only vertex 3's pointer and signed-y roles. This ordinary typed-lifetime correction improves the fully depinned function from total 55 to **33** (29 substitutions, 4 indels), still 430 words with the exact retail frame/save set.

That result sharpens the reconstruction substantially. With vertex 3 split, retail and candidate now agree exactly on the three index loads at words 117–119, the vertex-2 and vertex-3 pointer constructions at 122–127 apart from the global `s4/s5` base reversal, all vertex-2/3 field-load sites at 133–138, y2/y3 high-half construction at 142–145 and 153/162, later packed stores at 163/167–168, and all height1–3 code after word 169 apart from the same base reversal. The remaining local differences have two sources:

1. Vertex 1 is one real pointer-to-y reused local, as retail requires, but the candidate colors that role `t1` while retail uses `t2`; this rotates only the packed xy1 registers through words 104–132 and the store at 154.
2. The candidate issues `addu/andi` for xy2 at words 139–140 before the height0 subtraction at 141. Retail performs the subtraction at 139 and issues the xy2 pair at 140–141. Candidate then stores height0 at 146 and masks x3 at 148, while retail masks x3 at 146 and stores height0 at 147. These are four ordering indels with an otherwise matching opcode multiset.

The global allocator observation remains independent and exact: zero-pin pseudo 88 (vertex base) is allocated before pseudo 354 (strength-reduced cell pointer), yielding `s4/s5`; retail requires pseudo 354 first, yielding `s4` for cell and `s5` for vertices. The late diagnostic use reverses precisely that order. The prediction is that the original source had one additional ordinary lifetime boundary or reuse that lowered vertex-base priority without merging it into the post-terrain object cursor; v16/v17 prove those two obvious later merges perturb already-exact `s0/s1` roles.

Additional probes after the first table: splitting vertex 3 on top of the v12 merged-vertex-2 model scored 52; splitting vertex 3 alone produced the 33-point result and supports different source lifetimes for the neighboring vertices in this reconstruction. Reusing the vertex-1 index and pointer as one source local scored 153 and is refuted; changing only vertex-1 signedness is byte-neutral at 33. Attempts to retain subsets of the old pins after the vertex-3 split score 35–138 because those diagnostics themselves extend the now-short pointer lifetime; they do not validate the reconstructed shape.

The next source experiment is an embedded height0 assignment/store shape that preserves the proven vertex-3 split and creates a real dependence or pseudo death between `subu height0,bias` and xy2 construction. Its prediction is limited to moving candidate words 139–148 into retail order without changing the exact word-117–138 access sites. After that local order is stable, the allocator route will address pseudo 88 versus 354 separately.

### Allocator trace and final mechanism probes

The existing tracer's underlying `observe` and `trace` APIs were run directly on v20; no new instrumentation was added. The trace reproduced the ordinary compilation exactly and reported no errors. Pseudos were rebound from this compilation rather than copied from an earlier dump:

- Pseudo 88 is v20's vertex base. It has 33 references, live length 241, crosses 10 calls, priority 6846, is global-order entry 10, and receives hard register 20 (`s4`). It has no hard or copy preference for `s4`/`s5`; `find_reg` chooses `s4` by global scan order.
- Pseudo 355 is v20's strength-reduced cell pointer. It has 27 references, live length 168, crosses 3 calls, priority 6428, is global-order entry 11, and receives hard register 21 (`s5`). Its attempt identifies `s4` as an **earlier-global-conflict**, with pseudo 88 as the sole recorded competitor (6846 versus 6428).

This replaces the earlier qualitative priority claim with measured inputs. To reverse the order naturally, source must lower the vertex priority below 6428 (at current refs, live length must grow from 241 to at least 257), raise the cell priority above 6846, or produce a relevant preference. The current source produces no preference. The pin's artificial late use grows the vertex range enough to reverse the order, but the tested real post-terrain merges also change emitted object-loop roles and are invalid reconstructions. The summary is retained in `evidence/alloc_trace_v20_summary.txt`.

The predicted height experiment did not move the residual. A signed cast, direct subtraction, direct scratch-field expression, function-local versus face-block locals, signed bias widths, embedded vertex-1 pointer/y assignments, and embedded xy1/xy3 masks all normalize to the same 430 words and score 33. Reusing the bias temporary as xy2 scratch creates the intended source anti-dependence but over-merges the range and scores 154; moving the scratch height store earlier scores 44. Moving the entire height source block earlier scores 156, showing that pseudo creation order destabilizes the global set before it repairs scheduling. Reusing one height local for all four vertices scores 46, and reusing one bias local for all four reloads produces 429 words and scores 44; retail's repeated bias loads and separate height ranges are therefore supported in this reconstruction.

The vertex-1 experiments are also resolved directionally. Splitting its pointer/y roles scores 168, while signedness and embedded assignments are byte-neutral at 33. Retail's shared `t2` role is thus supported as a single source lifetime, although the surviving `t1/t2` color swap remains unresolved. By contrast, the vertex-3 split is the strong positive because it aligns all of words 117–138 except the callee-save base register.

Cell-source and control probes did not supply the 418-point priority increase required by the trace. Direct typed `D_80027120[cell_index]` accesses, a typed cleanup pointer, and a pre-tested `while` spelling are byte-neutral at 33. An explicit cell local without using it for cleanup rotates the whole saved set and scores 50; using it through cleanup previously shortened the function to 421 words. An inner `for` loop compiles to 428 words and scores 41. These results rule out those specific routes while leaving other source shapes unresolved.

An evidence-backed lineage retry on v20 gives total 35 at both `2.8.0-G0` and `2.8.1-G0`, versus 33 at recorded CDK. Recipe reattribution still does not help the closest reconstruction.

The final status remains **UNRESOLVED**. v20 is the best zero-pin whole-function reconstruction and is retained only as a diagnostic control because it is not exact. No file is written to `out/`. The precise next handoff is to find an ordinary lifetime that changes the measured 6846/6428 global order while preserving the exact post-terrain region, then revisit the four sched2 order indels with that hard-register assignment fixed; the two effects may be co-adapted.
