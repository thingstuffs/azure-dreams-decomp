#ifndef TOWN_SHOP_ITEM_LOOKUP_H
#define TOWN_SHOP_ITEM_LOOKUP_H

int get_item_chk(void);
void *find_item_by_kind_and_type(int item_kind, int item_type);
int find_first_vacant_record(const unsigned char *records, int count);

int get_index_address_in_range_four_byte_slots_n_1(void *target_addr, void *slot_addr, int slot_count);

#endif
