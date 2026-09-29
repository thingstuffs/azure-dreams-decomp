# Round 80 wave record (post-restart pickup, 2026-09-29)

Previous round: evidence/r79_wave_report.md (closed at f5c32120, 2,762 pin sites in 735 rows).
Goal (owner, 09-29): pick up from round 79 once its landings finish, try Sonnet 5.5, keep reducing pins to 0 and
continue the consolidation/cleanup so the source is byte-exact AND something to be proud to share.

## Start (2026-09-29 ~03:20Z)

- Restart condition met: the Agent `sonnet` alias now resolves to **claude-sonnet-5-5** (probe agent quoted
  "Sonnet 5.5 ... claude-sonnet-5-5"). The r79 lander finished r79_astra_b3 at 03:17Z (LAND_GAP_END fin0049).
- Prebuilt packs checked against live src (all 11 rows' base copies identical to src/ after phase 10): no rebuild.
- Routing per the r79 record's recommendation (r70-plateaued big rows -> Opus fresh-eyes; keep one Astra to test
  the claim): b4 stays Astra, b5/b6 renamed to Opus Agent lanes (same brief; lane paths rewritten).
- Phase-11 brief: the six b4-b6 rows appended to its busy list before launch.

| lane | model (quoted in codex.log) | rows | shape |
|---|---|---|---|
| r79_astra_b4 | gpt-6-astra xhigh | 802835B8 (24), 8008EE88 (22) | big-row continuation (Astra arm of the tier test) |
| r79_opus_b5 | claude-opus-5-5[1m] | 800AFA68 (20), 800C4A80 (19) | same pack, Opus fresh-eyes arm |
| r79_opus_b6 | claude-opus-5-5[1m] | 80F36D0C (19), 81978428 (19) | same pack, Opus fresh-eyes arm |
| r79_sonnet_s1 | claude-sonnet-5-5 | 8009F018, w_80052A90 (7), 80092824, 807B040C, 80EB751C (6) | Sonnet 5.5 probe, never-served 3-7 (Opus baseline 2.8 pins/lane) |
| r79_types_p11 | claude-opus-5-5[1m] | type consolidation phase 11 | EntityRec propagation, town root D_80016000, D_80082E60 |
| r79_sonnet_g1 | claude-sonnet-5-5 | 6 pin-free rows, 35 plain gotos | NEW: goto readability pilot |

## Readability lane (new this round)

