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

## Opus relay r94_opus_de48ec (same day) - nothing staged; the frame question narrowed to one measurement
- Pin-free text with the RIGHT frame (80): work/native_lane/r94_opus_de48ec/cand/v1_e4clean.c - the 24-byte struct
  local stays as the saved pointer's home (`state.saved_ptr = actor - 0x20;` passed, read back at the tail), no
  volatiles, no goto, `return result;` - total 13 at cdk and 2.8.0 (Fable's 19 for this shape still had the scaffolding).
  Residue: entry `addiu a0` vs retail `addiu t0; move a0,t0`; the `move a0,s1` position (pin 4); tail load order.
- One hypothesis covers frame + entry + tail: retail = the struct text with two BLOCK-LOCAL pseudos made equivalent to
  state.saved_ptr (store-equivalence local-alloc.c 1008-1021 at entry, load-equivalence 1086-1092 at the tail) and left
  unallocated, so reload emits `addiu t0; sw t0,16(sp); move a0,t0` and `lw a0,16(sp)`. Blocker: cdk local-alloc
  (472-477) allocates every block-local pseudo with reg_n_deaths == 1; validate_equiv_mem (583) refuses an
  equivalence across a call. DECIDING MEASUREMENT (not yet run): can an honest shape make reg_n_deaths != 1 for that
  pseudo (flow.c 2156 counts a REG_UNUSED set as a death; combine.c 2116-2312 adjusts it)? Needs a gdb probe printing
  reg_n_deaths / reg_basic_block / reg_qty at local_alloc entry (frame_gdb.py has the plumbing) - kit gap.
- Partials at 2.8.0 (not exact): q1_no12.c (REG $20/$6 erased, 3 pins) total 2 = only `li a2,8` behind
  KEEP(update_flags); q7_no125.c (2 pins) total 4.
- Third unreferenced-slot path (also excluded): reload1.c 6629 output reload of a REG_UNUSED pseudo is never stored.
