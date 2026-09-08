#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801728C4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    union { volatile u16 s; u16 u; } unk_98;   /* accessed as both */
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801728C4_0;   /* arg0 in func_801728C4 */

typedef struct S_801728C4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 s; s8 u; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_801728C4_1;   /* arg3 in func_801728C4 */

typedef struct S_801728C4_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801728C4_2_pre;   /* the 0x14 bytes before mode_global in func_801728C4, addressed as mode_global[-1] */

typedef struct S_801728C4_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801728C4_3_pre;   /* the 0x14 bytes before parent in func_801728C4, addressed as parent[-1] */

typedef struct S_801728C4_3 {
    u8 pad_00[0xC];
    union { void * s; s32 u; } unk_0C;   /* accessed as both */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
} S_801728C4_3;   /* parent in func_801728C4 */

typedef struct S_801728C4_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x3];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
    void * unk_2C;
} S_801728C4_4;   /* arg2 in func_801728C4 */


typedef struct S_801728C4_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_801728C4_6;   /* global in func_801728C4 */

typedef struct S_801728C4_7 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_801728C4_7;   /* entity in func_801728C4 */

typedef struct S_801728C4_8 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0xC];
    s32 unk_A4;
} S_801728C4_8;   /* part in func_801728C4 */

typedef struct S_801728C4_9 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801728C4_9;   /* global_state in func_801728C4 */

typedef struct S_801728C4_10 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801728C4_10;   /* ((S_801728C4_7 *)entity)->unk_08 in func_801728C4 */



extern void *D_80170858[];
extern u8 D_8006DE24[20];
extern u8 *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[16];
extern s32 D_8008346C[3];
extern u8 D_80083498[16];
extern u8 D_80170E84[];
extern u8 D_80174820[];
extern u8 D_80174850[];

extern s32 func_8003F270();
extern s32 func_8003DE58(void *, void *, void *, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80045340(void);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern void *func_800A05A4(void *, s32, s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, void *, s32, void *);
extern void func_800DA840(void *, s32);
extern void func_801740FC(void);

/* Updates actor action states, movement, and impact effects. */
void func_801728C4(void *action, void *motion, void *sprite, void *actor)
{
    static void *const dispatch_labels[] = {
        &&jt_1, &&jt_2, &&jt_3, &&jt_4, &&jt_5, &&jt_6, &&jt_7
    };
    u16 pos[3];
    u16 delta[3];
    s32 state;
    u32 anim_id;
    u32 action_kind;
    u32 dispatch_index;
    s32 normal_action;
    s32 special_mode;
    s32 special_test;
    s32 particle_count;
    register s32 current_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *anim;
    u16 timer;
    void *effect;
    void *effect_state;
    void *target_sprite;
    u32 callback_page;
    void (*callback)(void);
    void *player_state;
    void *special_target;
    u8 *effect_status;
    s32 offset_x;
    s32 offset_y;
    u16 flags;

    special_mode = 0;
    state = ((S_801728C4_0 *)action)->unk_9B;
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
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    if (!(((S_801728C4_1 *)actor)->unk_1C & 0x2000)) {
        goto no_special;
    }
    action_kind = ((S_801728C4_1 *)actor)->unk_46 & 0x3FFF;
    dispatch_index = action_kind - 1;
    if (dispatch_index >= 7) {
        goto jt_4;
    }
    (void)dispatch_labels;
    goto *D_80170858[dispatch_index];

jt_7:
    special_mode = 1;
    goto no_3;
jt_6:
    special_mode = 1;
    goto no_2;
jt_5:
    special_mode = 1;
    goto no_1;

no_special:
    normal_action = ((S_801728C4_1 *)actor)->unk_46 & 0x3FFF;
    if (normal_action == 2) {
        goto no_2;
    }
    if (normal_action < 3) {
        if (normal_action == 1) {
            goto no_1;
        }
        anim = 0;
        goto selected;
    }
    if (normal_action != 3) {
        anim = 0;
        goto selected;
    }
no_3:
jt_3:
    anim = (u8 *)actor + 0xE;
    goto selected;
no_2:
jt_2:
    anim = (u8 *)actor + 0xB;
    goto selected;
no_1:
jt_1:
    anim = (u8 *)actor + 8;
    goto selected;
jt_4:
    anim = 0;

selected:
    if (*anim == 0) {
        goto empty_anim;
    }
    ((S_801728C4_0 *)action)->unk_98.s &= 0xFF7F;
    special_test = special_mode;
    ASM_KEEP_NV(special_test);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (special_test != 0) {
        special_target = D_800814A8;
        ((S_801728C4_1 *)actor)->unk_60 = special_target;
        target_sprite = ((S_801728C4_2_pre *)special_target)[-1].unk_00;
        goto copy_parent;
    }

    anim_id = *anim;
    if (D_8006DE24[anim_id * 0x14 + 0x12] == 2) {
        target_sprite = ((S_801728C4_1 *)actor)->unk_60;
        if (target_sprite != 0) {
            target_sprite = ((S_801728C4_3_pre *)target_sprite)[-1].unk_00;
copy_parent:
            ((S_801728C4_1 *)actor)->unk_72.s = ((S_801728C4_3 *)target_sprite)->unk_24;
            ((S_801728C4_1 *)actor)->unk_73.s = ((S_801728C4_3 *)target_sprite)->unk_25;
            goto object_ready;
        }
    } else {
        ((S_801728C4_1 *)actor)->unk_60 = func_800A05A4(
            actor, ((S_801728C4_4 *)sprite)->unk_24, ((S_801728C4_4 *)sprite)->unk_25,
            ((S_801728C4_1 *)actor)->unk_2A, 0x10);
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        offset_x = ((S_801728C4_1 *)actor)->unk_72.u;
        offset_y = ((S_801728C4_1 *)actor)->unk_73.u;
        if (offset_x < 0) {
            offset_x = -offset_x;
        }
        if (offset_y < 0) {
            offset_y = -offset_y;
        }
        ((S_801728C4_1 *)actor)->unk_72.s = offset_x;
        ((S_801728C4_1 *)actor)->unk_73.s = offset_y;
    }

object_ready:
    pos[0] = ((Rec_D_800E3D7C *)motion)->unk_00.at02_u16.v;
    pos[1] = ((Rec_D_800E3D7C *)motion)->unk_04.at02_u16.v;
    pos[2] = ((Rec_D_800E3D7C *)motion)->unk_08.at02_u16.v;
    if (func_800A94A0(actor, anim, special_mode, (u8 *)action + 0x98) != 0) {
        ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
        func_800A56E0(0x703);
        func_800DA840(pos, (s16)((*anim - 1) % 3));
        current_state = ((S_801728C4_0 *)action)->unk_9B;
        ((S_801728C4_0 *)action)->unk_96 = 30000;
        goto increment_state;
    }
    goto done;

empty_anim:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((S_801728C4_4 *)sprite)->unk_24, ((S_801728C4_4 *)sprite)->unk_25);
    player_state = D_800814A8;
    D_8008346C[0] = 0;
    ((S_801728C4_6 *)player_state)->unk_A6--;
    func_800A4ACC(actor);
    ((S_801728C4_1 *)actor)->unk_6D.s--;
    ((S_801728C4_0 *)action)->unk_8C = D_80170E84;
    ((S_801728C4_1 *)actor)->unk_73.s = 0;
    ((S_801728C4_1 *)actor)->unk_72.s = 0;
    ((S_801728C4_1 *)actor)->unk_46 &= 0x7FFF;
    goto done;

state_1:
    if (func_8003F270() != 0) {
        ((S_801728C4_4 *)sprite)->unk_14 |= 0x800;
        goto done;
    }
    ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_801728C4_0 *)action)->unk_9B++;

