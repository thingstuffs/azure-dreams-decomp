# Private fidelity controls refresh

The final detached control run passed **60/60** checks. It used the repaired candidate SLUS sources and the guarded assembler in `fixture_final/`; production objects, tools, source, and configuration stayed unchanged. The two changed tool files are a control-only update to `aspsx_diff.py` and a docstring correction in `maspsx_trace.py`. Their complete source diff is `controls.patch`. Executable AST outside `run_controls` and module docstrings is byte-for-byte equivalent after AST normalization.

The historical casesi assets `sw_base.o`, `sw_preserve.o`, `sw.proc.s`, and `sw.c` were copied from the existing `work/maspsx_jtbl` into the detached fixture and SHA-pinned. Both historical object controls and the live `sw.c` control actually ran and passed; no casesi control was skipped. The obsolete optional `d92c_genuine.c` path was removed from the control: it does not satisfy the current owner include-order contract. The current canonical D92C owner instead passed 136-word, zero-mask retail and genuine comparisons at 2.67, 2.77, and 2.79. Three formerly pass-dependent SLUS rows now prove their canonical owner streams are genuine/retail exact with their old pass idle. The remaining positive control, `dungeon/func_818D4E68`, measured `_split_funcaddr_la` firing and `no:_split_funcaddr_la` reaching genuine. Fifty-two plain pin-free sample controls passed across the registered cells.

The first detached run passed 59 controls and failed `plain slus/code`: the old top-level check looked for a whole-row ablation, while this logical row now has seven physical units. Its `run.log` and `run_receipt.json` remain unchanged. The revised control checks all 156 functions exactly once across those seven units; every unit must pass pipeline/self-check/unmasked retail comparison and be genuinely exact or have its **own** measured ablation. It does not promote an owner-only fix to the entire logical row. The revised run passed 60 controls, with zero failures or skips.

| Artifact | SHA-256 |
| --- | --- |
| baseline `aspsx_diff.py` | `385c3d7ef4f10df3892c0b18653ca91edf14fdbe6ebac76452f0ea2c93a48d72` |
| revised `tools/fidelity/aspsx_diff.py` | `34ea90ca45d1a3753851145b9731a728da3214fc640def9a12592f27731d5338` |
| baseline `maspsx_trace.py` | `d0336210e99493c2857abc13930bbcedeb92162b5d684037874fdb2a0a7d99c6` |
| revised `tools/fidelity/maspsx_trace.py` | `cae6004277b9fc15f706a045195e6e96d185c34bdcc422b06393aafffa6ad0c9` |
| `controls.patch` | `e63ba8ccea244ef103746e0831dda4965b640031bd2ffab9c7bfae606a79c6d5` |
| first `run_receipt.json` | `689af9b8933841fac68075230a8066fdf2a0eae5694ba686f04f7f3814010201` |
| final `prepare_final_receipt.json` | `0d8bac1b1419d4927166a4e6fb3f56c950c6d8cfaf961a947968921bfcc5a509` |
| final `final_run_receipt.json` | `5b775f530d62f9a02bd9c5717e833945b6a9346e730e51c4d2f401e5467d8e27` |
| final `final_run.log` | `73a2b526c84ccedade580f1b0d34469a26d4c375746cf43e708be4e0592040c7` |

Fresh private reproduction, before these artifact directories exist:

```sh
python3 work/native_lane/gp_partition_only_tools/controls_refresh/prepare.py
python3 work/native_lane/gp_partition_only_tools/controls_refresh/run.py
python3 work/native_lane/gp_partition_only_tools/controls_refresh/prepare_final.py
python3 work/native_lane/gp_partition_only_tools/controls_refresh/run_final.py
```

The first `run.py` exits 1 by design, preserving the representation-change failure. The last command exits 0 and writes `final_run_receipt.json`. All ASPSX scratch is under a short private `/tmp/pctrl_*` path; the controls call the real `A.process_row` and existing `run_controls`, without substituting results.
