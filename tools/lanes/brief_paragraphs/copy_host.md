## Surviving register copy (r85_fable_copy, 2026-10-01)

Your pin holds a register copy `V = W` that gcc would otherwise fold. Two things keep
such a copy in retail: (1) the value was just STORED to or LOADED from a struct field - then the original code read the
field back, `V = p->f;`: cse does not forward it and the post-reload cse turns the reload into the `move` you see
(reload1.c reload_cse_simplify_set). Try that spelling first, it is one line. (2) the copy is tested with `if (V)` or `if (!V)` and W is a
0/1 flag: combine cannot fold a branch on a 0/1 value (it rewrites `(eq x 0)` to `(xor x 1)` / `(ne x 0)` to `x` and gives up), but only when
W is never assigned anything but 0 and 1 (split a merged flag/angle variable) AND V is a variable with a later mention in the
function (cse must keep V as the head: host the copy on the function's reused temp). If the move must sit after a store
(`sh ...; move; beq`), write that store's read-modify-write through the same temp. Never add a later mention as a dead
store, never keep the asm.

Evidence: work/native_lane/r85_fable_copy/MECHANISM.md (fixtures fx1-fx7; combine.c 3885-3920, reload1.c 7869). Exact on 818DA800 and 800A2564; the copy site went exact on 80D68308/80E8D490 (other residues remain). An ADJACENT read-back (nothing between) is forwarded by cse - it is then a colour pin, not this class.

In-place shift keeps a copy (r85_opus_bg2): for `copy = v; v *= 4;`, gcc expands `*=` through a fresh temporary and combine folds the copy away. `v <<= 2` re-sets v in place, and the copy survives (use_crosses_set_p). Try `<<=` when a KEEP holds a copy taken just before a power-of-two scale (800AFA68).
