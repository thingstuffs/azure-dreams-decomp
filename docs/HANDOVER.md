# Handover (2026-10-04 ~17:20, round 93: native Claude lanes + luna/Gemini pools; IN PROGRESS, updated 10-05 03:30Z) - start here

**Owner brief (10-04):** ~12 h of Claude usage left; Sonnet first, 1 Opus at a time, 1-2 Sonnet; minimal sol/astra; luna and
agy Gemini 3.8 flash for grunt work; goal = fewer pins, compiler alignment, cleanliness (gotos, do-while(0) ...).
Native Agent lanes (not agy-Claude: the r92 agy pilot was content-filter-blocked on every try).

**Numbers (10-05 ~05:45Z):** pins 357/143 -> 306/126. Rows off their build 20 -> 14. Volatiles 539 -> ~420.
Goto sites now 1,388 in 414 files (587 files at pickup); computed-goto files 69 -> 16; m2c-name files 758 -> ~400;
~2,000 M2C_UNK prototypes / data externs typed (t138 785 + t139 + lanes); t140 named argN prototype params (299 files).
**Fable -> Opus relay solved dungeon/func_800C9858 15 -> 0** (r93_fable_c9858 74 -> 29, r93_opus_c9858 exact). Its
mechanisms opened the VOLATILE family: tools/lanes/brief_paragraphs/volatile_removal.md (11 measured shapes incl. the
four reload gates from r93_opus_rl1); Opus vb2/vb3 -8 pins on byte-volatile rows; Sonnet vb1-vb9 ports.
**Best pin lever this round: Opus on rows whose text was RESTRUCTURED by cleanup lanes** (r93_opus_p7 -4, p8 -1, p9 -7,
p10 -3, p11 -1): earlier analyses at the old text are stale once real loops/switches replace m2c gotos. The near-miss
queue (r91 open_rows.tsv) is exhausted (p4-p6: 1 pin over 11 rows).

