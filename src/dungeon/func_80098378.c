#include "common.h"

extern u8 D_80082E80[];
extern u8 D_80083160[];
extern s32 D_800E296C;
extern u8 D_800E3548[];
extern u8 D_800E3648[];
extern u8 D_800E36C8[];
extern u8 D_800E39C8[];
extern u8 D_800E3CD8[];
extern u8 *D_800E3D7C;

extern s32 func_800644B8(s32);
extern void func_8009DA70(s32, s32, u8 *, s32);
extern s32 func_8009EE4C(s32, s32);
extern void func_8009EF04(void);
extern void func_8009EF78(void);
extern void func_8009F020(void);
extern void func_8009F0B4(void);
extern void func_8009F13C(void);
extern s32 func_8009FD40(u8 *, u8 *);

typedef struct {
    u8 x;
    u8 y;
    u8 pad[10];
} MapEntry;

typedef struct {
    s16 type;
    s16 x;
    s16 y;
    s16 pad;
} ObjectEntry;

typedef struct {
    u8 exists;
    u8 active;
    u8 pad;
    u8 flags;
} EntryInfo;

typedef struct {
    u8 pad[6];
    u8 x;
    u8 y;
    u8 rest[16];
} LargeMapEntry;

void func_8009DAD8(s32 arg0) {
    u8 colour[4];
    u8 *head;
    u8 *entry;
    u8 *object;
    long playerAndIndex;
    u8 *system;
    MapEntry *mapEntry;
    ObjectEntry *objectEntry;
    EntryInfo *info;
    LargeMapEntry *largeMapEntry;
    s32 brightness;
    s32 mode;
    u8 *playerLater;
    register long a0Value ASM_REG("$4");   /* MATCH pin: retail keeps a computation the compiler would drop */
    s32 firstY;
    u8 *firstColour;
    s32 firstContext;
    s32 distance;
    register long pageOrTwo ASM_REG("$20");   /* MATCH pin: retail register colouring depends on it */
    register long callPage ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
    register long flagsPage ASM_REG("$16");   /* MATCH pin: retail basic-block layout depends on it */
    register long loopFlagsPage ASM_REG("$22");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    system = D_80083160;
    head = D_800E3D7C;

    if (D_800E296C & 0x1000) {
        D_800E296C &= ~0x1000;
        func_8009F13C();
    }
    if (D_800E296C & 0x400) {
        D_800E296C &= ~0x400;
        func_8009F0B4();
    }
    if (D_800E296C & 0x200) {
        D_800E296C &= ~0x200;
        func_8009F020();
    }
    if (D_800E296C & 0x800) {
        D_800E296C &= ~0x800;
        func_8009EF78();
    }
    if (D_800E296C & 0x100) {
        D_800E296C &= ~0x100;
        func_8009EF04();
    }

    a0Value = *(u16 *)(system + 4) << 8;
    brightness = (func_800644B8(a0Value) >> 6) + 0x80;
    firstColour = colour;
    if (brightness >= 0x100) {
        brightness = 0xff;
    }

    firstContext = arg0;
    ASM_KEEP(firstContext);   /* MATCH pin: retail schedule: same instructions, different order without it */
    pageOrTwo = 0x80080000;
    ASM_KEEP(pageOrTwo);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    playerAndIndex = pageOrTwo + 0x2e80;
    ASM_USE_NV(pageOrTwo);   /* MATCH pin: load-bearing for the whole function shape */
    a0Value = ((u8 *)playerAndIndex)[0x24];
    firstY = ((u8 *)playerAndIndex)[0x25];
    colour[3] = 0x68;
    colour[2] = 0;
    colour[1] = brightness;
    colour[0] = brightness;
    func_8009DA70(a0Value, firstY, firstColour, firstContext);

    entry = *(u8 **)(head + 0x5c) + 0x20;
    colour[1] = 0;
    if (entry == head) {
        goto after_entries;
    }
#ifdef NON_MATCHING
    flagsPage = (long)&D_800E296C - 0x296c;
#else
    ASM_UNDEF(flagsPage);   /* MATCH pin: retail immediate-load split depends on it */
#endif
    loopFlagsPage = flagsPage;
    playerLater = (u8 *)playerAndIndex;
    pageOrTwo = 2;
    do {
        if (*(s8 *)(entry + 0x13) > 0) {
            object = *(u8 **)(entry - 0x14);
            if (!(*(s32 *)(loopFlagsPage + 0x296c) & 4)) {
                if (*(s8 *)(object + 0x26) < 0 ||
                    *(s8 *)(object + 0x26) != *(s8 *)(playerLater + 0x26)) {
                    a0Value = (long)object;
                    callPage = 0x80080000;
                    ASM_KEEP(callPage);   /* MATCH pin: load-bearing for the whole function shape */
                    distance = func_8009FD40((u8 *)a0Value,
                                             (u8 *)(callPage + 0x2e80));
                    if ((s16)distance >= 4) {
                        goto next_entry;
                    }
                }
            }

            a0Value = 0;
            if (entry[0x13] == 0x1e) {
                if (entry[0xad] == 0) {
                    a0Value = 1;
                } else {
                    a0Value = 2;
                    goto process_mode;
                }
            } else if (entry[0x13] != 0x23 ||
                       *(s16 *)(entry + 0xa6) == 0 ||
                       (*(s32 *)(loopFlagsPage + 0x296c) & 4)) {
                a0Value = 1;
            }

process_mode:
            mode = a0Value;
            if (mode != 0) {
                if (mode == pageOrTwo) {
                    colour[2] = brightness;
                    colour[0] = 0;
                }
                a0Value = object[0x24];
                func_8009DA70(a0Value, object[0x25], colour, arg0);
                if (mode == pageOrTwo) {
                    colour[2] = 0;
                    colour[0] = brightness;
                }
            }
        }
next_entry:
        entry = *(u8 **)(entry + 0x5c) + 0x20;
    } while (entry != head);
after_entries:
    playerAndIndex = 0;
    mapEntry = (MapEntry *)D_800E36C8;
    info = (EntryInfo *)D_800E3548;
    colour[2] = brightness;
    colour[0] = 0;
    do {
        if (info[playerAndIndex].active != 0) {
            if ((D_800E296C & 2) ||
                func_8009EE4C(a0Value = mapEntry[playerAndIndex].x,
                              mapEntry[playerAndIndex].y)) {
                func_8009DA70(a0Value = mapEntry[playerAndIndex].x,
                              mapEntry[playerAndIndex].y, colour, arg0);
            }
        }
        playerAndIndex++;
    } while (playerAndIndex < 0x40);

    playerAndIndex = 0;
    objectEntry = (ObjectEntry *)D_800E3CD8;
    colour[2] = 0;
    colour[1] = brightness;
    do {
        if (objectEntry[playerAndIndex].type != 2) {
            goto object_entries_done;
        }
        if ((D_800E296C & 1) ||
            func_8009EE4C(a0Value = objectEntry[playerAndIndex].x,
                          objectEntry[playerAndIndex].y)) {
            func_8009DA70(a0Value = (u16)objectEntry[playerAndIndex].x,
                          (u16)objectEntry[playerAndIndex].y, colour, arg0);
        }
        playerAndIndex++;
    } while (playerAndIndex < 4);

object_entries_done:
    playerAndIndex = 0;
    largeMapEntry = (LargeMapEntry *)D_800E39C8;
    info = (EntryInfo *)D_800E3648;
    colour[1] = 0x20;
    colour[2] = brightness;
    colour[0] = brightness;
    do {
        if (info[playerAndIndex].active != 0 &&
            info[playerAndIndex].exists != 0 &&
            !(info[playerAndIndex].flags & 0x40)) {
            if ((D_800E296C & 8) ||
                (!(info[playerAndIndex].flags & 0x80) &&
                 func_8009EE4C(a0Value = largeMapEntry[playerAndIndex].x,
                               largeMapEntry[playerAndIndex].y))) {
                func_8009DA70(a0Value = largeMapEntry[playerAndIndex].x,
                              largeMapEntry[playerAndIndex].y, colour, arg0);
            }
        }
        playerAndIndex++;
    } while (playerAndIndex < 0x20);
}
