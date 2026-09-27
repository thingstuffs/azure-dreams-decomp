## Fresh-eyes continuation

This is a CONTINUATION pack (cut-off experiment, `tools/lanes/cutoff_report.py`): earlier lanes worked these
rows and stopped close but not exact. Their findings, best partial candidates and failed spellings are in
`evidence/` (one `<row>.md` per row, plus `prior_<lane>/`). Use them, but as a skeptic with fresh eyes:

1. Before your first compile, re-measure the prior best partial (lab.py) - do not trust a recorded distance.
2. Write down, per row, which of the prior lane's ASSUMPTIONS you doubt (the mechanism it named, the variable
   roles, the types, the control-flow shape) and test the doubted one first. Do not re-run spellings the evidence
   lists as failed unless you changed what surrounds them.
3. The remaining gap is usually outside the local window the prior lane stared at: address formation, a
   variable's live range across the whole function, set counts, the real types of a parameter or field, the
   callers' and callees' prototypes, or the true control-flow shape.
4. Report per row: which prior assumption was wrong (or that none was), and the distance you reached.
