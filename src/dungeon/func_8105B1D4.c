#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern s32 D_80170F68;
extern u8 D_80173FB8[8];

extern s32 func_8003F270();
extern void func_80047784();
extern void *func_800A05A4();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern s32 func_800A94A0();
extern void func_800DA840();


typedef struct S_801729D4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801729D4_0;   /* arg0 in func_801729D4 */

typedef struct S_801729D4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 u; s8 s; } unk_72;   /* accessed as both */
    union { u8 u; s8 s; } unk_73;   /* accessed as both */
} S_801729D4_1;   /* arg3 in func_801729D4 */

typedef struct S_801729D4_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801729D4_2_pre;   /* the 0x14 bytes before root in func_801729D4, addressed as root[-1] */

typedef struct S_801729D4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801729D4_3;   /* source in func_801729D4 */

typedef struct S_801729D4_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_801729D4_4;   /* arg2 in func_801729D4 */


typedef struct S_801729D4_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801729D4_6;   /* status in func_801729D4 */

/* Advance the actor animation state and reset movement when it finishes. */
void func_801729D4(void *action, void *motion, void *sprite, void *actor)
{
    static void *const anim_labels[] = {
        &&jt_1, &&jt_2, &&jt_3, &&jt_4, &&jt_5, &&jt_6, &&jt_7
    };
    u16 position[3];
    u8 *animation;
    s16 reuse_target;
    s32 reuse_test;
    s32 state;
    s32 anim_kind;
    void *target_root;
    void *target_source;
    void *new_target;
    u8 *status;
    s32 target_x;
    s32 target_y;

    state = ((S_801729D4_0 *)action)->unk_9B;
    reuse_target = 0;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
    if (!(((S_801729D4_1 *)actor)->unk_1C & 0x2000)) {
        goto no_special;
    }
    anim_kind = (((S_801729D4_1 *)actor)->unk_46 & 0x3FFF) - 1;
    if ((u32)anim_kind >= 7U) {
        goto jt_4;
    }
    (void)anim_labels;
    goto *(((void **)D_80170838)[anim_kind]);

jt_7:
    reuse_target = 1;
    goto no_3;
jt_6:
    reuse_target = 1;
    goto no_2;
jt_5:
    reuse_target = 1;
    goto no_1;

no_special:
    anim_kind = ((S_801729D4_1 *)actor)->unk_46 & 0x3FFF;
    if (anim_kind == 2) {
        goto no_2;
    }
    if (anim_kind < 3) {
        if (anim_kind == 1) {
            goto no_1;
        }
        animation = 0;
        ASM_KEEP(animation);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        goto selected;
    }
    if (anim_kind == 3) {
        goto no_3;
    }
    animation = 0;
    goto selected;

no_3:
jt_3:
    animation = (u8 *)actor + 0xE;
    goto selected;
no_2:
jt_2:
    animation = (u8 *)actor + 0xB;
    goto selected;
no_1:
jt_1:
    animation = (u8 *)actor + 8;
    goto selected;
jt_4:
    animation = 0;

selected:
    if (*animation == 0) {
        goto empty_anim;
    }
    ((S_801729D4_0 *)action)->unk_98 &= 0xFF7F;
    reuse_test = reuse_target;
    if (reuse_test != 0) {
        target_root = D_800814A8;
        ((S_801729D4_1 *)actor)->unk_60 = target_root;
        target_source = ((S_801729D4_2_pre *)target_root)[-1].unk_00;
        ((S_801729D4_1 *)actor)->unk_72.u = ((S_801729D4_3 *)target_source)->unk_24;
        ((S_801729D4_1 *)actor)->unk_73.u = ((S_801729D4_3 *)target_source)->unk_25;
        goto set_position;
    }

    new_target = func_800A05A4(
        actor, ((S_801729D4_4 *)sprite)->unk_24, ((S_801729D4_4 *)sprite)->unk_25,
        ((S_801729D4_1 *)actor)->unk_2A, 0x10);
    ((S_801729D4_1 *)actor)->unk_60 = new_target;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    target_x = ((S_801729D4_1 *)actor)->unk_72.s;
    target_y = ((S_801729D4_1 *)actor)->unk_73.s;
    if (target_x < 0) {
        target_x = -target_x;
    }
    if (target_y < 0) {
        target_y = -target_y;
    }
    ((S_801729D4_1 *)actor)->unk_72.u = target_x;
    ((S_801729D4_1 *)actor)->unk_73.u = target_y;

set_position:
    position[0] = ((Rec_D_800E3D7C *)motion)->unk_00.at02_u16.v;
    position[1] = ((Rec_D_800E3D7C *)motion)->unk_04.at02_u16.v;
    position[2] = ((Rec_D_800E3D7C *)motion)->unk_08.at02_u16.v;
    if (func_800A94A0(actor, animation, reuse_target, (u8 *)action + 0x98) != 0) {
        ((S_801729D4_4 *)sprite)->unk_14 &= 0xF7FF;
        func_800A56E0(0x703);
        func_800DA840(position, (s16)((*animation - 1) % 3));
        ((S_801729D4_0 *)action)->unk_9B++;
        return;
    }
    goto done;

empty_anim:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((S_801729D4_4 *)sprite)->unk_24, ((S_801729D4_4 *)sprite)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + (0xA6)))--;
    func_800A4ACC(actor);
    ((S_801729D4_1 *)actor)->unk_6D.u--;
    ((S_801729D4_0 *)action)->unk_8C = &D_80170F68;
    ((S_801729D4_1 *)actor)->unk_73.u = 0;
    ((S_801729D4_1 *)actor)->unk_72.u = 0;
    ((S_801729D4_1 *)actor)->unk_46 &= 0x7FFF;
    return;

