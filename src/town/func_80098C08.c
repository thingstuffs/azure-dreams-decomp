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
    register s32 second ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 delta;
    register s32 magnitude ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 limit ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    pos.x = arg0->x;
    pos.y = arg0->y;
    pos.z = arg0->z;
    first = func_8008CA20(&pos, D_800D0410[0], 6);
    {
        s32 *d8010_page = (s32 *)0x80100000;
        ASM_KEEP(d8010_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        delta = d8010_page[-0x68D];
    }
    limit = 0x140000;
    magnitude = delta;
    if (delta < 0) {
        magnitude = -magnitude;
    }
    if (magnitude <= limit) {
        Vec3s32 *tail_arg = &pos;
        s32 tail_value = (s16)first;
        ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_80096424();
    }
    pos.x = arg0->x - (delta / 2);
    second = func_8008CA20(&pos, D_800D0410[0], 6, delta);
    if (second >= first) {
        second = first;
    }
    return second;
}
