#ifndef DUNGEON_OVL_1924800_H
#define DUNGEON_OVL_1924800_H
#include "shared/dungeon_effect_views.h"
#include "common.h"
#include "m2c_compat.h"
#include "modules/dungeon_native_abi.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/entity_height_offsets.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/effect.h"

/* Same three position slots, with the signed spawn and unsigned raise views
 * visible together. Retail loads at +2,+6,+10; raise also updates the z word. */

typedef u8 *(*FnPtr)(void *, s32, void *, void *, u8 *);

typedef struct { s32 w0, w1, w2, w3; } Blk16;

typedef struct { s32 w0, w1; } Blk8;

typedef struct { s32 a0,a1,a2,a3,a4,a5,a6,a7,a8,a9; } Blk40;

typedef struct S_func_81904990_1 {
    s32 unk_00;
    void * unk_04;
    u8 pad_08[0x72];
    u16 unk_7A;
    u16 unk_7C;
} S_func_81904990_1;

typedef struct S_func_81904990_2 {
    u8 pad_00[0x8];
    void * unk_08;
    union {
        s32 as_s32_0C;
        struct {
            u8 pad_0C[0x3];
            u8 unk_0F;
        } as_u8_0F;
    } unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
} S_func_81904990_2;

typedef struct S_func_81904990_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u16 unk_06;
    union {
        FnPtr as_FnPtr_08;
        u8 as_u8_08;
        struct {
            u8 pad_08[0x1];
            u8 unk_09;
        } as_u8_09;
        struct {
            u8 pad_08[0x2];
            u8 unk_0A;
        } as_u8_0A;
        struct {
            u8 pad_08[0x3];
            u8 unk_0B;
        } as_u8_0B;
    } unk_08;
} S_func_81904990_3;

typedef struct S_func_81904990_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    union {
        s32 as_s32_10;
        u16 as_u16_10;
    } unk_10;
    union {
        s32 as_s32_14;
        u16 as_u16_14;
    } unk_14;
    u8 pad_18[0x8];
    s32 * unk_20;
    u16 unk_24;
    u8 pad_26[0xA];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x34];
    u16 unk_70;
    u16 unk_72;
    u16 unk_74;
    u8 pad_76[0x2];
    u16 unk_78;
    u16 unk_7A;
    u16 unk_7C;
    u8 pad_7E[0x2];
    u16 unk_80;
    u16 unk_82;
    u16 unk_84;
    u8 pad_86[0x2];
    u16 unk_88;
    u16 unk_8A;
    u16 unk_8C;
    u8 pad_8E[0x2A];
    u16 unk_B8;
    u16 unk_BA;
    u8 pad_BC[0x4];
    s32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u16 unk_F0;
    u16 unk_F2;
    u16 unk_F4;
    u16 unk_F6;
    u16 unk_F8;
    u16 unk_FA;
    u16 unk_FC;
    u16 unk_FE;
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
    u8 pad_106[0x2];
    u16 unk_108;
    u16 unk_10A;
} S_func_81904990_4;

typedef struct S_func_81904990_6 {
    u16 unk_00;
    u16 unk_02;
} S_func_81904990_6;

typedef struct S_func_81904990_7 {
    union {
        s32 as_s32_00;
        struct {
            u8 pad_00[0x3];
            s8 unk_03;
        } as_s8_03;
    } unk_00;
    s32 unk_04;
    union {
        s16 as_s16_08;
        u16 as_u16_08;
    } unk_08;
    s16 unk_0A;
    union {
        s16 as_s16_0C;
        struct {
            u8 pad_0C[0x1];
            u8 unk_0D;
        } as_u8_0D;
    } unk_0C;
    u16 unk_0E;
    union {
        s16 as_s16_10;
        u16 as_u16_10;
    } unk_10;
    s16 unk_12;
    union {
        s16 as_s16_14;
        u8 as_u8_14;
        struct {
            u8 pad_14[0x1];
            u8 unk_15;
        } as_u8_15;
    } unk_14;
    u16 unk_16;
    union {
        s16 as_s16_18;
        u16 as_u16_18;
    } unk_18;
    s16 unk_1A;
    union {
        s16 as_s16_1C;
        struct {
            u8 pad_1C[0x1];
            u8 unk_1D;
        } as_u8_1D;
    } unk_1C;
    u8 pad_1E[0x2];
    union {
        s16 as_s16_20;
        u16 as_u16_20;
    } unk_20;
    s16 unk_22;
    union {
        s16 as_s16_24;
        u8 as_u8_24;
        struct {
            u8 pad_24[0x1];
            u8 unk_25;
        } as_u8_25;
    } unk_24;
} S_func_81904990_7;

typedef struct S_func_81904990_8 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_func_81904990_8;

