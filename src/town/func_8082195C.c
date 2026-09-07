#include "common.h"

typedef struct S_8002415C_0_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_8002415C_0_pre;   /* the 0x8 bytes before node in func_8002415C, addressed as node[-1] */

typedef struct S_8002415C_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0xC];
    u16 unk_24;
} S_8002415C_0;   /* node in func_8002415C */

typedef struct S_8002415C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8002415C_1;   /* record in func_8002415C */



typedef struct PacketTag {
    unsigned addr : 24;
    unsigned len : 8;
} PacketTag;

#define setaddr(packet, address) (((PacketTag *)(packet))->addr = (u32)(address))
#define getaddr(packet) ((u32)(((PacketTag *)(packet))->addr))
#define addPrim(ordering_table, primitive) \
    (setaddr((primitive), getaddr(ordering_table)), \
     setaddr((ordering_table), (primitive)))

typedef struct RenderState {
    u8 pad0[0x8D0];
    u8 *next_prim;
} RenderState;

typedef struct TownState {
    RenderState *render_state;
} TownState;

extern TownState D_80083160;
extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80066640(void *, s32);
extern void func_800667BC(void *);
extern void func_80067F20(void *, s32, s32, u16, s32);

s32 func_8002415C(u8 *node)
{
    s32 coords[2];
    s32 *coord1p;
    TownState *global;
    RenderState *root;
    u8 *record;
    u8 *new_record;
    u8 *next;
    s16 first;
    s32 average;
    s32 offset;

    global = &D_80083160;
    coord1p = &coords[1];
    for (;;) {
        if (!(((S_8002415C_0 *)node)->unk_24 & 1)) {
            root = global->render_state;
            record = root->next_prim;
            root->next_prim = record + 0x10;
            ((S_8002415C_1 *)record)->unk_04 = ((S_8002415C_0 *)node)->unk_14;
            func_800667BC(record);
            func_80066640(record, 1);
            first = func_80065420(node + 4, record + 8,
                                  &coords[0], coord1p);
            average = (first + func_80065420(node + 0xC, record + 0xC,
                                             &coords[0], coord1p)) >> 1;
            if ((u16)average < 0x1E0U) {
                offset = (s16)average * 4;
                addPrim((u8 *)(offset + (s32)global->render_state) + 0xB0,
                        record);

                root = global->render_state;
                new_record = root->next_prim;
                root->next_prim = new_record + 0xC;
                func_80067F20(new_record, 0, 0,
                    func_80066460(0, 0, 0, 0) & 0xFFFF, 0);
                addPrim((u8 *)(offset + (s32)global->render_state) + 0xB0,
                        new_record);
            }
        }

        next = ((S_8002415C_0_pre *)node)[-1].unk_00;
        if (next != 0) {
            node = next + 0x20;
            continue;
        }
        break;
    }
    return 0;
}
