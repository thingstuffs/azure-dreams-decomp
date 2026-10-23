/* Every v2 category except cross-function clones, plus nearby exclusions. */
typedef struct { u8 pad_00[16]; s16 unk_10; } Entity;
typedef struct Actor Actor;
struct Actor { s32 value; u8 pad04[4]; };
typedef struct { u8 pad[8]; s32 value; } Rec_test;
typedef struct { u8 unk_00; } S_80012345_0;
typedef struct { s32 x; s32 y; } Position;

void debt(Entity *ent) {
    value = F(ent, u8, 0xAE);
    value = U8(ent, 0xA0);
    value = S8(ent, 0xA1);
    value = S16(ent, 0xA2);
    value = U16(ent, 0xA4);
    value = U32(ent, 0xA8);
    value = S32(ent, 0xAC);
    value = U32_AT(ent, 0x24);
    value = PTR(ent, 0x60);
    value = F(nested(a, b), u16, (0x40U));
    value = U8(ent, dynamic);
    value = F(ent, u8, 0x10, extra);
    value = object.U8(ent, 0x10);
    view = (u8 *)&ent->unk_10 + 1;
    scratch = (u8 *)0x1F800000;
    word = *(s32 *)0x1F800020;
    fixed = (u8 *)0x80010000;
    small = (u8 *)32;
    null = (u8 *)0;
    sentinel = (u8 *)1;
    dynamic = (u8 *)address;
    x = (value << 16) >> 16;
    y = value << 0x10;
    y >>= 16U;
    z = (value << 8) >> 8;
    z = (value << 16) + other >> 16;
    value = (s32)(s16)x;
    value = (u32)(u16)x;
    do { value = next(); } while (0);
    do { value = next(); } while (1);
    state = 0x14;
    ent->state = 0x1;
    if (timer >= 0x79) { next(); }
    if (0x20 < timer) { next(); }
    flags = 0x80;
    lifetime = 0x20;
    decimal_state = 20;
    state = 0x14 + next();
    state_mask &= 0x10;
}

void uses_types(Actor *actor, Rec_test *rec, S_80012345_0 *record, Position *pos) {
    use(actor, rec, record, pos);
}