typedef struct ScreenPos {
    u16 x;
    s16 y;
} ScreenPos;

typedef struct ScreenRect {
    u16 x;
    s16 y;
    s32 size;
} ScreenRect;

typedef struct FillPacket {
    u32 tag;       /* low 24 bits next address; byte 3 = word count (3) */
    u32 command;   /* 0x60000000: monochrome rectangle, black */
    u16 x;
    s16 y;
    s32 size;
} FillPacket;

typedef struct Scratch80024D64 {
    u16 x;
    u16 y;
    u16 z;
    u8 pad06[0x12];
    u8 *cursor;
    u8 pad1C[4];
    u32 *ot;
    u8 pad24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad98[0x28];
    u32 index;
} Scratch80024D64;

typedef struct EffectRecord {
    u8 pad_00[0x32];
    s16 timer;
} EffectRecord;

typedef struct S_800251A0_0_pre {
    u16 unk_00;
} S_800251A0_0_pre;

typedef struct S_800251A0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800251A0_0;

typedef struct DungeonAnimSlot {
    u8 pad_00[0x50];
    s16 field_50;
    u8 pad_52[0x10];
    u16 field_62;
} DungeonAnimSlot;

typedef struct CountdownRecord {
    u16 pad_00;
    u16 counter;
} CountdownRecord;

typedef struct {
    u8 bytes[0x20];
} LocalPoints;

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} Box __attribute__((packed));

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} PackedVector __attribute__((packed));

typedef struct {
    u16 x;
    u16 y;
} Point __attribute__((packed));

typedef struct {
    u8 bytes[8];
} Copy8;

typedef struct {
    u8 bytes[12];
} Copy12;

typedef struct {
    u8 bytes[32];
} Copy32;

typedef struct {
    s16 a;
    s16 b;
    s16 c;
} Vec3;

typedef struct S_func_81905FD0_1 {
    void * owner;
    void * launch_flags;
    u8 pad_08[0x1];
    u8 unk_09;
    union {
        s16 s16;
        u16 u16;
    } phase;
    u8 pad_0C[0x6C];
    union {
        s16 s16;
        u16 u16;
    } target_height;
    u8 flags;
    u8 travel_ticks;
    u8 pad_7C[0x2];
    union {
        s16 s16;
        u16 u16;
    } direction;
    u8 pad_80[0x2];
    union {
        s16 s16;
        u16 u16;
    } timer;
    u8 pad_84[0x4];
    u16 unk_88;
    u16 unk_8A;
    u8 pad_8C[0x4];
    union {
        s16 s16;
        u16 u16;
    } scale_shrinking;
    u16 scale_timer;
    union {
        s16 s16;
        u16 u16;
    } scale_period;
    u16 scale_step;
    u8 pad_98[0x4];
    union {
        s16 s16;
        u16 u16;
    } child_done;
    u8 pad_9E[0x1C];
    u8 unk_BA;
    u8 unk_BB;
} S_func_81905FD0_1;

typedef struct S_func_81905FD0_2 {
    union {
        u32 u32;
        struct {
            u8 pad_00[0x2];
            u16 unk_02;
        } u16_02;
    } x;
    union {
        u32 u32;
        struct {
            u8 pad_04[0x2];
            u16 unk_06;
        } u16_06;
    } y;
    union {
        s32 s32;
        u32 u32;
        struct {
            u8 pad_08[0x2];
            s16 unk_0A;
        } s16_0A;
        struct {
            u8 pad_08[0x2];
            u16 unk_0A;
        } u16_0A;
    } z;
    u32 velocity_x;
    u32 velocity_y;
    union {
        s32 s32;
        u32 u32;
    } velocity_z;
} S_func_81905FD0_2;

typedef struct S_func_81905FD0_3 {
    u8 pad_00[0x6];
    u16 depth_bias;
    void * source;
    union {
        u32 u32;
        u8 u8;
        struct {
            u8 pad_0C[0x1];
            u8 unk_0D;
        } u8_0D;
        struct {
            u8 pad_0C[0x2];
            u8 unk_0E;
        } u8_0E;
    } color;
    union {
        s16 s16;
        u16 u16;
    } tpage_abr;
    u8 pad_12[0x2];
    u16 flags;
    u8 pad_16[0x4];
    u16 angle_z;
    union {
        s16 s16;
        u16 u16;
    } scale_x;
    union {
        s16 s16;
        u16 u16;
    } scale_y;
    u8 pad_20[0x2];
    s16 offset_y;
    u8 tile_x;
    u8 tile_y;
} S_func_81905FD0_3;

