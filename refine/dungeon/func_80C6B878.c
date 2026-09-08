#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_80170D28(void *, s32, s32, s32, s32, s32, s32);
extern void func_80170F2C(void *, s32, s32, s32, s32, s32, s32);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170850[];
extern void *D_80170868[];
extern u8 D_80171650[];
extern u8 D_801742C8[];


typedef struct S_80173078_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80173078_0;   /* arg0 in func_80173078 */

typedef struct S_80173078_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80173078_1_pre;   /* the 0x14 bytes before active in func_80173078, addressed as active[-1] */

typedef struct S_80173078_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173078_2;   /* linked in func_80173078 */



typedef struct S_80173078_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80173078_5;   /* global in func_80173078 */

/* Updates an item action, its animation, particle effects, and completion state. */
void func_80173078(void *action, void *movement, void *sprite, void *actor)
{
    static void *const state_labels[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4
    };
    static void *const kind_labels[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    u8 *item_slot;
    s32 special;
    s32 next_state;
    u8 state;
    void *target;

    special = 0;
    state = ((S_80173078_0 *)action)->unk_9B;
    if ((u32)state >= 5) {
        goto end;
    }
    (void)state_labels;
    goto *D_80170850[state];

state_0:
    if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
        u32 kind_index;

        kind_index = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
        if (kind_index >= 7) {
            goto kind_default;
        }
        (void)kind_labels;
        goto *D_80170868[kind_index];

kind_5:
        special = 1;
        goto kind_3;
kind_6:
        special = 1;
        goto kind_2;
kind_7:
        special = 1;
        goto kind_1;
    }

    {
        s32 kind;

        kind = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
        if (kind == 2) {
            goto kind_2;
        }
        if (kind < 3) {
            item_slot = 0;
            if (kind == 1) {
                goto normal_kind_1;
            }
            goto selection_ready;
        }
        if (kind != 3) {
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
    if (*item_slot == 0) {
        goto empty_selection;
    }
    ((S_80173078_0 *)action)->unk_98 &= 0xFF7F;
    {
        s32 is_special;

        is_special = special;
        ASM_KEEP(is_special);   /* MATCH pin: retail basic-block layout depends on it */
        if (is_special != 0) {
            target = D_800814A8;
            (*(void * *)((u8 *)actor + 0x60)) = target;
            goto copy_active_coords;
        }
    }

    {
        u8 item_id;

        item_id = *item_slot;
        if (D_8006DE24[item_id * 20 + 0x12] == 2) {
            target = (*(void * *)((u8 *)actor + 0x60));
            if (target != 0) {
                register u8 *target_sprite ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

copy_active_coords:
                target_sprite = ((S_80173078_1_pre *)target)[-1].unk_00;
                (*(u8 *)((u8 *)actor + 0x72)) = ((S_80173078_2 *)target_sprite)->unk_24;
                (*(u8 *)((u8 *)actor + 0x73)) = ((S_80173078_2 *)target_sprite)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            target = func_800A05A4(
                actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
            (*(void * volatile *)((u8 *)actor + 0x60)) = target;
            ASM_KEEP(target);   /* MATCH pin: keeps a statement from moving across a call/branch */
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

invoke_item:
    if (func_800A94A0(actor, item_slot, special, (u8 *)action + 0x98) == 0) {
        goto end;
    }
    next_state = ((S_80173078_0 *)action)->unk_9B + 1;
    goto store_next_state;

empty_selection:
    ((Rec_D_800E3D7C *)movement)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)movement)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)movement)->unk_0C.as_s32 = 0;
    func_800A2B04(movement, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(actor);
    (*(u8 *)((u8 *)actor + 0x6D))--;
    ((S_80173078_0 *)action)->unk_8C = D_80171650;
    (*(u8 *)((u8 *)actor + 0x73)) = 0;
    (*(u8 *)((u8 *)actor + 0x72)) = 0;
    (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
    goto end;

state_1:
    if (func_8003F270()) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
        goto end;
    }
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
    ((S_80173078_0 *)action)->unk_9B++;
    func_800A56E0(0x703);

state_2:
    {
        u16 flags;
        s16 timer;

        flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
        if (flags & 0x8000) {
            next_state = ((S_80173078_0 *)action)->unk_9B + 1;
            ((S_80173078_0 *)action)->unk_96.u = 0;
store_next_state:
            ((S_80173078_0 *)action)->unk_9B = next_state;
            goto end;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 2 && (flags & 0x1000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = flags | 0x800;
            ((S_80173078_0 *)action)->unk_96.u = 0x16;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 < 2) {
            goto end;
        }
        timer = ((S_80173078_0 *)action)->unk_96.u - 1;
        ((S_80173078_0 *)action)->unk_96.u = timer;
        if (timer <= 0) {
            ((S_80173078_0 *)action)->unk_96.u = 0;
            ((S_80173078_0 *)action)->unk_9B++;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (((S_80173078_0 *)action)->unk_96.s < 7) {
            goto end;
        }
    }

    special = 0;
state_4:
    {
        s32 brightness;
        register s32 x ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 y ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
        s16 z;

        special++;
        brightness = (rand() & 0xFF) | 0x80;
        x = rand();
        x &= 0x7F;
        x -= 0x40;
        x = (s16)x;
        y = rand();
        y &= 0x7F;
        y -= 0x40;
        y = (s16)y;
        z = (rand() & 0x7F) - 0x40;
        func_80170D28((u8 *)action - 0x20, 0, 0x00C0C0C0,
                      brightness, x, y, z);
        if ((u16)special < 5) {
            goto state_4;
        }
    }
    goto end;

state_3:
    if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 4 &&
         (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
        ((S_80173078_0 *)action)->unk_96.u = 0x20;
        ((S_80173078_0 *)action)->unk_98 |= 0x80;
        ((S_80173078_0 *)action)->unk_9B++;
        special = 0;
        do {
            s32 brightness;

            special++;
            brightness = (rand() & 0xFF) | 0x80;
            func_80170F2C((u8 *)action - 0x20, 0, 0x00C0C0C0,
                          brightness, 0, 0, 0);
        } while ((u16)special < 20);
        ASM_KEEP(special);   /* MATCH pin: retail basic-block layout depends on it */
    }
    {
        u8 *effect_state;
        s16 timer;

        effect_state = (u8 *)&D_80083460;
        if (((S_80173078_5 *)effect_state)->unk_0C == 0) {
            ((S_80173078_0 *)action)->unk_96.u = 0;
        }
        timer = ((S_80173078_0 *)action)->unk_96.u - 1;
        ((S_80173078_0 *)action)->unk_96.u = timer;
        if (timer <= 0) {
            ((S_80173078_0 *)action)->unk_96.u = 0;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            goto end;
        }
        ((Rec_D_800E3D7C *)movement)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)movement)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)movement)->unk_0C.as_s32 = 0;
        func_800A2B04(movement, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_801742C8) {
            u8 *animation_table;
            s32 direction;

            animation_table = D_801742C8;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = animation_table;
            direction = ((D_80083228 + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
            func_80047784(sprite, animation_table[direction], 0);
        }
        if (((S_80173078_5 *)effect_state)->unk_0C != 0) {
            goto end;
        }
        ((S_80173078_5 *)effect_state)->unk_0A--;
        ((S_80173078_0 *)action)->unk_8C = D_80171650;
        func_800A4ACC(actor);
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u8 *)((u8 *)actor + 0x6D))--;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);
    }

end:
    return;
}
