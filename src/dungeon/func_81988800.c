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

void BODY_NAME(void *arg0, void *arg1)
{
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
    };
    s16 position[3];
    void *object;
    u8 *work;
    register void *state ASM_REG("$18") = arg0;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *base;
    register void *out ASM_REG("$20") = arg1;   /* MATCH pin: load-bearing for the whole function shape */
    void *global;
    u8 *fields;
    u16 timer;

    ASM_KEEP(state);   /* MATCH pin: retail schedule: same instructions, different order without it */
    timer = ((S_81988800_0 *)state)->unk_50.u;
    ASM_KEEP(timer);   /* MATCH pin: retail schedule: same instructions, different order without it */
    base = ((S_81988800_0 *)state)->unk_00;
    ((S_81988800_0 *)state)->unk_50.u = timer - 1;
    work = (u8 *)base - 0x20;
    if (0) {
    }

    (void)jt_keep;
    {
        s32 dispatch = ((S_81988800_0 *)state)->unk_0A.s;

        if ((u32)dispatch >= 5) {
            goto done;
        }
        goto *D_80024008[(u32)dispatch];
    }

jt_c0:
        ((Rec_D_800814A8 *)D_800814A8)->unk_102 = 1;
        ((Rec_D_800814A8 *)D_800814A8)->unk_F4 = 0;
        ((S_81988800_2 *)out)->unk_00 = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_00;
        ((S_81988800_2 *)out)->unk_04 = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_04;
        ((S_81988800_2 *)out)->unk_08.at00.v = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_08;
        ((S_81988800_0 *)state)->unk_0A.u++;
jt_c1: {
        u8 *spawn_fields;

        if (0) {
        }
        if (((S_81988800_11 *)(((S_81988800_0 *)state)->unk_04))->unk_00 & 0x80) {
            global = D_800814A8;
            ((S_81988800_0 *)state)->unk_50.u = 10;
            ((S_81988800_4 *)global)->unk_A6--;
            ((S_81988800_4 *)global)->unk_A8 = ((S_81988800_0 *)state)->unk_08;

            object = func_8003FD64(0x302, D_80083498);
            if (object != 0) {
                if (func_8003DE58(((S_81988800_12 *)(((S_81988800_3 *)work)->unk_0C))->unk_08,
                                   ((S_81988800_3 *)work)->unk_0C, position, 0) == 0) {
                    position[2] = 0;
                    position[1] = 0;
                    position[0] = 0;
                }
                ((S_81988800_5 *)object)->unk_10 = &D_80024648;
                func_8004491C(object, &D_8002441C);
                ((S_81988800_5 *)object)->unk_20 = state;
                spawn_fields = (u8 *)object + 0x20;

                ((S_81988800_2 *)out)->unk_00 = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_00 +
                                      ((s32)position[0] << 16);
                ((S_81988800_6 *)spawn_fields)->unk_1C = ((S_81988800_2 *)out)->unk_00;
                ((S_81988800_2 *)out)->unk_04 = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_04 +
                                      ((s32)position[1] << 16);
                ((S_81988800_6 *)spawn_fields)->unk_20 = ((S_81988800_2 *)out)->unk_04;
                ((S_81988800_2 *)out)->unk_08.at00.v = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_08 +
                                      ((s32)position[2] << 16);
                ((S_81988800_6 *)spawn_fields)->unk_24 = ((S_81988800_2 *)out)->unk_08.at00.v;
            }
            ((S_81988800_0 *)state)->unk_0A.u++;
        }
        goto done;
    }

jt_c2: {
        s32 choice;
        s32 result;

        if (0) {
        }
        if (((S_81988800_0 *)state)->unk_50.s <= 0) {
            result = func_80053EF0(4);
            choice = 0x4300;
            if (result != 2) {
                choice = 0x300;
            }
            func_800A56E0(choice);
            ((S_81988800_0 *)state)->unk_50.u = 13;
            ((S_81988800_0 *)state)->unk_0A.u++;
        }
        goto done;
    }

jt_c3: {
        register u8 *settings ASM_REG("$3");   /* MATCH pin: retail immediate-load split depends on it */
        register u8 *loop_ptr ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
        s32 counter;

        if (0) {
        }
        if (((S_81988800_0 *)state)->unk_50.s <= 0) {
            object = func_8003FD64(0x302, D_80083498);
            if (object != 0) {
                ((S_81988800_5 *)object)->unk_10 = &D_80024B20;
                func_8004491C(object, &D_80024D58);
                settings = D_80082E80;
                position[0] = (((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_u16 >> 9) & 7;
                work = (u8 *)object + 0x20;
                ((S_81988800_3 *)work)->unk_04 = (settings[0x24] << 6) + 0x20;
                ((S_81988800_3 *)work)->unk_06 = (settings[0x25] << 6) + 0x20;
                ((S_81988800_3 *)work)->unk_08.u16 = ((S_81988800_2 *)out)->unk_08.at02.v;
                loop_ptr = (u8 *)object + 0x4A;
                for (counter = 7; counter >= 0; counter--, loop_ptr -= 6) {
                    ((S_81988800_7 *)loop_ptr)->unk_12 = 0;
                    ((S_81988800_7 *)loop_ptr)->unk_10 = 0;
                    ASM_KEEP(counter);   /* MATCH pin: retail schedule: same instructions, different order without it */
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
                u8 *table;

                out = object;
                table = (u8 *)0x80080000;
                ASM_KEEP(table);   /* MATCH pin: load-bearing for the whole function shape */
                work = table + 0x2E80;
loop:
                object = func_800A3F28(work[0x24], work[0x25], out, object);
                if (object == 0) {
                    goto loop_done;
                }
                if (((S_81988800_5 *)object)->unk_1C & 0x2000) {
                    goto loop;
                }
                func_8009CE1C(object, 0x10, ((S_81988800_0 *)state)->unk_09, 10,
                             ((S_81988800_8 *)base)->unk_2A, base, 2);
                goto loop;
loop_done:
                ;
            }
        }

        if ((D_80082E94 & 0x8000) || ((S_81988800_0 *)state)->unk_50.s < 0) {
            if (((S_81988800_0 *)state)->unk_52.s & 0x8000) {
                ((S_81988800_0 *)state)->unk_52.u &= 0x7FFF;
            } else {
                u8 *tail;

                tail = (u8 *)&D_80083460;
                if (0) {
                }
                ((S_81988800_9 *)tail)->unk_0C = 0;
                ((S_81988800_9 *)tail)->unk_0A--;
                (*(u16 *)((u8 *)state + -2)) |= 0x8000;
                D_800814A0 |= 0x8000;
            }
        }
        goto done;
    }

done:
    ;
}
