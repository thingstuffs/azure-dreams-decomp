#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))
#define VFIELD(p, type, offset) (*(volatile type *)((u8 *)(p) + (offset)))

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef void (*Callback)(void *, void *, void *, void *);

extern u8 *D_80083160;
extern void func_80024544(void) __attribute__((noreturn));
extern void func_8002454C(void) __attribute__((noreturn));
extern void func_8002459C(void) __attribute__((noreturn));
extern void func_800246D0(void) __attribute__((noreturn));
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);

void func_81874988(void *arg0, void *arg1, void *arg2, s16 arg3)
{
    u8 *global_value = D_80083160;
    register u32 helper_value ASM_REG("$2");
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    Callback callback;
    s32 index;
    u16 flags;
    s32 adjust;
    u8 tex_flags;
    MATRIX matrix;

    FIELD(scratch, u8 *, 0x24) = global_value + 0xB0;
    FIELD(scratch, s32, 0x88) = FIELD(arg1, s16, 2);
    FIELD(scratch, s32, 0x8C) = FIELD(arg1, s16, 6);
    FIELD(scratch, s32, 0x90) = FIELD(arg1, s16, 0xA);

    packet = FIELD(global_value, u8 *, 0x8D0);
    FIELD(global_value, u8 *, 0x8D0) = packet + 0x28;

    FIELD(arg2, u16, 0x14) |= 0x8000;
    func_800649A0();

    FIELD(scratch, s32, 0x3C) = 0x2000;
    FIELD(scratch, s32, 0x38) = 0x2000;
    FIELD(scratch, s32, 0x34) = 0x2000;
    FIELD(scratch, u16, 0xA4) = FIELD(arg2, u16, 0x16);
    FIELD(scratch, u16, 0xA8) = FIELD(arg2, u16, 0x1A);
    FIELD(scratch, u16, 0xA6) = FIELD(arg2, u16, 0x18);
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture = FIELD(arg2, u8 *, 8);
    FIELD(scratch, u16, 0x28) = FIELD(arg2, u16, 0x14);

    if (texture[0] & 0x20) {
        goto callback_tail;
    }

    FIELD(scratch, s32, 0xC) = texture[8];
    FIELD(scratch, s32, 0x10) = texture[9];
    FIELD(scratch, s32, 0x14) = texture[0xA];
    FIELD(scratch, s32, 0x18) = texture[0xB];

    FIELD(scratch, u16, 0xB0) = FIELD(arg0, u16, 0x50);
    FIELD(scratch, u16, 0xB8) = FIELD(arg0, u16, 0x52);
    FIELD(scratch, u16, 0xC0) = FIELD(arg0, u16, 0x54);
    FIELD(scratch, u16, 0xC8) = FIELD(arg0, u16, 0x56);
    FIELD(scratch, u16, 0xB2) = FIELD(arg0, u16, 0x58);
    FIELD(scratch, u16, 0xBA) = FIELD(arg0, u16, 0x5A);
    FIELD(scratch, u16, 0xC2) = FIELD(arg0, u16, 0x5C);
    FIELD(scratch, u16, 0xCA) = FIELD(arg0, u16, 0x5E);
    FIELD(scratch, u16, 0xB4) = FIELD(arg0, u16, 0x60);
    FIELD(scratch, u16, 0xBC) = FIELD(arg0, u16, 0x62);
    FIELD(scratch, u16, 0xC4) = FIELD(arg0, u16, 0x64);
    FIELD(scratch, u16, 0xCC) = FIELD(arg0, u16, 0x66);

    index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                          scratch + 0xC0, scratch + 0xC8,
                          packet + 8, packet + 0x10,
                          packet + 0x18, packet + 0x20,
                          scratch + 0xD0, scratch + 0xD4) - arg3 - 6;
    FIELD(scratch, s32, 0x100) = index;

    if ((u32)index >= 0x1E0) {
        goto done;
    }
    if (
            (((u16)(FIELD(packet, u16, 8) + 0x20) < 0x181) &&
             ((u16)(FIELD(packet, u16, 0xA) + 0x20) < 0x121)) |
            (((u16)(FIELD(packet, u16, 0x10) + 0x20) < 0x181) &&
             ((u16)(FIELD(packet, u16, 0x12) + 0x20) < 0x121)) |
            (((u16)(FIELD(packet, u16, 0x18) + 0x20) < 0x181) &&
             ((u16)(FIELD(packet, u16, 0x1A) + 0x20) < 0x121)) |
            (((u16)(FIELD(packet, u16, 0x20) + 0x20) < 0x181) &&
             ((u16)(FIELD(packet, u16, 0x22) + 0x20) < 0x121))
        ) {
        goto visible;
    }
    goto done;

