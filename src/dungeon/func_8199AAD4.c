#include "common.h"
#include "records/Rec_D_800814A8.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8199AAD4_0_pre {
    u16 unk_00;
} S_8199AAD4_0_pre;   /* the 0x2 bytes before self in func_8199AAD4, addressed as self[-1] */

typedef struct S_8199AAD4_0 {
    void * unk_00;
    void * unk_04;
    void * unk_08;
    void * unk_0C;
    union { s32 s; u8 * u; } unk_10;   /* accessed as both */
    s32 unk_14;
    u8 pad_18[0x10];
    union { s16 s; volatile u16 u; u16 p; } unk_28;   /* accessed as both */
    u8 pad_2A[0x4];
    union { volatile s16 s; s16 u; u16 p; } unk_2E;   /* accessed as both */
    union { s16 s; u16 u; } unk_30;   /* accessed as both */
    u8 pad_32[0x6];
    s16 unk_38;
} S_8199AAD4_0;   /* self in func_8199AAD4 */

typedef struct S_8199AAD4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_8199AAD4_1;   /* source in func_8199AAD4 */

typedef struct S_8199AAD4_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_8199AAD4_2;   /* coords in func_8199AAD4 */

typedef struct S_8199AAD4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8199AAD4_3;   /* position in func_8199AAD4 */

typedef struct S_8199AAD4_4 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_8199AAD4_4;   /* global_flags in func_8199AAD4 */

typedef struct S_8199AAD4_5 {
    void * unk_00;
    u8 pad_04[0x4];
    void * unk_08;
} S_8199AAD4_5;   /* entry in func_8199AAD4 */

typedef struct S_8199AAD4_6 {
    s32 unk_00;
    s32 unk_04;
} S_8199AAD4_6;   /* target_node in func_8199AAD4 */


typedef struct S_8199AAD4_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8199AAD4_8;   /* call_node in func_8199AAD4 */

typedef struct S_8199AAD4_9 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8199AAD4_9;   /* created in func_8199AAD4 */

typedef struct S_8199AAD4_10 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_8199AAD4_10;   /* ((S_8199AAD4_0 *)self)->unk_00 in func_8199AAD4 */

typedef struct S_8199AAD4_11 {
    u16 unk_00;
} S_8199AAD4_11;   /* ((S_8199AAD4_0 *)self)->unk_0C in func_8199AAD4 */


#define self arg0
#define coords arg1
#define source work
#define iteration work

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern u8 D_80024AE0;
extern u16 D_80024A70;
extern s32 D_800814A0;
extern void *D_800814A8;
extern s16 D_80083228;
extern void *D_800E3D18;

extern void func_80024410(void) __attribute__((noreturn));
extern void func_80024464(void) __attribute__((noreturn));
/* Ordinary declaration: the private selector authenticates this one
 * returning tail by qid/geometry/context instead of using an asm symbol alias. */
extern void func_800244DC(void);
extern void func_800246C4(void) __attribute__((noreturn));
extern void *func_80024924(void *, s32, s32, s32, void *, s32, s32, s32, void *);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_800644B8(s32);
extern void func_800B8D64(s16, s16, s16);


