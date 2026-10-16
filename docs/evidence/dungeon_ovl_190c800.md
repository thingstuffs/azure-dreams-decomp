# dungeon_ovl_190c800

Complete ledger cohort, strictly contiguous in file order with one selector load delta, a uniform recipe, no member assigned to another certified module.

Authenticated selector 37 loads bank [0x190c800, 0x1912800) to 0x80024000; all members lie within it.

Shared header reconciles private structure views and declarations; retail control-flow edges and shared data references recorded below. Singleton cohorts are complete standalone helper units; multirow cohorts share the same loaded bank and effect/object services.

Repair the inherited composite first row: its first 148 bytes are three unused section-pinned array scaffolds, followed by the actual stack-frame entry at bank+0x94. Separate those exact bytes as one raw storage segment and retain the existing logical function ID for its complete 2504-byte body. The second function directly calls the real 0x80024094 entry, corroborating the boundary.

Remove all three unused arrays and their section attributes. The 148-byte storage predecessor stays byte-identical and outside native ownership; its jump destinations are not asserted as callback ABI contracts. Both actual complete function bodies emit 3008 text bytes and no rodata. Historical exact baselines remain historical; the guarded split records disclose the extent correction.

The original assigned byte count includes 148 bytes now explicitly classified as predecessor storage. Both function rows receive complete native ownership; the storage does not. Review pending.

Reviewer: orchestrator-r120 (2026-10-15): membership (complete ledger group, selector receipt placement), types (member declarations reconciled into the module header) and ownership (imports bound to proven maps; no storage ownership claimed) reviewed.
