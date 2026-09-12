#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct S_800BFB8C_0_pre {
    u16 unk_00;
} S_800BFB8C_0_pre;   /* the 0x2 bytes before temp_s2 in func_800BFB8C, addressed as temp_s2[-1] */

typedef struct S_800BFB8C_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
    u16 unk_0E;
} S_800BFB8C_0;   /* temp_s2 in func_800BFB8C */

typedef struct S_800BFB8C_1 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800BFB8C_1;   /* var_a0 in func_800BFB8C */

typedef struct S_800BFB8C_2 {
    u8 pad_00[0xBC];
    s16 unk_BC;
} S_800BFB8C_2;   /* town in func_800BFB8C */

typedef struct S_800BFB8C_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0xC];
    s16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    u8 pad_24[0x2];
    s16 unk_26;
} S_800BFB8C_3;   /* temp_s0 in func_800BFB8C */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_80033BC0();
void *func_8003FD64();
void func_8004491C(void *, void *);
s32 rand(void);
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083160;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BFD14;
extern M2C_UNK D_800BFFF4;

/* Spawn objects at randomized coordinates and mark completion when the countdown expires. */
void func_800BFB8C(void *source)
{
    s16 fixed_coord;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 state;
    s32 coord_term;
    s32 random_value;
    s32 spawn_count;
    s32 count_bits;
    register s32 random_coord ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 base_coord;
    u16 next_value;
    u8 *town;
    u8 *kind;
    void *coords;
    register void *emitter ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *new_object;
    void *object;
    void *callback;

    object = source;
    emitter = object;
    count_bits = ((S_800BFB8C_0 *)emitter)->unk_0E;
    count_bits <<= 0x10;
    spawn_count = count_bits >> 0x11;
    town = (u8 *)&D_80083160;
    if (spawn_count >= 0) {
        kind = (u8 *)&D_800BFD14;
        do {
            new_object = func_8003FD64((void *)0x202, &D_80083498);
            if (new_object != NULL) {
                object = new_object;
                callback = &D_800BFFF4;
                coords = object + 0x20;
                ((S_800BFB8C_1 *)object)->unk_10 = (M2C_UNK *)kind;
                func_8004491C(object, callback);
                random_coord = rand();
                random_value = random_coord;
                coord_term = ((S_800BFB8C_2 *)town)->unk_BC;
                if (random_value >= 0) {
                    random_coord = random_coord >> 0xA;
                } else {
                    random_coord = (s32)(random_value + 0x3FF) >> 0xA;
                }
                random_coord <<= 0xA;
                random_coord = random_value - random_coord;
                random_coord = coord_term + random_coord;
                random_coord -= 0x200;
                ((S_800BFB8C_3 *)coords)->unk_0C = random_coord;
                ((S_800BFB8C_3 *)coords)->unk_1E = random_coord;
                coord_term = rand()
                        % (s16)((S_800BFB8C_0 *)emitter)->unk_0A;
                base_coord = ((S_800BFB8C_0 *)emitter)->unk_08;
                fixed_coord = -0x180;
                ((S_800BFB8C_3 *)coords)->unk_10 = fixed_coord;
                ((S_800BFB8C_3 *)coords)->unk_26 = fixed_coord;
                count_bits = base_coord;
                count_bits += coord_term;
                ((S_800BFB8C_3 *)coords)->unk_0E = count_bits;
                ((S_800BFB8C_3 *)coords)->unk_22 = count_bits;
            }
            spawn_count -= 1;
            object = (void *)0x202;
        } while (spawn_count >= 0);
    }
    state = ((S_800BFB8C_0 *)emitter)->unk_0C.s;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    if (func_80033BC0(0xA1) == 0) {
        goto done;
    }
    next_value = ((S_800BFB8C_0 *)emitter)->unk_0C.u + 1;
    ((S_800BFB8C_0 *)emitter)->unk_0C.u = next_value;
    goto done;

state_one:
    next_value = ((S_800BFB8C_0 *)emitter)->unk_0E - 1;
    ((S_800BFB8C_0 *)emitter)->unk_0E = next_value;
    if ((next_value << 0x10) <= 0) {
        (*(u16 *)((u8 *)emitter + -2)) =
            (u16)(((S_800BFB8C_0_pre *)emitter)[-1].unk_00 | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }

done:
    return;
}