void func_8199AAD4(void *arg0, void *arg1)
{
    u16 delta[3];
    s32 target[3];
    s32 start_x;
    s32 start_y;
    s32 start_z;
    s16 state;
    volatile void *work;
    S_8199AAD4_6 *target_node;
    S_8199AAD4_8 *call_node;
    S_8199AAD4_3 *position;
    void *entry_base;
    register void *entry ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    S_8199AAD4_9 *created;
    register u8 *table_end ASM_REG("$22");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *table_start ASM_REG("$23");   /* MATCH pin: load-bearing for the whole function shape */
    s32 index;
    s32 curve;
    s32 global_value;
    u16 count;
    u16 position_z;
    register u32 tail_z ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 *global_flags;
    void *hit_out;
    register s32 nine ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    D_80024A70++;

    state = ((S_8199AAD4_0 *)self)->unk_28.s;
    if (state != 1) {
        if (state < 2) {
            if (state != 0) {
                func_800246C4();
            }
            goto state_zero;
        }

        ASM_KEEP(table_start);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        tail_z = 2;
        if (state == (s32)tail_z) {
            iteration = NULL;
            goto state_two;
        }
        func_800246C4();

state_zero:
            source = ((S_8199AAD4_10 *)(((S_8199AAD4_0 *)self)->unk_00))->unk_0C;
            if ((((S_8199AAD4_1 *)source)->unk_14 & 0x8000) ||
                func_8003DE58(((S_8199AAD4_1 *)source)->unk_08, source, delta, 0)) {
                position = ((S_8199AAD4_10 *)(((S_8199AAD4_0 *)self)->unk_00))->unk_08;
                ((S_8199AAD4_2 *)coords)->unk_00.at02.v = position->unk_02;
                ((S_8199AAD4_2 *)coords)->unk_04.at02.v = position->unk_06;
                position_z = position->unk_0A;
                ((S_8199AAD4_2 *)coords)->unk_08.at02.v = position_z;

                if (((S_8199AAD4_1 *)source)->unk_14 & 0x8000) {
                    goto fixed_position;
                }
                ((S_8199AAD4_2 *)coords)->unk_00.at02.v += delta[0];
                ((S_8199AAD4_2 *)coords)->unk_04.at02.v += delta[1];
                ASM_KEEP(source);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                tail_z = ((S_8199AAD4_2 *)coords)->unk_08.at02.v;
                tail_z += delta[2];
                ASM_TAILSLOT_PIN(tail_z);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                func_80024410();

fixed_position:
                ASM_KEEP(source);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                ((S_8199AAD4_2 *)coords)->unk_08.at02.v = position_z - 0x20;
            }

            if (((S_8199AAD4_11 *)(((S_8199AAD4_0 *)self)->unk_0C))->unk_00 & 0x80) {
                ((S_8199AAD4_0 *)self)->unk_2E.s = 8;
                tail_z = ((S_8199AAD4_0 *)self)->unk_28.u;
                nine = 9;
                ((S_8199AAD4_0 *)self)->unk_30.s = nine;
                func_80024464();
            }
            goto done;
    }

    count = ((S_8199AAD4_0 *)self)->unk_30.u - 1;
    ((S_8199AAD4_0 *)self)->unk_30.u = count;
    if ((s16)count > 0) {
        goto done;
    }
    ((S_8199AAD4_0 *)self)->unk_28.p++;
    func_800246C4();

finish:
    ((S_8199AAD4_2 *)coords)->unk_00.at00.v = target[0];
    ((S_8199AAD4_2 *)coords)->unk_04.at00.v = target[1];
    ((S_8199AAD4_2 *)coords)->unk_08.at00.v = target[2];
    func_800B8D64(((S_8199AAD4_2 *)coords)->unk_00.at02u.v, ((S_8199AAD4_2 *)coords)->unk_04.at02u.v,
                  ((S_8199AAD4_2 *)coords)->unk_08.at02u.v);
    tail_z = ((S_8199AAD4_0_pre *)self)[-1].unk_00;
    ASM_KEEP(tail_z);   /* MATCH pin: keeps a statement from moving across a call/branch */
    global_flags = (s32 *)0x80080000;
    ASM_KEEP(global_flags);   /* MATCH pin: load-bearing for the whole function shape */
    ((S_8199AAD4_0_pre *)self)[-1].unk_00 = tail_z | 0x8000;
    count = ((S_8199AAD4_0 *)self)->unk_28.p;
    ASM_KEEP(count);   /* MATCH pin: keeps a constant in a register as retail does */
    global_value = ((S_8199AAD4_4 *)global_flags)->unk_14A0;
    count++;
    global_value |= 0x8000;
    ASM_KEEP(global_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_8199AAD4_0 *)self)->unk_28.p = count;
    ((S_8199AAD4_4 *)global_flags)->unk_14A0 = global_value;
    func_800246C4();

