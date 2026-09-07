#include "common.h"

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

extern void func_80024210(void) __attribute__((noreturn));
extern void *func_8003FC64(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_8004491C(void *, void *);
extern u8 D_800240C4[];
extern u8 D_80025238[];
extern u8 D_80045340[];

#ifndef NON_MATCHING
register u32 match_v0 ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
#endif

/* Creates and initializes an object with the supplied data and coordinates. */
void *func_818A4948(s32 user_data, void *source_coords) {
    void *obj;
    void *render_data;
    void *coords;
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
    ASM_KEEP(init_data);   /* MATCH pin: retail immediate-load split depends on it */
    init_data += 0x5238;
    match_v0 = 0x80020000;
    ASM_KEEP(match_v0);   /* MATCH pin: keeps a statement from moving across a call/branch */
    match_v0 += 0x40C4;
#else
    match_v0 = (u32)D_800240C4;
#endif
    FIELD(obj, void **, 0x10) = (void *)match_v0;
    match_v0 = 0x80;
    render_data = FIELD(obj, void **, 0xC);
    FIELD(obj, s32 *, 0x20) = user_data;
    FIELD(render_data, u8 *, 0xE) = (u8)match_v0;
    FIELD(render_data, u8 *, 0xD) = (u8)match_v0;
    FIELD(render_data, u8 *, 0xC) = (u8)match_v0;
    func_8003DB94(render_data, init_data, 0);
    {
        void *init_obj = obj;

        ASM_KEEP(init_obj);   /* MATCH pin: retail schedule: same instructions, different order without it */
        init_data = D_80045340;
        ASM_KEEP(init_data);   /* MATCH pin: retail immediate-load split depends on it */
        match_v0 = 0x800;
        FIELD(render_data, s16 *, 0x1E) = (s16)match_v0;
        FIELD(render_data, s16 *, 0x1C) = (s16)match_v0;
        match_v0 = FIELD(render_data, u16 *, 0x14);
        FIELD(render_data, s16 *, 0x12) = 0x7E07;
        match_v0 |= 0x100;
        FIELD(render_data, u16 *, 0x14) = (u16)match_v0;
        func_8004491C(init_obj, init_data);
    }
    coords = FIELD(obj, void **, 8);
#ifndef NON_MATCHING
    __asm__ __volatile__("" : : "r"(source_coords));
#endif
    match_v0 = FIELD(source_coords, u16 *, 2);
    FIELD(coords, u16 *, 2) = (u16)match_v0;
    match_v0 = FIELD(source_coords, u16 *, 6);
    FIELD(coords, u16 *, 6) = (u16)match_v0;
    FIELD(coords, u16 *, 0xA) = FIELD(source_coords, u16 *, 0xA);
    return obj;
}
