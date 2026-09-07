#include "common.h"

extern void func_800C2E84(void *arg0, void *arg1, void *arg2);
extern void func_800C4174(void *arg0, s32 arg1, void *arg2);

extern u8 D_80082660[];
extern u8 D_800D6CA8[];

typedef struct {
    u8 pad0[0xC];
    u8 unkC;
    u8 unkD;
    u8 unkE;
} Func800CEC24Arg2;

/* Reset the object's table entry and brighten the packet to a clamped grayscale intensity. */
void func_800CC384(void *object, s32 draw_arg, Func800CEC24Arg2 *packet) {
    register u32 intensity ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

    func_800C2E84(object, packet, D_800D6CA8);
    D_80082660[*(s32 *)((u8 *)object + 0x60) * 8] = 0;

    intensity = packet->unkC + 0x20;
    if (intensity >= 0x100) {
        intensity = 0xFF;
    }

    packet->unkE = intensity;
    packet->unkD = intensity;
    packet->unkC = intensity;
    func_800C4174(object, draw_arg, packet);
}
