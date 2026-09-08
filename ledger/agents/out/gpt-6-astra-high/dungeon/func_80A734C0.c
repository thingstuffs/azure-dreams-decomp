#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"



extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[16];
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern u8 D_80170E54;
extern u8 D_80174148[8];
extern u8 D_80174180[8];

extern s32 func_8003F270();
extern void func_80047784();
extern void *func_800A05A4();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern s32 func_800A94A0();
extern void func_800DA840();


typedef struct S_80172CC0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    u16 unk_A8;
} S_80172CC0_0;   /* arg0 in func_80172CC0 */

typedef struct S_80172CC0_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_80172CC0_1_pre;   /* the 0x14 bytes before node in func_80172CC0, addressed as node[-1] */

typedef struct S_80172CC0_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172CC0_2;   /* owner in func_80172CC0 */



typedef struct S_80172CC0_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172CC0_5;   /* global_state in func_80172CC0 */

/* Updates an entity's item action, animation, and completion state. */
void func_80172CC0(void *action, void *motion, void *sprite, void *actor) {
    static void *const item_targets[7] = {
        &&item_8, &&item_b, &&item_e, &&item_none,
        &&item_8, &&item_b, &&item_e
    };
    u16 pos[3];
    s32 is_special;
    register u8 *item ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *entity;
    void *node;
    u8 state;

    entity = actor;
    is_special = 0;
    state = ((S_80172CC0_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)entity + 0x1C)) & 0x2000) {
            u32 kind = ((*(u16 *)((u8 *)entity + 0x46)) & 0x3FFF) - 1;
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
            s32 kind = (*(u16 *)((u8 *)entity + 0x46)) & 0x3FFF;
            if (kind == 2) {
                goto item_b_value;
            }
            if (kind < 3) {
                item = 0;
                if (kind == 1) {
                    goto item_8_value;
                }
                goto item_ready;
            }
            item = 0;
            if (kind != 3) {
                goto item_ready;
            }
item_e_value:
            item = (u8 *)entity + 0xE;
            goto item_ready;
item_b_value:
            item = (u8 *)entity + 0xB;
            goto item_ready;
item_8_value:
            item = (u8 *)entity + 8;
            goto item_ready;
item_none:
            item = 0;
        }

item_ready:
        if (*item == 0) {
            goto no_item;
        }

        ((S_80172CC0_0 *)action)->unk_98 &= 0xFF7F;
        {
            s32 use_existing;

            use_existing = is_special;
            ASM_KEEP(use_existing);   /* MATCH pin: retail basic-block layout depends on it */
            if (use_existing) {
                node = D_800814A8;
                (*(void * *)((u8 *)entity + 0x60)) = node;
                goto copy_existing;
            }
        }

        {
            u8 *item_table = D_8006DE24;
            u8 item_id = *item;
            u8 *item_entry = item_table + item_id * 20;
            if (item_entry[0x12] == 2) {
                node = (*(void * *)((u8 *)entity + 0x60));
                if (node != 0) {
copy_existing:
                    {
                        register u8 *owner ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

                        owner = ((S_80172CC0_1_pre *)node)[-1].unk_00;
                        (*(u8 *)((u8 *)entity + 0x72)) = ((S_80172CC0_2 *)owner)->unk_24;
                        (*(u8 *)((u8 *)entity + 0x73)) = ((S_80172CC0_2 *)owner)->unk_25;
                    }
                    goto object_ready;
                }
            } else {
                s32 x;
                s32 y;

                node = func_800A05A4(
                    entity,
                    ((Rec_D_80082E80 *)sprite)->unk_24,
                    ((Rec_D_80082E80 *)sprite)->unk_25,
                    (*(s16 *)((u8 *)entity + 0x2A)),
                    0x10);
                (*(void * volatile *)((u8 *)entity + 0x60)) = node;
                ASM_KEEP(node);   /* MATCH pin: keeps a statement from moving across a call/branch */
                x = (*(s8 *)((u8 *)entity + 0x72));
                y = (*(s8 *)((u8 *)entity + 0x73));
                if (x < 0) {
                    x = -x;
                }
                if (y < 0) {
                    y = -y;
                }
                (*(s8 *)((u8 *)entity + 0x72)) = x;
                (*(s8 *)((u8 *)entity + 0x73)) = y;
            }
        }

object_ready:
        pos[0] = ((Rec_D_800E3D7C *)motion)->unk_00.at02_u16.v;
        pos[1] = ((Rec_D_800E3D7C *)motion)->unk_04.at02_u16.v;
        pos[2] = ((Rec_D_800E3D7C *)motion)->unk_08.at02_u16.v;
        if (func_800A94A0(entity, item, is_special, (u8 *)action + 0x98)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DA840(pos, (s16)((*item - 1) % 3));
            ((S_80172CC0_0 *)action)->unk_9B++;
            goto end;
        }
        goto end;

no_item:
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        D_8008346C = 0;
        {
            u8 *active_entity = (u8 *)D_800814A8;
            (*(u16 *)((u8 *)active_entity + 0xA6))--;
        }
        func_800A4ACC(entity);
        (*(u8 *)((u8 *)entity + 0x6D))--;
        ((S_80172CC0_0 *)action)->unk_8C = &D_80170E54;
        (*(u8 *)((u8 *)entity + 0x73)) = 0;
        (*(u8 *)((u8 *)entity + 0x72)) = 0;
        (*(u16 *)((u8 *)entity + 0x46)) &= 0x7FFF;
        goto end;
    case 1:
        if (func_8003F270()) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            goto end;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172CC0_0 *)action)->unk_9B++;
        /* fall through */

    case 2:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            goto end;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174180;
        func_80047784(
            sprite,
            D_80174180[((D_80083228 + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100) >> 9) & 7],
            0);
        ((S_80172CC0_0 *)action)->unk_A8 = 0x10;
        ((S_80172CC0_0 *)action)->unk_9B++;
        goto end;

    case 3:
        {
            s16 sound_timer = ((S_80172CC0_0 *)action)->unk_A8 - 1;
            ((S_80172CC0_0 *)action)->unk_A8 = sound_timer;
            if (sound_timer == 0) {
                func_800A56E0(0x610);
            }
        }

        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 12 &&
             (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((S_80172CC0_0 *)action)->unk_96 = 0x10;
            ((S_80172CC0_0 *)action)->unk_98 |= 0x80;
        }

        {
            u16 anim_timer = ((S_80172CC0_0 *)action)->unk_96 - 1;
            ((S_80172CC0_0 *)action)->unk_96 = anim_timer;
            if ((s16)anim_timer <= 0) {
                ((S_80172CC0_0 *)action)->unk_96 = 0;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            }
        }

        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            goto end;
        }

        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pv != D_80174148) {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80174148;
            func_80047784(
                sprite,
                D_80174148[((D_80083228 + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100) >> 9) & 7],
                0);
        }

        {
            u8 *global_state = D_80083460;
            if (((S_80172CC0_5 *)global_state)->unk_0C != 0) {
                goto end;
            }
            ((S_80172CC0_5 *)global_state)->unk_0A--;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172CC0_0 *)action)->unk_8C = &D_80170E54;
        func_800A4ACC(entity);
        if ((*(s8 *)((u8 *)entity + 0x6D)) > 0) {
            (*(u8 *)((u8 *)entity + 0x6D))--;
        }
        (*(u8 *)((u8 *)entity + 0x73)) = 0;
        (*(u8 *)((u8 *)entity + 0x72)) = 0;
        (*(u16 *)((u8 *)entity + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);
        break;

    default:
        break;
    }

end:
    return;
}
