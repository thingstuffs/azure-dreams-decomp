# Private ready18 + CD8 rehearsal

The merged private generated build is a retail match. It preserves all 30
ready18 modules, adds `cd_command_state` as module 31, and retains the existing
`code`/DCE0 partition while moving F240 from the `code2` remainder into the
new CD owner. The graph has 858 physical C objects and 884 logical rows.

The private guarded generic assembler compiled exactly thirteen TUs: the
existing ready18 twelve and the CD owner. The normal link left the CD owner
object unchanged. The image and generated SHA-1 gate match retail; image
SHA-256 is `ae19d8d4bdd2db9a933b1e44d70dd61be670781e441d7cb37da85250a7aed31f`.
All 856 surviving outside C objects are byte-identical to the retained
ready18 stage. The 22 remaining `code2` functions retain 224 exact words;
only F240 moved.

The script freshly recompiled and compared all twelve ready18 physical TUs
inside this merged stage: 18 functions, 891 retail-exact words, zero masks.
It also repeated the 56 prior linked-data checks. The new CD owner has eight
functions, 1041 retail-exact words through fresh generic, built generic, and
genuine ASPSX 2.79, all with zero masks. Its eleven named data pieces have
the specified object bytes, retail asset bytes, and linked VMAs. Together the
measured cohort is 26 functions and 1932 words. The connected collector
closure has 198 emitted functions; this does not claim genuine exactness for
the whole collector.

`receipt.json` retains the full fresh per-owner and data records, generated
graph and closure counts, source/tool SHA-256 provenance, and matching
production snapshots before and after. The CD owner object SHA-256 is
`84b03e9d27636a7eb2804e666989bdc1dbf0532e37e060fea78ddc3ad25743da`
before and after link. The staged owner source SHA-256 is
`3a1a47fdaca76973cef226a7fb9acdc5d7cfe46cdb2cb62eee65da28aa716f6b`.

Reproduce with `python3 work/native_lane/gp_ready26_cd/probe.py` from the
repository root. This proof is scoped to thirteen selected generic assembler
TUs; no global assembler transition or production edit was made.
