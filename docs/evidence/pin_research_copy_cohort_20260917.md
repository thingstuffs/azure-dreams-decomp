Working paths in this review snapshot refer to `work/native_lane/r42_initializers/`.

# Round 42 initializer and fixed-copy cohort

This is a bounded, read-only source audit at baseline `cfbab7cd`, before the
round-42 Record68 landing. Its source hashes and references to the pinned
`800B0994` describe that baseline. It inspected the five named pinned
allocator initializers, the two now-pin-free 88-byte references, their visible
callback installers, and registered pinned `src/town` rows with recognizable
fixed-copy source shapes. It did not compile candidates, edit production files,
or establish a population-wide absence claim.

## What transfers from the two references

`town/func_8080E838` and `town/func_8081DD70` each allocate a kind-`0x136`
object, copy exactly 88 bytes from the first argument to `object + 0x20`, copy
exactly 24 bytes from the second argument through `object->initial`, install a
callback at object offset `0x10`, run the family initialization helper, and pass
the payload at `+8`, the initial record, and a setup table to a three-argument
helper. The first uses `func_800373DC`, `func_8003BC18`, callback
`func_80529594`, and `func_8023FA58`; the second uses `func_8003FC64`,
`func_8004491C`, callback `func_800206D0`, and `func_8008F074`.

Those links are useful source evidence. The allocator kind alone is not an
eligibility rule: most `0x136` occurrences initialize fields in place and have
no source/destination record copy.

## Named allocator rows

### Sole strong reconstruction handoff: `town/func_8080E59C`

This row has one real fixed contiguous copy. After initializing the six-word
state record at `object->unk_08`, source lines 153-166 load offsets
`0x00,0x04,0x08,0x0c,0x10,0x14` and store them contiguously to object offsets
`0x78..0x8f`: **24 bytes**. The otherwise unused `Copy24` declaration supports
that extent. `ASM_KEEP(object_state)`, the `$t0` binding on the fourth word, and
`ASM_KEEP(first_word)` surround this copy.

The family links are concrete: it uses the same `func_800373DC` allocator,
`func_8003BC18` initializer, `func_8023FA58` setup family, and
`D_8052643C` table as `8080E838`. It installs `D_80529AC4` for the first object
and `D_8052AE20` for the three child objects. The first helper call receives
`object + 0x2c`, the copied record at `object + 0x78`, `D_805300DC`, and the
third copied word; child calls use `object + 0x28`, the live state record,
`D_805300C4`, and the render record.

It is not eligible for the mechanical copy rewrite. The third source word is
read through `object_state->unk_08.v`, explicitly volatile, while the other five
are ordinary reads. A plain `Copy24` assignment would erase that access
contract. The row is therefore a semantic/allocator reconstruction handoff,
already owned by `allocator_explain`, and no second automatic target is selected
from the allocator inventory.

### Non-copy rows

- `town/func_808216B0` is an update callback, not an input-record initializer.
  `town/func_8081FCE0` allocates its parent objects and stores callback
  `D_80023EB0` at offset `0x10`. On state zero the callback allocates two
  `0x136` children, assigns their callback/data pointer, calls
  `func_8004491C`, and initializes render fields in place. There is no fixed
  source/destination copy. Its six pins own child/index allocation and two
  scheduling sites.
- `town/func_80813368` is the corresponding scene-family update callback.
  `town/func_808119EC` installs `D_8052DF68` at object offset `0x10`. It has the
  same two-child state-zero shape as `808216B0`, with `func_800373DC` and
  `func_8003BC18`, but again initializes each field in place. Its three pins are
  in later motion arithmetic, not a copy.
- `town/func_8081FCE0` builds several parent/child objects and installs
  `D_80023EB0`; its `0x136` object receives scalar primitive/render stores and a
  `func_8008F104` call. It has no incoming record or copy extent.
- `town/func_8081B4A4` is a larger multi-object builder. Its only copy-like
  loop reads two bytes from `D_80020144` and fans each byte out to two distinct
  destinations. That is neither one contiguous source-to-destination record nor
  a four-load/four-store copy. Its four pins govern parent/final-state and
  scheduling lifetimes.

These exclusions do not say the functions cannot be reconstructed. They say the
88-byte aggregate-copy mechanism has no source-level trigger in them.

## Mechanical fixed-copy boundary

The smallest safe first-pass pattern is a single straight-line loop with:

1. a nonvolatile source pointer, destination pointer, and constant end derived
   from the same source base;
2. four word loads followed by four stores for each 16-byte chunk;
3. constant pointer advances and a fixed zero-to-three-word scalar tail;
4. no call, conditional, transform, second source object, or other side effect
   in the copied region; and
5. only an attached `ASM_KEEP`/`ASM_SCHED_BARRIER`/`ASM_MEM_BARRIER` as the pin
   being explained. Unrelated text and pins must remain unchanged.

The candidate may replace exactly that region with one typed record assignment,
but still needs non-overlap/alignment review and byte verification. Existing
aggregate assignments and pin-free rows are controls, not candidates.

The bounded current-source scan found **no new registered pinned TOWN row beyond
the round-40 five** that satisfies all five conditions. Three pin-free controls
show the source family without claiming eligibility: `808834DC` copies
3x16+4 = 52 bytes, `8080BFFC` copies 3x16 = 48 bytes, and `800A29F0`
copies 5x16+4 = 84 bytes. The current pinned `800B0994` remains the canonical
known example: four scalar loads, four stores, `ASM_KEEP(src)`, and a 68-byte
extent, but it belongs to the prior round-40 set.

## Mechanistic negative control: `town/func_800B6A28`

This row looks superficially suitable because one arm copies three 16-byte
chunks with four loads followed by four stores. It must be refused by the
mechanical recognizer:

- a runtime alignment test selects between that scalar loop and an existing
  packed 16-byte assignment loop;
- the final 12 bytes come from a different global, not the end of the 48-byte
  source block;
- the destination is contiguous but the two source regions are disjoint; and
- all five copy-related pins are hard-register bindings, with no attached
  keep or barrier for this first-pass rule.

It is a useful negative because a broad “four loads/four stores” matcher would
silently change control flow and source-object semantics here. This bounded
audit therefore promotes no new automatic candidate rather than padding the
cohort with a structurally ineligible row.
