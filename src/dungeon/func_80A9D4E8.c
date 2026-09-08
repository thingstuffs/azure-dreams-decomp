#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;


extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[16];
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern u8 D_80170E7C;
extern u8 D_80174C3C[8];
extern u8 D_80174C7C[8];

extern s32 func_8003F270();
extern void func_80047784();
extern void *func_800A05A4();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern s32 func_800A94A0();
extern void func_800DA840();


typedef struct S_80172CE8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172CE8_0;   /* arg0 in func_80172CE8 */

typedef struct S_80172CE8_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_80172CE8_1_pre;   /* the 0x14 bytes before node in func_80172CE8, addressed as node[-1] */

typedef struct S_80172CE8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172CE8_2;   /* owner in func_80172CE8 */

typedef struct S_80172CE8_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80172CE8_3;   /* arg2 in func_80172CE8 */


typedef struct S_80172CE8_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172CE8_5;   /* global_state in func_80172CE8 */

/* Updates item activation, actor animation, and action cleanup. */
void func_80172CE8(void *action, void *motion, void *actor, void *object) {
    static void *const item_targets[7] = {
        &&item_8, &&item_b, &&item_e, &&item_none,
        &&item_8, &&item_b, &&item_e
    };
    u16 position[3];
    s32 is_special;
    u8 *item_slot;
    void *node;
    u8 state;

    is_special = 0;
    state = ((S_80172CE8_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)object + 0x1C)) & 0x2000) {
            u32 kind = ((*(u16 *)((u8 *)object + 0x46)) & 0x3FFF) - 1;
            if (kind >= 7) {
                goto item_none;
            }
            (void)item_targets;
            goto *(((void **)D_80170838)[kind]);
item_e:
            is_special = 1;
            goto item_e_value;
item_b:
            is_special = 1;
            goto item_b_value;
item_8:
            is_special = 1;
            goto item_8_value;
        }

        {
            s32 kind = (*(u16 *)((u8 *)object + 0x46)) & 0x3FFF;
            if (kind == 2) {
                goto item_b_value;
            }
            if (kind < 3) {
                item_slot = 0;
                if (kind == 1) {
                    goto item_8_value;
                }
                goto item_ready;
            }
            item_slot = 0;
            if (kind != 3) {
                goto item_ready;
            }
item_e_value:
            item_slot = (u8 *)object + 0xE;
            goto item_ready;
item_b_value:
            item_slot = (u8 *)object + 0xB;
            goto item_ready;
item_8_value:
            item_slot = (u8 *)object + 8;
            goto item_ready;
item_none:
            item_slot = 0;
        }

item_ready:
        if (*item_slot == 0) {
            goto no_item;
        }

        ((S_80172CE8_0 *)action)->unk_98 &= 0xFF7F;
        {
            s32 use_existing;

            use_existing = is_special;
            ASM_KEEP(use_existing);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            if (use_existing) {
                node = D_800814A8;
                (*(void * *)((u8 *)object + 0x60)) = node;
                goto copy_existing;
            }
        }

        {
            u8 *item_defs = D_8006DE24;
            u8 item_id = *item_slot;
            u8 *item_def = item_defs + item_id * 20;
            if (item_def[0x12] == 2) {
                node = (*(void * *)((u8 *)object + 0x60));
                if (node != 0) {
copy_existing:
                    {
                        register u8 *owner ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                        owner = ((S_80172CE8_1_pre *)node)[-1].unk_00;
                        (*(u8 *)((u8 *)object + 0x72)) = ((S_80172CE8_2 *)owner)->unk_24;
                        (*(u8 *)((u8 *)object + 0x73)) = ((S_80172CE8_2 *)owner)->unk_25;
                    }
                    goto object_ready;
                }
            } else {
                s32 x;
                s32 y;

                node = func_800A05A4(
                    object,
                    ((S_80172CE8_3 *)actor)->unk_24,
                    ((S_80172CE8_3 *)actor)->unk_25,
                    (*(s16 *)((u8 *)object + 0x2A)),
                    0x10);
                (*(void * volatile *)((u8 *)object + 0x60)) = node;
                ASM_KEEP(node);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                x = (*(s8 *)((u8 *)object + 0x72));
                y = (*(s8 *)((u8 *)object + 0x73));
                if (x < 0) {
                    x = -x;
                }
                if (y < 0) {
                    y = -y;
                }
                (*(s8 *)((u8 *)object + 0x72)) = x;
                (*(s8 *)((u8 *)object + 0x73)) = y;
            }
        }

