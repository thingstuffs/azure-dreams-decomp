#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_80170A44(void *, void *, void *, void *);
extern void func_801731F4(void) __attribute__((noreturn));
extern void func_80173268(void) __attribute__((noreturn));

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170850[];
extern void *D_801708B0[];
extern s32 D_801714D4[];
extern u8 D_801740E0[];
extern u8 D_80174110[];
extern u8 D_80174118[];


typedef struct S_80172A48_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
} S_80172A48_0;   /* arg0 in func_80172A48 */

typedef struct S_80172A48_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172A48_1_pre;   /* the 0x14 bytes before active in func_80172A48, addressed as active[-1] */

typedef struct S_80172A48_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172A48_2;   /* linked in func_80172A48 */

typedef struct S_80172A48_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172A48_3;   /* arg2 in func_80172A48 */


typedef struct S_80172A48_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172A48_5;   /* global in func_80172A48 */

void func_80172A48(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *held_arg0 ASM_REG("$16") = arg0;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *held_arg1 = arg1;
    void *held_arg2 = arg2;
    void *held_arg3 = arg3;
    static void *volatile state_keep[] = {
        &&state_0, &&state_1, &&state_2, &&state_3,
        &&state_4, &&state_5, &&state_6, &&state_7,
        &&state_8, &&end, &&end, &&end,
        &&end, &&end, &&end, &&end,
        &&state_16, &&state_17, &&state_18, &&state_19,
        &&state_20, &&state_21, &&state_22, &&state_23
    };
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    register u8 *selection ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 special;
    s32 call_special;
    s32 next_state;
    u8 state;
    void *active;

#define arg0 held_arg0
#define arg1 held_arg1
#define arg2 held_arg2
#define arg3 held_arg3

    ASM_KEEP(held_arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    special = 0;
    state = ((S_80172A48_0 *)arg0)->unk_9B;
    if ((u32)state >= 24) {
        goto end;
    }
    (void)state_keep;
    goto *D_80170850[state];

state_0:
    if ((*(u32 *)((u8 *)arg3 + 0x1C)) & 0x2000) {
        u32 dispatch;

        dispatch = ((*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF) - 1;
        if (dispatch >= 7) {
            goto kind_default;
        }
        (void)kind_keep;
        goto *D_801708B0[dispatch];

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
        s32 type;

        type = (*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF;
        if (type == 2) {
            goto kind_2;
        }
        if (type < 3) {
            selection = 0;
            if (type == 1) {
                goto normal_kind_1;
            }
            goto selection_ready;
        }
        if (type != 3) {
            selection = 0;
            goto selection_ready;
        }
    }

kind_3:
    selection = (u8 *)arg3 + 0xE;
    goto selection_ready;
kind_2:
    selection = (u8 *)arg3 + 0xB;
    goto selection_ready;
normal_kind_1:
kind_1:
    selection = (u8 *)arg3 + 8;
    goto selection_ready;
kind_default:
    selection = 0;

selection_ready:
    if (*selection == 0) {
        goto empty_selection;
    }
    ((S_80172A48_0 *)arg0)->unk_98 &= 0xFF7F;
    {
        s32 special_test;

        special_test = special;
        ASM_KEEP(special_test);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (special_test != 0) {
            active = D_800814A8;
            (*(void * *)((u8 *)arg3 + 0x60)) = active;
            goto copy_active_coords;
        }
    }

    {
        u8 item;

        item = *selection;
        if (D_8006DE24[item * 20 + 0x12] == 2) {
            active = (*(void * *)((u8 *)arg3 + 0x60));
            if (active != 0) {
                register u8 *linked ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

copy_active_coords:
                linked = ((S_80172A48_1_pre *)active)[-1].unk_00;
                (*(u8 *)((u8 *)arg3 + 0x72)) = ((S_80172A48_2 *)linked)->unk_24;
                (*(u8 *)((u8 *)arg3 + 0x73)) = ((S_80172A48_2 *)linked)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            active = func_800A05A4(
                arg3, ((S_80172A48_3 *)arg2)->unk_24, ((S_80172A48_3 *)arg2)->unk_25,
                (*(s16 *)((u8 *)arg3 + 0x2A)), 0x10);
            (*(void * volatile *)((u8 *)arg3 + 0x60)) = active;
            ASM_KEEP(active);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            dx = (*(s8 *)((u8 *)arg3 + 0x72));
            dy = (*(s8 *)((u8 *)arg3 + 0x73));
            if (dx < 0) {
                dx = -dx;
            }
            if (dy < 0) {
                dy = -dy;
            }
            (*(u8 *)((u8 *)arg3 + 0x72)) = dx;
            (*(u8 *)((u8 *)arg3 + 0x73)) = dy;
        }
    }

invoke_item:
    call_special = special;
    ASM_KEEP_NV(call_special);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    if (func_800A94A0(arg3, selection, call_special, (u8 *)arg0 + 0x98) == 0) {
        goto end;
    }
    ((S_80172A48_0 *)arg0)->unk_96.u = 0;
    ((S_80172A48_0 *)arg0)->unk_9B++;
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    if ((u32)(*selection - 0x2E) >= 3) {
        goto end;
    }
    if (call_special == 1) {
        goto end;
    }
    ((S_80172A48_0 *)arg0)->unk_9B = 0x10;
    return;

empty_selection:
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((S_80172A48_3 *)arg2)->unk_24, ((S_80172A48_3 *)arg2)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(arg3);
    (*(u8 *)((u8 *)arg3 + 0x6D))--;
    ((S_80172A48_0 *)arg0)->unk_8C = D_801714D4;
    (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
    (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
    (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
    return;

state_1:
    if (func_8003F270()) {
        goto set_actor_flag;
    }
    ((S_80172A48_3 *)arg2)->unk_14 &= 0xF7FF;
    ((S_80172A48_0 *)arg0)->unk_9B++;

state_2:
    {
        s16 timer;

        timer = ((S_80172A48_0 *)arg0)->unk_96.u;
        ((S_80172A48_0 *)arg0)->unk_96.u = timer + 1;
        if ((s16)timer < 8) {
            if (!(((S_80172A48_3 *)arg2)->unk_14 & 0x8000)) {
                goto end;
            }
        }
    }
    next_state = ((S_80172A48_0 *)arg0)->unk_9B + 1;
    ((S_80172A48_0 *)arg0)->unk_96.u = 0;
    ASM_TAILSLOT_PIN(next_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_80173268();

state_3:
    if (((S_80172A48_0 *)arg0)->unk_A2 != 0) {
        s16 timer;

        timer = ((S_80172A48_0 *)arg0)->unk_96.u;
        ((S_80172A48_0 *)arg0)->unk_96.u = timer + 1;
        if ((s16)timer < 15) {
            if (!(((S_80172A48_3 *)arg2)->unk_14 & 0x8000)) {
                goto end;
            }
        }
    }
    ((S_80172A48_0 *)arg0)->unk_96.u = 0;
    ((S_80172A48_0 *)arg0)->unk_9B++;
    func_800A56E0(0x703);
    {
        register void *model_base ASM_REG("$5") = D_80174110;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_TAILSLOT_PIN(model_base);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        func_801731F4();
    }

state_4:
    func_80170A44(arg0, arg1, arg2, arg3);
    {
        s16 timer;

        timer = ((S_80172A48_0 *)arg0)->unk_96.u;
        ((S_80172A48_0 *)arg0)->unk_96.u = timer + 1;
        if ((s16)timer < 3) {
            if (!(((S_80172A48_3 *)arg2)->unk_14 & 0xE000)) {
                goto end;
            }
        }
    }
    ((S_80172A48_3 *)arg2)->unk_14 |= 0x800;
    next_state = ((S_80172A48_0 *)arg0)->unk_9B + 1;
    ASM_TAILSLOT_PIN(next_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_80173268();

state_5:
    ((S_80172A48_3 *)arg2)->unk_14 |= 0x800;
    {
        s16 timer;

        timer = ((S_80172A48_0 *)arg0)->unk_96.u;
        ((S_80172A48_0 *)arg0)->unk_96.u = timer + 1;
        if ((s16)timer < 10) {
            if (!(((S_80172A48_3 *)arg2)->unk_14 & 0x8000)) {
                goto end;
            }
        }
    }
    ((S_80172A48_0 *)arg0)->unk_96.u = 0;
    ((S_80172A48_0 *)arg0)->unk_9B++;
    ((S_80172A48_3 *)arg2)->unk_14 &= 0xF7FF;
    return;

state_6:
    ((S_80172A48_0 *)arg0)->unk_96.u = 0;
    ((S_80172A48_0 *)arg0)->unk_98 |= 0x80;
    ((S_80172A48_0 *)arg0)->unk_9B++;
    return;

state_7:
    if (!(((S_80172A48_3 *)arg2)->unk_14 & 0xE000)) {
        goto end;
    }
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((S_80172A48_3 *)arg2)->unk_24, ((S_80172A48_3 *)arg2)->unk_25);
    ((S_80172A48_0 *)arg0)->unk_9B++;
    if (((S_80172A48_3 *)arg2)->unk_2C == D_801740E0) {
        goto end;
    }
    {
        u8 *model = D_801740E0;

        (*(void * *)((u8 *)arg2 + 0x2C)) = model;
        func_80047784(arg2,
            model[((D_80083228 + (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7],
            0);
    }
    ((S_80172A48_0 *)arg0)->unk_9E = 0;
    ((S_80172A48_0 *)arg0)->unk_92 = -0x20;
    return;

state_8:
    {
        u8 *global;

        global = (u8 *)&D_80083460;
        if (((S_80172A48_5 *)global)->unk_0C != 0) {
            goto end;
        }
        ((S_80172A48_5 *)global)->unk_0A--;
        ((S_80172A48_0 *)arg0)->unk_8C = D_801714D4;
        func_800A4ACC(arg3);
        (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
        (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
        (*(u8 *)((u8 *)arg3 + 0x6D))--;
        (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);
    }
    return;

state_16:
    if (func_8003F270()) {
set_actor_flag:
        ((S_80172A48_3 *)arg2)->unk_14 |= 0x800;
        return;
    }
    ((S_80172A48_3 *)arg2)->unk_14 &= 0xF7FF;
    ((S_80172A48_0 *)arg0)->unk_9B++;

state_17:
    {
        s16 timer;

        timer = ((S_80172A48_0 *)arg0)->unk_96.u;
        ((S_80172A48_0 *)arg0)->unk_96.u = timer + 1;
        if ((s16)timer < 8 &&
            !(((S_80172A48_3 *)arg2)->unk_14 & 0x8000)) {
            goto end;
        }
    }
    next_state = ((S_80172A48_0 *)arg0)->unk_9B + 1;
    ((S_80172A48_0 *)arg0)->unk_96.u = 0;
    ASM_TAILSLOT_PIN(next_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_80173268();

state_18:
    if (((S_80172A48_0 *)arg0)->unk_A2 != 0) {
        s16 timer;

        timer = ((S_80172A48_0 *)arg0)->unk_96.u;
        ((S_80172A48_0 *)arg0)->unk_96.u = timer + 1;
        if ((s16)timer < 15 &&
            !(((S_80172A48_3 *)arg2)->unk_14 & 0x8000)) {
            goto end;
        }
    }
    ((S_80172A48_0 *)arg0)->unk_96.u = 0;
    ((S_80172A48_0 *)arg0)->unk_9B++;
    func_800A56E0(0x703);
    {
        register void *model_base ASM_REG("$5") = D_80174110;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_TAILSLOT_PIN(model_base);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        func_801731F4();
    }

state_19:
    func_80170A44(arg0, arg1, arg2, arg3);
    {
        s16 timer;

        timer = ((S_80172A48_0 *)arg0)->unk_96.u;
        ((S_80172A48_0 *)arg0)->unk_96.u = timer + 1;
        if ((s16)timer < 2 &&
            !(((S_80172A48_3 *)arg2)->unk_14 & 0xE000)) {
            goto end;
        }
    }
    ((S_80172A48_3 *)arg2)->unk_14 |= 0x800;
    next_state = ((S_80172A48_0 *)arg0)->unk_9B + 1;
    ASM_TAILSLOT_PIN(next_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_80173268();

state_20:
    ((S_80172A48_3 *)arg2)->unk_14 |= 0x800;
    if (((S_80172A48_0 *)arg0)->unk_96.s < 5) {
        func_80170A44(arg0, arg1, arg2, arg3);
    }
    {
        s16 timer;

        timer = ((S_80172A48_0 *)arg0)->unk_96.u;
        ((S_80172A48_0 *)arg0)->unk_96.u = timer + 1;
        if ((s16)timer < 10 &&
            !(((S_80172A48_3 *)arg2)->unk_14 & 0x8000)) {
            goto end;
        }
    }
    ((S_80172A48_0 *)arg0)->unk_96.u = 0;
    ((S_80172A48_0 *)arg0)->unk_9B++;
    ((S_80172A48_3 *)arg2)->unk_14 &= 0xF7FF;
    ((S_80172A48_0 *)arg0)->unk_98 |= 0x80;
    return;

state_21:
    if (!(((S_80172A48_3 *)arg2)->unk_14 & 0xE000)) {
        goto end;
    }
    ((S_80172A48_0 *)arg0)->unk_96.u = 0;
    ((S_80172A48_0 *)arg0)->unk_9B++;
    {
        u8 *model_base = D_80174118;

        (*(void * *)((u8 *)arg2 + 0x2C)) = model_base;
        func_80047784(arg2,
            model_base[((D_80083228 + (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7],
            0);
    }
    return;

state_22:
    {
        s16 timer;

        timer = ((S_80172A48_0 *)arg0)->unk_96.u;
        ((S_80172A48_0 *)arg0)->unk_96.u = timer + 1;
        if ((s16)timer < 5) {
            goto end;
        }
    }
    next_state = ((S_80172A48_0 *)arg0)->unk_9B + 1;
    ((S_80172A48_0 *)arg0)->unk_96.u = 0;
    ASM_TAILSLOT_PIN(next_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_80173268();

state_23:
    next_state = 6;
    ((S_80172A48_0 *)arg0)->unk_96.u = 0;

store_next_state:
    ((S_80172A48_0 *)arg0)->unk_9B = next_state;

end:
    return;
}
