## CLUSTER PACK: one cluster per row, a PARTIAL landing is the goal

Each row here is a big function (8+ pins) served for ONE cluster of 3-5 pins, named under
**TARGET CLUSTER** in `rows.md` and recorded in `cluster.json`. The listing diff shows what erasing
ONLY that cluster changes; every other pin of the row stays exactly where it is.

- Make the cluster's pins fall (all of them, or as many as you can) with the rest of the row
  unchanged and byte-exact. A candidate that removes 2 of the 4 target pins and keeps the other
  pins is a success: stage it in `out/` like any byte-exact candidate. Owner ruling 2026-09-22
  (afternoon, (c)): partial landings of a multi-site row are allowed (fewer sites, bytes exact).
- Do not start on pins outside the cluster; if a cluster pin only falls together with an outside
  pin, say which one, and land the pair only if both fall byte-exact.
- Never add a pin, fence, `volatile` or one-trip block elsewhere to pay for a cluster pin (the land
  script's grow check refuses it; a tracked site-for-pin trade needs the orchestrator).
- Why: whole-function lanes on rows with 11+ pins of residue went 0/5 (gpt-6-astra, round 74), while
  round 75's partial-landing packs (`r75_astra_p*`) took 30 pins to 15. The residue you leave is a new
  text and is served again as its own cluster.
- REPORT.md: per row, the cluster pins that fell, the ones that did not (with the residual you named),
  and which other cluster of the row looks next.
