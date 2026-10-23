# Town: prices, buildings and events

[Mechanics index](README.md) · [Town source map](../town.md) · [Items](items.md)

## Shops and prices

Verified by reading
[`calc_item_value`](../../../src/engine/item/calc_item_value.c),
[`get_item_buy_money`, `get_item_sell_money`](../../../src/slus/code.c)
and [`populate_shop_item_rows`](../../../src/town/shop/item/populate_shop_item_rows.c).
The category and subtype select the item's pricing record. Buy and sell
values are **separate** record halfwords, rather than one fixed sell/buy ratio:

```text
category = itemCategoryTable[item.kind]
record = category.records[item.id]
multiplier = item_value_multipliers[category.multiplierIndex]
buy  = record.value0 * multiplier
sell = record.value1 * multiplier
if category.callback exists:
    value = category.callback(value, item, category, record)
```

The callback can adjust the selected value using the item and its definition.
This formula does not establish one uniform charge, enhancement or curse
multiplier for every category. The shop display builds up to five entries
per page and chooses buy values in mode zero, sell values otherwise, only
when the entry passes its price-display eligibility check. A complete stock
and category-callback price catalog requires reading those data bindings too.

Verified by reading
[`has_money_at_least`](../../../src/town/scene/money/has_money_at_least.c),
[`has_enough_money_for_stored_price`](../../../src/town/scene/money/has_enough_money_for_stored_price.c)
and [`subtract_money`](../../../src/town/scene/money/subtract_money.c).
Ordinary wallet checks compare the town state's +0x2d5c word against an
unsigned amount; the subtraction helper directly subtracts its argument and
does not itself clamp or check affordability. The stored-price helpers use
the same wallet with `scene_price` or `scene_charge`. Callers must supply the
matching check before charging. Another helper and dialogue selector read
+0x2d68; that separate counter should not automatically be labeled the wallet.

## Building eligibility

Verified by reading
[`CheckBuildBuildingLand`](../../../src/town/map/check_build_building_land.c)
and [`CheckBuildBuildingLandNo`](../../../src/town/map/building.c).
These functions first require the resident progress bit named by the
building record's +8 halfword. They then test the building's kind:

| Building-record kind | Checked land condition |
| --- | --- |
| 1 | Among 33 slots, dimensions match record bytes +4/+5; current first ID is at least `0x2d` and not `0x30`; second ID is zero. An existing occurrence of this building rejects it. |
| 4 or 8 | Record byte +6 is nonzero; a slot's first ID equals it and second ID differs from the requested building. |
| 16 | Record byte +6 matches the special slot's first ID and its second ID differs. The list helper returns slot `0x0b`. |
| Other tested/default kinds | No eligible land returned by these helpers. |

The first helper answers whether a match exists; the second collects eligible
slot indices. These are availability/placement predicates. Their source alone
does not supply every building's name, construction price, prerequisite story
scene or completion delay.

## Pending building changes

Verified by reading
[`BuildLandBuilding`](../../../src/town/map/build_land_building.c)
and [`apply_building_pending_updates`](../../../src/town/map/apply_building_pending_updates.c).
The setter writes selected codes into pending second bytes of slot pairs.
Codes 1..3 use the ordinary selected pair, codes 37..41 use a special pair,
and other codes also update the common selected/previous palette bytes.
The application helper scans 34 pairs, copies each nonzero pending byte into
the current byte and clears the pending byte. It then copies two additional
palette-state bytes. This proves a staged state update, not an independent
real-time building timer or an automatic money deduction in the setter.

## Events are ordered state/flag decisions

Verified by reading
[`select_next_dialogue_line`](../../../src/town/scene/dialogue/select_next_dialogue_line.c)
alongside [`script_symbols.h`](../../../include/script_symbols.h)
and [`TownEventState`](../../../include/shared/town_event_state.h).
The selector checks branches in order and returns the first matching text
pointer. It also sets some one-time flags as it selects lines. Examples:

- It records the initial home dialogue flag, then uses state queries to gate
  later invitation branches.
- With its outer conditions satisfied, a progress query at least 5 and an
  unfinished named scene test can select a windmill invitation, with a
  separate first-invitation flag.
- Pool invitation flags and scene completion are checked before the later
  +0x2d68 counter branches at 10000 and 20000.
- Temple invitation tests combine another state callback with building-slot
  IDs. Further dialogue depends on several `TownEventState` bytes and the
  enabled-record count. A final bread-given flag selects another fallback.

The invitation labels are **inferred from the existing symbolic flag names**;
the C establishes the predicate order and one-time writes. These examples
are not a complete event walkthrough or proof that a counter threshold alone
unlocks a building. Follow the town guide's scene/script route to connect a
predicate to its invoking event and the resulting state changes.

[`build_current_event_entry_list`](../../../src/town/map/build_current_event_entry_list.c)
selects a null-terminated list of one or three entries based on the current
event code, while
[`request_event_with_toggled_selector`](../../../src/town/map/request_event_with_toggled_selector.c)
requests scene code `0x16` with a toggled selector bit. These are concrete
examples of event plumbing separate from story prerequisites. No town-specific
bug is asserted here without an entry and supporting source in the current
[bug catalog](../../BUGS.md).
