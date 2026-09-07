#include "common.h"

#include "common.h"

s32 func_8003F5D4();                                /* extern */
extern s32 D_80084758;
extern s32 D_8008475C;
extern s32 D_80084760;
extern s32 D_80084764;

/* Store the fetched value in the global selected by the low 16 bits. */
void func_800558FC(s32 selector) {
    s32 slot_id;
    s32 value;

    value = func_8003F5D4();
    slot_id = selector & 0xFFFF;
    switch (slot_id) {                              /* irregular */
    case 17:
        D_80084758 = value;
        return;
    case 18:
        D_8008475C = value;
        return;
    case 20:
        D_80084760 = value;
        return;
    case 24:
        D_80084764 = value;
        return;
    }
}
