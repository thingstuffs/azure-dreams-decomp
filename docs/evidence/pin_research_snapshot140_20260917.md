# Round 42: Snapshot140 reconstruction

`dungeon/func_8008EE88` has 24 pins and 181 retail words. Its recorded
2.95.2-G0 baseline is exact. Source SHA-256:
`e1e8b2857ae1036d4b253d062848c89d0608906aa11edebed7d510304122cb0d`.
Retail SHA-256:
`ae091bfe85a71aea5127ca696b1dcfb5d1bc5167ae485dfe8599a461fa27b438`.
No source or recipe change was landed for this row.

The two manual loops each copy 128 bytes plus a 12-byte tail. The existing
source already names `Blob140`. Replacing both complete loops with aggregate
assignments and erasing all 24 pins produces 189 words and aligned distance 158
at 2.95.2-G0. This is a diagnostic, pending review of the inherited volatile
stores and actual objects.

Using stock CDK and existing symbolic table/buffer declarations recovers much
of the first 80 words: 187 words, distance 53. Expressing a separate unaligned
four-byte snapshot field as a four-byte aggregate then naturally emits retail's
`lwl/lwr` and `swl/swr`. This zero-pin candidate (`aggregate_copy4.c`) reaches
180 words and distance 40. Its SHA-256 is
`d08e16fa44bb3cdb210de36dbf2b00eff054090d235297f6969db08c7f47a519`.
It is not exact and is not a landing candidate.

The frame is 48 bytes instead of 56. Retail holds the shared snapshot-buffer
page in s7 across the second loop; the ordinary candidate does not. Index and
slot-field cursors also have different base/offset representations. These
controls distinguish the issues:

- Changing only the two copies while retaining existing pins at 2.95.2 keeps
  181 words but has 42 substitutions: the copy itself changes allocation.
- That control plus the four-byte aggregate at CDK has 182 words and distance
  25; the remaining scaffolding does not establish a correct ordinary source.
- Restoring only the existing buffer-page keep in the zero-pin CDK diagnostic
  restores the frame and saved-register set, but leaves distance 41 and 180
  words. The keep is diagnostic evidence, not a proposed repair.

The next experiment should trace how the compiler shares the buffer's high
page and low address across the second loop. Recover the surrounding global
object layout and both index-array views before changing body expressions.
A real object relationship must explain the retained page; dead uses, literal
page bindings and replacement pins do not count. The 140-byte record is a
snapshot prefix: the routine also reads record byte 0xA8, so the full runtime
object must be larger. The [independent semantic review](pin_research_snapshot140_review_20260917.md)
supports ordinary nonvolatile RAM, a disjoint second copy and a disjoint-or-exact-self
first copy in recognized writers. Common types and indirect writers remain open.

Artifacts: `work/native_lane/r42_snapshot140/` contains the complete retail map,
source controls, compiler output, scores and identity receipt. These bounded
negatives establish neither an architectural limit nor a unique compiler
release.
