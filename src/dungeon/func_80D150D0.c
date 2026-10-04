#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_801748D0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801748D0_0;   /* arg0 in func_801748D0 */


typedef struct S_801748D0_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_801748D0_2;   /* arg2 in func_801748D0 */

typedef struct S_801748D0_3 {
    u8 pad_00[0x94];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
    u8 pad_A4[0x4];
    void * unk_A8;
} S_801748D0_3;   /* body in func_801748D0 */

typedef struct S_801748D0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    void * unk_0C;
    void * unk_10;
} S_801748D0_4;   /* obj in func_801748D0 */


typedef struct S_801748D0_6_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_801748D0_6_pre;   /* the 0x18 bytes before body_link in func_801748D0, addressed as body_link[-1] */

typedef struct S_801748D0_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_801748D0_7;   /* mesh in func_801748D0 */

typedef struct S_801748D0_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801748D0_9;   /* anchor in func_801748D0 */

typedef struct S_801748D0_10 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_801748D0_10;   /* scratch in func_801748D0 */

typedef struct S_801748D0_11 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_801748D0_11;   /* link in func_801748D0 */


extern s32 func_8003DE58(s32, void *, s16 *, s16);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_800C8788(void *, void *);

extern s8 D_800DCECC[];
extern u8 D_80170AD0[];
extern u8 D_80171760[];
extern u8 D_80174E88[];
extern u8 D_80174ED0[];

typedef struct {
    s16 delta[3];
    u16 pad06;
    u16 pos[3];
    u16 pad0E;
    s32 out0[2];
    s32 out1;
    s32 out2;
} LocalFrame;

typedef struct {
    s32 w[12];
} MeshCopy;

