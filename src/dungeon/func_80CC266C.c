#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"


typedef struct S_80175E6C_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80175E6C_1;   /* arg2p in func_80175E6C */

typedef struct S_80175E6C_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80175E6C_2;   /* temp_v0 in func_80175E6C */

typedef struct S_80175E6C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80175E6C_3;   /* base in func_80175E6C */


typedef struct S_80175E6C_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80175E6C_5;   /* temp_v0_2 in func_80175E6C */

typedef struct S_80175E6C_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80175E6C_6_pre;   /* the 0x14 bytes before ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv in func_80175E6C, addressed as ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv[-1] */


void func_80047784(void *, u8, s32);
void *func_800A04F0(void *, u8, u8, s16);
s16 func_800A0818(u8, u8, u8, u8, s32 *);
s32 func_800A2C34(void *);
void func_800A9A0C(void *);
void func_80175E14(void *);
extern s16 D_80083228;
extern u8 D_80083460[];
extern u16 D_80083462;
extern u8 *D_800E3D7C;
extern u8 D_80176348[];

/* Selects a neighboring target and starts an action when the reference entity is nearby. */
s32 func_80175E6C(void *action_state, void *unused, void *actor_pos_arg, void *actor) {
    s32 distance;
    s32 neighbor_flags;
    s32 direction;
    s32 reference_found;
    s32 result;
    void *neighbor;
    void *target_pos;
    register void *target ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *global_state;

    target = NULL;
    ASM_KEEP_NV(target);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)actor)->unk_71.as_u8 & 0x7F);
    if ((D_80083462 & 0x2008) ||
        (reference_found = (s32) target, ((func_800A2C34(actor) << 0x10) != 0))) {
        goto return_failure;
    }
    direction = 0;
    goto scan_start;
return_failure:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    result = -1;
    goto done;
scan_start:
scan_neighbors:
    neighbor = func_800A04F0(actor, ((S_80175E6C_1 *)actor_pos_arg)->unk_24, ((S_80175E6C_1 *)actor_pos_arg)->unk_25, (s16) (direction << 9));
    if (neighbor != NULL) {
        if (neighbor == D_800E3D7C) {
            reference_found = 1;
            goto next_direction;
        }
        neighbor_flags = ((S_80175E6C_2 *)neighbor)->unk_14;
        if (neighbor_flags & 0x4000) {
            if (!(neighbor_flags & 0x20000000)) {
                target = neighbor;
            }
        }
        goto next_direction;
    }
next_direction:
    direction += 1;
    if (direction >= 8) {
        if ((target != NULL) && (reference_found & 0xFFFF)) {
            global_state = D_80083460;
            ASM_KEEP(reference_found);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            ((S_80175E6C_3 *)global_state)->unk_0A = (u16) (((S_80175E6C_3 *)global_state)->unk_0A + 1);
            ((Rec_D_800E3D7C *)actor)->unk_60.as_pv = target;
            func_800A9A0C(target);
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x17;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
            target_pos = ((S_80175E6C_6_pre *)(((Rec_D_800E3D7C *)actor)->unk_60.as_pv))[-1].unk_00;
            ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = func_800A0818(((S_80175E6C_1 *)actor_pos_arg)->unk_24, ((S_80175E6C_1 *)actor_pos_arg)->unk_25, ((S_80175E6C_5 *)target_pos)->unk_24, ((S_80175E6C_5 *)target_pos)->unk_25, &distance);
            (*(u8 **)((u8 *)actor_pos_arg + 0x2C)) = D_80176348;
            func_80047784(actor_pos_arg, D_80176348[((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
            func_80175E14(actor);
            result = 1;
            goto done;
        }
        result = 0;
        goto done;
    }
    goto scan_neighbors;
done:
    return result;
}
