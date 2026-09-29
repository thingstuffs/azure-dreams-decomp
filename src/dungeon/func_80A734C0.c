#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "records/Rec_func_80172CC0_arg0.h"


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


typedef struct S_80172CC0_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_80172CC0_1_pre;   /* the 0x14 bytes before node in func_80172CC0, addressed as node[-1] */

typedef struct S_80172CC0_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172CC0_2;   /* owner in func_80172CC0 */


/* Updates an entity's item action, animation, and completion state. */
void func_80172CC0(void *action, EntityRec *motion, void *sprite, void *actor) {
    u16 pos[3];
    s16 is_special;
    register u8 *item ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *entity;
    void *node;
    u8 *state;

    entity = actor;
    is_special = 0;
    state = (u8 *)(((Rec_func_80172CC0_arg0 *)action)->unk_9B.as_u8);
    switch ((u8)state) {
    case 0:
        if ((*(u32 *)((u8 *)entity + 0x1C)) & 0x2000) {
            u32 kind = ((*(u16 *)((u8 *)entity + 0x46)) & 0x3FFF) - 1;
            switch (kind) {
            case 0:
                goto item_8_value;
            case 1:
                goto item_b_value;
            case 2:
                goto item_e_value;
            case 4:
                is_special = 1;
                goto item_e_value;
            case 5:
                is_special = 1;
                goto item_b_value;
            case 6:
                is_special = 1;
                goto item_8_value;
            default:
                goto item_none;
            }
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

        ((Rec_func_80172CC0_arg0 *)action)->unk_98 &= 0xFF7F;
        {
            s32 use_existing;

            use_existing = is_special;
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

                        state = ((S_80172CC0_1_pre *)node)[-1].unk_00;
                        (*(u8 *)((u8 *)entity + 0x72)) = ((S_80172CC0_2 *)state)->unk_24;
                        (*(u8 *)((u8 *)entity + 0x73)) = ((S_80172CC0_2 *)state)->unk_25;
                    }
                    goto object_ready;
                }
            } else {
                s32 x;
                s32 y;

                x = (s32)func_800A05A4(
                    entity,
                    ((Rec_D_80082E80 *)sprite)->unk_24,
                    ((Rec_D_80082E80 *)sprite)->unk_25,
                    (*(s16 *)((u8 *)entity + 0x2A)),
                    0x10);
                (*(void * volatile *)((u8 *)entity + 0x60)) = (void *)x;
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
        pos[0] = ((u16)motion->x.w.i);
        pos[1] = ((u16)motion->y.w.i);
        pos[2] = ((u16)motion->z.w.i);
        if (func_800A94A0(entity, item, is_special, (u8 *)action + 0x98)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DA840(pos, (s16)((*item - 1) % 3));
            ((Rec_func_80172CC0_arg0 *)action)->unk_9B.as_u8++;
            return;
        }
        return;

no_item:
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        dungeonStatus.unk_0C = 0;
        {
            u8 *active_entity = (u8 *)D_800814A8;
            (*(u16 *)((u8 *)active_entity + 0xA6))--;
        }
        func_800A4ACC(entity);
        (*(u8 *)((u8 *)entity + 0x6D))--;
        ((Rec_func_80172CC0_arg0 *)action)->unk_8C.as_pv = &D_80170E54;
        (*(u8 *)((u8 *)entity + 0x73)) = 0;
        (*(u8 *)((u8 *)entity + 0x72)) = 0;
        (*(u16 *)((u8 *)entity + 0x46)) &= 0x7FFF;
        return;
    case 1:
        if (func_8003F270()) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((Rec_func_80172CC0_arg0 *)action)->unk_9B.as_u8++;
                        /* fall through */

    case 2:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174180;
        func_80047784(
            sprite,
            D_80174180[((gameWork.view.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100) >> 9) & 7],
            0);
        ((Rec_func_80172CC0_arg0 *)action)->unk_A8 = 0x10;
        ((Rec_func_80172CC0_arg0 *)action)->unk_9B.as_u8++;
        return;

    case 3:
    {
        s16 sound_timer = ((Rec_func_80172CC0_arg0 *)action)->unk_A8 - 1;
        ((Rec_func_80172CC0_arg0 *)action)->unk_A8 = sound_timer;
        if (sound_timer == 0) {
            func_800A56E0(0x610);
        }
    }

        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 12 &&
             (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((Rec_func_80172CC0_arg0 *)action)->unk_96.as_u16 = 0x10;
            ((Rec_func_80172CC0_arg0 *)action)->unk_98 |= 0x80;
        }

        {
            u16 anim_timer = ((Rec_func_80172CC0_arg0 *)action)->unk_96.as_u16 - 1;
            ((Rec_func_80172CC0_arg0 *)action)->unk_96.as_u16 = anim_timer;
            if ((s16)anim_timer <= 0) {
                ((Rec_func_80172CC0_arg0 *)action)->unk_96.as_u16 = 0;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            }
        }

        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pv != D_80174148) {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80174148;
            func_80047784(
                sprite,
                D_80174148[((gameWork.view.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100) >> 9) & 7],
                0);
        }

        {
            if (((s32)dungeonStatus.unk_0C) != 0) {
                return;
            }
            dungeonStatus.unk_0A--;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((Rec_func_80172CC0_arg0 *)action)->unk_8C.as_pv = &D_80170E54;
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

    return;
}
