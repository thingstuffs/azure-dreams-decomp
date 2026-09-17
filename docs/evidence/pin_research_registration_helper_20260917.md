Working paths in this review snapshot refer to `work/native_lane/r43_helper_abi`.

# Registration helper contract

The registered resident SLUS function func_8004491C is defined in
src/slus/w_8004491C.c as an integer-returning function with two parameters:
RegistrationNode *entry and s32 registration_id. The independently rebuilt
object is exact (receipt helper_verify.json). It walks registration arrays,
links entry into a list and returns success; it does not consume incoming a2/a3.

Six recognized DUNGEON call sites pass copy cursors as third/fourth arguments.
These values are pure local reads after copying, with no side effects. Removing
those extra arguments follows the actual resident helper contract. Retaining
the values as explicit additions after aggregate assignment instead invents
post-copy lifetimes not required by the helper.

The two selected pinned rows are 8132B300 and 81339700. Other recognized calls
are in pin-free 80D653B8, 800D1660, 81251350 and one-pin 80D137FC, whose action keep
is unrelated to the copy. This source-name scan is bounded; it does not prove
absence of differently named or indirect calls. The historical registration-ID
pointer/integer representation debt is unchanged; no new pointer narrowing is
introduced. Caller function signatures are unchanged.
