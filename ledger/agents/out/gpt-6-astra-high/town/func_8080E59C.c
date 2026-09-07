#include "common.h"

typedef struct S_8080E59C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void ** unk_20;
    void ** unk_24;
    u8 pad_28[0x48];
    void * unk_70;
    union { void * p32; s16 s16; } unk_74;   /* accessed as both */
    s32 unk_78;
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    s32 unk_88;
    s32 unk_8C;
} S_8080E59C_0;   /* obj in func_8080E59C */

typedef struct S_8080E59C_1 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    s16 unk_06;
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_8080E59C_1;   /* part in func_8080E59C */

typedef struct S_8080E59C_2 {
    s32 unk_00;
    s32 unk_04;
    union { s32 n; volatile s32 v; } unk_08;   /* accessed as both */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8080E59C_2;   /* data in func_8080E59C */

typedef struct S_8080E59C_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8080E59C_3;   /* slot in func_8080E59C */



typedef struct {
    u8 bytes[8];
} Copy8;

typedef union {
    Copy8 copy;
    s16 half[4];
} StackData;

typedef struct {
    s32 word[6];
} Copy24;

extern void *func_800373DC();
extern void func_8003BC18();
extern void func_8006E590();
extern void func_8006E8B8();
extern void func_8023FA58(void *, void *, void *, void *);

extern u8 D_8003D588[];
extern u8 D_8052643C[];
extern Copy8 D_80526440[];
extern u8 D_80529AC4[];
extern u8 D_8052A0A4[];
extern u8 D_8052AE20[];
extern u8 D_805300C4[];
extern u8 D_805300DC[];
extern u8 D_80530668[];

/* Creates and initializes a group of town objects and loads their graphics. */
void func_8080E59C(void)
{
    StackData upload_rect;
    void **child_slots;
    void *object;
    S_8080E59C_1 *render_part;
    S_8080E59C_2 *object_state;
    u8 *child_slot;
    u8 *shared_state;
    s32 child_index;
    s32 unit_scale;

    child_slots = 0;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    upload_rect.copy = D_80526440[0];
    object = func_800373DC(2, D_80526440);
    shared_state = D_8052643C;
    if (object != 0) {
        child_slots = (void **)((u8 *)object + 0x20);
        ((S_8080E59C_0 *)object)->unk_10 = D_8052A0A4;
    }

    object = func_800373DC(0x136);
    *child_slots = object;
    if (object != 0) {
        void *setup_target;
        void *saved_state;
        void *setup_table;
        s32 color;

        func_8003BC18(object, D_8003D588);
        color = 0x808080;
        setup_target = (u8 *)object + 0x2C;
        saved_state = (u8 *)object + 0x78;
        setup_table = D_805300DC;
        ASM_KEEP(setup_target);   /* MATCH pin: retail schedule: same instructions, different order without it */
        object_state = ((S_8080E59C_0 *)object)->unk_08;
        render_part = ((S_8080E59C_0 *)object)->unk_0C;
        ((S_8080E59C_0 *)object)->unk_10 = D_80529AC4;
        ((S_8080E59C_0 *)object)->unk_20 = child_slots;
        render_part->unk_1C = 0x1000;
        render_part->unk_1E = 0x1000;
        render_part->unk_20 = 0x1000;
        render_part->unk_06 = 3;
        render_part->unk_08 = 0x2D;
        render_part->unk_12 = 0;
        render_part->unk_14 = 0;
        render_part->unk_10 = 0;
        render_part->unk_16 = 0;
        render_part->unk_18 = 0;
        render_part->unk_1A = 0;
        render_part->unk_00 = 0;
        render_part->unk_04 = 0;
        render_part->unk_05 = 0;
        render_part->unk_0C = color;
        object_state->unk_00 = 0x03600000;
        object_state->unk_04 = 0x03600000;
        object_state->unk_08.n = 0;
        ASM_KEEP(object_state);   /* MATCH pin: load-bearing for the whole function shape */
        {
            s32 first_word;
            s32 second_word;
            s32 third_word;
            register s32 fourth_word ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */

            first_word = object_state->unk_00;
            second_word = object_state->unk_04;
            third_word = object_state->unk_08.v;
            fourth_word = object_state->unk_0C;
               /* MATCH pin: load-bearing for the whole function shape */
               /* MATCH pin: retail schedule: same instructions, different order without it */
            ((S_8080E59C_0 *)object)->unk_78 = first_word;
            ((S_8080E59C_0 *)object)->unk_7C = second_word;
            ((S_8080E59C_0 *)object)->unk_80 = third_word;
            ((S_8080E59C_0 *)object)->unk_84 = fourth_word;
            first_word = object_state->unk_10;
            second_word = object_state->unk_14;
            ((S_8080E59C_0 *)object)->unk_88 = first_word;
            ((S_8080E59C_0 *)object)->unk_8C = second_word;
            ASM_KEEP(first_word);   /* MATCH pin: load-bearing for the whole function shape */
            ((S_8080E59C_0 *)object)->unk_74.p32 = shared_state;
            func_8023FA58(setup_target, saved_state, setup_table, (void *)third_word);
        }
    }

    child_index = 2;
    unit_scale = 0x1000;
    child_slot = (u8 *)child_slots + 8;
    do {
        object = func_800373DC(0x136);
        ((S_8080E59C_3 *)child_slot)->unk_04 = object;
        if (object != 0) {
            s32 color;
            void *setup_target;
            void *handler;
            void *setup_table;

            func_8003BC18(object, D_8003D588);
            color = 0x808080;
            ASM_KEEP(color);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            setup_target = (u8 *)object + 0x28;
            ASM_KEEP(setup_target);   /* MATCH pin: retail schedule: same instructions, different order without it */
            handler = D_8052AE20;
            ASM_KEEP(handler);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            object_state = ((S_8080E59C_0 *)object)->unk_08;
            render_part = ((S_8080E59C_0 *)object)->unk_0C;
            ASM_KEEP(render_part);   /* MATCH pin: retail schedule: same instructions, different order without it */
            setup_table = D_805300C4;
            ASM_KEEP(setup_table);   /* MATCH pin: retail schedule: same instructions, different order without it */
            ((S_8080E59C_0 *)object)->unk_10 = handler;
            ((S_8080E59C_0 *)object)->unk_24 = child_slots;
            ((S_8080E59C_0 *)object)->unk_74.s16 = child_index;
            render_part->unk_12 = 0;
            render_part->unk_14 = 0;
            render_part->unk_10 = 0;
            render_part->unk_16 = 0;
            render_part->unk_18 = 0;
            render_part->unk_1A = 0;
            render_part->unk_00 = 0;
            render_part->unk_04 = 0;
            render_part->unk_05 = 0;
            render_part->unk_1C = unit_scale;
            render_part->unk_1E = unit_scale;
            render_part->unk_20 = unit_scale;
            render_part->unk_0C = color;
            render_part->unk_08 = *(s32 *)((u8 *)D_805300C4 + 0x54 +
                (((S_8080E59C_0 *)object)->unk_74.s16 << 2));
            object_state->unk_00 = (child_index << 23) + 0x04600000;
            object_state->unk_04 = 0x03600000;
            object_state->unk_08.n = 0;
            ((S_8080E59C_0 *)object)->unk_70 = shared_state;
            func_8023FA58(setup_target, object_state, setup_table, render_part);
        }
        child_index--;
        child_slot -= 4;
    } while (child_index >= 0);

    upload_rect.half[0] = 0x70;
    upload_rect.half[1] = 0x1C1;
    upload_rect.half[2] = 0x30;
    upload_rect.half[3] = 1;
    func_8006E8B8(upload_rect.half, D_80530668);
    func_8006E590(0);
}
