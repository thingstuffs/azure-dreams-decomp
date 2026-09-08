#include "common.h"
#include "records/Rec_D_800814A8.h"


typedef s32 M2C_UNK;

typedef struct S_81988800_0 {
    void * unk_00;
    void * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x44];
    union { u16 u; s16 s; } unk_50;   /* accessed as both */
    union { s16 s; u16 u; } unk_52;   /* accessed as both */
} S_81988800_0;   /* state in BODY_NAME */


typedef struct S_81988800_2 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_81988800_2;   /* out in BODY_NAME */

typedef struct S_81988800_3 {
    void * unk_00;
    s16 unk_04;
    s16 unk_06;
    union { void * p32; u16 u16; } unk_08;   /* accessed as both */
    void * unk_0C;
    u8 pad_10[0x30];
    s16 unk_40;
} S_81988800_3;   /* work in BODY_NAME */

typedef struct S_81988800_4 {
    u8 pad_00[0xA6];
    u16 unk_A6;
    u8 unk_A8;
} S_81988800_4;   /* global in BODY_NAME */

typedef struct S_81988800_5 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
    void * unk_20;
} S_81988800_5;   /* object in BODY_NAME */

typedef struct S_81988800_6 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
} S_81988800_6;   /* spawn_fields in BODY_NAME */

typedef struct S_81988800_7 {
    u8 pad_00[0x10];
    s16 unk_10;
    s16 unk_12;
} S_81988800_7;   /* loop_ptr in BODY_NAME */

typedef struct S_81988800_8 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_81988800_8;   /* base in BODY_NAME */

typedef struct S_81988800_9 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_81988800_9;   /* tail in BODY_NAME */

typedef struct S_81988800_10 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_81988800_10;   /* ((S_81988800_3 *)work)->unk_08.p32 in BODY_NAME */

typedef struct S_81988800_11 {
    u16 unk_00;
} S_81988800_11;   /* ((S_81988800_0 *)state)->unk_04 in BODY_NAME */

typedef struct S_81988800_12 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81988800_12;   /* ((S_81988800_3 *)work)->unk_0C in BODY_NAME */


extern M2C_UNK D_8002441C;
extern M2C_UNK D_80024648;
extern M2C_UNK D_80024B20;
extern M2C_UNK D_80024D58;
extern void *D_80024008[];
extern s32 D_800814A0;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern u16 D_80082E94;
extern s32 D_80083460;
extern u8 D_80083498[];

extern s32 func_8003DE58();
extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_80053EF0();
extern void func_8009CE1C();
extern void *func_800A3F28();
extern void func_800A56E0();

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
    0x8002401C,
    0x00000000,
    0x80024080,
    0x800240E8,
    0x800241E8,
    0x80024224,
    0x800242EC,
};
__asm__(".globl func_80024000\n"
        ".size func_80024000, 1052");
#define BODY_NAME func_8002401C
#else
#define BODY_NAME func_80024000
#endif

