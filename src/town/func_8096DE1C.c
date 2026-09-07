#include "common.h"

typedef struct Inner {
    u16 pad0;
    u16 value;
} Inner;

typedef struct Entry {
    u32 word0;
    u32 pad4;
    Inner *inner;
} Entry;

typedef struct TownContext {
    u8 pad0[0x70];
    void **slot70;
} TownContext;

typedef struct TownObject {
    u8 pad0[4];
    u16 state;
    u8 pad6[0x52];
    TownContext *context;
} TownObject;

extern Entry *D_80129728[28];

extern void func_80123754(void);
extern void func_80124728(TownObject *);
extern void func_801235EC(void);
extern void func_801247F8(TownObject *);

void func_801262B4(TownObject *obj)
{
    switch ((s16)(obj->state - 1)) {
    case 0:
        *obj->context->slot70 = 0;
        func_80123754();
        func_80124728(obj);
        func_801235EC();
        func_801247F8(obj);
        break;

    case 7:
    case 8:
    case 9: {
        s32 i;
        Entry **base;
        Entry *entry;
        Inner *inner;

        do { i = 14; } while (0);
        base = D_80129728;
        do {
            entry = base[i];
            inner = entry->inner;
            inner->value += 0x100;
            i++;
        } while (i < 28);
        break;
    }

    case 10: {
        s32 i;
        Entry **base;
        Entry *entry;
        Inner *inner;

        i = 16;
        base = D_80129728;
        do {
            base[i]->word0 = 0;
            i++;
        } while (i < 28);

    case 11:
    case 12:
    case 13:
        i = 14;
        base = D_80129728;
        do {
            entry = base[i];
            inner = entry->inner;
            inner->value += 0x100;
            i++;
        } while (i < 28);
        break;
    }

    case 14: {
        s32 i;
        Entry **base;
        Entry *entry;
        Inner *inner;

        i = 14;
        base = D_80129728;
        do {
            entry = base[i];
            inner = entry->inner;
            inner->value += 0x100;
            i++;
        } while (i < 28);

        i = 14;
        base = D_80129728;
        do {
            base[i]->word0 = 0;
            i++;
        } while (i < 16);
        break;
    }

    case 19:
    default:
        break;
    }
}

/* MECHANISM: The true-space rowbase function naturally forms retail's 0x18 frame and s0-held object.
   Narrowing state-1 to s16 restores the two-word sll/sra switch-index sequence.
   Shared locals across the case-10 fallthrough preserve retail's a0 index and a1 base coloring. */
