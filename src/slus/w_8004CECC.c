/* func_8004CECC -- BYTE-EXACT, LINKABLE candidate (computed-goto idiom).
 * Config: gcc 2.7.2-cdk -O2, aspsx 2.56  (also byte-exact at cdk O2 nocse2 and
 * at the genuine SN cc1, psyq4.1 -O2).
 *
 * HSV -> RGB. `hue` is 0x600 units per revolution (0x100 per sector, 6 sectors);
 * `saturation` and `value` are 8-bit. p/q/t are the standard HSV intermediates
 * rounded by (x + 0x7F80) / 0xFF00.
 *
 * The switch dispatches through the RETAIL table jtbl_8002E5F8 (an absolute in
 * config/generated/slus_006.14.undefined_syms.txt), so this TU emits NO
 * compiler-generated jump table into .text-referenced .rodata and therefore
 * links. Idiom from src/w_800595C0.c / src/w_8005F134.c: `keepalive` exists only
 * to stop gcc deleting the case labels; it lands in .rodata but is unreferenced
 * from .text, so the linker discards it silently.
 *
 * Guards (all no-ops under -DNON_MATCHING), unchanged from the pre-conversion
 * candidate -- the forced_labels/flow.c register migration that bit
 * src/w_8005F134.c does not bite here, because nothing except `dst` ($t1) and
 * the six p/q/t/val values is live across the dispatch and those already sit in
 * call-clobbered registers:
 *   s32 val  -- retail keeps `value` in $a2 across the
 *       saturation==0 early-out and the six store arms; unpinned the allocator
 *       picks $v1 and the six `sb` arms all recolour (aligned 44).
 *   ASM_KEEP(value)                 -- pins the entry `addu $a2,$v1,$zero` into
 *       the bnez delay slot instead of letting it sink past the branch.
 *   ASM_KEEP(sector)                -- keeps the hue>>8 sector live to the end of
 *       the dispatch so the jump-table index temp cannot steal its register
 *       (removing it: aligned 16).
 */
#include "common.h"

extern void *jtbl_8002E5F8[];

u8 *func_8004CECC(u32 hue, s32 saturation, s32 value, u8 *out)
{
    u8 *dst = out;
    s32 p;
    s32 q;
    s32 t;
    s32 sat;
    u32 sector;
    s32 frac;
    register s32 val ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    static void *const keepalive[] = {
        &&L_case_0, &&L_case_1, &&L_case_2,
        &&L_case_3, &&L_case_4, &&L_case_5
    };
    (void)keepalive;

    ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    val = value;

    if ((saturation << 16) == 0) {
        dst[0] = val;
        dst[1] = val;
        dst[2] = val;
        goto done;
    }

    val = value & 0xFF;
    sat = saturation & 0xFF;
    p = (val * (0xFF00 - (sat << 8)) + 0x7F80) / 0xFF00;
    hue = hue % 0x600;
    frac = hue & 0xFF;
    q = (val * (0xFF00 - sat * frac) + 0x7F80) / 0xFF00;
    t = (val * (0xFF00 - sat * (0x100 - frac)) + 0x7F80) / 0xFF00;
    sector = hue >> 8;

    if (sector >= 6) {
        goto after_switch;
    }
    goto *jtbl_8002E5F8[sector];

L_case_0:
    dst[0] = val;
    dst[1] = t;
    dst[2] = p;
    goto after_switch;
L_case_1:
    dst[0] = q;
    dst[1] = val;
    dst[2] = p;
    goto after_switch;
L_case_2:
    dst[0] = p;
    dst[1] = val;
    dst[2] = t;
    goto after_switch;
L_case_3:
    dst[0] = p;
    dst[1] = q;
    dst[2] = val;
    goto after_switch;
L_case_4:
    dst[0] = t;
    dst[1] = p;
    dst[2] = val;
    goto after_switch;
L_case_5:
    dst[0] = val;
    dst[1] = p;
    dst[2] = q;
after_switch:
    ASM_KEEP(sector);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
done:
    return dst;
}
