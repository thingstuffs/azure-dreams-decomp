#include "common.h"

extern void *D_80016000;
extern u8 D_80016524[];
extern u8 D_80016578[];
extern u8 D_800165CC[];
extern u8 D_80016620[];
extern u8 D_80016674[];
extern void *D_80017C7C;

/* Selects a data table using the current object's ID at offset 8. */
void func_80016840(void) {
    switch (*(s32 *)((u8 *)D_80016000 + 8)) {
    case 37:
        D_80017C7C = D_80016524;
        return;
    case 38:
        D_80017C7C = D_80016578;
        return;
    case 39:
        D_80017C7C = D_800165CC;
        return;
    case 40:
        D_80017C7C = D_80016620;
        return;
    default:
        D_80017C7C = D_80016674;
        return;
    }
}
