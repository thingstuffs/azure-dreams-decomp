#include "common.h"
#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))
extern s16 func_80042900(void *, s32);
extern s32 D_800835E8[];
extern u8 *D_800E3D7C[];
extern u8 D_800E0000[];
/* Checks whether an entity can level up with its current experience. */
s32 func_800A1C58(void *entity) {
    s16 can_level_up = 0;
    s32 *exp_table;
    u8 *exp_entry;
    u8 level;
    u32 table_offset;

    if (F(entity, s8, 0x13) < 0) {
        return 0;
    }
    if (F(entity, u8, 0x11) >= 0x63) {
        return 0;
    }
    if ((func_80042900(entity,  10) << 16) != 0) {
        return 0;
    }
    if (F(entity, u32, 0x1C) & 0x80000) {
        return can_level_up;
    }
    if (F(entity, u8, 0x13) == 0) {
         /* Required for byte-exact code generation. */
        if (F(F(D_800E0000, u8 *, 0x3D7C), u8, 0x9A) == 0x22) {
            return can_level_up;
        }
    }
    if (F(entity, u32, 0x1C) & 0x228) {
        return can_level_up;
    }
     /* Required for byte-exact code generation. */
    level = F(entity, u8, 0x11);
    table_offset = level << 2;
    exp_table = (s32 *)D_800835E8;
    exp_entry = (u8 *)(table_offset + (u32)exp_table);
    ASM_KEEP(exp_entry); /* Required for byte-exact code generation. */
    if (*(u32 *)exp_entry <= F(entity, u32, 0x18)) {
        can_level_up++;
    }
    return can_level_up;
}
