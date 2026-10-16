# OVMOVIE GAME shared source contract (W1O-1)

Review pending. This is a source cleanup, not native-module activation.

The eleven GAME rows share one declaration/header contract and a natural-order
include TU. Shared MovieState/MovieRect definitions replace three duplicate type
sets. The initializer and waiter retain explicitly documented byte views of the
MovieState+4 buffer subobject; the unsigned halfword copy view is intentional.
D_80189390 is consistently one MovieState pointer, and D_801781E0 one signed
word. The first runtime-dispatch word uses the existing shared RuntimeDispatchState
contract. LIBPRESS callback and decoder declarations agree with its shared header.
The two legacy-named definitions now use their independently proven true addresses.
The callback registration and unused playback-state argument preserve the observed
O32 call interface. The existing volatile timeout and width expression are retained;
no asm, pins, goto, new volatile, or new assembler flags are introduced.

The complete code interval [0xAC,0xED8), 11 rows / 3628 bytes, compiles once at
2.7.2-cdk-G0. GNU/maspsx and genuine ASPSX 2.79 both match every retail byte,
zero masked relocations. Each updated row also passes the unchanged production
OVMOVIE window. The include TU is available for review but is not registered.

The resource loader in src/slus/w_80040CBC.c proves a candidate record's first word
is a pointer to a resident resource word and its second word supplies playback
flags/frame limit. Nine entries in the fixed resident resource directory reference
all seven candidate records. The fixed PS-X EXE header maps every pointee.
See ovmovie_game.record_abi.json for byte addresses, directory indices and guards.
The third word of each candidate record is zero and its purpose is unknown.

The retained candidate definitions reproduce six scalar words plus seven typed
pointer records at [0x19D0,0x1A3C), 108 semantic bytes. One compilation of that
candidate plus this exact code matches 3736 semantic bytes through both assembler
arms, with seven real R_MIPS_32 pointer relocations and zero unresolved words.
GNU emits four additional zero alignment bytes beyond the 108-byte data extent;
genuine emits exactly 108. This diagnostic does not authorize discarding padding
in production or prove the candidate's original allocation boundary.

Native activation remains held on original storage/object ownership and ordinary
relocated pointer-record support. The current separated-allocation validator
accepts literal word records and hardware pointers only, and rejects the candidate
with 'unsupported literal allocation kind'; its object checks also reject data
relocations. No tool or gate has been weakened. No candidate storage definition,
strong membership stamp, module entry, promotion, or GAME certificate is installed.
The preceding 36-byte VLC workspace and following LIBPRESS data remain excluded.

Existing row identities, recipes, extents, assignments, and historical baselines
are preserved. All eleven rows are already L3, so no Layer-2 promotion is needed.
The enclosing transaction must renew ovmovie_libpress because its production
window fingerprint includes changed GAME sources. A scratch renewal is separate
from any production review or landing authority.
