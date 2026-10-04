#include "common.h"
extern int abs(int);
#include "shared/object_index_slots.h"
#include "m2c_compat.h"

struct S_80083178_L
{
    char pad0[2];
    unsigned short unk2;
    char pad4[6];
    unsigned short unkA;
    char padC[0x94];
    short f_A0;
    char pad_a2[2];
    short f_A4;
    short f_A6;
    short f_A8;
    char pad_aa[0xB4 - 0xAA];
    void (*callback)(void);
    void *field_B8;
    char pad_bc[(0xD8 - 0xB8) - 4];
    void *ptr;
    char pad_dc[0x1C4 - 0xDC];
};
extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;
extern unsigned char D_80071298[];
extern volatile int D_80071250[];
extern int D_800712B4[];
extern int D_80084130[3];
s32 func_8003BD84();
void func_80098928();
u16 func_800C2AE8();
extern M2C_UNK D_80099C18;
/* Set travel timing from distance and speed, or snap motion to the destination. */
void func_8009A1E8(void *actor, void *motion, M2C_UNK context)
{
    s32 base_ticks;
    s32 scaled_ticks;
    s32 distance;
    s32 speed_modifier;
    s32 modifier_magnitude;
    s8 *movement_state;
    *(((*((s32 *) (((s8 *) actor) + 0x40))) * 8) + ((u8 *)D_80082660)) = 0;
    *((M2C_UNK **) (((s8 *) actor) + 4)) = &D_80099C18;
    distance = func_8003BD84(((*((s16 *) (((s8 *) actor) + 0x36))) << 0x10) - (*((s32 *) (((s8 *) motion) + 0))),
        ((*((s16 *) (((s8 *) actor) + 0x38))) << 0x10) - (*((s32 *) (((s8 *) motion) + 4))));
    if (distance < 0) {
        distance += 0x1FFFF;
    }
    movement_state = (s8 *) (((*((s32 *) (((s8 *) actor) + 0x40))) * 8) + ((u8 *)D_80082660));
    base_ticks = distance >> 0x11;
    *((s16 *) (((s8 *) actor) + 0xA)) = (s16) base_ticks;
    speed_modifier = *((s8 *) (movement_state + 2));
    if (speed_modifier == (-0x80)) {
        *((s32 *) (((s8 *) motion) + 0)) = (s32) ((*((s16 *) (((s8 *) actor) + 0x36))) << 0x10);
        *((s32 *) (((s8 *) motion) + 4)) = (s32) ((*((s16 *) (((s8 *) actor) + 0x38))) << 0x10);
        *((u16 *) (((s8 *) motion) + 0xA)) = (u16) ((*((u16 *) (((s8 *) motion) + 0xA))) - 0x80);
        *((u16 *) (((s8 *) motion) + 0xA)) = func_800C2AE8(motion);
        func_80098928(actor, motion, context);
        return;
    }
    if (speed_modifier > 0) {
        *((s16 *) (((s8 *) actor) + 0xA)) = (s16) ((base_ticks << 4) / (speed_modifier + 0x10));
        return;
    }
    if (speed_modifier < 0) {
        modifier_magnitude = abs(speed_modifier);
        scaled_ticks = base_ticks * (modifier_magnitude + 0x10);
        if (scaled_ticks < 0) {
            scaled_ticks += 0xF;
        }
        *((s16 *) (((s8 *) actor) + 0xA)) = (s16) (scaled_ticks >> 4);
    }
}
