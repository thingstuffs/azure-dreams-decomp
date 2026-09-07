#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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

extern void func_800248D8(void) __attribute__((noreturn));
extern void func_80024920(void) __attribute__((noreturn));
extern void func_80033B78(s32);
extern void func_80033B9C(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_8003F540(s32, s32, s32, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800483AC(s32);
extern s32 func_80053DA8(s32);
extern void func_800C15C0(s32, s32);

void func_800243D8(State8081A3D8 *arg0)
{
    u8 *object;
    register u8 *inner ASM_REG("$16");
    u8 *spawn_list;
    u8 *callback;
    s16 interval;
    s16 value;
    s32 score_threshold;
    u16 highscore;
    s32 state;
    register s32 spawn_kind ASM_REG("$4");
    register s32 dialog_zero ASM_REG("$4");
    s32 *limit;
    static void *const keepalive[6] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&case_5
    };

    callback = D_800200B4;
    value = arg0->rate;
    interval = 42 - value / 6;
    if (interval < 16) {
        interval = 16;
    }

    limit = (s32 *)D_80083780;
    if (limit[1] > 0x03200000) {
        limit[1] = 0x03200000;
    }

    state = arg0->state;
    if ((u32)state >= 6) {
        goto end;
    }
    goto *D_800200CC[state];

case_0:
    if (((s16)arg0->timer % interval) != 0) {
        goto tick;
    }
    if (arg0->countdown <= 0) {
        if ((arg0->state != 1) || !(arg0->flags & 4)) {
            goto tick;
        }
    }

    arg0->timer = 0;
    arg0->phase = (arg0->phase + 1) & 3;
    if (arg0->state == 0) {
        arg0->countdown--;
    }

    object = func_8003FD64(0x136, D_80083498);
    if (object != 0) {
        u8 *object_tail = object + 0x20;
        FIELD(object, void *, 0x10) = D_80024B48;
        func_8004491C(object, D_80045340);
        inner = FIELD(object, u8 *, 0x0C);
        FIELD(FIELD(object, u8 *, 8), s32, 0) = 0x03200000;
        FIELD(FIELD(object, u8 *, 8), s32, 4) = 0x02E00000;
        FIELD(FIELD(object, u8 *, 8), s32, 8) = 0xFFFC0000;
        {
            u16 object_phase = arg0->phase;
            FIELD(object_tail, State8081A3D8 *, 0xAC) = arg0;
            FIELD(object_tail, s16, 0xA0) = object_phase;
        }
        FIELD(inner, s16, 0x1E) = 0x1000;
        FIELD(inner, s16, 0x1C) = 0x1000;
        FIELD(inner, s16, 6) = -0x100;
        func_8003DB94(inner, D_800F7DFC, 0);
        FIELD(inner, s32, 0x0C) = 0x00808080;
    }
    arg0->flags |= 1;

tick:
    arg0->timer++;
    if (arg0->flags & 1) {
        goto end;
    }
    if (arg0->countdown > 0) {
        goto end;
    }
    if (arg0->flags & 4) {
        arg0->state = 2;
        func_80024920();
    }

case_1:
    ASM_SCHED_BARRIER();
    spawn_kind = 1;
    ASM_KEEP(spawn_kind);
    spawn_list = D_80083498;
    object = func_8003FD64(spawn_kind, spawn_list);
    ASM_KEEP(object);
    if (object != 0) {
        inner = object + 0x20;
        FIELD(object, void *, 0x10) = D_80024AC0;
        func_8004491C(object, D_80053858);
        FIELD(inner, s16, 0x14) = 0x7C;
        FIELD(inner, s16, 0x16) = 0x78;
        FIELD(inner, s16, 0x1A) = 0x7C80;
        FIELD(inner, s32, 0x10) = 0x00808080;
        FIELD(inner, void *, 4) = callback;
        FIELD(inner, s16, 2) = 0x96;
    }

    spawn_kind = 1;
    ASM_KEEP(spawn_kind);
    object = func_8003FD64(spawn_kind, spawn_list);
    ASM_KEEP(object);
    if (object != 0) {
        inner = object + 0x20;
        FIELD(object, void *, 0x10) = D_80024B04;
        func_8004491C(object, &D_80053A88);
        FIELD(inner, s16, 0x0C) = 0x74;
        FIELD(inner, s16, 0x0E) = 0x74;
        FIELD(inner, s16, 0x10) = 0x58;
        FIELD(inner, s16, 0x12) = 0x10;
        FIELD(inner, s32, 8) = 0x00101010;
        FIELD(inner, s16, 2) = 0x96;
        FIELD(inner, u16, 0x16) |= 1;
    }
    arg0->timer = 0x96;
    arg0->state = 3;
    func_80024920();

case_2:
    spawn_kind = 1;
    ASM_KEEP(spawn_kind);
    spawn_list = D_80083498;
    object = func_8003FD64(spawn_kind, spawn_list);
    ASM_KEEP(object);
    if (object != 0) {
        inner = object + 0x20;
        FIELD(object, void *, 0x10) = D_80024AC0;
        func_8004491C(object, D_80053858);
        FIELD(inner, s16, 0x14) = 0x80;
        FIELD(inner, s16, 0x16) = 0x78;
        FIELD(inner, s16, 0x1A) = 0x7C80;
        FIELD(inner, void *, 4) = D_800200C0;
        FIELD(inner, s32, 0x10) = 0x00808080;
        FIELD(inner, s16, 2) = 0x96;
    }

    spawn_kind = 1;
    ASM_KEEP(spawn_kind);
    object = func_8003FD64(spawn_kind, spawn_list);
    ASM_KEEP(object);
    if (object != 0) {
        inner = object + 0x20;
        FIELD(object, void *, 0x10) = D_80024B04;
        func_8004491C(object, &D_80053A88);
        FIELD(inner, s16, 0x0C) = 0x78;
        FIELD(inner, s16, 0x0E) = 0x74;
        FIELD(inner, s16, 0x10) = 0x50;
        FIELD(inner, s16, 0x12) = 0x10;
        FIELD(inner, s32, 8) = 0x00101010;
        FIELD(inner, s16, 2) = 0x96;
        FIELD(inner, u16, 0x16) |= 1;
    }
    arg0->state = 4;
    arg0->timer = 0x64;
    func_80024920();

case_3:
    arg0->timer--;
    if ((s16)arg0->timer >= 0) {
        goto end;
    }
    arg0->timer = 0;
    arg0->state = 1;
    func_80024920();

case_4:
    arg0->timer--;
    if ((s16)arg0->timer == 0x50) {
        func_80053DA8(0xB1);
    }
    if ((s16)arg0->timer >= 0) {
        goto end;
    }

    func_800C15C0(0x20, 0x200);
    func_80033B78(0xA4);
    highscore = D_800135BC[0];
    score_threshold = arg0->threshold;
    ASM_KEEP(highscore);
    dialog_zero = 0;
    if ((s16)highscore < score_threshold) {
        register s32 dialog_id_true ASM_REG("$5");
        ASM_KEEP(dialog_zero);
        dialog_id_true = 0x2C3D;
        ASM_KEEP(dialog_id_true);
        func_8003F540(dialog_zero, dialog_id_true, 0x01000001, 0x01000271);
        func_80053DA8(0x300);
        D_800135BC[0] = arg0->threshold;
        func_80033B9C(0x553);
        func_800248D8();
    }

    {
        register s32 dialog_id_false ASM_REG("$5");
        ASM_KEEP(dialog_zero);
        dialog_id_false = 0x2C3D;
        ASM_KEEP(dialog_id_false);
        func_8003F540(dialog_zero, dialog_id_false, dialog_zero, 0x01000290);
    }
    func_80053DA8(0x300);
    func_80033B78(0x553);
    func_800483AC(1);
    func_80033B78(0xA5);
    arg0->state = 5;
    arg0->flags |= 2;
    func_80024920();

case_5:
    *((u16 *)arg0 - 1) |= 0x8000;
    D_800814A0 |= 0x8000;

end:
    arg0->flags &= 0xFFFE;
}
