typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern void fill_ten_paged_entry_slots(s32 a0, void *a1, s32 a2);

/* Forwards a value and the referenced record's data to fill_ten_paged_entry_slots. */
void forward_paged_record_data(s32 value, void **record_ptr) {
    void *record;

    record = *record_ptr;
    fill_ten_paged_entry_slots(value, (u8 *)record + 0x1C, *(s32 *)((u8 *)record + 0x3C));
}
