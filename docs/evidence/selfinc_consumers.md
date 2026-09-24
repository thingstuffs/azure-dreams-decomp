# Current consumers of `_fold_selfinc_la`

The resumed 49F68 repair needs this imitation pass disabled in its private owner
input. The [fresh consumer receipt](selfinc_consumers/receipt.json) confirms that
**all 12 current direct ledger consumers still require it** with their registered
source and recipes. Stock assembly matches retail on every row. Disabling only
this pass makes each match genuine ASPSX 2.79, but adds one instruction and breaks
retail equality. No production pass or recipe was changed.

| Consumer | Stock words | Disabled words | Aligned changed words |
|---|---:|---:|---:|
| `dungeon/func_80093898` | 21 | 22 | 3 |
| `dungeon/func_800938EC` | 17 | 18 | 3 |
| `dungeon/func_81811E30` | 16 | 17 | 2 |
| `dungeon/func_81811E70` | 20 | 21 | 3 |
| `dungeon/func_81811EC0` | 17 | 18 | 2 |
| `dungeon/func_81811F54` | 21 | 22 | 3 |
| `dungeon/func_819B3414` | 266 | 267 | 7 |
| `slus/konami_runtime_w_8003B7C8` | 22 | 23 | 3 |
| `slus/w_8004A6C0` | 16 | 17 | 3 |
| `town/func_800A1480` | 23 | 24 | 4 |
| `town/func_800A2244` | 12 | 13 | 2 |
| `town/func_800C3800` | 17 | 18 | 4 |

The historical fired-but-independent control, `dungeon/func_808CB16C`, remains
retail-exact at 63 words, with identical stock and disabled object hashes.
The table uses relocation-normalized aligned comparisons; raw positional retail
mismatch counts retained in the receipt are not repair distances.

One targeted [recipe experiment](selfinc_consumers/recipe_trial.json) removes
only `-mno-split-addresses` from unchanged 81811E30, 81811E70 and 81811EC0.
It stops the imitation pass firing and makes maspsx equal genuine ASPSX, but
each function remains one word longer than retail. That flag removal alone
does not repair these consumers. Their C address and loop forms require
attribution before further recipe or source trials.

Reproduce with `python3 work/native_lane/selfinc_consumers/run.py` and
`python3 work/native_lane/selfinc_consumers/recipe_trial.py`. The isolated
harness preserves registered compiler and assembler flags and records source
hashes. This bounded 12-consumer-plus-control check is not a fresh whole-tree
fired-pass census. A complete census, consumer repairs and full gates still
precede any retirement or required final owner sign-off.

The [49F68 ownership proof](gp_order_bytes.md) remains queued with its solved
source and full private retail link; it does not justify deleting this pass
while the measured consumers remain.
