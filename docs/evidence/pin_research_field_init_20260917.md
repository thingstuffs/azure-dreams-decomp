Working paths in this review snapshot refer to `work/native_lane/r42_field_init/`.

# Round 42 field-initializer diagnosis: `func_800BC1DC`

## Result

The lost `addiu v1,s0,32` is owned by GCC 2.8.1's `combine` pass for the
current ordinary-pointer source.  It is present as a standalone pseudo from
initial RTL through `flow`; `combine` substitutes that one-use pseudo into the
halfword address, deletes the add, and changes the store to object +34.
Scheduling then allocates the following render pointer as `v0` and the
constants as `v1`, accounting for the downstream register swap.  The swap is
a consequence of the deleted address instruction, not a separate defect.

The bounded source probes did not produce an exact ordinary-C repair.  The
best probe is 45/45 words with one addressing substitution and demonstrates
that a real second use is sufficient to preserve the payload-base instruction.
It also shows why the remaining question is source ownership rather than
register allocation or assembler behavior.

## Fixed evidence

| Input | SHA-256 | Result at `2.8.1` |
|---|---|---|
| `base.c` | `52440b6983b0b608d7e2d93340fb7e12add706986c1c5a743fb50586ddb1afaf` | Exact, 45/45; two pins. |
| `erased.c` | `9cdd2c82d98463473e51114ea9692e5db14ab2eebbb77479fcb9718838bf7cd8` | 44/45, total 11: 10 substitutions, 1 indel. |
| `candidate_typed.c` | `0d00e83f3be4ea7b3d35425ce793db7e285b0bbd3139a13ff00cf616b0c9cd69` | Screen negative; typed payload folds to `sh ...,34(s0)` and moves `lw ...,12(s0)` before it. |
| `candidate_owner.c` | `58d77e7e05fe68f62c8b3c9e36e27202d35570e851d4c8da653921f44af74959` | Full verifier: 45/45, total 1, one substitution, no indels. |

The baseline assembly SHA-256 is
`a2888c7984b39ce678899d06bb91ea04bda4e666e9c2b4b52e39c170c4e62691`.
The complete linked retail map and register roles are in `SITE_MAP.md`.

## Pass-level proof

The unpinned initial RTL contains:

```text
insn 55: pseudo 84 = pseudo 83 + 32
insn 60: mem:HI [pseudo 84 + 2] = 30
insn 63: pseudo 84 = mem:SI [pseudo 83 + 12]
```

The same two instructions survive `jump`, `cse`, `loop`, `cse2`, and `flow`.
In `scratch/dumps_erased/f.i.combine`, insn 55 is marked deleted and insn 60
becomes:

```text
mem:HI [pseudo 83 + 34] = 30
```

That form persists through `sched`.  The base hard-register declaration makes
the payload value an explicit copy into hard `v1`, which prevents this combine;
the empty keep adds another compiler-visible use.  Neither pin represents a
runtime operation.

This also corrects the inherited keep comment: erasure does not primarily
change a source basic-block layout.  It enables an address combine, removes one
instruction, then changes local allocation in the remaining straight-line
block.

Assembler ownership is excluded at this site.  Raw cc1 already differs by the
payload-base instruction and subsequent registers.  The final pipeline only
normalizes the epilogue (`addiu sp`; `jr`; `nop`) in both candidates.

## Two predicted source probes

### 1. Embedded typed payload

`candidate_typed.c` gives the object a real `Payload payload` member at +0x20,
with `lifetime` at +2, and writes through a named `Payload *`.  The two definite
callers and the sibling initialization in `func_800BC45C` support this layout:
the field at object +0x22 is consistently initialized to 30.

GCC still treats the payload address as one-use and combines it into
`sh v0,34(s0)`.  Because the typed member store has a narrower alias set, the
scheduler also moves `lw v1,12(s0)` before that store.  This is a useful
negative: adding the correct record type alone cannot own retail's standalone
address or operation order.

### 2. Genuine owner recovery from the payload

`candidate_owner.c` uses the embedded payload pointer both for its lifetime
store and to recover the enclosing object's render/data pointer.  This is real
dataflow: no asm, volatile access, fake dependency, pointer narrowing, or dead
lifetime use is present.  The second use blocks the combine and recovers words
26-28, the retail instruction count, and every register role.

Its sole mismatch is word 29:

```text
generated: lw v1,-20(v1)
retail:    lw v1,12(s0)
```

The full verifier records one substitution and no indels.  Dumps under
`scratch/dumps_owner/` show that `combine` retains the `+32` pseudo because it
feeds both the store and the `-20` load.  GCC does not reassociate
`(object + 32) - 20` back to `object + 12` at this pass sequence.

## Semantic evidence

The two definite callers are in `src/town/func_8081FA90.c` and
`src/town/func_800BECFC.c`; each calls `func_800BC1DC` twice with a two-halfword
position record, an object setup address, and a resource/setup word.  The
function allocates class 0x136, copies the two position halfwords to the vector
record, registers the object, initializes the embedded payload lifetime at
+0x22, and initializes the render record reached through object +0x0c.

`src/town/func_800BECFC.c` independently creates the same style of display
object and writes `0x1e` to `display_data + 2`, supporting the payload member
interpretation.  Neither caller nor sibling provides a second observable use
of the payload base in this routine.  The one-use interval shown in retail is
therefore real evidence that the original expression or compiler decision has
not yet been reconstructed; inventing a lifetime-only use would merely restate
the pin.

## Ownership and next experiment

| Feature | Owner | Evidence | Route |
|---|---|---|---|
| Standalone `object + 32` | C expression plus GCC `combine` acceptance | Present through `flow`, deleted in `combine`; real second use restores it. | C-rebuild handoff with the one-word owner probe as the positive control. |
| Later `v0/v1` swap | Local allocation after combine | Disappears completely when the add survives. | No separate allocation search. |
| Final `nop` | Existing assembler epilogue convention | Added after raw cc1 for both paths. | No assembler change. |

The next discriminating experiment is not another type spelling or recipe
sweep.  Instrument this recovered GCC 2.8.1's `combine.c` at the insn-55/60
attempt and record the exact acceptance predicate and cost for a minimal
microprobe containing `p = base + 32; *(short *)(p + 2) = 30; p = *(char
**)(base + 12)`.  Then compare that decision with any independently recovered,
historically compatible 2.8.1 build, if one exists.  In parallel, C rebuild can
search for an authentic expression that gives the payload address a second
semantic role while still expressing the render load from the object base;
`candidate_owner.c` is the fixed one-substitution oracle for that search.

No production source, recipe, assembler, or shared tool was changed.  No
candidate is retained for landing.