/* Advances a timed actor effect, spawning and positioning its visual object before cleanup. */
void func_801748D0(void *effect_state, EntityRec *position, void *source_mesh, EntityRec *actor)
{
    LocalFrame frame;
    void *effect_body;
    S_801748D0_7 *effect_mesh;
    void *anchor_pos;
    S_801748D0_11 *owner_link;
    void *linked_owner;
    void *linked_body;
    void *owner;
    s16 count;
    s32 object_or_height;
    s32 anchor_height;
    s32 first_height;
    u16 timer;
    u16 anchor_z;
    u16 flags;
    s32 call_value;
    s32 mesh_flags;
    s32 lookup_value;
    s32 phase;

    owner = (u8 *)effect_state - 0x20;
    phase = ((S_801748D0_0 *)effect_state)->unk_9B;
    switch (phase) {
    case 0:
        position->flags14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        timer = ((S_801748D0_0 *)effect_state)->unk_96 - 1;
        ((S_801748D0_0 *)effect_state)->unk_96 = timer;
        if (((s32)(timer << 16) <= 0) ||
            (((S_801748D0_2 *)source_mesh)->unk_14 & 0x8000)) {
            ((S_801748D0_0 *)effect_state)->unk_96 = 0;
            ((S_801748D0_0 *)effect_state)->unk_9B++;
            flags = ((S_801748D0_2 *)source_mesh)->unk_14;
            ((S_801748D0_2 *)source_mesh)->unk_14 = flags & 0xF7FF;
        }
        return;
    case 1:
        if (!(((S_801748D0_2 *)source_mesh)->unk_14 & 0x8000)) {
            func_800A56E0(0x80D);
        }
        count = 0;
        do {
            object_or_height = (s32)func_8003FD64(0x112, &D_80083498);
            effect_body = (u8 *)((void *)object_or_height);
            effect_body += 0x20;
            if (((void *)object_or_height) == 0) {
                continue;
            }
            ((S_801748D0_3 *)effect_body)->unk_96 = 0x2D;
            ((S_801748D0_3 *)effect_body)->unk_9E = 0x2D;
            ((S_801748D0_4 *)((void *)object_or_height))->unk_10 = D_80170AD0;
            linked_body = actor->target;
            if (linked_body == 0) {
                ((S_801748D0_3 *)effect_body)->unk_A8 = position;
                ((S_801748D0_3 *)effect_body)->unk_A2 = 0;
            } else {
                linked_owner = ((S_801748D0_6_pre *)linked_body)[-1].unk_00;
                ((S_801748D0_3 *)effect_body)->unk_A2 = 1;
                ((S_801748D0_3 *)effect_body)->unk_A8 = linked_owner;
            }
            ((S_801748D0_3 *)effect_body)->unk_94 = actor->facing;
            effect_mesh = ((S_801748D0_4 *)((void *)object_or_height))->unk_0C;
            anchor_pos = ((S_801748D0_3 *)effect_body)->unk_A8;
            *(MeshCopy *)effect_mesh = *(MeshCopy *)source_mesh;
            mesh_flags = effect_mesh->unk_14;
            effect_mesh->unk_1E = 0x400;
            effect_mesh->unk_1C = 0x400;
            effect_mesh->unk_0E = 0x80;
            effect_mesh->unk_0D = 0x80;
            effect_mesh->unk_0C = 0x80;
            effect_mesh->unk_10 = 0x20;
            effect_mesh->unk_12 = 0xFF80;
            mesh_flags |= 0xC;
            effect_mesh->unk_14 = mesh_flags;
            func_8004491C((void *)object_or_height, func_80045340);
            call_value = D_80174ED0[0];
            effect_mesh->unk_2C = D_80174ED0;
            func_80047784(effect_mesh, call_value, 0);
            object_or_height = (s32)((S_801748D0_4 *)((void *)object_or_height))->unk_08.at00.v;
            ((S_801748D0_4 *)((void *)object_or_height))->unk_02 = ((S_801748D0_9 *)anchor_pos)->unk_02;
            ((S_801748D0_4 *)((void *)object_or_height))->unk_06 = ((S_801748D0_9 *)anchor_pos)->unk_06;
            anchor_z = ((S_801748D0_9 *)anchor_pos)->unk_0A;
            ((S_801748D0_4 *)((void *)object_or_height))->unk_08.at02.v = anchor_z;
            if (actor->target == 0) {
                owner_link = ((S_801748D0_10 *)owner)->unk_0C;
                if (func_8003DE58(owner_link->unk_08, owner_link, frame.delta, 0) != 0) {
                    ((S_801748D0_4 *)((void *)object_or_height))->unk_02 += frame.delta[0];
                    ((S_801748D0_4 *)((void *)object_or_height))->unk_06 += frame.delta[1];
                    ((S_801748D0_4 *)((void *)object_or_height))->unk_08.at02.v += frame.delta[2];
                }
                frame.pos[0] = ((S_801748D0_4 *)((void *)object_or_height))->unk_02;
                frame.pos[1] = ((S_801748D0_4 *)((void *)object_or_height))->unk_06;
                frame.pos[2] = ((S_801748D0_4 *)((void *)object_or_height))->unk_08.at02.v;
                first_height = func_80065420(frame.pos, frame.out0, &frame.out1, &frame.out2);
                mesh_flags = ((S_801748D0_9 *)anchor_pos)->unk_02;
                frame.pos[0] = mesh_flags;
                mesh_flags = ((S_801748D0_9 *)anchor_pos)->unk_06;
                frame.pos[1] = mesh_flags;
                mesh_flags = ((S_801748D0_9 *)anchor_pos)->unk_0A;
                frame.pos[2] = mesh_flags;
                anchor_height = func_80065420(frame.pos, frame.out0, &frame.out1, &frame.out2);
                lookup_value = D_800DCECC[((gameWork.view.viewAngle + (s16)((S_801748D0_3 *)effect_body)->unk_94 + 0x100)
                    >> 9) & 7];
                effect_mesh->unk_06 = first_height - anchor_height - (lookup_value << 1);
                continue;
            }
            ((S_801748D0_4 *)((void *)object_or_height))->unk_08.at02.v = anchor_z - 0x1E;
            effect_mesh->unk_06 = 4;

        } while (++count < 1);
        ((S_801748D0_0 *)effect_state)->unk_96 = 0x2D;
        ((S_801748D0_0 *)effect_state)->unk_9B++;
        return;
    case 2:
        if (((S_801748D0_2 *)source_mesh)->unk_14 & 0xE000) {
            if (((S_801748D0_2 *)source_mesh)->unk_2C != D_80174E88) {
                ((S_801748D0_2 *)source_mesh)->unk_2C = D_80174E88;
                ((S_801748D0_2 *)source_mesh)->unk_14 &= 0xF7FF;
                func_80047784(source_mesh, ((u8 *)((S_801748D0_2 *)source_mesh)->unk_2C)[((gameWork.view.viewAngle
                    + actor->facing + 0x100) >> 9) & 7], 0);
            }
        }
        if (!(((S_801748D0_2 *)source_mesh)->unk_14 & 0x8000)) {
            timer = ((S_801748D0_0 *)effect_state)->unk_96 - 1;
            ((S_801748D0_0 *)effect_state)->unk_96 = timer;
            if ((s32)(timer << 16) > 0) {
                return;
            }
        }
        position->flags14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        func_800A2B04(position, ((S_801748D0_2 *)source_mesh)->unk_24, ((S_801748D0_2 *)source_mesh)->unk_25);
        if (((S_801748D0_2 *)source_mesh)->unk_2C != D_80174E88) {
            ((S_801748D0_2 *)source_mesh)->unk_2C = D_80174E88;
            ((S_801748D0_2 *)source_mesh)->unk_14 &= 0xF7FF;
            func_80047784(source_mesh, ((u8 *)((S_801748D0_2 *)source_mesh)->unk_2C)[((gameWork.view.viewAngle
                + actor->facing + 0x100) >> 9) & 7], 0);
        }
        ((S_801748D0_0 *)effect_state)->unk_9B++;
        return;
    case 3:
        owner_link = actor->target;
        if (owner_link != 0) {
            func_800C8788(actor, owner_link);
        }
        func_800AD594(actor, 0x400);
        ((S_801748D0_0 *)effect_state)->unk_8C = D_80171760;
        dungeonStatus.unk_0C = 0;
        actor->unk_46 &= 0x7FFF;

        return;
    }
}
