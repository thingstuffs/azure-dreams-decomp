#include "common.h"

typedef struct S_801717D0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    s16 unk_46;
    u8 pad_48[0x18];
    s32 unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_801717D0_0;   /* self in func_801717D0 */

typedef struct S_801717D0_1 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_801717D0_1;   /* D_800E3D7C in func_801717D0 */

typedef struct S_801717D0_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801717D0_2;   /* counter_base in func_801717D0 */

typedef struct S_801717D0_3 {
    u8 pad_00[0x98];
    union { s32 s32; u16 u16; } unk_98;   /* accessed as both */
    u8 pad_9C[0xA];
    u16 unk_A6;
} S_801717D0_3;   /* player in func_801717D0 */

typedef struct S_801717D0_4 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
} S_801717D0_4;   /* arg0 in func_801717D0 */

typedef struct S_801717D0_5 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 unk_13;
} S_801717D0_5;   /* entry in func_801717D0 */

typedef struct S_801717D0_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801717D0_6;   /* call_arg2 in func_801717D0 */



extern u8 D_8006DE24[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
extern u8 *D_800E3D7C;

extern void func_80047784(void *, u8, s32);
extern s32 func_800A05A4(void *, u8, u8, s16, u8);
extern s32 func_800A2B5C(void *);
extern void func_800A4ACC(void *);
extern s32 func_800A6D30(void);
extern void func_800C77D0(void *, s32, s32, s32);

/* Prepares an entity action, updates its directional animation, and advances the counter. */
void func_801717D0(u8 *entity, s32 action_param, u8 *sprite, u8 *direction_frames, s32 fallback_state)
{
    register s32 saved_param ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 *action_sprite ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 *frame_table ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *self;
    u8 *player;
    u8 *action_slot;
    u8 *counter_base;
    u8 *action_table;
    u8 *action_entry;
    volatile u16 *action_flags;
    u16 counter;
    s32 special_action;
    s32 selection_index;
    s32 entry_index;
    register s32 state_flags ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

    saved_param = action_param;
    action_sprite = sprite;
    frame_table = direction_frames;
    special_action = 0;
    self = entity;
    ASM_KEEP(saved_param);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(action_sprite);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_801717D0_0 *)self)->unk_71 &= 0x7F;

    if (((S_801717D0_0 *)self)->unk_1C & 0x2000) {
        if ((((S_801717D0_0 *)self)->unk_46 & 0x3FFF) >= 5) {
            special_action = 1;
            if (((S_801717D0_1 *)D_800E3D7C)->unk_A6 == 2) {
                counter_base = (u8 *)&D_80083460;
                ASM_KEEP(counter_base);   /* MATCH pin: retail register colouring depends on it */
                counter = ((S_801717D0_2 *)counter_base)->unk_0A;
                counter--;
                ((S_801717D0_2 *)counter_base)->unk_0A = counter;
            }

            player = D_800E3D7C;
            if ((((S_801717D0_3 *)player)->unk_98.s32 & 0x3000) == 0x2000 &&
                ((S_801717D0_3 *)player)->unk_A6 != special_action) {
                ((S_801717D0_3 *)player)->unk_A6 = special_action;
                ((S_801717D0_3 *)player)->unk_98.u16 |= 0x1000;
                counter_base = (u8 *)&D_80083460;
                ((S_801717D0_2 *)counter_base)->unk_0A++;
                goto process;
            }

            func_800A4ACC(self);
            ((S_801717D0_0 *)self)->unk_6D--;
            ((S_801717D0_4 *)entity)->unk_8C = fallback_state;
            goto done;
        }
    }

    if (D_80083462 & 8) {
        goto done;
    }
    if ((func_800A2B5C(self) << 16) != 0) {
        goto done;
    }

    func_800C77D0(self - 0x20, saved_param, 8, 0x300);
    if ((func_800A2B5C(self) << 16) != 0) {
        goto done;
    }

process:
    if (special_action == 0) {
        if (((S_801717D0_0 *)self)->unk_1C & 0x400) {
            state_flags = ((S_801717D0_0 *)self)->unk_14;
            if (state_flags >= 0) {
                state_flags |= 0x80000000;
                ((S_801717D0_0 *)self)->unk_14 = state_flags;
                ((S_801717D0_0 *)self)->unk_2A.u += (func_800A6D30() & 7) << 9;
            }
        }

        action_flags = (volatile u16 *)(self + 0x46);
        if (!(*action_flags & 0x4000)) {
            selection_index = *action_flags & 0x3FFF;
            entry_index = selection_index - 1;
            action_table = D_8006DE24;
            action_slot = self;
            action_slot += entry_index * 3;
            entry_index = action_slot[8];
            action_entry = action_table + entry_index * 20;
            if (((S_801717D0_5 *)action_entry)->unk_12 == 2) {
                ((S_801717D0_0 *)self)->unk_60 =
                    func_800A05A4(self,
                                  ((S_801717D0_6 *)action_sprite)->unk_24,
                                  ((S_801717D0_6 *)action_sprite)->unk_25,
                                  ((S_801717D0_0 *)self)->unk_2A.s,
                                  ((S_801717D0_5 *)action_entry)->unk_13);
            }
        }
    }

    ((S_801717D0_4 *)entity)->unk_9A = 0x12;
    ((S_801717D0_4 *)entity)->unk_9B = 0;
    ((S_801717D0_4 *)entity)->unk_8C = 0;

    if (frame_table != 0) {
        (*(u8 * *)((u8 *)action_sprite + 0x2C)) = frame_table;
        selection_index = (D_80083228 + ((S_801717D0_0 *)self)->unk_2A.s + 0x100) >> 9;
        func_80047784(action_sprite, frame_table[selection_index & 7], 0);
        ASM_KEEP(frame_table);   /* MATCH pin: keeps a statement from moving across a call/branch */
    }

    counter_base = (u8 *)&D_80083460;
    ASM_KEEP(counter_base);   /* MATCH pin: retail register colouring depends on it */
    ((S_801717D0_2 *)counter_base)->unk_0A++;

done:
    return;
}
