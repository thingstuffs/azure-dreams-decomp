#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct {
    u8 pad[0xC];
    s32 x;
    s32 y;
} Actor;

typedef struct {
    u8 pad0[8];
    s32 field8;
    u8 padC[0xBC];
    s16 fieldC8;
} TownState;

extern TownState D_80083160;
extern s16 func_80094BC8(s32, s16);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_800652AC(Vec3 *, Vec3 *, Vec3 *);

void func_800951B4(Actor *actor)
{
    Vec3 first;
    volatile Vec3 delta;
    Vec3 point;
    Vec3 result;
    s16 index;
    s32 status;
    s32 value;
    s32 dx;
    s32 dy;
    TownState *town;
    Vec3 *call_first;
    Vec3 *call_point;
    Vec3 *call_result;

    town = &D_80083160;
    ASM_KEEP(town);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    index = func_80094BC8(town->field8, town->fieldC8);
    if (index == -1) {
        return;
    }

    first.x = func_800644B8(index);
    first.y = func_80064584(index);
    first.z = 0;

    value = actor->x;
    if (value < 0) {
        value += 0xFFF;
    }
    point.x = value >> 12;

    call_first = &first;
    value = actor->y;
    if (value < 0) {
        value += 0xFFF;
    }
    call_point = &point;
    call_result = &result;
    ASM_KEEP(call_result);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    point.y = value >> 12;
    point.z = 0;

    func_800652AC(call_first, call_point, call_result);
    status = result.z;

    if (status >= 0) {
        s32 x;
        s32 y;

        y = first.y;
        x = first.x;
        dx = y << 5;
        dy = -x;
    } else {
        s32 x;
        s32 y;

        y = first.y;
        x = first.x;
        dx = (-y) << 5;
        dy = x;
    }
    dy <<= 5;
    delta.x = dx;
    delta.y = dy;

    value = actor->x + delta.x;
    if (value < 0) {
        value += 0xFFF;
    }
    point.x = value >> 12;

    call_first = &first;
    value = actor->y + delta.y;
    if (value < 0) {
        value += 0xFFF;
    }
    call_point = &point;
    call_result = &result;
    ASM_KEEP(call_result);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    point.y = value >> 12;
    point.z = 0;

    func_800652AC(call_first, call_point, call_result);
    if (status >= 0) {
        if (result.z < 0) {
            return;
        }
    } else if (result.z >= 0) {
        return;
    }

    actor->x += delta.x;
    actor->y += delta.y;
}
