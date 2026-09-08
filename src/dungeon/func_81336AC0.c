#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

extern void func_80047784(void *, u8, s32);
extern void func_800A4ACC(void *);
extern s16 D_80083228[8];
extern u8 D_801739E0[];



/* Reset state and select a direction-dependent sprite entry from one of four tables. */
void func_8016DAC0(Rec_func_800A9E70_arg0 *state, void *unused, void *sprite, Rec_D_800E3D7C *actor) {
    s32 table_kind;
    u32 direction_entry;
    u8 *direction_table;

    actor->unk_71.as_u8 = (s8) (actor->unk_71.as_u8 & 0x7F);
    table_kind = state->unk_AC;
    state->unk_9A.as_s8 = 0x18;
    state->unk_8C = 0;
    state->unk_9B.as_s8 = 0;
    if (table_kind != 1) {
        if ((s32) table_kind < 2) {
            if (table_kind == 0) {
                goto table_0;
            }
            goto done;
        } else {
            if (table_kind == 2) {
                goto table_2;
            }
            if (table_kind == 3) {
                goto table_3;
            }
            goto done;
        }
    }
    goto table_1;

table_0:
    direction_table = (u8 *)0x80170000;
    ASM_KEEP(direction_table);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    direction_table += 0x39E0;
    goto dispatch;
table_1:
    direction_table = (u8 *)0x80170000;
    ASM_KEEP(direction_table);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    direction_table += 0x39E8;
    goto dispatch;
table_2:
    direction_table = (u8 *)0x80170000;
    ASM_KEEP(direction_table);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    direction_table += 0x39F0;
    goto dispatch;
table_3:
    direction_table = (u8 *)0x80170000;
    ASM_KEEP(direction_table);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    direction_table += 0x39F8;

dispatch:
    *(volatile void **)((u8 *)sprite + 0x2C) = direction_table;
    direction_entry = (((D_80083228[0] + actor->unk_2A.as_s16 + 0x100) >> 9) & 7);
    direction_entry = direction_entry + (u32)direction_table;
    func_80047784(sprite, *(u8 *)direction_entry, 0);

done:
    func_800A4ACC(actor);
    actor->unk_6D.as_u8 = (u8) (actor->unk_6D.as_u8 - 1);
}
