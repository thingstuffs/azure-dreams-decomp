#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80174CCC_0_pre {
    union { volatile u16 s; u16 u; } unk_00;   /* accessed as both */
} S_80174CCC_0_pre;   /* the 0x2 bytes before arg0 in func_80174CCC, addressed as arg0[-1] */

typedef struct S_80174CCC_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA];
    union { s16 s; u16 u; } unk_1E;   /* accessed as both */
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    u8 pad_22[0x10];
    s16 unk_32;
    s16 unk_34;
    union { s16 s; u16 u; } unk_36;   /* accessed as both */
    union { volatile u16 s; u16 u; } unk_38;   /* accessed as both */
    u16 unk_3A;
} S_80174CCC_0;   /* arg0 in func_80174CCC */

typedef struct S_80174CCC_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_80174CCC_1;   /* arg1 in func_80174CCC */


typedef struct S_80174CCC_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174CCC_3;   /* global_base in func_80174CCC */

typedef struct S_80174CCC_4 {
    u8 pad_00[0x2968];
    s8 unk_2968;
} S_80174CCC_4;   /* (void *)state_page in func_80174CCC */

typedef struct S_80174CCC_5 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80174CCC_5;   /* (void *)used_page in func_80174CCC */

typedef struct S_80174CCC_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80174CCC_6_pre;   /* the 0x14 bytes before created in func_80174CCC, addressed as created[-1] */

typedef struct S_80174CCC_6 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 unk_29;
    s16 unk_2A;
    u8 pad_2C[0x17];
    u8 unk_43;
    u8 pad_44[0x60];
    void * unk_A4;
} S_80174CCC_6;   /* created in func_80174CCC */

typedef struct S_80174CCC_7 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x8C];
    void * unk_A4;
} S_80174CCC_7;   /* source in func_80174CCC */

typedef struct S_80174CCC_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_80174CCC_8;   /* tail_arg in func_80174CCC */

typedef struct S_80174CCC_9 {
    u8 pad_00[0xCA];
    u16 unk_CA;
} S_80174CCC_9;   /* parent in func_80174CCC */

typedef struct S_80174CCC_10 {
    u8 pad_00[0x12];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x16];
    union { void * s; u8 * u; } unk_2C;   /* accessed as both */
} S_80174CCC_10;   /* owner in func_80174CCC */

typedef struct S_80174CCC_11 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x22];
    u8 unk_28;
    u8 unk_29;
} S_80174CCC_11;   /* ((S_80174CCC_0 *)arg0)->unk_10 in func_80174CCC */



extern s32 D_800814A0;
extern s16 D_80083228;
extern s32 D_80083460;
extern s8 D_800E2968;
extern u8 D_80176668[];

extern s32 func_8003FA44(s32);
extern void func_80042640(void *, s32);
extern void func_80047784(void *, s32, s32);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A152C(s32, s32);
extern s32 func_800A1618(s32, s32);
extern void *func_801708B4(s32, s16, s16, s16);
extern void func_80174FBC(void) __attribute__((noreturn));

