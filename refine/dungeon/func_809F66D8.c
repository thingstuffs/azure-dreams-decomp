#include "common.h"



extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174218(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171400[];
extern u8 D_80175180[];
extern u8 D_80175188[];


typedef struct S_80173ED8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
} S_80173ED8_0;   /* arg0 in func_80173ED8 */

typedef struct S_80173ED8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80173ED8_1;   /* arg2 in func_80173ED8 */

typedef struct S_80173ED8_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173ED8_2;   /* counter in func_80173ED8 */

typedef struct S_80173ED8_3 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80173ED8_3;   /* arg3 in func_80173ED8 */

typedef struct S_80173ED8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80173ED8_4;   /* global in func_80173ED8 */

typedef struct S_80173ED8_5 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80173ED8_5;   /* owner in func_80173ED8 */

/* Advances entity animation states and handles pending actions. */
void func_80173ED8(void *action, void *context, void *sprite, void *entity)
{
    void *saved_action;
    register void *saved_context ASM_REG("$19");   /* MATCH pin: load-bearing for the whole function shape */
    void *saved_sprite;
    register void *dungeon_state;
    register void *saved_entity ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
    u8 state;
    register u8 *direction_frames ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    s32 direction;

    saved_action = action;
    saved_context = context;
    saved_sprite = sprite;
#define action saved_action
#define context saved_context
#define sprite saved_sprite
    ASM_KEEP_NV(saved_action);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    ASM_KEEP_NV(saved_context);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_KEEP_NV(saved_sprite);   /* MATCH pin: load-bearing for the whole function shape */

    state = ((S_80173ED8_0 *)action)->unk_9B;
    saved_entity = entity;
#define entity saved_entity
    switch (state) {
    case 0:
    {
        u8 *counter_state;

        if ((((S_80173ED8_1 *)sprite)->unk_14 & 0xE000) == 0) {
            return;
        }

        counter_state = (u8 *)&D_80083460;
#ifndef __mips__
#endif
        ((S_80173ED8_2 *)counter_state)->unk_0A--;
        direction_frames = D_80175188;
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_frames;
        direction = (D_80083228 + ((S_80173ED8_3 *)entity)->unk_2A + 0x100) >> 9;
        func_80047784(sprite, direction_frames[direction & 7], 0);
        goto increment_state;
    }

    case 1:
        if (((S_80173ED8_3 *)entity)->unk_25 != 0) {
            register u8 *counter_state;

            direction_frames = D_80175180;
            (*(void * *)((u8 *)sprite + 0x2C)) = direction_frames;
            direction = (D_80083228 + ((S_80173ED8_3 *)entity)->unk_2A + 0x100) >> 9;
            func_80047784(sprite, direction_frames[direction & 7], 0);
            (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
            counter_state = (u8 *)&D_80083460;
#ifndef __mips__
#endif
            ((S_80173ED8_2 *)counter_state)->unk_0A++;
            goto increment_state;
        }

        dungeon_state = &D_80083460;
        if (((S_80173ED8_4 *)dungeon_state)->unk_02 & 0x1000) {
            return;
        }

        if ((((S_80173ED8_3 *)entity)->unk_64 != 0) &&
            func_800AA6B4(action, context, sprite, 0)) {
            return;
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            return;
        }

        if (((S_80173ED8_3 *)entity)->unk_1C & 0x100) {
            func_800AA258(action, context, sprite, entity);
            return;
        }

        if (((S_80173ED8_3 *)entity)->unk_1C & 0x80000) {
            func_800AA888(action, context, sprite, entity);
            ((S_80173ED8_0 *)action)->unk_A8 = 0;
            func_80174218(action, context, sprite, entity);
            return;
        }

        if (((S_80173ED8_3 *)entity)->unk_6D == 0) {
            return;
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            void *owner = D_800814A8;

            if ((func_8009A180(entity,
                    (u8 *)((S_80173ED8_5 *)owner)->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A9A0C(entity);
        func_800A9A04(entity);
        if (((S_80173ED8_3 *)entity)->unk_25 == 0) {
            return;
        }

        direction_frames = D_80175180;
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_frames;
        direction = (D_80083228 + ((S_80173ED8_3 *)entity)->unk_2A + 0x100) >> 9;
        func_80047784(sprite, direction_frames[direction & 7], 0);
        ((S_80173ED8_3 *)entity)->unk_1C |= 0x40000;
        ((S_80173ED8_4 *)dungeon_state)->unk_0A++;

increment_state:
        ((S_80173ED8_0 *)action)->unk_9B++;
        return;

    case 2:
    {
        u8 *counter_state;

        if ((((S_80173ED8_1 *)sprite)->unk_14 & 0xE000) == 0) {
            return;
        }

        counter_state = (u8 *)&D_80083460;
#ifndef __mips__
#endif
        ((S_80173ED8_2 *)counter_state)->unk_0A--;
        ((S_80173ED8_3 *)entity)->unk_1C &= ~0x208;
        ((S_80173ED8_0 *)action)->unk_8C = D_80171400;
        return;
    }

    default:
        return;
    }
}
