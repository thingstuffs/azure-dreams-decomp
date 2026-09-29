## Family: hand-written byte sign-extension held by keeps (round 80, r79_opus_f1 slus/w_8003DBD0 4 -> 0)

**APPEARS** a byte loaded into an int local (`s32 v = U8_AT(p, n);`), sign-extended by hand (`(v << 24) >> 24`),
with an `ASM_KEEP_DEP_NV` / `ASM_KEEP` beside it; retail has `lbu` + `sll 24` + `sra 24`, and erasing the keep gives
`lb` (the compiler folds the shifts into a signed load) or drops a copy.

**MECHANISM** gcc 2.7.2's mips.md `extendqisi2` expander (`force_not_mem`) loads the byte into a QImode pseudo and
shifts a paradoxical subreg. When the result feeds a HImode (s16) store, the arithmetic is narrowed to HImode, the
expansion's destination is a subreg and no REG_EQUAL `(sign_extend (mem))` note is attached - so neither cse nor
combine can turn it into `lb`, and retail's `lbu/sll/sra` survives. The original simply read the field as SIGNED
inside the s16 expression.

**RESOLVES** read the byte as `s8` in the expression and drop the keep and the temporaries:

    -        s32 point_x = U8_AT(point, 2);
    -        saved_offset_x = U16_AT(scratch, 0x108);
    -        ASM_KEEP_DEP_NV(point_x, saved_offset_x);
    -        S16_AT(scratch, 0x70) = -((point_x << 24) >> 24) - saved_offset_x;
    +        S16_AT(scratch, 0x70) = -S8_AT(point, 2) - U16_AT(scratch, 0x108);

All six spellings tried on the exemplar were exact. On a row where the destination is NOT a 16-bit store the
mechanism differs (an s32 destination keeps the REG_EQUAL note, so `lb` appears): measure first, and look for the
narrowing the original had (an s16 local, an s16 field, a `(s16)` cast of the whole expression).

**Round-80 family results (r79_opus_fam1, 17 pins on 3 rows):** an s32 byte local with `<<24>>24` + keep feeding
s16 stores -> `s16 v = S8_AT(p, n)` (extendqihi2 into an HImode local: combine never forms `lb`); a negation after an
if/else join held by a keep -> `x = -(a)` / `x = -(b)` in both arms (jump2 cross-jumps them back); a signed byte is
doubled with `<< 1`, never `* 2`; a squared extended byte -> `s8 t; s16 copy = t; s32 d = t * copy` (two users stop
the fold); field read-modify-write (`F += G; F <<= 8`) makes cse emit the copy retail keeps. On 2.8.1 cells any s32
use of the byte gives `lb` - the family does not carry over there.
