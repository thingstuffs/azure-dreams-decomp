# Fable r94_fable_de48ec - dungeon/func_80DE48EC (5 pins; registered 2.8.0-G0 crutch, target 2.7.2-cdk-G0)
Open-ended Fable lane (owner 10-05: "one Fable agent with its freedom on something nothing, not even astra, figured
out"). Nothing staged; best pin-free text total 29 at cdk (27 = a 16-byte frame shift, 2 = one `move a0,s1` position),
work/native_lane/r94_fable_de48ec/cand/g3_novol_nogoto.c (0 pins, 0 volatiles, 0 gotos). Full RETRO.md in the lane.

## Mechanisms (pin -> deciding pass -> C)
- REG $8 `output` + padded 24-byte struct home -> reload: with all nine s-registers taken global.c spills the
  call-crossing pointer (priority 329); reload register = first never-live call-used = $t0; slot 16(sp) = frame_offset 0;
  tail `lw a0,16(sp)` = the reload at the use -> write `output` as a plain local used at both helper calls.
- REG $20 / REG $6: colours that only exist with the hard-register `output` -> fall with pin 1.
- KEEP_NV(delta_offset): sched1 birthing boost of the single-set x_delta chain beats the a0 copy at a LUID tie.
  A two-set `x_delta = base; x_delta += off` gives retail's order but raises refs (priority 5555) and recolours s0-s2
  (total 53). Open: an honest spelling with the order and not the refs.
- KEEP_NV(update_flags): (a) tail reload order - falls with pin 1; (b) global.c tie result 512 vs sprite 515 ->
  `return result;` at the fall-through return (5th ref, priority 588): byte-neutral, solved at both cells.
- 3 volatiles + 1 goto: scaffolding, free on the spill text.
- FRAME (decided negative for reload-time sources): retail's 20 unreferenced bytes at 20..39 sit ABOVE the reload slot.
  cdk can orphan a reload slot only via emit_reload_insns 6262-6306 (set redirected into the reload reg) or
  delete_output_reload 7387 (block-local, one death); local-alloc.c 472-477 takes every block-local one-death GR pseudo,
  so neither applies; caller-save needs refs > 4*calls (impossible in a 10-call function). Expand-time objects
  (unused aggregates, inlined frames, struct temps) sit BELOW the reload slot (frame grows upward) - an unused
  aggregate measured 37 (frame 88).
  Orchestrator note: the ORIGINAL pinned text's `struct { void *saved_ptr; u8 pad[20]; } state` occupies exactly
  16..39 - Fable measured "struct + store + output at both calls" = 12 (frame RIGHT, but output un-spilled into s6) and
  "struct + field read-back" = 19. If the next lane takes this row: retail may be an expand-time 24-byte local whose
  first word holds output (frame right) with output still spilled - look for what keeps output from an s-register
  with the struct present (one more call-crossing value? the store-equivalence path local-alloc.c 1008-1021).
- 7-9 sibling rows of this family carry an owner-ruled `s32 unused[2]` (expand-time there): a shared, still
  unexplained reservation - a common macro/inline helper in the original source is a candidate explanation.

## Kit corrections (applied to briefs)
- Fidelity-first prototypes: MEASURE definition prototypes one at a time. Here `s16 func_800A2B5C(...)` and
  `func_8009B4B0(u8 *, u16, u16)` from the definitions moved the frame to 56 and recoloured everything (total 67):
  the original TU declared them K&R / implicit int (`extern s32 f();`). A worse byte score is evidence, not noise.
- `u16 result = 0` that is only returned: combine's nonzero_bits folds every read to `move $2,$0`; the `move $sN,$0`
  is a dead set that still owns a callee-saved register; `return result;` vs `return 0;` is byte-neutral but changes
  result's refs/priority (a global.c order lever).
- Argument copy sinking below an address chain (sched1): the a0 copy (priority 1) beats a boosted single-set address
  pseudo only at an equal-priority LUID tie; a multi-set address pseudo gives retail's order but adds refs - check
  prio.py before trying it.
- New kit tools: lanekit/frame_trace.py (+ frame_gdb.py), lanekit/frame_slack.py.
Wanted (not built): prio.py/alloc_need.py on a PROPOSED edit (refs/live before compiling); why.py --pass sched
--trace for two texts side by side; a frame-shift bucket in diff.py --scorer --classify.
