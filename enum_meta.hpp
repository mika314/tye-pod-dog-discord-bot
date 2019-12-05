#pragma once
#include <array>

#define PP_NARG(...) PP_NARG_(__VA_ARGS__, PP_RSEQ_N())
#define PP_NARG_(...) PP_ARG_N(__VA_ARGS__)

#define PP_ARG_N(_1,  \
                 _2,  \
                 _3,  \
                 _4,  \
                 _5,  \
                 _6,  \
                 _7,  \
                 _8,  \
                 _9,  \
                 _10, \
                 _11, \
                 _12, \
                 _13, \
                 _14, \
                 _15, \
                 _16, \
                 _17, \
                 _18, \
                 _19, \
                 _20, \
                 _21, \
                 _22, \
                 _23, \
                 _24, \
                 _25, \
                 _26, \
                 _27, \
                 _28, \
                 _29, \
                 _30, \
                 _31, \
                 _32, \
                 _33, \
                 _34, \
                 _35, \
                 _36, \
                 _37, \
                 _38, \
                 _39, \
                 _40, \
                 _41, \
                 _42, \
                 _43, \
                 _44, \
                 _45, \
                 _46, \
                 _47, \
                 _48, \
                 _49, \
                 _50, \
                 _51, \
                 _52, \
                 _53, \
                 _54, \
                 _55, \
                 _56, \
                 _57, \
                 _58, \
                 _59, \
                 _60, \
                 _61, \
                 _62, \
                 _63, \
                 N,   \
                 ...) \
  N

#define PP_RSEQ_N()                                                                               \
  63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
    39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,   \
    16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

// need extra level to force extra eval
#define Paste(a, b) a##b
#define XPASTE(a, b) Paste(a, b)

// PP_APPLY_Xn variadic X-Macro by M Joshua Ryan
// Free for all uses. Don't be a jerk.
// I got bored after typing 15 of these.
// You could keep going upto 64 (PPNARG's limit).
#define PP_APPLY_X1(name, arg0) name::arg0
#define PP_APPLY_X2(name, arg0, arg1) name::arg0, name::arg1
#define PP_APPLY_X3(name, arg0, arg1, arg2) name::arg0, name::arg1, name::arg2
#define PP_APPLY_X4(name, arg0, arg1, arg2, arg3) name::arg0, name::arg1, name::arg2, name::arg3
#define PP_APPLY_X5(name, arg0, arg1, arg2, arg3, arg4) \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4
#define PP_APPLY_X6(name, arg0, arg1, arg2, arg3, arg4, arg5) \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5
#define PP_APPLY_X7(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6) \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6
#define PP_APPLY_X8(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7
#define PP_APPLY_X9(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)                   \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8
#define PP_APPLY_X10(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)            \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9
#define PP_APPLY_X11(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)     \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10
#define PP_APPLY_X12(                                                                             \
  name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11)                 \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11
#define PP_APPLY_X13(                                                                             \
  name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12)          \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12
#define PP_APPLY_X14(                                                                             \
  name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13)   \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13
#define PP_APPLY_X15(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14
#define PP_APPLY_X16(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15
#define PP_APPLY_X17(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16
#define PP_APPLY_X18(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17
#define PP_APPLY_X19(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18
#define PP_APPLY_X20(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19
#define PP_APPLY_X21(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20
#define PP_APPLY_X22(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21
#define PP_APPLY_X23(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22
#define PP_APPLY_X24(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23
#define PP_APPLY_X25(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24
#define PP_APPLY_X26(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25
#define PP_APPLY_X27(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26
#define PP_APPLY_X28(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27
#define PP_APPLY_X29(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28
#define PP_APPLY_X30(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29
#define PP_APPLY_X31(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30
#define PP_APPLY_X32(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31
#define PP_APPLY_X33(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32
#define PP_APPLY_X34(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33
#define PP_APPLY_X35(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34
#define PP_APPLY_X36(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35
#define PP_APPLY_X37(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36
#define PP_APPLY_X38(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37
#define PP_APPLY_X39(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38
#define PP_APPLY_X40(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39
#define PP_APPLY_X41(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40
#define PP_APPLY_X42(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41
#define PP_APPLY_X43(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42
#define PP_APPLY_X44(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43
#define PP_APPLY_X45(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44
#define PP_APPLY_X46(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45
#define PP_APPLY_X47(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46
#define PP_APPLY_X48(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47
#define PP_APPLY_X49(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48
#define PP_APPLY_X50(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49
#define PP_APPLY_X51(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50
#define PP_APPLY_X52(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50,                                                                       \
                     arg51)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50, name::arg51
