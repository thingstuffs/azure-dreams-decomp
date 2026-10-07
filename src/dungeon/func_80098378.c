#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/entity.h"

extern u8 D_800E3648[];
extern u8 D_800E36C8[];
extern u8 D_800E39C8[];
extern u8 D_800E3CD8[];

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

/* Services pending redraw flags, then draws map markers for nearby monsters, dropped items, and large map entries. */
void func_8009DAD8(s32 draw_param) {
    u8 colour[4];
    EntityRec *head;
    u8 *entry;
    u8 *object;
    long playerAndIndex;
    GameWork *system;
    MapEntry *mapEntry;
    ObjectEntry *objectEntry;
    EntryInfo *info;
    LargeMapEntry *largeMapEntry;
    s32 brightness;
    long kind;
    s32 firstX;
    s32 firstY;
    u8 *firstColour;
    s32 firstContext;
    s32 distance;
    long flagsPage;
    register long loopFlagsPage ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    system = &gameWork;
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

    brightness = (func_800644B8(system->unk_004 << 8) >> 6) + 0x80;
    firstColour = colour;
    if (brightness >= 0x100) {
        brightness = 0xff;
        firstContext = draw_param;
    } else {
        firstContext = draw_param;
    }
    playerAndIndex = (long)&D_80082E80;
    firstX = ((u8 *)playerAndIndex)[0x24];
    firstY = ((u8 *)playerAndIndex)[0x25];
    colour[3] = 0x68;
    colour[2] = 0;
    colour[1] = brightness;
    colour[0] = brightness;
    func_8009DA70(firstX, firstY, firstColour, firstContext);

    entry = ((u8 *)head->unk_5C) + 0x20;
    colour[1] = 0;
    if (entry != head) {
        ASM_UNDEF(flagsPage);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        loopFlagsPage = flagsPage;
        for (; entry != head; entry = *(u8 **)(entry + 0x5c) + 0x20) {
            if (*(s8 *)(entry + 0x13) > 0) {
                object = *(u8 **)(entry - 0x14);
                if (!(*(s32 *)(loopFlagsPage + 0x296c) & 4)) {
                    if (*(s8 *)(object + 0x26) < 0 ||
                        *(s8 *)(object + 0x26) != D_80082E80.unk_026) {
                        distance = func_8009FD40(object,
                                                 (u8 *)&D_80082E80);
                        if ((s16)distance >= 4) {
                            continue;
                        }
                    }
                }

                kind = 0;
                if (entry[0x13] == 0x1e) {
                    if (entry[0xad] != 0) {
                        kind = 2;
                    } else {
                        kind = 1;
                    }
                } else if (entry[0x13] != 0x23 ||
                           *(s16 *)(entry + 0xa6) == 0 ||
                           (*(s32 *)(loopFlagsPage + 0x296c) & 4)) {
                    kind = 1;
                }

                flagsPage = kind;
                if (flagsPage != 0) {
                    if (flagsPage == 2) {
                        colour[2] = brightness;
                        colour[0] = 0;
                    }
                    func_8009DA70(object[0x24], object[0x25], colour, draw_param);
                    if (flagsPage == 2) {
                        colour[2] = 0;
                        colour[0] = brightness;
                    }
                }
            }
        }
    }
    playerAndIndex = 0;
    mapEntry = (MapEntry *)D_800E36C8;
    info = (EntryInfo *)((u8 *)D_800E3548);
    colour[2] = brightness;
    colour[0] = 0;
    do {
        if (info[playerAndIndex].active != 0) {
            if ((D_800E296C & 2) ||
                func_8009EE4C(mapEntry[playerAndIndex].x,
                              mapEntry[playerAndIndex].y)) {
                func_8009DA70(mapEntry[playerAndIndex].x,
                              mapEntry[playerAndIndex].y, colour, draw_param);
            }
        }
        playerAndIndex++;
    } while (playerAndIndex < 0x40);

    playerAndIndex = 0;
    objectEntry = (ObjectEntry *)D_800E3CD8;
    colour[2] = 0;
    colour[1] = brightness;
    for (; playerAndIndex < 4 && objectEntry[playerAndIndex].type == 2; playerAndIndex++) {
        if ((D_800E296C & 1) ||
            func_8009EE4C(objectEntry[playerAndIndex].x,
                          objectEntry[playerAndIndex].y)) {
            func_8009DA70((u16)objectEntry[playerAndIndex].x,
                          (u16)objectEntry[playerAndIndex].y, colour, draw_param);
        }
    }

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
                 func_8009EE4C(largeMapEntry[playerAndIndex].x,
                               largeMapEntry[playerAndIndex].y))) {
                func_8009DA70(largeMapEntry[playerAndIndex].x,
                              largeMapEntry[playerAndIndex].y, colour, draw_param);
            }
        }
        playerAndIndex++;
    } while (playerAndIndex < 0x20);
}
