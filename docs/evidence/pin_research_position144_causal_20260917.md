Working paths in this review snapshot refer to `work/native_lane/r43_position144`.

# Round 43 position-copy prologue diagnosis

## Result

The four-indel CDK residual is caused by the RTL position of the `held_source`
bind relative to the source-alignment computation.  It is not a register
allocation failure and it is not a different instruction selection.  The
aggregate candidate and retail contain the same 210 instructions, roles, and
frame; CDK emits the `sw s3,0xac(sp); move s3,a0` pair at words 5--6 rather
than retail words 8--9.

The exact 2.8.1 baseline exposes the source relationship that produces the
retail order: it establishes the copy destination and source, computes
`src_misalignment`, and then binds `held_source`, before branching on the
misalignment.  Its initial RTL is:

```
uid 21  copy destination = frame + 16
uid 23  high(D_8016484C)
uid 24  low_sum(D_8016484C)
uid 26  source & 3
uid 29  s3 = incoming a0
uid 32  branch on source & 3
```

GCC's reverse scheduler selects the branch, alignment result, argument load,
held-source bind, low half, high half, and destination in that order.  The
resulting forward RTL is destination, high, low, bind, argument load,
alignment test, exactly the retail prologue.  This is visible in
`raw/prologue_diag/base_281.rtl`, `base_281.sched`, and `base_281.sched2`.

The CDK aggregate form instead emits the hard-register bind before the
block-move expander's address and alignment RTL:

```
uid 21  s3 = incoming a0
uid 26  copy destination = frame + 16
uid 23  high(D_8016484C)
uid 28  low_sum(D_8016484C)
uid 30  source & 3
uid 32  branch on source & 3
```

All five ordinary operations have scheduler priority 1.  The first scheduler
therefore leaves the bind before the destination/address chain.  Reload then
inserts the `s3` save as an anti-dependency predecessor of the bind; the
second scheduler moves the save and bind together.  In `aggregate.sched2`,
save uid 547 feeds bind uid 21, while destination uid 26 and source-address
uids 23/28 are independent.  The final order is consequently save/bind,
destination, high, low.

This agrees with the repository GCC 2.7.2 scheduler source.  `sched.c` lines
38--65 describe reverse list scheduling, lines 2394--2428 rank equal-priority
instructions by dependence class and then original LUID, and lines
3884--3891 prepend each selected instruction to the forward schedule.  The
ready lists in the saved dumps exhibit those decisions directly, so no UID
identity is assumed across the 2.8.1 and CDK compilations.

## Why source reordering did not close it

Moving `held_source = source_obj` after the aggregate copy moves its initial
RTL bind to uid 56, after the whole expanded copy.  Global allocation then
records pseudo 80's preference for hard register 19, assigns `80 in 19`, and
deletes the late copy.  The incoming argument move consequently becomes
`s3 = a0` at function entry, even earlier than the original candidate.  The
evidence is in `after.rtl`, `after.lreg`, `after.greg`, and `after.sched2`.

Thus an aggregate assignment offers no source statement boundary at the
needed point.  A preceding bind has an earlier RTL position than the
expander's address/alignment chain.  A following bind is after the complete
unaligned/aligned block move and is coalesced into the incoming argument move.
The exact scalar source can put the bind between its explicit alignment value
and branch because those are separate C operations.

## Single grounded source probe

`raw/prologue_diag/probe_pointer_stage.c` tested the natural aggregate analogue
of the exact source relationship:

```c
position_dst = &positions;
position_src = &D_8016484C;
held_source = source_obj;
*position_dst = *position_src;
```

It used ordinary, semantically active pointers with no new pin, fake use,
volatile, flag, or literal address.  Initial RTL did establish destination
uid 21, high uid 23, low uid 24, and bind uid 27 in source order.  The
aggregate expander's alignment result was still later (uid 34), so the first
scheduler placed the independent bind before the address chain.  Full
verification remained 210/210, zero substitutions, four indels, and the same
reorder-only residual.  No further source probes were run.

The bounded conclusion is that the current aggregate operation removes the
four copy pins and recovers the retail block-move family, but ordinary pointer
staging does not reproduce the prologue order.  An exact aggregate solution
would need evidence for a real C construct whose lowering places the
held-source bind between the block-move alignment result and its branch.  The
available C variants do not establish such a construct; inserting a fake
dependency or volatile barrier would only encode the assembly accident.

## Provenance

- Row: `dungeon/func_813315CC`, function `func_801685CC`, target 840 bytes / 210 words.
- Recorded row SHA-256: `7960124fa5ddfd1ff2b03ef0c06e182c5c27fb76b3f564e70f48d6acf9398237`.
- Exact baseline C SHA-256: `6f115b6841623640bf0600711154404aec9db48eca4acf84a269e50da61fde88`.
- Aggregate C SHA-256: `5bdb8a6cb355006aed6afc2913cbdfa01af95df5cac015422f463207266d9354`.
- Pointer-stage probe SHA-256: `f1b2a746968c594f67e4fe7ba6fc8d0850f3a400606c416b33bcd9301452ca30`.
- CDK compiler SHA-256: `7a571911a97cef0c6b7b5d4174e89ac54f9806ce3d4b233c0f8620e3503c672b`.
- 2.8.1 compiler SHA-256: `451e6521d860fc6ff49000567d94d983125263bb0ae2149f89d95eaed34b3a02`.
- Recipes: aggregate and probe `2.7.2-cdk-G0`; exact scalar control `2.8.1-G0`; both `-O2 -G0 -Iinclude -w -da` for saved diagnostics.
- Aggregate RTL SHA-256: `e93ea211a52bcbd9efc38918c21e9f03fa16894b65c9620dcc43244c498dd49e`.
- Aggregate sched2 SHA-256: `fefdd3110dc513bc03fc99490c2772957aa17b03b34182aea10cd16fa1a375ad`.
- Exact-control RTL SHA-256: `f1ee0ca03fed660f9d565bbafa47cb9f01879900a987defac4fe19f19f1a3ac8`.
- Exact-control sched2 SHA-256: `bb4702e6346a09df495e3f4e26562059ee74978c03ad8d1f115b65137b134321`.

No production source, configuration, toolchain, or build-root file was
modified.

Root qualification: the needed bind placement describes this partial source,
which still binds held_source to s3. Removing that binding is a separate
ordinary reconstruction route; its first control has distance 12 rather than
four. The trace does not prove that every exact aggregate source needs a C
statement boundary inside expansion. Full argument-role reconstruction remains
open.