object_ready:
        position[0] = ((Rec_D_800E3D7C *)motion)->unk_00.at02_u16.v;
        position[1] = ((Rec_D_800E3D7C *)motion)->unk_04.at02_u16.v;
        position[2] = ((Rec_D_800E3D7C *)motion)->unk_08.at02_u16.v;
        if (func_800A94A0(object, item_slot, is_special, (u8 *)action + 0x98)) {
            ((S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DA840(position, (s16)((*item_slot - 1) % 3));
            goto increment_state;
        }
        goto end;

no_item:
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((S_80172CE8_3 *)actor)->unk_24, ((S_80172CE8_3 *)actor)->unk_25);
        D_8008346C = 0;
        {
            u8 *active_object = (u8 *)D_800814A8;
            (*(u16 *)((u8 *)active_object + 0xA6))--;
        }
        func_800A4ACC(object);
        (*(u8 *)((u8 *)object + 0x6D))--;
        ((S_80172CE8_0 *)action)->unk_8C = &D_80170E7C;
        (*(u8 *)((u8 *)object + 0x73)) = 0;
        (*(u8 *)((u8 *)object + 0x72)) = 0;
        (*(u16 *)((u8 *)object + 0x46)) &= 0x7FFF;
        goto end;

    case 1:
        if (!(((S_80172CE8_3 *)actor)->unk_14 & 0xE000)) {
            goto end;
        }
        (*(void * *)((u8 *)actor + 0x2C)) = D_80174C7C;
        func_80047784(
            actor,
            D_80174C7C[((D_80083228 + (*(s16 *)((u8 *)object + 0x2A)) + 0x100) >> 9) & 7],
            0);
increment_state:
        ((S_80172CE8_0 *)action)->unk_9B++;
        goto end;

    case 2:
        if (func_8003F270()) {
            ((S_80172CE8_3 *)actor)->unk_14 |= 0x800;
            goto end;
        }
        ((S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
        ((S_80172CE8_0 *)action)->unk_9B++;
        /* fall through */

    case 3:
        if ((((S_80172CE8_3 *)actor)->unk_04 == 5 &&
             (((S_80172CE8_3 *)actor)->unk_14 & 0x1000)) ||
            (((S_80172CE8_3 *)actor)->unk_14 & 0xE000)) {
            ((S_80172CE8_3 *)actor)->unk_14 |= 0x800;
            ((S_80172CE8_0 *)action)->unk_96 = 0x10;
            ((S_80172CE8_0 *)action)->unk_98 |= 0x80;
        }

        {
            u16 timer = ((S_80172CE8_0 *)action)->unk_96 - 1;
            ((S_80172CE8_0 *)action)->unk_96 = timer;
            if ((s16)timer <= 0) {
                ((S_80172CE8_0 *)action)->unk_96 = 0;
                ((S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
            }
        }

        if (!(((S_80172CE8_3 *)actor)->unk_14 & 0xE000)) {
            goto end;
        }

        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((S_80172CE8_3 *)actor)->unk_24, ((S_80172CE8_3 *)actor)->unk_25);

        if (((S_80172CE8_3 *)actor)->unk_2C != D_80174C3C) {
            (*(void * *)((u8 *)actor + 0x2C)) = D_80174C3C;
            func_80047784(
                actor,
                D_80174C3C[((D_80083228 + (*(s16 *)((u8 *)object + 0x2A)) + 0x100) >> 9) & 7],
                0);
        }

        {
            u8 *global_state = D_80083460;
            if (((S_80172CE8_5 *)global_state)->unk_0C != 0) {
                goto end;
            }
            ((S_80172CE8_5 *)global_state)->unk_0A--;
        }
        ((S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
        ((S_80172CE8_0 *)action)->unk_8C = &D_80170E7C;
        func_800A4ACC(object);
        if ((*(s8 *)((u8 *)object + 0x6D)) > 0) {
            (*(u8 *)((u8 *)object + 0x6D))--;
        }
        (*(u8 *)((u8 *)object + 0x73)) = 0;
        (*(u8 *)((u8 *)object + 0x72)) = 0;
        (*(u16 *)((u8 *)object + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);
        break;

    default:
        break;
    }

end:
    return;
}
