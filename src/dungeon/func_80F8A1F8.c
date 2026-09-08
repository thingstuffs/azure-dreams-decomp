#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"



extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173D38(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171138[];
extern u8 D_80174AF4[];
extern u8 D_80174AFC[];


typedef struct S_801739F8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_801739F8_0;   /* arg0 in func_801739F8 */


typedef struct S_801739F8_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801739F8_2;   /* counter in func_801739F8 */


typedef struct S_801739F8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801739F8_4;   /* global in func_801739F8 */

typedef struct S_801739F8_5 {
    u8 pad_00[0x58];
    void * unk_58;
} S_801739F8_5;   /* owner in func_801739F8 */

/* Advances entity animation states and updates the shared activity count. */
void func_801739F8(void *controller, void *context, void *sprite, void *entity)
{
    void *saved_controller;
    register void *saved_context ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *saved_sprite;
    register void *dungeon_state;
    register void *saved_entity ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 state;
    register u8 *anim_table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 direction;

    saved_controller = controller;
    saved_context = context;
    saved_sprite = sprite;
#define controller saved_controller
#define context saved_context
#define sprite saved_sprite
    ASM_KEEP_NV(saved_controller);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(saved_context);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(saved_sprite);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    state = ((S_801739F8_0 *)controller)->unk_9B;
    saved_entity = entity;
#define entity saved_entity
    switch (state) {
    case 0:
    {
        u8 *activity_counts;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        activity_counts = (u8 *)&D_80083460;
#ifndef __mips__
#endif
        ((S_801739F8_2 *)activity_counts)->unk_0A--;
        anim_table = D_80174AFC;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        direction = (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9;
        func_80047784(sprite, anim_table[direction & 7], 0);
        goto increment_state;
    }

    case 1:
        if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v != 0) {
            register u8 *activity_counts;

            anim_table = D_80174AF4;
            (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
            direction = (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9;
            func_80047784(sprite, anim_table[direction & 7], 0);
            (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
            activity_counts = (u8 *)&D_80083460;
#ifndef __mips__
#endif
            ((S_801739F8_2 *)activity_counts)->unk_0A++;
            goto increment_state;
        }

        dungeon_state = &D_80083460;
        if (((S_801739F8_4 *)dungeon_state)->unk_02 & 0x1000) {
            return;
        }

        if ((((Rec_D_800E3D7C *)entity)->unk_64.as_s16 != 0) &&
            func_800AA6B4(controller, context, sprite, 0)) {
            return;
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            return;
        }

        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x100) {
            func_800AA258(controller, context, sprite, entity);
            return;
        }

        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x80000) {
            func_800AA888(controller, context, sprite, entity);
            ((S_801739F8_0 *)controller)->unk_A0 = 0;
            func_80173D38(controller, context, sprite, entity);
            return;
        }

        if (((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 == 0) {
            return;
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            void *owner = D_800814A8;

            if ((func_8009A180(entity,
                    (u8 *)((S_801739F8_5 *)owner)->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A9A0C(entity);
        func_800A9A04(entity);
        if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v == 0) {
            return;
        }

        anim_table = D_80174AF4;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        direction = (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9;
        func_80047784(sprite, anim_table[direction & 7], 0);
        ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 |= 0x40000;
        ((S_801739F8_4 *)dungeon_state)->unk_0A++;

increment_state:
        ((S_801739F8_0 *)controller)->unk_9B++;
        return;

    case 2:
    {
        u8 *activity_counts;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        activity_counts = (u8 *)&D_80083460;
#ifndef __mips__
#endif
        ((S_801739F8_2 *)activity_counts)->unk_0A--;
        ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 &= ~0x208;
        ((S_801739F8_0 *)controller)->unk_8C = D_80171138;
        return;
    }

    default:
        return;
    }
}