visible:
    FIELD(packet, u8, 3) = 9;
    FIELD(packet, u8, 7) = 0x2C;
    FIELD(arg2, u16, 0x14) &= 0x7FFF;

    FIELD(scratch, s32, 0x14) += FIELD(scratch, s32, 0xC);
    if (FIELD(scratch, s32, 0x14) & 0x100) {
        FIELD(scratch, s32, 0x14)--;
    }
    FIELD(scratch, s32, 0x18) += FIELD(scratch, s32, 0x10);
    if (FIELD(scratch, s32, 0x18) & 0x100) {
        FIELD(scratch, s32, 0x18)--;
    }
    FIELD(scratch, s32, 0x10) <<= 8;
    FIELD(scratch, s32, 0x18) <<= 8;

    adjust = FIELD(arg2, u16, 0x12);
    if (adjust) {
        if (FIELD(scratch, u16, 0x28) & 0x100) {
            FIELD(packet, u16, 0xE) = adjust;
            func_8002454C();
        }
        helper_value = adjust + FIELD(texture, u16, 6);
        ASM_TAILSLOT_PIN(helper_value);
        func_80024544();
    }
    FIELD(packet, u16, 0xE) = FIELD(texture, u16, 6);

    FIELD(packet, u16, 0xC) = VFIELD(scratch, u16, 0x10) +
                              VFIELD(scratch, u16, 0xC);
    FIELD(packet, u16, 0x14) = VFIELD(scratch, u16, 0x10) +
                               VFIELD(scratch, u16, 0x14);

    adjust = FIELD(arg2, u16, 0x10);
    if (adjust) {
        helper_value = adjust +
                       (FIELD(texture, u16, 4) & 0xFF9F);
        ASM_TAILSLOT_PIN(helper_value);
        func_8002459C();
    }
    FIELD(packet, u16, 0x16) = FIELD(texture, u16, 4);

    FIELD(packet, u16, 0x1C) = VFIELD(scratch, u16, 0x18) +
                               VFIELD(scratch, u16, 0xC);
    FIELD(packet, u16, 0x24) = VFIELD(scratch, u16, 0x18) +
                               VFIELD(scratch, u16, 0x14);

    if (FIELD(packet, s16, 8) > FIELD(packet, s16, 0x20)) {
        FIELD(packet, u8, 0x14)--;
        FIELD(packet, u8, 0x24)--;
    }
    if (FIELD(packet, s16, 0xA) > FIELD(packet, s16, 0x22)) {
        FIELD(packet, u8, 0x1D)--;
        FIELD(packet, u8, 0x25)--;
    }

    tex_flags = texture[1];
    FIELD(arg2, u8, 0xF) = tex_flags;
    flags = FIELD(scratch, u16, 0x28);
    if (flags & 8) {
        FIELD(arg2, u8, 0xF) = (flags & 4) ?
            (tex_flags | 2) : (tex_flags & 0xFD);
    }

    FIELD(packet, u32, 4) = FIELD(arg2, u32, 0xC);
    FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & 0xFF000000) |
        (FIELD(FIELD(scratch, u32 *, 0x24), u32,
               FIELD(scratch, s32, 0x100) * 4) & 0x00FFFFFF);
    FIELD(FIELD(scratch, u32 *, 0x24), u32,
          FIELD(scratch, s32, 0x100) * 4) =
        (FIELD(FIELD(scratch, u32 *, 0x24), u32,
               FIELD(scratch, s32, 0x100) * 4) & 0xFF000000) |
        ((u32)packet & 0x00FFFFFF);
    func_800246D0();

callback_tail:
    callback = FIELD(texture, Callback, 8);
    if (callback != 0) {
        callback(arg0, arg1, arg2, texture);
    }

done:
    func_80064A40();
}
