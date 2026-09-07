#include "common.h"

typedef struct {
    s32 base;
    u8 pad_04[0x10];
    s16 shift;
} DungeonState;

typedef struct {
    u8 bytes[8];
} __attribute__((packed)) Packed8;

extern u8 D_80082E80[0x28];
extern DungeonState D_8008333C;
extern u16 D_80083462;
extern s32 D_800814A0;
extern u8 *D_800814A8;
extern u8 D_800DCF5B;
extern u8 *D_800E3D7C;
extern Packed8 D_800F8B24;

extern void func_80043A68(void);
extern void func_80094E34(void);
extern void func_800F6820(void) __attribute__((noreturn));

#define CLEAR_HIGH_BIT(ptr) \
    (*(u16 *)((u8 *)(ptr) + 4) = *(u16 *)((u8 *)(ptr) + 4) & 0x7FFF)

void func_807AEF8C(void *arg0) {
    DungeonState *state;
    s32 base;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v0_5;
    u8 *temp_v0_6;
    u8 *temp_v0_7;
    u8 *temp_v1_4;
    u8 *mode_page;
    u8 *objects;
    u8 *object;
    u32 copy_dest;
    u16 flags;
    register s32 mode ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 i;
    s32 i3;

    base = D_8008333C.base;
    mode = 0;
    state = &D_8008333C;
    if (!(D_80083462 & 2)) {
        return;
    }
    if (*(s32 *)(D_800E3D7C + 0x14) & 0x100000) {
        return;
    }
    if (D_80082E80[0x25] != 0x24) {
        return;
    }
    if (D_80082E80[0x24] == 0x1F) {
        mode = 2;
        ASM_TAILSLOT_PIN_TIED(mode);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800F6820();
    }
    if (D_80082E80[0x24] == 0x20) {
        mode = 1;
    }
    if (mode == 0) {
        return;
    }

    func_80094E34();
    copy_dest = 0x80013720;
    *(Packed8 *)copy_dest = D_800F8B24;
    mode_page = (u8 *)0x80010000;
    flags = *(u16 *)(mode_page + 0x3714);
    *(s16 *)(mode_page + 0x371A) = mode - 1;
    *(u16 *)(mode_page + 0x3718) = 0;
    *(u16 *)(mode_page + 0x3716) = 0;
    *(u16 *)(mode_page + 0x3714) = flags | 1;
    ASM_KEEP(mode);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    temp_v0 = (u8 *)(((0x23 << state->shift) * 6) + base + 0xBA);
    CLEAR_HIGH_BIT(temp_v0);
    temp_v0_2 = (u8 *)(((0x23 << state->shift) * 6) + base + 0xC0);
    CLEAR_HIGH_BIT(temp_v0_2);

    i = 0x10;
    do {
        temp_v1 = (u8 *)(((i + (0x11 << state->shift)) * 6) + base);
        CLEAR_HIGH_BIT(temp_v1);
        i++;
    } while (i < 0x1D);

    i = 0x23;
    do {
        temp_v1_2 = (u8 *)(((i + (0x11 << state->shift)) * 6) + base);
        CLEAR_HIGH_BIT(temp_v1_2);
        i++;
    } while (i < 0x30);

    i3 = 0x12;
    do {
        temp_v0_5 = (u8 *)(((i3 << state->shift) * 6) + base + 0x60);
        CLEAR_HIGH_BIT(temp_v0_5);
        temp_v0_6 = (u8 *)(((i3 << state->shift) * 6) + base + 0x11A);
        CLEAR_HIGH_BIT(temp_v0_6);
        i3++;
    } while (i3 < 0x20);

    i = 0x10;
    do {
        temp_v0_7 = (u8 *)(((i + (0x20 << state->shift)) * 6) + base);
        CLEAR_HIGH_BIT(temp_v0_7);
        temp_v1_4 = (u8 *)(((i + (0x21 << state->shift)) * 6) + base);
        CLEAR_HIGH_BIT(temp_v1_4);
        i++;
    } while (i < 0x30);

    func_80043A68();
    i = 0;
    *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
    D_800814A0 |= 0x8000;
    objects = D_800814A8;
    do {
        object = *(u8 **)(objects + 0xAC);
        if (object != 0) {
            *(u16 *)(object + 0x46) &= 0x7FFF;
        }
        i++;
        objects += 4;
    } while (i < 2);
    D_800DCF5B = 0;
}
