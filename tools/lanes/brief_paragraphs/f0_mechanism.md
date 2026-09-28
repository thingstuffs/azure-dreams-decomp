## Mechanism task (clone family F0: 11 byte-identical rows, 66 pins)

This pack is ONE row, and a solution ports mechanically to 10 clones (clone_transfer.py). The previous lane
(r78_opus_c1, evidence/func_80BE5084_c1.md, its dumps under evidence/prior_r78_opus_c1/) measured the mechanism:
the three dead volatile colour read-backs are the whole residue, and retail's sched1 must have placed them inside
the first OT insert (OT1a) with the `$6=$4` argument copy between green and blue. Run ITS falsifiable next
measurement first:

1. Diagnostically (hard-reg bindings are fine in a DIAGNOSTIC text, never in a candidate) build a text whose three
   read temps sit inside OT1a at sched1; `dump.py --pass all`; does local-alloc give red->$3, green->$6, blue->$7,
   and does sched2 then reproduce retail?
2. YES: search ordinary C shapes that make the OT1a launch chain leave three gaps (non-birthing OT temporaries,
   load-latency stalls, the real OT/packet types of the sibling pin-free rows func_818D4800 / func_8187B5A0).
   NO: the reads were live together at local-alloc through a real consumer removed after reload - test shapes that
   jump2's delete_computation removes (it stops at in-place ops and can leave a load behind).
Report the answer to (1) whatever happens: it is a reusable finding even with no pin removed.
