#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80173140_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80173140_0;   /* temp_v0 in func_80173140 */

typedef struct S_80173140_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x72];
    s16 unk_92;
    u8 pad_94[0xC];
    s32 unk_A0;
} S_80173140_1;   /* temp_s1 in func_80173140 */

typedef struct S_80173140_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173140_2;   /* temp_a1 in func_80173140 */


typedef struct S_80173140_4 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { M2C_UNK * s; void * u; } unk_2C;   /* accessed as both */
} S_80173140_4;   /* temp_s0 in func_80173140 */

typedef struct S_80173140_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173140_5;   /* ((Rec_D_800E3D7C *)(&D_80083498))->unk_08.at00_pv.v in func_80173140 */


void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009A028();                      /* extern */
M2C_UNK func_8009A3D0();             /* extern */
void func_800A9C18(void *, void *, void *, s32); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80171D74;
extern M2C_UNK D_80173DA4;
extern void *D_80175D54;

/* Create and initialize a dungeon object and store it as the active object. */
void func_80173140(void) {
    s32 masked_flags;
    s32 flag_mask;
    s32 state_flags;
    s16 initial_offset;
    s32 cell_x;
    s32 cell_y;
    register void *object ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    M2C_UNK cell_mask;
    s32 origin_x;
    s32 origin_y;
    void *object_attrs;
    void *sprite;
    void *state;
    u8 *environment;

    object = func_8003FD64(0x112, &D_80083498);
    if (object != NULL) {
        state = object + 0x20;
        ((S_80173140_0 *)object)->unk_10 = &D_80171D74;
        ((S_80173140_1 *)state)->unk_13 = 2;
        func_8004491C(object, &D_80045340);
        environment = (u8 *)&D_80082E80;
        object_attrs = ((S_80173140_0 *)object)->unk_08;
        ((S_80173140_2 *)object_attrs)->unk_0A = (u16) ((S_80173140_5 *)(((Rec_D_800E3D7C *)(&D_80083498))->unk_08.at00_pv.v))->unk_0A;
        sprite = ((S_80173140_0 *)object)->unk_0C;
        origin_x = environment[0x24];
        ((S_80173140_4 *)sprite)->unk_24 = (u8) (origin_x - 1);
        origin_y = environment[0x25];
        ((S_80173140_4 *)sprite)->unk_2C.s = &D_80173DA4;
        ((S_80173140_4 *)sprite)->unk_25 = (u8) (origin_y + 7);
        func_800A9C18(object, object_attrs, sprite, 0);
        (*(s16 *)((u8 *)state + 0x2A)) = 0xC00;
        func_80047784(sprite, ((u8 *) ((S_80173140_4 *)sprite)->unk_2C.u)[((s32) (D_80083228 + 0xD00) >> 9) & 7], 0);
        ((S_80173140_4 *)sprite)->unk_1E = 0x1000;
        ((S_80173140_4 *)sprite)->unk_1C = 0x1000;
        state_flags = ((S_80173140_1 *)state)->unk_1C;
        flag_mask = 0x40000;
        ((S_80173140_1 *)state)->unk_A0 = 0;
        state_flags |= flag_mask;
        ((S_80173140_1 *)state)->unk_1C = state_flags;
        ASM_KEEP(state_flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        masked_flags = state_flags;
        ASM_KEEP(masked_flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        initial_offset = -0x20;
        ASM_KEEP(initial_offset);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        masked_flags &= 0x2000;
        ((S_80173140_1 *)state)->unk_92 = initial_offset;
        cell_x = ((S_80173140_4 *)sprite)->unk_24;
        cell_y = ((S_80173140_4 *)sprite)->unk_25;
        cell_mask = 0x3000;
        if (masked_flags) {
            cell_mask = 0x300;
        }
        func_8009A3D0(cell_x, cell_y, cell_mask);
        func_8009A028(state);
        D_80175D54 = object;
        ((S_80173140_0 *)object)->unk_10 = (M2C_UNK *) ((s32) ((S_80173140_0 *)object)->unk_10 | 0x80000000);
    }
}
