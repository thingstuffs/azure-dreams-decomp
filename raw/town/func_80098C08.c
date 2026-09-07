#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused[3];
} Vec3s32;

extern s16 func_8008CA20();
extern void func_80096424(void) __attribute__((noreturn));
extern void *D_800D0410[3];
extern s32 D_800FE5CC[3];

s32 func_80096368(Vec3s32 *arg0) {
    Vec3s32 pos;
    s16 first;
    register s32 second ASM_REG("$2");
    s32 delta;
    register s32 magnitude ASM_REG("$3");
    register s32 limit ASM_REG("$2");

    pos.x = arg0->x;
    pos.y = arg0->y;
    pos.z = arg0->z;
    first = func_8008CA20(&pos, D_800D0410[0], 6);
    {
        register s32 *d8010_page ASM_REG("$3") = (s32 *)0x80100000;
        ASM_KEEP(d8010_page);
        delta = d8010_page[-0x68D];
        ASM_KEEP(delta);
    }
    limit = 0x140000;
    ASM_KEEP(limit);
    magnitude = delta;
    if (delta < 0) {
        magnitude = -magnitude;
    }
    if (magnitude <= limit) {
        register Vec3s32 *tail_arg ASM_REG("$4") = &pos;
        register s32 tail_value ASM_REG("$2") = (s16)first;
        ASM_KEEP(tail_arg);
        ASM_TAILSLOT_PIN_TIED(tail_value);
        func_80096424();
    }
    pos.x = arg0->x - (delta / 2);
    second = func_8008CA20(&pos, D_800D0410[0], 6, delta);
    if (second >= first) {
        second = first;
    }
    return second;
}
