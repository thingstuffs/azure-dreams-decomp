#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800814A0;
extern void func_800478B8(void *, void *, s32, s32);
/* Advances and damps motion, then propagates collision flags. */
void func_80921A44(void *objectData, void *motionState, void *collisionState) {
    s32 velocityY;
    s32 velocityX;
    s32 nextX;
    s32 positionZ;

    velocityX = M2C_FIELD(motionState, s32 *, 0xC);
    velocityY = M2C_FIELD(motionState, s32 *, 0x10);
    nextX = M2C_FIELD(motionState, s32 *, 0) + M2C_FIELD(motionState, volatile s32 *, 0xC);
    positionZ = M2C_FIELD(motionState, volatile s32 *, 8);
    M2C_FIELD(motionState, volatile s32 *, 0) = nextX;
    M2C_FIELD(motionState, s32 *, 8) = positionZ + 0xFFFE8000;
    M2C_FIELD(motionState, volatile s32 *, 4) = (s32) (M2C_FIELD(motionState, s32 *, 4) + M2C_FIELD(motionState, s32 *, 0x10));
    M2C_FIELD(motionState, volatile s32 *, 0xC) = (s32) ((velocityX * 4) / 5);
    M2C_FIELD(motionState, s32 *, 0x10) = (s32) ((velocityY * 4) / 5);
    func_800478B8(collisionState, motionState, (s32) (velocityY * 4) >> 0x1F, (s32) (velocityX * 4) >> 0x1F);
    if (M2C_FIELD(collisionState, u16 *, 0x14) & 0x6000) {
        M2C_FIELD(objectData, u16 *, -2) = (u16) (M2C_FIELD(objectData, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