#define PP_APPLY_X53(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50,                                                                       \
                     arg51,                                                                       \
                     arg52)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50, name::arg51, name::arg52
#define PP_APPLY_X54(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50,                                                                       \
                     arg51,                                                                       \
                     arg52,                                                                       \
                     arg53)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50, name::arg51, name::arg52, name::arg53
#define PP_APPLY_X55(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50,                                                                       \
                     arg51,                                                                       \
                     arg52,                                                                       \
                     arg53,                                                                       \
                     arg54)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50, name::arg51, name::arg52, name::arg53, name::arg54
#define PP_APPLY_X56(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50,                                                                       \
                     arg51,                                                                       \
                     arg52,                                                                       \
                     arg53,                                                                       \
                     arg54,                                                                       \
                     arg55)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50, name::arg51, name::arg52, name::arg53, name::arg54, name::arg55
#define PP_APPLY_X57(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50,                                                                       \
                     arg51,                                                                       \
                     arg52,                                                                       \
                     arg53,                                                                       \
                     arg54,                                                                       \
                     arg55,                                                                       \
                     arg56)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50, name::arg51, name::arg52, name::arg53, name::arg54, name::arg55, name::arg56
#define PP_APPLY_X58(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50,                                                                       \
                     arg51,                                                                       \
                     arg52,                                                                       \
                     arg53,                                                                       \
                     arg54,                                                                       \
                     arg55,                                                                       \
                     arg56,                                                                       \
                     arg57)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50, name::arg51, name::arg52, name::arg53, name::arg54, name::arg55, name::arg56,    \
    name::arg57
#define PP_APPLY_X59(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50,                                                                       \
                     arg51,                                                                       \
                     arg52,                                                                       \
                     arg53,                                                                       \
                     arg54,                                                                       \
                     arg55,                                                                       \
                     arg56,                                                                       \
                     arg57,                                                                       \
                     arg58)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50, name::arg51, name::arg52, name::arg53, name::arg54, name::arg55, name::arg56,    \
    name::arg57, name::arg58
#define PP_APPLY_X60(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50,                                                                       \
                     arg51,                                                                       \
                     arg52,                                                                       \
                     arg53,                                                                       \
                     arg54,                                                                       \
                     arg55,                                                                       \
                     arg56,                                                                       \
                     arg57,                                                                       \
                     arg58,                                                                       \
                     arg59)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50, name::arg51, name::arg52, name::arg53, name::arg54, name::arg55, name::arg56,    \
    name::arg57, name::arg58, name::arg59
#define PP_APPLY_X61(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50,                                                                       \
                     arg51,                                                                       \
                     arg52,                                                                       \
                     arg53,                                                                       \
                     arg54,                                                                       \
                     arg55,                                                                       \
                     arg56,                                                                       \
                     arg57,                                                                       \
                     arg58,                                                                       \
                     arg59,                                                                       \
                     arg60)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50, name::arg51, name::arg52, name::arg53, name::arg54, name::arg55, name::arg56,    \
    name::arg57, name::arg58, name::arg59, name::arg60
#define PP_APPLY_X62(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50,                                                                       \
                     arg51,                                                                       \
                     arg52,                                                                       \
                     arg53,                                                                       \
                     arg54,                                                                       \
                     arg55,                                                                       \
                     arg56,                                                                       \
                     arg57,                                                                       \
                     arg58,                                                                       \
                     arg59,                                                                       \
                     arg60,                                                                       \
                     arg61)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50, name::arg51, name::arg52, name::arg53, name::arg54, name::arg55, name::arg56,    \
    name::arg57, name::arg58, name::arg59, name::arg60, name::arg61
