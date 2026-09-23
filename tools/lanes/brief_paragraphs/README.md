# Brief paragraphs

Named paragraphs appended to a pack's `BRIEF.md`, after the standard brief and before the rows:

    python3 tools/lanes/build_class_pack.py <lane> ... --paragraphs big_rows,new_findings

Until round 68 these were `cat`-ed onto each BRIEF.md by hand from the session scratchpad
(`$SCRATCH/big_rows_paragraph.md`, and the "THE CLASS QUESTION" / "NEW TODAY" blocks pasted into
`work/native_lane/r63_astra_*/BRIEF.md`), so they were lost with the session and the next pack got
an older text - or none.

- `big_rows.md` - whole functions with many pins: work the duck's groups, a partial result is a
  success. Append it to every pack built from a big-row list.
- `class_question.md` - TEMPLATE for a one-class pack (the mechanism is the ask, not the rows).
  Copy, fill the `<<...>>` slots by hand, pass the copy's name.
- `cluster_partial.md` - a CLUSTER pack (`build_class_pack.py --rows ... --cluster 3-5`, round 76): one
  cluster per big row, land it and keep every other pin. Added automatically in cluster mode (and by
  `kit_pack.py` when the lane has `cluster.json`).
- `new_findings.md` - "NEW TODAY": what yesterday's lanes found that this pack should try first.
  Rewrite it at the top of a round; it is the one paragraph that goes stale in a day.

Keep each one short enough to be read: they compete with the row's own duck brief.