typedef struct S_func_81905FD0_4 {
    u8 pad_00[0x2A];
    u16 facing;
    u8 pad_2C[0x34];
    void * target;
    u8 pad_64[0xE];
    s8 target_tile_x;
    s8 target_tile_y;
    u8 pad_74[0x14];
    u16 ground_height;
} S_func_81905FD0_4;

typedef struct S_func_81905FD0_5 {
    u8 pad_00[0x8];
    void * position;
    void * sprite;
    void * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_func_81905FD0_5;

typedef struct S_func_81905FD0_6 {
    u8 pad_00[0x13];
    u8 species;
    u32 property_flags;
    u8 pad_18[0x4];
    u32 state_flags;
} S_func_81905FD0_6;

typedef struct S_func_81905FD0_7 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x2A];
    void * unk_38;
    void * unk_3C;
    void * unk_40;
    void * unk_44;
    void * unk_48;
    void * unk_4C;
} S_func_81905FD0_7;

typedef struct S_func_81905FD0_8 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} S_func_81905FD0_8;

typedef struct S_func_81905FD0_9 {
    s16 unk_00;
    u16 unk_02;
} S_func_81905FD0_9;

typedef struct S_func_81905FD0_10 {
    union {
        s16 s16;
        u16 u16;
    } unk_00;
} S_func_81905FD0_10;

typedef struct S_func_81905FD0_11 {
    u8 unk_00;
} S_func_81905FD0_11;

typedef struct S_func_81905FD0_12 {
    u16 flags;
} S_func_81905FD0_12;

typedef struct S_func_81905FD0_13 {
    u8 pad_00[0x4];
    u16 tpage;
} S_func_81905FD0_13;

extern const u16 strip_texture_rect[4];
extern const u16 strip_small_texture_rect[4];
extern const s16 strip_direction_steps[8][2];
extern void *get_unused_text_buffer(s32, s32);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern void *write_text_byte_and_advance(s8 value, s8 *dest);
extern u8 *append_entity_display_text(void *record, u8 *out);
extern void adjust_source_value_and_finalize(void *context, const void *source);
#include "dungeon/effect/screen.h"
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern s32 generate_random_value(void);
extern u8 counter_halved_message[];
extern u8 counter_halve_failed_message[];
extern void CompMatrix(void *, void *, void *);
extern void PushMatrix(s32, s32);
extern void PopMatrix(s32);
extern void ScaleMatrix(void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern void RotTransPers4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void RotMatrix(void *, void *);
extern void func_80067EF4();
extern u8 effect_view_matrix[3];
extern u8 upper_draw_context[16];
extern void SetDrawArea(void *, void *);
extern u32 RotTransPers(void *, void *, void *, void *);
extern s32 GetTPage(s32, s32, s32, s32);
extern void SetDrawMode(void *, s32, s32, s32, s32);
extern s16 traveling_strip_effect_updated[5];
extern s32 rand(void);
extern s32 rsin(s32);
extern s32 DrawSync(s32);
extern void LoadImage(Box *, u8 *);
extern void StoreImage(Box *, u8 *);
extern void draw_transformed_sprite_with_clip_rect(void *, void *, void *, s32, s32);
extern u8 D_80026820[];
extern u8 D_80026760[12];
extern u8 D_8002676C[12];
extern u8 D_80026778[12];
extern u8 D_80026784[24];
extern u8 D_800267A8[12];
extern u8 current_spell_effect_variant[1];
extern s32 get_sprite_attachment_vector(void *, void *, Vec3 *, s32);
extern s32 func_8003DF74(void *, void *, Vec3 *, s32);
extern s32 rand(void);
s16 check_adjacent_tile_height_clearance(u16 x, u16 y, s32 z, void *skip_check);
void try_halve_actor_counter(u8 *entity, s32 chance, void *unused_context);
void build_textured_sprite_strips(void *screen_pos, void *sprite, s32 *ordering_table, s32 draw_mode);
void decrement_effect_counter_by_twelve(s32 draw_data, ScreenRect *clip_rect, void *screen_pos, u16 clear_rect, s16 draw_param);
s32 draw_brightness_scaled_linked_tiles(PointRecord *first_point, ObjectPosition *first_position);
void raise_effect_to_height_limit(EffectRecord *object, ObjectPosition *source);
void get_half_byte_length(ObjectNodeHeader *parent, s16 field_34, s32 field_28, s16 field_52, s16 offset_x, s16 offset_y, s16 offset_z);
void update_effect_animation_slots(void *anim_state);
void tick_effect_record(CountdownRecord *record);
void update_effect_brightness_pulse(u8 *effect, void *unused, u8 *target);
void build_inverted(void *context, void *unused, void *effect_data);
void update_traveling(S_func_81905FD0_1 *effect, S_func_81905FD0_2 *motion, S_func_81905FD0_3 *render);
#endif
