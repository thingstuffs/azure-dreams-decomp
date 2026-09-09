#include "common.h"

typedef struct S_800259D8_0_pre {
    u16 unk_00;
} S_800259D8_0_pre;   /* the 0x2 bytes before arg0 in func_800259D8, addressed as arg0[-1] */

typedef struct S_800259D8_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x68];
    union { u16 u; s16 s; } unk_74;   /* accessed as both */
    union { u16 u; s16 s; } unk_76;   /* accessed as both */
    union { u16 u; s16 s; } unk_78;   /* accessed as both */
    u8 unk_7A;
    u8 pad_7B[0x1];
    union { s16 s; u16 u; } unk_7C;   /* accessed as both */
    u8 pad_7E[0x2];
    s16 unk_80;
    u8 pad_82[0x2];
    union { u16 u; s16 s; } unk_84;   /* accessed as both */
    u8 pad_86[0x2];
    s16 unk_88;
    u8 pad_8A[0x12];
    u16 unk_9C;
    u8 pad_9E[0x2];
    s16 unk_A0;
    u8 pad_A2[0x8];
    u8 unk_AA;
    u8 pad_AB[0x3];
    u8 unk_AE;
    u8 unk_AF;
} S_800259D8_0;   /* arg0 in func_800259D8 */

typedef struct S_800259D8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800259D8_1;   /* base in func_800259D8 */

typedef struct S_800259D8_2 {
    u8 pad_00[0x8];
    void * unk_08;
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { s8 v; } at00p; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x1]; s8 v; } at01u; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x2]; s8 v; } at02u; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800259D8_2;   /* arg2 in func_800259D8 */

typedef struct S_800259D8_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800259D8_3_pre;   /* the 0x14 bytes before obj in func_800259D8, addressed as obj[-1] */

typedef struct S_800259D8_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    u8 pad_73[0x15];
    u16 unk_88;
} S_800259D8_3;   /* obj in func_800259D8 */

typedef struct S_800259D8_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800259D8_4;   /* arg1 in func_800259D8 */

typedef struct S_800259D8_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x6];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x1A];
    void * unk_38;
    void * unk_3C;
    void * unk_40;
    void * unk_44;
    void * unk_48;
    void * unk_4C;
} S_800259D8_5;   /* entry in func_800259D8 */

typedef struct S_800259D8_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800259D8_6;   /* resident_work in func_800259D8 */

typedef struct S_800259D8_7 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800259D8_7;   /* spawn in func_800259D8 */

typedef struct S_800259D8_8 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800259D8_8;   /* work in func_800259D8 */

typedef struct S_800259D8_9 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800259D8_9;   /* dst in func_800259D8 */

typedef struct S_800259D8_10_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800259D8_10_pre;   /* the 0x14 bytes before fade_node in func_800259D8, addressed as fade_node[-1] */

typedef struct S_800259D8_10 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800259D8_10;   /* fade_node in func_800259D8 */

typedef struct S_800259D8_11 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800259D8_11;   /* fade_entry in func_800259D8 */

typedef struct S_800259D8_12_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800259D8_12_pre;   /* the 0x14 bytes before tail_node in func_800259D8, addressed as tail_node[-1] */

typedef struct S_800259D8_12 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800259D8_12;   /* tail_node in func_800259D8 */

typedef struct S_800259D8_13 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800259D8_13;   /* ((S_800259D8_1 *)base)->unk_0C in func_800259D8 */

typedef struct S_800259D8_14 {
    u16 unk_00;
} S_800259D8_14;   /* ((S_800259D8_0 *)arg0)->unk_04 in func_800259D8 */

typedef struct S_800259D8_15_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800259D8_15_pre;   /* the 0x18 bytes before ((S_800259D8_3 *)obj)->unk_60 in func_800259D8, addressed as ((S_800259D8_3 *)obj)->unk_60[-1] */

typedef struct S_800259D8_15 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_800259D8_15;   /* ((S_800259D8_3 *)obj)->unk_60 in func_800259D8 */



typedef struct {
    u8 bytes[32];
} Copy32;

typedef struct {
    u8 bytes[12];
} Copy12;

typedef struct {
    s16 x;
    s16 y;
    u16 z;
} Vec3s;

typedef union {
    u16 u;
    s16 s;
} H16;

typedef struct {
    H16 x;
    H16 y;
} Pair;

/* These resident data/code addresses are not present in the catalog for this
 * cold overlay row; the binds retain real link-resolved symbols. */
