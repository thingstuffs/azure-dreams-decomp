#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


typedef struct {
    u32 words[3];
} __attribute__((packed)) Packet12;

extern s32 func_8003F270(void);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_80170D28(void *, s32, s32, s32, s32, s32, s32);
extern void func_80170F2C(void *, s32, s32, s32, s32, s32, s32);

extern u8 D_80171080[];
extern s32 D_801719DC;
extern u8 D_80174634[];
extern Packet12 D_80174694;


typedef struct S_801732C4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A4;   /* overlapping accesses */
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
    u8 pad_B4[0x4];
    u16 unk_B8;
} S_801732C4_0;   /* arg0 in func_801732C4 */

typedef struct S_801732C4_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801732C4_1_pre;   /* the 0x14 bytes before active in func_801732C4, addressed as active[-1] */

typedef struct S_801732C4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801732C4_2;   /* linked in func_801732C4 */



typedef struct S_801732C4_5 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 pad_05[0x15];
    s16 unk_1A;
    s16 unk_1C;
} S_801732C4_5;   /* object_base in func_801732C4 */

typedef struct S_801732C4_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801732C4_6;   /* transform in func_801732C4 */

typedef struct S_801732C4_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801732C4_7;   /* display in func_801732C4 */

/* Advances an actor's item-use sequence, animation, and particle effects. */
void func_801732C4(void *action, EntityRec *motion, void *sprite, void *actor)
{
    u8 *item_slot;
    s32 special;
    u8 state;
    u8 next_state;
    void *target;

    special = 0;
    state = ((S_801732C4_0 *)action)->unk_9B;
    switch (state) {
    case 0:
    if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
        u32 kind_index;

        kind_index = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
        switch (kind_index) {
        case 0:
            goto kind_1;
        case 1:
            goto kind_2;
        case 2:
            goto kind_3;
        case 4:
            special = 1;
            goto kind_3;
        case 5:
            special = 1;
            goto kind_2;
        case 6:
            special = 1;
            goto kind_1;
        default:
            goto kind_default;
        }
    }

    {
        s32 action_kind;

        action_kind = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
        if (action_kind == 2) {
            goto kind_2;
        }
        if (action_kind < 3) {
            item_slot = 0;
            if (action_kind == 1) {
                goto normal_kind_1;
            }
            goto selection_ready;
        }
        if (action_kind != 3) {
            item_slot = 0;
            goto selection_ready;
        }
    }

kind_3:
    item_slot = (u8 *)actor + 0xE;
    goto selection_ready;
kind_2:
    item_slot = (u8 *)actor + 0xB;
    goto selection_ready;
normal_kind_1:
kind_1:
    item_slot = (u8 *)actor + 8;
    goto selection_ready;
kind_default:
    item_slot = 0;

selection_ready:
    if (*item_slot != 0) {
        ((S_801732C4_0 *)action)->unk_98 &= 0xFF7F;
        {
            s32 special_test;

            special_test = special;
            ASM_KEEP(special_test);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            if (special_test != 0) {
                target = D_800814A8;
                (*(void * *)((u8 *)actor + 0x60)) = target;
                {
                    u8 *item_id;

                    item_id = ((S_801732C4_1_pre *)target)[-1].unk_00;
                    (*(u8 *)((u8 *)actor + 0x72)) = ((S_801732C4_2 *)item_id)->unk_24;
                    (*(u8 *)((u8 *)actor + 0x73)) = ((S_801732C4_2 *)item_id)->unk_25;
                }
            } else {
                u8 *item_id;
                u8 *item_defs;

                item_defs = D_8006DE24;
                item_id = (u8 *)(*item_slot);
                if (item_defs[((u8)item_id) * 20 + 0x12] == 2) {
                    target = (*(void * *)((u8 *)actor + 0x60));
                    if (target != 0) {
                        item_id = ((S_801732C4_1_pre *)target)[-1].unk_00;
                        (*(u8 *)((u8 *)actor + 0x72)) = ((S_801732C4_2 *)item_id)->unk_24;
                        (*(u8 *)((u8 *)actor + 0x73)) = ((S_801732C4_2 *)item_id)->unk_25;
                    }
                } else {
                    s32 dx;
                    s32 dy;

                    dx = (s32)func_800A05A4(
                        actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                        (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
                    (*(void * volatile *)((u8 *)actor + 0x60)) = (void *)dx;
                    dx = (*(s8 *)((u8 *)actor + 0x72));
                    dy = (*(s8 *)((u8 *)actor + 0x73));
                    if (dx < 0) {
                        dx = -dx;
                    }
                    if (dy < 0) {
                        dy = -dy;
                    }
                    (*(u8 *)((u8 *)actor + 0x72)) = dx;
                    (*(u8 *)((u8 *)actor + 0x73)) = dy;
                }
            }
        }

        if (func_800A94A0(actor, item_slot, special, (u8 *)action + 0x98) == 0) {
            return;
        }
        next_state = ((S_801732C4_0 *)action)->unk_9B;
        next_state++;
        ((S_801732C4_0 *)action)->unk_9B = next_state;
        return;
    }
    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    dungeonStatus.unk_0C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(actor);
    (*(u8 *)((u8 *)actor + 0x6D))--;
    ((S_801732C4_0 *)action)->unk_8C = &D_801719DC;
    (*(u8 *)((u8 *)actor + 0x73)) = 0;
    (*(u8 *)((u8 *)actor + 0x72)) = 0;
    (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
    return;

    case 1:
    if (func_8003F270()) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
        return;
    }
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
    ((S_801732C4_0 *)action)->unk_9B++;
    func_800A56E0(0x703);

    case 2:
    {
        u16 flags;
        s16 timer;

        flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
        if (flags & 0x8000) {
            next_state = ((S_801732C4_0 *)action)->unk_9B;
            ((S_801732C4_0 *)action)->unk_96.u = 0;
            next_state++;
            ((S_801732C4_0 *)action)->unk_9B = next_state;
            return;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 2 && (flags & 0x1000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = flags | 0x800;
            ((S_801732C4_0 *)action)->unk_96.u = 0x16;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 < 2) {
            return;
        }
        timer = ((S_801732C4_0 *)action)->unk_96.u - 1;
        ((S_801732C4_0 *)action)->unk_96.u = timer;
        if (timer <= 0) {
            ((S_801732C4_0 *)action)->unk_96.u = 0;
            ((S_801732C4_0 *)action)->unk_9B++;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (((S_801732C4_0 *)action)->unk_96.s >= 7) {
            special = 0;
            do {
                s32 brightness;
                register s32 offset_x;
                register s32 offset_y;
                s16 offset_z;

                special++;
                brightness = (func_80069EF8() & 0xFF) | 0x80;
                offset_x = (s16)((func_80069EF8() & 0x7F) - 0x40);
                offset_y = (s16)((func_80069EF8() & 0x7F) - 0x40);
                offset_z = (func_80069EF8() & 0x7F) - 0x40;
                func_80170D28((u8 *)action - 0x20, 0, 0x00C0C0C0,
                              brightness, offset_x, offset_y, offset_z);
            } while ((u16)special < 5);
        }
    }

    {
        void *object;
        u8 *object_base;
        void *transform;
        void *display;
        u16 timer;
        u16 flags;

        timer = ((S_801732C4_0 *)action)->unk_96.u;
        if (!(timer & 1) || (s16)timer < 0x13) {
            return;
        }
        object = func_8003FC64(0x212);
        if (object == 0) {
            return;
        }
        object_base = (u8 *)object + 0x20;
        ((S_801732C4_5 *)object_base)->unk_1A = 0x19;
        ((S_801732C4_5 *)object_base)->unk_1C = 0x19;
        (*(void * *)((u8 *)object + 0x10)) = D_80171080;
        func_8004491C(object, func_80045340);
        transform = (*(void * *)((u8 *)object + 8));
        ((S_801732C4_6 *)transform)->unk_02 = ((u16)motion->x.w.i);
        ((S_801732C4_6 *)transform)->unk_06 = ((u16)motion->y.w.i);
        ((S_801732C4_6 *)transform)->unk_0A = ((u16)motion->z.w.i) - 0x60;
        display = (*(void * *)((u8 *)object + 0xC));
        (*(Packet12 *)((u8 *)object + 0x48)) = D_80174694;
        ((S_801732C4_7 *)display)->unk_08 = (u8 *)object + 0x48;
        ((S_801732C4_7 *)display)->unk_10 = 0x40;
        ((S_801732C4_7 *)display)->unk_1E = 0x32C8;
        ((S_801732C4_7 *)display)->unk_1C = 0x32C8;
        ((S_801732C4_7 *)display)->unk_06 = 0x64;
        ((S_801732C4_7 *)display)->unk_0C = 0;
        flags = ((S_801732C4_7 *)display)->unk_14;
        ((S_801732C4_7 *)display)->unk_14 = flags | 0xC;
        ((S_801732C4_5 *)object_base)->unk_04 = 0x80;
        ((S_801732C4_5 *)object_base)->unk_03 = 0x80;
        ((S_801732C4_5 *)object_base)->unk_02 = 0x80;
    }
    return;

    case 3:
    if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 5 &&
         (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
        ((S_801732C4_0 *)action)->unk_96.u = 0x14;
        ((S_801732C4_0 *)action)->unk_98 |= 0x80;
        ((S_801732C4_0 *)action)->unk_9B++;
        special = 0;
do {
        {
            s32 brightness;

            special++;
            brightness = (func_80069EF8() & 0xFF) | 0x80;
            func_80170F2C((u8 *)action - 0x20, 0, 0x00C0C0C0,
                          brightness, 0, 0, 0);
        }
        if ((u16)special >= 20) {
            return;
        }
        } while (1);
    }
    return;

    case 4:
    {
        s16 timer;

        if (((s32)dungeonStatus.unk_0C) == 0) {
            ((S_801732C4_0 *)action)->unk_96.u = 0;
        }
        timer = ((S_801732C4_0 *)action)->unk_96.u - 1;
        ((S_801732C4_0 *)action)->unk_96.u = timer;
        if (timer > 0 && !(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        ((S_801732C4_0 *)action)->unk_96.u = 0;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        next_state = ((S_801732C4_0 *)action)->unk_9B;
        next_state++;
        ((S_801732C4_0 *)action)->unk_9B = next_state;
        return;
    }

    case 5:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_80174634) {
        u8 *anim_table;
        s32 direction;
        s32 saved_a4;

        anim_table = D_80174634;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
        direction = ((gameWork.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
        func_80047784(sprite, anim_table[direction], 2);
        ((Rec_D_80082E80 *)sprite)->unk_05.as_u8 = 1;
        saved_a4 = ((S_801732C4_0 *)action)->unk_A4.at00.v;
        ((S_801732C4_0 *)action)->unk_A4.at02.v = 0;
        ((S_801732C4_0 *)action)->unk_B8 = 0;
        ((S_801732C4_0 *)action)->unk_AC = 0;
        ((S_801732C4_0 *)action)->unk_B0 = 0;
        ((S_801732C4_0 *)action)->unk_A8 = saved_a4;
    }
    {

        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }
        dungeonStatus.unk_0A--;
        ((S_801732C4_0 *)action)->unk_8C = &D_801719DC;
        func_800A4ACC(actor);
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u8 *)((u8 *)actor + 0x6D))--;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);
    }

    return;
    }
}