Shape census (STATUS): plain gotos remain in 1,597 files; 964 pin-free rows hold 5,581 plain gotos (no computed
goto). The goto generators t41/t44/t48/t102 go the other way (goto forms that remove pins). A readability lane
turns gotos back into structured C, byte-exact. Tooling: `land_lanes.sh` lands an equal-pin candidate whose plain
goto count fell (and refuses one that adds gotos at equal pins); `kitlib.admissible` stages the same, plus
equal-pin candidates whose volatile / one-trip count fell (the lander's round-78 rule, now in the kit too).
Pilot r79_sonnet_g1 asks for a generator rule per working shape, so the 900-row tail can be swept by CPU.

## Sonnet 5.5 results (lanes ended 03:25Z-04:10Z)

**Pin lanes (the probe rule: scale only at >= 2.8 pins/lane on two lanes):** r79_sonnet_s1 3 pins on 5 never-served
3-7 rows (80092824 6->5 by a single-set `(s32)SYM` local in place of a KEEP_NV'd page constant; 80EB751C 6->4 by
folding `|= 0xC` into the load - a sched1 tie between two adjacent loads); 248,262 A-tokens, 85 tool uses. r79_sonnet_s2
0 pins on 5 never-served rows (all at listing distance 2-6; stopped at ~60-80 of 150 calls, earlier than the brief's
keep-going rule); 188,525 A. **1.5 pins/lane < 2.8: Sonnet 5.5 is NOT scaled for pins.** s2's rows went to an Opus
fresh-eyes continuation (r79_opus_c1) with its evidence; a fresh Opus pack r79_opus_f1 runs beside it.

**Readability (goto) lanes: Sonnet 5.5 is the workhorse.** Pack builder `tools/lanes/build_goto_lane.py`, brief
template `tools/lanes/goto_lane_brief.md` (measured rules folded in after g1 and g5), served ledger
`ledger/goto_lanes.jsonl`. Every staged file byte-exact, 0 pins, nothing banned added.

| lane | rows | gotos | extra scaffolding removed | A-tokens | tool uses |
|---|---:|---|---|---:|---:|
| r79_sonnet_g1 | 6 | 35 -> 5 | - | 86,554 | 27 |
| r79_sonnet_g2 | 8 | 66 -> 6 | - | 131,763 | 56 |
| r79_sonnet_g3 | 8 | 16 -> 3 | - | 110,644 | 36 |
| r79_sonnet_g4 | 8 | 25 -> 1 | 2 nested one-trip blocks | 105,294 | 43 |
| r79_sonnet_g5 | 8 | 38 -> 1 | 7 volatile sites | 98,146 | 40 |
| r79_sonnet_g6 | 8 | 47 -> 5 | - | 108,935 | 40 |
| r79_sonnet_g7 | 8 | 55 -> 4 (+1 row rejected, below) | 2 one-trip blocks, a dead variable | 128,106 | 53 |
| r79_sonnet_g8 | 8 | 41 -> 1 | 1 one-trip block | 97,285 | 31 |
| r79_sonnet_g9 | 8 | 55 -> 3 | 1 volatile read, 1 one-trip block | 133,459 | 53 |
| r79_sonnet_g10 | 8 | 30 -> 4 | 1 volatile pointer | 97,962 | 37 |
| r79_sonnet_g11 | 8 | 48 -> 0 | 1 unused volatile union member | 104,563 | 29 |

About 7 gotos per 10k tokens. What the lanes measured (folded into the template): state/phase ladders are `switch`
with fallthrough in block order (if/else chains measured dist 20-98); a goto pair into a shared tail is
`if (a || !b) { default } else { alt }` default arm first; different bit tests of one word stay nested (a merged `&&`
lets combine fold them, dist 12); `*(volatile T *)` reads are often plain. Goto LOOPS mostly stay: a structured loop
gets NOTE_INSN_LOOP notes and loop.c hoists/strength-reduces what retail kept inside (0 of ~30 loop spellings on
8 rows) - a measured fact about the original, recorded per row in the lane REPORTs.

**Coordinator decisions (owner delegated):**
- REJECTED r79_sonnet_g7 slus/w_80058E6C (14 -> 3): exact only with a dead GNU case range `case 0 ... 0xF:` that
  exists to push gcc from a jump table to a compare tree (imitates the compiler; charter legitimacy). Moved to the
  lane's rejected/ with a README; the row keeps its ladder.
- KEPT r79_sonnet_g4 dungeon/func_80FB3AB4's zero-goto form (a 5-line block duplicated into case 0) over the 1-goto
  variant, whose label sits inside an if body that case 0 jumps into (a goto into a block reads worse; the owner's
  duplicate-statement ruling covers the copy).

## CPU generators

t122_gotowhile (rotated/bottom-tested goto loops -> while/do): 52 rows applied (first pass 3; a keyword bug refused
128 rows, fixed, rerun applied 49). t123_returntail (goto into the function's final `return E;` -> `return E;`): 397
of 529 rows applied. Combined: 440 files, isolated gate 298 windows MATCH + SLUS SHA-1 MATCH (03:46Z).

## Incident

r79_opus_b6 ran `rm -rf` on the orchestrator's session scratchpad (subagents share it) to clean one stray file; only
finished sweep scripts were lost. tools/lanes/agent_lane_prompt.md (and the goto prompt) now forbid the shared
scratchpad and `rm -rf` outside the lane (bfb28f13).

## Big-row lanes

r79_opus_b6 (Opus fresh-eyes on r70-plateaued rows): **dungeon/func_80F36D0C 19 -> 0** (the prior lane had copied
retail's registers into C: scratch `angle_index` standing for eight values, hand-built table addresses, KEEPs on all
four parameters; natural C with abs(), table-base locals and case-2 reuse of `index` is exact). func_81978428 open:
the evidence says its registered 2.7.2 recipe is wrong (paired `lui 0x8008`, %lo+4 forms and %hi(D_800814A8) held
across the loop are cdk split-address output; zero-pin symbol C at 2.7.2-cdk-G0 totals 53, pinned base there 15) -
a recipe trade to decide once a cdk candidate closes. 295,990 A, 94 tool uses.

## Opus continuation of the Sonnet pin rows (r79_opus_c1)

town/func_8081B4A4 **3 -> 0**: field-order final stores (lifetime overlap in local-alloc, not the dependents tie Sonnet
named) + both do-while loops as goto loops beside the function's existing goto loop (global-alloc weights refs by
loop depth; loops without loop notes give retail's $21 for parent_state). **Coordinator decision:** accepted - the goto
loops are measured evidence of the original's shape, and a pin removed at a less pretty spelling is owner-approved;
the 1-pin do-while alternative is kept at the lane's cand/t_fieldorder.c. Four rows open with named next measurements
(818F30EC/80BC1084: cse-folded argument-2 zero floats at sched1; 8188E648: one variable spans two residues;
w_8004B954: spilled-copy with no predecessor). 289,015 A-tokens, 83 tool uses.

## Near-miss continuation (r79_opus_c2) and fresh Opus lanes

r79_opus_c2 on dungeon/func_800AFA68 (b5 left it at total 4 / 12 of 20 pins): total **2** at 12 pins (one `lui
%hi(gameWork)` two slots late), plus an exact-ORDER variant at total 6 (a $2/$3 colour swap). b5's "one sched1 tie"
was three mechanisms: reload find_equiv_reg inheriting a shared HIGH (fixed by assigning depth_table after the first
call), sched1 birthing priority (fresh single-set initial_pitch), and a HIGH-before-$17 order no statement order
reaches (sched.c gives every birthing insn 0x7f000001; only a non-birthing ALU consumer below the scratch set, which
the ASM_KEEP_MEM provided, orders it - pure C: `render_state += 0xB0` before the scratch set, at a colouring cost).
Candidates in the lane's best/. Two Opus lanes deep: a Fable escalation on this one mechanism is the charter's next
step if the pin count justifies it (8 pins). func_800C4A80 17/19 at total 4 (combine folds the lbu args into the
call copies). 343,295 A-tokens, 114 tool uses.

r79_opus_f1: **slus/w_8003DBD0 4 -> 0** (hand-written `(u8 << 24) >> 24` + four KEEP_DEP_NV = retail's lbu/sll/sra,
because gcc 2.7.2's extendqisi2 into an s16 store gets no REG_EQUAL note; the original read the byte as s8). Family
of 8 more rows / 63 pins -> brief paragraph byte_signext.md, lanes r79_opus_fam1/fam2. 291,598 A.

## Clone transfer for goto rewrites (Sonnet-built tooling)

`clone_transfer.py --metric gotos` (built by a Sonnet 5.5 tooling lane in a worktree, 76k tokens, reviewed and merged
47e0f714; 26 unit tests) replays a goto lane's base->out edit on clone siblings: 382 exemplars from r79_sonnet_g*,
171 siblings tried, **144 staged byte-exact in 100 s** (CPU only). 81 collided with rows a goto lane already staged
(the lane's own result is kept; the clone copy moved to r79_clone_goto/dropped/), **63 new rows** stay in
r79_clone_goto/out for the lander. The same tool's pin metric runs over this round's Opus pin exemplars
(r79_clone_pins).

## Readability-lane decisions (coordinator, owner delegated)

Rejected/replaced so a landed rewrite never reads worse or steers the compiler: g7 w_80058E6C (dead GNU case range),
gb1 town/func_80956260 (dummy `case 0x101` reshaping the case tree), g41 dungeon/func_800B8758 (label moved into a block
so a goto jumps into it), g46 dungeon/func_80A49CB0 (15-line tail copy -> its exact 3-goto variant), g49 three table rows
(5-line apply block copied into 3 cases to skip a block -> exact 1-goto variants; func_80CF81A0 keeps the copy form,
its 1-goto variant is not exact), f3 dungeon/func_81977584 (goto-label form -> the exact real-`switch` variant, same 2
pins). Each rule is now in tools/lanes/goto_lane_brief.md. Densest-first packs (`--densest`) pay far more than random
ones: g47 170 -> 0, g48 106 -> 3, g49 104 -> 0, g50 104 -> 0 (random-pick lanes averaged ~35 -> 3).