#define PP_APPLY_X63(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50,                                                                       \
                     arg51,                                                                       \
                     arg52,                                                                       \
                     arg53,                                                                       \
                     arg54,                                                                       \
                     arg55,                                                                       \
                     arg56,                                                                       \
                     arg57,                                                                       \
                     arg58,                                                                       \
                     arg59,                                                                       \
                     arg60,                                                                       \
                     arg61,                                                                       \
                     arg62)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50, name::arg51, name::arg52, name::arg53, name::arg54, name::arg55, name::arg56,    \
    name::arg57, name::arg58, name::arg59, name::arg60, name::arg61, name::arg62
#define PP_APPLY_X64(name,                                                                        \
                     arg0,                                                                        \
                     arg1,                                                                        \
                     arg2,                                                                        \
                     arg3,                                                                        \
                     arg4,                                                                        \
                     arg5,                                                                        \
                     arg6,                                                                        \
                     arg7,                                                                        \
                     arg8,                                                                        \
                     arg9,                                                                        \
                     arg10,                                                                       \
                     arg11,                                                                       \
                     arg12,                                                                       \
                     arg13,                                                                       \
                     arg14,                                                                       \
                     arg15,                                                                       \
                     arg16,                                                                       \
                     arg17,                                                                       \
                     arg18,                                                                       \
                     arg19,                                                                       \
                     arg20,                                                                       \
                     arg21,                                                                       \
                     arg22,                                                                       \
                     arg23,                                                                       \
                     arg24,                                                                       \
                     arg25,                                                                       \
                     arg26,                                                                       \
                     arg27,                                                                       \
                     arg28,                                                                       \
                     arg29,                                                                       \
                     arg30,                                                                       \
                     arg31,                                                                       \
                     arg32,                                                                       \
                     arg33,                                                                       \
                     arg34,                                                                       \
                     arg35,                                                                       \
                     arg36,                                                                       \
                     arg37,                                                                       \
                     arg38,                                                                       \
                     arg39,                                                                       \
                     arg40,                                                                       \
                     arg41,                                                                       \
                     arg42,                                                                       \
                     arg43,                                                                       \
                     arg44,                                                                       \
                     arg45,                                                                       \
                     arg46,                                                                       \
                     arg47,                                                                       \
                     arg48,                                                                       \
                     arg49,                                                                       \
                     arg50,                                                                       \
                     arg51,                                                                       \
                     arg52,                                                                       \
                     arg53,                                                                       \
                     arg54,                                                                       \
                     arg55,                                                                       \
                     arg56,                                                                       \
                     arg57,                                                                       \
                     arg58,                                                                       \
                     arg59,                                                                       \
                     arg60,                                                                       \
                     arg61,                                                                       \
                     arg62,                                                                       \
                     arg63)                                                                       \
  name::arg0, name::arg1, name::arg2, name::arg3, name::arg4, name::arg5, name::arg6, name::arg7, \
    name::arg8, name::arg9, name::arg10, name::arg11, name::arg12, name::arg13, name::arg14,      \
    name::arg15, name::arg16, name::arg17, name::arg18, name::arg19, name::arg20, name::arg21,    \
    name::arg22, name::arg23, name::arg24, name::arg25, name::arg26, name::arg27, name::arg28,    \
    name::arg29, name::arg30, name::arg31, name::arg32, name::arg33, name::arg34, name::arg35,    \
    name::arg36, name::arg37, name::arg38, name::arg39, name::arg40, name::arg41, name::arg42,    \
    name::arg43, name::arg44, name::arg45, name::arg46, name::arg47, name::arg48, name::arg49,    \
    name::arg50, name::arg51, name::arg52, name::arg53, name::arg54, name::arg55, name::arg56,    \
    name::arg57, name::arg58, name::arg59, name::arg60, name::arg61, name::arg62, name::arg63
#define PP_APPLY_X_(name, M, ...) M(name, __VA_ARGS__)
#define PP_APPLY_Xn(name, ...) \
  PP_APPLY_X_(name, XPASTE(PP_APPLY_X, PP_NARG(__VA_ARGS__)), __VA_ARGS__)

#define ENUM(name, ...)            \
  enum class name { __VA_ARGS__ }; \
  constexpr std::array name##_META{PP_APPLY_Xn(name, __VA_ARGS__)};
