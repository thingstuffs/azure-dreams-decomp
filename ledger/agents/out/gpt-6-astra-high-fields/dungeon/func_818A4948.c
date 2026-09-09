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

extern void func_80024210(void) __attribute__((noreturn));
extern void *func_8003FC64(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_8004491C(void *, void *);
extern u8 D_800240C4[];
extern u8 D_80025238[];
extern u8 D_80045340[];

#ifndef NON_MATCHING
register u32 match_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif

/* Creates and initializes an object with the supplied data and coordinates. */
void *func_818A4948(s32 user_data, S_func_818A4948_2 *source_coords) {
    S_func_818A4948_0 *obj;
    S_func_818A4948_1 *render_data;
    S_func_818A4948_2 *coords;
    u8 *init_data;
#ifdef NON_MATCHING
    u32 match_v0;
#endif

    obj = func_8003FC64(0x212);
#ifndef NON_MATCHING
    init_data = (u8 *)0x80020000;
#else
    init_data = D_80025238;
#endif
    if (obj == 0) {
        match_v0 = 0;
        func_80024210();
    }
#ifndef NON_MATCHING
    ASM_KEEP(init_data);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    init_data += 0x5238;
    match_v0 = 0x80020000;
    ASM_KEEP(match_v0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    match_v0 += 0x40C4;
#else
    match_v0 = (u32)D_800240C4;
#endif
    obj->unk_10 = (void *)match_v0;
    match_v0 = 0x80;
    render_data = obj->unk_0C;
    obj->unk_20 = user_data;
    render_data->unk_0E = (u8)match_v0;
    render_data->unk_0D = (u8)match_v0;
    render_data->unk_0C = (u8)match_v0;
    func_8003DB94(render_data, init_data, 0);
    {
        void *init_obj = obj;

        ASM_KEEP(init_obj);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        init_data = D_80045340;
        ASM_KEEP(init_data);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        match_v0 = 0x800;
        render_data->unk_1E = (s16)match_v0;
        render_data->unk_1C = (s16)match_v0;
        match_v0 = render_data->unk_14;
        render_data->unk_12 = 0x7E07;
        match_v0 |= 0x100;
        render_data->unk_14 = (u16)match_v0;
        func_8004491C(init_obj, init_data);
    }
    coords = obj->unk_08;
#ifndef NON_MATCHING
    __asm__ __volatile__("" : : "r"(source_coords));
#endif
    match_v0 = source_coords->unk_02;
    coords->unk_02 = (u16)match_v0;
    match_v0 = source_coords->unk_06;
    coords->unk_06 = (u16)match_v0;
    coords->unk_0A = source_coords->unk_0A;
    return obj;
}
