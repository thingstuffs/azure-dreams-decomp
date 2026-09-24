# azure-dreams-decomp status

Generated 2026-09-24T17:20:45Z. Pin `82f20568` (82f20568997a, raw/ frozen at 2026-09-07T12:42:23Z).

## Denominator (rows matched at the pin)

| container | rows | bytes | stock rows | stock bytes | baseline exact | exact bytes | unverified |
|---|---:|---:|---:|---:|---:|---:|---:|
| slus | 884 | 473,788 | 884 | 473,788 | 884 | 473,788 | 0 |
| main | 423 | 62,760 | 423 | 62,760 | 423 | 62,760 | 0 |
| town | 2695 | 457,832 | 2695 | 457,832 | 2695 | 457,832 | 0 |
| dungeon | 2743 | 1,560,892 | 2743 | 1,560,892 | 2743 | 1,560,892 | 0 |
| ovmovie | 22 | 2,852 | 22 | 2,852 | 22 | 2,852 | 0 |
| ALL | 6745 | 2,555,272 | 6745 | 2,555,272 | 6745 | 2,555,272 | 0 |

ovmovie is parked by the owner (listed, excluded from ALL). Ordinary SLUS rows use pinned-TU object verification; grouped module candidates use the full SLUS image gate, including sibling functions and owned data. Historical raw baselines stay per row. Overlay rows use retail-slice comparison through the per-row scorer, with the window gate as the fallback of record. Non-stock rows (bridge cells, per-row assembler dials, platform asm) would be excluded; there are none at the pin.

Baseline NOT exact: 0 rows

## SLUS modules

| module | logical rows | placement evidence | shared headers |
|---|---:|---|---|
| runtime_directory | 3 | current: retail + genuine ASPSX 2.79 | include/common.h, include/slus/runtime_directory.h |
| entry_words | 1 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/entry_words.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| render_words | 1 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/render_words.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/records/Rec_func_80034F58_arg0.h |
| owned_80035484 | 1 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/owned_80035484.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| owned_80038A10 | 1 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/owned_80038A10.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| owned_80044698 | 1 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/owned_80044698.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| owned_800448BC | 1 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/owned_800448BC.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| owned_8004713C | 1 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/owned_8004713C.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| owned_80047338 | 1 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/owned_80047338.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| owned_80047468 | 1 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/owned_80047468.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| state_defaults | 1 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/state_defaults.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| slot_transition | 4 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/slot_transition.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/slot_transition.h |
| slot_transition_secondary | 4 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/slot_transition_secondary.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/slot_transition.h |
| konami_runtime_gp_count | 1 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/konami_runtime_gp_count.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| gp_shared_slots | 2 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/gp_shared_slots.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| gp_split_storage | 1 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/gp_split_storage.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| gp_shared_81510 | 2 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/gp_shared_81510.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/gp_shared_81510.h |
| gp_shared_8099c | 2 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/gp_shared_8099c.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/gp_shared_8099c.h |
| cache_afe | 1 | unproved: certificate unavailable or invalid: [Errno 2] No such file or directory: '<repo>/ledger/modules/cache_afe.json' | include/common.h, include/game.h, include/globals.h, include/include_asm.h |

Module placement preserves logical row IDs. The existing L4/L5 pin, tail-jump and fidelity requirements still apply; changed shared inputs invalidate placement evidence.

## Shape census: pinned raw text vs current clean tree (files / bytes carrying each defect)

| defect | files (pin) | bytes (pin) | % bytes | files (clean) | bytes (clean) | % bytes |
|---|---:|---:|---:|---:|---:|---:|
| m2c boilerplate block | 2332 | 515,092 | 20.1% | 0 | 0 | 0.0% |
| M2C_FIELD raw offsets | 2950 | 1,457,076 | 57.0% | 0 | 0 | 0.0% |
| m2c local names | 5182 | 2,172,128 | 84.9% | 2695 | 1,274,264 | 49.8% |
| ASM_ pins | 2135 | 1,465,048 | 57.3% | 769 | 755,112 | 29.5% |
| goto | 1545 | 1,318,412 | 51.5% | 1599 | 1,365,188 | 53.4% |
| computed-goto jump table | 317 | 437,288 | 17.1% | 315 | 435,848 | 17.0% |
| inline asm outside macros | 362 | 256,260 | 10.0% | 272 | 230,476 | 9.0% |
| fidelity blocking site (LABEL_AS_CALL/PASSTHRU_NO_ARGS) | 1489 | 680,132 | 26.6% | 308 | 157,064 | 6.1% |
| any fidelity site | 2655 | 1,286,668 | 50.3% | 1778 | 960,508 | 37.5% |
| noreturn tail-call spelling (scaffolding, docs/FIDELITY.md) | 751 | 560,500 | 21.9% | 122 | 106,264 | 4.2% |
| maspsx marker pins (scaffolding) | 393 | 351,556 | 13.7% | 3 | 3,176 | 0.1% |
| do{}while(0) scheduling barrier (scaffolding, pure C) | 227 | 156,176 | 6.1% | 354 | 249,960 | 9.8% |
| fake dependency x=(e)+a;x-=a / arg+v-v (scaffolding, pure C) | 1 | 408 | 0.0% | 2 | 820 | 0.0% |
| local address-named struct | 633 | 346,988 | 13.6% | 3144 | 1,615,304 | 63.1% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 632 | 156,440 | 6.1% | 3090 | 552,084 | 21.6% |

