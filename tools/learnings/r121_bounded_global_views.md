# r121: bounded import views and short-valued parameters

Measured scope: the r121 remnants continuation; genuine 2.7.2-cdk-G0 and
2.6.3-G0, unchanged MASPSX/ASPSX-2.79 pipeline. These are source reconstruction
observations, not a recipe sweep or a rule to recast arbitrary globals.

* The newly recovered DUNGEON callbacks at file 0x1955128 (168 B) and
  0x1967288 (140 B) read/update the same imported 32-bit flags word at
  0x800814A0. A bounded `struct { s32 flags; }` extern and a local pointer to
  it reproduce the complete retail bodies. The initial scalar-extern views
  scheduled the global read before the preceding owner-halfword write; the
  initial candidates scored 9 and 10 respectively. Full scalar source remains
  reconstructible from the lane's continue_large.py; the exact views are in
  src/dungeon/func_81935128.c and func_81947288.c. The type is a four-byte
  imported view; it is not an ownership claim or a page-sized alias barrier.
* At TOWN file 0x26E624, the 168-byte initializer requires individual word
  assignments. Bounded single-word default-object views and the observed
  read order reproduce the complete body at 2.6.3-G0. The corresponding
  180-byte loop at 0x26E6F4 likewise uses individual assignments rather than
  whole-structure copies. The final combination is measured; do not infer
  that either edit alone is universally sufficient.
* DUNGEON file 0x19BB124 has a short-valued incoming frame argument, promoted
  to an ordinary s32 local before the test/decrement. That lifetime produces
  the required sll/sra conversion while retaining the other saved-register
  roles. The final 320-byte source, argument types and store order are jointly
  verified; changing the coordinate parameter widths changed allocation.

The unresolved counterexample is dungeon/func_800B7914. Its bounded two-word
MenuState retains HIGH across the call, but the active field at +4 receives a
low-base add before the load. The pending field at +0 already uses LO_SUM.
A matching complete C body has not been found; the actual full candidate is
180 bytes against 176 retail bytes. Literal 0x80010000 page views are not
admitted. See the lane hold and r121_remnants_continue.receipt.json.

## ABI admission

A wrapper that compiles to the same jal sequence with an empty parameter list
does not establish ordinary C semantics. Forward every actual callee argument
and result explicitly. The r121 continuation rescored 231 corrected wrappers
exactly; 28 candidates with unresolved imports or caller-bank placement were
withdrawn despite byte matches. Use the active overlay engine map rather than
joining unrelated functions by the same RAM address. A BIOS-library wrapper
may have a genuine no-argument contract: the SDK declares SsGetNck(void).
