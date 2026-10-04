#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_800287A4.h"

s32 func_80042900();                 /* extern */
s32 func_800A6D30(void); /* Retail RNG at 0x800A6D30 reads no argument registers, including $a3. */
void *func_800CB82C();

typedef struct S_8009D218_1_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_8009D218_1_pre;   /* the 0x18 bytes before entity in func_8009D218, addressed as entity[-1] */

/* extern */

s32 func_8009D218(EntityRec *entity, s32 flags, Rec_D_800287A4 *record) {
    u8 *value_ptr;

    if (!(flags & 8) && (record != NULL)) {
        if (flags & 1) {
            if (((func_80042900(entity, 0x16) << 0x10) != 0) && (record->unk_13 >= 0)) {
                func_800CB82C(((S_8009D218_1_pre *)entity)[-1].unk_00, entity, record);
                return 1;
            }
        } else if (flags & 2) {
            if ((((func_80042900(entity, 0x16) << 0x10) != 0) || ((func_80042900(entity, 0x17) << 0x10) != 0))
                && (record->unk_13 >= 0)) {
                func_800CB82C(((S_8009D218_1_pre *)entity)[-1].unk_00, entity, record);
                return 1;
            }
        } else if ((flags & 4) && (((func_80042900(entity, 0x16) << 0x10) != 0) || ((func_80042900(entity, 0x15) << 0x10)
            != 0)) && (record->unk_13 >= 0)) {
            func_800CB82C(((S_8009D218_1_pre *)entity)[-1].unk_00, entity, record);
            return 1;
        }
        {
            if (record != NULL) {
                value_ptr = (*(u8 * *)&entity->unk_50);
                if (value_ptr != NULL) {
                    if ((*value_ptr == 3) && (record->unk_13 >= 0) && (func_800A6D30() & 3)) {
                                                /* Duplicate return node #22. Try simplifying control flow for better match */
                        func_800CB82C(((S_8009D218_1_pre *)entity)[-1].unk_00, entity, record);
                        return 1;
                    }
                                        /* Duplicate return node #25. Try simplifying control flow for better match */
                    return 0;
                }
                return 0;
            }
                        /* Duplicate return node #25. Try simplifying control flow for better match */
            return 0;
        }
    }
    return 0;
}

/* MECHANISM (byte-exact @ 2.7.2, dungeon overlay)
 * 1. IMPLICIT $a0 PASSTHROUGH: the first func_80042900 site is spelled
 *    func_80042900(entity, 0x16) like the other three -- NOT m2c's one-arg
 *    func_80042900((void*)0x16). It sits in the ENTRY extended basic block, so
 *    cse still knows $a0 == entity and deletes the `move a0,s0` copy; retail's
 *    jal delay slot therefore carries `addiu a1,zero,0x16` (word 13) while the
 *    three later sites (all branch targets, cse reset) keep their `move a0,s0`.
 * 2. LEAD-22 SHAPE-C TAIL: func_8009D368 is declared VOID and the arm is spelled
 *    as two plain calls + a bare `return 1;` (never `return func_8009D368();`).
 *    Both callees are in config/sibcall_syms.dungeon.txt, so maspsx rewrites the
 *    shared-epilogue jal->j and relocates `addiu v0,zero,1` into the converted
 *    `j func_8009D368` delay slot (word 82) -- the func_800C7C24 spelling.
 * 3. ONE-SIDED ASM_MEM_BARRIER after the FIRST `return func_8009D34C();` arm
 *    defeats -O2 cross-jump merging of the two identical `j 8009d34c; nop` tail
 *    sites (words 21 and 39) so both survive; the flags&4 arm's `bgez -> 7bec`
 *    keeps the two func_800CB82C/func_8009D368 tails legitimately merged.
 */
