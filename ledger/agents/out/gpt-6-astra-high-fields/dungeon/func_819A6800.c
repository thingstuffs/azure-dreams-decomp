#include "common.h"

typedef struct S_func_819A6800_1 {
    void *unk_00;
    void *unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;
    u8 pad_0C[0x44];
    union { s16 s; u16 u; } unk_50;
    union { s16 s; u16 u; } unk_52;
} S_func_819A6800_1;

typedef struct S_func_819A6800_2 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0x0C];
    void *unk_20;
    u8 unk_24;
    u8 unk_25;
} S_func_819A6800_2;

typedef struct S_func_819A6800_3 {
    u8 pad_00[0x60];
    union { void *p; u32 u; } unk_60;
    u8 pad_64[0x0E];
    u8 unk_72;
    u8 unk_73;
} S_func_819A6800_3;

typedef struct S_func_819A6800_4 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x7A];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x4B];
    volatile u32 unk_F4;
    u8 pad_F8[0x0A];
    u8 unk_102;
} S_func_819A6800_4;

typedef struct S_func_819A6800_5 {
    union {
        u32 u;
        s32 s;
        struct { u8 pad_00[2]; u16 unk_02; } h;
    } unk_00;
    union {
        u32 u;
        s32 s;
        struct { u8 pad_04[2]; u16 unk_06; } h;
    } unk_04;
    union {
        u32 u;
        s32 s;
        struct { u8 pad_08[2]; u16 unk_0A; } h;
    } unk_08;
} S_func_819A6800_5;

typedef struct S_func_819A6800_6 {
    u16 unk_00;
} S_func_819A6800_6;

typedef struct S_func_819A6800_7 {
    u8 pad_00[0x0C];
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x1E];
    u16 unk_30;
    u16 unk_32;
    u32 unk_34;
    u32 unk_38;
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
    u16 unk_42;
    u8 pad_44[8];
    u16 unk_4C;
} S_func_819A6800_7;

typedef struct S_func_819A6800_8 {
    void *unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[2];
    u32 unk_08;
    u32 unk_0C;
    u16 unk_10;
    u8 pad_12[2];
    u16 unk_14;
    u8 pad_16[6];
    u16 unk_1C;
    u16 unk_1E;
} S_func_819A6800_8;

typedef struct S_func_819A6800_9 {
    u8 pad_00[4];
    u32 unk_04;
} S_func_819A6800_9;

typedef struct S_func_819A6800_10 {
    u8 pad_00[0x0A];
    u16 unk_0A;
    u32 unk_0C;
} S_func_819A6800_10;

extern void *D_80024008[];
extern u8 D_800814A8[16];
extern u8 D_80082E80[];
extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_800244BC[];
extern u8 D_80024810[];
extern u8 D_80024B20[];
extern u8 D_800DEE38[];
extern u16 D_80082E94[];
extern u8 D_80083460[];
extern u32 D_800814A0[];

#define GLOBAL_OBJECT (*(void **)D_800814A8)

extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void *func_8003FD64(s32, void *);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern u16 func_80066460(s32, s32, s32, s32);
extern u16 func_8006649C(s32, s32);
extern void func_8009CE1C(void *, s32, s32, s32, s32, void *, s32);
extern void func_8002413C(void) __attribute__((noreturn));
extern void func_80024434(void) __attribute__((noreturn));
extern void func_80024438(void) __attribute__((noreturn));
extern void func_8002449C(void) __attribute__((noreturn));

#ifdef __mips__
static const u32 func_819A6800_table[] __asm__("func_819A6800")
    __attribute__((used, section(".text.func_819A6800"), aligned(4))) = {
    0x80024020,
    0,
    0x80024080,
    0x8002414C,
    0x800242C4,
    0x80024304,
    0x80024424,
    0x80024448,
};
__asm__(".globl func_819A6800\n.size func_819A6800, 1212");
#define FUNC_819A6800_BODY func_819A6800_body
#else
#define FUNC_819A6800_BODY func_819A6800
#endif

