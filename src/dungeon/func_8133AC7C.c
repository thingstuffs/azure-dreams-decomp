#include "common.h"


typedef struct {
    s32 x;
    s32 y;
    s32 z;
} __attribute__((packed)) PackedVec;

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80045340;
extern s32 D_80083780[3];
extern s32 D_801717A8;
extern PackedVec D_80173B40;
extern void *D_80175D60;


typedef struct S_80171C7C_0 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80171C7C_0;   /* temp_a3 in func_80171C7C */

typedef struct S_80171C7C_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80171C7C_1;   /* temp_a0 in func_80171C7C */

typedef struct S_80171C7C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80171C7C_2;   /* temp_v1 in func_80171C7C */

/* Creates an object with default coordinates and initializes its rendering state. */
void func_80171C7C(void) {
    s32 *default_coords;
    S_80171C7C_1 *coords;
    S_80171C7C_0 *render_state;
    void *object;
    u16 render_flags;

    object = func_8003FC64(0x12);
    if (object != 0) {
        (*(s16 *)((u8 *)object + 0x38)) = 0;
        (*(s32 * *)((u8 *)object + 0x10)) = &D_801717A8;
        func_8004491C(object, &D_80045340);
        render_state = (*(void * *)((u8 *)object + 0xC));
        render_state->unk_06 = 0;
        coords = (*(void * *)((u8 *)object + 8));
        default_coords = D_80083780;
        coords->unk_00 = ((S_80171C7C_2 *)default_coords)->unk_00;
        coords->unk_04 = ((S_80171C7C_2 *)default_coords)->unk_04;
        coords->unk_08 = ((S_80171C7C_2 *)default_coords)->unk_08;
        render_state = (*(void * *)((u8 *)object + 0xC));
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        render_state->unk_0E = 0x80;
        render_state->unk_0D = 0x80;
        render_state->unk_0C = 0x80;
        render_flags = render_state->unk_14;
        D_80175D60 = object;
        render_state->unk_14 = render_flags | 0x80;
        (*(PackedVec *)((u8 *)object + 0x48)) = D_80173B40;
        render_state->unk_08 = (u8 *)object + 0x48;
    }
}