state_two:
    ASM_KEEP(iteration);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    entry = (void *)0x80020000;
    ASM_KEEP(entry);   /* MATCH pin: load-bearing for the whole function shape */
    table_end = (u8 *)entry + 0x4AE0;
    ASM_KEEP(table_end);   /* MATCH pin: keeps a statement from moving across a call/branch */
    table_start = table_end - 0x54;
    entry = ((S_8199AAD4_0 *)self)->unk_04;
    start_x = ((S_8199AAD4_2 *)coords)->unk_00.at02u.v;
    start_y = ((S_8199AAD4_2 *)coords)->unk_04.at02u.v;
    target_node = ((S_8199AAD4_5 *)entry)->unk_08;
    ASM_KEEP(entry);   /* MATCH pin: load-bearing for the whole function shape */
    start_z = ((S_8199AAD4_2 *)coords)->unk_08.at02u.v;
    target[0] = target_node->unk_00;
    target[1] = target_node->unk_04;
    target[2] = (((S_8199AAD4_0 *)self)->unk_38 - 0x50) << 16;

    index = (D_80083228 + ((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_s16 + 0x100) >> 7;
    hit_out = delta;
    entry_base = D_800E3D18;
    index &= 0x1C;
    entry = (void *)(index + (s32)entry_base);
    call_node = ((S_8199AAD4_0 *)self)->unk_04;
    if (func_8003DE58(((S_8199AAD4_5 *)entry)->unk_00, call_node->unk_0C, hit_out, 0)) {
        target[0] += (s32)(s16)delta[0] << 16;
        target[1] += (s32)(s16)delta[1] << 16;
        target[2] += (s32)(s16)delta[2] << 16;
    }

    ((S_8199AAD4_2 *)coords)->unk_00.at00.v +=
        (target[0] - ((S_8199AAD4_2 *)coords)->unk_00.at00.v) / ((S_8199AAD4_0 *)self)->unk_2E.u;
    ((S_8199AAD4_2 *)coords)->unk_04.at00.v +=
        (target[1] - ((S_8199AAD4_2 *)coords)->unk_04.at00.v) / ((S_8199AAD4_0 *)self)->unk_2E.u;
    curve = func_800644B8(((S_8199AAD4_0 *)self)->unk_2E.u * 170);
    ((S_8199AAD4_2 *)coords)->unk_08.at00.v +=
        (target[2] - ((S_8199AAD4_2 *)coords)->unk_08.at00.v) / ((S_8199AAD4_0 *)self)->unk_2E.u -
        (curve << 7);

    created = func_80024924(((S_8199AAD4_0 *)self)->unk_08, start_x, start_y, start_z,
                            coords, ((S_8199AAD4_0 *)self)->unk_10.s, 4,
                            ((S_8199AAD4_0 *)self)->unk_14, iteration);
    if (created != NULL) {
        ((S_8199AAD4_0 *)self)->unk_08 = created;
        ((S_8199AAD4_0 *)self)->unk_14 = created->unk_08;
    }

    count = ((S_8199AAD4_0 *)self)->unk_2E.p - 1;
    ((S_8199AAD4_0 *)self)->unk_2E.p = count;
    if ((s16)count <= 0) {
        goto finish;
    }

    ((S_8199AAD4_0 *)self)->unk_10.u += 0xC;
    if (((S_8199AAD4_0 *)self)->unk_10.u >= table_end) {
        ((S_8199AAD4_0 *)self)->unk_10.u = table_start;
    }
    func_800244DC();
    iteration = (u8 *)iteration + 1;
    ASM_KEEP(iteration);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

done:
    return;
}

/* MECHANISM: The census baseline holds the 0x68 sibling-local frame and retail saved-register set.
   Register pins encode the surviving bases and late call operands; residual work starts at word 120. */
