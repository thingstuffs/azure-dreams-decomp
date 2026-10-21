#include "common.h"
#include "frontend/card.h"

void *initialize_consecutive();                         /* extern */
void *func_80404818();                         /* extern */
void func_80404888(s32);                         /* extern */
void func_804048F8();                         /* extern */
typedef struct MainPacket12 MainPacket12;
MainPacket12 *initialize_drawing();                         /* extern */

/* Process four embedded components, then the containing object. */
void card_background_init_components(s32 object_addr) {
    initialize_consecutive(object_addr + 8);
    func_80404818(object_addr + 0x80);
    func_80404888(object_addr + 0xF8);
    initialize_drawing(object_addr + 0x170);
    func_804048F8(object_addr);
}
