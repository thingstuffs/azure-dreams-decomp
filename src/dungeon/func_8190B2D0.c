#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} __attribute__((packed)) Rect;

typedef struct {
    s16 x;
    s16 y;
} Point;

typedef struct {
    s16 x;
    u16 y;
} Coord;

typedef struct {
    Coord value[8];
} __attribute__((packed)) CoordTable;

typedef struct {
    u32 word[3];
} __attribute__((packed)) Packed12;

extern Rect D_80024038;
extern CoordTable D_80024064;
extern void *jtbl_80024088[9];
__asm__(".set jtbl_80024088, 0x80024088");

extern Packed12 D_80025618;
extern Packed12 D_80025624;
extern s16 D_80025630[8];
extern void *D_800246B4[3];
extern u8 D_80045340[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_800DDC40[];
extern u8 D_800E3D68[];
extern s32 D_8008346C;
extern s32 D_800814A0[3];

extern s32 func_8003DF74(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);
extern void func_80024470(void *, s32, s32, s32, s32, s32, s32);
extern s32 func_800A4778(s32, s32, s32, void *);
extern void func_800A56E0(s32);
extern void func_800B8FC8(void *, void *, void *, s32, s32);
extern void *func_8003FC64(s32);
extern u16 GetTPage(s32, s32, s32, s32);
extern void func_800240AC(void *, s32, void *);

void func_80024AD0(void *arg0, void *arg1, void *arg2)
{
    static void *const keepalive[] = {
        &&state0, &&state1, &&state2, &&state3, &&state4,
        &&state5, &&done, &&done, &&state8
    };
    s16 output[3];
    Rect rect;
    Point point;
    CoordTable table;
    void *s4;
    u32 s0;
    register u32 s5 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 state;
    register void *arg0_r ASM_REG("$19") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *arg1_r = arg1;
    void *arg2_r = arg2;
#define arg0 arg0_r
#define arg1 arg1_r
#define arg2 arg2_r

    ASM_KEEP_NV(arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s4 = FIELD(arg0, void *, 0);
    rect = D_80024038;
    table = D_80024064;
    s0 = (u32)((u8 *)s4 - 32);
    s5 = (u32)FIELD((void *)s0, void *, 8);
    state = FIELD(arg0, s16, 0xA);

    if ((u32)state >= 9U) {
        goto done;
    }
    (void)keepalive;
    goto *jtbl_80024088[(u32)state];

state0:
    {
    s16 value;
    u16 next;
    s32 result;
    FIELD(arg2, u32, 0xC) = 0x00808080;
    *(Packed12 *)((u8 *)arg0 + 0x96) = D_80025624;
    FIELD(arg2, void *, 8) = (u8 *)arg0 + 0x96;
    value = FIELD(s4, u16, 0x2A);
    D_80025630[0] = 1;
    next = FIELD(arg0, u16, 0xA);
    FIELD(arg0, u16, 0x7E) = (u16)(value >> 9) & 7;
    next++;
    FIELD(arg0, u16, 0xA) = next;
    result = func_8003DF74(FIELD(FIELD((void *)s0, void *, 0xC), void *, 8),
                           FIELD((void *)s0, void *, 0xC), output, 0);
    if (result == 0 &&
        !(FIELD(FIELD((void *)s0, void *, 0xC), u16, 0x14) & 0x8000)) {
        goto done;
    }
    }

state1:
    {
    s16 value;
    u16 next;
    u16 base_z;
    u16 base_height;
    void *info;
    register void *entry1 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *entry;
    s32 distance;
    register s32 offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    FIELD(arg1, u16, 2) = FIELD((void *)s5, u16, 2);
    FIELD(arg1, u16, 6) = FIELD((void *)s5, u16, 6);
    base_z = FIELD((void *)s5, u16, 0xA);
    FIELD(arg1, u16, 0xA) = base_z;
    if (!(FIELD(FIELD((void *)s0, void *, 0xC), u16, 0x14) & 0x8000)) {
        FIELD(arg1, u16, 2) += output[0];
        FIELD(arg1, u16, 6) += output[1];
        FIELD(arg1, u16, 0xA) += output[2];
    } else {
        FIELD(arg1, u16, 0xA) =
            (u16)(base_z - 64);
    }

    if (FIELD(FIELD(arg0, void *, 4), u16, 0) & 0x80) {
        if (!(FIELD(arg0, u8, 0x7A) & 4)) {
            func_8004491C((u8 *)arg0 - 32, D_80045340);
            FIELD(arg2, u8, 0xE) = 20;
            FIELD(arg2, u8, 0xD) = 20;
            FIELD(arg2, u8, 0xC) = 20;
            FIELD(arg2, u16, 0x14) |= 0xC;
            FIELD(arg2, u16, 0x10) = 0;
            FIELD(arg2, u16, 0x1E) = 0x800;
            FIELD(arg2, u16, 0x1C) = 0x800;
            FIELD(arg0, u8, 0x7A) |= 4;
        }
    } else {
        goto done;
    }

    info = FIELD(s4, void *, 0x60);
    if (info != 0) {
        entry1 = FIELD(info, void *, -24);
        offset = D_800DDC40[FIELD(info, u8, 0x13)] + 32;
        distance = FIELD(entry1, u16, 0xA) - offset;
        FIELD(arg0, u16, 0x78) = (u16)distance;
        entry = FIELD(s4, void *, -20);
        FIELD(arg0, u8, 0xA2) =
            FIELD(entry, u8, 0x24) +
            D_8006CCD8[(s16)FIELD(arg0, s16, 0x7E) * 2];
        FIELD(arg0, u8, 0xA3) =
            FIELD(entry, u8, 0x25) +
            D_8006CCE8[(s16)FIELD(arg0, s16, 0x7E) * 2];

        if (FIELD(s4, s8, 0x72) != FIELD(entry, u8, 0x24)) {
            offset = FIELD(s4, s8, 0x72) - FIELD(entry, u8, 0x24);
        } else {
            offset = FIELD(s4, s8, 0x73);
            offset -= FIELD(entry, u8, 0x25);
        }
        if (offset < 0) {
            offset = -offset;
        }
        FIELD(arg0, u8, 0x7B) = (u8)((offset << 1) - 1);
    } else {
        base_height = FIELD(s4, u16, 0x88);
        FIELD(arg0, u8, 0x7B) = 32;
        FIELD(arg0, u16, 0x78) = (u16)(base_height - 80);
    }

    FIELD(arg1, s32, 0xC) =
        (s32)table.value[FIELD(arg0, s16, 0x7E)].x << 16;
    FIELD(arg1, s32, 0x10) =
        (s32)table.value[FIELD(arg0, s16, 0x7E)].y << 16;
    FIELD(arg1, s32, 0x14) =
        (((s32)FIELD(arg0, s16, 0x78) << 16) - FIELD(arg1, s32, 8)) /
        (s8)FIELD(arg0, u8, 0x7B);
    FIELD(arg0, u16, 0x82) = 0;
    next = FIELD(arg0, u16, 0xA) + 1;
    FIELD(arg0, u16, 0xA) = next;
    FIELD(arg0, s16, 0x88) = (s16)(s8)FIELD(arg0, u8, 0x7B);
    FIELD(arg0, s16, 0x8A) =
        (s16)((s8)FIELD(arg0, u8, 0x7B) *
              (s8)FIELD(arg0, u8, 0x7B));
    goto done;
    }

state2:
    {
    u8 shade;
    register s32 delta ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 result;
    void *info;
    register void *entry ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s0 = 0;
    do {
        void *call_obj;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        s32 call_code;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        s32 call_shade;
        s32 random = func_80069EF8();
        call_obj = (u8 *)arg0 - 32;
        call_code = 0x00202020;
        call_shade = (random & 0xFF) | 0x80;
        func_80024470(call_obj, FIELD(arg0, s16, 0x7E),
                      call_code, call_shade, 0, 0, 0);
        s0++;
    } while ((s32)s0 < 4);
    {
        u16 angle = FIELD(arg2, u16, 0x1A) + 400;
        FIELD(arg2, u16, 0x1A) = angle;
        if ((u16)angle >= 0x1001) {
            FIELD(arg2, u16, 0x1A) =
                (u16)(angle - 4096);
        }
    }
    delta = FIELD(arg0, s16, 0x88) - FIELD(arg0, s8, 0x7B) + 1;
    FIELD(arg2, u8, 0xC) = (u8)((delta * delta * 108) /
                                FIELD(arg0, s16, 0x8A) + 20);
    delta = FIELD(arg0, s16, 0x88) - FIELD(arg0, s8, 0x7B) + 1;
    FIELD(arg2, u8, 0xD) = (u8)((delta * delta * 108) /
                                FIELD(arg0, s16, 0x8A) + 20);
    delta = FIELD(arg0, s16, 0x88) - FIELD(arg0, s8, 0x7B) + 1;
    FIELD(arg2, u8, 0xE) = (u8)((delta * delta * 108) /
                                FIELD(arg0, s16, 0x8A) + 20);
    result = func_800A4778(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                           FIELD(arg1, s16, 0xA), FIELD(s4, void *, 0x60));
    if ((result << 16) != 0) {
        FIELD(arg0, u16, 0xA) = 8;
        FIELD(arg0, u16, 0x82) = 0;
        FIELD(arg2, u8, 0xE) = 0;
        FIELD(arg2, u8, 0xD) = 0;
        FIELD(arg2, u8, 0xC) = 0;
        FIELD(arg2, u16, 0x1E) = 0;
        FIELD(arg2, u16, 0x1C) = 0;
        goto done;
    }
    shade = FIELD(arg0, u8, 0x7B) - 1;
    FIELD(arg0, u8, 0x7B) = shade;
    if ((s8)shade <= 0) {
        if (FIELD(s4, void *, 0x60) != 0) {
            FIELD(arg0, u16, 0xA) = 3;
            FIELD(arg0, u16, 0x82) = 0;
            func_800A56E0(0x300);
            FIELD(FIELD(s4, void *, 0x60), u32, 20) |= 0x100000;
            entry = FIELD(FIELD(s4, void *, 0x60), void *, -24);
            FIELD(arg1, u16, 2) = FIELD(entry, u16, 2);
            FIELD(arg1, u16, 6) = FIELD(entry, u16, 6);
            FIELD(arg1, u16, 0xA) = FIELD(arg0, u16, 0x78);
            goto done;
        }
        FIELD(arg0, u16, 0xA) = 8;
        FIELD(arg0, u16, 0x82) = 0;
        FIELD(arg2, u8, 0xE) = 0;
        FIELD(arg2, u8, 0xD) = 0;
        FIELD(arg2, u8, 0xC) = 0;
        FIELD(arg2, u16, 0x1E) = 0;
        FIELD(arg2, u16, 0x1C) = 0;
        goto done;
    }
    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
    goto done;
    }

state3:
    {
    register void *entry ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *dst;
    s32 state_count;
    register void *new_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *info;
    s32 current_count;
    {
        u16 angle = FIELD(arg2, u16, 0x1A) + 400;
        FIELD(arg2, u16, 0x1A) = angle;
        if ((u16)angle >= 0x1001) {
            FIELD(arg2, u16, 0x1A) =
                (u16)(angle - 4096);
        }
    }
    FIELD(arg0, u16, 0x82)++;
    state_count = FIELD(arg0, s16, 0x82);
    if (state_count == 1) {
        point.x = rect.x + ((s16)rect.w >> 1);
        point.y = rect.y + 72;
        func_800B8FC8(FIELD(s4, void *, 0x60), &rect, &point, 1,
                      state_count);
    }
    s5 = FIELD(arg0, s16, 0x82);
    if ((s16)s5 != 4) {
        goto done;
    }
    {
        arg1 = func_8003FC64(0x212);
        if (arg1 != 0) {
            new_obj = arg1;
            s0 = (u32)((u8 *)arg1 + 32);
                ASM_KEEP(s0);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                FIELD((void *)s0, void *, 44) = s4;
                FIELD((void *)s0, void *, 48) = FIELD(s4, void *, 0x60);
                FIELD((void *)s0, void *, 52) = arg0;
            FIELD(arg1, void *, 16) = D_800246B4;
            func_8004491C(new_obj, D_80045340);
            arg2 = FIELD(arg1, void *, 12);
            FIELD(arg2, u16, 16) = 32;
            FIELD(arg2, u16, 6) = 6;
            FIELD(arg2, u16, 20) |= 0xC;
            dst = FIELD(arg1, void *, 8);
            FIELD((void *)s0, u16, 10) = 0;
            FIELD((void *)s0, u16, 12) = 0;
            info = FIELD(s4, void *, 0x60);
            entry = FIELD(info, void *, -24);
            FIELD(dst, u32, 0) = FIELD(entry, u32, 0);
            FIELD(dst, u32, 4) = FIELD(entry, u32, 4);
            FIELD(dst, u32, 8) = FIELD(entry, u32, 8);
            arg2 = FIELD(arg1, void *, 12);
            FIELD(arg2, u16, 30) = 0x1000;
            FIELD(arg2, u16, 28) = 0x1000;
            FIELD(arg2, u8, 14) = 0x80;
            FIELD(arg2, u8, 13) = 0x80;
            FIELD(arg2, u8, 12) = 0x80;
            *(Packed12 *)((u8 *)arg1 + 64) = D_80025618;
            FIELD(arg2, void *, 8) = (u8 *)arg1 + 64;
            FIELD(FIELD(arg2, void *, 8), u16, 4) =
                GetTPage(2, 1, 0x340, 0x100);
        }
    }
    current_count = FIELD(arg0, s16, 0x82);
    if (current_count != (s16)s5) {
        goto done;
    }
    FIELD(arg0, u16, 0xA) = current_count;
    FIELD(arg0, u16, 0x82) = 0;
    FIELD(arg0, u16, 0x90) = 0;
    goto done;
    }

state4:
    {
    s32 value;
    s32 value2;
    void *info;
    void *entry;
    FIELD(arg0, u16, 0x82) = FIELD(arg0, u16, 0x82) + 1;
    {
        u16 angle = FIELD(arg2, u16, 0x1A) + 400;
        FIELD(arg2, u16, 0x1A) = angle;
        if ((u16)angle >= 0x1001) {
            FIELD(arg2, u16, 0x1A) =
                (u16)(angle - 4096);
        }
    }
    if (FIELD(arg0, s16, 0x82) < 42) {
        FIELD(arg1, s32, 8) -= 0x20000;
    }
    if (FIELD(arg0, s16, 0x82) == 81) {
        FIELD(arg2, u16, 16) = 32;
        FIELD(arg2, u8, 12) = 54;
        FIELD(arg2, u8, 13) = 54;
        FIELD(arg2, u8, 14) = 54;
    }
    if (FIELD(arg0, s16, 0x82) >= 81) {
        value = FIELD(arg0, s16, 0x82);
        FIELD(arg2, u8, 12) = (u8)(((100 - value) * 54) / 20);
        value2 = FIELD(arg0, s16, 0x82);
        FIELD(arg2, u8, 13) = (u8)(((100 - value2) * 54) / 20);
        value = FIELD(arg0, s16, 0x82);
        FIELD(arg2, u8, 14) = (u8)(((100 - value) * 54) / 20);
    }
    if (FIELD(arg0, s16, 0x82) >= 0) {
        info = FIELD(s4, void *, 0x60);
        FIELD(info, u32, 28) |= 0x10000000;
        entry = FIELD(info, void *, -20);
        if (FIELD(arg0, s16, 0x82) >= 43) {
            if (FIELD(arg0, s16, 0x82) < 64) {
                FIELD(entry, u8, 14) += 3;
                FIELD(entry, u8, 13) += 3;
                FIELD(entry, u8, 12) += 3;
            }
        } else {
            if (FIELD(arg0, s16, 0x82) == 41) {
                FIELD(entry, u8, 14) -= 60;
                FIELD(entry, u8, 13) -= 60;
                FIELD(entry, u8, 12) -= 60;
            }
        }
    }
    if (FIELD(arg0, s16, 0x82) >= 100) {
        void *final_info;
        u32 final_mask;
        final_mask = 0xEFFFFFFF;
        final_info = FIELD(s4, void *, 0x60);
        FIELD(final_info, u32, 28) &= final_mask;
        entry = FIELD(final_info, void *, -20);
        FIELD(entry, u8, 14) = 128;
        FIELD(entry, u8, 13) = 128;
        FIELD(entry, u8, 12) = 128;
        FIELD(arg0, u16, 0xA)++;
    }
    goto done;
    }

state5:
    {
    void *info;
    u8 setting;
    u32 mask;
    s32 value;
    if (FIELD(arg0, s16, 0x90) != 0) {
        mask = 0xFFEFFFFF;
        value = 255;
        info = FIELD(s4, void *, 0x60);
        setting = D_800E3D68[0];
        FIELD(info, u32, 20) &= mask;
        if (setting != value) {
            value = FIELD(arg0, u8, 9);
        }
        func_800240AC(FIELD(s4, void *, 0x60), value, s4);
        FIELD(arg0, u16, 0xA) = 8;
        FIELD(arg0, u16, 0x82) = 30;
    }
    goto done;
    }

state8:
    {
    s16 old_count;
    s16 count;
    s32 setting;
    old_count = FIELD(arg0, u16, 0x82);
    count = old_count + 1;
    FIELD(arg0, u16, 0x82) = count;
    if ((s16)count < 31) {
        goto done;
    }
    setting = D_80025630[0];
    FIELD(arg0, u16, 0x82) = old_count;
    switch (setting) {
    case 0: {
        D_8008346C = 0;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        break;
    }
    default:
        D_80025630[0] = 0;
        break;
    }
    }

done:
    return;
}
