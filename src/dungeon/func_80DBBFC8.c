#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

extern s32 func_8003F270(void);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern u8 D_80170FD8[];
extern u8 D_80171284[];
extern u8 D_80171E20[];
extern u8 D_801753BC[];
extern u8 D_80175424[12];


typedef struct S_801737C8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801737C8_0;   /* arg0 in func_801737C8 */

typedef struct S_801737C8_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801737C8_1_pre;   /* the 0x14 bytes before active in func_801737C8, addressed as active[-1] */

typedef struct S_801737C8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801737C8_2;   /* linked in func_801737C8 */



typedef struct S_801737C8_5 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_801737C8_5;   /* child in func_801737C8 */

typedef struct S_801737C8_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801737C8_6;   /* coords in func_801737C8 */

typedef struct S_801737C8_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801737C8_7;   /* global in func_801737C8 */

/* Process item use, spawn its visual effect, and finish the action when ready. */
void func_801737C8(void *controller, void *motion, void *actor, void *object)
{
    static void *const kind_labels[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    u8 *item_slot;
    s16 use_player;
    u8 state;
    void *target;

    use_player = 0;
    state = ((S_801737C8_0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        goto state_0;
    case 1:
        goto state_1;
    case 2:
        goto state_2;
    case 3:
        goto state_3;
    default:
        goto end;
    }

state_0:
    if ((*(u32 *)((u8 *)object + 0x1C)) & 0x2000) {
        u32 kind_index;

        kind_index = ((*(u16 *)((u8 *)object + 0x46)) & 0x3FFF) - 1;
        if (kind_index >= 7) {
            goto kind_default;
        }
        (void)kind_labels;
        goto *(*(void **)((u8 *)D_80170838 + kind_index * 4));

kind_5:
        use_player = 1;
        goto kind_3;
kind_6:
        use_player = 1;
        goto kind_2;
kind_7:
        use_player = 1;
        goto kind_1;
    }

    {
        s32 item_kind;

        item_kind = (*(u16 *)((u8 *)object + 0x46)) & 0x3FFF;
        if (item_kind == 2) {
            goto kind_2;
        }
        if (item_kind < 3) {
            item_slot = 0;
            if (item_kind == 1) {
                goto normal_kind_1;
            }
            goto selection_ready;
        }
        if (item_kind != 3) {
            item_slot = 0;
            goto selection_ready;
        }
    }

kind_3:
    item_slot = (u8 *)object + 0xE;
    goto selection_ready;
kind_2:
    item_slot = (u8 *)object + 0xB;
    goto selection_ready;
normal_kind_1:
kind_1:
    item_slot = (u8 *)object + 8;
    goto selection_ready;
kind_default:
    item_slot = 0;

selection_ready:
    if (*item_slot == 0) {
        goto empty_selection;
    }
    ((S_801737C8_0 *)controller)->unk_98 &= 0xFF7F;
    {
        s32 target_player;

        target_player = use_player;
        if (target_player != 0) {
            target = D_800814A8;
            (*(void * *)((u8 *)object + 0x60)) = target;
            goto copy_active_coords;
        }
    }

    {
        u8 *item_table;
        u8 item_id;
        u8 *item_data;

        item_table = D_8006DE24;
        item_id = *item_slot;
        item_data = item_table + item_id * 20;
        if (item_data[0x12] == 2) {
            target = (*(void * *)((u8 *)object + 0x60));
            if (target != 0) {
                register u8 *target_actor ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

copy_active_coords:
                target_actor = ((S_801737C8_1_pre *)target)[-1].unk_00;
                (*(u8 *)((u8 *)object + 0x72)) = ((S_801737C8_2 *)target_actor)->unk_24;
                (*(u8 *)((u8 *)object + 0x73)) = ((S_801737C8_2 *)target_actor)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            target = func_800A05A4(
                object, ((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25,
                (*(s16 *)((u8 *)object + 0x2A)), 0x10);
            (*(void * volatile *)((u8 *)object + 0x60)) = target;
            ASM_KEEP(target);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            dx = (*(s8 *)((u8 *)object + 0x72));
            dy = (*(s8 *)((u8 *)object + 0x73));
            if (dx < 0) {
                dx = -dx;
            }
            if (dy < 0) {
                dy = -dy;
            }
            (*(u8 *)((u8 *)object + 0x72)) = dx;
            (*(u8 *)((u8 *)object + 0x73)) = dy;
        }
    }

invoke_item:
    if (func_800A94A0(object, item_slot, use_player, (u8 *)controller + 0x98) == 0) {
        goto end;
    }
    ((S_801737C8_0 *)controller)->unk_9B = ((S_801737C8_0 *)controller)->unk_9B + 1;
    goto end;

empty_selection:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(object);
    (*(u8 *)((u8 *)object + 0x6D))--;
    ((S_801737C8_0 *)controller)->unk_8C = D_80171E20;
    (*(u8 *)((u8 *)object + 0x73)) = 0;
    (*(u8 *)((u8 *)object + 0x72)) = 0;
    (*(u16 *)((u8 *)object + 0x46)) &= 0x7FFF;
    goto end;

state_1:
    if (func_8003F270()) {
        ((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v |= 0x800;
        goto end;
    }
    ((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v &= 0xF7FF;
    ((S_801737C8_0 *)controller)->unk_9B++;
    func_800A56E0(0x703);

state_2:
    {
        s16 effect_count;
        s32 dim_channel;

        effect_count = 0;
        dim_channel = 0x20;
        do {
            object = func_8003FC64(0x212);
            if (object != 0) {
                u8 *effect_data;
                void *sprite;
                void *effect_pos;
                s32 dx;
                s32 dy;
                s32 color_bits;

                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                effect_data = (u8 *)object + 0x20;
                (*(u16 *)((u8 *)effect_data + 0x24)) = 0x13;
                (*(u16 *)((u8 *)object + 0x20)) = 0;
                (*(void * *)((u8 *)object + 0x10)) = D_80171284;
                func_8004491C(object, D_80170FD8);

                sprite = (*(void * *)((u8 *)object + 0x0C));
                ((S_801737C8_5 *)sprite)->unk_10 = dim_channel;
                ((S_801737C8_5 *)sprite)->unk_14 |= 0x0C;
                effect_pos = (*(void * *)((u8 *)object + 8));
                ((S_801737C8_6 *)effect_pos)->unk_02 = ((Rec_D_800E3D7C *)motion)->unk_00.at02_u16.v;
                ((S_801737C8_6 *)effect_pos)->unk_06 = ((Rec_D_800E3D7C *)motion)->unk_04.at02_u16.v;
                ((S_801737C8_6 *)effect_pos)->unk_0A = ((Rec_D_800E3D7C *)motion)->unk_08.at02_u16.v;

                dx = (rand() & 0x3F) - 0x20;
                dy = (rand() & 0x3F) - 0x20;
                ((S_801737C8_6 *)effect_pos)->unk_02 += dx;
                ((S_801737C8_6 *)effect_pos)->unk_06 += dy;
                ((S_801737C8_5 *)sprite)->unk_1C = 0x1000;
                ((S_801737C8_5 *)sprite)->unk_1E = 0x1000;

                color_bits = rand() & 7;
                if (color_bits & 1) {
                    ((S_801737C8_5 *)sprite)->unk_0C = 0x80;
                } else {
                    ((S_801737C8_5 *)sprite)->unk_0C = dim_channel;
                }
                if (color_bits & 2) {
                    ((S_801737C8_5 *)sprite)->unk_0D = 0x80;
                } else {
                    ((S_801737C8_5 *)sprite)->unk_0D = dim_channel;
                }
                if (color_bits & 4) {
                    ((S_801737C8_5 *)sprite)->unk_0E = 0x80;
                } else {
                    ((S_801737C8_5 *)sprite)->unk_0E = dim_channel;
                }
                (*(u8 *)((u8 *)effect_data + 2)) = ((S_801737C8_5 *)sprite)->unk_0C;
                (*(u8 *)((u8 *)effect_data + 3)) = ((S_801737C8_5 *)sprite)->unk_0D;
                (*(u8 *)((u8 *)effect_data + 4)) = ((S_801737C8_5 *)sprite)->unk_0E;
                ((S_801737C8_5 *)sprite)->unk_12 = 0x7DCF;
                ((S_801737C8_5 *)sprite)->unk_14 |= 0x100;
                (*(Copy12 *)((u8 *)effect_data + 0x34)) = *(Copy12 *)D_80175424;
                ((S_801737C8_5 *)sprite)->unk_08 = effect_data + 0x34;
                (*(u16 *)((u8 *)effect_data + 0x50)) = 8;
                (*(u16 *)((u8 *)effect_data + 0x4E)) = 4;
            }
            effect_count++;
        } while (effect_count < 1);
    }

    if ((((Rec_D_80082E80 *)actor)->unk_04.as_s8 == 6 &&
         (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0xE000)) {
        ((S_801737C8_0 *)controller)->unk_98 |= 0x80;
    }
    if ((((Rec_D_80082E80 *)actor)->unk_04.as_s8 == 9 &&
         (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0xE000)) {
        ((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v |= 0x800;
        ((S_801737C8_0 *)controller)->unk_96 = 0x14;
        ((S_801737C8_0 *)controller)->unk_9B = ((S_801737C8_0 *)controller)->unk_9B + 1;
        goto end;
    }
    goto end;

state_3:
    {
        u8 *action_state;
        s16 timer;

        action_state = (u8 *)&D_80083460;
        if (((S_801737C8_7 *)action_state)->unk_0C == 0) {
            ((S_801737C8_0 *)controller)->unk_96 = 0;
        }
        timer = ((S_801737C8_0 *)controller)->unk_96 - 1;
        ((S_801737C8_0 *)controller)->unk_96 = timer;
        if (timer <= 0) {
            ((S_801737C8_0 *)controller)->unk_96 = 0;
            ((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (!(((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0xE000)) {
            goto end;
        }
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25);
        if (((Rec_D_80082E80 *)actor)->unk_2C.as_pu8 != D_801753BC) {
            u8 *facing_frames;
            s32 facing_index;

            facing_frames = D_801753BC;
            (*(u8 * *)((u8 *)actor + 0x2C)) = facing_frames;
            facing_index = ((D_80083228 + (*(s16 *)((u8 *)object + 0x2A)) + 0x100) >> 9) & 7;
            func_80047784(actor, facing_frames[facing_index], 0);
            ((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (((S_801737C8_7 *)action_state)->unk_0C != 0) {
            goto end;
        }
        ((S_801737C8_7 *)action_state)->unk_0A--;
        ((S_801737C8_0 *)controller)->unk_8C = D_80171E20;
        func_800A4ACC(object);
        (*(u8 *)((u8 *)object + 0x73)) = 0;
        (*(u8 *)((u8 *)object + 0x72)) = 0;
        (*(u8 *)((u8 *)object + 0x6D))--;
        (*(u16 *)((u8 *)object + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);
    }

end:
    return;
}
