# Shared state ownership for 45340 and 453E0

Two adjacent SLUS functions now share one real C definition of their zero-valued
state word, `s32 D_80081510 = 0`. The full executable matches retail, and genuine
ASPSX 2.79 matches all 573 function words with zero masked relocations. The GP
cohort falls from 34 to 32 remaining rows; total dependency records fall from
201 to 199. The production assembler is unchanged.

The existing recipe lander first moved the unchanged 45340 source from 2.8.1 to
2.7.2-cdk. The full-image check passed, charter rule 2 held, and the raw object
baseline remained byte-identical after rebaselining. The recorded trade is in
`ledger/sweeps/recipe_move_gp_81510.jsonl`. Both grouped members therefore use
their registered CDK recipe with empty flags; no private recipe override is
needed in production.

The shared header declares 453E0's actual function signature and forward `Entry`
type. The caller explicitly converts its integer second argument to the position pointer
and its node pointer to the callee's entry view at that call. Its node layout
and the callee's distinct entry layout remain separate. The callee removes only
the duplicate forward typedef. No pin, other operation, struct extent or field
meaning changed. This resolves the conflicting declaration without claiming that
the two views are one interchangeable C structure.

The owner object contributes four initialized `.sdata` bytes at `0x80081510`,
replacing exactly four raw bytes from asset 54240 at offset `0xAD0`. The
[production ownership receipt](gp_shared_state_81510_receipt.json) verifies the
section bytes, symbol offset and binding, linked non-absolute address, complete
image, pinned recipe and every member's genuine/retail result. The image SHA-1
is `e6bfbb95ff6676899e077481221d73ddd4d3bf52`. All 884 logical rows remain, with
874 physical C inputs.

```sh
flock build_ovl/work/land.lock \
  python3 tools/fidelity/prove_slus_ownership.py gp_shared_81510 \
    --output work/native_lane/gp_81510_integration/recheck.json
```

The separate registered-cell check also passes both rows with zero masks and
no fired compatibility passes for genuine ASPSX 2.67, 2.77, 2.79, 2.81 and 2.86.
Its [compact receipt](gp_shared_state_81510_cell_retail.jsonl) records each result;
2.56 was not available in that check.

```sh
python3 tools/fidelity/cell_retail_check.py \
  --rows slus/w_80045340,slus/w_800453E0 --registered --workers 2 \
  --out work/native_lane/gp_81510_integration/cell_retail.jsonl
```

This proves present storage and code reconstruction, not original source-file
boundaries or L4 placement. The existing pins remain, and no new placement
certificate is granted to this group. The original runtime directory pilot is
recertified against the updated inputs. The earlier private trial is retained
in [gp_ready_ownership.md](gp_ready_ownership.md).