state_2:
    if (func_8003DE58(((S_801728C4_4 *)sprite)->unk_08, sprite, delta, 0) == 0) {
        delta[0] = delta[1] = delta[2] = 0;
    }
    if ((((S_801728C4_4 *)sprite)->unk_04 == 3 && (((S_801728C4_4 *)sprite)->unk_14 & 0x1000)) ||
        (((S_801728C4_4 *)sprite)->unk_14 & 0xE000)) {
        ((S_801728C4_4 *)sprite)->unk_14 |= 0x800;
        ((S_801728C4_0 *)action)->unk_96 = 6;
        ((S_801728C4_0 *)action)->unk_98.u |= 0x80;
        if (!(((S_801728C4_4 *)sprite)->unk_14 & 0x8000)) {
            flags = ((S_801728C4_0 *)action)->unk_98.s;
            ((S_801728C4_0 *)action)->unk_98.u = flags | 0x8000;
            effect = func_8003FD64(0x112, D_80083498);
            if (effect != 0) {
                func_8004491C(effect, func_80045340);
                effect_state = (u8 *)effect + 0x20;
                ((S_801728C4_7 *)effect)->unk_10 = func_801740FC;
                ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_02 =
                    ((Rec_D_800E3D7C *)motion)->unk_00.at02_u16.v + delta[0];
                ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_06 =
                    ((Rec_D_800E3D7C *)motion)->unk_04.at02_u16.v + delta[1];
                ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_0A =
                    ((Rec_D_800E3D7C *)motion)->unk_08.at02_u16.v + delta[2];
                ((S_801728C4_8 *)effect_state)->unk_A4 = 0;
                ((S_801728C4_8 *)effect_state)->unk_96 = 4;
                target_sprite = ((S_801728C4_7 *)effect)->unk_0C;
                ((S_801728C4_3 *)target_sprite)->unk_28 = ((S_801728C4_4 *)sprite)->unk_28;
                ((S_801728C4_3 *)target_sprite)->unk_1E = 0x1000;
                ((S_801728C4_3 *)target_sprite)->unk_1C = 0x1000;
                ((S_801728C4_3 *)target_sprite)->unk_14 = ((S_801728C4_4 *)sprite)->unk_14;
                ((S_801728C4_3 *)target_sprite)->unk_12 = ((S_801728C4_4 *)sprite)->unk_12;
                ((S_801728C4_3 *)target_sprite)->unk_0C.s = ((S_801728C4_4 *)sprite)->unk_0C;
                func_80047784(target_sprite, 0x2D, 0);
            }
        }
    }

    timer = ((S_801728C4_0 *)action)->unk_96 - 1;
    ((S_801728C4_0 *)action)->unk_96 = timer;
    if ((s32)(timer << 16) <= 0) {
        ((S_801728C4_0 *)action)->unk_98.u &= 0x7FFF;
        ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
    }

    if (((S_801728C4_0 *)action)->unk_98.u & 0x8000) {
        callback_page = 0x80170000;
        ASM_KEEP(callback_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        particle_count = 7;
        callback = (void *)(callback_page + 0x40FC);
        do {
            effect = func_8003FD64(0x112, D_80083498);
            if (effect != 0) {
                func_8004491C(effect, func_80045340);
                ((S_801728C4_7 *)effect)->unk_10 = callback;
                ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_02 =
                    ((Rec_D_800E3D7C *)motion)->unk_00.at02_u16.v + delta[0] + (func_80069EF8() & 0xF) - 8;
                ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_06 =
                    ((Rec_D_800E3D7C *)motion)->unk_04.at02_u16.v + delta[1] + (func_80069EF8() & 0xF) - 8;
                ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_0A =
                    ((Rec_D_800E3D7C *)motion)->unk_08.at02_u16.v + delta[2] + (func_80069EF8() & 0xF) - 8;
                ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_0C =
                    ((func_80069EF8() & 0xFF) - 0x80) << 11;
                ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_10 =
                    ((func_80069EF8() & 0xFF) - 0x80) << 11;
                ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_14 =
                    -(func_80069EF8() & 0xFF) << 12;
                effect_state = (u8 *)effect + 0x20;
                ((S_801728C4_8 *)effect_state)->unk_A4 = 0;
                ((S_801728C4_8 *)effect_state)->unk_96 = 7;
                target_sprite = ((S_801728C4_7 *)effect)->unk_0C;
                ((S_801728C4_3 *)target_sprite)->unk_28 = ((S_801728C4_4 *)sprite)->unk_28;
                ((S_801728C4_3 *)target_sprite)->unk_1E = 0x1000;
                ((S_801728C4_3 *)target_sprite)->unk_1C = 0x1000;
                ((S_801728C4_3 *)target_sprite)->unk_14 = ((S_801728C4_4 *)sprite)->unk_14;
                ((S_801728C4_3 *)target_sprite)->unk_12 = ((S_801728C4_4 *)sprite)->unk_12 - 0x80;
                ((S_801728C4_3 *)target_sprite)->unk_10 = 0x60;
                ((S_801728C4_3 *)target_sprite)->unk_0C.u = 0x00808080;
                ((S_801728C4_3 *)target_sprite)->unk_14 |= 0xC;
                func_80047784(target_sprite, 0x2F, 0);
            }
            particle_count--;
        } while (particle_count >= 0);
    }

    if (((S_801728C4_4 *)sprite)->unk_14 & 0xE000) {
        ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174850;
        func_80047784(
            sprite,
            D_80174850[((D_80083228 + ((S_801728C4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        current_state = ((S_801728C4_0 *)action)->unk_9B;
increment_state:
        ((S_801728C4_0 *)action)->unk_9B = current_state + 1;
        goto done;
    }
    goto done;

state_3:
    if (!(((S_801728C4_4 *)sprite)->unk_14 & 0xE000)) {
        goto done;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((S_801728C4_4 *)sprite)->unk_24, ((S_801728C4_4 *)sprite)->unk_25);
    if (((S_801728C4_4 *)sprite)->unk_2C != D_80174820) {
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174820;
        func_80047784(
            sprite,
            D_80174820[((D_80083228 + ((S_801728C4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
    effect_status = D_80083460;
    if (((S_801728C4_9 *)effect_status)->unk_0C == 0) {
        ((S_801728C4_9 *)effect_status)->unk_0A--;
        ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_801728C4_0 *)action)->unk_8C = D_80170E84;
        func_800A4ACC(actor);
        if (((S_801728C4_1 *)actor)->unk_6D.u > 0) {
            ((S_801728C4_1 *)actor)->unk_6D.s--;
        }
        ((S_801728C4_1 *)actor)->unk_73.s = 0;
        ((S_801728C4_1 *)actor)->unk_72.s = 0;
        ((S_801728C4_1 *)actor)->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
    }

done:
    return;
}
