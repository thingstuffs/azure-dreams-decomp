#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"
#include "records/Rec_func_80173204_arg0.h"


typedef struct S_80173204_1 {
    u8 pad_00[0xC];
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_80173204_1;   /* arg2 in func_80173204 */


typedef struct S_80173204_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173204_3;   /* counter_base in func_80173204 */

typedef struct S_80173204_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80173204_4;   /* status in func_80173204 */


typedef struct S_80173204_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80173204_6;   /* floor_base in func_80173204 */

typedef struct S_80173204_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173204_7;   /* counter in func_80173204 */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, s32);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA79C(void *, s32, void *, void *);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_80173A20(void *, s32, void *, void *);

extern void *D_800814A8;
extern s32 D_80082E80;
extern s16 D_80083228[];
extern u8 D_80083460[];
extern u8 D_80170E54;
extern u8 D_80173C9C[];
extern u8 D_80173CA4[];

/* Updates entity state, directional animation, and color fading. */
void func_80173204(Rec_func_80173204_arg0 *controller, s32 update_mode, S_80173204_1 *sprite, Rec_D_800E3D7C *entity)
{
    s32 state;
    s32 flags;
    s8 floor;
    register u8 *status ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 mode ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *counter_base;
    u8 *floor_base;
    u8 *status_page;
    register u8 *direction_table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    mode = update_mode;
    ASM_KEEP_NV(mode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (controller->unk_9B < 2U) {
        if (sprite->unk_0C.u8 < 0x33U) {
            goto dispatch;
        }
        sprite->unk_0C.s32 += -0x30303;
    } else if (sprite->unk_0C.u8 < 0x80U) {
        sprite->unk_0C.s32 += 0x30303;
    }

dispatch:
    state = controller->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    goto done;

state_0:
    entity->unk_1C.as_s32 |= 0x10000000;
    if (!(sprite->unk_14 & 0xE000)) {
        goto done;
    }
    direction_table = D_80173C9C;
    sprite->unk_2C = direction_table;
    func_80047784(
        sprite,
        direction_table[((D_80083228[0] + entity->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    counter_base = D_80083460;
    ((S_80173204_3 *)counter_base)->unk_0A =
        ((S_80173204_3 *)counter_base)->unk_0A - 1;
    goto increment_state;

state_1:
    if ((func_80042900(entity, 1) << 16) == 0) {
        direction_table = D_80173CA4;
        sprite->unk_2C = direction_table;
        func_80047784(
            sprite,
            direction_table[((D_80083228[0] + entity->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        if (sprite->unk_14 & 0x8000) {
            entity->unk_1C.as_s32 &= ~0x200;
            entity->unk_1C.as_s32 &= 0xEFFFFFFF;
            sprite->unk_0C.s32 = 0x808080;
            controller->unk_8C.as_pu8 = &D_80170E54;
            goto done;
        }
        goto increment_counter;
    }

    status_page = (u8 *)0x80080000;
    ASM_KEEP_NV(status_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    status = status_page + 0x3460;
    ASM_USE2(status_page, status);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if (((S_80173204_4 *)status)->unk_02 & 0x1000) {
        goto done;
    }
    if (entity->unk_64.as_s16 != 0) {
        if (func_800AA6B4(controller, mode, sprite, 0) != 0) {
            goto done;
        }
    }
    if (entity->unk_24.at01_u8.v == 0) {
        if (((S_80173204_4 *)status)->unk_02 & 0x2008) {
            goto done;
        }
        func_800AA79C(controller, mode, sprite, entity);
        goto done;
    }
    if ((func_800A2C34(entity) << 16) != 0) {
        goto done;
    }

    flags = entity->unk_1C.as_s32;
    if (flags & 0x100) {
        func_800AA258(controller, mode, sprite, entity);
        goto done;
    }
    if (flags & 0x80000) {
        func_800AA888(controller, mode, sprite, entity);
        func_80173A20(controller, mode, sprite, entity);
        goto done;
    }
    if (entity->unk_6D.as_s8 == 0) {
        goto done;
    }
    if ((func_800A2C34(entity) << 16) != 0) {
        if ((func_8009A180(
                 entity,
                 ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(entity);
    func_800A9A04(entity);
    if ((func_80042900(entity, 1) << 16) != 0) {
        floor_base = (u8 *)&D_80082E80;
        floor = sprite->unk_26;
        if (!((floor == ((S_80173204_6 *)floor_base)->unk_26) && (floor >= 0))) {
            if (func_8009FD40(floor_base, sprite) >= 2) {
                goto second_check;
            }
        }
        if ((func_800A6D30() & 7) == 0) {
            func_80042B68(entity, 1);
        }
    }

second_check:
    if ((func_80042900(entity, 1) << 16) != 0) {
        goto done;
    }
    direction_table = D_80173CA4;
    sprite->unk_2C = direction_table;
    func_80047784(
        sprite,
        direction_table[((D_80083228[0] + entity->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    if (sprite->unk_14 & 0x8000) {
        entity->unk_1C.as_s32 &= ~0x200;
        entity->unk_1C.as_s32 &= 0xEFFFFFFF;
        sprite->unk_0C.s32 = 0x808080;
        controller->unk_8C.as_pu8 = &D_80170E54;
        goto done;
    }
increment_counter:
    {
        register u8 *counter ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

        counter = D_80083460;
        ((S_80173204_7 *)counter)->unk_0A++;
    }

increment_state:
    controller->unk_9B++;
    goto done;

state_2:
    if (!(sprite->unk_14 & 0x8000)) {
        if (sprite->unk_0C.u8 < 0x80U) {
            goto done;
        }
    }
    {
        u8 *counter = D_80083460;
        ((S_80173204_7 *)counter)->unk_0A--;
    }
    entity->unk_1C.as_s32 &= 0xEFFFFFFF;
    sprite->unk_0C.s32 = 0x808080;
    entity->unk_1C.as_s32 &= ~0x200;
    controller->unk_8C.as_pu8 = &D_80170E54;

done:
    return;
}