__asm__(".set D_80024058, 0x80024058");
__asm__(".set D_80026634, 0x80026634");
__asm__(".set D_80026640, 0x80026640");
__asm__(".set D_8002664C, 0x8002664C");
__asm__(".set D_80026664, 0x80026664");
__asm__(".set D_80024704, 0x80024704");
__asm__(".set D_80024FD4, 0x80024FD4");
__asm__(".set D_80025470, 0x80025470");
__asm__(".set D_8006CCD8, 0x8006CCD8");
__asm__(".set D_8006CCE8, 0x8006CCE8");
__asm__(".set D_800DDC40, 0x800DDC40");
__asm__(".set D_8008346C, 0x8008346C");

__asm__(".set func_80026430, 0x80026430");

extern Copy32 D_80024058;
extern Copy12 D_80026634;
extern Copy12 D_80026640;
extern Copy12 D_8002664C;
extern s16 D_80026664[8];
extern u8 D_80045340[];
extern u8 D_80024704[];
extern u8 D_80025814[];
extern u8 D_80024FD4[];
extern u8 D_80025470[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_800DDC40[];
extern s32 D_8008346C[3];
extern s32 D_800814A0[3];

extern s32 func_8003DF74(void *, void *, Vec3s *, s32);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);
extern s32 func_800A4778(u16, u16, s16, void *);
extern void func_800A56E0(s32);
extern void func_80025338(void *, s32, s32, s32, s32, s32, s32);
extern void func_80024098(void *, u8, void *);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);

extern void func_80026430(void) __attribute__((noreturn));

