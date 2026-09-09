#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;

typedef struct S_8008C7B4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_8008C7B4_0;   /* arg0 in func_8008C7B4 */

typedef struct S_8008C7B4_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8008C7B4_1;   /* flags in func_8008C7B4 */

typedef struct S_8008C7B4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8008C7B4_2;   /* control in func_8008C7B4 */


extern M2C_UNK func_80048A44();
extern M2C_UNK func_8009F644();
extern s32 func_800A5C70(void *arg0, s32 arg1, void *arg2, void *arg3);
extern u16 D_80013714;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_800DCFB0;
extern M2C_UNK D_800DD0B8;

/* Reset state, update control flags, and select the entity's directional sprite. */
void func_8008C7B4(void *state, s32 mode, void *sprite, void *entity) {
    void *entity_arg;
    s32 control_needed;
#ifndef NON_MATCHING
    u8 *flags;
    s32 initial_state;
#else
    M2C_UNK *flags = &D_80083160;
#endif

#ifndef NON_MATCHING
    initial_state = 0x1C;
    ASM_KEEP_NV(initial_state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_8008C7B4_0 *)state)->unk_9A = initial_state;
    flags = (u8 *)0x80080000;
#else
    ((S_8008C7B4_0 *)state)->unk_9A = 0x1C;
#endif
    ((S_8008C7B4_0 *)state)->unk_9B = 0;
    ((S_8008C7B4_0 *)state)->unk_8C = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
#ifndef NON_MATCHING
    ASM_KEEP_NV(flags);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif
    if (D_80013714 & 2) {
        goto set_control;
    }
#ifndef NON_MATCHING
    flags += 0x3160;
    ASM_KEEP_NV(flags);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif
    entity_arg = entity;
    if (!(((S_8008C7B4_1 *)flags)->unk_08 & 0x20)) {
        goto after_control;
    }
    control_needed = func_800A5C70(entity_arg, mode, sprite, entity);
    entity_arg = entity;
    if (control_needed == 0) {
        goto after_control;
    }
set_control:
    {
        M2C_UNK *control = &D_80083460;

        ((S_8008C7B4_2 *)control)->unk_02 = (u16)(((S_8008C7B4_2 *)control)->unk_02 | 0x80);
    }
    ASM_SCHED_BARRIER(); /* MATCH: keep the control arm's a0 reload after its store. */
    entity_arg = entity;
after_control:
    func_8009F644(entity_arg, 0x10, 0, 0);
    {
        u8 *direction_table;

        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x100000) {
#ifndef NON_MATCHING
            u8 *table_page;

            table_page = (u8 *)0x800E0000;
            ASM_KEEP(table_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            direction_table = table_page - 0x2F48;
#else
            direction_table = (u8 *)&D_800DD0B8;
#endif
        } else {
#ifndef NON_MATCHING
            u8 *table_page;

            ASM_SET(table_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            table_page = (u8 *)0x800E0000;
            ASM_KEEP(table_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            direction_table = table_page - 0x3050;
#else
            direction_table = &D_800DCFB0;
#endif
        }
        (*(u8 **)((u8 *)sprite + 0x2C)) = direction_table;
#ifndef NON_MATCHING
        {
            u8 *direction_entry;

            direction_entry = direction_table + (((s32)(D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7);
            func_80048A44(sprite, *direction_entry, 0, 1);
        }
#else
        func_80048A44(sprite, direction_table[((s32)(D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
#endif
    }
}
