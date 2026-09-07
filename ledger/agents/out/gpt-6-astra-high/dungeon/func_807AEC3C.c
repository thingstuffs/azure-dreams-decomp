#include "common.h"
#include "m2c_compat.h"

typedef struct S_800F643C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800F643C_0;   /* temp_v0 in func_800F643C */

typedef struct S_800F643C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xA];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800F643C_1;   /* temp_s1 in func_800F643C */

typedef struct S_800F643C_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800F643C_2;   /* temp_s0 in func_800F643C */

typedef struct S_800F643C_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    u8 pad_0A[0x4];
    s16 unk_0E;
    s16 unk_10;
} S_800F643C_3;   /* temp_a0 in func_800F643C */


void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800BCB04();               /* extern */
extern M2C_UNK D_80046398;
extern s32 D_80083208;
extern M2C_UNK D_800F6160;
extern s16 *D_800F8A44[];

/* Creates a dungeon object at the given position and records it in its slot. */
void func_800F643C(s16 x, s16 y, s32 slot) {
    s16 height;
    s32 render_config;
    void *object_data;
    void *position;
    void *model;
    void *object;

    object = func_8003FC64(0x16);
    if (object != NULL) {
        ((S_800F643C_0 *)object)->unk_10 = &D_800F6160;
        func_8004491C(object, &D_80046398);
        render_config = D_80083208;
        model = ((S_800F643C_0 *)object)->unk_0C;
        (*(s16 *)((u8 *)model + 0x20)) = 0x1000;
        ((S_800F643C_1 *)model)->unk_1E = 0x1000;
        ((S_800F643C_1 *)model)->unk_1C = 0x1000;
        ((S_800F643C_1 *)model)->unk_06 = 4;
        ((S_800F643C_1 *)model)->unk_0C = render_config;
        ((S_800F643C_1 *)model)->unk_08 = 0x70;
        position = ((S_800F643C_0 *)object)->unk_08;
        ((S_800F643C_2 *)position)->unk_02 = x;
        ((S_800F643C_2 *)position)->unk_06 = y;
        height = func_800BCB04(x & 0xFFFF, y & 0xFFFF, -0x400) - 0xC0;
        object_data = object + 0x20;
        ((S_800F643C_2 *)position)->unk_0A = height;
        ((S_800F643C_3 *)object_data)->unk_0E = height;
        ((S_800F643C_3 *)object_data)->unk_08 = slot;
        if (slot != 0) {
            ((S_800F643C_3 *)object_data)->unk_02 = 0x800;
            ((S_800F643C_1 *)model)->unk_1A = 0x800;
        }
        D_800F8A44[slot] = object_data;
        ((S_800F643C_3 *)object_data)->unk_10 = slot;
        ASM_USE(slot);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    }
}

/* MECHANISM: The 0x30/no-local frame follows from six natural held values; s32 slot plus
   symbolic D_800F8A44[index] removes the sign-extension and scale-by-16 length cascade.
   ASM_USE(slot) restores retail s3/s4/s5 argument coloring, and the named one-read
   D_80083208 value hoists its lui/lw and preserves the v1 store schedule. */