**What paid (and the recipe for each):**
- **Opus pin lanes** (record_usage.py --prompt; mkq() in the session = build_class_pack + kit_pack --question q_<lane>.md):
  r92_agyO_p1 -2 (81810198 dbr marker from ANOTHER loop's backward fill -> for loop; 81820800 abs()), r92_agyO_p2 -3
  (81845068 PsyQ setaddr/getaddr OT link; 80095160 3->1), r93_opus_p3 -2 (800BAE88 K&R u8 parameter - tools/verify.py now
  accepts K&R definitions; 800B52D8 indexed for loops), r93_opus_tptabc: 10 composite rows real switch + rodata owners.
- **Sonnet goto lanes** (build_goto_lane.py --densest, AGENT_PROMPT.txt): g1-g14, pg1-pg4 (pinned rows: gotos only, 0 pins fell).
- **Sonnet computed-goto -> switch** cg1-cg7: 41 rows exact; read RETAIL tables (rtab.py), old label arrays were wrong.
  Recipe now in tools/lanes/brief_paragraphs/computed_goto_switch.md (+ goto_recipes.md, tools/learnings/pin_leads_r93.md).
- **CPU generators written by Sonnet:** t136_stubtail (76 gotos), t137_switchbreak (33 gotos); both in cascade_extra.txt.
  t16_absidiom now sees cast copies + pins on the tested value. CPU sweep r93: -1 pin (8080DAB8).
- **Alignment (Sonnet):** al2/al3/al4 retired crutches on 7 pin-free rows (8001A0F0, 806D30B4 nosr, 8001F368 cse-follow-jumps
  via local pointer reads, 8080BCD4, 81893024, 80813E14, 80E8D490 - several were r91c astra winners never landed).
- **Cleanup:** luna rename/proto/nm pools (build_cleanup_lane.py, ledger/cleanup_lanes.jsonl), Gemini goto pools (agy,
  15 lanes, ~70% rows staged), Sonnet big-row renames + proto lanes pr1-pr16. tools/lanes/proto_check.py guards prototype
  edits (rows are FILED by file offset: callees resolve by true_name; a sibling lane wrote 12 false voids before the check).

**Landed with owner review flagged (recipe_trades.jsonl notes):** 80EB7D2C 16-line join tail copied into both arms;
8186F0C4 12-line block copied into both arms; 8001A2B0 shared jump-only `fail:` block (gotos 2 -> 6) to drop a KEEP;
81832800 byte-offset dirStepX read; 8009B70C stepwise `x -= 0x20; x <<= 16; x >>= 16;`; 800971DC u16 narrow copy.
Prototype lanes respelled some `M2C_UNK` params/fields as `s32`/`s32 *` (same C type, marker lost) - tighten next time.
**Owner 10-05: accepted items 1 (re-carve) + 2 (tail recursion) -> land_own2tr.sh; items 3/4 -> copy-tail lane; flagged trades accepted.**
**Held for the owner (not landed):**
1. r93_sonnet_own2: 8195281C / 8195E81C real switches exact only after a ROW RE-CARVE (merge the 28-byte data rows
   func_81952800 / func_8195E800 into the function rows + owner records). LANDING.md in the lane. Row-identity call.
2. Gemini r93_agy_goto7 8009399C / 8009A108: `goto retry` loop -> self tail recursion (exact). Plausible? held/.
3. r93_agy_goto4/5 80BC1BA8 80BC7BA8 80BCDBA8 80BD9BA8 (8009E0EC RESOLVED goto-free by r93_opus_p16, see below): goto into a label inside another
   block (labels-into-blocks rule) - held/.
4. r92_agyO_p2 80095160 landed with `move_failed:` (pre-existing label inside an if block) now reached by more gotos.
6. town/func_808110CC: owner ACCEPTED (10-05) the visible redundant store `unk_A2 = 16;` (retail emits it) - landed.
- dungeon/func_800CA184 (r93_opus_ca184, 11 -> 10 pins, gotos 32 -> 24): pointer copy `scratch = view_scratch;` after a join (copy-host shape, byte-free) - admissible? recorded in ledger/recipe_trades.jsonl.
- dungeon/func_8009E0EC (r93_opus_p16, 8 -> 0 pins, 9 -> 0 gotos; was HELD for labels-into-block, now goto-free): trades `self = actor` copy, move_flags split, two-role shared temps `offset`/`temp` - admissible? (ledger/recipe_trades.jsonl).
- dungeon/func_800957B8 (r93_opus_p18, 5 -> 0): m2c `u16 tile_info[5]` -> one `u16 tile_flags` (callee definition func_8009A350 writes one u16; retail frame allows <= 8 B; array costs 56). Landed as typing-from-definition, not a dropped local.
- AWAITING OWNER (r93_opus_fp1, staged in lane out/): (a) dead volatile read -> `entity->unk_98 &= 0xF7FFFFFF;` on a u16
  field (no-op RMW; reload_cse_noop_set_p deletes the store, the load stays = retail) - 80B97298, 80CBD2E0, 800CE9F8;
  (b) volatile local -> type-pun `y = *(s32 *)&x;` (address taken keeps the stack slot) - 8181175C, 81810D28, 81810CD8.
  Never-accessed 8-byte frame (80B98600, 81334954, 80BEC6CC, 80BC3120, 8105A724): HOLD, no evidence for a local.
5. Refused (ledger/refused_trades.jsonl): 81910A9C `& addr_mask & addr_mask` double mask = fake dependency.

**Leads:** 80DE48EC pin-free spill text total 35 (16 frame bytes unexplained -> gdb assign_stack_local; r92_agyO_al1);
813274E4 needs an earlier no-code use of the page; 81326794 sched1 reload T-46; SLUS computed gotos (6 rows) need the
SLUS .rodata owner path (d9f94903e) - Opus; town 806D835C (lui page sharing) / 808119EC (shared pointer across loops);
type phase 13 (r91_types_p12/DESIGN.md) deferred - touches hundreds of rows, run when no lanes are in flight.
**Traps:** pool.py needs LAND_ISOLATED=1 in ITS env or it idles while landers run; batch landings (one land_gap for many
lanes) - per-lane landings queue for hours; Sonnet pin lanes 0/4 again (keep pins on Opus).

# Handover (2026-10-03 ~12:10, round 92 agy pilot: ARMED for 16:40Z, no lanes running now) - start here

agy now serves claude-opus-5-5-{low,medium,high} and claude-sonnet-5-5-{low,medium,high} (one SHARED "individual quota":
the r92 probes + 3 short runs exhausted it at 12:05Z, "Resets in 4h26m").
Kit: `launch_lane.sh <lane> agyopus|agysonnet` (AGY_MODEL overrides; agy_model.txt -> ledger tier opus/sonnet; caps in
config/lane_caps.json; set AGY_TIMEOUT to match). **Claude lanes get PROMPT_claude.txt, not PROMPT.txt**: the codex
prompt made agy/Vertex return "Your previous response was blocked by content safety filters" on EVERY first turn
(high and medium; retries too). Probes (3-min lanes): reading BRIEF/TOOLS/rows.md passes, running lab.py passes,
"remove the asm register pins ... start with the first row" passes and keeps working; "work through the rows as they
describe" + the duck line was blocked once and passed split in two - partly stochastic. The new template passed at
medium and high. Failed attempts are kept in each lane's attempt*_filter_block/ and quota429/.
**Running:** `_r92/chain.sh` (PID in ps as `bash work/native_lane/_r92/chain.sh`, log `_r92/chain.log`) sleeps to
16:40Z, then launches r92_agyO_p1 (8008F228, 81820800, 81810198), r92_agyO_p2 (80095160, 81845068, w_80048B8C,
800AE09C), r92_agyO_al1 alignment (813274E4, 80DE48EC, 81876014), r92_agyS_al2 Sonnet alignment on pin-free rows
(8001A0F0, 806D30B4, 808B2B04); relaunches a lane on a filter block or 429 (30-min wait), up to 3 tries; then
land_gap r92 + land_coherence for the alignment lanes, offbuild_after.json, status_after.txt. Then: check
land_gap.log / land_coh.log, commit, and compare with astra/sol61 (ab_report.py) before scaling agy-Claude up.
Left out on evidence: 800219C4 = PsyQ LIBCARD PATCH.OBJ (r91c_astra_al2 REPORT: stock-object route, owner call);
8087FEF0 = assembler lead (r91_sol61_p15 ASSEMBLER_LEAD.md), not a C lane.

# Handover (2026-10-03 ~09:30, round 91 END: codex wave done, no lanes running) - start here

**357 pins / 143 rows** (401 / 161 at pickup); rows off their build **55 -> 20** (9 pinned / 36 pins).
Landed: astra multi-pin + sol61 one-pin pools, compiler alignment waves r91b + r91c (via land_coherence.sh),
sol61 + luna goto/cleanup lanes, **type consolidation phase 12** (199 rows, 5 new shared headers; a83e8dbf6).
status.py parked-row fix (6610a48ac); autocommit now commits include/ too (c7a46d095).

**Monday (Opus quota): start from `work/native_lane/r91_harvest/`:**
- `open_rows.tsv` - 119 open rows ranked, each with best candidate path, distance/total, mechanism, next model.
  Top of the list is 1-4 words off (800219C4 reorg return liveness, 8087FEF0 li addiu/ori, 8008F228 sched1 ...).
- `HARVEST.md` (68 lanes, moves table), `learnings/` (47 draft notes) and `paragraphs/r91_harvest.md` - DRAFTS:
  review, then copy the good ones into tools/learnings/ and tools/lanes/brief_paragraphs/ (dedupe vs existing).
- `KIT_GAPS.md` (lane-written tools to fold into the kit), `GENERATORS.md` (20 CPU-generator proposals).
- Type phase 13: `work/native_lane/r91_types_p12/DESIGN.md` HOW TO CONTINUE.
- Script gloss pilot m00: `work/native_lane/r91_luna_gloss1/` (owner to judge before the other 53 modules).
- Cheap luna pools can keep going on the cleanup classes (`_r91/luna_briefs/`, builder lines in the 04:50 block).

# Handover (2026-10-03 ~00:20, round 91 codex wave RUNNING) - start here

**401 pins / 161 rows** at launch. Claude budget low, codex quota full: the owner asked for minimal Claude effort
directing astra + sol. Three pools (tools/lanes/pool.py, each lands itself through land_gap.sh with LAND_ISOLATED=1
when it drains; logs `work/native_lane/_r91/pool_r91{a,b,s}.log`, pool PIDs in `_r91/pool_pids.txt`):

- **r91a** astra c=3, 11 lanes `r91_astra_p1..p11`: the 25 multi-pin rows (75 pins) no astra/Opus lane served at their
  current text (`served.py --strong-kit`), 800AFA68 alone in p1.
- **r91b** astra c=3, 9 lanes `r91_astra_al1..al9`: **compiler alignment** - the 36 cdk-module rows the STATUS tracker
  lists off their build (late cell / cdk+crutch flags / stock cell in a cdk module). Each lane's question
  (`_r91/q_<lane>.md`) gives row -> TARGET (module recipe); stage-cell at the target, `--equal-pins` retires a crutch
  on pin-free rows. The 19 "other mismatch" rows (stock flavour / -G) were left out.
- **r91s** sol61 c=2, 15 lanes `r91_sol61_p1..p15`: the 44 one-pin rows of the same un-served list. Tidy NON_MATCHING
  debris in sol61 texts if the landing refuses them.
- pool.py gained the `sol61` key (gpt-6.1-sol, served tier sol6). Build script: `_r91/build.sh`; row lists `_r91/*.json`.

**Added 03:00 (owner: also goto readability, alignment wave 2, type phase 12, harvest):**
- **r91g** sol61 c=2, 10 goto lanes `r91_goto_g1..g10` (60 densest pin-free goto rows via build_goto_lane.py --densest,
  codex PROMPT.txt derived from AGENT_PROMPT.txt); lands at drain (land_lanes counts fewer gotos as a landing).
- **r91_types_p12** astra single lane (caps 2.5M tok / 300 min): type consolidation phase 12 per phase 11's HOW TO
  CONTINUE (town-root pointees unk_20/unk_38, D_80082E60). Delivers apply12.sh + manifest; NOT auto-applied - run
  `bash work/native_lane/r91_types_p12/apply12.sh --dry-run` then the sample, as in phase 11.
- `_r91/chain.sh` (log `_r91/chain.log`): after r91b drains -> recompute the tracker (`_r91/offbuild.py`) -> **r91c**
  alignment wave 2 (every row still off its build: the 19 "other mismatch" rows + r91b's open rows, briefed to start
  from the earlier lane's best candidate) -> after r91a/r91s/r91c drain -> **r91_harvest** astra lane: HARVEST.md,
  learnings/ drafts, paragraphs/r91_harvest.md, KIT_GAPS.md, GENERATORS.md, **open_rows.tsv = Monday's Opus queue**.
  Harvest outputs are drafts: review, then copy into tools/learnings + tools/lanes/brief_paragraphs.
- An early landing of the 20 lanes finished by 02:50 ran as `land_gap.sh r91early` (`_r91/land_early.log`).

**Added 04:50 (owner: luna on everything cheap + a read-only off-by-one investigation):**
- kitlib.admissible + land_lanes.sh now accept an equal-pin exact text whose decompiler leftovers fell (M2C_* tokens,
  temp_/var_/phi_ locals, argN, spXX, NON_MATCHING; comments excluded) and refuse one that adds them.
- **r91l** luna6 c=3 `--no-land` (log `_r91/pool_r91l.log`): `r91_luna_proto1-3` (M2C_UNK -> real prototypes),
  `rename1-3` (honest local names, "never a false name"), `nm1-2` (dead/stale NON_MATCHING arms), `goto1-3` (random
  easy goto rows). REVIEW a sample of rename/proto diffs for false names, then
  `LAND_ISOLATED=1 bash tools/lanes/land_gap.sh r91l <lanes>`. Briefs: `_r91/luna_briefs/`, rows `_r91/luna.json`.
- `r91_luna_gloss1` (luna6, 3M tok/180 min): literal JP->EN gloss of TOWN m00 with US-cut classification
  (gloss/m00.jsonl + GLOSS_NOTES.md), the script side project's raw material. Read-only outside its lane.
- `r91_luna_offby1` (luna6, read-only): why STATUS's shape table says 151 pinned rows while "Pin sites now" says 150.
  FINDINGS.md proposes a fix (not applied).
- alignment results land through `land_coherence.sh` (land_lanes skips equal-pin cell moves): chain2.sh does that.

**06:10 update:** r91a/r91s/r91g/r91c drained and landed (358 pins / 144 rows before r91c coherence). offby1 answered
(parked ovmovie/func_80041044; status.py fixed 6610a48ac). types_p12 delivered 201 verify-exact rows; gloss1 did m00
(353 items: 266 same, 13 abridged, 36 rewritten, 34 missing in US). `_r91/types12_apply.sh` (log types12_apply.log):
waits for r91l -> lands r91l (renames/protos spot-checked OK) -> apply12 dry run -> 40-row sample -> full apply.

**Owed after drain:** check each pool's land_gap result + gate, STATUS refresh, commit; harvest REPORT.md moves
(cheap: let a sol lane draft it); second wave = the 92 rows strong lanes already served at current text (sol61/astra
retry), and the 19 "other mismatch" alignment rows.

# Handover (2026-10-02, round 90 coupled-center diagnosis) - start here

**401 pins / 161 rows**, unchanged. `dungeon/func_80095160` still has three
pins; no exact reduction in 22 scored variants. Production source unchanged.

- Important correction to r89: raising center-Y's priority alone steals
  the X center's s0 and disrupts allocation. **Both centers must be ordered
  X before Y, ahead of direction**, preserving the table-offset register.
  An exact preference replay checked against cc1 reproduces 24/24 decisions;
  moving both centers restores only the three desired register roles.
  This is a diagnostic result, not a compiled C solution.
- Map/center union sharing is split by CSE; scalar sharing changes early
  registers. Moving center-Y after height-delta preparation does not shorten
  its post-sched1 lifetime. Sharing X center with the Y work variable raises
  X correctly but leaves Y wrong and changes scheduling (total 14).
- Best inherited leads remain center total **12** and tile total **3**.
  The latter's extra mask cannot simply be removed by widening: that restores
  the wrong scheduling. New three-pin traces confirm the earlier boost/tie
  diagnosis. No additional pin, dummy use, or compiler recipe was introduced.
- Evidence and next C-rebuild constraint:
  `docs/evidence/r90_80095160_coupled_centers.md`. Lane:
  `work/native_lane/r90_sol_80095160`, including `replay_center.py`, ignored
  pass dumps, candidates, and `REPORT_TABLE.md`. Start from the landed
  **three-pin** source. No agents/background lanes were launched.

# Handover (2026-10-02, round 89 rubber-duck follow-up)

**401 pins / 161 rows** (402 / 161 at pickup).

- Continued `dungeon/func_80095160` as requested: **4 -> 3**, exact at the
  same `2.7.2-cdk-G0` recipe. The `$3` scratch pin supported final comparison
  temporaries: without it local allocation occupied v0 and forced the
  global return result to a0. Writing the signed shift and boolean back
  into `coord_or_height` removes that local quantity. First targeted trial
  exact; no new pin, dummy use, or recipe change.
- Validation: independent row exact; both NON_MATCHING builds compile;
  all seven nonempty remaining-pin erasure subsets miss; t2 noop;
  **dungeon_engine 393,216-byte window MATCH; SLUS SHA-1 MATCH**.
- Rubber-duck evidence: `docs/evidence/r89_80095160_rubber_duck.md` answers
  what each pin supports, what erasure changes, which source statements
  matter, and which known residue applies. Lane:
  `work/native_lane/r89_sol_80095160` (DUCK.md, pass traces, 32 measured
  variants, REPORT_TABLE.md, candidates, landing.log).
- Three remain: center Y `$20` (copy folding/saved allocation), tile X `$5`
  (first-call scheduling tie plus later single-set boost), failure barrier
  (EQ fall-through delay-slot selection and return-block merging).
  New two-pin near-misses based on the landed three-pin source:
  `cand/two_center_fresh.c` total **12**, all register substitutions;
  `cand/tile_narrow_u16.c` total **3**, extra argument mask + first-call tie.
  Neither is ready to land. Do not repeat statement-order-only trials on
  the later tile shift: checks.py proves its boost makes those inert.

The shared-global brief and `tools/learnings/disjoint_role_hosting.md` now
carry the comparison fix. No worker agents or background lanes were launched.
Continue this row from **three pins**, or the first-touch pool (`8182C800`).

# Handover (2026-10-02, round 88 single-row pickup)

**402 pins / 161 rows** (403 / 161 at pickup).

- Picked the next named row, `dungeon/func_80095160`: **5 -> 4**, exact at
  its existing `2.7.2-cdk-G0` recipe. Removed the floor-height `$18` pin:
  a union hosts the actor pointer and later height result; the finished
  target-X variable hosts the placement status. Both variable-hosting
  spelling trades are recorded. No new pin or compiler change.
- Validation: independent row verifier exact; old/new NON_MATCHING builds
  compile (assembly differs, shared-C rewrite); t2 noop; all 15 nonempty
  subsets of the four surviving pins miss; **dungeon_engine 393,216-byte
  window MATCH**; **SLUS SHA-1 MATCH**.
- Evidence: `docs/evidence/r88_80095160_height_storage.md`. Lane:
  `work/native_lane/r88_sol_80095160` (49 measured variants, REPORT_TABLE.md,
  full retail site map, candidates, ignored scratch/ pass dumps, landing.log).
  Transferable finding: `tools/learnings/disjoint_role_hosting.md`.
- Remaining pins: coord/height `$3`, center Y `$20`, tile coordinate `$5`,
  and the failure-return scheduling barrier. The evidence note assigns a
  concrete next measurement to each. Start from the new four-pin source.

**Next:** continue the round-86 first-touch pool, e.g. `8182C800` (4 pins),
or take a focused follow-up from either single-row evidence note. No worker
lanes were launched; this was a single-agent pickup.

# Handover (2026-10-02, round 87 single-row pickup)

**403 pins / 161 rows** (404 / 161 at pickup).

- Picked the first next-pool row, `dungeon/func_800AFA68`: **10 -> 9**, exact at its
  existing `2.7.2-cdk-G0` recipe. Removed the rotation-matrix `$22` register pin;
  the existing entry memory keep now uses `view_matrix` instead of `transform_flags`.
  This is a recorded pin trade, not a pure-C solve. The old keep's allocation effect
  was what required the rotation pin. No new pin statement or compiler change.
- Validation: independent row verifier exact; both NON_MATCHING builds produce
  identical assembly; t2 noop; **dungeon_engine 393,216-byte window MATCH**;
  **SLUS SHA-1 MATCH**. Fresh single/pair erasures found no further exact removal.
- Evidence: `docs/evidence/r87_800AFA68_pin_trade.md`. Lane:
  `work/native_lane/r87_sol_800AFA68` (34 variants, REPORT_TABLE.md, candidates,
  compiler dumps under ignored scratch/, landing.log).
- Remaining 800AFA68 leads: the 8-pin entry-HIGH candidate still has total 2;
  typed scratch members reduce the scratch-pair erasure's listing residue from
  38 to 16 (byte total 16). Neither is ready to land; both start from the old text.
  The nine surviving pins remain unresolved.

**Next:** continue the round-86 first-touch pool, e.g. `80095160` (5 pins), or use
the evidence note for a focused 800AFA68 follow-up. No worker lanes were launched.

# Handover (2026-10-02 ~15:00, round 86 end of day; no lanes running)

**404 pins / 161 rows** (527 / 175 this morning).
- CPU sweep 2: -6 (bbc824854).
- Twin census rerun: no new switches (remaining twin disagreements are cross-object copies).
- Fable r86_fable_mech2: nothing exact; 8009F018 / 800C4A80 / 800A1AD4 parked at totals 1 / 2 / 6 (MECHANISM.md lists the missing constructs).

**Next pool:**
- 26 rows / 70 pins with no lane at their current text (800AFA68 10, 80095160 5, 8182C800, 80CC085C, 800AA854, 800A8714, 800A2564, 80084340 4 each, ...).
- 69 rows / 122 pins with no Opus/Fable lane at current text (served_now.json).

# Handover (2026-10-02 ~13:00, round 86 wave 4 landed; no lanes running) - start here

**410 pins / 163 rows** (527 / 175 this morning).

**Tracker:** 55 overlay rows off their build (16 pinned / 55 pins); 14 SLUS rows.

**Wave 4 landed:**
- 800969CC 7->0 (message cursor priority via one statement per call + hosting).
- 8180A990 4->2 (callee's defined (void) arity).
- 8008A31C 3->0 (page hosted in the reused mask variable = sched1 anti-dependence).

**Open near-misses at cdk-G0** (lane REPORTs hold the files):
- 8009F018: 0 pins, total 2 (r86_opus_w4b c/f018_best.c). The z = center_x copy conflicts cse head / sched1 tie / optimize_reg_copy_1.
- 800C4A80: 0 pins, total 2. -fno-cse-follow-jumps imitated cse following the jump past the y-bounds check.
- 800A1AD4: 0 pins, total 5 (r86_opus_w4c c/a_best_ydir.c).
- 800CDFD8: 1 pin, best 14.
- 81876014: 7 pins (three cse/sched effects).

**Deferred:** deleting the _fold_selfinc_la code. Default-off already gives genuine ASPSX behaviour; delete it together with the lo-fold once code2 / w_8003E188 are ported.

# Handover (2026-10-02 ~11:45, round 86 reconciliation pass + crutch lanes landed; no lanes running) - start here

**422 pins / 165 rows** (527 / 175 at this morning's pickup).

**Incorrect-compiler tracker:** 58 overlay rows (19 pinned / 69 pins); 14 SLUS rows off their region build (59 this morning).

**Reconciliation landed:**
- configure.py CC_VER override blocks folded.
- land_recipe_move.py --slus-region-b (sound TU -> stock 2.7.2, 11 rows).
- cd_command_state -G32 module (7 rows).
- 14 SLUS modules (23 rows) via work/native_lane/_r86/land_slus_module.py (the module lander: slus_modules.json recipe + CC_VER + slus.build.ninja / slus.jsonl / rows re-derived, SLUS gate or full restore).
- Module census refreshed (r86_opus_census: per image run / object direction counts, tie_with, 3 -O1 copies -> town_o1_misc.c, tracker honours ties) + 72 byte-neutral census switches.
- maspsx _fold_selfinc_la retired (switch + default OFF; 2 slus consumers to cdk; 8001AA50 3->0 at its stock 2.6.3-G0).

**Pins landed this stretch:**
- 800ABBF8 8->0.
- 80B471EC 4->0 (loop.c movable order).
- 8197C800 3->1.
- 8001AA50 3->0.
- 8080C650 crutch retired.

**Rules in briefs:** structured_loops gains movable order; dslot; param_priority; crutch_flags.

**Queued** (_landq/handover_todo.txt):
- Delete the _fold_selfinc_la code (and lo-fold once its last consumers port).
- prefs.py 2.6.3 support.
- The pre-existing maspsx hash test note.

**Next:**
- 19 pinned off-recipe rows: 800C4A80 16, 81876014 7, 8009F018 7 (0p t9), 800969CC 7 (needs big-row lane), 80DE48EC 5, 8180A990 4, ...
- Remaining near-misses: 800C4A80 t2, 800A1AD4 t11, 8008A31C t13, 800CDFD8 t13.
- 14 SLUS rows (sched ties, two big rows).

# Handover (2026-10-02 ~11:45, round 86 waves 2-3 landed; no lanes running) - start here

**439 pins / 168 rows** (527 / 175 at the round-86 pickup this morning).

**Waves 2-3 landed (all gated):**
- 80DB9000 20->0 (Fable; structured loops - MECHANISM.md).
- 8187A9A8 13->0, 81892C5C 3->0, 818B0E10 1->0 (crutch cells retired via the structured-loop recipe).
- 800C379C 4->0 (dbr use-marker rule).
- Build-up trades with one new KEEP each: 800AC008 3->2, 800BFE94 5->3.
- 8009612C crutch flag retired; 80084340 goto removed.

**SLUS reconciliation:**
- 312 byte-neutral moves to 2.7.2-cdk (land_recipe_move slus path).
- Sonnet sl1-sl3: 24 rows rewritten.
- r86_opus_decl: w_80059F8C (non-const cast read; owner rejected const) and w_80043C30.

**Rules now in the briefs:** structured_loops (+ GameWork* reads), crutch_flags, param_priority entry-move run, dslot
use-marker copy, fixed-address non-in-struct reads, SLUS small-data extents.

**STATUS tracker fixed** (-G0 overlay yardstick + a SLUS line): 158 overlay rows / 59 SLUS rows off their build.

**Queued** (_landq/handover_todo.txt):
- The SLUS reconciliation pass:
  - CC_VER override blocks;
  - 7 -G32 dodges;
  - region-B stock flag drops (w_8005D7BC, w_8005E97C staged in r86_sonnet_sl3/held and r86_sonnet_sl1/out);
  - module-member recipes.
- module_recipe_census refresh.
- maspsx _fold_selfinc_la retirement (w_8004A6C0).

**Open near-misses** (lane REPORTs):
- 800C4A80: 0 pins, total 2.
- 80B471EC: 0 pins, total 4 (r86_opus_sl2 cand/B4_best_b12.c; one sched2 tie).
- 800A1AD4: 0 pins, total 11.
- 800CDFD8: 13.
- 80DE48EC: frame + R1.

**Routing:**
- Opus pins at 1-2 rows/lane on first touch / crutch rows; second-pass near-miss lanes 1-2 rows.
- Sonnet reconciliation ~60%.

# Handover (2026-10-02 ~10:30, round 86 wave 1 landed; Fable r86_fable_mech still running) - start here

**483 pins / 173 rows** (500 at the wave start).

**Landed (all gated):**
- 81905FD0 6->0 (r86_opus_ft1).
- 800BAE88 6->1 (r86_opus_up build-up from the clean text: a new KEEP_NV(key) for six pins, tracked trade; egcs crutch retired).
- 800A3D40 5->1, 80095160 6->5 (r86_opus_ft2).
- 80098144 2->1 (sonnet_p2).
- tptab step B completed for 81820800 and 818DA800.

**Reconciliation (owner rule: no C for a wrong compiler):**
- Sonnet lanes rc1-rc5: 21 pin-free rows rewritten exact at the proven recipe. Their reports list ~30 open rows with the named residue.
- CPU byte-neutral switches: 124 (G8->G0 + crutch cells), 8 twin-census, 7 scan-2.
- Town -O1 family: 8032E254 moved into seg_o1 plus 3 copies.

**Census tools (work/native_lane/r86_eval):**
- recon_scan.py / recon_scan2.py: off-recipe rows at the target.
- twin_census.py + twin_score.py: relocation-masked twins must share a recipe. 32 rows conflict with an r84 "real" verdict and need a pass.
- o1_census.py: town -O1 stretches. -O1 is fully registered now.

**Model routing measured today:**
- Sonnet on pins pays nothing: p1 0 pins / 340k tokens, p2 1 pin / 250k.
- Sonnet on reconciliation pays: 21 of 49 rows at ~120-250k per lane.
- Opus first-touch: 2 rows/lane.

**Held / side leads:**
- 8046A828: zero-arg passthru; lead: call with the parameters.
- 8009CCC4: falls only at -G8.
- 80813E14, 80952114: unsplit addresses; maybe a non-splitting object.
- 806D23A4, 808106A4: stock rows exact at cdk -O1.

**Kit traps:**
- Never pgrep for lander names inside a waiter whose own command line holds them. This deadlocked for an hour on 10-02. Use land.lock instead.
- Reconciliation lanes need their own AGENT_PROMPT (the pin-lane prompt made rc4 stop at "0 pins").

**Next:** (also the queued SLUS RECONCILIATION PASS in _landq/handover_todo.txt: fold CC_VER.update overrides, retire 7 -G32 dodges, region-B stock flag drops, module-member recipes)
1. Opus on the 23 pinned rows still on late/flag cells (86 pins), at the proven recipe (recon_scan2.jsonl).
2. The twin-conflict pass.
3. SLUS reconciliation: region A cdk -G8 / region B stock sound TU.
4. bg21-26.

# Handover (2026-10-02 ~04:50, round 86 pickup: evaluation + CPU sweep + owner calls landed; no model lanes) - start here

**500 pins / 174 rows** (527 / 175 at pickup). Evaluation: work/native_lane/r86_eval/ASSESSMENT.md (tables: pins, served
at current text, Pareto of near-misses for 6+-pin rows, reconcile.txt).

**Landed today (all gated):**
- **CPU sweep** of every pin generator over the pinned rows at their current text: -18 pins (6f24bc26e, script
  r86_eval/cpu_sweep.sh). Biggest: 8133AD74 4->1, 8194D354 4->2.
  - KIT GAP behind it: switch_land_lanes.sh runs land_lanes.sh without EXTRA_T, so the cascade_extra generators
    (t88-t120) never swept r85's landings.
  - t130-t135, t26/t64/t60/t61/t67 are in no cascade.
  - Fix this, or re-run the sweep after each round.
- **Owner calls (owner 10-02: "go with your recommendation"):**
  - form R 818E6800 3->1; 81912154 5->3 (moved re-copy); 81084D04 3->0 (dead pre-loop store) - 0b85cdee2.
  - tptab step B, 3 rodata owners: 81880800, 8182C800, 8197C800 (092b14271). 81820800 and 818DA800 need re-staging
    on their newer texts.
  - maspsx lo-fold guard, patch + activation: 36b1b090b, 740f61d47. Both gate_all --all; maspsx 421 tests pass under
    .venv.
  - slus pair w_8004A700 / w_8004A7D8, rebaselined.
  - 8008F814 2->1 at cdk-G0, retiring the 2.8.1-G0 crutch (1a4fb3711).
- **Held:**
  - form S (fake dependency).
  - joint-scan hit 8009CCC4 (barrier falls only at -G8 = a cell its module doesn't use): a side lead, check the
    declaration of the symbol whose addressing differs.

**Owner rule (10-02):** never write C to satisfy a wrong compiler setting. Pin removals that need a cell or flag the
module doesn't use are side leads, not landings. Reconcile every row to its proven module recipe eventually.

**Reconciliation debt** (reconcile.txt, against r84_fable_build/VERDICT.tsv):
- 32 pinned rows / ~126 pins are registered on crutch cells, 15 of them on fitted 2.8+/egcs cells. This includes the
  big rows 800C4A80, 8187A9A8, 800ABBF8 and 81876014.
  - Their pins likely compensate for the wrong compiler (owner agrees).
  - Work them ONLY at the proven recipe and land via land_coherence.
- About 140 pin-free rows are off-recipe.
- 132 overlay rows are registered at -G8 (overlays are -G0 everywhere): CPU byte-neutral switches.

**Next, in order:**
1. A first-touch Opus pack from the 26 rows with no lane at their current text (served_now.json; e.g. 800AFA68,
   80095160, 81905FD0, 80A20A28).
2. A sol 6.1 wave on the 34 two/three-pin rows sol6.1 never saw at current text (codex quota permitting).
3. One Opus lane on the clean-rewrite rows (800C4A80 0-pin total 3 at cdk-G0, 800BAE88 total 4): pin only the residual
   alloc_need names.
4. Fable mechanism lane: 80DB9000 (scratch single set from a hard register), 800AFA68, 800C9858.
5. Blind rewrites as reference for 800C9858 / 800CA184 / 800969CC / 8009E0EC / 819613A8 / 8180C3C0.
6. bg21-bg26 (prebuilt; all Opus-served at current text).
7. A reconciliation pass over the 32 crutch-cell pinned rows.

fragclone refreshed: no new clone sources. The stale autocommit / clone_watch loops from 09-19/09-21 were killed. Lanes'
scorer root was rebuilt after the maspsx change (mk_ovl_root.sh in land_chain3).

# Handover (2026-10-01 ~23:40, round 85 WRAPPED UP on the owner's request; every lane finished and landed) - start here

**527 pins / 175 rows** (1,201 / 360 at round-85 start: -674; 886 at the start of this session's stretch).
**Remaining:** 66 one-pin rows, 57 rows with 2-3 pins (144 pins), 44 rows with 4-7 (210), 9 rows with 8+ (111).
- By container: dungeon 433, town 65, slus 24, main 5, ovmovie 4.
- Biggest rows: 80DB9000 20, 800C4A80 16, 800C9858 15, 8187A9A8 13, 800CA184 13, 800AFA68 10, 800ABBF8 8, 81876014 8, 8009E0EC 8.

**What paid in the last stretch:**
- **Two-row Opus "big-row" lanes, bg1-bg20 (~110 pins).** Recipe in work/native_lane/_r84/bg_prompt.txt:
  - real loops over named symbols;
  - the refs/live moves alloc_need/prefs.py ask for;
  - per-lifetime locals;
  - hosting a role in the variable that holds retail's register;
  - single-set vs multi-set for the sched1 birthing boost;
  - field-width locals;
  - K&R short widths.
- **Clone sources.** The pin-free clone 818B1664's probe loop (bg9, pclone: 4 rows 27->0) and tools/lanes/fragclone.py, the retail-code partial clone finder (5 rows 15->0).

**New kit tools:**
- counts.py: reg_n_sets.
- dbr.py: delay slots.
- prefs.py + tools/alloc_prefs.py: an exact global.c preference replay, 1,563/1,563 allocnos.
- tools/lanes/fragclone.py.

**Next:** launch the built packs r85_opus_bg21-bg26 (12 rows with 4-5 pins; prompt pattern in the handover_todo line). Run fragclone.py first on every remaining row (candidates_by_row.tsv in r85_opus_fragclone).

**Owner decisions still pending** (detail in work/native_lane/_landq/handover_todo.txt):
1. Form R, the unchanged-field re-read: 818E6800 is held, plus candidates 81876014, 818F2800, 8181214C, 800BAE88 and others.
2. 81912154 6->3: a moved re-copy is held; the 6->5 fallback landed.
3. 81084D04: dead pre-loop store.
4. maspsx lo-fold guard.
5. tptab step B: rodata-first owner.
6. Spellings to eyeball: 81845068, 808135E0, 800B39E4.

# Handover (2026-10-01 ~20:30, round 85 in progress: Opus multi-pass lanes, rule harvest, dbr tool) - start here

**658 pins / 196 rows** (1,201 / 360 at round-85 start). The goal from the owner (10-01) is to drive asm pins to 0 with all tiers.
**What paid this round:**
- Opus general and second-pass lanes, 5-6 rows each, briefs led by the new paragraphs: about 1-3 rows per lane, more on first touch.
- sol 6.1 current-text waves on 1-3-pin rows.
- Fable mechanism lanes: surviving copy, birthing boost, regequiv.
- Structural fixes: the w_8005EDA0 SLUS rodata owner, the 804FE77C row split (TOWN sector leftover + DUNGEON header), and 11 computed-goto rows made real switches with their tables at the retail address (tptab step A).

**New rules (tools/learnings "Round 85" sections + tools/lanes/brief_paragraphs):**
- shared_global: host a value in another block's variable so it becomes a global allocno; cdk local-alloc sorts a block's first three quantities by slot.
- copy_host: M1 0/1-flag branch, M2 reload_cse read-back, M3 live after use.
- early_arg, call_arity (now also real callee return types, e.g. bzero void*), narrow_copy (with the loop-tail shadow copy).
- one_trip, with the for-loop VTOP note deciding reorg's prediction.
- dslot: the EQ not-taken pattern.

**New kit tools:**
- tools/lanes/lanekit/counts.py: reg_n_sets at flow/combine, plus the sched1 boosted insns.
- tools/lanes/lanekit/dbr.py (also `why.py --pass dbr`): gdb-traced reorg, each candidate and its reason, plus a DECIDING line.
- alloc_sim and lreg_explain now support the egcs cells.

**OWNER DECISIONS PENDING (work/native_lane/_landq/handover_todo.txt has the detail):**
1. Form R (re-read an unchanged field after a store through the same base as a no-code second set): 818E6800 3->1 is held. If accepted, add r85_fable_birth/paragraph.md to the briefs; R-form candidates are 80A20A28, 81912154, 800CDFD8, 80098520, w_80048B8C, 818F2800 and 8181214C. Form S (same-value re-copy, 81941338) is held as a crutch.
2. 81084D04 0-pin text with a dead pre-loop store (r85_opus_j1 cand/b84_REJ_dxboth.c).
3. maspsx lo-fold guard (r85_opus_lofold: 4-step plan, 8008F814 2->1 plus a crutch cell retired).
4. tptab step B "rodata-first owner" for single-function DUNGEON composite modules (r85_opus_tptab/LANDING.md; 5 rows now, 10 later).
5. Spellings to eyeball (landed): 81845068 (store moved into an existing do-while(0)), 808135E0 (written-out setaddr mask), 800B39E4 (scratch pointer re-set at the loop top).

**Remaining families:**
- Birthing boost: about 17 rows; most need form R or a natural second set.
- Opaque page base: 81329AC4, 813274E4, 818FECCC.
- Register-priority hairs: alloc_need names the inequality on each.
- Delay-slot rows: 8009CCC4, 800C379C.
- Big rows: 80DB9000 20, 800C4A80 16, 800C9858 15, 8187A9A8 13, 802835B8 13, 800CA184 13, 800AFA68 12, 8180E7F4 11.

**Running at writing:** r85_sol61_w1-w16 (aq_watch auto-lands).
**Landing:**
- Runner queue: work/native_lane/_landq/land_queue.txt (`tag|lane|pin-or-switch|what`).
- Cell moves: c8_chain2.sh.
- Bespoke: work/native_lane/_r84/land_rodata_eda0.sh and land_split77c.sh are the patterns for patch-plus-gate landings.

# Handover (2026-10-01 ~09:00, round 84 CLOSED; round 85 sol 6.1 wave running) - start here

**1,201 pins / 360 rows** (1,483 / 487 at round-84 pickup: -282). maspsx_d3 applied as reviewed (587652d78: behind
--gp-limit-from-cc1, default OFF; ON = 0 bytes changed but la spelled lui/addiu, one golden-hash test - owner's call to
enable). Every overlay window (--all) + SLUS MATCH at 587652d78.
Round 84 levers, in order of yield: sol 6.1 waves on 1-3-pin rows never sol61-served at their CURRENT text (~180 pins over
five waves; partial wins re-enter the pool with new text), build structure (r84_fable_build: one cdk -G0 -O2 build + town
-O1 debug family + stock objects; 2.8.x/egcs cells are fitted), stock objects worked as stock rows (13 pins), the town -O1
family (4 pins + 18 crutch recipes), opaque base classes A/B/C (r84_fable_opaque; ~25 pins so far), cse/nosr flag classes
(flags, few pins). Rules: tools/learnings/pin_removal_possibilities.md "Round 84"; codex brief paragraphs r83_rules,
stock_rows, opaque_c.
**Round 85 (running):** r85_sol61_s1-s24 (96 one-to-three-pin cdk rows, launch_wave.sh cap 12, autoqueue lands).
**Open / next:** class-C rows not yet served (CLASS.tsv in r84_fable_opaque); 813274E4 (combine folds a dying page into a
const address); the 13 fitted 2.8.x carrier rows + RANKED_PINNED.tsv (r84_fable_build) at cdk-G0; the 47 held stock-flavour
switches (r84_fable_build/cells.jsonl, 1-3 deciding rows each) + 17 undecided; a named-struct tidy pass over r84_opus_opqC's
anonymous pad-struct field macros (8187B1F4, 800A406C); r84_sol61_s37 held func_80FB7000 (build fails); 800C9858 (astra c1
equal pins, held); 8001BA1C (2.6.3 birthing boost, 4 off); stock rows 808B8184 (3), 8080DAB8 (10), 808135E0 (33), 8080C650.
**Landing:** c8_chain2.sh (cell moves), runner queue (registered-cfg rows), work/native_lane/r84_fb_cdk/land.sh pattern for
byte-neutral switches. Any runner restart must close fd 8 (`8>&- 9>&-`).

# Handover (2026-10-01 ~06:00, round 84 in progress: build structure, -O1 debug family, stock objects, sol 6.1 waves) - start here

**Pin sites now: 1,322 in 405 rows** (1,483 at round-84 pickup). Owner calls of 09-30 all approved and done: 8046C280 at -O1 (trade), w_80049F68
6->0 (single-member slus module recipe; e1c553122), 8028B994/808B2E74 accepted, module splits (221f5522f) incl. the town -O1
image run; **maspsx_d3 patch still to apply at the END of round 84** (gate --all).
- **Build structure (r84_fable_build):** one 2.7.2-cdk -G0 -O2 build + town -O1 debug family + stock Sony/devkit/minigame
  objects (rules: tools/learnings "Round 84"). 100 byte-neutral switches landed (ee7113f1f); 47 stock-flavour switches HELD
  (r84_fable_build/cells.jsonl, decided by 1-3 rows each); 17 held undecided (cells_held_undecided.jsonl); module patch
  applied (f151efb7b). RANKED_PINNED.tsv = the pool at the proven recipe.
- **Landed lanes:** r84_opus_walk (3 flag drops), r84_opus_scratch (800A5398 5->0), r84_opus_cse (3 spellings; its 21
  byte-neutral drops only landed with ee7113f1f - land_coherence bug fixed ec2a8021d), r84_opus_o1 (4 pins), r84_sonnet_o1,
  r84_opus_stock (6 pins), r84_opus_fitted (800B998C cell only), codex r84_astra_b1-b8, r84_sol61_s1-s32.
- **Running:** r84_opus_stock2 (7 stock rows), r84_sol61_st1 (5 stock one-pin rows), r84_sol61_s33-s40 (2/3-pin),
  Fable r84_fable_opaque (opaque constant base family: ~57 rows / ~111 pins on integer-page / scratch-base locals).
- **Next:** sol 6.1 on the remaining 2-pin rows (two-pin probe 7/12 to zero) and a 3-pin decision from s38-s40; Opus on
  RANKED_PINNED fitted rows; apply the opaque-base rule if Fable finds one; maspsx_d3 at round end.
- **Landing (c8):** c8_chain2.sh now pauses the runner before waiting (a codex stream starved it); any script restarting
  land_queue2.sh MUST close fd 8 (`8>&- 9>&-`) or the runner holds c8_land.lock forever. Byte-neutral switches: copy of
  work/native_lane/r84_fb_cdk/land.sh (isolated gate, no codex check).

# Handover (2026-09-30 23:30, round 84 started: cse-flag mechanism, walker residual, scratchpad-struct class + codex wave) - start here

**Pickup 1,483 pins / 487 rows.** Round plan (census first: flag x pin table, erase census near scratch accesses):
- **r84_opus_cse** (mechanism, Opus): what -fno-cse-follow-jumps / -fno-cse-skip-blocks stand in for; 61 rows
  (work/native_lane/_r84/cse_rows.tsv: 22 pinned / 85 pins, 39 pin-free); CLASS.tsv + MECHANISM.md + apply brief.
  Next: Sonnet apply lanes on the pin-free rows, Opus on the pinned (the r83 pattern).
- **r84_opus_walk** (Opus): the last nosr rows 800CB068, 80090D8C, 8000F774, 8001BCD4, 800CDFD8 (literal += K walker).
- **r84_opus_scratch** (class, Opus): scratchpad stores as struct members (r83 rule) over 70 pinned rows / 343 pins
  referencing 0x1F80xxxx (206 live sites within 6 lines); fixture tools/fixtures/memdep; CLASS.tsv + generator spec.
- **Codex (autoqueue lands them; runner restarted, pid in _landq/runner.pid):** r84_astra_b1-b3 (807B040C+80092824,
  80A4707C+8195F0BC, 81331C88+800A3D40), r84_sol61_s1-s3 (15 one-pin rows never served by astra/Opus/sol61).
- New brief paragraph tools/lanes/brief_paragraphs/r83_rules.md (rounds 81-83 rules for codex packs).
- Flag census (09-30 night): pinned rows with flags 58 / 238 pins: cse-follow-jumps 13/44, cse-skip-blocks 10/42,
  expensive-opt 10/53, schedule-insns 10/46, rerun-cse 8/39, nosr 7/29. The town 8032xxxx -fno-schedule-insns
  -fno-schedule-insns2 rows are the town/main.c -O1 question (modsplit owner call) - not worked.
Owner calls still pending from round 83 (unchanged): 8046C280 -O1, 8028B994/808B2E74 review, w_80049F68 module
re-certification, modsplit patch, maspsx_d3.

# Handover (2026-09-30 evening, round 83 closed: strength-reduce class applied) - start here

**1,483 pins / 487 rows** (1,565 at this session's 13:14 pickup; ~51 pins from the r83 lanes, the rest from the peer's astra/sol lanes a41-a46, s14). Rows registered with -fno-strength-reduce: 71 -> 14.
Rules: tools/learnings/pin_removal_possibilities.md "Round 83" (both blocks). Lanes: r83_fable_nosr (mechanism),
r83_opus_b1/b2 (819B3414 32->0, 818D4E68 1->0), r83_sonnet_n1-n6 (41 of 46 pin-free flag rows exact, ~110-250k tokens
per 7-8 rows: Sonnet applies this rule cheaply), r83_opus_n1-n3 (12 of 14 pinned flag rows landed, 21 pins).
**Still flagged (14):** open near-misses 800CB068 (2 words, r83_sonnet_n4/experiments), 8000F774 (2, n6 cand/h2.c),
8001BCD4 (2, n5 cand/bcd/v7.c), 80090D8C (12, n4), 806D30B4 (44, not a walk), 800A2564 (8 with 7 pins, opus_n2
cand/2564/k2.c), 800CDFD8 (16 with 0 pins / 0 volatile, opus_n3 cand/fd8/w5e.c); never served this round: 818B0E10,
818C3B90 (was in astra a41); 8000EEE0 + 8001AFEC (flag never mattered; 8001AFEC's flag-only drop was skipped by
land_recipe_move - non-splitting target, land via c8_chain2/coh.sh); slus w_80049F68 (exact text staged in
r83_fable_nosr/out, single-member module gp_order_bytes_owner: needs config/slus_modules.json recipe + re-certification
with a reviewer), w_8005914C, w_800599B0 (sound-TU scalar declaration / -G question).
**Owner calls pending:** (1) town/func_8046C280: 0-pin natural text exact only at `2.7.2-cdk-G0 -O1`
(r83_opus_b2/r3/N2.c) - held; (2) 8028B994 landed 4->0 with one kept flag (-fno-cse-skip-blocks) and 808B2E74 2->0
with a two-statement offset spelling - review; (3) w_80049F68 module re-certification; (4) modsplit patch
(r83_sonnet_modsplit: apply only c_server 0x804010F0 block, town/main.c runs, lshop, card_opt, ovl_7f565800; then
regenerate the census with no lane landing); (5) optional maspsx_d3 patch (0 rows).
**Follow-ups:** a typed-view tidy pass over the landed `(View *)((u8 *)base + i * K)` spellings (Sonnet, byte-exact
per row); the "literal += K walker left unreduced" residual class (800CB068, 80090D8C, 8000F774) wants one mechanism
lane; scratchpad-as-struct and s16-local rules are sweep candidates over rows with scratch barriers / volatile byte
reads; 800C4A80 0-pin text 3 words off (r83_opus_b2/r2/rv_all.c). Harvest candidates for tools/lanes:
r83_fable_nosr/tmp/{loopcensus,cc,class_census}.py, r83_opus_n2/tmp/{lp.sh,rtl.py}. mk_ovl_root.sh was run after the
last landing. Note: commit ae5595de6's message lists w_80049F68 and 2f3e54bd9's lists two 2.6.3 rows that landed in
872d3d40b instead.

# Handover (2026-09-30 15:20, round 83 / c8 continuation: strength-reduce class decided, apply lanes running) - start here

**Landed:** 819B3414 32->0 (1227969b7, r83_opus_b1), 818D4E68 1->0 (d42e83430, r83_opus_b2), slus/w_800500B4 2->0 at plain
cdk (ae5595de6, r83_fable_nosr). **1,499 pins / 493 rows.** Rules: tools/learnings/pin_removal_possibilities.md "Round 83".
- **r83_fable_nosr:** -fno-strength-reduce hid pointer-walk spellings of indexed loops (MECHANISM.md, CLASS.tsv: 67 of 71
  flag rows; generator spec t136_indexwalk). Byte-neutral flag drops to land: slus/w_800537D0 -> 2.7.2-cdk,
  dungeon/func_800BE8D0 -> 2.7.2-cdk-G0, main/func_8001AFEC and town/func_8033077C (flag drop at the registered cell).
- **NOT landed (commit ae5595de6's message overstates): slus/w_80049F68 6->0** - staged in r83_fable_nosr/out/slus, gate
  MATCH in isolation, but it is the single member of slus module gp_order_bytes_owner: land_recipe_move.py skips grouped
  moves. Needs config/slus_modules.json modules[27].recipe.ccflags "" + the text + SLUS gate + module re-certification
  (tools/fidelity/certify_slus_module.py needs a reviewer) - owner/review step.
- **Apply lanes running (index-walk brief work/native_lane/r83_q_nosr.md):** r83_opus_n1-n3 (14 pinned flag rows),
  r83_sonnet_n1-n3 (24 pin-free flag rows, nearest first). 23 far pin-free rows unserved
  (r83_fable_nosr/tmp/apply_lanes.txt lists the served ones). Land overlay moves with c8_chain2.sh, slus with c8_move.sh.
- **r83_opus_b2 open:** 800C4A80 0-pin text now total 3 (r2/rv_all.c; one s4/s5 allocation order: centre pseudo needs
  refs 3); **town/func_8046C280: 0-pin natural text exact only at `2.7.2-cdk-G0 -O1`** (r3/N2.c; debug-print macro
  expanded five times; 19/38 module rows break at -O1) - OWNER CALL: per-row -O1 trade (8 pins + six one-trip blocks
  gone) vs hold. Open slus: w_8005914C, w_800599B0 (scalar loads that must not be in-struct: sound-TU -G / declaration
  question).
- **r83_sonnet_modsplit:** modsplit.py (lane dir) splits mixed-bag modules; patch NOT applied. Clear splits: c_server.c
  block 0x804010F0-0x80402508 = 2.6.3-G0 (33/34), town/main.c runs = cdk-G0 -O1 (33/43) / 2.7.2-G0 (19/21) / cdk-G0,
  lshop.c cdk-G0 -O1, card_opt.c, ovl_7f565800.c. Apply only those to ledger/modules.jsonl, then regenerate the census
  (the gate cache hashes census files: do it when no lane is landing). No pinned row reaches 0 by the split alone.
- Kit: genuine cdk source now at toolchain/gcc-src/2.7.2-cdk/ (in the kit tool table, 26b7ac0e7). Wishes: score/dump
  slus module rows at a trial recipe; `.loop` verdict summary in why.py; r83_fable_nosr/tmp/{loopcensus,cc,class_census}.py
  are harvest candidates for tools/lanes.

# Handover (2026-09-30 13:40, round 83 / c8 continuation: FOUR LANES BUILT, STOPPED BY THE SPEND LIMIT) - start here

All four Agent lanes died within minutes on the account's monthly spend limit (HTTP 429; weekly limit resets Oct 4 23:00 UTC).
Nothing staged, nothing landed; the lane dirs are built and re-launchable as they are (Agent prompt = "read
work/native_lane/<lane>/AGENT_PROMPT.txt and follow it"; model in brackets). Rows reserved in _landq/reserved_c8.txt.
- r83_fable_nosr [fable]: what -fno-strength-reduce stands in for (loop.c condition + natural loop shape); 4 slus rows
  (w_800500B4, w_800599B0, w_8005914C, w_80049F68) + CLASS.tsv over the 71 rows carrying the flag (nosr_rows.tsv).
- r83_opus_b1 [opus]: 819B3414 natural route (12 pins / total 4, from r82_opus_bg1/cand/g2_novol.c).
- r83_opus_b2 [opus]: 818D4E68 last pin (a2 preference), 800C4A80 (0 pins, total 7), 8046C280 recipe hypothesis
  (prove on the module with modcell.py before staging at an extra flag).
- r83_sonnet_modsplit [sonnet]: modsplit.py - split mixed-bag census modules (town/main.c, main/c_server.c) into TUs.
Not picked: the optional maspsx_d3 patch (0 rows; owner's call). Housekeeping: a duplicate land_queue2.sh (pid 1705093,
08:28) was killed - runner.pid 3007254 is the only runner. Peer codex lanes a41-a43 run under autoqueue (codex quota is separate).

# Handover (2026-09-30 midday, round 82 / session c8: same process, second batch) - start here

**Update 09-30 afternoon (c8):** decision 3 resolved - the maspsx genuine-ASPSX extern model was already in production
since 819de4599 (09-25); the ~130 slus -G16/-G0/stock registrations were declaration-size workarounds fitted before it.
Landed: 16 + 69 slus rows at plain 2.7.2-cdk with retail-extent declarations (4556d0f6b, 2b5c4b65a; tools in
work/native_lane/r82_opus_dec3/tmp: extents.py, gate_set.py = one isolated SLUS link gate for a set), slus crutch lanes
sc1/sc2 (f3eaacabd, 9b00e0c72, 59d701e78: 25 pins). Owner 09-30: per-TU declaration views of one symbol are legitimate.
New rule: a static inline helper with field arguments reproduces integrate.c's parameter copies (w_800597A8 5->0).
Optional, owner's call: r82_opus_dec3/patch/maspsx_d3.patch (-G from cc1 for TU-defined commons; 0 of 6,767 rows change).
Open slus: the -fno-strength-reduce family (w_800500B4, w_800599B0, w_8005914C: loop.c DEST_ADDR givs), w_80047054
(sched1 loop-note barrier), w_80052A90 (a1/a0 set at block start), w_80048B8C (combine_regs ties). **1,565 pins / 503 rows.**

**State:** 1,888 (c8 pickup, 05:10) -> 1,744 (end of round 81) -> ~1,630 now, with the other session's work.
Process as round 81: gap analysis (work/native_lane/r82_opus_gaps/REPORT.md) -> two Fable lanes -> Opus lanes -> land.
- **Flag-crutch lanes fc9-fc12** (never-served proven crutch rows, target = module census recipe): 10 of 24 rows to
  0 pins (fc12's 3 at FSF 2.6.3 - owner approved moves to an OLDER census cell on strong module proof).
- **Big rows at the census recipe:** 819B3414 33->32 (first exact at cdk: explicit $8 locals bar reload's spill reg),
  818D4E68 33->1 (switch from retail's table words, typed symbols, parameters direct; 1 pin left = a2 preference tie),
  807B0B3C / 800C4A80 open (r82_opus_bg2: real for(;;) loop, reload recomputes hoisted constants; 94 / 7 off).
- **r82_fable_resid** (second assumption under the cell?): YES on 3 rows - cell-carried pins, a flag masking a
  source shape, and **cdk's front end marks every sibling field of a struct with a volatile member volatile** - follow-ups
  fr1/fr2 landed 80F90E88 13->2, 8081822C 8->0, 800BC8AC 10->0. NO on 8187A9A8, 81876014, 8009F018: ordinary source
  shape - stop cell/flag work there (RESIDUE.md has the allocation inequalities per row).
- **r82_fable_slus**: the SLUS game code is ONE 2.7.2-cdk -G8 image 0x80033AA8-0x8005CA70 + ONE stock-2.7.2 sound TU
  0x8005CA90-0x8005FA34; the 29 ledger slus "modules" are call-graph clusters, not TUs. ~130 slus rows sit at
  stock / cdk -G0 / cdk -G16/-G32 only to dodge maspsx's small-extern $gp model. **Owner 09-30: do NOT land -G16
  dodges (4 held in work/native_lane/r82_slus_land); decision 3 (maspsx genuine-ASPSX extern model) SIGNED OFF to
  start** - r82_opus_dec3 is scoping it (patch copy, blast radius, true-size declaration recovery, landing plan).
  After it: 25 proven slus crutch rows / 51 pins (r82_fable_slus/out/pinned_table.md) become workable at cdk -G8.
- **Byte-neutral switches:** bn2 9 rows (d06564789); 81912154 free now for the next batch.
**Kit this round:** tools/lanes/modcell.py (is CFG this module's build?), cc1caps.py (per-cell pass table +
docs/evidence/cc1_capabilities_r82.md), from the other session: score_at diff+totals, why.py --vs-cfg, stage-cell
--equal-pins, diff.py/lab.py --no-jtbl (jump-table candidates diffable), lreg_explain.py (local-alloc replay),
erase_census --full-diff.
**Landing (c8):** work/native_lane/_landq/c8_move.sh TAG LANE "MSG" (tools/fidelity/land_recipe_move.py: overlay +
slus, splitting targets, verifies first, restores on failure) or c8_chain2.sh "lane|msg" (coh.sh/land_coherence:
overlay rows incl. non-splitting targets like 2.6.3). Both under c8_land.lock. coh.sh now refuses on a Traceback
(land_coherence crashed on slus rows at 07:09 and still committed - three lc4 rows were re-landed in 397226d32).
Never put a literal `land_coherence.sh` in a waiter's own command line (pgrep self-match).
**Open follow-ups:** 818D4E68's last pin (a2 preference); 819B3414 natural route 12 pins / total 4; 800BFE94 at
census after astra a30; 80041044 rowbase; town/main.c + c_server.c census groupings are mixed bags (8032EEE4,
8001A2B0); 8046C280 recipe hypothesis cdk-G0 -fno-expensive-optimizations; test_land_recipe_move.py fixture drift.

# Handover (2026-09-30 morning, round 81 / session c8: CELLS AND FLAG CRUTCHES) - start here

**Lever of the round: many pins were fitted together with the WRONG compiler cell or a per-row crutch flag.**
Gap analysis (work/native_lane/r81_opus_gaps/REPORT.md, ranked levers) -> two Fable lanes:
- r81_fable_late (TAXONOMY.md): on most 2.8.x rows the erased text is IDENTICAL at the late cell and at cdk; the cell
  dependence is carried by one KEEP/USE pin on an integer-page local (class P). cellcmp census over 138 non-cdk
  pinned rows: P 69 + P-near 4, D 65 (work/native_lane/r81_sonnet_cellcmp/{cellcmp.py,census.jsonl,REPORT.md}).
- r81_fable_eqv: "retail keeps what cse folds" was a cell/flag problem: 800AC3B0's residue is 2.8.0's
  reload_cse_simplify_operands, absent from the cdk cc1; 813231FC's -fno-expensive-optimizations broke 7 of its
  module's 28 pin-free rows. flag_crutch census (work/native_lane/r81_sonnet_flagcrutch/): 118 rows / 511 pins with the
  crutch proven STRICTLY (a pin-free neighbour exact at the census recipe breaks under the row's cfg).
**Flag-crutch lanes (Opus, brief work/native_lane/r81_q_fc.md, target = module census recipe, stage-cell):** fc1-fc8
solved ~30 of 47 rows to 0 pins (~60 pins); cell lanes lc1-lc4 ~20 pins; 19 byte-neutral recipe switches (1633422f0).
1,888 -> 1,744 pins (09:00, with the other session's work; every c8 lane landed through fc8 91a0b71b8). Rules: tools/learnings/pin_removal_possibilities.md "Round 81".
**Remaining:** proven-crutch rows not yet worked at the census recipe are few and far (list: flag_crutch census minus
reserved_c8.txt); big crutch rows (819B3414 33, 807B0B3C 23, 800C4A80 17, 800BC8AC 12) should get astra/Opus at the
census recipe - earlier lanes worked them at the crutch cfg. Class-P rows not crutch-flagged: cellcmp census (carriers).
**Open items from these lanes:** ovmovie/func_80041044 solved 4->0 in C but its two `j` words need a rowbase region
(foff 0x1044..0x10E0, delta 0x80176800, true name func_80177844; tail-slot true-base recipe) - candidate
work/native_lane/r81_opus_lc4/cand/41044/v1.c. main/func_8001A2B0: the 0x80401xxx block is census-grouped with
c_server.c but cannot match at that cell - needs its own module census. slus/w_80048B8C held at 2.7.2 (pin-free text
5 at 2.7.2 vs 23 at cdk). 80CC2494 -> 2.8.1 declined (owner). 80DE48EC: an unused 16-byte local would size retail's
frame - held (owner discussion: needs positive evidence, e.g. a sibling/JP body with that local). 81811F54 is written
with an integer table on purpose (symbol form 5 off at cdk) - do not symaddr it back. 8009F654 now returns s32*
(src/town/func_800BB6A8.c still declares it void).
**Landing:** c8 cell moves land with `bash work/native_lane/_landq/c8_chain2.sh "<lane>|<msg>" ...` (flock; waits for
sweeps, the queue runner and a clean src; pauses/restarts the runner via coh.sh). Byte-neutral switches: copy of
tools/lanes/land_recipe_switch.sh in work/native_lane/r81_bn_switch/ (stage-cell refuses equal-pin text).
**Two sessions:** the other session (queue runner owner) runs generators t131-t135, alloc_need.py, kit gaps, astra.
Reserve rows in work/native_lane/_landq/reserved_c8.txt; never let a waiter's command line contain `coh.sh r8`
(sweep_land waits on that pattern - deadlocked once).

# Handover (2026-09-29 late night, round 80: Sol 6.1, scaffolding lanes, JUMP-TABLE FIDELITY HOLE) - start here

**DONE 09-30 00:53 (c262202fa) - switch jump tables are now compared.** The overlay window gate
(overlay_local_gate.py local_table_mismatches, strict) and match.py build_text (local_table_diffs -> `CFAIL jtbl`)
compare every placed jump table with the retail container; tests in tools/tests/test_local_table_mismatches.py.
72 rows repaired (34 relabelled, incl. mid-body case labels that replaced barrier pins; 28 lane-made structural
switches restored to their pre-switch text; 9 previously reverted conversions landed; 80813E14's keep-alive moved to
.data): pins -4, gotos +40, every window (--all) MATCH. Before this, 63 rows had tables routing cases to the wrong
bodies with byte-identical text. The lanes' scorer root picks up the match.py compare at the next
`bash tools/build/mk_ovl_root.sh` (run it in a lane gap). Follow-ups: the 28 restored rows can likely get their
switch back with correct case labels (mid-body `case` technique, bin/mid.sh in work/native_lane/r80_opus_rodatawin);
four un-nested rows have shadowed locals worth renaming (8180C3C0, 81958878, 8080E994).

**Approach change 09-30 ~01:30 (owner asked "time to change approach?"):** fresh-row Opus lanes fell to 0-3 pins
(rows served 5-8 times since r66); mechanism lanes paid (early constant: 13 pins over two lanes, as a RULE). So:
census-first. `python3 tools/lanes/erase_census.py OUT.jsonl --procs 8 --diff 6 --fp` (10 s, whole tree) then cluster
by `fp.cls`/`fp.shape`: 09-30 near band (d0<=6) 586 sites / 291 rows = MOVED 236 (scheduling order), CHANGED 220
(page/symbol, narrow loads), RECOLOURED 85 (allocation ties). One Opus CLUSTER lane per tight shape (trace the deciding
pass on one row, derive the rule, apply to six, list the rest): r80_opus_cl_li / cl_lui / cl_move running; their
cluster_rest.txt holds the remaining members for apply lanes. Sol 6.1 stays on the one-pin pool (218 rows).

**State (09-30 ~12:30, this session = generators/kit/astra; the peer session azure-clean-c8 = cells, flag crutches, slus
recipes):** Pin sites now: 1,565 in 503 rows. Codex lanes are hands-off now: `nohup bash work/native_lane/_landq/autoqueue.sh <lane> &` waits for a
codex lane, checks every staged row (exact, base current, pins fewer, no added scaffolding) and appends it to the landing
queue (failures -> _landq/autoqueue.held). Row pools: build through `python3 work/native_lane/_landq/reserved_filter.py`
(skips the peer's reserved_c8.txt in any format + exclude_extra.txt). slus candidates verify.py cannot judge (symbol vs
integer) land via _landq/slus_gate_try.sh (SLUS SHA-1 only). Kit since 06:00: alloc_need.py + lreg_explain.py (allocation
inverses, global and local), row_census.py, why.py --vs-cfg, stage-cell --equal-pins, erase_census --full-diff, --no-jtbl,
slus rows score in the kit; generators t131-t135; t129 knows libc/PsyQ arities. Astra on 5-12-pin rows pays ~5 pins/lane
(a18-a40); the pool list is rebuilt each wave (tmp/astra_pool*.txt).

**Landing queue moved (09-30 05:50, session restart):** the batch runner and helper scripts now live in
work/native_lane/_landq/ (land_queue2.sh reads land_queue.txt there - append `tag|lane|KIND|WHAT`; runner.pid, land_queue.done,
coh.sh for cells.jsonl moves, sweep_land.sh for gated generator sweeps, mkgd.sh for goto lanes, handover_todo.txt).
**State (09-30 05:10):** 1,888 pins in 578 rows (2,068 when this session's evening block began, 2,493 at pickup);
gotos incl. &&label 4,042 (the jump-table repair restored 91), volatile 529, one-trip blocks 324.
Tonight's generators: t126_ppcollapse (dead #if splits, 41 rows), t127_gotonext (16), t128_nonvoid (dbr rule, 2+2 pins),
t129_defarity (calls trimmed to the callee's DEFINED arity - 280 rows of m2c fake arguments gone, byte-exact). Goto
lanes: the unserved dense pool is nearly exhausted (gd35 picked only 2 rows); the kept gotos are measured loop.c /
reorg decisions. Sol 6.1 paused at 34/89 one-pin rows (last two lanes 3/16). Cluster lanes pay 1-4 pins each but leave
RULES (learnings file end); open classes logged in the scratchpad handover_todo list and below.
**Sol 6.1 (gpt-6.1-sol, `launch_lane.sh <lane> sol61`, codex CLI >= 0.159):** ~60% on 1-pin rows (15/25), 0 on 2-pin and
big rows; tidy its texts (identical-arm NON_MATCHING splits, orphaned pin comments) before landing.
**Sonnet scaffolding lanes (vol1-4)** clear volatile/one-trip blocks on pin-free rows (vol2 7/10); patterns in
tools/learnings/pin_removal_possibilities.md "Scaffolding" section. **t126_ppcollapse** collapses dead #if splits.
**Owner rulings 09-29 evening:** copied blocks OK; case ranges OK when meaningful (w_80058E6C MIDI text events); common
byte-neutral flag trades for gotos OK; w_8003E4FC (Control_CD: one two-command group somewhere in 0x0F-0x14, bytes cannot
say which) - recommended a documented guess (GetlocL/GetlocP) unless another build pins it. The skip-copy goto family
(24 rows) is original control flow (reorg trace) - leave it. Cell moves land through scratchpad coh.sh (land_coherence.sh
with the queue runner paused).

**Open items (09-30, from the session list):**
- **TOP (09-29 late): switch jump tables are NOT compared by the overlay window gate** (tools/gate/overlay_local_gate.py compares .text only; match.py build_text too). r80_opus_rodatawin measured 63 landed rows (41 from r80 switch lanes, 22 since import) whose jump tables route cases to the wrong bodies with byte-identical text (confirmed by hand: dungeon/func_81862ED8 cases 0-5/6/7-14 vs retail 0-6/7/8-14; main/func_8001A6D0). Its patch (work/native_lane/r80_opus_rodatawin/patch/rodata_windows.patch: true-name fallback + local_table_mismatches) turns 86 windows red, so it lands only WITH the repair (relabel permutation rows, restore structural ones). Repair being built by the same lane (REPORT_REPAIR.md). HOLD all switch-producing lane work (computed goto -> switch, ladders -> jump-table switch) until the kit compares tables too.
- town/func_8087FEF0: 1 pin via literal 0/0xC9 + --aspsx-version=2.40 as-flag (t45 island; neighbours carry it; t45 skipped the row because of its NON_MATCHING arm) - candidate work/native_lane/r80_opus_q5/c/fe/v1.c, score through the real scorer
- RESOLVED (r80_opus_lafill): the o2 "maspsx delay-slot gap" claim is FALSE - genuine ASPSX 2.56-2.86 leaves the nop; retail's filled slot is cc1 splitting a NON-small-data symbol (807B0B3C declares D_80083160 as a 4-byte extern = small data at -G8). Row lead: `extern u8 *D_80083160[]` (cand/v_arr.c) + reload pressure for the $9 rebuild.
- HELD (owner call): slus/w_8003E4FC 29 -> 0 gotos needs a case range the retail tree proves exists but not WHICH values (any consecutive pair in 15..20 scores exact) - candidate work/native_lane/r80_sonnet_gb1/hold/slus/w_8003E4FC.c. Rejected as steering under the current brief. Also: lab.py/diff.py/why.py cannot score slus rows (PartitionError: plural compilation) - kit gap.
- after landing gb6/gb7: run tools/lanes/clone_transfer.py --metric gotos from func_809815A8 over its clone siblings (xxx5A8 family; gb6 did 809755A8/8097B5A8)
- HARVEST: work/native_lane/r80_sonnet_gp1/tmp/rw.py - a generic skip/else goto rewriter (34 gotos exact in one pass on 819835AC): candidate for a tools/xform generator (t124). Also: 8133336C carries one 8-line duplicated tail (over the ~6-line ceiling; accepted for 76 gotos gone) - owner may review.
- after o8 lands: func_800654B0 prototype - o8 declares 10 plain s16* args in func_800B6D74.c; other TUs may declare struct args (GeomTailArgs) - align in a type-consolidation pass
- CLEANUP: indentation of goto-lane rewrites is untidy in places (gp9 81912154/818FF710, gb4 80FB402C/80BC1BA8, crammed files 800AFA68/800BF6A0/800CA184/812A524C): a whitespace-only reformat pass (verify byte-exact per row) is worth a Sonnet lane
- DONE: r2 helpers folded into tools/lanes/lanekit/regcmp.py (5251bd69b; --subsets for pin-removal subsets)
- slus/w_80058E6C (r80_sonnet_gd19, held in the lane's held/): 14 -> 0 gotos exact, but only with a GNU case range `case 0 ... 0xF:` restating retail's bltz/slt<16 skip compares (without it gcc emits a 43-entry jump table) plus six func_800589B8(track) calls copied into case 0x54. Same class as w_8003E4FC (steering case values): owner's call.
- dungeon/func_80289FB8 (r80_sonnet_gd23): its 1 backward goto loop becomes `while (1) {... break;}` exact only at 2.7.2-cdk-G0 -fno-strength-reduce (pinned text byte-neutral there); a goto-for-flag trade, not applied (lane experiments/).
- Skip-copy goto family (24 rows): RESOLVED as original control flow by r80_opus_skipcopy (reorg trace), recorded in goto_lane_brief.md.
- Clone family dungeon 80CEC1A0 80CF21A0 80CFE1A0 80D041A0 80D0A1A0 80D101A0 (r80_sonnet_gd25, held in the lane's held/): `default: goto update_state` over a shared 5-line apply-table block after the switch is exact goto-free only by copying the 5-line block (with a call) into cases 13/14/15 (3 copies). Held: 3x5 lines exceeds the copy limit and reads worse than the one goto. Owner's call (6 gotos).
- r80_sonnet_gb31 computed goto -> switch, both reverted at landing (discarded-.rodata windows): slus/w_80057D20 27->0 needs a SLUS .rodata owner record for jtbl_80032F04 (docs/evidence/slus_rodata_migration.md procedure); dungeon/func_807AE960 10->0 needs its window to keep .rodata (table D_800F6000). Candidates in work/native_lane/r80_sonnet_gb31/out/.
- Residue class lbu+sll 24+sra 24 vs lb (combine folds the zero-extend/shift pair into lb without volatile): dungeon/func_800D1A48 12 volatile byte reads (r80_sonnet_vol1, dist 4 without them), dungeon/func_8187C45C tick byte (r80_opus_r3). Next: what non-volatile source stops combine (use_crosses_set_p / a store between load and use).
- Generator candidate (r80_sonnet_gd30, w_80046884): m2c pointer-walk goto loop (p--; q--; r--; i--; if (i>=0) goto L, pointers from &arr[N]) -> for (i = N; i >= 0; i--) with arr[i], pointer locals deleted; pointer-walk structured spellings all fail (loop.c). Sweep candidate. Also M2C_FIELD: 245 uses in 227 rows want real struct fields (type-consolidation work).
- dungeon/func_800BE8D0 (r80_opus_earlyconst3): landed 3->0 with a goto loop; the new text is also exact at plain 2.7.2-cdk-G0 (drop -fno-strength-reduce) while the old pinned text is not - a flag-reduction coherence trade for the module census pass. Early-constant open: 8187A9A8 (pins 9/10/12/13/14 jointly; D_80083160 lo_sum fold), 819ADDB8 (B-inverse: retail's parameter copies were multi-set), 8181214C (same).
- Open class (r80_opus_ap2): retail keeps a register copy that gcc cse/reload_cse would fold (800AC3B0 b_held/style_held - reload_cse turns sll 2 into sll $20; 813231FC first_result): the pins imitate a broken equivalence, not an order. Also: 81876014 is -fno-schedule-insns (sched2 only; retail double-reloads unk_60 after storing 0); 8132A210 pins 4+5 fall together at dist 2 (boosted volatile stack-param load).
- dungeon/func_819B3414 (34 pins): cell-trade lead at 2.7.2-cdk-G0 = 7 pins, total 4 (work/native_lane/r80_opus_big1/c/k2.c); with the volatile ASM_KEEP(first_screen_xy) barrier gone and a real do/while quad loop, only the xy-address register roles remain (P2 5 pins total 9, M3 total 8); next check: .lreg quantity order (column offset vs the v1 chain). At stock 2.7.2-G0 the five $8 locals are an all-or-nothing reload group (retail's $8 = cdk spill reloads) - this row belongs at cdk.


# Handover (2026-09-29 evening, round 80 continued: Opus harvest lanes, goto-lane scale-out, batch lander) - start here

**State:** ~2,200 pins in ~650 rows (from 2,493 / 696 at this session's pickup, 2,762 / 735 at round start); plain gotos
down by several thousand (Sonnet dense/big/pinned goto lanes gd1-18, gb1-11, gp1-15 + t124 tree pass). Landing is BATCHED:
append `tag|lane|KIND|WHAT` to the scratchpad land_queue.txt; land_queue2.sh lands every queued lane in ONE gated run
through tools/lanes/switch_land_lanes.sh (generic now: several lanes, KIND/WHAT commit text, SLUS NO MATCH attribution).
If the session ended mid-queue: re-run `bash tools/lanes/switch_land_lanes.sh <tag> <lane>...` for lanes with out/ and no
commit (check `git log --oneline | grep <lane>`).

**What paid, per lane (Claude Agent lanes):** Opus with the round-80 harvest in the prompt (tools/lanes/brief_paragraphs/
r80_harvest.md + tools/learnings/pin_removal_possibilities.md round-80 sections): fresh 4+-pin rows 5-109 pins/lane (clone
families best: xxx084 109 pins), big re-served rows 0-28 (o1 29->1 with a -fno-strength-reduce byte-neutral recipe switch);
1-3-pin plateau rows 3-6/lane (poor). Sonnet: dense goto rows ~30/lane, big pin-free goto rows 25-57/lane, PINNED goto rows
at equal pins 30-217/lane - best readability lever; Sonnet on 1-pin rows 2 pins/lane (poor). Codex: astra 2-3 pins per
2-row big-row lane (extra capacity, codex quota separate); sol 0-2 on 1-pin rows (capped); Gemini 0-1.

**Rulings applied this block (coordinator; owner may review):** rejected label-into-block / label-moved-deeper candidates
(gb11 w_80048734, gp7 808110CC), a contrived ternary spelling (gp15 813360FC), a case range the retail tree proves but does
not identify (gb1 w_8003E4FC, held); accepted one 8-line duplicated tail (gp1 8133336C, 76 gotos), write-back stores
(p3, post-reload CSE evidence), goto-loop spelling trades for pins (o3), recipe trades with rule 2 (o1, c7).

**Open items:**
- town/func_8087FEF0: 1 pin via literal 0/0xC9 + --aspsx-version=2.40 as-flag (t45 island; neighbours carry it; t45 skipped the row because of its NON_MATCHING arm) - candidate work/native_lane/r80_opus_q5/c/fe/v1.c, score through the real scorer
- RESOLVED (r80_opus_lafill): the o2 "maspsx delay-slot gap" claim is FALSE - genuine ASPSX 2.56-2.86 leaves the nop; retail's filled slot is cc1 splitting a NON-small-data symbol (807B0B3C declares D_80083160 as a 4-byte extern = small data at -G8). Row lead: `extern u8 *D_80083160[]` (cand/v_arr.c) + reload pressure for the $9 rebuild.
- HELD (owner call): slus/w_8003E4FC 29 -> 0 gotos needs a case range the retail tree proves exists but not WHICH values (any consecutive pair in 15..20 scores exact) - candidate work/native_lane/r80_sonnet_gb1/hold/slus/w_8003E4FC.c. Rejected as steering under the current brief. Also: lab.py/diff.py/why.py cannot score slus rows (PartitionError: plural compilation) - kit gap.
- clone replay (pins + gotos over all r80 lanes) found 0 more siblings - families were covered by the lanes.
- DONE: t124_skipgoto generator (79be74666) from gp1's rw.py; tree pass staged 239 rows (r80_t124_sweep) - rerun `sweep.py t124_skipgoto` after the queued lanes land (rows held in r80_t124_sweep/held/ were owned by lanes). Also: 8133336C carries one 8-line duplicated tail (over the ~6-line ceiling; accepted for 76 gotos gone) - owner may review.
- after o8 lands: func_800654B0 prototype - o8 declares 10 plain s16* args in func_800B6D74.c; other TUs may declare struct args (GeomTailArgs) - align in a type-consolidation pass
- CLEANUP: indentation of goto-lane rewrites is untidy in places (gp9 81912154/818FF710, gb4 80FB402C/80BC1BA8, crammed files 800AFA68/800BF6A0/800CA184/812A524C): a whitespace-only reformat pass (verify byte-exact per row) is worth a Sonnet lane

# Handover (2026-09-29 later, round 80 continued: switch phase 2, SLUS rodata ownership, Opus family wins) - start here

**Landing queue at writing (sequential, each gated; check `git log` and each lane's switch_land.out):** switch lanes
swp10-13 -> SLUS rodata migration (scratchpad script land_slusrodata.sh; log work/native_lane/r80_opus_slusrodata/
landing_real.log) -> r80_opus_p1 -> p2 -> r80_cell_c7 recipe move (land_recipe_move.py r80c7) -> r80_onetrip_noexp
(41 rows, 45 one-trip blocks) -> r80_opus_p3 (17+ rows to 0 pins) -> p4. Anything staged but not in git log after
that queue: re-run `KIND=pin bash tools/lanes/switch_land_lanes.sh <tag> <lane>` (it is generic now).

**Owner review requested:**
1. **SLUS jump-table ownership (build-infrastructure change, r80_opus_slusrodata):** 7 slus switch rows own their
   compiler .rodata jump tables at the retail address (config/slus_modules.json .rodata records carving
   assets/800.bin, tools/build/slus_rodata_trim.py drops the assembler's section-end padding, prove_slus_ownership
   .rodata branch). Evidence docs/evidence/slus_rodata_migration.md (+ receipts dir). Lighter than a partition
   activation (no function moves, no placement grant): ownership receipt + per-row/joint SHA-1 gates + negatives
   (case-17 table refused, no-trim NO MATCH). 8 more tables can follow (w_80041344, w_80041588, w_80052144,
   w_80057D20, w_800595C0, w_8005EDA0 x2; w_8003E758 blocked by the cd_command_state module rule). The lane's
   tools_draft/ (rodata_migrate.py, rodata_gate.py, rodata_receipt.py) should move into tools/ when that wave runs.
2. **Write-back stores (r80_opus_p3):** `r = p->r; ...; p->r = r;` on the xxx084 / TILE_1 clone family. Retail's
   three lbu loads have no consumer; the stores are in .lreg and deleted by post-reload CSE in .greg (checked per
   row, cand/wbcheck.py). Treated as recovered source (setRGB0-style), not a fake dependency - flag if you disagree.
3. **Recipe trade** town/func_8032E720 -> 2.7.2-cdk-G0 -fno-expensive-optimizations -fno-schedule-insns
   -fno-schedule-insns2 (calls.c:1659 constant-argument pre-copy; ledger/recipe_trades.jsonl).
4. Small: 80ACB000's 4-pin family text adds a red $3 pin its base lacks (not staged); 81850800 KEEP->KEEP_NV swap
   exact at 4 pins (not staged; subset gate).

**Measured this block:** switch pool nearly spent (sw20-26, swp2-13, ~90 rows landed as real switches; out of reach:
text-prefix tables D_800240xx ~12 rows, deep windows that discard .rodata ~10 rows, 2.91.66 800BAE88). 2.8.x rows need
NO cell change (old brief wrong). One-trip blocks: `-fno-expensive-optimizations` hypothesis does NOT generalise (1-2
of 327 rows); unwrap-ALL is exact on 41 rows -> t20 now tries unwrap-all first (dd5963b4) - re-sweep t20 next.
Opus pin lanes with the round-80 harvest in the prompt paid far above earlier rounds (p1 30, p3 ~80, c7 3, p2 2, p4 3).
New learnings sections (tools/learnings/pin_removal_possibilities.md): three-pseudo copy shape, clone transplant,
abs() templates (same/different register), symbol argument on a reassigned local, calls.c constant-arg pre-copy,
sched1 live recount, write-backs deleted by post-reload CSE.

**Running at writing:** r80_opus_p5, p6 (fresh rows with the harvest prompt), p3 follow-up 2 (d0360 body on
800BFE94 15, 807B0B3C 23, 80F90E88 17, 81910A9C, 81875828, 818B0E10, 818F30EC, town/800A5398).

# Handover (2026-09-29, round 80: Sonnet 5.5, goto/switch readability, cell moves, phase 11) - start here

**State.** 2,762 / 735 at pickup (f5c32120) -> **2,493 / 696** committed. Plain gotos ~8,157 -> 6,780; computed-goto
files 315 -> 190. Record: [r80 wave record](evidence/r80_wave_report.md). Everything landed is committed; nothing staged
is pending except lanes still running at hand-over (check `ls work/native_lane/r80_*` for out/ without a commit).

**What paid (in order):** (1) fidelity step-4 CELL MOVES - rows registered at a non-splitting cell whose retail shows
split addresses (docs/evidence/fidelity_step2_split_fingerprint.md) solved AT the retail-proven cell by Opus lanes
r80_cell_c* (brief paragraph cell_move.md, staging out/ + cells.jsonl, lander tools/fidelity/land_recipe_move.py):
~120 pins on ~35 rows, SLUS included (slus_iso). (2) Opus fresh/family lanes (byte sign-extension family 39 pins in 2
lanes). (3) Sonnet 5.5 goto lanes (build_goto_lane.py --densest; ~100 gotos/lane) + CPU generators t122/t123 + clone
replay (clone_transfer --metric gotos). (4) Sonnet 5.5 SWITCH lanes: computed-goto dispatch -> real switch
(build_switch_lanes.py --pool; lanes named r80_*; land ONLY with tools/lanes/switch_land_lanes.sh - some deep/truebase
window builds discard the compiler's .rodata jump table, the wrapper reverts exactly those rows and re-gates).

**Routing (owner 09-29):** Sonnet 5.5 for readability + bounded tooling (worktree); Opus for pins; Fable only as a
last resort (r80_fable_n1 proved two near-misses unreachable by statement order - see its REPORT). Harvest every
escalation lane (tools it wrote, method, ask for a retrospective) - memory feedback-harvest-lane-logs-20260929.

**New tools this round:** kit gate/lander accept equal-pin fewer-goto (incl. computed) candidates; lanekit --base,
--cfg on diff/why/erase, diff --scorer [--norm-regs|--classify], lab stage-cell, prio.py, why --trace/--insn/--deps,
checks.py (four proof checks); brief rule TRACE BEFORE YOU SWEEP (duck_pack_brief_v2.md).

**Next:** remaining switch pool (~40 pin-free 2.6.3/2.7.x rows; 2.8.x rows need `-mno-split-addresses`, a cell
change); pinned computed-goto rows via Opus; goto pool (~400 rows, --densest); switch rows reverted for discarded
.rodata (list in the switch lane commits) could keep their pin removals without the switch (81978140/81978428 2 pins
each); open near-misses 819B3414 / 800AFA68 / 800C4A80 (0 pins at total 7 at cdk). The r79 lander
(land_finished2.sh, pid 536862) still lands r7x lanes every 15 min; commit sweeps before landings.

# Handover (2026-09-29, round 79: short wave, paused for a Sonnet 5.5 restart) - start here

**Why paused.** Owner (09-28 ~23:40Z): Sonnet 5.5 may be available in fresh Claude instances; if a restart is needed,
let lanes wrap up, hand over, pause. The Agent-tool `sonnet` alias in this session resolved to **claude-sonnet-5**
(lane r79_sonnet_s1 codex.log), so a restart is needed; the Sonnet 5 lane was stopped (STOPPED.txt; not a 5.5 probe).

**State.** Record: [r79 wave record](evidence/r79_wave_report.md). 2,787 / 735 at pickup (commit 9d2eb009) -> **2,762 / 735**. Opus
r79_opus_w1: dungeon/func_81008664 22 -> 10 (r70's volatile param + stack struct + $8 carrier + attempts +/-1 pairs were
reload / loop hoists / reorg add-undo; one keep relocated, still counted). Astra b1-b3: 1-3 pins per row on the six
top-of-pool r70-plateaued rows (codex 21% -> 24%, ~2.7 pins per 1%, half round 78's rate) -> route such rows to Opus
next. Gemini 0/5 (paused on this pool). Type consolidation phase 10 fully landed (9034b1ce; 6,767/6,767 verify-exact).
Fixed a t2_pins infinite loop on macro-expansion pin sites that stalled the b3 landing (6c78cac0). The lander
land_finished2.sh (pid 536862) is still running and idle: it lands any finished r6x/r7x lane every 15 min, so name new
lanes r79_* (r80_* needs a lander restart with a wider glob). Codex weekly 24% used, resets 2026-10-03 23:05Z.

**Ready to launch on pickup (built, kitted, served-guard checked at build time; rebuild if the rows changed):**
- `r79_astra_b4` (802835B8 24, 8008EE88 22), `r79_astra_b5` (800AFA68 20, 800C4A80 19), `r79_astra_b6` (80F36D0C 19,
  81978428 19): `bash tools/lanes/launch_lane.sh r79_astra_bN astra` (caps default on: 750k / 90 min). Astra 2-row
  big-row continuations paid in 11 of 12 round-78 lanes (2-16 pins each, ~250-500k tokens).
- `r79_sonnet_s1`: the Sonnet 5.5 probe pack (5 never-served 3-7 rows; baseline Opus fresh 3-7 = 2.8 pins/lane).
  In the fresh instance: remove STOPPED.txt, codex.log, lab_log.jsonl, experiments/ tmp/ out/ contents, then launch
  with the agent prompt in AGENT_PROMPT.txt (Agent tool, model sonnet); STEP 0 must show a Sonnet 5.5 model ID -
  if not, record the substitution and stop. The served guard may count this lane as a sonnet serve: use --repack /
  a new lane name if a rebuild refuses.
- `r79_types_p11`: phase-11 type consolidation BRIEF.md (EntityRec type propagation 55 rows, town root D_80016000
  58 rows, D_80082E60 cross-binary). Launch as an Opus Agent lane after phase 10's full apply is committed:
  "read BRIEF.md in work/native_lane/r79_types_p11 and follow it" (phase-10 prompt shape, AGENT_PROMPT in r78_types_p10).

**Decisions taken this round (owner delegated):** F0 discarded clamps rejected under charter rule 3 (open items).

# Handover (2026-09-28, round 78: restart-plan pickup) - start here

**State.** 3,098 / 765 at pickup -> **2,982 / 752** at this note (plus staged partials the lander
`land_finished2.sh`, pid 536862, lands every 15 min). Records: [decision](evidence/r78_restart_decision.md),
[wave record](evidence/r78_wave1_report.md), rows per lane `evidence/r78_wave1_rows.json`. Codex weekly meter
0% -> ~2% (resets 2026-10-03 23:05Z); Gemini usable; Claude unmetered.

**What paid.** (1) Opus fresh-eyes continuations with evidence packets (`tools/lanes/continuation_notes.py`,
brief paragraph `fresh_eyes`): 11 of 44 rows reduced, 54 pins beyond the prior floor; the interrupted H28 lanes
paid in 5 of 7. (2) **Spill-register family** (`brief_paragraphs/spill_register.md`): ASM_REG on $8/$9/$10/$12
+ keeps imitating reload (spilled pseudos, REG_EQUIV rematerialisation) - use real params/tables/symbols, drop
all bindings together; Opus family lanes ~40-50% of rows. Rules folded into
`tools/learnings/pin_removal_possibilities.md`. (3) Gemini on 1-2 rows and known shapes: 3 of 5 lanes paid.
**Did not pay:** extend arm (resumed codex session) 0/5; Sol 6 on plateaued rows 1 pin in 3 lanes; Luna 6
0 in 3 lanes (paused; gpt-5.6-luna rescue lane r78_luna56_sp4b is the 6->5.6 observation).

**New tooling.** `cutoff_report.py` (cut-off experiment: near-misses at cap/limit/interruption, extend vs
fresh arms), `extend_lane.sh`, `continuation_notes.py`, `land_slus_rebaseline.sh` (SLUS rows exact after link
but not per-object: image SHA-1 gate + per-row rebaseline), lockstep port-arm landing rule, price-scaled default
caps (`config/lane_caps.json`), capped lanes landable (cap stub), agent lanes write reports via Bash heredoc.

**Owner decisions queued.** F0 clone family (11 rows x 6 pins): Astra reproduced retail with discarded colour
clamps (7 exact texts, self-rejected as artificial dead computation; `work/native_lane/r78_astra_f0/diag/
rejected_clamps/`) - land as a visible reconstruction or not? r77_opus_m6 site-for-pin trade (81875B38).

**Routing adopted 2026-09-28 06:00Z (from per-mode yield, wave record):** Opus = continuation packs with
evidence (near-miss conversion ranked by `cutoff_report.py --json`, fresh-eyes on reduced/interrupted rows) and
family packs with exemplars; fresh never-served packs are the fallback (2.8 pins/lane vs 4-6). Astra = family
packs with exemplars (7.5/lane on spill). Sol = bounded census/tooling only; Luna = no pin lanes (0 in 5).
Gemini = 1-2 rows. Meters at 06:00Z: Claude 13%, Codex 10%. Lander now also lands scaffolding-only removals
(volatile etc. with equal pins); screen.py expands la/ulw/usw so lab.py scores those exact candidates itself.
**Readability:** STATUS m2c-names metric fixed (comments excluded): 789 rows, only 191 outside extern
prototypes - naming is nearly done; the real debt is gotos (1,599 rows) and address-named local struct types
(3,140) - needs a type/header design decision before a campaign.

**Type consolidation (owner rulings 2026-09-28, docs/TYPE_CONSOLIDATION.md):** pilot + phases 2-8 landed 6,009 row
migrations onto 15 include/shared/ headers (EntityRec, GameWork with its view sub-structure, ObjectNodeHeader, ...), every row
verify-exact with full window/SLUS gates; tools in tools/consolidate/ (run from a lane copy), per-object specs
in tools/consolidate/objects/. Mostly pin-neutral directly; phase 4 freed 4 SLUS pins (pointer globals m2c had declared as arrays). verify.py
now compiles current SLUS texts against the live include/ (e8874f3b). SLUS C-only data symbols: config/slus_006.14.c_syms.txt (configure.py C_SYMS). Script symbol dump parse fixed
(c54f8361: records are name then value; call number n = entry n). Continue cold from the latest phase design doc's
HOW TO CONTINUE (docs/evidence/type_consolidation_phase8_design.md); phase 9 running. Next objects are listed at the end of the design doc
(D_80083178 fold into GameWork first). Preview page: https://claude.ai/artifact/LA63o6jeL9Xc5hHTXuw6LZ

**Open items:** docs/OPEN_ITEMS.md (tracked list; fix when a safe moment arises, then move to Closed).

**Next.** Remaining spill-family rows (~18 with 7-30 pins; `ASM_REG("$8"..)` census in the wave record);
fresh-eyes on this round's reduced rows; jump2 cross-jump blocker question (c8); set-once/birthing rows from
c11 (known r76 family: zero-init is deleted by flow there).

# Next restart (2026-09-27)

Read [Claude / Codex restart plan](CLAUDE_CODEX_RESTART_PLAN_20260927.md) for the
next review and pin campaign, model routing, retry policy and usage measurement.
The GP transition below completed in production on September 25; its
[final receipt](evidence/gp_partition_only/production_transition/README.md)
supersedes the earlier pending/private checkpoints retained here.

# Previous goal (2026-09-24, completed 2026-09-25)

See [GOAL_TOOLCHAIN_AND_MODULES.md](GOAL_TOOLCHAIN_AND_MODULES.md): SLUS `$gp`
repair, obsolete maspsx pass retirement, one verified module pilot, and explicit
accounting for the three unregistered MAIN routines. The primary agent handles
hard analysis and orchestration; the owner authorizes Sol and Luna delegates for
bounded grunt work. Claude's reset in about three days is a handoff checkpoint.

Latest checkpoint: [AFE cache ownership](evidence/gp_cache_afe.md) separates the
cache halfword from adjacent AFC selector storage. Its existing plain 2.7.2
recipe gives all 32 words through genuine ASPSX, with zero masks and full retail
image equality. Normal Splat registration and real two-byte C storage pass;
4437C's object stays unchanged. Production: **197 dependency records, 29 GP rows,
19 ownership units, 873 physical / 884 logical rows**. The runtime pilot is
recertified; no production assembler default or pass changed.

Current private rehearsal: [14 prepared rows](evidence/gp_ready14.md) coexist in
one retail-exact image. All 735 words match fresh linked/generic/genuine objects
with zero masks and nine correctly owned symbols. Nine of 29 GP rows are ready;
the remaining 20 form the collector-linked component. Production counts and
defaults remain unchanged by this selective rehearsal.

Current architecture checkpoint: [explicit function partitions](SLUS_PARTITIONS.md)
now support optional build generation, logical projection, plural candidate
compilation and full-image gating. Both normal Ninja and isolated verification
require exact emitted-function coverage before link/equality. All 181 private E0
functions, 884 logical rows and 44 genuine-exact words are retained. Six MIPS
candidate scenarios verify routing and restoration, including compile failures
and macro-hidden extra functions. All 99 SLUS tests and the row database pass;
the production image still matches the pinned recipe and retail. The runtime
pilot is recertified. Activation still needs per-owner genuine records and
part-aware ownership/placement certificates; then activate E0 and remove only
its proved-eliminated GP dependency. No production partition plan or assembler
default/pass change is active.

Previous checkpoint: [shared cancellation state at 8099C](evidence/gp_shared_8099c.md)
lands 33D44/33D54 at 2.8.1 after an unchanged-source byte-neutral setter move.
The full retail image and actual four-byte C storage pass. The setter is direct
genuine-exact; the renderer stays exact through the already accepted epilogue
model, separately recorded by explicit verifier opt-in. Production: **198
dependencies, 30 remaining GP rows, 18 ownership units, 873 physical / 884
logical rows**. Renderer pins and its model dependency remain. The runtime pilot
is recertified; no production assembler default or pass changed.

Previous checkpoint: [shared state at 81510](evidence/gp_shared_state_81510.md)
lands 45340/453E0 after a byte-neutral 45340 CDK recipe move. All 573 words are
genuine/retail exact without masks or compatibility passes, and the complete
image matches retail. Production: 199 dependencies, 32 remaining GP rows,
17 ownership units, 874 physical / 884 logical rows. Existing pins remain; the
runtime pilot is recertified. The generic assembler correction remains private.

Previous checkpoint: [split small-data storage](evidence/gp_split_storage.md)
lands 48660 with real `.sdata` and `.sbss` ownership. Production counts are now
201 dependency records and 34 remaining GP rows; 875 physical / 884 logical
rows. Full image, 53 words of genuine proof, 87 focused tests and the pilot's
negative candidate checks pass. The runtime pilot is recertified. Address-taking
owners remain private pending the coordinated assembler change.

Previous checkpoint: [runtime count and shared display slots](evidence/gp_count_and_slots.md)
recover seven C-owned globals for three more GP rows. Full SLUS retail image and
402 words of genuine ASPSX 2.79 proof pass with zero masks. Current totals:
202 dependency records, 35 remaining GP rows, 875 physical C inputs / 884 logical
rows. No assembler default switch or pass deletion; existing pins are unchanged.
The original runtime pilot is recertified, with no placement claims for these
two new ownership units. The numbered checkpoints below retain their historical
counts and intermediate findings.

[Next private ownership proofs](evidence/gp_next_ownership.md) establish two
address-taking owners under the experimental generic correction, including a
53CFC C declaration repair, and stock-assembler exact split `.sdata`/`.sbss`
storage for 48660 (now integrated with per-section carve/proof support);
the global assembler switch still needs the remaining coordinated repairs.

[Further private groups](evidence/gp_ready_ownership.md) prove 8152C's three
consumers and the prepared pin-free 3D92C under the generic correction. The
45340/453E0 group has since landed with stock assembly. A separate
[49F68 RTL-guided repair](evidence/gp_order_bytes.md) now matches all 50 retail
words through genuine ASPSX 2.79. Reading the first byte before assigning the
sentinel fixes its register roles without added pins. Its private full image is
exact with real four-byte storage. The newer [local-data guard](evidence/selfinc_local_guard.md)
proves the same full image with **every pass enabled**, six corrected local-data
micro cases, 12 unchanged controls, 13 unchanged consumer objects/traces and 70
unchanged genuine-exact small-data probes. This removes pass retirement as a
prerequisite for 49F68's correction. The pass still has
[12 measured consumers](evidence/selfinc_consumers.md) to repair before retirement;
no production assembler or dependency change follows yet. The
[81811E30 compiler investigation](evidence/selfinc_81811E30.md) records why later
combine/allocation retain its full pointer and queues address-GIV analysis.

[8099C ownership](evidence/gp_shared_8099c.md) is now integrated and full-image exact
after retaining the runtime source-name prefix required by the current linker.
33D44 is direct genuine-exact; 33D54 retains the accepted compiler epilogue model.
Applying that model to the fresh compiler stream lets genuine ASPSX reproduce
all 541 words. Its residual is retained. Ownership verification supports an
explicit row opt-in with a separate modeled proof; the default and placement
certificate still require direct genuine equality.


[Largest remaining GP component](evidence/gp_component20.md): 20 of the 32
rows share 22 symbol names across seven recipe variants. The recovered assertion
map does not establish SLUS grouping here. Inventory distinguishes lexical source
bodies from registry symbols; next establish per-access addressing and data
extents for a local cluster before choosing any combined ownership.
[AF3 declaration repair](evidence/gp_af3_declarations.md) now resolves the earlier
recipe obstacle: removing 4450C's artificial padded externs and asm alias gives
all 153 pair words through default CDK and genuine ASPSX. Private real AF3/AFC
storage and the full image pass, with every production module preserved. This
pair awaits the coordinated generic assembler correction; no production
exception or dependency removal is made. AFE has already landed independently.
The earlier negative recipe and pointer-local trials remain recorded.

First execution checkpoint: [SLUS small-data measurements](evidence/fidelity_gp_repair_progress.md).
The isolated generic assembler correction passes 70/70 pinned-version probes and
changes exactly 59/884 SLUS TUs; all 69 affected globals currently have raw-asset
storage and absolute linker names, not C definitions. Five prepared candidates
are genuine-exact and diagnostic-link exact. A three-function owned-data module
now replaces the raw four bytes for D_80080A6C with a real C definition and links
SLUS byte-exact under the corrected assembler (`tools/fidelity/probe_gp_module.py`).
Production module/row/data integration and the other ownership repairs remain
before a global switch. A separate CD-control module source pilot is exact.
The [MAIN coverage audit](evidence/main_kernel_coverage_audit.md)
independently hashes/disassembles all three gaps without claiming C completion.

Second checkpoint: optional module build/verification consumers are implemented
and the real generated stock-Ninja pilot passes the full image gate, genuine
ASPSX (104 words, zero masked relocations), logical-row preservation and negative
candidate checks. See [receipt](evidence/slus_module_build_receipt.json) and
`tools/fidelity/probe_slus_module_build.py`. Canonical-name measurement is fixed;
the fresh stock 59-row census still shows all 59 external-data dependencies.
Production's 884-TU SHA-1 gate and 64 focused tests pass. No production manifest
is active yet: lane diagnostics, status/L4 evidence and the coordinated source/
manifest/pinned-build activation are the next work. The old private verifier
draft has been superseded by the current tools.

Third checkpoint: the inferred `runtime_directory` module is now active in the
production build. Its three canonical row fragments share a typed header and one
real `D_80080A6C = 4` definition. The full image remains retail-exact, with 882
physical compilation units and the same 884 logical rows. Fresh genuine ASPSX
2.79 proofs cover all three functions (104 words, zero masked relocations; no
compatibility passes fired). Certificate: `ledger/modules/runtime_directory.json`.
The unchanged ladder now reports C634/C920 at L5 and C758 at L4 with its
existing fidelity site retained. Only these three dependency entries were removed: 226 -> 223 total, 59 -> 56 GP
rows. No global assembler switch or pass removal has been made. See
[repeatable workflow](SLUS_MODULES.md) and [membership review](evidence/runtime_directory_module.md).
The next bounded data-ownership trials are `slus/w_800508F0` and
`slus/konami_runtime_w_80035888`: each has two contiguous nonzero signed words
and no other recorded users. Detailed ranking:
`work/native_lane/gp_next_cohorts/{REPORT.md,cohorts.json}`. Cross-recipe shared
users remain explicit; do not claim all users of the pilot's global repaired.

Fourth checkpoint: [the ownership wave](evidence/gp_ownership_wave.md) activates
18 more rows and 24 ordinary initialized data definitions, including actual zero
initializers. Nine recipe changes passed the existing lander. Two four-function
slot groups share declarations and each use CDK -G16; all 884 logical rows remain
and physical inputs are now 876. Fresh genuine/retail proof covers 781 words with
zero masks or compatibility passes. Total dependencies 223 -> 205; GP rows
56 -> 38. The twelve new ownership units make no L4 placement claim; the original
pilot has a fresh certificate. Halfword carves now preserve exact layout despite
the old output SUBALIGN(4); a real linker regression test covers the padding bug.
No global assembler switch or pass deletion has been made.

Next hard lead: `w_80047E78` with real storage is genuine-ASPSX/retail exact
(29 words), but stock downstream GNU assembly shortens its address load. The
existing generic GP correction fixes this object; it awaits a linked cohort
proof and the global change. `w_80053CFC` needs the same retail-anchor diagnosis.
Do not repeat the disproved forward-definition/C-shape hypothesis for 47E78.
For later pass retirement, the current single-consumer queue is
`_prefer_lui_over_sll_branch_delay` -> `w_80048224`,
`_sink_call_separated_la` -> `w_8004AB7C`, and
`_hoist_zero_arg_before_global_clears` -> `w_8005D7BC`.
The accepted two missing-compiler rules remain excluded from that queue.

# Handover (2026-09-24, H28 recovery)

Picked up the interrupted 67-row H28 wave from `r77_opus_h1..h16` after the
compiler investigation. **11 functions moved to CDK, 74 pins removed, 9 newly
pin-free and 2 partial improvements.** Ten candidates recovered from h1-h8;
town/func_800B7CEC newly solved with a packed prefix copy and loop-counter
initialization before the entry test. All affected windows MATCH, SLUS MATCH,
row database OK, all eleven exact under genuine ASPSX with no compatibility
passes firing. `maspsx_dependence` 237 -> 226.

Start at `docs/evidence/r77_h28_recovery.md` and its receipt/queued-screen TSV.
The 40 queued h9-h16 rows were calibrated and screened at CDK (erasure alone:
0/40 exact); only the town prefix row received a completed reconstruction.
Do not label these packs completed. The original cohort still has 58 pinned
rows: two partially improved at CDK, 56 at their original proxy recipes.
Continue the interrupted h1-h8 candidates/dumps and the 39 unsolved queued rows.
The old h1 report predates its exact `C98cdk_p27` result and is superseded here.

# Handover (2026-09-24 00:30Z, round 77 in flight) - fresh-eyes check, then an Opus wave

**PAUSE PIN LANES -> `docs/TOOLCHAIN_FIDELITY_PLAN.md` (owner, 2026-09-24).** When the running r77 lanes finish and land, work that plan (steps 1-5) before any new pin lanes.


**Fresh-eyes check of the round-76 plan (what changed it).**
1. **slus was never offered to a strong lane.** `build_class_pack.py:78` and `ab_plan.py` skip `slus` like the parked
   `ovmovie`, with no recorded reason (round 60). slus rows land through the normal gate (`build_slus.sh` in every
   lander; 72 commits under `src/slus`) and the kit scores them. 89 rows / 306 pins had no kit-era astra/Opus serve.
   Wave 1 includes 4 slus rows (via `--rows`, which bypasses the skip); the auto-selection skip is left in place
   until wave 1 shows the kit works on slus rows.
2. **Pins per Opus lane rise with row size** (r73-r76): about 3-5 on 1-pin rows, about 6 on 2-3-pin rows, 9-16 on the
   5-6-pin partial pool. The 8+ band is 106 rows / 1,408 pins (40% of the rest); astra's cluster pack there took 5
   pins at weight 35 (`r76_astra_b8c_1`, 47 -> 42). So wave 1 leads with the 3-7 band and clone representatives.
   The 1-2 band (430 rows / 510 pins) comes after.
3. **Clone families:** 25 live families / 302 pins. Family 0 (10 members, 95 pins) had a rep no strong lane had served.
   Family 1 (11 x 6 = 66 pins) was served only by astra (r75_astra_p4). Family 18's rep is already pin-free and its
   sibling `80EA3000` failed mechanical transfer. All three are in wave 1. **After the clone lanes land:
   `python3 tools/lanes/clone_transfer.py --lanes r77_opus_c1,r77_opus_c2,r77_opus_c3`** (or the families mode).
4. The r76o overlap candidates were already landed as partial wins; the only pending item was the trade (below).
5. `brief_paragraphs/new_findings.md` was dated 09-21. It now carries round 76's set-exactly-once family, the
   dead-init ruling and the sched2-off signature.

**Split-address "toolchain gap" DISPROVED (Fable sceptic, owner request, 2026-09-24).** The retail split pairs come
from the `2.7.2-cdk` cell (address splitting), not the assembler; ~50 rows / ~125 page-constant pin sites at
non-splitting cells are cell-imitation scaffolding. Four owner decisions follow (maspsx la-splitting passes, slus ASPSX
version, small-extern `$gp` model, recipe route): `docs/evidence/r77_splitaddr_verdict.md`. The ADDR_ALIAS comment in
`src/slus/w_8003D92C.c` is wrong.

**Round-77 levers measured:** clone ports (lane given the solved sibling's base/out/REPORT) ~150k tokens and ~6 min a
lane at 3/3 rows vs ~400k / ~45 min for from-scratch lanes; `tools/lanes/port_candidates.py` finds them,
`clone_wholeport.py` does token-identical siblings mechanically. slus: 4 rows served, 1 pin (the split class). Kit fix:
slus rows had func=None (lab.py crashed on all 556).
Review items (landed through the gate): town/func_80953900 deletes a NON_MATCHING block whose arms both reduce to the
symbol; slus/w_8003E39C removes a $3 pin by reusing the $2-pinned variable; spelling trades in r77_opus_c4 (goto into
block, duplicated tails), m7, p1, m5 (dead init). r77_opus_m6 has an unstaged site-for-pin trade
(`trades/func_81875B38_keep_z_dest.c`, 4 -> 1).

**Landed:** `town/func_8032FD1C` pin-for-flag trade (+`-fno-schedule-insns2`; the current 2-pin text is exact at the
target, so rule 2 holds): 3,512 -> **3,510 / 857**. Ledger kind corrected to `pin-for-flag` by hand.
This is the second adjacent town row with the sched2 signature, after round 73's `func_8032E364`.

**Wave 1 (Opus, Agent tool, 7 lanes, 31 rows, `docs/evidence/r77_wave1_rows.json`):** `r77_opus_m1..m4` (3-7 band,
never strong-served, random within container strata seed 77: 12 dungeon / 4 town / 4 slus), `r77_opus_c1` (family
0 + 1 reps), `r77_opus_c2` (family 2, 18, 9, 10), `r77_opus_c3` (1-2-pin family reps 3/15/4/11/7). `land_finished2`
(pid 536862) lands `r77_*`. Record each lane's usage at completion (`record_usage.py`).
Gemini: at its weekly limit since 16:15Z; `gemini_feed.sh` (pid 1018772) re-probes hourly.
compose2 near-fullB2 finished: 211 rows, 11 wins, 5 h.

# Handover (2026-09-23, round 76) - start here

**State.** Round 76 started at 3,701 pins / 902 rows. The owner's 2026-09-23 ruling ("3706 seems like the more
accurate count") made `pin_census.sites_of` count a pin inside a local macro once per call instead of once per
definition (`docs/evidence/r76_pin_count_discrepancy.md`): 3,701 -> **3,706 / 902** (2 rows affected;
`hidden_asm` wrapper-call bucket 9 -> 0). Landings since (cascade catch-up + composition, clone transfer, cell
scan, the A/B harvest, ongoing model lanes) have taken STATUS.md's "Pin sites now" to **3,529 in 865 rows**
(check `grep "Pin sites now" STATUS.md` for the live figure - it moves under `land_finished2.sh`).

**A/B result (`python3 tools/lanes/ab_report.py --glob 'r76*' --ok-only`, last table).** Exact rate / weighted
cost-per-pin (`config/model_cost_weights.json`, luna=1 unit): claude-opus-5-5 50.0% exact, 0.703/pin, weight 10;
gpt-6-astra 56.0%, 4.507/pin, weight 35; gpt-6-sol 16.7%, 1.842/pin, weight 10; gpt-6-luna 10.0%, 1.670/pin,
weight 1; gemini-3.8-flash-high 8.6%, **0/pin (free this window)**; claude-sonnet-5 **0/30 rows** - not a
solver at this band. Routing for round 77+: **Opus is the 1-7-pin workhorse** (cheapest per pin among the
non-free arms); **astra for clone-family representatives, 8+-pin cluster packs, and rows Opus fails** (second
try); **Gemini (agy) free feed takes everything it can** (`tools/lanes/gemini_feed.sh`, pid/log in
`r76_measurement_protocol.md`, stops on `work/native_lane/STOP_GEMINI_FEED` or a probe hitting the weekly
limit); luna/sol stay weak lanes (cheap top-up only, not primary).

**Mechanism: set-exactly-once (`pin_research_round76_move_table.md`).** An `ASM_KEEP`/`ASM_REG` pin fakes a
SECOND set of a pseudo (`REG_N_SETS==1` gets sched.c's `birthing_insn_p` boost and local-alloc's REG_EQUIV
live-length doubling). 25 of the harvest's 43 removed pins are this family. Built/extended generators:
**t118_setonce** (fold an in-place update chain to one set), **t119_deadinit** (owner-approved: a dead `= 0`/
`NULL` declaration initializer is ordinary C, not a dead-store violation), **t120_unvolatile** (drop a
volatile access together with its register pin), t69/t111/t113/t115/t94 extended with UNPIN_REST/HOIST/
ADDRCARRIER/CALLCOPY/CASTUSE levers; **t121_barrierstrip** (probe: strips one-trip `do{}while(0)` + barriers,
0 standalone exact, 2 wins composed with t118/t119/t120, not added to the cascade).

**Tooling fixes this round:** `cascade_list.py` (the one EXTRA_T parser; repaired `cascade_extra.txt` sed
corruption, added t100/t103-t117); `compose2.py` (depth-2 generator composition, now with `--pinfree` for
stage-1 candidates that reach zero pins); `clone_transfer.py` v2 (code-line alignment) + `clone_families.py`
(union-find over 902 rows, 194 pairs, `ledger/clone_families.jsonl`); `served.py` tier guard; `lane_limit.py`;
`record_usage.py`; `lane_cap.py`; cluster packs (`--cluster N-M`).

**Running at hand-back:** `tools/lanes/land_finished2.sh` pid 536862 (lands every `r7[0-9]_*` lane, 15 min
cycle); the Gemini free feed (`gemini_feed.sh`, pid 1018772); `compose2.py r76_compose_near_fullB2 --near 2`
pid 2292536 (depth-2 composition over ~211 near-miss rows, est. 3h+, lands itself). Check liveness with
`ps -p <pid>` before relying on any of these.

**NEXT:**
(a) An Opus wave on the never-strong-served pool (`python3 tools/lanes/served.py --strong-kit --count`) and
the clone-family representatives (`ledger/clone_families.jsonl`, 26 families / 92 rows / 358 pins projected
324 after in-flight transfers); astra as the second try on every Opus miss.
(b) Land the pending recipe trade `town/func_8032FD1C` at `+-fno-schedule-insns2` (found by lane
`r76o_opus_b37`, `cells/town/func_8032FD1C.c`; rules 1-2 hold) through the normal trade lander.
(c) L4 module placement is untouched: all rows still `not_in_module`.

Full detail: `docs/evidence/r76_cascade_compose.md`, `r76_pin_count_discrepancy.md`, `r76_clones.md`,
`r76_cells_small.md`, `r76_measurement_protocol.md`, `pin_research_round76_move_table.md`. Everything below
the previous two dated blocks moved to `docs/handover_archive/HANDOVER_through_20260922.md`.


# Handover (2026-09-23 07:30Z) - round 73/74/75 done: 4,322 -> 3,776 pins, 1,053 -> 911 rows in one night

Read the 2026-09-22 23:55Z block and the 03:40Z / 04:35Z updates below for the design. Outcome (ab_report --ok-only over
r73_*/r74_*/r75_*): **Claude Opus 5.5 lanes** (Agent tool, same kit pack) 215 rows / 132 exact / 251 pins staged;
**gpt-6-astra** 97 / 70 / 154; **gpt-6-sol** 106 / 20 (19%; 30-33% with `brief_paragraphs/residual_to_form.md`, now in
the brief); **gpt-6-luna** 70 / 10 (14%). Routing that held: Opus and astra on 1-6-pin rows (Opus ~70% on 1-pin rows,
50-80% on 3-4-pin, 2-5 rows and 9-17 pins per pack on the partial-residue pool at 5-6 pins; astra 22/30 there);
sol6+v3 as a cheap 30% lane on 3-pin rows; luna6 not worth its tokens; nobody on the astra-failed 11+ residue (0/5) or
the 2-pin dungeon page-constant tail (~20%; cse folds the integer, symbols need a split-address cell). Four recipe
trades landed through `land_coherence.sh` (now LAND_ISOLATED-aware, ROUND/date from env): main/func_8001270C ->
plain 2.8.1; dungeon/func_81811EC0 -> 2.8.1-G0 -mno-split-addresses (byte-neutral, kind corrected by hand);
town/func_8032E364 +-fno-schedule-insns2 (byte-neutral); dungeon/func_810830BC 2.7.2 -> 2.8.1-G0 (coherence, matches
its three twins). Harvests: t103-t113 built (docs/evidence/pin_research_round73_move_table.md; harvest 3 running as
this is written - lanes r73_h3_*, landed by land_finished2). Kit: lanekit/diff.py, dump.py, `lab.py --grid`,
`lab.py cellscore`/--cfg (docs/evidence/lane_tool_harvest_20260923.md: 26/23/21/3 lanes had rebuilt them). Withheld:
`r73_opus_a2/exp/rejected_fakedep/func_8194CF00.c` (identity helper). Review items: `r73_opus_s11` deleted an emptied
`#ifdef NON_MATCHING` declaration block (func_800C30E4), `r73_opus_s20` rewrote a pin-only NON_MATCHING arm
(func_80096134), `r73_opus_p2` dropped a `.set` alias (func_81844800) - all went through the landing gate.
**Next:** partial-residue pool (100 rows at 4-6 pins unserved; `scratchpad/partial_pool.json` rule: live pins, a
candidate somewhere, never Opus-served) for Opus/astra; 64 one-pin retry rows for Opus; land the harvest-3 lanes;
commit config/ tools/ docs/ (the snapshot job commits src/ ledger/ STATUS only). Every pack's rows:
`docs/evidence/r73_ab_rows.json`; pool logs `work/native_lane/_r73_logs/`.

# Handover (2026-09-22 23:55Z) - round 73 in flight: gpt-6-sol / gpt-6-luna A/B

Codex capacity returned early (all four models answer; the 09-26 date in the old error text was wrong). The owner
asked to try the new, much cheaper `gpt-6-sol` and `gpt-6-luna` before spending astra. Three pools are running with
`--no-land` (`tools/lanes/land_finished2.sh`, pid 536862, lands every finished lane every 15 min):
`R73SOL6` (gpt-6-sol, c=4, 11 packs), `R73LUNA6` (gpt-6-luna, c=4, 14 packs), `R73ASTRA` (c=2, 2 control packs);
logs `work/native_lane/_r73_logs/pool_r73{sol6,luna6,astra}.log`, wave script `tools/lanes/r73_ab_wave.sh`, rows
`docs/evidence/r73_ab_rows.json` (3-7-pin band alternated by rank between sol6 and luna6; 8-19-pin band 2:1
sol6/astra; 1-2-pin band luna6; every row a retry of 5.6-era lanes with no candidate anywhere, never served by astra).
Read the result with `python3 tools/lanes/ab_report.py --glob 'r73_*' --ok-only`; baselines (same tool over
`r7[012]_kit*`, `--ok-only`): gpt-5.6-sol 29/95 rows exact (30.5%), gpt-6-astra 96/120 (80%).
Tooling this round (Opus 5.5): `sol6`/`luna6` keys in `launch_lane.sh` + `pool.py`, `pool.py --kit`, `ledger.py`
tiers sol6/luna6 and an ANSI fix for the `model:` header (codex 0.154+ writes it bold; every recent lane had lost its
model in the ledger), `tools/lanes/ab_report.py` + tests (74 pass). The 15 stale unrun kit packs (rows landed since)
were moved to `work/native_lane/_unrun_stale_20260922/` because `served.py` counts an unrun pack's rows as served.
`reset_watch2.sh` (would have relaunched astra + 5.6-sol on those packs) was killed.


**03:40Z update (round 73/74 in flight).** Codex A/B on matched 3-7-pin retry rows: gpt-6-sol 4/40 rows exact, gpt-6-luna
~5/55, gpt-6-astra 5/10 on the same band (and 4/7 on 8+); gpt-6-sol 0/11 on 8+. Claude Opus 5.5 run as lanes through the
Agent tool (same kit pack, `codex.log` carries `model: claude-opus-5-5[1m]`): 1-2-pin band 9/10 rows (17/20 pins), 4-pin
band 7/10 rows (21/40 pins) - the best rate per row tonight; one candidate withheld as a fake dependency
(`r73_opus_a2/exp/rejected_fakedep/func_8194CF00.c`, identity inline helper). Running: R74ASTRA (40 rows, 3-7 band),
R74SOL6V3 (gpt-6-sol + `brief_paragraphs/residual_to_form.md`, A/B vs tonight's 10%), R74ASTRAPRE (astra on sol6-failed
rows with sol6's diagnosis appended), Opus lanes r73_opus_a3-a6 / s3-s6 / h1 (h1 = astra-failed 11-12-pin rows), an Opus
harvest agent (round-73 move table + generators -> `r73_h_*` lanes, landed by land_finished2), a Sonnet check of the
`main/func_8001270C` pin-for-flag trade (plain 2.8.1; record prepared under `r73_opus_s2/exp/1270c/`). Miner's verdict on
the cheap models: `docs/evidence/lane_log_mining_gpt6_20260923.md`. Pins 4,322 -> 4,264 (03:15Z landing). Row plan for
every lane: `docs/evidence/r73_ab_rows.json`.


**04:35Z checkpoint.** Pins 4,322 -> 4,047 in 997 rows (04:08 landing batch of 18 lanes). Decision matrix: Opus 5.5 lanes 65%
of rows exact, astra 68%, luna6 15%, sol6 13% -> 30% with `brief_paragraphs/residual_to_form.md` (adopt for cheap lanes;
pool `R74SOL6V3B` running it on the partial-residue pool's 3-pin rows). Pre-diagnosis for astra: no lift, dropped. Harvest 2
built t109-t113 (43 rows / 55 pins staged in `r73_h2_*`, land automatically). Opus is now on: 1-pin rows (s16/s17), the
partial-residue pool (p1/p2: rows with an earlier partial win, pins left), a8/s14 finishing. The 2-pin dungeon tail of the
1-2 retry pool is hard (page-constant pins: cse folds the integer, symbols need a split-address cell). Full lane list:
`docs/evidence/r73_ab_rows.json`; harvest-3 notes `work/native_lane/_r73_logs/harvest2_notes.md`.


Everything before the 2026-09-23 07:30Z block: docs/handover_archive/HANDOVER_through_20260922.md
