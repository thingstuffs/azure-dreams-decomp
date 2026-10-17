/* Relink of matched dungeon/func_80D150D0; every changed retail word is a paired relocation. */
#define dungeonAdvanceTimedActorVisualEffect func_801628D0
#define D_80174E88 D_80162E88
#define D_80174ED0 D_80162ED0
#define dungeonUpdateActorBehaviorAndDirection D_8015F760
#include "modules/dungeon_ovl_7f43f800_p08.h"
extern void func_8015EAD0(void *, void *, void *);
extern s32  func_80065420(void *,void *,void *,void *);

/* Advances a timed actor effect, spawning and positioning its visual object before cleanup. */
void func_801628D0(void *effect_state, EntityRec *position, void *source_mesh, EntityRec *actor)
{
    T_801748D0_LocalFrame frame;
    void *effect_body;
    T_801748D0_S_801748D0_7 *effect_mesh;
    void *anchor_pos;
    T_801748D0_S_801748D0_11 *owner_link;
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
    phase = ((T_801748D0_S_801748D0_0 *)effect_state)->unk_9B;
    switch (phase) {
    case 0:
        position->flags14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        timer = ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 - 1;
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 = timer;
        if (((s32)(timer << 16) <= 0) ||
            (((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 & 0x8000)) {
            ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 = 0;
            ((T_801748D0_S_801748D0_0 *)effect_state)->unk_9B++;
            flags = ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14;
            ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 = flags & 0xF7FF;
        }
        return;
    case 1:
        if (!(((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 & 0x8000)) {
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
            ((T_801748D0_S_801748D0_3 *)effect_body)->unk_96 = 0x2D;
            ((T_801748D0_S_801748D0_3 *)effect_body)->unk_9E = 0x2D;
            ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_10 = func_8015EAD0;
            linked_body = actor->target;
            if (linked_body == 0) {
                ((T_801748D0_S_801748D0_3 *)effect_body)->unk_A8 = position;
                ((T_801748D0_S_801748D0_3 *)effect_body)->unk_A2 = 0;
            } else {
                linked_owner = ((T_801748D0_S_801748D0_6_pre *)linked_body)[-1].unk_00;
                ((T_801748D0_S_801748D0_3 *)effect_body)->unk_A2 = 1;
                ((T_801748D0_S_801748D0_3 *)effect_body)->unk_A8 = linked_owner;
            }
            ((T_801748D0_S_801748D0_3 *)effect_body)->unk_94 = actor->facing;
            effect_mesh = ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_0C;
            anchor_pos = ((T_801748D0_S_801748D0_3 *)effect_body)->unk_A8;
            *(T_801748D0_MeshCopy *)effect_mesh = *(T_801748D0_MeshCopy *)source_mesh;
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
            call_value = D_80162ED0[0];
            effect_mesh->unk_2C = D_80162ED0;
            func_80047784(effect_mesh, call_value, 0);
            object_or_height = (s32)((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_08.at00.v;
            ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_02 = ((T_801748D0_S_801748D0_9 *)anchor_pos)->unk_02;
            ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_06 = ((T_801748D0_S_801748D0_9 *)anchor_pos)->unk_06;
            anchor_z = ((T_801748D0_S_801748D0_9 *)anchor_pos)->unk_0A;
            ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_08.at02.v = anchor_z;
            if (actor->target == 0) {
                owner_link = ((T_801748D0_S_801748D0_10 *)owner)->unk_0C;
                if (resolveRecordOrientationOrFallback(owner_link->unk_08, owner_link, frame.delta, 0) != 0) {
                    ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_02 += frame.delta[0];
                    ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_06 += frame.delta[1];
                    ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_08.at02.v += frame.delta[2];
                }
                frame.pos[0] = ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_02;
                frame.pos[1] = ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_06;
                frame.pos[2] = ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_08.at02.v;
                first_height = func_80065420(frame.pos, frame.out0, &frame.out1, &frame.out2);
                mesh_flags = ((T_801748D0_S_801748D0_9 *)anchor_pos)->unk_02;
                frame.pos[0] = mesh_flags;
                mesh_flags = ((T_801748D0_S_801748D0_9 *)anchor_pos)->unk_06;
                frame.pos[1] = mesh_flags;
                mesh_flags = ((T_801748D0_S_801748D0_9 *)anchor_pos)->unk_0A;
                frame.pos[2] = mesh_flags;
                anchor_height = func_80065420(frame.pos, frame.out0, &frame.out1, &frame.out2);
                lookup_value = D_800DCECC[((gameWork.view.viewAngle + (s16)((T_801748D0_S_801748D0_3 *)effect_body)->unk_94 + 0x100)
                    >> 9) & 7];
                effect_mesh->unk_06 = first_height - anchor_height - (lookup_value << 1);
                continue;
            }
            ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_08.at02.v = anchor_z - 0x1E;
            effect_mesh->unk_06 = 4;

        } while (++count < 1);
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 = 0x2D;
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_9B++;
        return;
    case 2:
        if (((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 & 0xE000) {
            if (((T_801748D0_S_801748D0_2 *)source_mesh)->unk_2C != D_80162E88) {
                ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_2C = D_80162E88;
                ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 &= 0xF7FF;
                func_80047784(source_mesh, ((u8 *)((T_801748D0_S_801748D0_2 *)source_mesh)->unk_2C)[((gameWork.view.viewAngle
                    + actor->facing + 0x100) >> 9) & 7], 0);
            }
        }
        if (!(((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 & 0x8000)) {
            timer = ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 - 1;
            ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 = timer;
            if ((s32)(timer << 16) > 0) {
                return;
            }
        }
        position->flags14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(position, ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_24, ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_25);
        if (((T_801748D0_S_801748D0_2 *)source_mesh)->unk_2C != D_80162E88) {
            ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_2C = D_80162E88;
            ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 &= 0xF7FF;
            func_80047784(source_mesh, ((u8 *)((T_801748D0_S_801748D0_2 *)source_mesh)->unk_2C)[((gameWork.view.viewAngle
                + actor->facing + 0x100) >> 9) & 7], 0);
        }
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_9B++;
        return;
    case 3:
        owner_link = actor->target;
        if (owner_link != 0) {
            func_800C8788(actor, owner_link);
        }
        dungeonReduceActorFoodMeter(actor, 0x400);
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_8C = dungeonUpdateActorBehaviorAndDirection;
        dungeonStatus.unk_0C = 0;
        actor->unk_46 &= 0x7FFF;

        return;
    }
}
