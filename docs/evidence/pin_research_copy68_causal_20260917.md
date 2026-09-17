Working paths in this snapshot refer to `work/native_lane/r42_copy68/`.

# Record68 scratch-allocation cause

## Result

The automatic CDK control is causal at the compiler-source level. For this 68-byte aggregate copy, GCC 2.8.1 does **not** defer the four `movstrsi_internal` scratch operands because its `o` memory constraint fails or because the scratch list is full. It defers their representation in the instruction because `local-alloc.c` changed how a successful scratch assignment is recorded.

GCC 2.7.2/CDK mutates the original instruction operand in place:

```c
PUT_CODE (qty_scratch_rtx[q], REG);
REGNO (qty_scratch_rtx[q]) = qty_phys_reg[q];
```

Consequently the CDK `.lreg` dump already contains hard clobbers `$v0/$v1/$a0/$a1`. Those hard clobbers participate directly in the following allocation stages, so the source, destination, and end pointers avoid them and become `$a2/$a3/$t0`.

GCC 2.8.1 instead replaces only the allocator's side-table entry:

```c
qty_scratch_rtx[q] = gen_rtx (REG, GET_MODE (qty_scratch_rtx[q]),
                              qty_phys_reg[q]);
scratch_list[scratch_index++] = qty_scratch_rtx[q];
```

It does not rewrite the `SCRATCH` node in the instruction at this point. The 2.8.1 `.lreg` dump therefore still exposes four `SCRATCH` operands. The global pointers are colored first as `$a1/$a2/$v0`; the later register/reload path resolves the remaining scratch operands as `$a3/$t0/$t1/$t2`, visible in the saved `.greg` dump. This source change explains the stage shift and the resulting register partition without a C perturbation or patched compiler.

## Trusted 2.8.1 observation

One completed debugger-controlled 2.8.1 compile is retained in `debug_281/`. Its normalized assembly equals the ordinary control compile. At both block-move instructions it recorded:

- `scratch_list_length = 15`.
- Scratch counters before operands 4 through 7 were `0..3` for the loop copy and `4..7` for the tail copy; every `counter < length` test was true.
- `offsettable_nonstrict_memref_p` returned 1 for both `o` memory operands of each instruction.
- `constrain_operands(code=201, strict=0)` returned 1 and selected alternative 0.
- `alloc_qty_for_scratch` proceeded past its class check for all eight operands, creating all eight scratch quantities.

Thus the `Ro` to `o` machine-description change is real but not the cause here, and neither is `scratch_list_length` exhaustion.

## Saved-pass evidence

- `raw/cdk_dumps/aggregate.c.lreg`: CDK has already rewritten the four loop and four tail scratches to hard registers `$v0/$v1/$a0/$a1`.
- `../r40_copy_transfer/candidates/evidence/b0994_v1_dumps/func_800B0994_v1.c.lreg`: 2.8.1 retains four `SCRATCH` operands at both copies.
- The corresponding 2.8.1 `.greg` dump contains `$a3/$t0/$t1/$t2` scratch clobbers after the pointers have become `$a1/$a2/$v0`.
- The recorded pointer pseudos and lifetimes are otherwise the same across the two builds, as summarized in `SITE_MAP.md`.

## Limits

The trusted run directly proves constraint acceptance, capacity, and scratch-quantity creation in 2.8.1. It did not instrument every `find_free_reg` attempt, so it does not independently replay each later hard-register choice. The hard choices and phase boundary come from the retained exact pass dumps. The compiler-source difference proves why the original instruction is rewritten during CDK local allocation but left as `SCRATCH` by 2.8.1.

An attempted CDK debugger command setup stopped at its first breakpoint before producing a complete compiler output, so it is not used as trusted evidence. CDK's completed saved `.lreg` dump and the 2.7.2 source are sufficient for the in-place-mutation side of the comparison.
