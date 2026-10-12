# Oracle family commands

Use the kit path from your private scratch checkout and a lane-owned output.

| Purpose | Command |
|---|---|
| Observe candidate sites | `python3 KIT/pass_oracle.py ROW erased --discover --keep oracle/sites --json oracle/sites.json` |
| Veto one birthing boost | `python3 KIT/pass_oracle.py ROW candidate.c --change '{"kind":"sched-birth","uid":65,"phase":"sched1","value":0}' --families sched --keep oracle/birth --json oracle/birth.json` |
| Forbid a combine attempt | `python3 KIT/pass_oracle.py ROW erased --change '{"kind":"combine-veto","uids":[1131,1130,1125]}' --families combine --keep oracle/combine --json oracle/combine.json` |
| Force a store/load dependency | `python3 KIT/pass_oracle.py ROW candidate.c --change '{"kind":"alias","uids":[279,19],"phase":"sched2","value":1}' --families alias --keep oracle/alias --json oracle/alias.json` |
| Avoid one hard register in global.c | `python3 KIT/pass_oracle.py ROW erased --change '{"kind":"global-avoid","pseudo":81,"hardreg":4}' --families '' --keep oracle/avoid --json oracle/avoid.json` |
| Veto one destructive reorg merge | `python3 KIT/pass_oracle.py slus/konami_runtime_w_800345B8 erased --change '{"kind":"reorg-delete","uid":1400,"value":0}' --families '' --keep oracle/reorg --json oracle/reorg.json` (recorded raw-exact case) |
| Toggle delay-slot eligibility | `python3 KIT/pass_oracle.py ROW candidate.c --change '{"kind":"reorg-fill","uid":23,"candidate_uid":20,"value":0}' --families '' --keep oracle/fill --json oracle/fill.json` |
| Veto jump2 tail sharing | `python3 KIT/pass_oracle.py ROW candidate.c --change '{"kind":"jump-cross","uids":[33,64],"value":0}' --families '' --keep oracle/jump --json oracle/jump.json` |
| Veto reload reuse/no-op deletion | `... --change '{"kind":"reload-reuse","uid":54,"occurrence":0,"value":0}'` / `... --change '{"kind":"reload-noop","uid":54,"value":0}'` |
| Move a stack-slot cursor | `... --change '{"kind":"frame-offset","occurrence":3,"value":-40}'` |
| Select a CSE equivalence head | `... --change '{"kind":"cse-eqv-head","new":88,"old":81,"occurrence":0,"head":88}'` |
| Composite (2..4 changes, one run) | `python3 KIT/pass_oracle.py ROW erased --change '[{"kind":"combine-crosses","uids":[1131,1130,1125]},{"kind":"combine-crosses","uids":[1188,1187,1182]}]' --families '' --keep oracle/pair --json oracle/pair.json` |
| Allocator input inside a composite | `... --change '[{"kind":"alloc","pseudo":87,"input":{"kind":"refs-add","value":-2}},{"kind":"keep-dead","uid":163}]'` |
| Search one row | `python3 KIT/oracle_search.py --row ROW --text erased --out search/ROW --trials 192 --composites 32 --workers 6` |
| Validate search | `python3 KIT/oracle_search.py --validate validation_inputs.json --out validation --trials 128 --composites 24 --workers 6` |
| Search all pin rows | `python3 KIT/oracle_search.py --all --gate validation/validation.json --out search_all --trials 192 --composites 32 --workers 6` |
| Observed reference sites | `python3 KIT/source_refs.py ROW erased --out source_refs/ROW` |
| Targeted reference/life map | `python3 KIT/source_refs.py dungeon/func_8180B064 erased --pseudo 369 --fewer-refs 3 --life-at-least 180 --out source_refs/goal` |
| Numeric 2.6.3 allocator | `python3 KIT/alloc263_oracle.py town/func_808119EC erased --pseudo 75 --change '{"kind":"refs","value":14}' --out oracle/263` |
| Attribute every differing word | `python3 KIT/attribute.py ROW candidate.c --out attribution/ROW` |
| Cross source mutations with oracle | `python3 KIT/mutate_search.py ROW candidate.c --out mutation/ROW --mutations 8 --oracle-trials 24 --workers 2` |

UIDs and pseudo numbers above are examples for the recorded fixtures. Discover
again for a different text. `README.md` documents all schemas and ABI limits.
Outputs remain counterfactual, reviewer pending, and never stageable.
