# Two complete common-module TOWN callbacks

TOWN +2ABEC8 at 800166C8 is an 84-byte callback. It tests flag DAC; on a nonzero mask it passes the original object and signed entry index to 80019958 and returns one, otherwise zero. The callee reads the entry table at object +10 and a signed flag ID at indexed entry +0C, then calls the flag setter. No additional input carrier is consumed.

TOWN +2AD68C at 80017E8C is an 88-byte callback. Under flag 1455 it sets the signed flag ID at object +18, then forwards the original object and signed entry index to 80019C68 and returns that helper's result. That helper tests the object's flag, sets the indexed entry flag, clears the object's flag and returns zero or one. The existing census record describes the observed +10 and +18 fields.

Both complete sections match at 2.7.2-cdk -G0. The existing common-module views image_2ab800, s2_sweep_2AB9C0 and region_2ab9c0_2b09ec establish file-to-runtime delta 7FD6A800. The new homes belong to region_2ab9c0_2b09ec, which has no per-image relocation rebinding. Overlapping views retain their existing, disjoint owner sets. Each callback retains its actual calls without home bindings or duplicate placements. The eight-byte interior rows town/func_8028BF14 and town/func_8028D6DC are retired. Their source homes and archive baselines remain intact. Net matched code grows by 156 bytes.

Both prototypes live in town/scene.h. The sources add no casts, goto, volatile, macros, assembly or register pins. Complete image comparison is required before claiming the registered rows proved. Bounded local port scenarios do not exercise these two companion-observed entries; no new runtime reachability claim is inferred from the image proof.


## Current-target shared callback placements

The follow-on cohort is based on the fully proved 82-placement rebase of target 648eafb94.
Dungeon +FDD76C / 80164F6C is the complete 2,468-byte Mandara action section, reused from
dungeon/func_80FB176C. Its compiler emits a 72-byte local switch-table section. The normal
production table placement/content verifier independently checks all table bytes and case targets;
the complete rebound text is also compared with retail. No new C definition is duplicated.

Dungeon +D86EEC / 801726EC is the complete 1,824-byte actor-path callback, reused from
dungeon/func_80CE9758. The former eight-byte return-zero placement at +D87604 is its interior
terminal epilogue. Only that placement is retired; its shared MAIN source and archive remain intact.
The staged registrar checks every overlap, runtime view, source identity and epilogue extent before
publishing any authority change. The other existing placements retain their target metadata.

Fresh ordinary compiler objects prove these two complete sections. Both prepared common callbacks
were recompiled against the current headers and their complete 84/88-byte sections also match.
The final scoped retail image proof and registry/layout checks are required after registration.
This is C ownership and retail-byte evidence. The supplied sweep observations are historical;
current native dispatch and hit totals need a separate port rerun.

The image builder retains the symbol-renaming map from ordinary object rebinding when selecting the function used for local switch-table discovery. This fixes the stale-name lookup for a placed function; the production table-content verifier and byte comparisons remain in force. Five focused tests exercise the real image pipeline up to discovery, including the unchanged ordinary case.
