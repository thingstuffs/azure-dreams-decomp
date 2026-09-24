# Toolchain fidelity: ASPSX version trial (measurement only)

Brief: `work/fidelity/STEP_ASV_BRIEF.md` (follows "decision 2" in `docs/evidence/fidelity_step1_aspsx_diff.md`).
Question: the pipeline runs maspsx with `--aspsx-version=2.56`, but genuine ASPSX 2.56 cannot parse `%hi/%lo` and every
genuine-exact row is reproduced by 2.77/2.79/2.81. Would switching maspsx to `--aspsx-version=2.79` (or 2.77) be
byte-neutral over the WHOLE tree?

This was measurement only. Nothing under src/, include/, ledger/, config/, tools/maspsx or tools/build was edited. No gate,
landing or git command was run.

- Tool: `tools/fidelity/asv_trial.py` (reuses aspsx_diff's compile and verdict code). Tables:
  `tools/fidelity/asv_report.py`. Test: `tools/tests/test_asv_trial.py` (7 tests: the version-to-behaviour table,
  the classifiers, the predictor, and one synthetic positive control per version-gated behaviour, run through the
  real maspsx).
- Data: `work/fidelity/asv/asv_trial.jsonl` (6,767 records, hash-keyed and resumable), `tables.md` (the generated
  tables), `changed_rows.tsv` (the 85 rows that change at 2.81), `dial_rows.tsv` (the 23 row dials).
- Re-run: `python3 tools/fidelity/asv_trial.py --workers 8` (25 min on this box), then
  `python3 tools/fidelity/asv_report.py > work/fidelity/asv/tables.md`.

## Headline

**Yes. `--aspsx-version=2.79` is byte-neutral on all 6,767 rows, and so is 2.77.** At each of 2.60, 2.77 and 2.79,
every row's maspsx object is **byte-identical** (sha256 of the `.o`) to the 2.56 object. No row changes, so no row
stops matching and none starts matching. The 2.77 and 2.79 objects are identical on 6,767/6,767 rows.

| global `--aspsx-version` | same object | changed, still exact | stops matching | starts matching |
|---|---|---|---|---|
| 2.60 | 6,767 | 0 | 0 | 0 |
| **2.77** | **6,767** | 0 | 0 | 0 |
| **2.79** | **6,767** | 0 | 0 | 0 |
| 2.81 | 6,682 | 0 | **85** | 0 |

The baseline is sound. On all 6,767 rows the maspsx leg at 2.56 is retail-exact by the pipeline's own verdict: 6,766
pass the scorer or `verify_slus`, and slus/w_8005A1D0 is proven by direct retail resolution, as in step 1. The
self-check also passes on 6,767/6,767 rows: the traced 2.56 object equals the pipeline's object (slus: sha256; overlays:
every word equals the scorer's linked slice outside relocation fields). "Starts matching" is empty by construction,
because every row already matches at 2.56. The column is reported, not dropped.

**2.81 is NOT neutral.** 85 rows stop matching (42 dungeon, 18 slus, 16 main, 8 town, 1 ovmovie; by cell: 24 at 2.6.3,
27 at 2.7.2, 22 at 2.7.2-cdk, 6 at 2.8.0, 6 at 2.8.1). All 85 are caused by maspsx's `gp_allow_la` (see below).

## Why 2.77 == 2.79: the version-gated behaviours

maspsx never sees the version string. `config_for_aspsx_version` (tools/maspsx/maspsx.py) maps the version to eight
flags that `MaspsxProcessor` reads, and the processor has no other version test (`self.<flag>` reads at the lines
cited below). Between 2.56 and 2.8x, three flags change:

| maspsx flag | set at | what it does (tools/maspsx/maspsx/__init__.py) | 2.56 | 2.77 / 2.79 | 2.81 |
|---|---|---|---|---|---|
| `expand_li` | < 2.50 | `li rX,K` becomes `ori rX,$zero,K` (old-ASPSX li expansion; l. 3976, 6071) | off | off | off |
| `sltu_at` | < 2.60 | `sltu rD,rS,-K` becomes `li $at,-K; sltu rD,rS,$at` (l. 6193) | **on** | off | off |
| `gp_allow_offset` | >= 2.70 | a `SYM+OFF` operand of a small `.comm` symbol may be `$gp`-relative; this changes `%gp_rel` emission and the load-delay nop decision `_uses_gp` (l. 3851, 5894, 6003) | off | **on** | on |
| `gp_allow_la` | >= 2.80 | a bare `la` of a small-data symbol may be `$gp`-relative, and it disables the post-pass `_expand_smalldata_la` (l. 5247, 6009) | off | off | **on** |

(`div_uses_tge`, `nop_at_expansion`, `nop_mflo_mfhi` and `addiu_at` only differ below 2.30.) 2.77 and 2.79 therefore
produce the same config, so the two trial versions are one trial. The tree run confirms it: the objects are identical
on every row. The trial versions nest: 2.60 flips `sltu_at` only, 2.7x adds `gp_allow_offset`, and 2.8x adds
`gp_allow_la`. The first version at which a row's object moves therefore names the flag responsible.

| cause (first version that moves the object) | rows | class at 2.79 | class at 2.81 |
|---|---|---|---|
| `sltu_at` (2.60) | 0 | - | - |
| `gp_allow_offset` (2.7x) | 0 | - | - |
| `gp_allow_la` (2.8x) | 85 | same | stops matching |

A static predictor was also run on maspsx's input for each row. It counts the constructs each flag rewrites:
negative-immediate `sltu`, `SYM+OFF` memory operands of a small `.comm` symbol, and bare `la` of a small-data symbol.
It agrees with the measured result and misses nothing:

| behaviour | rows with the construct | rows whose object moved | moved but not predicted |
|---|---|---|---|
| `sltu_at` | 1 (town/func_80614B88, whose own `--aspsx-version=2.60` dial already turns it off) | 0 | 0 |
| `gp_allow_offset` | 0 | 0 | 0 |
| `gp_allow_la` | 85 | 85 | 0 |

So the 2.79 switch is neutral for a structural reason, not by luck. Outside the one row that already carries a 2.60
dial, the tree contains no construct that `sltu_at` or `gp_allow_offset` acts on. The synthetic controls in the test
show that each flag does move an object when its construct is present, so a future row with a negative `sltu`
immediate or a `.comm SYM+OFF` access WOULD assemble differently at 2.79. Such a row would then be judged by genuine
ASPSX's behaviour (genuine ASPSX 2.67-2.86 emits `sltiu`, 2.56 and older `li $at; sltu`: `tools/maspsx/aspsx/test_sltu_at.py`), which is the faithful direction.

### 2.81: the extern `la` guard is tied to `gp_allow_la`

All 85 rows that change at 2.81 are the rows where `_expand_smalldata_la` fires today. At 2.81 it stops firing (the
only difference in fired passes at any trial version), and every one of these `la` targets is an **`.extern`** small
symbol, not one the TU defines (85/85, checked on maspsx's input). The mechanism has two parts. maspsx's own `$gp` rewrite
of `la` (in `_process`) applies only to TU-defined small data (`sdata_entries`/`sbss_entries`), so it touches none of
these rows. What moves the object is that `_expand_smalldata_la` stands down (`if self.gp_allow_la: return res`). The
bare `la` of an extern then reaches GNU as, which `$gp`-relativises it on the strength of the `.extern` size: the
extern-size leak of step 1's decision 3, this time through `as`. In the step-1 journal, **68 of these 85 rows are exact
under GENUINE ASPSX 2.81 and 2.86** (55 under all six versions, 13 under 2.67+). The other 17 are maspsx-dependent for
other reasons. Genuine 2.81 does not `$gp` these extern `la`s. The version gate on `la` of TU-DEFINED small data may
well model genuine >= 2.80 correctly. What is wrong is that the guard for EXTERN targets hangs on the same flag.

## Per-row version dials (23 town rows)

A row dial is a row as-flag `--aspsx-version=X` (config/overlays/town.as_flags.jsonl, carried as `row_asflags`). It
comes after the global flag on the argv (in tools/build/cc.sh, tools/verify.py and match.build_text), so argparse's
last occurrence wins and the dial overrides the global version. Under a global switch to 2.79 all 23 dial rows are
therefore byte-identical ("global 2.79, dial kept" = same).

What each dial does, measured by dropping it (at 2.56 = today's global, and at 2.79 = the proposed global):

- **`--aspsx-version=2.40` (21 rows) and `2.34` (1 row: town/func_80878924)**: 2.40 and 2.34 produce the same maspsx
  config. Against 2.56 their only effect is `expand_li` (`li` becomes `ori rX,$zero,K`, the old-ASPSX materialisation
  retail has in the town islands 0x80874C9C-0x808816D8). Every one of them is load-bearing: dropped at 2.56 or at
  2.79, the row stops matching (1-6 words). No version >= 2.50 has `expand_li`, so the switch cannot retire them.
  They stay, and they are the rows that need an ASPSX older than any genuine one we hold (step 1).
- **`--aspsx-version=2.60` (1 row: town/func_80614B88, 2.7.2-cdk)**: its only effect against 2.56 is
  `sltu_at` off (`sltiu` rather than `li $at; sltu`). Dropped at 2.56 it stops matching (4 words). **Dropped at 2.79 its
  object is byte-identical to today's.** The global switch retires this dial: it becomes redundant, because 2.79 is
  already `sltu_at` off. The dial also moves the row from 2.60 to 2.79's `gp_allow_offset`, which is inert on it.

| row | dial | cell | global 2.79, dial kept | dial dropped @2.56 | dial dropped @2.79 | config dial -> 2.79 |
|---|---|---|---|---|---|---|
| town/func_80878924 | 2.34 | 2.7.2 | same | stops-matching (1 w) | stops-matching (1 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_80874D84 | 2.40 | 2.7.2 | same | stops-matching (1 w) | stops-matching (1 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_80874E18 | 2.40 | 2.6.3 | same | stops-matching (3 w) | stops-matching (3 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_80874F4C | 2.40 | 2.6.3 | same | stops-matching (2 w) | stops-matching (2 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_80875060 | 2.40 | 2.7.2 | same | stops-matching (1 w) | stops-matching (1 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_80875124 | 2.40 | 2.6.3 | same | stops-matching (1 w) | stops-matching (1 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_8087514C | 2.40 | 2.7.2 | same | stops-matching (2 w) | stops-matching (2 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_80875238 | 2.40 | 2.6.3 | same | stops-matching (3 w) | stops-matching (3 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_808752CC | 2.40 | 2.6.3 | same | stops-matching (3 w) | stops-matching (3 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_80875364 | 2.40 | 2.6.3 | same | stops-matching (3 w) | stops-matching (3 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_808755AC | 2.40 | 2.6.3 | same | stops-matching (3 w) | stops-matching (3 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_808757A0 | 2.40 | 2.6.3 | same | stops-matching (1 w) | stops-matching (1 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_80878974 | 2.40 | 2.7.2 | same | stops-matching (1 w) | stops-matching (1 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_80878A78 | 2.40 | 2.7.2 | same | stops-matching (6 w) | stops-matching (6 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_8087FD58 | 2.40 | 2.6.3 | same | stops-matching (1 w) | stops-matching (1 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_8087FDA4 | 2.40 | 2.6.3 | same | stops-matching (2 w) | stops-matching (2 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_8087FE98 | 2.40 | 2.6.3 | same | stops-matching (1 w) | stops-matching (1 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_8088116C | 2.40 | 2.6.3 | same | stops-matching (1 w) | stops-matching (1 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_8088124C | 2.40 | 2.6.3 | same | stops-matching (6 w) | stops-matching (6 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_808813CC | 2.40 | 2.6.3 | same | stops-matching (1 w) | stops-matching (1 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_80881478 | 2.40 | 2.6.3 | same | stops-matching (3 w) | stops-matching (3 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_808816D8 | 2.40 | 2.6.3 | same | stops-matching (5 w) | stops-matching (5 w) | sltu_at True->False; expand_li True->False; gp_allow_offset False->True |
| town/func_80614B88 | 2.60 | 2.7.2-cdk | same | stops-matching (4 w) | same | gp_allow_offset False->True |

## Method

For every row in ledger/rows.jsonl, one gcc -S of the row's current `src/` text at its registered recipe is made
through the project pipeline itself: `aspsx_diff.prepare_slus` (= `verify.compile_slus` and its verdict) or
`prepare_overlay` (= the per-row scorer's `overlay_func_compare` steps and its `linked_words_equal` verdict). Then:

1. The maspsx leg (unmodified maspsx, traced by `tools/fidelity/maspsx_trace.py`) is run at 2.56, 2.60, 2.77, 2.79 and
   2.81. Only the pipeline's global `--aspsx-version=2.56` (argv element 0) is swapped; the row's own flags, a version
   dial included, stay where the pipeline puts them.
2. An object byte-identical to the 2.56 object is `same`, a sufficient condition for byte-neutral.
3. A changed object is judged the way the maspsx leg is judged now. slus rows use verify_slus's rule (the pinned TU
   object's sha, else a name-masked disassembly identical to `ledger/cache/slus_dis`), with a direct resolution against
   the retail SLUS as supplementary proof. Overlay rows use the scorer itself: `match.build_text` at that
   `--aspsx-version` with the scorer's captured argv, then `linked_words_equal` against the retail slice. Changed slus
   objects were also resolved against the retail SLUS: all 18 differ from retail (1-85 words), so no pinned-object
   artefact hides a match.
4. Dial rows are also run with the dial dropped, at 2.56 and at 2.79.
5. Each row's changes are attributed to a flag by the first version at which its object moves, and cross-checked by
   the static predictor.

Validation (before the tree run): town/func_80614B88 (dial 2.60: dropped at 2.56, 4 words off; dropped at 2.79,
same); town/func_80874D84 (dial 2.40: kept, same; dropped, 1 word off at both versions); slus/w_8003D92C (same at
every version); dungeon/func_7FFE83DC (`_expand_smalldata_la` row: same through 2.79, 57 words off at 2.81); and the
synthetic controls in the test (a negative `sltu` moves at 2.60, `lw; sw $2,D_c+4` with `.comm D_c,8` gains a
load-delay nop at 2.79, and `la` of a small extern becomes `addiu $5,$gp,...` at 2.81).

Run notes:
- The first tree run (8 workers, 1,494 s) shared the scratch directory `work/fidelity/tmp/rows` with the concurrent
  step-1b job, which deleted it mid-run. 10 dungeon rows ended in a harness error and 10 more lost some version legs.
  In the other direction, the end of that first run removed `work/fidelity/tmp/rows` (aspsx_diff's default scratch) at
  about 06:56 and may have hit a concurrent fidelity job that was using it. The tool now uses its own scratch directory
  (`work/fidelity/asv/tmp`), the only directory it ever removes. The 21 affected rows were re-run cleanly (those 20 plus
  slus/w_8005A1D0, whose verdict now falls back to retail resolution as in step 1).
- The tables above come from a **second full tree run with the final code** (6,724 rows recomputed, 1,249 s; the other
  43 were current), with the same result.
- Journal currency: the key fingerprint (aspsx_diff's `tool_fingerprint` plus this tool) hashes files a concurrent job
  was changing (`tools/verify.py`, the `ledger/cache/slus_obj.json` pin cache, the SLUS ELF). The fingerprint moved
  during this work, so a later re-run may recompute every row. The byte-identity result depends only on the gcc -S
  output and maspsx, not on those files.

## Where the literal 2.56 lives (the switch is a multi-site edit)

- `tools/build/cc.sh:21` (SLUS build; mirrored in `build_ovl/tools/cc.sh:21`)
- `tools/verify.py:305` (`compile_slus`)
- `tools/gate/overlay_func_compare.py:597` (the scorer's `build_text(..., "2.56", ...)`; mirrored in
  `build_ovl/tools/overlay_func_compare.py` and `build_ovl/work/g3/overlay_func_compare.py`)
- `tools/gate/residue_class.py:140` (and its `build_ovl/tools/` mirror)
- `tools/gate/match.py:1458` CLI default `--aspsx 2.56` (and the `build_ovl/tools/` mirror); `match.py`'s "all" sweep
  lists 2.34/2.56/2.79/2.86
- the measurement tools that model the pipeline: `tools/fidelity/aspsx_diff.py` (prepare_slus/prepare_overlay, and
  the `asv:` ablation, which substitutes the literal string) and this trial (`BASE`)

The 2.40/2.34/2.60 dials in `config/overlays/town.as_flags.jsonl` still override the global version after a switch.

## Decisions for the orchestrator / owner

1. **Switch 2.56 -> 2.79: measured byte-neutral on 6,767/6,767 rows** (identical objects, not just identical verdicts).
   It makes the recorded assembler a version that can assemble the tree's `%hi/%lo` output, and it is the version
   genuine ASPSX reproduces. 2.77 is the same maspsx model, so which of 2.77 and 2.79 to write down is a record-keeping
   choice only (step 1 found 2.77 = PsyQ 4.3 and 2.79 = PsyQ 4.4 equivalent on every genuine-exact row). Making the
   switch means editing the sites above (tools/build, tools/gate, tools/verify.py), and the gate must still be run
   once: this trial measured the per-row verdict paths, not the full SLUS link or the overlay window gates.
2. **Do not use 2.81 (or anything >= 2.80) in maspsx as it stands.** 85 rows break, 68 of which genuine 2.81/2.86
   reproduce. If anyone wants maspsx to say >= 2.80, `_expand_smalldata_la` must keep firing for `.extern` targets at
   every version (genuine ASPSX never `$gp`s an extern), with only TU-defined `la` gated on `gp_allow_la`. That is a
   one-condition maspsx change, to be made and gated separately. It is not needed for the 2.79 switch.
3. **Retire the town/func_80614B88 `--aspsx-version=2.60` dial with the switch** (its object is identical without it
   at 2.79). Keep the 22 `2.40`/`2.34` dials: `expand_li` is load-bearing on all of them at any version >= 2.50. 2.34
   and 2.40 are the same maspsx config, so the one 2.34 dial could be spelled 2.40 for uniformity (byte-identical).
