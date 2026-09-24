# Prior E758 wall and rebuild evidence

## Located records

- `work/wall_8003E758/REPORT.md` is absent from this checkout.
- The exact prior report exists at `<reference-repo>/work/wall_8003E758/REPORT.md` (dated 2026-07-08). Its named candidate/scorer artifacts also exist there: `v3_cdk.c`, `v4_layout.c`, and `score_configs.py`. Hashes are recorded below so the parent can identify this snapshot.
- The bounded `docs/` search found supporting current-tree snapshots under `docs/evidence/gp_component20_local/`; the bounded `tools/learnings/` search found no E758-specific note. The only file in that directory was the unrelated `pin_aggregate_contracts.md`.

## What the wall report claims

The report routes the historical “compiler-version wall” for `func_8003E758` to source shape plus distinct emission features. Its leading source-shape claims are: retain pointer bases to `D_80083958` and `D_80083968` across state arms/calls to get byte-shaped held bases and displacement accesses; use retail's lexical switch/block order; and express head-index accesses with neighboring-byte pointer expressions such as `hp = &D_800814D3; hp[-3]`. It also records a state-local `idx` read, explicit `case 4`, and a `case 0xFF` constant comparison. These are candidate-source findings in the wall report, not claims that a unique historical source has been recovered. See its “C-shape discoveries” and candidate pointers below.

The report separates three code-generation observations: (1) cdk/2.8.x at `-G8` retains the tested pointer bases while the 2.7.2/PSYQ 4.0 tests fold them; (2) a two-label split `la` can place the `lui` in a jump delay slot; and (3) macro direct stores can expand to fresh `$at` sequences, whereas the tested `-mgas` path allocated `$2/$3` scratch. It says genuine CC1PSX 4.1 `-mmips-as` produced macro stores but kept `la` macro-shaped, so it did not combine all three observed features in those trials. The report proposes an opt-in maspsx split-store `$at` canonicalization lead and notes that this would not repair shared `%hi` values in its cdk `-O2` output.

The lineage discussion calls cdk/PSYQ 4.1 a useful comparison point and describes `addiu $sN,$v0,%lo(SYM)` as a cdk/4.1-lineage fingerprint, reportedly present at 66 main-EXE sites. This is a heuristic in the report, not proof of E758's original compiler binary or source TU.

## Flags and score scope

The report's aligned-LCS table gives these distances (subs+indels over reloc-normalized words):

| Tested recipe label | v3 | v4 |
| --- | ---: | ---: |
| PSYQ 4.0 / 2.7.2 O2 | 508 | 424 |
| cdk O2 / PSYQ 4.1 | 704 | 478 |
| cdk O1 | 1292 | 567 |
| 2.7.2 O1 / PSYQ 4.0 O1 | 786 | 689 |

The report cautions that the 4.0 O2 score is not the preferred lead because it folds the held bases; cdk's store-dialect residual is described as bridgeable. It also notes `match.py --psyq X --opt O1` silently uses O2 unless `--gcc-flags "-O1"` overrides it. These are finite tested cells and candidate scores. They do **not** establish that no compiler/flag combination can match retail. The `-mmips-as` conclusion is likewise limited to the tested CC1PSX 4.1 probe.

The current-tree GP audit is a separate evidence context: `docs/evidence/gp_component20_local/REPORT.md` records the current split row `slus/w_8003E758` as CDK 2.7.2 with `-G32 -fno-expensive-optimizations`, 698 retail words and five registry `defs` (one lexical source body). Do not substitute that recipe for the wall report's cdk O1/O2 or 2.8.x micro-probe cells. Its companion receipt records matching built-image and split-asset slices for that snapshot, not a historical-TU attribution.

## Pointers and identity

- Prior wall report: `<reference-repo>/work/wall_8003E758/REPORT.md`
- Candidate C: `<reference-repo>/work/wall_8003E758/v3_cdk.c`, `<reference-repo>/work/wall_8003E758/v4_layout.c`
- Score implementation: `<reference-repo>/work/wall_8003E758/score_configs.py`
- Current-tree local GP audit and evidence: `docs/evidence/gp_component20_local/REPORT.md`, `receipt.json`, `retail_3e758_698.dis`, `source_hits.txt`
- Current-tree recipe and extern evidence: `docs/evidence/fidelity_step1_maspsx_dependent.tsv` row 424; `docs/evidence/fidelity_step1_gp_extern_rows.tsv` row 18; `docs/evidence/fidelity_gp_symbols.tsv` rows 14–18.

Hashes of the external wall snapshot files checked:

```text
58ba99b0386c66619113d6450776844fcc7fad68321c96c31bed082a5919b8a5  REPORT.md
5684b545e426f3c4b8d30465d3ba8209c67b0dbe73040190f8bbb20f272ccb07  v3_cdk.c
3510fa4414dde8d17015d4692cd0536f544886cedb0ca335a099b266ea878060  v4_layout.c
a5ca37f7409cbc16579ccfc965bf385626ea5898680d345383b4c2b49ef1e0f7  score_configs.py
```
