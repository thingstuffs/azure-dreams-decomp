# B18 assembly notes

Tree: B16d (cefe76079) + link/ restored (root/ copy lacked link/; reconstructed by reverse-applying the B17 link/ hunks onto r121w_b17asm's tree, hash-verified) + B17 patches 0001/0002, then six deliveries. Patch 0001-r121-B18.patch is vs that B17 tree (561 files; applies with git apply, replay verified byte-identical).

## Per delivery
1. r121w_types4 (347 files: 303 C, 44 headers, 7 new / 3 deleted): applied clean, no conflicts, no overlap with other deliveries.
2. opus_goto (10 files, 60 gotos): clean.
3. opus_goto2 (6 files, 7 gotos): clean.
4. r121w_goto5 (4 files): clean.
5. opus_heur (+16,920 B dungeon C placements = 12 twin placements, 2 volatile donors fixed): 5 reject groups from B17 reformatting; all merged by hand (see merged_by_hand.tsv), none dropped. overlay_modules.build.json regenerated. Twin entries carry no `bindings` (gate MATCH confirms).
6. r121w_data1 (176 paths, typed extern data): dropped 3 whole-file hunks (TUs merged by B17), the fingerprint fix (already in B17) and build_ovl copy; 3 town .c include/extern hunks re-applied by hand; town_map_props.h: first change already in B17, second (S_800BE214_2 -> TrailHeightView) applied. First scoped gate hit town_scene ERROR (previous declaration of advance_actor_animation_pose) before this fix; re-gated after it.

Step 2 (decision 66): ledger/unrecoverable_details.jsonl created for slus/w_8005552C. Evidence: caller w_800542BC dispatches 0x500/0x600/0x700/0x800 to it, so 0x500 is the only in-range value the game sends (consistent, not byte-proven); comment in source updated to say so.

## Generated files regenerated
registry.py (rows.jsonl, 21,572 rows), levels.py (levels.jsonl), gen_src_index.py (INDEX.md), overlay_module_gate --graph, mk_ovl_root.sh. ledger/gate.jsonl is the post-gate journal. ledger/gate_slus.jsonl left as in B17.

## Checks
registry OK; row_db check OK; gen_noreturn_syms.py --check OK (4 families); SLUS SHA-1 gate MATCH (842 TUs); scoped gate_all --workers 6: 1725 windows (union of the five touched_windows lists, all exist) 1725/1725 MATCH, final audit clean (10,703 s).

## Debt (changed .c/.h files, before -> after; debt_scan.tsv)
goto 118->47; volatile 10->8; __asm__ 0->0; NON_MATCHING 0->0; #pragma 0->0; M2C_ 233->155; /home paths 0->0; S_<addr> tokens 7015->6714.
Whole src+include tree: goto 395->324; M2C_ 1916->1838; S_ tokens 87051->86750; volatile 157->155. No increases.
