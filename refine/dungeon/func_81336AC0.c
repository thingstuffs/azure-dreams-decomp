#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

extern void func_80047784(void *, u8, s32);
extern void func_800A4ACC(void *);
extern s16 D_80083228[8];
extern u8 D_801739E0[];

typedef struct S_8016DAC0_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_8016DAC0_0;   /* arg3 in func_8016DAC0 */

typedef struct S_8016DAC0_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
} S_8016DAC0_1;   /* arg0 in func_8016DAC0 */

/* Reset state and select a direction-dependent sprite entry from one of four tables. */
void func_8016DAC0(S_8016DAC0_1 *state, void *unused, void *sprite, S_8016DAC0_0 *actor) {
    s32 table_kind;
    u32 direction_entry;
    u8 *direction_table;

    actor->unk_71 = (s8) (actor->unk_71 & 0x7F);
    table_kind = state->unk_AC;
    state->unk_9A = 0x18;
    state->unk_8C = 0;
    state->unk_9B = 0;
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
    ASM_KEEP(direction_table);   /* MATCH pin: load-bearing for the whole function shape */
    direction_table += 0x39E0;
    goto dispatch;
table_1:
    direction_table = (u8 *)0x80170000;
    ASM_KEEP(direction_table);   /* MATCH pin: load-bearing for the whole function shape */
    direction_table += 0x39E8;
    goto dispatch;
table_2:
    direction_table = (u8 *)0x80170000;
    ASM_KEEP(direction_table);   /* MATCH pin: load-bearing for the whole function shape */
    direction_table += 0x39F0;
    goto dispatch;
table_3:
    direction_table = (u8 *)0x80170000;
    ASM_KEEP(direction_table);   /* MATCH pin: load-bearing for the whole function shape */
    direction_table += 0x39F8;

dispatch:
    *(volatile void **)((u8 *)sprite + 0x2C) = direction_table;
    direction_entry = (((D_80083228[0] + actor->unk_2A + 0x100) >> 9) & 7);
    direction_entry = direction_entry + (u32)direction_table;
    func_80047784(sprite, *(u8 *)direction_entry, 0);

done:
    func_800A4ACC(actor);
    actor->unk_6D = (u8) (actor->unk_6D - 1);
}