#ifdef __mips__
void FUNC_819A6800_BODY(void *, void *)
    __attribute__((section(".text.func_819A6800")));
#endif

/* Runs a timed object creation sequence with visual effects and final cleanup. */
void FUNC_819A6800_BODY(void *sequence, void *out_position)
{
    S_func_819A6800_1 *self = (S_func_819A6800_1 *)sequence;
    register S_func_819A6800_3 *owner ASM_REG("$18") = self->unk_00;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_func_819A6800_2 *record = ((S_func_819A6800_2 *)((u8 *)owner - 0x20))->unk_0C;
    register S_func_819A6800_2 *owner_object ASM_REG("$16") = (S_func_819A6800_2 *)((u8 *)owner - 0x20);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 timer;
    s32 state;
    static void *const state_labels[] = {
        &&state2,
        &&state4,
        &&state5,
        &&state6,
        &&state7,
        &&advance_state,
    };

    timer = self->unk_50.u - 1;
    state = self->unk_0A.s;
    self->unk_50.u = timer;
    if ((u32)state >= 6U) {
        goto return_done;
    }
    (void)state_labels;
    goto *D_80024008[state];

state2:
    {
        S_func_819A6800_2 *new_object;
        S_func_819A6800_4 *counter_object;
        s16 position_offset[3];
        S_func_819A6800_7 *effect_data;
        register S_func_819A6800_8 *sprite ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        u8 *global_slot = (u8 *)&D_800814A0[2];
        S_func_819A6800_4 *global_object = *(void **)global_slot;
        S_func_819A6800_4 *reloaded_object;
        global_object->unk_102 = 1;
        reloaded_object = *(void * volatile *)global_slot;
        reloaded_object->unk_F4 = 0;

        ((S_func_819A6800_5 *)(out_position))->unk_00.u = ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_00.u;
        ((S_func_819A6800_5 *)(out_position))->unk_04.u = ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_04.u;
        ((S_func_819A6800_5 *)(out_position))->unk_08.u = ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_08.u;

        new_object = func_800A05A4(reloaded_object,
                                D_80082E80[0x24],
                                D_80082E80[0x25],
                                reloaded_object->unk_2A,
                                7);
        owner->unk_60.p = new_object;
        if (new_object == 0) {
            owner->unk_72 = record->unk_24;
            owner->unk_73 = record->unk_25;
            return func_8002413C();
        } else {
            register S_func_819A6800_2 *created_record ASM_REG("$6") =
                ((S_func_819A6800_2 *)((u8 *)new_object - 0x20))->unk_0C;
            owner->unk_72 = created_record->unk_24;
            owner->unk_73 = created_record->unk_25;
        }

        ((volatile S_func_819A6800_1 *)(self))->unk_0A.u++;
        if ((((S_func_819A6800_6 *)(((volatile S_func_819A6800_1 *)(self))->unk_04))->unk_00 & 0x80) == 0) {
            goto return_done;
        }

        counter_object = GLOBAL_OBJECT;
        self->unk_50.u = 10;
        counter_object->unk_A6--;
        counter_object->unk_A8 = self->unk_08;
        new_object = func_8003FD64(0x312, D_80083498);
        record = new_object;
        if (record == 0) {
            goto advance_state;
        }

        if (func_8003DE58(((S_func_819A6800_2 *)(owner_object->unk_0C))->unk_08,
                          owner_object->unk_0C, position_offset, 0) == 0) {
            position_offset[2] = 0;
            position_offset[1] = 0;
            position_offset[0] = 0;
        }
        record->unk_10 = D_800244BC;
        func_8004491C(record, D_80045340);
        sprite = record->unk_0C;

        ((S_func_819A6800_5 *)(record->unk_08))->unk_00.s =
            ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_00.s + ((s32)position_offset[0] << 16);
        ((S_func_819A6800_5 *)(record->unk_08))->unk_04.s =
            ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_04.s + ((s32)position_offset[1] << 16);
        ((S_func_819A6800_5 *)(record->unk_08))->unk_08.s =
            ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_08.s + ((s32)position_offset[2] << 16);

        effect_data = (S_func_819A6800_7 *)((u8 *)record + 0x20);
        effect_data->unk_0C = ((S_func_819A6800_5 *)(record->unk_08))->unk_00.h.unk_02;
        effect_data->unk_0E = ((S_func_819A6800_5 *)(record->unk_08))->unk_04.h.unk_06;
        effect_data->unk_10 = ((S_func_819A6800_5 *)(record->unk_08))->unk_08.h.unk_0A;

        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_10 = 0x20;
        sprite->unk_14 |= 0x0C;
        sprite->unk_00 = D_800DEE38;
        sprite->unk_08 = ((S_func_819A6800_9 *)(D_800DEE38))->unk_04;
        sprite->unk_04 = 0;
        sprite->unk_05 = 0;
        sprite->unk_0C = 0x00606060;
        record->unk_20 = self;
        effect_data->unk_4C = 0;
    }
    return func_80024434();

state4:
    if ((s16)self->unk_50.u > 0) {
        goto return_done;
    }
    {
        s32 mode = func_80053EF0(4);
        if (mode != 2) {
            mode = 0x300;
        } else {
            mode = 0x4300;
        }
        func_800A56E0(mode);
    }
    {
        u16 unused_state = self->unk_0A.u;
        register u16 timer ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(unused_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        timer = 10;
        self->unk_50.u = timer;
    }
    return func_80024438();

state5:
    {
        s16 timer_left = self->unk_50.s;
        if (timer_left == 7) {
            if (owner->unk_60.p != 0) {
                S_func_819A6800_2 *new_object = func_8003FD64(0x302, D_80083498);
                if (new_object != 0) {
                    S_func_819A6800_7 *effect_data = (S_func_819A6800_7 *)((u8 *)new_object + 0x20);
                    u32 target_object;
                    new_object->unk_10 = D_80024810;
                    func_8004491C(new_object, D_80024B20);
                    target_object = owner->unk_60.u;
                    effect_data->unk_3C = 0;
                    effect_data->unk_3E = 0;
                    effect_data->unk_32 = 0x1F;
                    effect_data->unk_30 = 0x1F;
                    effect_data->unk_34 = target_object;
                    effect_data->unk_40 = func_80066460(0, 1, 0x2C0, 0x100);
                    effect_data->unk_42 = func_8006649C(0x60, 0x1F8);
                    effect_data->unk_38 = 0x00404040;
                    new_object->unk_20 = self;
                }
            }
        }
    }
    if (self->unk_50.s == 4) {
        func_8009CE1C(owner->unk_60.p,
                      10,
                      self->unk_09,
                      12,
                      ((S_func_819A6800_4 *)(GLOBAL_OBJECT))->unk_2A,
                      owner,
                      2);
    }
    if ((D_80082E94[0] & 0x8000) == 0 &&
        self->unk_50.s >= 0) {
        goto return_done;
    }
    {
        u16 unused_state;
        register u16 cleanup_delay ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        unused_state = self->unk_0A.u;
        ASM_KEEP(unused_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        cleanup_delay = 20;
        self->unk_50.u = cleanup_delay;
    }
    return func_80024438();

state6:
    if ((s16)self->unk_50.u > 0) {
        goto return_done;
    }

advance_state:
    self->unk_0A.u++;
    return func_8002449C();

state7:
    {
        s16 signed_flags = self->unk_52.s;
        u16 flags = self->unk_52.u;
        if ((signed_flags & 0x8000) != 0) {
            self->unk_52.u = flags & 0x7FFF;
            return func_8002449C();
        }
    }
    {
        S_func_819A6800_10 *globals = (S_func_819A6800_10 *)D_80083460;
        globals->unk_0C = 0;
        globals->unk_0A--;
    }
    ((S_func_819A6800_6 *)((u8 *)self - 2))->unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;

return_done:
    return;
}