void func_800259D8(void *in0, void *in1, void *in2)
{
    Vec3s delta;
    Copy32 copy;
    register void *obj ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *base;
    void *entry;
    void *node;
    S_800259D8_8 *work;
    void *dst;
    u32 state;
    u16 old_count;
    s16 count;
    s32 result;
    s32 index;
    s32 value;
    register s32 tail_a ASM_REG("$2");   /* MATCH: both state transitions pass their loaded state in v0. */
    register s32 phase ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 i ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register void *arg0 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register void *arg1 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    S_800259D8_2 *arg2;
    void *spawn_code;

    arg0 = in0;
    arg1 = in1;
    arg2 = in2;

    ASM_KEEP_NV(arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(arg1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    obj = ((S_800259D8_0 *)arg0)->unk_00;
    copy = D_80024058;
    spawn_code = D_80025814;
    ASM_USE(dst);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    state = ((S_800259D8_0 *)arg0)->unk_0A.s;
    base = (u8 *)obj - 0x20;
    entry = ((S_800259D8_1 *)base)->unk_08;
    switch (state) {
    case 0:
    {
        s32 setup;
        setup = 0x00808080;
        arg2->unk_0C.at00.v = setup;
        setup = 0x1000;
        arg2->unk_1E = setup;
        arg2->unk_1C = setup;
    }
    *(Copy12 *)((u8 *)arg0 + 0xA2) = D_80026634;
    {
        s32 init_value;
        u16 init_count;
        arg2->unk_08 = (u8 *)arg0 + 0xA2;
        init_value = (((S_800259D8_3 *)obj)->unk_2A >> 9) & 7;
        D_80026664[0] = 1;
        init_count = ((S_800259D8_0 *)arg0)->unk_0A.u + 1;
        ((S_800259D8_0 *)arg0)->unk_80 = init_value;
        ((S_800259D8_0 *)arg0)->unk_0A.u = init_count;
    }
    case 1:
    result = func_8003DF74(
        ((S_800259D8_13 *)(((S_800259D8_1 *)base)->unk_0C))->unk_08,
        ((S_800259D8_1 *)base)->unk_0C, &delta, 0);
    if (result == 0) {
        if (!(((S_800259D8_13 *)(((S_800259D8_1 *)base)->unk_0C))->unk_14 & 0x8000U)) {
            goto done;
        }
    }
    {
    u16 z_value;
    register s32 tail_z ASM_REG("$2");   /* MATCH: both z arms merge into the retail v0 store. */
    ((S_800259D8_4 *)arg1)->unk_00.at02.v = ((S_800259D8_5 *)entry)->unk_00.at02.v;
    ((S_800259D8_4 *)arg1)->unk_04.at02.v = ((S_800259D8_5 *)entry)->unk_04.at02.v;
    z_value = ((S_800259D8_5 *)entry)->unk_08.at02.v;
    ((S_800259D8_4 *)arg1)->unk_08.at02.v = z_value;
    if (!(((S_800259D8_13 *)(((S_800259D8_1 *)base)->unk_0C))->unk_14 & 0x8000U)) {
        ((S_800259D8_4 *)arg1)->unk_00.at02.v += delta.x;
        ((S_800259D8_4 *)arg1)->unk_04.at02.v += delta.y;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        tail_z = ((S_800259D8_4 *)arg1)->unk_08.at02.v;
        tail_z = tail_z + delta.z;
    } else {
L0_adjust_z:
        ASM_SCHED_BARRIER();   /* MATCH: retain the alternate z calculation's scheduling boundary. */
        tail_z = z_value - 0x40;
    }
    ((S_800259D8_4 *)arg1)->unk_08.at02u.v = tail_z;
    }
    if (!(((S_800259D8_14 *)(((S_800259D8_0 *)arg0)->unk_04))->unk_00 & 0x80U)) {
        goto done;
    }
    if (!(((S_800259D8_0 *)arg0)->unk_7A & 4U)) {
        func_8004491C((u8 *)arg0 - 0x20, D_80045340);
        arg2->unk_10 = 0x20;
        arg2->unk_0C.at02.v = 0x80;
        arg2->unk_0C.at01.v = 0x80;
        arg2->unk_0C.at00u.v = 0x80;
        arg2->unk_14 |= 0xC;
        ((S_800259D8_0 *)arg0)->unk_7A |= 4;
    }
    if (((S_800259D8_3 *)obj)->unk_60 != 0) {
        void *resident_work;
        entry = ((S_800259D8_15_pre *)(((S_800259D8_3 *)obj)->unk_60))[-1].unk_00;
        ((S_800259D8_0 *)arg0)->unk_74.u = ((S_800259D8_5 *)entry)->unk_00.at02u.v;
        ((S_800259D8_0 *)arg0)->unk_76.u = ((S_800259D8_5 *)entry)->unk_04.at02u.v;
        {
            s32 depth_bias;
            s32 resident_value;
            depth_bias = D_800DDC40[((S_800259D8_15 *)(((S_800259D8_3 *)obj)->unk_60))->unk_13];
            resident_value = ((S_800259D8_5 *)entry)->unk_08.at02.v - depth_bias - 0x60;
            ((S_800259D8_0 *)arg0)->unk_78.u = resident_value;
        }
        resident_work = ((S_800259D8_3_pre *)obj)[-1].unk_00;
        ((S_800259D8_0 *)arg0)->unk_AE = ((S_800259D8_6 *)resident_work)->unk_24 +
            D_8006CCD8[((S_800259D8_0 *)arg0)->unk_80 << 1];
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ((S_800259D8_0 *)arg0)->unk_AF = ((S_800259D8_6 *)resident_work)->unk_25 +
            D_8006CCE8[((S_800259D8_0 *)arg0)->unk_80 << 1];
        entry = ((S_800259D8_15_pre *)(((S_800259D8_3 *)obj)->unk_60))[-1].unk_00;
        {
            register s32 resident_delta ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s32 resident_copy;
            if (((S_800259D8_3 *)obj)->unk_72 != ((S_800259D8_6 *)resident_work)->unk_24) {
                resident_delta = ((S_800259D8_4 *)arg1)->unk_00.at02.v;
                resident_delta = resident_delta - ((S_800259D8_5 *)entry)->unk_00.at02.v;
                phase = ((S_800259D8_0 *)arg0)->unk_80 << 2;   /* MATCH: the x-table index occupies v0 only in this arm. */
                resident_copy = *(s16 *)((u8 *)&copy + phase);
                if (resident_delta < 0) {
                    resident_delta = -resident_delta;
                }
                ASM_USE2(resident_delta, resident_copy);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            } else {
                Pair *cp;
                s32 cidx;
                resident_delta = ((S_800259D8_4 *)arg1)->unk_04.at02.v;
                cidx = ((S_800259D8_0 *)arg0)->unk_80 << 2;
                resident_delta = resident_delta - ((S_800259D8_5 *)entry)->unk_04.at02.v;
                cp = (Pair *)&copy;
                resident_copy = ((Pair *)((u8 *)cp + cidx))->y.u;
                if (resident_delta < 0) {
                    resident_delta = -resident_delta;
                }
                resident_copy = (s32)((u32)resident_copy << 16) >> 16;
            }
            if (resident_copy < 0) {
                resident_copy = -resident_copy;
            }
            resident_delta = resident_delta / resident_copy;
            ((S_800259D8_0 *)arg0)->unk_7C.s = resident_delta;
        }
        goto L_calc2;
    }
    {
    ((S_800259D8_0 *)arg0)->unk_7C.s = 0x80;
    ((S_800259D8_0 *)arg0)->unk_74.s = ((S_800259D8_4 *)arg1)->unk_00.at02u.v +
        (((Pair *)((u8 *)&copy + (((S_800259D8_0 *)arg0)->unk_80 << 2)))->x.u << 7);
    ((S_800259D8_0 *)arg0)->unk_76.s = ((S_800259D8_4 *)arg1)->unk_04.at02u.v +
        (((Pair *)((u8 *)&copy + (((S_800259D8_0 *)arg0)->unk_80 << 2)))->y.u *
         ((S_800259D8_0 *)arg0)->unk_7C.u);
    ((S_800259D8_0 *)arg0)->unk_78.s = ((S_800259D8_3 *)obj)->unk_88 - 0x50;
    }
L_calc2:
    {
    Pair *cp = (Pair *)&copy;
    ((S_800259D8_4 *)arg1)->unk_0C =
        ((Pair *)((u8 *)cp + (((S_800259D8_0 *)arg0)->unk_80 << 2)))->x.s << 16;
    ((S_800259D8_4 *)arg1)->unk_10 =
        ((Pair *)((u8 *)cp + (((S_800259D8_0 *)arg0)->unk_80 << 2)))->y.u << 16;
    }
    ((S_800259D8_4 *)arg1)->unk_14 =
        ((((S_800259D8_0 *)arg0)->unk_78.s << 16) - ((S_800259D8_4 *)arg1)->unk_08.at00.v) /
        ((S_800259D8_0 *)arg0)->unk_7C.s;
    ((S_800259D8_0 *)arg0)->unk_84.u = 0;
    ((S_800259D8_0 *)arg0)->unk_9C = 55;
    ((S_800259D8_0 *)arg0)->unk_0A.u++;
    i = 0;
    do {
        void *spawn;
        spawn = func_8003FC64(0x12);
        if (spawn != 0) {
                entry = (u8 *)spawn + 0x20;
            {
            void *sp0 = spawn;
            u8 *tbl = D_80024704;
                ((S_800259D8_5 *)entry)->unk_38 = obj;
                ((S_800259D8_5 *)entry)->unk_44 = arg1;
                ((S_800259D8_5 *)entry)->unk_48 = arg2;
                ((S_800259D8_5 *)entry)->unk_4C = arg0;
            ((S_800259D8_7 *)spawn)->unk_10 = spawn_code;
            func_8004491C(sp0, tbl);
            }
            work = ((S_800259D8_7 *)spawn)->unk_0C;
            work->unk_14 |= 0xC;
            work->unk_10 = 0x20;
            dst = ((S_800259D8_7 *)spawn)->unk_08;
            ASM_KEEP_NV(i);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            ((S_800259D8_5 *)entry)->unk_08.at02u.v = (func_80069EF8() & 7) + 12;
            ((S_800259D8_5 *)entry)->unk_0C = func_80069EF8() & 0xFFF;
            work->unk_16 = (func_80069EF8() & 0xFF) << 4;
            work->unk_18 = (func_80069EF8() & 0xFF) << 4;
            work->unk_1A = (func_80069EF8() & 0xFF) << 4;
            value = func_80064584(((S_800259D8_5 *)entry)->unk_0C);
            ((S_800259D8_9 *)dst)->unk_00 = (((S_800259D8_5 *)entry)->unk_08.at02u.v * value) << 4;
            value = func_800644B8(((S_800259D8_5 *)entry)->unk_0C);
            ((S_800259D8_9 *)dst)->unk_04 = (((S_800259D8_5 *)entry)->unk_08.at02u.v * value) << 4;
            ((S_800259D8_9 *)dst)->unk_08.at02.v = ((S_800259D8_4 *)arg1)->unk_08.at02.v;
            work = ((S_800259D8_7 *)spawn)->unk_0C;
            {
                s32 scale1;
                scale1 = 0x1000;
                work->unk_1E = scale1;
                work->unk_1C = scale1;
            }
            {
                s32 alpha;
                alpha = 0x80;
                work->unk_0E = alpha;
                work->unk_0D = alpha;
                work->unk_0C = alpha;
            }
            *(Copy12 *)((u8 *)spawn + 0x4C) = D_80026640;
            work->unk_08 = (u8 *)spawn + 0x4C;
        }
        i++;
        if (i < 8) {
            ASM_USE2(i, spawn);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            continue;
        }
    } while (i < 8);
    goto done;

    case 2:
    if (((S_800259D8_0 *)arg0)->unk_A0 == 0) {
        ((S_800259D8_0 *)arg0)->unk_A0 = 1;
        phase = ((S_800259D8_0 *)arg0)->unk_AA + 0x18;
    } else {
        phase = ((S_800259D8_0 *)arg0)->unk_AA - 0x18;
        ((S_800259D8_0 *)arg0)->unk_A0 = 0;
    }
    ((S_800259D8_0 *)arg0)->unk_AA = phase;
    result = func_800A4778(((S_800259D8_4 *)arg1)->unk_00.at02u.v, ((S_800259D8_4 *)arg1)->unk_04.at02u.v,
                           ((S_800259D8_4 *)arg1)->unk_08.at02u.v, ((S_800259D8_3 *)obj)->unk_60);
    if ((result << 16) != 0) {
        goto L1_state7;
    }
    node = ((S_800259D8_3 *)obj)->unk_60;
    if (node == 0) {
        arg2->unk_0C.at00u.v -= 4;
        arg2->unk_0C.at01.v -= 4;
        arg2->unk_0C.at02.v -= 4;
        if (arg2->unk_0C.at00u.v == 0) {
            ((S_800259D8_0 *)arg0)->unk_7C.u = 1;
        }
    }
    count = ((S_800259D8_0 *)arg0)->unk_7C.u - 1;
    ((S_800259D8_0 *)arg0)->unk_7C.u = count;
    if (count > 0) {
        goto L1_calc;
    }
    if (((S_800259D8_3 *)obj)->unk_60 != 0) {
        ((S_800259D8_0 *)arg0)->unk_0A.u = 3;
        ((S_800259D8_0 *)arg0)->unk_84.u = 0;
        entry = ((S_800259D8_15_pre *)(((S_800259D8_3 *)obj)->unk_60))[-1].unk_00;
        ((S_800259D8_4 *)arg1)->unk_00.at02u.v = ((S_800259D8_5 *)entry)->unk_00.at02u.v;
        ((S_800259D8_4 *)arg1)->unk_04.at02u.v = ((S_800259D8_5 *)entry)->unk_04.at02u.v;
        ((S_800259D8_4 *)arg1)->unk_08.at02.v = ((S_800259D8_0 *)arg0)->unk_78.u;
        func_800A56E0(0x300);
        goto done;
    }
L1_state7:
    ((S_800259D8_0 *)arg0)->unk_0A.u = 7;
    ((S_800259D8_0 *)arg0)->unk_84.u = 0;
    arg2->unk_0C.at02.v = 0;
    arg2->unk_0C.at01.v = 0;
    arg2->unk_0C.at00u.v = 0;
    goto done;

L1_calc:
    ((S_800259D8_4 *)arg1)->unk_0C =
        ((((S_800259D8_0 *)arg0)->unk_74.s << 16) - ((S_800259D8_4 *)arg1)->unk_00.at00.v) / count;
    ((S_800259D8_4 *)arg1)->unk_10 =
        ((((S_800259D8_0 *)arg0)->unk_76.s << 16) - ((S_800259D8_4 *)arg1)->unk_04.at00.v) /
        ((S_800259D8_0 *)arg0)->unk_7C.s;
    ((S_800259D8_4 *)arg1)->unk_14 =
        ((((S_800259D8_0 *)arg0)->unk_78.s << 16) - ((S_800259D8_4 *)arg1)->unk_08.at00.v) /
        ((S_800259D8_0 *)arg0)->unk_7C.s;
    ((S_800259D8_4 *)arg1)->unk_00.at00.v += ((S_800259D8_4 *)arg1)->unk_0C;
    ((S_800259D8_4 *)arg1)->unk_04.at00.v += ((S_800259D8_4 *)arg1)->unk_10;
    ((S_800259D8_4 *)arg1)->unk_08.at00.v += ((S_800259D8_4 *)arg1)->unk_14;
    goto done;

    case 3:
    if (((S_800259D8_0 *)arg0)->unk_A0 == 0) {
        ((S_800259D8_0 *)arg0)->unk_A0 = 1;
        phase = ((S_800259D8_0 *)arg0)->unk_AA + 0x18;
    } else {
        phase = ((S_800259D8_0 *)arg0)->unk_AA - 0x18;
        ((S_800259D8_0 *)arg0)->unk_A0 = 0;
    }
    ((S_800259D8_0 *)arg0)->unk_AA = phase;
    {
    void *spawn;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    spawn = func_8003FC64(0x12);
    if (spawn != 0) {
        entry = (u8 *)spawn + 0x20;
        ((S_800259D8_5 *)entry)->unk_00.at02.v = 0;
        ((S_800259D8_5 *)entry)->unk_38 = obj;
        ((S_800259D8_5 *)entry)->unk_3C = ((S_800259D8_3 *)obj)->unk_60;
        ((S_800259D8_5 *)entry)->unk_40 = arg0;
        ((S_800259D8_5 *)entry)->unk_08.at02u.v = 0x0C;
        ((S_800259D8_5 *)entry)->unk_0C = 8;
        ((S_800259D8_5 *)entry)->unk_0E = 0;
        ((S_800259D8_5 *)entry)->unk_10 = 0;
        ((S_800259D8_5 *)entry)->unk_12 = 0;
        ((S_800259D8_5 *)entry)->unk_1C = 0;
        ((S_800259D8_5 *)entry)->unk_1A = 0x40;
        entry = ((S_800259D8_15_pre *)(((S_800259D8_3 *)obj)->unk_60))[-1].unk_00;
        ((S_800259D8_7 *)spawn)->unk_10 = D_80025470;
        func_8004491C(spawn, D_80024FD4);
        work = ((S_800259D8_7 *)spawn)->unk_0C;
        work->unk_10 = 0x20;
        work->unk_14 |= 0x000C;
        dst = ((S_800259D8_7 *)spawn)->unk_08;
        ((S_800259D8_9 *)dst)->unk_00 = ((S_800259D8_5 *)entry)->unk_00.at00.v;
        ((S_800259D8_9 *)dst)->unk_04 = ((S_800259D8_5 *)entry)->unk_04.at00.v;
        index = ((S_800259D8_3 *)obj)->unk_60 != 0;
        index = ((S_800259D8_15 *)(((S_800259D8_3 *)obj)->unk_60))->unk_13;
        ((S_800259D8_9 *)dst)->unk_08.at00.v = ((S_800259D8_5 *)entry)->unk_08.at00.v -
            (D_800DDC40[index] << 15);
        work = ((S_800259D8_7 *)spawn)->unk_0C;
        {
            s16 scale2 = 0x1000;
            work->unk_1E = scale2;
            work->unk_1C = scale2;
        }
        work->unk_0E = 0x80;
        work->unk_0D = 0x80;
        work->unk_0C = 0x80;
        *(Copy12 *)((u8 *)spawn + 0x4C) = D_8002664C;
        work->unk_08 = (u8 *)spawn + 0x4C;
    }
    }
        ((S_800259D8_0 *)arg0)->unk_0A.u = 4;
    ((S_800259D8_0 *)arg0)->unk_84.u = 0;
    goto done;

    case 4:
    count = ((S_800259D8_0 *)arg0)->unk_84.u + 1;
    ((S_800259D8_0 *)arg0)->unk_84.u = count;
    if (count < 30) {
        arg2->unk_0C.at00p.v = ((30 - ((S_800259D8_0 *)arg0)->unk_84.s) * 0x80) / 30;
        arg2->unk_0C.at01u.v = ((30 - ((S_800259D8_0 *)arg0)->unk_84.s) * 0x80) / 30;
        arg2->unk_0C.at02u.v = ((30 - ((S_800259D8_0 *)arg0)->unk_84.s) * 0xE0) / 30;
        if (((S_800259D8_0 *)arg0)->unk_A0 == 0) {
            ((S_800259D8_0 *)arg0)->unk_A0 = 1;
            phase = ((S_800259D8_0 *)arg0)->unk_AA + 0x18;
        } else {
            phase = ((S_800259D8_0 *)arg0)->unk_AA - 0x18;
            ((S_800259D8_0 *)arg0)->unk_A0 = 0;
        }
        ((S_800259D8_0 *)arg0)->unk_AA = phase;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        i = 0;
        ASM_KEEP_NV(i);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        value = func_80069EF8();
        i++;
        {
        register void *p0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        s32 p1;
        register s32 c2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        register s32 a3v ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        p0 = (u8 *)arg0 - 0x20;
        c2 = 0x00E02020;
        a3v = (value & 0xFF) | 0x80;
        p1 = ((S_800259D8_0 *)arg0)->unk_80;
        ASM_USE2(p0, c2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        func_80025338(p0, p1, c2, a3v, 0, 0, 0);
        }
        if (i < 4) {
            ASM_USE(i);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            func_80026430();
        }
        goto done;
    }
    ((S_800259D8_0 *)arg0)->unk_0A.u++;
    ((S_800259D8_0 *)arg0)->unk_84.u = 0;
    arg2->unk_14 |= 0x80;
    goto done;

    case 5:
    if (((S_800259D8_0 *)arg0)->unk_88 == 0) {
        goto done;
    }
    {
        tail_a = ((S_800259D8_0 *)arg0)->unk_0A.u;
        ASM_KEEP(tail_a);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ((S_800259D8_0 *)arg0)->unk_84.u = 0;
        goto L_state_advance;
    }

    case 6:
    {
    void *fade_node;
    void *fade_entry;
    s32 fade14;
    count = ((S_800259D8_0 *)arg0)->unk_84.u + 1;
    ((S_800259D8_0 *)arg0)->unk_84.u = count;
    fade_node = ((S_800259D8_3 *)obj)->unk_60;
    ((S_800259D8_10 *)fade_node)->unk_1C |= 0x10000000;
    fade_entry = ((S_800259D8_10_pre *)fade_node)[-1].unk_00;
    if (((S_800259D8_0 *)arg0)->unk_84.s >= 36) {
        ((S_800259D8_11 *)fade_entry)->unk_0C += 2;
        fade14 = ((S_800259D8_11 *)fade_entry)->unk_0E;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        phase = ((S_800259D8_11 *)fade_entry)->unk_0D;
        ((S_800259D8_11 *)fade_entry)->unk_0E = fade14 - 3;
        phase = phase + 2;
    } else {
        ((S_800259D8_11 *)fade_entry)->unk_0C -= 2;
        fade14 = ((S_800259D8_11 *)fade_entry)->unk_0E;
        ASM_SCHED_BARRIER();   /* MATCH: retain the color store before loading the shared green value. */
        phase = ((S_800259D8_11 *)fade_entry)->unk_0D;
        ((S_800259D8_11 *)fade_entry)->unk_0E = fade14 + 3;
        phase = phase - 2;
    }
    ((S_800259D8_11 *)fade_entry)->unk_0D = phase;
    if (((S_800259D8_0 *)arg0)->unk_84.s < 71) {
        goto done;
    }
    {
        void *tail_node;
        tail_node = ((S_800259D8_3 *)obj)->unk_60;
        ((S_800259D8_12 *)tail_node)->unk_1C &= 0xEFFFFFFF;
        fade_entry = ((S_800259D8_12_pre *)tail_node)[-1].unk_00;
        ((S_800259D8_11 *)fade_entry)->unk_0E = 0x80;
        ((S_800259D8_11 *)fade_entry)->unk_0D = 0x80;
        ((S_800259D8_11 *)fade_entry)->unk_0C = 0x80;
        func_80024098(((S_800259D8_3 *)obj)->unk_60, ((S_800259D8_0 *)arg0)->unk_09, obj);
    }
    tail_a = ((S_800259D8_0 *)arg0)->unk_0A.u;
    ((S_800259D8_0 *)arg0)->unk_84.u = 13;
L_state_advance:
    ((S_800259D8_0 *)arg0)->unk_0A.u = tail_a + 1;
    goto done;
    }

    case 7:
    old_count = ((S_800259D8_0 *)arg0)->unk_84.u;
    ((S_800259D8_0 *)arg0)->unk_84.u = old_count + 1;
    if ((s16)old_count < 15) {
        goto done;
    }
    {
        s32 seen;
        seen = D_80026664[0];
        ((S_800259D8_0 *)arg0)->unk_84.u = old_count;
        if (seen == 0) {
            D_8008346C[0] = 0;
            ((S_800259D8_0_pre *)arg0)[-1].unk_00 |= 0x8000;
            D_800814A0[0] |= 0x8000;
            goto done;
        }
    }
    D_80026664[0] = 0;
    goto done;
    }

done:
    return;
}
