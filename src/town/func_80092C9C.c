#include "common.h"

typedef s32 M2C_UNK;
typedef void (*ObjectCallback)(void *, s32, s32);
typedef void (*ActorCallback)(void *, void *, s32);


extern s32 func_800352FC(void);
extern void func_8008B158(void *owner);
extern s32 func_8008C180(s16 owner, s16 node_in);
extern void func_8008F664(void *owner, void *node_in);
extern void func_8009065C(void *owner, void *node_in, s32 mode);
extern void func_8009539C(void *owner);
extern void func_800953D0(void *owner);
extern void func_80095460(void *owner);
extern void func_8009550C(void *owner);
extern void func_80095910(void *owner);
extern s32 func_8009593C(void *owner);
extern s16 func_80095978(void *owner, void *node_in);
extern void func_80095A94(void *owner, s16 node_in, void *mode);
extern void func_80096FF4(void *owner);
extern void func_80098868(void *owner, void *node_in, s32 mode);
extern void func_800A573C(void *owner, void *node_in, s32 mode);
extern s32 func_800C1D44(u16 owner);

extern s16 D_8006ADD4[];
extern u8 D_80082BC0[];
extern u8 D_80090A64[];
extern u8 D_80097D2C[];
extern u8 D_800A5638[];
extern M2C_UNK D_800CFCB4;
extern u8 D_800FE488[];
extern M2C_UNK D_800FE490;


typedef struct S_800903FC_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_800903FC_0;   /* node_in in func_800903FC */

typedef struct S_800903FC_1 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x2];
    u16 unk_16;
} S_800903FC_1;   /* work in func_800903FC */

typedef struct S_800903FC_2 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x17];
    u8 unk_3B;
} S_800903FC_2;   /* base in func_800903FC */

typedef struct S_800903FC_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800903FC_3;   /* node in func_800903FC */

typedef struct S_800903FC_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800903FC_4;   /* ((S_800903FC_2 *)base)->unk_20 in func_800903FC */

/* Rebuild the town menu's node list for the current mode and hand it to the drawing pass. */
void func_800903FC(void *owner, S_800903FC_0 *node_in, s32 mode) {
    S_800903FC_3 *node;
    void *handler;
    u8 *base;
    u8 *object;
    u8 *work;
    s16 value;

    handler = (*(void * *)((u8 *)owner + (0)));
    if (handler != D_80097D2C || handler != D_80090A64) {
        func_800953D0(node_in);
    }
    func_8009539C(node_in);

    handler = (*(void * *)((u8 *)owner + (0)));
    if (handler != D_80097D2C || handler != D_80090A64) {
        func_80096FF4(node_in);
    }

    if (node_in->unk_08 > 0 && D_8006ADD4[0] != 12 &&
        node_in->unk_04.at00.v > 0x03FFFFFF) {
        if (func_800C1D44((u16)func_8008C180(node_in->unk_02,
                                                  node_in->unk_04.at02.v)) == 0) {
            node_in->unk_08 = 0;
        }
    }

    func_80095460(node_in);

    work = (u8 *)&D_800FE490;
    ((S_800903FC_1 *)work)->unk_16 = (*(u16 *)((u8 *)owner + (0x10)));
    func_80095910(work);
    if (func_8009593C(work) != 0) {
        (*(s32 *)((u8 *)owner + (0x2C))) = 0;
        func_8008B158(((S_800903FC_1 *)work)->unk_10);

        object = D_80082BC0;
        (*(ObjectCallback *)((u8 *)object + (0x10)))(object + 0x20, 0, 0);

        if (func_800352FC() != 0) {
            base = (u8 *)&D_800CFCB4;
            if (((S_800903FC_2 *)base)->unk_3B != 0) {
                node = ((S_800903FC_4 *)(((S_800903FC_2 *)base)->unk_20))->unk_08;
                if (node->unk_0C == 0 &&
                    node->unk_10 == 0 &&
                    node->unk_14 == 0) {
                    goto skip_update;
                }
            }

            {
                u8 *update_work;

                update_work = D_800FE488;
                value = func_80095978(node_in, update_work);
                func_80095A94(node_in, value, update_work);
            }

skip_update:
            func_8009550C(node_in);
            if ((*(void * *)((u8 *)owner + (0))) != D_80097D2C) {
                func_80098868(owner, node_in, mode);
            }
        }
    }

    func_8008F664(&D_800CFCB4, node_in);
    (*(ActorCallback *)((u8 *)owner + (0)))(owner, node_in, mode);

    if ((*(void * *)((u8 *)owner + (-0x10))) == D_800A5638) {
        func_800A573C(owner, node_in, mode);
        return;
    }
    func_8009065C(owner, node_in, mode);
}

/* MECHANISM: The 0x28 frame and s2/s1/s3 argument holds preserve the retail prologue.
   A block-local update_work separates D_800FE488 from the earlier work lifetime.
   GCC coalesces both to s0 and emits the two-edge lui/addiu held base. */
