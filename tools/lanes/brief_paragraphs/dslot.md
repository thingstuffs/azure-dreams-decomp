## Delay-slot residues (r85_opus_dbrtool / r85_opus_dslot, 2026-10-01)
If the erased text differs only in a branch's or call's delay slot, run `tools/lanes/lanekit/dbr.py <row> erased --retail` (or `why.py --pass dbr`). Its DECIDING line names the cause. The most common one: cdk predicts an EQ branch NOT taken and fills the slot from the owned fall-through, while retail's slot holds the head of the target thread. Levers:
- **A `for` loop:** its LOOP_VTOP note right after the target label predicts the branch taken. This solved 810ADDF4 and 80B471EC.
- **A label at the arm head:** the fall-through is then not owned.
- **A fall-through head that reorg refuses.**

If dbr reports "ADDED ... at (use (insn N))", a USE marker from an earlier jal-slot fill holds the register live. Only an argument set placed before the branch helps then (800C379C).

r86 (800C379C 4->0, r86_opus_nm2): when dbr.py shows fill_eager refusing an argument move at the head of the fall-through
arm because of a `(use (insn N))` marker, compute the test into a local, copy the argument BEFORE the branch, use the copy
only in the fall-through arm and give the copy a real later role in the taken arm (cse.c 856-870 then keeps the copy as
class head on that path; reorg's fill_simple takes the pre-branch set backward into the slot).
