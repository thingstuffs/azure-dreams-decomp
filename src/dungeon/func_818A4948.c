#include "common.h"

typedef struct S_func_818A4948_0 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_func_818A4948_0;

typedef struct S_func_818A4948_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_func_818A4948_1;

typedef struct S_func_818A4948_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_func_818A4948_2;

extern void *func_8003FC64(s32);
extern void func_8003DB94(void *, void *, s16);
extern s32 func_8004491C(void *, s32);
extern u8 D_800240C4[];
extern u8 D_80025238[];
extern u8 D_80045340[];

/* Creates and initializes an object with the supplied data and coordinates. */
void *func_818A4948(s32 user_data, S_func_818A4948_2 *source_coords) {
    S_func_818A4948_0 *obj;
    S_func_818A4948_1 *render_data;
    S_func_818A4948_2 *coords;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->unk_10 = D_800240C4;
        render_data = obj->unk_0C;
        obj->unk_20 = user_data;
        render_data->unk_0E = 0x80;
        render_data->unk_0D = 0x80;
        render_data->unk_0C = 0x80;
        func_8003DB94(render_data, D_80025238, 0);
        render_data->unk_1E = 0x800;
        render_data->unk_1C = 0x800;
        render_data->unk_12 = 0x7E07;
        render_data->unk_14 |= 0x100;
        func_8004491C(obj, (s32) D_80045340);
        coords = obj->unk_08;
        coords->unk_02 = source_coords->unk_02;
        coords->unk_06 = source_coords->unk_06;
        coords->unk_0A = source_coords->unk_0A;
        return obj;
    }
    return 0;
}
