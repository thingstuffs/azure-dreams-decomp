/* Relink of matched town/func_8046C280; every changed retail word is a paired relocation. */
#define D_8001902C D_8001B0D0
#define D_8001916C D_80016020
#define D_80019178 D_8001602C
#define D_8001917C D_80016030
#define D_80019184 D_80016038
#define D_80019190 D_80016044
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "common.h"


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


extern Lookup D_8001B0D0[][3];
extern s8 D_80016020[];
extern s8 D_8001602C[];
extern s8 D_80016030[];
extern s8 D_80016038[];
extern s8 D_80016044[];

/* Select a vertex relative to the list head, print its coordinates, and return its address. */
void *func_80018544(s32 group, s32 n, s32 lookup_variant) {
    s32 lookup_flag;
    s32 head;
    Entry *ptr;
    s32 delta;

    if (group >= 10) {
        return 0;
    }
    lookup_flag = D_8001B0D0[group][lookup_variant].flag;
    head = D_80016000->unk_38->headIndices[group];
    ptr = D_8001B0D0[group][lookup_variant].entries;
    D_80016000->unk_20->callback_168(D_80016020, D_8001602C, n);
    D_80016000->unk_20->callback_168(D_80016020, D_80016030, head);
    delta = n - head;
    if (lookup_flag != 0) {
        if (delta >= 0) {
            delta++;
            n = lookup_flag - delta;
        } else {
            n = head - n - 1;
        }
    }
    D_80016000->unk_20->callback_168(D_80016020, D_8001602C, n);
    D_80016000->unk_20->callback_168(D_80016020, D_80016038, ptr[n].vx);
    D_80016000->unk_20->callback_168(D_80016020, D_80016044, ptr[n].vy);
    return &ptr[n];
}
