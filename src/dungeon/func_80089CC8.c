#include "common.h"

typedef s32 M2C_UNK;


extern M2C_UNK func_80048A44();
extern s32 rand();
extern s32 func_800990FC();
extern s32 func_80099194();
extern M2C_UNK func_80099290();
extern s32 func_80099734();
extern M2C_UNK func_80099844();
extern M2C_UNK func_80099F04();
extern M2C_UNK func_80099F70();
extern M2C_UNK func_800A56E0();
extern M2C_UNK func_800A5720();
extern s16 func_800A6DA4();

extern s32 D_80081484;
extern s16 D_80083228;
extern s32 D_8008ACDC;
extern u8 D_8008EAC8[];
extern u8 D_800DCFB0[8];
extern u8 D_800DD0B8[8];
extern u8 D_800E0523[];
extern u8 D_800E0683[];
extern u8 D_80083460[12];
extern s32 D_800E3540;
extern s16 D_800E3DA8[2];

#line 1 "a"

typedef struct S_8008F428_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x80];
    void * unk_11C;
    u8 pad_120[0x4];
    void * unk_124;
} S_8008F428_0;   /* arg0 in func_8008F428 */

typedef struct S_8008F428_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
} S_8008F428_1;   /* arg2 in func_8008F428 */

typedef struct S_8008F428_2 {
    u8 pad_00[0x1484];
    s32 unk_1484;
} S_8008F428_2;   /* old_value_page in func_8008F428 */

typedef struct S_8008F428_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008F428_3;   /* entity in func_8008F428 */

typedef struct S_8008F428_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x30];
    void * unk_5C;
} S_8008F428_4;   /* arg3 in func_8008F428 */

typedef struct S_8008F428_5 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8008F428_5;   /* flags_base in func_8008F428 */

typedef struct S_8008F428_6 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008F428_6;   /* ((S_8008F428_0 *)arg0)->unk_124 in func_8008F428 */

/* Updates the timed effect state, entity flags, and directional animation. */
void func_8008F428(void *effect_state, void *saved_effect_id, void *animation, void *owner) {
    s32 effect_result;
    u16 ticks_left;
    u8 state;
    void *target;

    if (((S_8008F428_0 *)effect_state)->unk_124 != 0) {
        if (!(((S_8008F428_1 *)animation)->unk_14 & 0x6000)) {
            return;
        }

        state = ((S_8008F428_0 *)effect_state)->unk_9B;
        if (state == 0) {
            void *effect_target;
            s32 entity_flags;
            s32 wait_roll;

            D_800E3DA8[0] = 0;
            D_800E3DA8[1] = 0;
            entity_flags = ((S_8008F428_6 *)(((S_8008F428_0 *)effect_state)->unk_124))->unk_1C;
            effect_target = animation;
            if (entity_flags & 0x2000) {
                goto use_effect;
            }
            if (entity_flags & 0x228) {
                goto use_effect;
            }
            wait_roll = func_800A6DA4(0, 0x10);
            effect_target = animation;
            if ((s16)wait_roll < 6) {
                goto start_wait;
            }
use_effect:
            ((S_8008F428_0 *)effect_state)->unk_8C = D_8008EAC8;
            (*(u8 * *)((u8 *)effect_target + (0x2C))) = D_800DD0B8;
            func_80048A44(effect_target,
                D_800DD0B8[((D_80083228 + ((S_8008F428_4 *)owner)->unk_2A + 0x100) >> 9) & 7],
                0, 1);
            return;
        }

        if (state == 1) {
            D_800E3DA8[0] = (rand() & 0xF) - 8;
            D_800E3DA8[1] = (rand() & 0xF) - 8;
            ticks_left = ((S_8008F428_0 *)effect_state)->unk_96 - 1;
            ((S_8008F428_0 *)effect_state)->unk_96 = ticks_left;
            if ((s16)ticks_left > 0) {
                return;
            }
            func_800A56E0(0x510);
            func_80099844(((S_8008F428_0 *)effect_state)->unk_124, D_800E0523);
            {
                void *entity;
                s32 saved_global;
                u32 entity_mask;
                u32 owner_mask;
                u8 *global_page;
                register s32 flags ASM_REG("$2");

                entity_mask = 0xFFF7FFFF;
                owner_mask = 0xFFEF0000;
                global_page = (u8 *)0x80080000;
                entity = ((S_8008F428_0 *)effect_state)->unk_124;
                saved_global = ((S_8008F428_2 *)global_page)->unk_1484;
                flags = ((S_8008F428_3 *)entity)->unk_1C;
                owner_mask |= 0xFFFF;
                ((S_8008F428_2 *)global_page)->unk_1484 = 0;
                ((S_8008F428_3 *)entity)->unk_1C = flags & entity_mask;
                flags = ((S_8008F428_4 *)owner)->unk_1C;
                D_800E3540 = saved_global;
                ((S_8008F428_4 *)owner)->unk_1C = flags & owner_mask;
            }
            ((S_8008F428_0 *)effect_state)->unk_9B = ((S_8008F428_0 *)effect_state)->unk_9B + 1;
            return;
        }

        {
            u8 *flags_base = D_80083460;

            ((S_8008F428_5 *)flags_base)->unk_02 |= 0x412;
        }
        func_80099F70(((S_8008F428_4 *)owner)->unk_5C);
        func_80099F04(((S_8008F428_4 *)owner)->unk_5C);
        target = animation;
        goto reset_effect;
    }

    state = ((S_8008F428_0 *)effect_state)->unk_9B;
    if (state == 0) {
        if (((S_8008F428_1 *)animation)->unk_04 < 2) {
            return;
        }
        ((S_8008F428_1 *)animation)->unk_14 |= 0x800;
start_wait:
        ((S_8008F428_0 *)effect_state)->unk_96 = 0x10;
        ((S_8008F428_0 *)effect_state)->unk_9B = ((S_8008F428_0 *)effect_state)->unk_9B + 1;
        return;
    }

    ticks_left = ((S_8008F428_0 *)effect_state)->unk_96 - 1;
    ((S_8008F428_0 *)effect_state)->unk_96 = ticks_left;
    if ((s16)ticks_left > 0) {
        return;
    }
    ((S_8008F428_1 *)animation)->unk_14 &= 0xF7FF;
    func_800A56E0(0x506);
    {
        register s32 effect_id ASM_REG("$5");

        effect_result = func_800990FC();
        target = ((S_8008F428_0 *)effect_state)->unk_11C;
        effect_id = effect_result;
        saved_effect_id = effect_id;
        func_80099290(func_80099194(D_800E0683,
            func_80099734(target, effect_id)));
        func_800A5720(saved_effect_id);
        target = animation;
reset_effect:
        ((S_8008F428_0 *)effect_state)->unk_8C = (u8 *)&D_8008ACDC;
        (*(u8 * *)((u8 *)target + (0x2C))) = D_800DCFB0;
        func_80048A44(target,
            D_800DCFB0[((D_80083228 + ((S_8008F428_4 *)owner)->unk_2A + 0x100) >> 9) & 7],
            0, 1);
    }
}
