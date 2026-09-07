#include "common.h"
typedef struct { s32 x; s32 y; s32 z; } Vec3;
typedef struct { s16 field_0; s16 angle; } Rotation;
extern s32 func_800644B8(s32); extern s32 func_80064584(s32);
extern void func_800A2AF8(Vec3 *, Vec3 *); extern void func_800A9E68(Vec3 *, Vec3 *);
extern s32 D_80100D1C; extern u16 D_80100D40, D_80100D42, D_80100D80, D_80100D82;
extern Vec3 D_80100D48, D_80100D68; extern Rotation D_80100D60;

static inline s32 add_x_and_get_angle(Vec3 *position, s32 product, Rotation *rotation)
{
    s32 secondAngle=rotation->angle;
    position->x += product;
    return secondAngle;
}
void func_800A9F14(Vec3 *arg0)
{
    s32 angle; s32 scale; Vec3 *position=&D_80100D68; s16 first;
    ++arg0; --arg0;
    D_80100D40 += D_80100D80;
    {
        Rotation *rotation=&D_80100D60;
        first=rotation->angle; angle=first;
        position->x=arg0->x; position->y=arg0->y; position->z=arg0->z;
        D_80100D42 += D_80100D82;
        position->y += func_80064584(add_x_and_get_angle(
            position, func_800644B8(angle)*D_80100D1C, rotation))*D_80100D1C;
        func_800A2AF8(position,arg0); scale=D_80100D1C;
        D_80100D48.x=arg0->x+scale*0x1800; D_80100D48.y=arg0->y; D_80100D48.z=arg0->z;
        func_800A9E68(&D_80100D48,arg0);
    }
}
