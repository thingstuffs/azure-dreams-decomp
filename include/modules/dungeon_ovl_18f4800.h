#ifndef DUNGEON_OVL_18F4800_H
#define DUNGEON_OVL_18F4800_H
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
typedef struct Packed12 { u8 bytes[12]; } __attribute__((packed)) Packed12;
typedef struct Packed8 { u8 bytes[8]; } __attribute__((packed)) Packed8;
typedef union PackedOffsets {
    struct { s16 x; u16 y; } pairs[8];
    struct { Packed12 first; Packed12 second; Packed8 third; } copy;
    u8 bytes[32];
} __attribute__((packed)) PackedOffsets;
struct Actor33;
struct Motion33;
struct Render33;
void func_80024668(struct Actor33 *, struct Motion33 *, struct Render33 *);
s32 func_80024044(void *, void *);
void func_80024294(void *, void *);
void func_80024394(ObjectNodeHeader *, s32, s32, s32, s32, s32, s32);
struct RenderFade33;
void func_80024548(void *, s32, struct RenderFade33 *);
extern const PackedOffsets dungeon_18f4800_offsets;
extern s16 D_80025118[5];
#endif