void func_80174CCC(void *arg0, S_80174CCC_1 *arg1, Rec_D_80082E80 *arg2)
{
    s32 state;
    s32 trig;
    void *created;
    S_80174CCC_7 *source;
    S_80174CCC_10 *owner;
    S_80174CCC_9 *parent;
    register void *tail_arg ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *global_base;
    s32 kind;
    s32 target_coord;
    s32 target_coord_x;
    s32 current_coord_x;
    s32 delta_x;
    s32 target_coord_y;
    s32 current_coord_y;
    s32 delta_y;
    s32 source_byte;
    u32 created_flags14;
    u32 created_flags1C;
    u32 first_created_flags;
    u32 used_page;
    u32 state_page;
    u16 flags;
    u16 marked;
    u16 timer;

    state = ((S_80174CCC_0 *)arg0)->unk_1E.s;
    if (state != 0) {
        if (state == 1) {
            goto state_one;
        }
        goto cleanup;
    }

    target_coord_x = ((S_80174CCC_0 *)arg0)->unk_32 << 6;
    current_coord_x = arg1->unk_00.at02.v - 0x20;
    delta_x = target_coord_x - current_coord_x;
    arg1->unk_00.at00.v +=
        (delta_x << 16) / ((S_80174CCC_0 *)arg0)->unk_20.s;

    target_coord_y = ((S_80174CCC_0 *)arg0)->unk_34 << 6;
    current_coord_y = arg1->unk_04.at02.v - 0x20;
    delta_y = target_coord_y - current_coord_y;
    arg1->unk_04.at00.v +=
        (delta_y << 16) / ((S_80174CCC_0 *)arg0)->unk_20.s;

    trig = func_800644B8(((S_80174CCC_0 *)arg0)->unk_20.s << 6) >> 4;
    arg1->unk_08.at00.v +=
        (((((S_80174CCC_0 *)arg0)->unk_36.s - trig) -
          arg1->unk_08.at02.v) << 16) /
        ((S_80174CCC_0 *)arg0)->unk_20.s;

    if (((S_80174CCC_0 *)arg0)->unk_20.s == 6) {
        func_80047784(arg2, 0x42, 0);
    }

    timer = ((S_80174CCC_0 *)arg0)->unk_20.u - 1;
    ((S_80174CCC_0 *)arg0)->unk_20.u = timer;
    if ((s16)timer > 0) {
        goto cleanup;
    }

    target_coord = ((S_80174CCC_0 *)arg0)->unk_32;
    target_coord = (target_coord << 6) + 0x20;
    arg1->unk_00.at02.v = target_coord;
    target_coord = ((S_80174CCC_0 *)arg0)->unk_34;
    target_coord = (target_coord << 6) + 0x20;
    arg1->unk_04.at02.v = target_coord;
    arg1->unk_08.at02u.v = ((S_80174CCC_0 *)arg0)->unk_36.u;
    func_80047784(arg2, 0x43, 0);
    ((S_80174CCC_0 *)arg0)->unk_1E.u++;
    goto cleanup;

state_one:
    if ((arg2->unk_14.at00_u16.v & 0xE000) == 0) {
        goto cleanup;
    }
    if (func_800A1618(0x1E, 1) == 0) {
        if (func_800A1618(0x1E, 3) == 0) {
            goto done;
        }
    }
    if (func_8003FA44(3) == 0) {
        goto done;
    }

    global_base = (u8 *)&D_80083460;
    kind = 4;
    ((S_80174CCC_3 *)global_base)->unk_0A--;
    used_page = 0x80080000;
    marked = ((S_80174CCC_0_pre *)arg0)[-1].unk_00.s;
    flags = ((S_80174CCC_0 *)arg0)->unk_38.s;
    marked |= 0x8000;
    ((S_80174CCC_0_pre *)arg0)[-1].unk_00.u = marked;
    state_page = 0x800E0000;
    ASM_KEEP(state_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ((S_80174CCC_4 *)((void *)state_page))->unk_2968 = state;
    ((S_80174CCC_5 *)((void *)used_page))->unk_14A0 |= 0x8000;
    if (flags & 0x2000) {
        kind = 7;
    }

    created = func_801708B4(kind,
        ((S_80174CCC_0 *)arg0)->unk_32,
        ((S_80174CCC_0 *)arg0)->unk_34,
        ((S_80174CCC_0 *)arg0)->unk_36.s);
    if (created == 0) {
        goto cleanup;
    }

    func_80042640(created, 0x1E);
    ((S_80174CCC_6 *)created)->unk_14 &= ~7;
    created_flags14 = ((S_80174CCC_6 *)created)->unk_14;
    first_created_flags = ((S_80174CCC_0 *)arg0)->unk_38.u;
    ((S_80174CCC_6 *)created)->unk_1C &= ~7;
    created_flags1C = ((S_80174CCC_6 *)created)->unk_1C;
    created_flags14 |= first_created_flags;
    ((S_80174CCC_6 *)created)->unk_14 = created_flags14;
    created_flags1C |= ((S_80174CCC_0 *)arg0)->unk_38.u;
    ((S_80174CCC_6 *)created)->unk_1C = created_flags1C;

    ((S_80174CCC_6 *)created)->unk_05 =
        (((S_80174CCC_11 *)(((S_80174CCC_0 *)arg0)->unk_10))->unk_05 + 1) >> 1;
    ((S_80174CCC_6 *)created)->unk_29 =
        (((S_80174CCC_11 *)(((S_80174CCC_0 *)arg0)->unk_10))->unk_29 + 1) >> 1;
    source_byte = ((S_80174CCC_11 *)(((S_80174CCC_0 *)arg0)->unk_10))->unk_28;
    ((S_80174CCC_6 *)created)->unk_43 = 0xFD;
    ((S_80174CCC_6 *)created)->unk_28 = (source_byte + 1) >> 1;

    source = ((S_80174CCC_0 *)arg0)->unk_10;
    if (source->unk_14 & 0x4000) {
        tail_arg = created;
        ((S_80174CCC_6 *)created)->unk_A4 = ((S_80174CCC_0 *)arg0)->unk_0C;
        func_80174FBC();
    }
    tail_arg = created;
    ASM_KEEP_NV(tail_arg);   /* MATCH pin: retail delay-slot contents depend on it */
    if (source->unk_A4 != 0) {
        ((S_80174CCC_6 *)created)->unk_A4 = source->unk_A4;
    }

    parent = ((S_80174CCC_8 *)tail_arg)->unk_A4;
    if (parent != 0) {
        parent->unk_CA++;
    }

    owner = ((S_80174CCC_6_pre *)created)[-1].unk_00;
    owner->unk_2C.s = D_80176668;
    owner->unk_14 |= 0x4000;
    owner->unk_12 = ((S_80174CCC_0 *)arg0)->unk_3A;
    func_80047784(owner,
        owner->unk_2C.u
            [((D_80083228 + ((S_80174CCC_6 *)created)->unk_2A + 0x100) >> 9) & 7],
        0);
    func_800A152C(0x1E, 1);

cleanup:
    func_800478B8(arg2);
done:
    return;
}
