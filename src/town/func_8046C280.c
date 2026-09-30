#include "common.h"

typedef void (*Callback)();

typedef struct {
    u8 pad_00[0x168];
    Callback callback;
} CallbackBlock;

typedef struct {
    u8 pad_00[0x3700];
    u8 heads[1];
} ItemState;

typedef struct {
    u8 pad_00[0x20];
    CallbackBlock *callbacks;
    u8 pad_24[0x14];
    ItemState *items;
} Engine;

typedef struct {
    s16 vx;
    s16 vy;
    s32 unused;
} Entry;

typedef struct {
    s16 flag;
    s16 unused;
    Entry *entries;
} Lookup;

extern Engine *D_80016000;
extern Lookup D_8001902C[][3];
extern s8 D_8001916C[];
extern s8 D_80019178[];
extern s8 D_8001917C[];
extern s8 D_80019184[];
extern s8 D_80019190[];

/* Select a vertex relative to the list head, print its coordinates, and return its address. */
void *func_8001D280(s32 group, s32 n, s32 lookup_variant) {
    s32 lookup_flag;
    s32 head;
    Entry *ptr;
    s32 delta;

    if (group >= 10) {
        return 0;
    }
    lookup_flag = D_8001902C[group][lookup_variant].flag;
    head = D_80016000->items->heads[group];
    ptr = D_8001902C[group][lookup_variant].entries;
    D_80016000->callbacks->callback(D_8001916C, D_80019178, n);
    D_80016000->callbacks->callback(D_8001916C, D_8001917C, head);
    delta = n - head;
    if (lookup_flag != 0) {
        if (delta >= 0) {
            delta++;
            n = lookup_flag - delta;
        } else {
            n = head - n - 1;
        }
    }
    D_80016000->callbacks->callback(D_8001916C, D_80019178, n);
    D_80016000->callbacks->callback(D_8001916C, D_80019184, ptr[n].vx);
    D_80016000->callbacks->callback(D_8001916C, D_80019190, ptr[n].vy);
    return &ptr[n];
}