state_1:
    if (func_8003F270() != 0) {
        ((S_801729D4_4 *)sprite)->unk_14 |= 0x800;
        return;
    }
    ((S_801729D4_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_801729D4_0 *)action)->unk_9B++;

state_2:
    if ((((S_801729D4_4 *)sprite)->unk_04 == 8 &&
         (((S_801729D4_4 *)sprite)->unk_14 & 0x1000)) ||
        (((S_801729D4_4 *)sprite)->unk_14 & 0xE000)) {
        ((S_801729D4_4 *)sprite)->unk_14 |= 0x800;
        ((S_801729D4_0 *)action)->unk_96 = 3;
        ((S_801729D4_0 *)action)->unk_98 |= 0x80;
    }
    ((S_801729D4_0 *)action)->unk_96--;
    if ((s16)((S_801729D4_0 *)action)->unk_96 <= 0) {
        ((S_801729D4_0 *)action)->unk_96 = 0;
        ((S_801729D4_4 *)sprite)->unk_14 &= 0xF7FF;
    }
    if (((S_801729D4_4 *)sprite)->unk_14 & 0xE000) {
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((S_801729D4_4 *)sprite)->unk_24, ((S_801729D4_4 *)sprite)->unk_25);
        if (((S_801729D4_4 *)sprite)->unk_2C != D_80173FB8) {
            (*(void * *)((u8 *)sprite + (0x2C))) = D_80173FB8;
            func_80047784(
                sprite,
                D_80173FB8[((D_80083228 + ((S_801729D4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        status = (u8 *)&D_80083460;
        if (((S_801729D4_6 *)status)->unk_0C == 0) {
            ((S_801729D4_6 *)status)->unk_0A--;
            ((S_801729D4_4 *)sprite)->unk_14 &= 0xF7FF;
            ((S_801729D4_0 *)action)->unk_8C = &D_80170F68;
            func_800A4ACC(actor);
            if (((S_801729D4_1 *)actor)->unk_6D.s > 0) {
                ((S_801729D4_1 *)actor)->unk_6D.u--;
            }
            ((S_801729D4_1 *)actor)->unk_73.u = 0;
            ((S_801729D4_1 *)actor)->unk_72.u = 0;
            ((S_801729D4_1 *)actor)->unk_46 &= 0x7FFF;
            func_800A56E0(0xB4);
        }
    }

done:
    return;
}