Pin sites now: 3,108 in 768 rows; REG 1,480, KEEP 693, KEEP_NV 427, SCHED_BARRIER 158, KEEP_DEP_NV 75, USE_NV 50, USE 42, CLOBBER 35.  At the pin: 25,759; REG 12,778, KEEP 6,854, KEEP_NV 2,500, SCHED_BARRIER 1,349, TAILSLOT_PIN 499, USE 294, USE_NV 260, KEEP_DEP_NV 184.

Hidden scaffolding, not in the pin count (`pin_census.hidden_asm`): raw asm statements 3, calls of local asm wrappers 0, hand-written asm in function bodies 4 (C that is missing); symbol aliases 110 (a second typed name for one symbol: a missing type); file-scope asm directives 432.

Per-row optimization flags (weak evidence about the real build; each switch is undone from the `t30_cellpins` journal's `cell_from`): 290 rows carry one flag, 41 carry two or more.

Site-for-pin trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"site_for_pin","id":row,"site":"LABEL_AS_CALL|ITC|PASSTHRU","pin":macro,"residue_without_pin":str,"at":iso,"note":str}` -- one pin, or two when one is not enough (owner ruling 2026-09-22 afternoon, "accept 2 pins") -- charter rule 3, "a pin moved elsewhere is not a removal"; the trade is tracked, and L4 is where pins stop counting toward removal regardless): 27.

Dead-initializer trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"dead_init","id":row,"site":pins,"init":decl,"lane":lane,"at":iso,"note":str}` -- a never-read `= 0` at a declaration makes the variable multi-set; ordinary C by the owner ruling 2026-09-23, tracked as a spelling trade, informational, the pin count is unchanged; appended by tools/apply_candidates.py at landing): 6.

Void callees (`config/void_callees.txt`, tiers read from its section-header comments -- no per-line marker exists): tier A 30, tier B 1 symbols (matches `census.declared_void_callees()`). Rows whose PASSTHRU_NO_ARGS exemption rests on a tier-B symbol alone (blocked again if tier B were dropped, tier-A/in-tree exemptions do not cover them): 11 rows, 11,864 B.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 2,558,124 | 100.0% |
| L1 | 2,558,124 | 100.0% |
| L2 | 2,558,124 | 100.0% |
| L3 | 2,558,124 | 100.0% |
| L4 | 584 | 0.0% |
| L5 | 288 | 0.0% |

On shared record headers (T7, `include/records/`): 1163 rows, 658,372 bytes (25.7%); records used: 102.

L4 residue (rows below L4, by blocker; a row can carry more than one; parked containers excluded): pins 768 rows (754,988 B), tail_jump 8 rows (2,392 B), not_in_module 6,742 rows (2,554,688 B).

## Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)

| container | assert file:line / expression | developer identifiers | randomizer map (code) | randomizer map (data tables) | resident pointer tables | script function names | prior notes | applied names | any (rows / bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| slus | 0 | 0 | 1 | 0 | 72 | 7 | 408 | 14 | 479 / 328,024 |
| main | 18 | 5 | 1 | 0 | 0 | 0 | 0 | 0 | 19 / 6,420 |
| town | 21 | 8 | 1 | 1 | 0 | 114 | 0 | 0 | 137 / 18,196 |
| dungeon | 0 | 0 | 24 | 21 | 0 | 0 | 0 | 0 | 44 / 35,592 |

Every lane prompt (tools/agent_task.py) carries the row's block; L4 module placement must agree with the assertion source map.
