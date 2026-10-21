typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 scene_object_payload_alias;
extern void call_the_handler_selects_nonzero_entry(s32 a0, void *a1, s32 a2);

/* Calls call_the_handler_selects_nonzero_entry with the input value and global context. */
void apply_global_scene_value(s32 value) {
    s32 *context = &scene_object_payload_alias;
    call_the_handler_selects_nonzero_entry(value, context, *(s32 *)((u8 *)context - 0x14));
}
