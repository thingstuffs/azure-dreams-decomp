#ifndef DUNGEON_OVL_C9B084_H
#define DUNGEON_OVL_C9B084_H
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"



typedef struct Scratch {
    u8 pad0[4];
    u16 in0;
    u16 in1;
    u16 in2;
    u8 pad0A[0x12];
    u8 *current;
    u8 pad20[4];
    u8 *table;
    u8 pad28[0xA8];
    u16 out0;
    u16 padD2;
    u16 out1;
    u8 padD4[0x2A];
    s32 index;
} Scratch;

typedef struct Packet {
    u8 pad0[3];
    u8 code;
    union {
        u32 link;
        struct {
            u8 r;
            u8 g;
            u8 b;
            u8 command;
        } color;
    } data;
} Packet;

extern s32 RotTransPers(void *, void *, void *, void *);
extern s32 GetTPage(s32, s32, s32, s32);
extern void SetDrawMode(void *, s32, s32, u16, s32);

s32 queue_linked_render_packets(u8 *entry_data, u16 *position);
#endif
