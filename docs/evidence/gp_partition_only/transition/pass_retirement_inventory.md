# Candidate pass-retirement inventory

The production `MaspsxProcessor.process_lines()` invokes `_sink_call_separated_la` and `_split_funcaddr_la` unconditionally, in that order, at `tools/maspsx/maspsx/__init__.py:1160-1161`. This only establishes that each input passes through the routines; it does not say either routine changes every input. The methods themselves are still present and invoked at the same locations in `transition/payload/tools/maspsx/maspsx/__init__.py`. The transition payload changes assembler/data handling, but does not remove either pass. Its candidate ledger contains `rows.jsonl`, `splits/slus.jsonl`, and `splits/slus.build.ninja`; it contains no refreshed `maspsx_dependence.jsonl`.

The current dependence ledger and the transition recipes identify a small revalidation set:

| Pass | Current `maspsx_pass` rows | Candidate transition evidence |
|---|---|---|
| `_sink_call_separated_la` | `slus/w_8004AB7C` (`ledger/maspsx_dependence.jsonl:137`; current recipe `2.7.2`) | It is re-reciped to `2.7.2-cdk` (`transition/serialized_slus.jsonl:550`). Candidate `w_8004AB7C.c` changes `D_80012090`/`D_80013628` from padded struct externs to `s32`, but keeps the `itemCategoryTable` pointer and call sequence that motivated the pass. The candidate pass also changes its small-data test for locally declared `.sdata`/`.sbss` symbols. This is a one-row candidate to remeasure, not an established retirement. |
| `_split_funcaddr_la` | `slus/w_80041AB0` and `slus/w_80043CD0` (`ledger/maspsx_dependence.jsonl:123-124`; current recipe `2.7.2`); `dungeon/func_818D4E68` (`:92`; recipe `2.7.2-G0`) | Both SLUS rows move to `2.7.2-cdk` (`transition/serialized_slus.jsonl:391,425`). Their candidate C changes padded data declarations to `s32`, while both function-address callback arguments remain. The dungeon row is outside this SLUS transition and remains `2.7.2-G0`; therefore this transition alone cannot justify global removal of `_split_funcaddr_la`. |

The ledger kinds have a stronger meaning than “the routine fired”: the campaign charter defines `maspsx_pass` as a row exact only through a source-driven Maspsx rewrite that genuine ASPSX lacks (`docs/PIN_CAMPAIGN_CHARTER.md:120-126`). Those classifications describe the current registered source/recipe state. The transition changes the three SLUS recipes and their C declarations, so the old records require fresh row-level evidence before they can be retained or retired. The candidate’s full image result and generic-assembler rehearsal do not, by themselves, report whether either routine changed a given row. Nor would a missing row in a future ledger prove that the routine never fired; it could mean the row no longer depends on that output.

Relevant unit coverage:

- `tools/maspsx/tests/test_funcaddr_split.py` and its transition copy exercise the split callback argument, interaction with store-delay filling, and negative controls. The transition copy removes the former padded `.extern` fixture lines but retains assertions for the split behavior.
- `tools/maspsx/tests/test_funcaddr_split_branch_delay.py` and its transition copy cover safe hoist placement, including the `dungeon/func_818D4E68` branch-delay witness. These tests preserve `_split_funcaddr_la` behavior in the candidate payload.
- No test under `tools/maspsx/tests/` or the payload tests names `_sink_call_separated_la` or `func_8004AB7C`; its current single-row dependence has source/docstring evidence but no direct pass-specific unit test found in this bounded search.

For the next evidence step, remeasure these four rows at their candidate recipes, then ablate each pass separately on the exact generated inputs and compare against the genuine reference. The likely SLUS retirement subset is only `w_8004AB7C`, `w_80041AB0`, and `w_80043CD0`; keep the dungeon split consumer in scope before making any claim that the split pass itself can be removed. No compiler run or production edit was made for this inventory.
