#include "common.h"


typedef struct State8081A3D8 {
    s16 state;
    u16 timer;
    u16 phase;
    s16 threshold;
    s16 rate;
    s16 countdown;
    u16 flags;
} State8081A3D8;

extern u16 D_800135BC[];
extern u8 D_800200B4[];
extern u8 D_800200C0[];
extern void *D_800200CC[];
extern u8 D_80024AC0[];
extern u8 D_80024B04[];
extern u8 D_80024B48[];
extern u8 D_80045340[];
extern s32 D_80053858[4];
extern s32 D_80053A88;
extern int D_800814A0;
extern u8 D_80083498[];
extern u8 D_80083780[];
extern u8 D_800F7DFC[];

extern void func_80033B78(s32);
extern void func_80033B9C(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_8003F540(s32, s32, s32, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800483AC(s32);
extern s32 SD_Call(s32);
extern void tw_sd_sq_ld_call(s32, s32);


typedef struct S_800243D8_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_800243D8_0;   /* object in func_800243D8 */

typedef struct S_800243D8_1 {
    u8 pad_00[0xA0];
    s16 unk_A0;
    u8 pad_A2[0xA];
    State8081A3D8 * unk_AC;
} S_800243D8_1;   /* object_tail in func_800243D8 */

typedef struct S_800243D8_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    s16 unk_14;
    union { s16 s; u16 u; } unk_16;   /* accessed as both */
    u8 pad_18[0x2];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800243D8_2;   /* inner in func_800243D8 */

typedef struct S_800243D8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800243D8_3;   /* ((S_800243D8_0 *)object)->unk_08 in func_800243D8 */

/* Advances object spawning, result displays, and high-score handling. */
void func_800243D8(State8081A3D8 *controller)
{
    u8 *object;
    register u8 *object_data ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *spawn_list;
    u8 *callback;
    s16 spawn_interval;
    s16 spawn_rate;
    s32 score_threshold;
    u16 best_score;
    s32 state;
    s32 spawn_kind;
    s32 dialog_zero;
    s32 *position;
    static void *const state_labels[6] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&case_5
    };

    callback = D_800200B4;
    spawn_rate = controller->rate;
    spawn_interval = 42 - spawn_rate / 6;
    if (spawn_interval < 16) {
        spawn_interval = 16;
    }

    position = (s32 *)D_80083780;
    if (position[1] > 0x03200000) {
        position[1] = 0x03200000;
    }

    state = controller->state;
    if ((u32)state >= 6) {
        goto end;
    }
    goto *D_800200CC[state];

case_0:
    if (((s16)controller->timer % spawn_interval) != 0) {
        goto tick;
    }
    if (controller->countdown <= 0) {
        if ((controller->state != 1) || !(controller->flags & 4)) {
            goto tick;
        }
    }

    controller->timer = 0;
    controller->phase = (controller->phase + 1) & 3;
    if (controller->state == 0) {
        controller->countdown--;
    }

    object = func_8003FD64(0x136, D_80083498);
    if (object != 0) {
        u8 *object_tail = object + 0x20;
        ((S_800243D8_0 *)object)->unk_10 = D_80024B48;
        func_8004491C(object, D_80045340);
        object_data = ((S_800243D8_0 *)object)->unk_0C;
        ((S_800243D8_3 *)(((S_800243D8_0 *)object)->unk_08))->unk_00 = 0x03200000;
        ((S_800243D8_3 *)(((S_800243D8_0 *)object)->unk_08))->unk_04 = 0x02E00000;
        ((S_800243D8_3 *)(((S_800243D8_0 *)object)->unk_08))->unk_08 = 0xFFFC0000;
        {
            u16 object_phase = controller->phase;
            ((S_800243D8_1 *)object_tail)->unk_AC = controller;
            ((S_800243D8_1 *)object_tail)->unk_A0 = object_phase;
        }
        ((S_800243D8_2 *)object_data)->unk_1E = 0x1000;
        ((S_800243D8_2 *)object_data)->unk_1C = 0x1000;
        ((S_800243D8_2 *)object_data)->unk_04.at02.v = -0x100;
        func_8003DB94(object_data, D_800F7DFC, 0);
        ((S_800243D8_2 *)object_data)->unk_0C.at00.v = 0x00808080;
    }
    controller->flags |= 1;

tick:
    controller->timer++;
    if (controller->flags & 1) {
        goto end;
    }
    if (controller->countdown > 0) {
        goto end;
    }
    if (controller->flags & 4) {
        controller->state = 2;
        goto end;
    }

case_1:
    spawn_kind = 1;
    ASM_KEEP(spawn_kind);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    spawn_list = D_80083498;
    object = func_8003FD64(spawn_kind, spawn_list);
    if (object != 0) {
        object_data = object + 0x20;
        ((S_800243D8_0 *)object)->unk_10 = D_80024AC0;
        func_8004491C(object, D_80053858);
        ((S_800243D8_2 *)object_data)->unk_14 = 0x7C;
        ((S_800243D8_2 *)object_data)->unk_16.s = 0x78;
        ((S_800243D8_2 *)object_data)->unk_1A = 0x7C80;
        ((S_800243D8_2 *)object_data)->unk_10.at00.v = 0x00808080;
        ((S_800243D8_2 *)object_data)->unk_04.at00.v = callback;
        ((S_800243D8_2 *)object_data)->unk_02 = 0x96;
    }

    spawn_kind = 1;
    object = func_8003FD64(spawn_kind, spawn_list);
    if (object != 0) {
        object_data = object + 0x20;
        ((S_800243D8_0 *)object)->unk_10 = D_80024B04;
        func_8004491C(object, &D_80053A88);
        ((S_800243D8_2 *)object_data)->unk_0C.at00u.v = 0x74;
        ((S_800243D8_2 *)object_data)->unk_0C.at02.v = 0x74;
        ((S_800243D8_2 *)object_data)->unk_10.at00u.v = 0x58;
        ((S_800243D8_2 *)object_data)->unk_10.at02.v = 0x10;
        ((S_800243D8_2 *)object_data)->unk_08 = 0x00101010;
        ((S_800243D8_2 *)object_data)->unk_02 = 0x96;
        ((S_800243D8_2 *)object_data)->unk_16.u |= 1;
    }
    controller->timer = 0x96;
    controller->state = 3;
    goto end;

case_2:
    spawn_kind = 1;
    ASM_KEEP(spawn_kind);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    spawn_list = D_80083498;
    object = func_8003FD64(spawn_kind, spawn_list);
    if (object != 0) {
        object_data = object + 0x20;
        ((S_800243D8_0 *)object)->unk_10 = D_80024AC0;
        func_8004491C(object, D_80053858);
        ((S_800243D8_2 *)object_data)->unk_14 = 0x80;
        ((S_800243D8_2 *)object_data)->unk_16.s = 0x78;
        ((S_800243D8_2 *)object_data)->unk_1A = 0x7C80;
        ((S_800243D8_2 *)object_data)->unk_04.at00.v = D_800200C0;
        ((S_800243D8_2 *)object_data)->unk_10.at00.v = 0x00808080;
        ((S_800243D8_2 *)object_data)->unk_02 = 0x96;
    }

    spawn_kind = 1;
    object = func_8003FD64(spawn_kind, spawn_list);
    if (object != 0) {
        object_data = object + 0x20;
        ((S_800243D8_0 *)object)->unk_10 = D_80024B04;
        func_8004491C(object, &D_80053A88);
        ((S_800243D8_2 *)object_data)->unk_0C.at00u.v = 0x78;
        ((S_800243D8_2 *)object_data)->unk_0C.at02.v = 0x74;
        ((S_800243D8_2 *)object_data)->unk_10.at00u.v = 0x50;
        ((S_800243D8_2 *)object_data)->unk_10.at02.v = 0x10;
        ((S_800243D8_2 *)object_data)->unk_08 = 0x00101010;
        ((S_800243D8_2 *)object_data)->unk_02 = 0x96;
        ((S_800243D8_2 *)object_data)->unk_16.u |= 1;
    }
    controller->state = 4;
    controller->timer = 0x64;
    goto end;

case_3:
    controller->timer--;
    if ((s16)controller->timer >= 0) {
        goto end;
    }
    controller->timer = 0;
    controller->state = 1;
    goto end;

case_4:
    controller->timer--;
    if ((s16)controller->timer == 0x50) {
        SD_Call(0xB1);
    }
    if ((s16)controller->timer >= 0) {
        goto end;
    }

    tw_sd_sq_ld_call(0x20, 0x200);
    func_80033B78(0xA4);
    best_score = D_800135BC[0];
    score_threshold = controller->threshold;
    ASM_KEEP(best_score);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    dialog_zero = 0;
    if ((s16)best_score < score_threshold) {
        s32 dialog_id;
        dialog_id = 0x2C3D;
        func_8003F540(dialog_zero, dialog_id, 0x01000001, 0x01000271);
        SD_Call(0x300);
        D_800135BC[0] = controller->threshold;
        func_80033B9C(0x553);
    } else {
        s32 dialog_id;
        dialog_id = 0x2C3D;
        func_8003F540(dialog_zero, dialog_id, dialog_zero, 0x01000290);
        SD_Call(0x300);
        func_80033B78(0x553);
    }
    func_800483AC(1);
    func_80033B78(0xA5);
    controller->state = 5;
    controller->flags |= 2;
    goto end;

case_5:
    *((u16 *)controller - 1) |= 0x8000;
    D_800814A0 |= 0x8000;

end:
    controller->flags &= 0xFFFE;
}
