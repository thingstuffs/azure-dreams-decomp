/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void func_800673A0(s16 *, s32, s32);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern s32 generate_random_value();
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern u8 D_8015EB40[];
extern u8 D_8015EF6C[];
extern u8 D_80163258[];
extern u8 D_80163298[];

extern void *func_8015E8A4(s16, s16, s16, s16);

void *func_8015E8A4(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
;

typedef void (*Callback)(void);
typedef struct { s16 x, y, w, h; } Rect;

typedef struct S_80FB1000_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FB1000_0;   

typedef struct S_80FB1000_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FB1000_1;   

typedef struct S_80FB1000_2 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80FB1000_2;   

/* Creates a Mandara actor, initializes status and tile placement, and prepares sprite image rectangles. */
void *func_8015E8A4(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s16 saved_flags;
    s16 saved_kind_id;
    s8 saved_variant;
    s16 saved_spawn_value;
    void *created;
    u8 *work = 0;
    u8 *position;
    SpriteFrameState *monster;
    u8 *actor;
    s32 kind;
    Rect rect;

    saved_kind_id = kind_id;
    saved_spawn_value = spawn_value;
    saved_variant = variant;
    kind_id = 0x112;
    created = allocate_list_node(kind_id, ((u8 *)(&scene_object_list_anchor)));
    saved_flags = (s32)flags;
    if (created != 0) {
        void *init_arg0;
        s32 flags0;
        s32 flags1;
        s32 value;
        u8 *entry;
        s32 i;
        s32 scale;

        work = (u8 *)created + 0x20;
        (*(Callback *)((u8 *)created + 0x10)) = D_8015EB40;
        ((S_80FB1000_0 *)work)->unk_13 = MONSTER_MANDARA;
        register_node(created, project_sprite_chain);

        position = (*(u8 * *)((u8 *)created + 8));
        ((S_80FB1000_1 *)position)->unk_0A = saved_spawn_value;
        monster = (*(u8 * *)((u8 *)created + 0xC));
        monster->unk_25 = saved_variant;
        actor = work;
        monster->frameTable = D_80163258;
        monster->unk_24 = saved_kind_id;

        kind = (s32)flags & 3;
        if (kind == 1) {
            flags0 = ((S_80FB1000_0 *)work)->unk_14 | 0x6000;
            flags1 = ((S_80FB1000_0 *)work)->unk_1C | 0x6000;
            ((S_80FB1000_0 *)work)->unk_14 = flags0;
            ((S_80FB1000_0 *)work)->unk_1C = flags1;
        } else if (kind >= 2) {
            flags0 = ((S_80FB1000_0 *)work)->unk_14 | 0x2000;
            flags1 = ((S_80FB1000_0 *)work)->unk_1C | 0x2000;
            ((S_80FB1000_0 *)work)->unk_14 = flags0;
            ((S_80FB1000_0 *)work)->unk_1C = flags1;
        } else {
            if ((s16)((s32)flags & -4) == 0 &&
                !(((S_80FB1000_0 *)work)->unk_14 & 0x200)) {
                value = generate_random_value();
                if (value & 1) {
                    ((S_80FB1000_0 *)work)->unk_1C |= 0x200;
                    value = generate_random_value();
                    set_or_clear_actor_status_slot(work, 1, (value & 0x3F) | 0x20);
                    monster->frameTable = D_80163298;
                }
            }
        }

        init_arg0 = created;
        initialize_actor_sprite_and_animation(init_arg0, position, monster, (s16)saved_flags);
        i = 0;
        value = monster->clut;
        (*(u8 *)((u8 *)actor + 0x9A)) = 0xFF;
        (*(s8 *)((u8 *)actor + 0x9C)) = -1;
        (*(Callback *)((u8 *)actor + 0x8C)) = D_8015EF6C;
        (*(s16 *)((u8 *)actor + 0xAE)) = value;

        entry = *(u8 * *)&monster->source;
        while (1) {
            scale = i << 1;
            if (!(entry[0] & 0x20)) {
                break;
            }
            entry += 12;
            i++;
        }
        value = ((S_80FB1000_2 *)(*(u8 * *)&monster->source + (scale + i) * 4))->unk_06 >> 6;
        rect.x = 0;
        rect.y = value;
        rect.w = 0x100;
        rect.h = 1;
        func_800673A0(&rect, 0, value - 1);

        rect.w = 0x10;
        rect.x = 0x30;
        rect.y--;
        do {
            func_800673A0(&rect, rect.x - 0x30, rect.y);
            rect.x += 0x40;
        } while (rect.x < 0x100);

        try_move_actor_to_valid_position(actor, position, monster, work);
    }
    return work;
}
