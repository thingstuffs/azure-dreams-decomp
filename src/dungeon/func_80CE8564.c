#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/entity.h"

typedef struct S_80171D64_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80171D64_2;   /* position in func_80171D64 */

typedef struct S_80171D64_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80171D64_4;   /* the record, addressed through its copy in func_80171D64 */


extern void *func_8003FD64();
extern void func_8004491C();
extern void func_80047784();
extern void func_800A48F0();
extern s32 func_800A6D30();
extern void func_800A9C18();
extern void func_800AA36C();

extern s8 D_800E2968;
extern u8 D_801720B4[];
extern u8 D_801724BC[];
extern u8 D_80175E24[];
extern u8 D_80175E2C[];
extern u8 D_80175E34[];
extern u8 D_80175E54[];
extern u8 D_80175E5C[];
extern u8 D_80175E64[];

/* Creates an object and initializes its position, flags, and directional frame table. */
void *func_80171D64(s32 spawn_flags, s32 sprite_x, s32 sprite_y, s32 initial_height)
{
    s32 record_addr;
    EntityRec *result;
    s16 saved_x;
    s16 saved_y;
    EntityRec *sprite;
    s16 init_flags;
    ObjectNodeHeader *object;
    register void *position ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 call_object;
    s32 call_position;
    s32 alternate_kind;
    s32 state_flags;
    void *new_frames;
    s32 kind;
    s32 mode;
    u32 global_kind;
    u32 branch_flags;
    void *current_frames;
    u8 *frame_table;
    s32 default_frames;

    result = 0;
    call_object = 0x112;
    saved_x = sprite_x;
    call_position = (s32)((u8 *)(&D_80083498));
    saved_y = sprite_y;
    object = func_8003FD64(call_object, (void *)call_position);
    init_flags = spawn_flags;
    if (object != 0) {
        result = (EntityRec *)((u8 *)object + 0x20);
        object->unk_10 = D_801720B4;
        *(s8 *)((u8 *)result + 0x13) = 0x16;
        func_8004491C(object, func_80045340);

        default_frames = (s32)D_80175E24;
        call_position = 0xE;
        position = object->unk_08;
        alternate_kind = 0xF;
        ((S_80171D64_2 *)position)->unk_0A = initial_height;
        sprite = object->unk_0C;
        mode = spawn_flags & 3;
        *(void **)((u8 *)sprite + 0x2C) = (void *)default_frames;
        default_frames = 0x20;
        sprite->tileY = saved_y;
        record_addr = (s32)result;
        sprite->tileX = saved_x;
        result->unk_4B = default_frames;
        result->unk_48 = call_position;
        result->unk_49 = alternate_kind;

        if (mode == 1) {
            (*(u32 *)((u8 *)result + 0x14)) |= 0x6000;
            branch_flags = result->flags1C;
            global_kind = (u8)D_800E2968;
            result->flags1C = branch_flags | 0x6000;
            if (global_kind >= 0xA) {
                if (global_kind < 0xD) {
                    result->unk_48 = alternate_kind;
                } else {
                    result->unk_48 = 0xD;
                }
            }
        } else {
            if (mode >= 2) {
                result->flags14 |= 0x2000;
                result->flags1C |= 0x2000;
            } else {
                global_kind = (u8)D_800E2968;
                if (global_kind < 0xA) {
                    result->unk_48 = call_position;
                } else if (global_kind < 0xD) {
                    result->unk_48 = alternate_kind;
                } else {
                    result->unk_48 = 0xD;
                }

                if (((init_flags & ~3) << 16) == 0) {
                    call_object = (s32)object;
                    call_position = (s32)position;
                    if (!(result->flags14 & 0x200)) {
                        call_object = func_800A6D30((void *)call_object, (void *)call_position);
                        state_flags = call_object;
                        call_object = (s32)object;
                        if (state_flags & 1) {
                            func_800A48F0(result, 1,
                                (func_800A6D30((void *)call_object) & 0x3F) | 0x20);
                            kind = result->unk_48;
                            switch (kind) {
                            case 0xD:
                                current_frames = *(void **)((u8 *)sprite + 0x2C);
                                new_frames = D_80175E54;
                                if (current_frames != new_frames) {
                                    *(void **)((u8 *)sprite + 0x2C) = new_frames;
                                }
                                break;
                            case 0xE:
                                current_frames = *(void **)((u8 *)sprite + 0x2C);
                                new_frames = D_80175E5C;
                                if (current_frames != new_frames) {
                                    *(void **)((u8 *)sprite + 0x2C) = new_frames;
                                }
                                break;
                            case 0xF:
                                current_frames = *(void **)((u8 *)sprite + 0x2C);
                                new_frames = D_80175E64;
                                if (current_frames != new_frames) {
                                    *(void **)((u8 *)sprite + 0x2C) = new_frames;
                                }
                                break;
                            }
                        } else {
                            goto setup_args_ready;
                        }
                    } else {
                        call_position = (s32)position;
                        goto setup_args2_ready;
                    }
                }
            }
        }

        call_object = (s32)object;
setup_args_ready:
        call_position = (s32)position;
setup_args2_ready:
        func_800A9C18((void *)call_object, (void *)call_position, sprite,
            (s16)init_flags);
        ((S_80171D64_4 *)((void *)record_addr))->unk_9A = 0xFF;
        ((S_80171D64_4 *)((void *)record_addr))->unk_9C = -1;
        ((S_80171D64_4 *)((void *)record_addr))->unk_8C = D_801724BC;
        func_800AA36C((void *)record_addr, position, sprite, result);

        kind = result->unk_48;
        switch (kind) {
        case 0xD:
            current_frames = *(void **)((u8 *)sprite + 0x2C);
            frame_table = D_80175E24;
            break;
        case 0xE:
            current_frames = *(void **)((u8 *)sprite + 0x2C);
            frame_table = D_80175E2C;
            break;
        case 0xF:
            current_frames = *(void **)((u8 *)sprite + 0x2C);
            frame_table = D_80175E34;
            break;
        default:
            return result;
        }
        if (current_frames != frame_table) {
            (*(void **)((u8 *)sprite + 0x2C)) = frame_table;
            default_frames = ((gameWork.view.viewAngle + result->facing + 0x100) >> 9) & 7;
            func_80047784(sprite,
                *(u8 *)((u32)default_frames + (u32)frame_table),
                0);
        }
    }
    return result;
}
