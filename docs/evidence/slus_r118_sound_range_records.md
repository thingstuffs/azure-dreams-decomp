# Sound range records: bounded membership and scalar-view review

Reviewer: pending. This is an inferred partial cluster within the established
stock-2.7.2 sound TU, not a recovered historical filename or TU boundary.
docs/HANDOVER.md records the r82 sound interval 0x8005CA90..0x8005FA34.
All three actual logical recipes use stock 2.7.2 with empty compiler and
assembler flags. The new aggregator includes only w_8005D838, w_8005D95C and
w_8005D9DC, in retail address order. No recipe exception is added.

These functions share the same list pointer at D_800799BC and a two-word record.
The first word contains a masked base value and high-bit flags; the second word
is the range size. func_8005D838 publishes the positive record count and head,
clears the count/index state D_800799B8, and initializes the head words.
func_8005D95C tests the raw address against the non-skipped ranges.
func_8005D9DC first left-shifts its value by D_80079980, then performs the same
base/size tests. Both searches advance by exactly eight bytes and use unsigned
range addition/comparison. They provide shared-layout and membership evidence
beyond a common compiler cell. func_8005D88C is an intervening reverb helper
that calls the shifted search, but is excluded from this bounded candidate.
Other sound allocation functions and all collector contributions are excluded.

The header reconciles three independently declared two-word layouts into
S_800799BC {u32 flags; u32 size}. The initializer stores the same 32-bit
calculation into the second word; making that storage view unsigned preserves
its bit pattern and agrees with both unsigned search uses. There is no added
field, padding, extent, volatility or storage definition. D_80079980,
D_800799B4 and D_800799B8 are the four-byte scalars actually loaded/stored.
D_800799BC is the four-byte record pointer actually loaded/stored. Their old
three-element extern arrays were addressing workarounds, not accessed extents.

Each canonical candidate passed an unchanged-recipe frozen-raw object control
and an exact complete-object identity trial before staging. The private cache
does not change the verifier's pinned certificate cache. Delivery additionally
requires a real one-input module build, exact full retail image, and the
unchanged certify_slus_module.py dry-run with complete physical-owner/direct
genuine ASPSX 2.79 proof and zero masked retail relocations. Object identity
alone is not placement proof. The orchestrator supplies review identity and
runs --write after final inputs under the landing lock.

No logical row, collector part, split record, rowbase, owned data, production
window value, gate code or noreturn census is changed. The header allocates no
storage and claims no adjacent symbol. Existing source-quality debt elsewhere
remains work. The inferred partial cluster does not assert that excluded
functions belong to another historical TU.

Rebase receipt at 97f105e7f: this input uses the committed code/code2 parent recipes (both 2.7.2-cdk) and preserves the seven-function stock-2.7.2 sound_tu_code partition. Any earlier production proof is historical; this delivery requires fresh unchanged full-image, member/physical-owner genuine and relevant production-window checks at this HEAD. No old collector recipe, asm alias, compiler flag, pin-census implementation or parked-container setting is restored. Reviewer remains pending.