/* Advance a timed effect sequence, spawning objects and applying the effect to targets. */
void BODY_NAME(void *state_data, void *position_data)
{
    static void *const phase_labels[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
    };
    s16 offset[3];
    void *object;
    u8 *work;
    register void *state ASM_REG("$18") = state_data;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *source;
    register void *position_ref ASM_REG("$20") = position_data;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *actor;
    u8 *unused_fields;
    u16 timer;

    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    timer = ((S_81988800_0 *)state)->unk_50.u;
    ASM_KEEP(timer);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    source = ((S_81988800_0 *)state)->unk_00;
    ((S_81988800_0 *)state)->unk_50.u = timer - 1;
    work = (u8 *)source - 0x20;
    if (0) {
    }

    (void)phase_labels;
    {
        s32 phase = ((S_81988800_0 *)state)->unk_0A.s;

        if ((u32)phase >= 5) {
            goto done;
        }
        goto *D_80024008[(u32)phase];
    }

jt_c0:
        ((Rec_D_800814A8 *)D_800814A8)->unk_102 = 1;
        ((Rec_D_800814A8 *)D_800814A8)->unk_F4 = 0;
        ((S_81988800_2 *)position_ref)->unk_00 = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_00;
        ((S_81988800_2 *)position_ref)->unk_04 = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_04;
        ((S_81988800_2 *)position_ref)->unk_08.at00.v = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_08;
        ((S_81988800_0 *)state)->unk_0A.u++;
jt_c1: {
        u8 *spawn_data;

        if (0) {
        }
        if (((S_81988800_11 *)(((S_81988800_0 *)state)->unk_04))->unk_00 & 0x80) {
            actor = D_800814A8;
            ((S_81988800_0 *)state)->unk_50.u = 10;
            ((S_81988800_4 *)actor)->unk_A6--;
            ((S_81988800_4 *)actor)->unk_A8 = ((S_81988800_0 *)state)->unk_08;

            object = func_8003FD64(0x302, D_80083498);
            if (object != 0) {
                if (func_8003DE58(((S_81988800_12 *)(((S_81988800_3 *)work)->unk_0C))->unk_08,
                                   ((S_81988800_3 *)work)->unk_0C, offset, 0) == 0) {
                    offset[2] = 0;
                    offset[1] = 0;
                    offset[0] = 0;
                }
                ((S_81988800_5 *)object)->unk_10 = &D_80024648;
                func_8004491C(object, &D_8002441C);
                ((S_81988800_5 *)object)->unk_20 = state;
                spawn_data = (u8 *)object + 0x20;

                ((S_81988800_2 *)position_ref)->unk_00 = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_00 +
                                      ((s32)offset[0] << 16);
                ((S_81988800_6 *)spawn_data)->unk_1C = ((S_81988800_2 *)position_ref)->unk_00;
                ((S_81988800_2 *)position_ref)->unk_04 = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_04 +
                                      ((s32)offset[1] << 16);
                ((S_81988800_6 *)spawn_data)->unk_20 = ((S_81988800_2 *)position_ref)->unk_04;
                ((S_81988800_2 *)position_ref)->unk_08.at00.v = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_08 +
                                      ((s32)offset[2] << 16);
                ((S_81988800_6 *)spawn_data)->unk_24 = ((S_81988800_2 *)position_ref)->unk_08.at00.v;
            }
            ((S_81988800_0 *)state)->unk_0A.u++;
        }
        goto done;
    }

jt_c2: {
        s32 effect_id;
        s32 variant;

        if (0) {
        }
        if (((S_81988800_0 *)state)->unk_50.s <= 0) {
            variant = func_80053EF0(4);
            effect_id = 0x4300;
            if (variant != 2) {
                effect_id = 0x300;
            }
            func_800A56E0(effect_id);
            ((S_81988800_0 *)state)->unk_50.u = 13;
            ((S_81988800_0 *)state)->unk_0A.u++;
        }
        goto done;
    }

jt_c3: {
        register u8 *settings ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        register u8 *entry_ptr ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 entry_index;

        if (0) {
        }
        if (((S_81988800_0 *)state)->unk_50.s <= 0) {
            object = func_8003FD64(0x302, D_80083498);
            if (object != 0) {
                ((S_81988800_5 *)object)->unk_10 = &D_80024B20;
                func_8004491C(object, &D_80024D58);
                settings = D_80082E80;
                offset[0] = (((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_u16 >> 9) & 7;
                work = (u8 *)object + 0x20;
                ((S_81988800_3 *)work)->unk_04 = (settings[0x24] << 6) + 0x20;
                ((S_81988800_3 *)work)->unk_06 = (settings[0x25] << 6) + 0x20;
                ((S_81988800_3 *)work)->unk_08.u16 = ((S_81988800_2 *)position_ref)->unk_08.at02.v;
                entry_ptr = (u8 *)object + 0x4A;
                for (entry_index = 7; entry_index >= 0; entry_index--, entry_ptr -= 6) {
                    ((S_81988800_7 *)entry_ptr)->unk_12 = 0;
                    ((S_81988800_7 *)entry_ptr)->unk_10 = 0;
                    ASM_KEEP(entry_index);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                }
                ((S_81988800_3 *)work)->unk_00 = state;
                ((S_81988800_3 *)work)->unk_40 = 0;
            }
            ((S_81988800_0 *)state)->unk_50.u = 0x3D;
            ((S_81988800_0 *)state)->unk_0A.u++;
        }
        goto done;
    }

jt_c4: {
        if (((S_81988800_0 *)state)->unk_50.s == 8) {
            object = D_800814A8;
            if (object != 0) {
                u8 *data_base;

                position_ref = object;
                data_base = (u8 *)0x80080000;
                ASM_KEEP(data_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                work = data_base + 0x2E80;
loop:
                object = func_800A3F28(work[0x24], work[0x25], position_ref, object);
                if (object == 0) {
                    goto loop_done;
                }
                if (((S_81988800_5 *)object)->unk_1C & 0x2000) {
                    goto loop;
                }
                func_8009CE1C(object, 0x10, ((S_81988800_0 *)state)->unk_09, 10,
                             ((S_81988800_8 *)source)->unk_2A, source, 2);
                goto loop;
loop_done:
                ;
            }
        }

        if ((D_80082E94 & 0x8000) || ((S_81988800_0 *)state)->unk_50.s < 0) {
            if (((S_81988800_0 *)state)->unk_52.s & 0x8000) {
                ((S_81988800_0 *)state)->unk_52.u &= 0x7FFF;
            } else {
                u8 *cleanup_state;

                cleanup_state = (u8 *)&D_80083460;
                if (0) {
                }
                ((S_81988800_9 *)cleanup_state)->unk_0C = 0;
                ((S_81988800_9 *)cleanup_state)->unk_0A--;
                (*(u16 *)((u8 *)state + -2)) |= 0x8000;
                D_800814A0 |= 0x8000;
            }
        }
        goto done;
    }

done:
    ;
}
