# Round 42: `town/func_8080E59C`

## Verdict

Bounded negative. The registered `2.6.3-G0` baseline is exact at 167/167 words, but no tested aggregate reconstruction is exact. The strongest aggregate candidate is `candidate.c` at aligned distance 19 (167/167, 15 substitutions, 4 indels). It is evidence only and must not be landed.

The retail machine code does copy six consecutive words from the object's initial-state record to the object at `+0x78`. In the tested direct `Copy24` candidate, that copy remains one `mem:BLK` operation through `combine` and `sched`; in the exact pinned baseline source, the manually expanded copy is already six independent scalar operations in initial RTL. This comparison explains why this candidate allocates and schedules differently, but it does **not** expose retail RTL or establish the original C operation. The exact neighboring round-41 initializer `town/func_8080E838` reproduces a retail 24-byte copy from a `mem:BLK` assignment, proving that a late-expanded block copy can match retail in a different surrounding live-range graph.

For this candidate, the late block-move expansion chooses `$a0/$a1` as copy temporaries and defers helper argument formation. The target machine code instead forms `$a0/$a1` before the copy and uses `$a3/$t0` for its middle words. This is the concrete mismatch for the tested source shape; it is not proof that retail began as scalar C.

## Baseline and retail dataflow

- Source SHA-256: `3123c3ca5d9ee43ef3eb6de0084da7ba86f999cbb822bb07ed00fcd3438a7b04`.
- Recipe: registered `2.6.3-G0`.
- Baseline verification: exact, 167/167 words, total 0.
- The first child receives an internal initial-state record at object `+0x08`, a render record at `+0x0C`, a callback at `+0x10`, and a saved copy of the six-word initial state at object `+0x78`.
- Retail initializes source words 0, 1, and 2, loads all six source words, and stores them at object offsets `0x78..0x8C`. The first four source loads occupy `$v0`, `$v1`, `$a3`, and `$t0`; the last two reuse `$v0/$v1`.
- Before those loads, retail forms helper arguments `$a0 = object + 0x2C`, `$a1 = object + 0x78`, and `$a2 = D_805300DC`. The shared-state store to object `+0x74` fills the helper call's delay slot.
- The three later children use `$a0 = object + 0x28`, `$a1 = object_state`, and `$a2 = D_805300C4`.

## Helper and callback semantics

`func_8023FA58` has no registered definition in this tree, so its global ISO C prototype cannot be proven from source. Its machine code could not be located through the registered row/name data. Mapping `0x8023FA58` with this town row's recovered load delta led to non-code bytes in `TOWN_TOWN.BIN`, so the helper belongs to a different resident image or load segment whose mapping is not established here. The best local evidence supports a three-meaningful-argument hypothesis at these setup sites:

- Exact neighbor `town/func_8080E838` declares and calls it with three arguments after copying an `Initial24` record.
- In that neighbor, the copy initially puts source word 2 in `$a3`, but an intervening `func_8003BC18` call occurs before `func_8023FA58`. Since `$a3` is caller-saved, that source cannot rely on preserving the copied value as a fourth argument across the call. The target machine code explicitly forms only `$a0..$a2` immediately before the setup call.
- Other reconstructed town sources use three, four, variadic, and unprototyped declarations. Those declarations show repository-wide prototype debt; they do not establish a fourth argument.

The values left in `$a3` at this target's two setup calls are consistent with incidental liveness: source word 2 for the first child and the render-record pointer in the loop. The neighbor and clobbering-call evidence support that local interpretation, but do not prove the helper's complete ABI or that every call site has only three semantic arguments. Applying the local three-argument hypothesis improved the direct aggregate candidate from distance 23 to 19, but did not make it exact.

The callback field at object `+0x10` is heterogeneous across the group. `D_80529AC4` resolves to the three-argument `func_80529AC4`; `D_8052AE20` resolves to the three-argument `func_8052AE20`; `D_8052A0A4` resolves to a larger one-argument game update function. This supports treating the field as an engine callback slot rather than imposing one invented function type on all objects. No direct C caller of `func_8052919C` was found in the registered town/main source set, so its registration or table-driven invocation remains unsupported rather than diagnosed.

## Bounded probes

The four pre-dump whole-operation probes were:

1. Direct `Copy24` assignment, nonvolatile source word, retained four-argument helper spelling: distance 23, 168 generated words. It reloaded source word 2 for `$a3` and formed `$a0/$a1` after the copy.
2. Keep source word 2 in an ordinary local across the copy: distance 60. Since the source word had just been assigned zero, GCC propagated the constant and changed allocation throughout the function.
3. Use the struct-assignment result's word 2 as the fourth call expression: distance 23. GCC reloaded the destination word after the block copy.
4. Move the independent shared-state store after the call in C so it could fill the delay slot: distance 22. The source-word reload remained.

The dump then showed the `mem:BLK` versus scalar-RTL distinction above. A nonvolatile integer/pointer-union scalar probe scored 31 and also propagated the just-stored zero, so type punning did not supply a real replacement for `volatile`.

After the helper audit, two predicted three-argument aggregate probes were allowed:

1. Direct six-word assignment plus three-argument helper calls: distance 19, 167/167 words.
2. The same assignment through the already-named `saved_state` destination pointer: distance 19 with the same residue. GCC canonicalized it back to the same block move and still formed `$a0/$a1` afterward.

The remaining distance-19 residue is concrete:

- The candidate loads `object_state` into `$t0` and `render_part` into `$a3` where the target first emits `addiu $a0, object, 0x2C` and `addiu $a1, object, 0x78`.
- The target then loads `object_state` into `$t1` and `render_part` into `$a3`. The candidate has already performed those loads.
- During the copy, the candidate uses `$v0/$v1/$a0/$a1` for source words 0 through 3; the target uses `$v0/$v1/$a3/$t0`. The last two words use `$v0/$v1` on both sides.
- The candidate emits the two helper-address `addiu` instructions after the copy. The target emitted them before it. Both outputs remain 167 words; this is register-role and instruction-order residue rather than an added operation.
- The earlier `$t0` choice propagates into the loop: the candidate holds `object_state` in `$t0` and moves it to `$a1`, while the target uses `$t1`. The retained loop keeps otherwise preserve the existing loop shape.

## What remains

The direct aggregate is semantically credible and works exactly in the neighboring `func_8080E838`, but the tested aggregate forms do not reproduce this row's target instruction order and register roles. The pinned-baseline dump only explains that tested mismatch; it cannot identify retail's pre-scheduling representation. Landing the candidate would trade three first-child pins for a 19-point mismatch while leaving the three loop keeps in place.

A future pass should start from the target's six-word machine-code ordering and the observed behavior of these tested C shapes. It would need evidence for a real source-level alias or operation that prevents propagation of the just-stored zero while naturally producing the six transfers and early helper-address formation. Adding another volatile access, fixed register, empty asm, arbitrary flags, or a comma-expression scaffold would only rename the existing pins and is not supported by the semantics found here. The three loop keeps also remain in `candidate.c`; removing them cannot repair the already divergent first-child region and was not pursued after the aggregate hypothesis failed.
