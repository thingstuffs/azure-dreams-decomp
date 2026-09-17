# Round 48: Gemini whole-function pilot and a genuine switch

**One pin removed: 6,038 pins in 1,272 functions; 65 gated removals from 6,103.**
The full 173,608-byte covering window and SLUS match. Row database checks pass.
All six edited files pass host NON_MATCHING syntax checks. Evidence, sources,
negative probes and worker briefs are retained in the
[durable receipt](evidence/pin_research_round48_20260917.json).

## Accepted repair

The round 47 `agy` pilot reconstructed `818B15F4` as an ordinary switch. Its
zero-pin candidate missed five address words at the inherited plain 2.7.2 cell.
The same source and old pinned baseline both match at stock `2.7.2-cdk-G0`.
This is a controlled reproducible recipe transition, not proof of the exact
historical compiler release. The reviewed result removes the label keepalive,
computed-goto scaffold and false external epilogue calls. Cases 4, 5 and 6 call
the three real helpers; every other state returns zero.

The complete callback contract passes three pointers. The forwarding helpers,
actual drawing callee and registration declaration now agree. The drawing
callee takes its phase as a full word and performs its existing halfword
conversion locally; moving that conversion into the caller prototype changes
one instruction in each of the three helpers. Existing unrelated pins remain.
See the [review and publication addendum](evidence/pin_research_switch_review_20260917.md).

The first full gate exposed a source-symbol mismatch after rowbase promotion:
the row was registered as `func_80024DF4` but still defined `func_818B15F4`.
Using the proven runtime name restores the existing generic jump-table placement.
No backend or gate implementation changed. The table itself is **before** the
window, at file 0x18D0808/runtime 0x80024008. A separate link that emits its
section proves all eight entries, 32 bytes, against retail. NOLOAD placement
alone would not have established table contents.

Host syntax checks also caught two old unused macros redefining `do` in the
registration caller's NON_MATCHING arm. Removing that dead macro block leaves
all 650 target words unchanged and fixes the host syntax failure.

## Bounded delegation results

`agy --print ... --model gemini-3.8-flash-high` works on this machine. The first
pilot took 243 seconds for five candidates; this round's second function took
308 seconds for six. No token or billing totals were reported by the CLI.

- **818B15F4:** the first pilot supplied the useful whole-switch reconstruction;
  local verification, recipe controls and contract review completed the landing.
- **8195AB84:** Gemini recovered two local jumps into allocation/loop regions,
  not return epilogues. Its best fewer-pin candidate has eight versus nine pins,
  but misses 19 of 113 words. No removal is counted. Its claim that the pinned
  baseline disproves the compiler fingerprint is unverified and must not become
  a lineage conclusion. Audit local-jump classification before further probes.
- **81844F2C:** the other bounded worker exhausted eight source probes. The
  honest local-CFG candidate is 78 versus 79 words, with 34 substitutions and
  one indel. Removing the artificial ABI edge coalesces the input pointer and
  changes the countdown register. No exact removal; no impossibility verdict.
  The lane directory says `luna`, but its model identity was not recorded.

Ten isolated erasures in the three forwarding helpers and drawing callee add
**zero** removals. This directly measures the local cascade for this repair.
The 25 pins in the registration body were not rescanned after declaration-only
work and dead macro cleanup.

## What to do next

The remaining count is pin sites, not distinct patterns. Before this landing,
the local-jump routing inventory had 32 pinned functions/328 whole-row pins,
59 in-row targets and 105 apparent-call sites. That is a candidate inventory,
not a promised yield or a pattern census. Two earlier constructors already
proved that one complete repair can transfer to another function.

Keep using compact function packs with the exact recipe, retail map, actual
callee contracts and a four-to-six-probe limit. Ask the worker to explain the
whole operation and return its best candidate plus the specific residual.
Require it to stop and report contradictory identity or compiler evidence.
A local launcher deadline enforces the budget; `--print-timeout` alone is not
an exact wall-clock cap. Keep workers out of production files and shared gates.

Split the local-jump inventory into actual epilogue returns, internal loop
edges, and switch dispatch before assigning the next few representatives.
These three targets show why mere in-row membership is too broad a family.
Automate jump-target mapping and known positive transformations; reserve
expensive diagnosis for a shared residual such as lost entry copies or allocator
role changes. Do not rerun the archived six/eight-probe menus. Generalize a
source rewrite only when a second independently reviewed example supports its
semantic prerequisites. The zero-pin objective remains active.
