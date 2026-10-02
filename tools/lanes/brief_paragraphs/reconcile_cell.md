## Rows on a crutch cell: work them at the PROVEN recipe (owner rule 2026-10-02)
r84_fable_build established the build: one `2.7.2-cdk -G0 -O2` game build (plus the town -O1 debug family, the
devkit/Sony objects at 2.6.3, two stock Konami objects). Every 2.8.0/2.8.1/2.91.66/2.95.2 registration is a FITTED
cell, a stock cell inside a cdk run is a crutch, and overlays are -G0 everywhere (no overlay function touches $gp).
The owner's rule: **never write C to satisfy an incorrect compiler setting.** If your row's registered cfg differs from
the proven recipe named in rows.md, its pins are likely compensating for the wrong compiler: score and stage at the
PROVEN recipe (`lab.py <row> cand.c --cfg <proven> --score`, then `lab.py stage-cell <row> cand.c --cfg <proven>
--note "..."`), not at the registered one. A candidate exact only at a cell or flag the module does NOT use is not a
landing: report it as a side lead (what that cell difference reveals about the source) and keep working at the
proven recipe.
