# r78 type consolidation phase 6 - report

Model: claude-opus-5-5[1m].  Deliverable: apply6.sh (+ payload6/, cand6/MANIFEST.tsv 428 rows, sample6_rows.txt
40 rows across dungeon/town/slus).  `bash work/native_lane/r78_types_p6/apply6.sh --dry-run` -> 425 to land, 3
skipped as busy (dungeon/func_80CC085C, func_810AFA04, func_81324774: r78_astra_b4 / r78_opus_w7 out/ staged within the
hour; re-checked at run time; their unchanged texts also verify under the new headers).
Run order: `bash work/native_lane/r78_types_p6/apply6.sh --rows work/native_lane/r78_types_p6/sample6_rows.txt`
then the full run (resumable).  Paths for --rows are relative to the repo root.

| task | result |
|---|---|
| 1 SLUS C-only data symbols | configure.py C_SYMS + config/slus_006.14.c_syms.txt (4 symbols) + mk_slus_root.sh link; recipe diff = link rule + link edge only, cc edges identical, scratch image SHA-1 OK. apply6 re-pins ledger/splits/slus.build.ninja and requires the SLUS gate MATCH on it. |
| open item (3 SLUS rows) | w_8004D614 landed (verify.py exact). w_8003D8B0 / w_8003F80C NOT landed: their candidates folded the separate 128-word table D_80082EC0 into TileObject; they stay as they are (D_80082EC0 links today). TileObject corrected to 0x40 bytes. Do not re-run apply5 for them. |
| 2 record_ptrs.h -> EntityRec | D_800E3D7C / D_800814A8 now `struct EntityRec *`; 158 rows drop the generated Rec include (2 retyped by hand onto EntityRec); Rec_D_800814A8.h retired after landing (+ ledger/records.json entry); Rec_D_800E3D7C.h kept for dungeon/func_8133AD74 (volatile view; exposing it would grow scaffolding). |
| 3 D_80083498 | ObjectNodeHeader (include/shared/object_node.h): the node header func_8003FD64 links; next/pprev/flags named from that allocator, rest unk_; name stays D_. 277 rows exact and staged; misses: town/func_8009E660, func_800CCAB4, func_800D0968 (local TownState views -> build error), dungeon/func_800ACC98 (2.6.3, 8 words). D_800834B8 (+0x20 record half) deliberately separate. |
| pins | none freed: pins2 over the 73 pinned D_80083498 rows found no pin exact-erasable on the migrated text; tasks 1-2 leave every cc1 listing identical. |

Tooling notes for the orchestrator:
- tools/consolidate/ lacks rewrite.py and flow.py (drive3.py imports rewrite; census.py uses flow): copied from the
  pilot lane into this lane's tools/.  New lane tool: tools/drive6.py (header-update driver: drops unused
  generated-record includes, verifies every includer against the lane headers).  Worth syncing all three.
- apply6 verify set is computed at run time (landed rows + every includer of an updated shared header, transitive
  through include/shared/), so rows landed by other lanes in the meantime are covered.

Caveats:
- The pinned-recipe sha changes once (as with every land_recipe_move.py landing): module-evidence records keyed on
  the old sha256 of ledger/splits/slus.build.ninja (slus_module_evidence.py, certify_slus_module.py,
  prove_slus_ownership.py, pin_search.py) read as stale until re-derived.
- Only the SLUS image link and SlusView copies (verify.py module/partition gates) see config/slus_006.14.c_syms.txt;
  tools/gate/match.py and tools/fidelity/probe_gp_module.py link with splat's undefined_syms alone, so a future SLUS
  candidate naming a c_syms symbol is proven by the image/partition gate only (probe_gp_module: follow-up).
- The verify step covers 1,068 rows incl. SLUS module/partition rows (SlusView copies): expect ~10 min plus gates.
- Optional after landing: python3 -m pytest tools/tests/test_configure_slus_modules.py tools/tests/test_slus_partition_export.py.

Next: fold the 4 D_80083498 misses by hand; the D_800834B8 record (x/y/z at 0/4/8 fit EntityRec, +0x2C is read as
a word where EntityRec has a short - A/B it before typing); game.h S_80083178 removal; D_80083120; D_800E2970/296C;
D_80013714 (ranked list in docs/evidence/type_consolidation_pilot_design.md).
