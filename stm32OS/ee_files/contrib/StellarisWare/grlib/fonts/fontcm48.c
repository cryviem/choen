//*****************************************************************************
//
// fontcm48.c - Font definition for the 48pt Cm font.
//
// Copyright (c) 2011 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 8028 of the Stellaris Graphics Library.
//
//*****************************************************************************

//*****************************************************************************
//
// This file is generated by ftrasterize; DO NOT EDIT BY HAND!
//
//*****************************************************************************

#include "grlib/grlib.h"

//*****************************************************************************
//
// Details of this font:
//     Characters: 32 to 126 inclusive
//     Style: cm
//     Size: 48 point
//     Bold: no
//     Italic: no
//     Memory usage: 6568 bytes
//
//*****************************************************************************

//*****************************************************************************
//
// The compressed data for the 48 point Cm font.
// Contains characters 32 to 126 inclusive.
//
//*****************************************************************************
static const unsigned char g_pucCm48Data[6367] =
{
      5,  19,   0, 116,  48,  38,   8, 240,  34,  84,  68,  68,
     68,  68,  68,  68,  68,  68,  82,  98,  98,  98,  98,  98,
     98,  98,  98,  98,  98,  98,  98,  98,  98,  98,   0,   5,
     98,  84,  68,  82,   0,  12,  80,  35,  18,   0,   6, 115,
     99,  85,  69,  69,  69,  84,  84, 129, 129, 129, 129, 129,
    129, 129, 129, 113, 129, 129, 129, 129, 129, 113, 129, 114,
    114, 113, 129,   0,  72, 112, 136,  37,   0,  15, 113, 146,
    240, 146, 146, 240, 146, 146, 240, 146, 145, 240, 161, 146,
    240, 146, 146, 240, 146, 146, 240, 146, 145, 240, 161, 146,
    240, 161, 146, 240, 146, 146, 240, 146, 145, 240, 162, 130,
    240, 161, 146, 240, 146, 146, 240, 146, 145, 240, 162, 130,
    223,  15,   3, 242, 145, 240, 162, 130, 240, 161, 146, 240,
    146, 146, 240, 146, 146, 240, 146, 145, 240, 162, 130, 240,
    161, 146, 255,  15,   3, 210, 130, 240, 161, 146, 240, 146,
    146, 240, 146, 145, 240, 162, 130, 240, 161, 146, 240, 146,
    146, 240, 146, 145, 240, 162, 145, 240, 161, 146, 240, 146,
    146, 240, 146, 146, 240, 146, 145, 240, 161, 146, 240, 146,
    146, 240, 146, 146, 240, 146, 145,   0,  11,  96,  99,  22,
    129, 240,  97, 240,  97, 240,  71, 210,  33,  51, 161,  65,
     82, 129,  81, 113,  98,  81, 113,  97,  97, 129,  66,  97,
     99,  66,  97,  84,  66,  97,  84,  66,  97,  98,  83,  81,
    211,  81, 227,  65, 229,  33, 247, 240,  25, 249, 248, 241,
     37, 225,  68, 209,  83, 209,  99, 193,  99,  82,  81, 114,
     67,  81, 114,  67,  81, 114,  67,  81, 114,  65, 113, 114,
     65, 113,  98,  97,  97,  98,  98,  81,  82, 130,  65,  66,
    162,  49,  35, 214, 240,  65, 240,  97, 240,  97,   0,  26,
     48, 143,  37,  84, 240,  65, 194,  49, 240,  34, 178,  81,
    242, 178,  98, 211, 163, 114, 179, 179, 113,  18, 114,  18,
    178, 129,  55,  34, 179, 145, 177, 195, 145, 162, 195, 145,
    161, 211, 145, 146, 211, 145, 130, 227, 145, 129, 243, 145,
    114, 240,  18, 145,  98, 240,  34, 129, 114, 240,  35, 113,
     98, 240,  66,  97, 113, 240,  98,  81,  98, 240, 114,  49,
     98, 240, 163, 114, 129, 240, 162, 114,  19, 240, 113, 114,
     81, 240,  82,  98,  97, 240,  66,  99, 113, 240,  50,  98,
    129, 240,  34, 114, 145, 242, 115, 145, 242, 115, 145, 226,
    131, 145, 225, 147, 145, 210, 147, 145, 194, 163, 145, 194,
    163, 145, 178, 194, 129, 178, 211, 113, 178, 226, 113, 162,
    243,  81, 178, 240,  19,  49, 193, 240,  68,   0,  42,  80,
    112,  34,   0,   9,  84, 240, 226,  49, 240, 194,  65, 240,
    179,  81, 240, 162,  97, 240, 147,  97, 240, 147,  97, 240,
    147,  97, 240, 147,  97, 240, 147,  81, 240, 163,  81, 240,
    164,  49, 240, 195,  33, 240, 211,  17, 240, 227,  17, 169,
    179, 212, 227, 226, 243, 225, 245, 209, 241,  19, 193, 241,
     51, 177, 225,  67, 161, 225,  99, 145, 210,  99, 129, 225,
    131, 113, 210, 131,  97, 226, 147,  65, 227, 163,  49, 227,
    163,  33, 243, 179,  17, 161,  68, 179, 177,  83, 195, 161,
     83, 180, 145, 115, 145,  36,  98, 132,  67,  83,  66, 182,
    165,   0,  47,  96,  20,   9, 240, 211,  85,  69,  84, 129,
    129, 129, 129, 113, 129, 129, 113, 114, 113,   0,  36, 112,
     52,  15, 161, 209, 209, 210, 194, 194, 210, 194, 210, 194,
    210, 195, 194, 210, 195, 195, 195, 195, 179, 195, 195, 195,
    195, 195, 195, 195, 195, 195, 195, 195, 195, 196, 195, 195,
    195, 195, 211, 195, 195, 211, 195, 210, 226, 210, 226, 226,
    225, 241, 241,  64,  52,  15,   1, 241, 241, 226, 226, 226,
    211, 210, 211, 210, 211, 195, 210, 211, 195, 195, 195, 211,
    195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195,
    195, 194, 195, 195, 195, 194, 210, 195, 194, 210, 194, 210,
    194, 210, 194, 194, 209, 209, 209, 224,  51,  21, 129, 240,
     81, 240,  81, 240,  81, 240,  81, 194,  97,  98,  68,  65,
     68,  99,  49,  51, 162,  33,  34, 229, 240,  49, 240,  53,
    226,  33,  34, 163,  49,  51, 100,  65,  68,  66,  97,  98,
    193, 240,  81, 240,  81, 240,  81, 240,  81,   0,  75,  97,
     34,   0,  40,   2, 240, 240,  34, 240, 240,  34, 240, 240,
     34, 240, 240,  34, 240, 240,  34, 240, 240,  34, 240, 240,
     34, 240, 240,  34, 240, 240,  34, 240, 240,  34, 240, 240,
     34, 240, 240,  34, 240, 240,  34, 240, 240,  34, 240, 240,
     34, 240,  63,  15, 240,  50, 240, 240,  34, 240, 240,  34,
    240, 240,  34, 240, 240,  34, 240, 240,  34, 240, 240,  34,
    240, 240,  34, 240, 240,  34, 240, 240,  34, 240, 240,  34,
    240, 240,  34, 240, 240,  34, 240, 240,  34,   0,  40,  64,
     20,   9,   0,  37,  35,  85,  69,  84, 129, 129, 129, 129,
    113, 129, 129, 113, 129, 113, 240, 160,   9,  16,   0,  52,
     12,  76,   0,  42,  64,  11,   8,   0,  33,  18,  84,  68,
     82,   0,  12,  80, 102,  22, 240,  18, 240,  82, 240,  81,
    240,  82, 240,  82, 240,  81, 240,  82, 240,  82, 240,  81,
    240,  82, 240,  82, 240,  81, 240,  82, 240,  82, 240,  81,
    240,  82, 240,  82, 240,  66, 240,  82, 240,  82, 240,  66,
    240,  82, 240,  82, 240,  66, 240,  82, 240,  82, 240,  66,
    240,  82, 240,  82, 240,  66, 240,  82, 240,  82, 240,  66,
    240,  82, 240,  81, 240,  82, 240,  82, 240,  81, 240,  82,
    240,  82, 240,  81, 240,  82, 240,  82, 240,  81, 240,  82,
    240,  82, 240,  81, 240,  82, 240,  82, 240,  80,  71,  22,
      0,  14,  70, 242,  67, 179,  99, 162, 130, 146, 162, 130,
    162, 115, 163,  98, 194,  98, 194,  83, 195,  67, 195,  67,
    195,  67, 195,  67, 195,  67, 195,  67, 195,  67, 195,  67,
    195,  67, 195,  67, 195,  67, 195,  67, 195,  67, 195,  67,
    195,  82, 194,  99, 178,  99, 163, 114, 163, 114, 162, 146,
    130, 163,  99, 179,  67, 230,   0,  31,  64,  66,  19,   0,
     12, 113, 240,  34, 229, 164,  35, 240,  19, 240,  19, 240,
     19, 240,  19, 240,  19, 240,  19, 240,  19, 240,  19, 240,
     19, 240,  19, 240,  19, 240,  19, 240,  19, 240,  19, 240,
     19, 240,  19, 240,  19, 240,  19, 240,  19, 240,  19, 240,
     19, 240,  19, 240,  19, 240,  19, 240,  19, 240,  19, 245,
    159,   0,  29,  71,  22,   0,  14,  70, 226,  83, 177, 131,
    145, 163, 113, 195,  97, 195,  81, 227,  67, 195,  68, 179,
     68, 179,  82, 195, 240,  67, 240,  51, 240,  67, 240,  66,
    240,  67, 240,  51, 240,  66, 240,  66, 240,  66, 240,  66,
    240,  66, 240,  66, 240,  66, 240,  81, 161, 145, 177, 129,
    193, 113, 209,  97, 209, 111,   1,  95,   2,  95,   2,   0,
     33,  80,  70,  23,   0,  15,  23, 226,  99, 177, 147, 145,
    179, 115, 163, 116, 148, 100, 148, 114, 163, 240,  83, 240,
     83, 240,  67, 240,  82, 240,  82, 240,  82, 240,  21, 240,
    131, 240, 115, 240,  84, 240,  83, 240,  84, 240,  83, 240,
     84, 240,  68,  67, 196,  68, 180,  68, 180,  67, 196,  65,
    227,  97, 196,  98, 179, 130, 147, 178,  84, 230,   0,  33,
     79,  24,   0,  13,  97, 240, 114, 240,  99, 240,  99, 240,
     84, 240,  65,  19, 240,  65,  19, 240,  49,  35, 240,  49,
     35, 240,  33,  51, 240,  17,  67, 240,  17,  67, 241,  83,
    241,  83, 225,  99, 225,  99, 209, 115, 193, 131, 193, 131,
    177, 147, 177, 147, 161, 163, 145, 179, 145, 179, 159,   5,
    240,  19, 240,  99, 240,  99, 240,  99, 240,  99, 240,  99,
    240,  99, 240,  43,   0,  36,  80,  71,  22,   0,  14,   2,
    162, 141, 156, 161,  23, 209, 240,  97, 240,  97, 240,  97,
    240,  97, 240,  97, 240,  97, 240,  97, 240,  97,  69, 193,
     33,  83, 163, 130, 145, 178, 240,  83, 240,  67, 240,  83,
    240,  67, 240,  67, 240,  67,  67, 195,  67, 195,  67, 195,
     66, 211,  65, 226,  81, 211,  97, 194, 114, 162, 146, 130,
    178,  98, 230,   0,  31,  80,  74,  22,   0,  14, 117, 242,
     82, 178, 145, 146, 131, 146, 131, 130, 147, 114, 240,  82,
    240,  67, 240,  67, 240,  66, 240,  82,  69, 163,  49,  67,
    131,  33, 114, 115,  17, 146, 100, 162, 100, 163,  83, 194,
     83, 195,  67, 195,  67, 195,  67, 195,  67, 195,  82, 195,
     82, 195,  82, 195,  83, 178, 114, 178, 114, 162, 146, 146,
    162, 114, 194,  67, 230,   0,  31,  64,  75,  23,   0,  11,
     82, 240, 111,   3,  95,   3,  95,   2,  97, 241,  97, 225,
     97, 225, 113, 225, 113, 209, 240,  97, 240, 113, 240,  97,
    240,  97, 240, 113, 240,  97, 240, 113, 240, 113, 240,  97,
    240, 113, 240,  98, 240,  98, 240,  98, 240,  82, 240,  98,
    240,  98, 240,  98, 240,  98, 240,  83, 240,  83, 240,  83,
    240,  83, 240,  83, 240,  83, 240,  83,   0,  33,  48,  71,
     22,   0,  14,  70, 241,  83, 178, 130, 161, 162, 129, 179,
    113, 194, 113, 194,  98, 194,  99, 178, 114, 177, 131, 146,
    133,  98, 165,  66, 197,  34, 230, 240,  53, 240,  17,  21,
    210,  54, 162, 101, 130, 133,  98, 179,  98, 195,  66, 211,
     66, 226,  66, 226,  66, 226,  66, 226,  67, 210,  82, 209,
     99, 177, 131, 146, 163,  82, 230,   0,  31,  64,  74,  22,
      0,  14,  70, 242,  67, 178, 130, 146, 146, 146, 162, 114,
    178, 114, 194,  83, 194,  83, 194,  83, 195,  67, 195,  67,
    195,  67, 195,  67, 195,  82, 195,  82, 180,  83, 164,  98,
    145,  19, 114, 113,  35, 130,  82,  35, 165,  67, 240,  66,
    240,  82, 240,  67, 240,  67, 240,  66, 115, 162, 115, 146,
    131, 146, 130, 146, 146, 130, 178,  83, 230,   0,  31,  96,
     17,   8,   0,  16,  18,  84,  68,  82,   0,  13,  98,  84,
     68,  82,   0,  12,  80,  26,   8,   0,  16,  18,  84,  68,
     82,   0,  13,  98,  84,  68,  83, 113, 113, 113, 113,  97,
    113, 113,  97, 113,  97, 240, 128,  38,   8,   0,  13,  18,
     84,  68,  82, 240, 240, 145,  98,  98,  98,  98,  98,  98,
     98,  98,  98,  98,  98,  98,  98,  98,  98,  99,  68,  68,
     68,  68,  68,  68,  68,  68,  82, 240,  96,  13,  34,   0,
     85,  15,  15,   0,  34,  79,  15,   0,  81,  32,  67,  20,
      0,  33,  35, 240,  36, 240,  20, 240,  19,   0,  12,  33,
    240,  65, 240,  65, 240,  65, 240,  65, 240,  65, 240,  65,
    240,  50, 240,  49, 240,  50, 240,  50, 240,  34, 240,  50,
    240,  34, 240,  34, 240,  35, 240,  19, 240,  35, 163,  67,
    163,  67, 163,  67, 163,  67, 193,  82, 177,  99, 145, 131,
     98, 183,   0,   6,  16,  67,  20,   0,   8,  23, 162, 115,
    113, 163,  81, 194,  83, 163,  67, 163,  67, 163,  67, 163,
    240,  35, 240,  19, 240,  34, 240,  34, 240,  34, 240,  34,
    240,  50, 240,  34, 240,  50, 240,  49, 240,  65, 240,  49,
    240,  65, 240,  65, 240,  65, 240,  65, 240,  65, 240,  65,
      0,  12,  35, 240,  20, 240,  20, 240,  35,   0,  31,  48,
    126,  34,   0,  14,  39, 240, 147, 115, 240,  81, 194, 240,
     34, 241, 241, 240,  49, 209, 240,  81, 178, 133, 129, 161,
    114,  82,  98, 129, 114, 114,  97, 129,  98, 146,  82,  97,
     99, 163,  65,  97,  83, 195,  49,  97,  83, 195,  50,  65,
     98, 211,  65,  65,  83, 211,  65,  65,  83, 211,  65,  65,
     83, 211,  65,  65,  83, 211,  65,  65,  83, 211,  65,  65,
     83, 211,  65,  65,  83, 211,  65,  81,  83, 195,  65,  81,
     83, 195,  65,  81,  99, 164,  65,  97,  98, 149,  49, 113,
     99, 114,  19,  49, 129, 115,  66,  51,  33, 130, 133, 100,
    162, 240, 240,  50, 240, 240,  50, 240,  82, 179, 243, 243,
    148, 240, 105,   0,  52,  80, 108,  35,   0,  10,  81, 240,
    240,  66, 240, 240,  35, 240, 240,  35, 240, 240,  36, 240,
    241,  19, 240, 241,  19, 240, 241,  20, 240, 209,  51, 240,
    209,  51, 240, 209,  52, 240, 177,  83, 240, 177,  83, 240,
    161, 100, 240, 145, 115, 240, 145, 115, 240, 129, 132, 240,
    113, 147, 240, 113, 147, 240,  97, 164, 240,  81, 179, 240,
     81, 179, 240,  79,   2, 240,  49, 211, 240,  49, 211, 240,
     33, 243, 240,  17, 243, 240,  17, 244, 225, 240,  35, 225,
    240,  35, 225, 240,  36, 194, 240,  51, 194, 240,  51, 164,
    240,  52, 120, 218,   0,  53,  89,  32,   0,  16,  15,   5,
    240,  19, 180, 227, 212, 195, 228, 179, 244, 163, 244, 163,
    240,  19, 163, 240,  20, 147, 240,  20, 147, 240,  19, 163,
    244, 163, 243, 179, 227, 195, 211, 211, 163, 240,  31,   2,
    243, 196, 211, 228, 179, 244, 163, 240,  20, 147, 240,  20,
    147, 240,  36, 131, 240,  36, 131, 240,  36, 131, 240,  36,
    131, 240,  36, 131, 240,  36, 131, 240,  20, 147, 240,  20,
    147, 244, 163, 228, 179, 196, 159,   6,   0,  49,  48,  99,
     32,   0,  13,  87, 113, 227, 114,  81, 195, 177,  50, 179,
    209,  34, 147, 240,  20, 132, 240,  20, 131, 240,  51, 115,
    240,  67, 100, 240,  82,  99, 240,  98,  84, 240,  98,  84,
    240, 113,  84, 240, 113,  68, 240, 212, 240, 212, 240, 212,
    240, 212, 240, 212, 240, 212, 240, 212, 240, 212, 240, 228,
    240, 113,  84, 240, 113,  84, 240, 113,  99, 240, 113, 100,
    240,  81, 131, 240,  81, 147, 240,  65, 148, 240,  33, 180,
    241, 212, 209, 240,  19, 177, 240,  68,  98, 240, 120,   0,
     45,  64,  99,  34,   0,  17,  15,   4, 240,  67, 180, 240,
     19, 211, 243, 227, 227, 243, 211, 240,  19, 195, 240,  35,
    179, 240,  36, 163, 240,  51, 163, 240,  52, 147, 240,  52,
    147, 240,  67, 147, 240,  68, 131, 240,  68, 131, 240,  68,
    131, 240,  68, 131, 240,  68, 131, 240,  68, 131, 240,  68,
    131, 240,  68, 131, 240,  68, 131, 240,  67, 147, 240,  52,
    147, 240,  52, 147, 240,  51, 163, 240,  36, 163, 240,  35,
    179, 240,  19, 195, 240,  19, 195, 243, 211, 211, 243, 180,
    207,   4,   0,  52, 112, 100,  31,   0,  15,  79,  10, 163,
    213, 163, 243, 163, 240,  18, 163, 240,  33, 163, 240,  34,
    147, 240,  49, 147, 240,  49, 147, 240,  49, 147, 161, 113,
    147, 161, 240,  35, 161, 240,  35, 161, 240,  35, 146, 240,
     35, 131, 240,  46, 240,  35, 131, 240,  35, 146, 240,  35,
    161, 240,  35, 161, 240,  35, 161, 129, 131, 161, 129, 131,
    240,  65, 131, 240,  65, 131, 240,  65, 131, 240,  65, 131,
    240,  50, 131, 240,  49, 147, 240,  49, 147, 240,  34, 147,
    240,  19, 147, 229,  95,  11,   0,  47,  16,  91,  30,   0,
     15,  15,  10, 147, 213, 147, 243, 147, 240,  18, 147, 240,
     33, 147, 240,  33, 147, 240,  33, 147, 240,  33, 147, 240,
     49, 131, 240,  49, 131, 161, 113, 131, 161, 240,  19, 161,
    240,  19, 161, 240,  19, 146, 240,  19, 131, 240,  30, 240,
     19, 131, 240,  19, 146, 240,  19, 161, 240,  19, 161, 240,
     19, 161, 240,  19, 161, 240,  19, 240, 195, 240, 195, 240,
    195, 240, 195, 240, 195, 240, 195, 240, 195, 240, 196, 240,
    124,   0,  47,  32, 111,  35,   0,  14,  88, 113, 240,  35,
    114,  81, 243, 177,  50, 227, 209,  34, 195, 240,  20, 180,
    240,  20, 179, 240,  51, 163, 240,  82, 148, 240,  82, 147,
    240,  98, 132, 240, 113, 132, 240, 113, 131, 240, 129, 116,
    240, 240,  20, 240, 240,  20, 240, 240,  20, 240, 240,  20,
    240, 240,  20, 240, 240,  20, 240, 240,  20, 240, 240,  20,
    252,  84, 240,  68, 132, 240,  83, 132, 240,  83, 147, 240,
     83, 148, 240,  67, 163, 240,  67, 179, 240,  51, 180, 240,
     35, 196, 240,  19, 212, 225,  18, 243, 193,  34, 240,  36,
    114,  65, 240,  73,   0,  49, 112,  72,  33,   0,  16,  75,
    123, 131, 243, 195, 243, 195, 243, 195, 243, 195, 243, 195,
    243, 195, 243, 195, 243, 195, 243, 195, 243, 195, 243, 195,
    243, 195, 243, 195, 243, 207,   6, 195, 243, 195, 243, 195,
    243, 195, 243, 195, 243, 195, 243, 195, 243, 195, 243, 195,
    243, 195, 243, 195, 243, 195, 243, 195, 243, 195, 243, 195,
    243, 195, 243, 139, 123,   0,  50,  39,  15,   0,   7,  75,
    131, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195,
    195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195,
    195, 195, 195, 195, 195, 195, 195, 139,   0,  23,  72,  21,
      0,  11,  43, 228, 240,  51, 240,  51, 240,  51, 240,  51,
    240,  51, 240,  51, 240,  51, 240,  51, 240,  51, 240,  51,
    240,  51, 240,  51, 240,  51, 240,  51, 240,  51, 240,  51,
    240,  51, 240,  51, 240,  51, 240,  51, 240,  51, 240,  51,
    240,  51, 240,  51, 130, 131, 116, 115, 116, 115, 115, 130,
    145, 131, 146,  99, 178,  67, 229,   0,  30,  48, 101,  34,
      0,  17,  11, 184, 131, 240,  20, 179, 240,  18, 211, 240,
     17, 227, 241, 243, 225, 240,  19, 209, 240,  35, 193, 240,
     51, 177, 240,  67, 161, 240,  83, 145, 240,  99, 129, 240,
    115, 113, 240, 131,  99, 240, 115,  84, 240, 115,  65,  35,
    240,  99,  49,  52, 240,  83,  33,  83, 240,  83,  18,  84,
    240,  69, 116, 240,  52, 147, 240,  51, 164, 240,  35, 180,
    240,  19, 195, 240,  19, 196, 243, 211, 243, 227, 227, 228,
    211, 243, 211, 244, 195, 240,  20, 179, 240,  21, 107, 169,
      0,  51,  64,  74,  28,   0,  14,  12, 240,  83, 240, 163,
    240, 163, 240, 163, 240, 163, 240, 163, 240, 163, 240, 163,
    240, 163, 240, 163, 240, 163, 240, 163, 240, 163, 240, 163,
    240, 163, 240, 163, 240, 163, 240, 163, 240, 163, 240, 163,
    240, 163, 240,  17, 131, 241, 147, 241, 147, 241, 147, 241,
    147, 241, 147, 226, 147, 226, 147, 211, 147, 196, 147, 166,
     95,   7,   0,  42,  96, 138,  40,   0,  20,   8, 240, 103,
    132, 240,  84, 193,  18, 240,  65,  19, 193,  19, 240,  49,
     19, 193,  19, 240,  49,  19, 193,  34, 240,  33,  35, 193,
     35, 240,  17,  35, 193,  35, 240,  17,  35, 193,  50, 241,
     51, 193,  51, 225,  51, 193,  51, 209,  67, 193,  67, 193,
     67, 193,  67, 193,  67, 193,  82, 177,  83, 193,  83, 161,
     83, 193,  83, 161,  83, 193,  98, 145,  99, 193,  99, 129,
     99, 193,  99, 129,  99, 193, 114, 113, 115, 193, 115,  97,
    115, 193, 115,  97, 115, 193, 131,  65, 131, 193, 131,  65,
    131, 193, 131,  49, 147, 193, 147,  33, 147, 193, 147,  33,
    147, 193, 162,  17, 163, 193, 164, 163, 193, 164, 163, 193,
    178, 179, 180, 146, 179, 137, 114, 123,   0,  60,  64, 101,
     33,   0,  16,  72, 201, 132, 243, 181, 241, 193,  19, 241,
    193,  35, 225, 193,  36, 209, 193,  51, 209, 193,  67, 193,
    193,  68, 177, 193,  83, 177, 193,  84, 161, 193,  99, 161,
    193, 115, 145, 193, 116, 129, 193, 131, 129, 193, 132, 113,
    193, 147, 113, 193, 163,  97, 193, 164,  81, 193, 179,  81,
    193, 180,  65, 193, 195,  65, 193, 211,  49, 193, 212,  33,
    193, 227,  33, 193, 243,  17, 193, 245, 193, 240,  20, 193,
    240,  20, 193, 240,  35, 193, 240,  50, 179, 240,  34, 137,
    241,   0,  50,  64, 106,  35,   0,  14,  87, 240, 164,  84,
    240,  98, 179, 240,  35, 211, 243, 243, 211, 240,  35, 195,
    240,  36, 163, 240,  67, 148, 240,  68, 131, 240,  99, 116,
    240, 100, 100, 240, 100,  99, 240, 131,  84, 240, 132,  68,
    240, 132,  68, 240, 132,  68, 240, 132,  68, 240, 132,  68,
    240, 132,  68, 240, 132,  68, 240, 132,  68, 240, 132,  84,
    240, 115, 100, 240, 100, 100, 240, 100, 115, 240,  99, 132,
    240,  68, 147, 240,  67, 164, 240,  36, 180, 240,  19, 211,
    243, 243, 211, 240,  36, 147, 240, 100,  84, 240, 167,   0,
     50,  16,  71,  30,   0,  15,  15,   4, 243, 164, 211, 196,
    179, 212, 163, 228, 147, 243, 147, 244, 131, 244, 131, 244,
    131, 244, 131, 244, 131, 243, 147, 228, 147, 227, 163, 211,
    179, 164, 223, 243, 240, 195, 240, 195, 240, 195, 240, 195,
    240, 195, 240, 195, 240, 195, 240, 195, 240, 195, 240, 195,
    240, 195, 240, 195, 240, 195, 240, 195, 240, 139,   0,  47,
     48, 139,  35,   0,  14,  87, 240, 164,  84, 240,  99, 163,
    240,  35, 211, 243, 243, 211, 240,  35, 195, 240,  36, 163,
    240,  67, 148, 240,  68, 131, 240,  99, 116, 240, 100, 100,
    240, 100,  99, 240, 131,  84, 240, 132,  68, 240, 132,  68,
    240, 132,  68, 240, 132,  68, 240, 132,  68, 240, 132,  68,
    240, 132,  68, 240, 132,  68, 240, 132,  84, 240, 115, 100,
    240, 100, 100, 240, 100, 115, 240,  99, 132, 240,  68, 147,
    132, 115, 164,  97,  65,  84, 179,  81,  97,  67, 211,  65,
     97,  51, 243,  49,  97,  35, 240,  51,  17, 116, 240,  83,
     17,  83, 240, 167,  17, 240, 240,  66, 129, 240, 146, 129,
    240, 161, 129, 240, 162,  98, 240, 163,  66, 240, 185, 240,
    200, 240, 199, 240, 229,   0,   9,  80,  91,  35,   0,  17,
     79,   3, 240,  99, 164, 240,  51, 195, 240,  35, 212, 243,
    228, 227, 228, 227, 244, 211, 244, 211, 244, 211, 244, 211,
    244, 211, 243, 227, 227, 243, 211, 240,  19, 195, 240,  35,
    163, 240,  77, 240, 115, 147, 240,  83, 179, 240,  51, 195,
    240,  35, 211, 240,  19, 211, 240,  19, 211, 240,  19, 212,
    243, 212, 243, 212, 243, 212, 243, 212, 243, 212, 243, 227,
     97, 131, 228,  81, 131, 228,  81,  75, 180,  49, 240, 229,
      0,  48, 112,  85,  25,   0,  10,  23,  81, 163,  83,  49,
    146, 146,  18, 130, 180, 115, 195, 114, 226,  99, 226,  99,
    241,  99, 241,  99, 241, 100, 225, 100, 225, 116, 240, 101,
    240, 103, 240,  73, 240,  44, 251, 240,  56, 240,  86, 240,
    101, 240, 100, 240, 116,  65, 240,  20,  65, 240,  35,  65,
    240,  35,  66, 240,  19,  66, 240,  19,  66, 240,  19,  67,
    242,  83, 227,  84, 195,  98,  34, 162, 114,  66,  99, 129,
    119,   0,  35,  80,  82,  33,   0,  16,  95,  12, 100, 131,
    132,  98, 163, 162,  82, 179, 178,  66, 179, 178,  65, 195,
    193,  65, 195, 193,  65, 195, 193,  65, 195, 193,  65, 195,
    193,  65, 195, 193, 240,  35, 240, 243, 240, 243, 240, 243,
    240, 243, 240, 243, 240, 243, 240, 243, 240, 243, 240, 243,
    240, 243, 240, 243, 240, 243, 240, 243, 240, 243, 240, 243,
    240, 243, 240, 243, 240, 243, 240, 243, 240, 229, 240, 157,
      0,  51, 104,  33,   0,  16,  75, 153, 131, 244, 179, 240,
     33, 195, 240,  33, 195, 240,  33, 195, 240,  33, 195, 240,
     33, 195, 240,  33, 195, 240,  33, 195, 240,  33, 195, 240,
     33, 195, 240,  33, 195, 240,  33, 195, 240,  33, 195, 240,
     33, 195, 240,  33, 195, 240,  33, 195, 240,  33, 195, 240,
     33, 195, 240,  33, 195, 240,  33, 195, 240,  33, 195, 240,
     33, 195, 240,  33, 195, 240,  33, 195, 240,  33, 210, 240,
     17, 227, 241, 242, 225, 240,  19, 209, 240,  34, 193, 240,
     67, 145, 240, 114,  98, 240, 166,   0,  47,  32, 109,  36,
      0,  18,  10, 232, 116, 240,  68, 163, 240,  82, 179, 240,
     81, 196, 240,  50, 211, 240,  49, 228, 240,  33, 243, 240,
     17, 240,  19, 240,  17, 240,  20, 241, 240,  35, 225, 240,
     51, 225, 240,  52, 194, 240,  67, 193, 240,  84, 177, 240,
     99, 161, 240, 115, 161, 240, 116, 145, 240, 131, 129, 240,
    147, 129, 240, 148,  98, 240, 163,  97, 240, 180,  81, 240,
    195,  65, 240, 211,  65, 240, 212,  49, 240, 227,  33, 240,
    243,  33, 240, 244,  17, 240, 240,  20, 240, 240,  36, 240,
    240,  50, 240, 240,  66, 240, 240,  66,   0,  51, 112, 149,
     49,   0,  24,  74, 138, 152, 116, 228, 228, 148, 228, 242,
    179, 243, 241, 195, 243, 241, 196, 227, 241, 211, 228, 209,
    227, 209,  19, 209, 228, 193,  19, 209, 243, 193,  20, 177,
    240,  19, 177,  51, 177, 240,  20, 161,  51, 177, 240,  35,
    161,  52, 145, 240,  51, 145,  83, 145, 240,  51, 145,  83,
    145, 240,  52, 129,  84, 129, 240,  67, 113, 115, 113, 240,
     83, 113, 115, 113, 240,  84,  97, 115, 113, 240,  99,  97,
    116,  81, 240, 115,  81, 147,  81, 240, 116,  65, 147,  81,
    240, 131,  65, 148,  49, 240, 147,  49, 179,  49, 240, 148,
     33, 179,  49, 240, 163,  33, 180,  17, 240, 179,  17, 211,
     17, 240, 179,  17, 211,  17, 240, 181, 212, 240, 211, 243,
    240, 211, 243, 240, 211, 243, 240, 226, 242, 240, 241, 240,
     33,   0,  69,  64, 101,  36,   0,  18,  26, 169, 165, 228,
    228, 226, 240,  35, 226, 240,  36, 209, 240,  68, 177, 240,
     99, 161, 240, 116, 145, 240, 132, 113, 240, 163,  97, 240,
    180,  66, 240, 196,  49, 240, 227,  33, 240, 246, 240, 240,
     20, 240, 240,  51, 240, 240,  52, 240, 240,  37, 240, 241,
     36, 240, 210,  36, 240, 209,  68, 240, 177, 100, 240, 146,
    100, 240, 145, 132, 240, 113, 164, 240,  82, 164, 240,  81,
    196, 240,  49, 228, 240,  18, 228, 240,  17, 240,  20, 226,
    240,  36, 181, 246, 121, 218,   0,  54,  64, 106,  37,   0,
     18,  74, 248, 117, 240,  67, 180, 240,  66, 212, 240,  49,
    243, 240,  33, 240,  20, 240,  17, 240,  36, 225, 240,  52,
    210, 240,  68, 193, 240,  99, 177, 240, 116, 161, 240, 132,
    129, 240, 148, 113, 240, 180,  97, 240, 195,  81, 240, 212,
     50, 240, 228,  33, 240, 240,  19,  17, 240, 240,  37, 240,
    240,  51, 240, 240,  67, 240, 240,  67, 240, 240,  67, 240,
    240,  67, 240, 240,  67, 240, 240,  67, 240, 240,  67, 240,
    240,  67, 240, 240,  67, 240, 240,  67, 240, 240,  67, 240,
    240,  67, 240, 251,   0,  57,  48,  73,  27,   0,  13,  95,
      7,  86, 196,  84, 212,  99, 227, 114, 228, 113, 228, 129,
    227, 145, 212, 145, 211, 161, 196, 161, 180, 240, 131, 240,
    132, 240, 116, 240, 131, 240, 132, 240, 131, 240, 132, 240,
    116, 240, 131, 240, 132, 240, 131, 193, 164, 193, 148, 209,
    147, 225, 132, 225, 131, 241, 115, 242, 100, 242,  99, 243,
     84, 228,  68, 214,  79,   8,   0,  41,  51,  11, 183,  66,
    146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146,
    146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146,
    146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146,
    146, 146, 146, 146, 146, 146, 146, 146, 146, 151,  64,  37,
     18,   0,   7,  17, 129, 129, 129, 113, 129, 113, 129, 129,
    129, 129, 129, 113, 129, 129, 129, 129, 129, 129, 129, 129,
     18,  81,  18,  85,  69,  84,  84,  83,  99,   0,  72,  80,
     51,  11, 183, 146, 146, 146, 146, 146, 146, 146, 146, 146,
    146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146,
    146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146,
    146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146,
    146,  71,  64,  19,  16,   0,   6,  81, 242, 209,  18, 177,
     50, 145,  97, 113, 129,  81, 161,   0,  78,  64,  11,   8,
    240, 240, 178,  84,  68,  82,   0,  40,  80,  21,   9, 240,
    241, 129, 113, 113, 129, 129, 113, 129, 129, 129, 129,  18,
     85,  84,  83,   0,  36,  80,  59,  24,   0,  45, 101, 240,
     34,  67, 225, 115, 193, 147, 177, 147, 178, 147, 148, 131,
    148, 131, 162, 147, 240,  24, 211,  83, 179, 115, 163, 131,
    147, 147, 147, 147,  49,  67, 163,  49,  67, 163,  49,  67,
    148,  49,  67, 148,  49,  83, 113,  19,  49,  99,  66,  53,
    149,  99,   0,  36,  96,  77,  25,   0,  12,  70, 240, 100,
    240, 115, 240, 115, 240, 115, 240, 115, 240, 115, 240, 115,
    240, 115, 240, 115, 240, 115, 240, 115,  69, 211,  34,  67,
    179,  17, 115, 164, 147, 147, 178, 147, 179, 131, 194, 131,
    195, 115, 195, 115, 195, 115, 195, 115, 195, 115, 195, 115,
    195, 115, 195, 115, 194, 131, 179, 131, 178, 148, 146, 162,
     33, 115, 162,  49,  82, 193,  85,   0,  38, 112,  48,  20,
      0,  38,  53, 210,  82, 147, 114, 130, 145, 114, 177,  83,
    147,  83, 147,  82, 163,  67, 240,  35, 240,  35, 240,  35,
    240,  35, 240,  35, 240,  35, 240,  51, 240,  35, 177,  99,
    161,  99, 145, 131, 129, 163,  66, 213,   0,  31,  77,  25,
      0,  11,  35, 240,  70, 240, 115, 240, 115, 240, 115, 240,
    115, 240, 115, 240, 115, 240, 115, 240, 115, 240, 115, 240,
    115, 229,  51, 194,  81,  35, 163, 113,  19, 162, 148, 146,
    179, 131, 179, 131, 179, 130, 195, 115, 195, 115, 195, 115,
    195, 115, 195, 115, 195, 115, 195, 115, 195, 131, 179, 131,
    179, 146, 179, 147, 148, 163, 113,  19, 179,  66,  38, 165,
     70,   0,  38,  49,  22,   0,  42,  21, 242,  67, 194, 114,
    162, 131, 130, 163,  99, 163,  98, 195,  82, 195,  67, 195,
     67, 195,  79,   3,  67, 240,  67, 240,  67, 240,  67, 240,
     82, 240,  83, 209,  98, 194,  99, 177, 131, 145, 179,  82,
    230,   0,  34,  16,  44,  18,   0,   7, 101, 194,  50, 162,
     51, 147,  51, 146, 243, 243, 243, 243, 243, 243, 243, 243,
    188, 163, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243,
    243, 243, 243, 243, 243, 243, 243, 243, 202,   0,  27, 112,
     75,  25,   0,  47,  85,  84, 163,  20,  18,  35, 130,  83,
     66, 130, 115, 195, 130, 194, 147, 178, 147, 178, 147, 178,
    147, 178, 147, 179, 130, 210, 115, 211,  98, 228,  66, 225,
     53, 240,  17, 240, 145, 240, 145, 240, 146, 240, 156, 237,
    162, 165, 114, 226, 113, 243,  82, 240,  18,  82, 240,  18,
     82, 240,  18,  83, 242,  98, 226, 131, 178, 164,  99, 248,
      0,   7,  80,  74,  25,   0,  12,  70, 240, 100, 240, 115,
    240, 115, 240, 115, 240, 115, 240, 115, 240, 115, 240, 115,
    240, 115, 240, 115, 240, 115,  69, 211,  34,  51, 195,  17,
     99, 180, 131, 164, 131, 164, 131, 163, 147, 163, 147, 163,
    147, 163, 147, 163, 147, 163, 147, 163, 147, 163, 147, 163,
    147, 163, 147, 163, 147, 163, 147, 163, 147, 163, 147, 163,
    147, 121,  57,   0,  38,  34,  13,   0,   8,  51, 164, 148,
    147,   0,  11,  34, 118, 148, 163, 163, 163, 163, 163, 163,
    163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163,
    121,   0,  20,  49,  15,   0,  10,  35, 181, 165, 179,   0,
     12, 115, 135, 180, 195, 195, 195, 195, 195, 195, 195, 195,
    195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195,
    195, 195, 195, 195,  67,  82,  83,  82,  83,  66, 113,  66,
    149, 240, 240, 128,  80,  26,   0,  13,   6, 240, 116, 240,
    131, 240, 131, 240, 131, 240, 131, 240, 131, 240, 131, 240,
    131, 240, 131, 240, 131, 240, 131, 240, 131, 120, 131, 133,
    163, 131, 195, 129, 227, 113, 243,  97, 240,  19,  81, 240,
     35,  65, 240,  51,  51, 240,  35,  36, 240,  35,  17,  35,
    240,  20,  67, 243,  83, 243,  99, 227, 115, 211, 115, 211,
    131, 195, 146, 195, 147, 179, 148, 121,  88,   0,  39,  64,
     39,  13,   0,   6,  70, 148, 163, 163, 163, 163, 163, 163,
    163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163,
    163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163,
    121,   0,  20,  78,  38,   0,  71,  53,  69, 118, 166,  34,
     51,  66,  67, 180,  17,  99,  33, 115, 180, 131,  17, 131,
    164, 132, 147, 164, 132, 147, 163, 147, 163, 163, 147, 163,
    163, 147, 163, 163, 147, 163, 163, 147, 163, 163, 147, 163,
    163, 147, 163, 163, 147, 163, 163, 147, 163, 163, 147, 163,
    163, 147, 163, 163, 147, 163, 163, 147, 163, 163, 147, 163,
    163, 147, 163, 121,  57,  73,   0,  57,  64,  52,  25,   0,
     47,   5,  69, 166,  34,  51, 180,  17,  99, 180, 131, 164,
    131, 164, 131, 163, 147, 163, 147, 163, 147, 163, 147, 163,
    147, 163, 147, 163, 147, 163, 147, 163, 147, 163, 147, 163,
    147, 163, 147, 163, 147, 163, 147, 163, 147, 121,  57,   0,
     38,  51,  24,   0,  45, 118, 240,  18,  83, 210, 130, 178,
    162, 146, 194, 115, 195,  98, 226,  98, 227,  67, 227,  67,
    227,  67, 227,  67, 227,  67, 227,  67, 227,  67, 227,  82,
    226,  99, 195, 114, 194, 146, 162, 178, 130, 211,  67, 240,
     22,   0,  37,  48,  72,  25,   0,  50,  21,  69, 166,  34,
     67, 179,  17, 115, 164, 147, 147, 179, 131, 179, 131, 179,
    131, 195, 115, 195, 115, 195, 115, 195, 115, 195, 115, 195,
    115, 195, 115, 179, 131, 179, 131, 178, 148, 147, 147,  17,
    115, 163,  33,  82, 195,  53, 227, 240, 115, 240, 115, 240,
    115, 240, 115, 240, 115, 240, 115, 240, 115, 240, 115, 240,
     73,   0,   8,  32,  74,  25,   0,  50, 117,  81, 194,  81,
     65, 163, 113,  34, 147, 145,  18, 146, 164, 131, 179, 131,
    179, 115, 195, 115, 195, 115, 195, 115, 195, 115, 195, 115,
    195, 115, 195, 131, 179, 131, 179, 146, 164, 147, 148, 163,
    113,  19, 179,  66,  35, 213,  67, 240, 115, 240, 115, 240,
    115, 240, 115, 240, 115, 240, 115, 240, 115, 240, 115, 240,
    115, 240,  73,   0,   6,  96,  36,  18,   0,  33, 117,  52,
     86,  33,  50, 100,  17,  51, 115,  17,  51, 116,  81, 132,
    227, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243,
    243, 243, 243, 202,   0,  28,  49,  19,   0,  36,  22,  49,
    114, 100,  98, 131,  97, 162,  82, 177,  82, 177,  83, 161,
     84, 240,  21, 248, 201, 230, 240,  20,  81, 179,  65, 179,
     66, 178,  66, 178,  66, 178,  67, 161,  82,  17, 130,  82,
     33,  98,  97,  70,   0,  29,  64,  50,  18,   0,  16,  65,
    240,  33, 240,  33, 240,  33, 240,  18, 240,  18, 243, 243,
    213, 189, 147, 243, 243, 243, 243, 243, 243, 243, 243, 243,
    243, 243,  97, 131,  97, 131,  97, 131,  97, 131,  97, 131,
     97, 147,  65, 179,  34, 196,   0,  27, 112,  50,  25,   0,
     50,   6, 102, 148, 147, 163, 147, 163, 147, 163, 147, 163,
    147, 163, 147, 163, 147, 163, 147, 163, 147, 163, 147, 163,
    147, 163, 147, 163, 147, 163, 147, 163, 147, 163, 132, 163,
    132, 179,  97,  19, 195,  65,  38, 166,  54,   0,  38,  57,
     26,   0,  52,   8, 119, 115, 179, 147, 178, 178, 177, 195,
    161, 210, 145, 227, 129, 227, 129, 242, 113, 240,  19,  97,
    240,  19,  97, 240,  35,  65, 240,  51,  65, 240,  66,  49,
    240,  83,  33, 240,  83,  33, 240,  98,  17, 240, 116, 240,
    130, 240, 146, 240, 146,   0,  40,  96,  86,  35,   0,  70,
      8,  56, 102, 100, 131, 147, 147, 146, 161, 163, 146, 161,
    178, 147, 129, 195, 131, 129, 195, 113,  18, 129, 210, 113,
     19,  97, 227,  81,  50,  97, 227,  81,  50,  97, 242,  81,
     51,  65, 240,  19,  49,  82,  65, 240,  19,  49,  82,  65,
    240,  34,  49,  83,  33, 240,  51,  17, 114,  33, 240,  51,
     17, 114,  33, 240,  66,  17, 116, 240,  83, 147, 240,  83,
    147, 240,  98, 146, 240, 113, 177,   0,  54,  16,  57,  27,
      0,  54,   8, 119, 132, 148, 179, 146, 227, 129, 240,  19,
     97, 240,  35,  81, 240,  67,  65, 240,  83,  33, 240, 116,
    240, 131, 240, 163, 240, 148, 240, 113,  35, 240,  81,  51,
    240,  81,  67, 240,  49,  99, 240,  17, 130, 241, 147, 210,
    163, 179, 164, 119, 136,   0,  41,  80,  26,   0,  52,   8,
    119, 115, 179, 147, 178, 178, 177, 195, 161, 195, 145, 226,
    145, 227, 129, 242, 113, 240,  19,  97, 240,  19,  81, 240,
     50,  81, 240,  51,  65, 240,  66,  49, 240,  83,  33, 240,
     83,  33, 240,  98,  17, 240, 116, 240, 130, 240, 146, 240,
    146, 240, 145, 240, 161, 240, 145, 240, 161, 240, 161, 240,
     19,  81, 240,  35,  81, 240,  35,  65, 240,  65,  65, 240,
    100,   0,   9,  50,  21,   0,  42,  31,   1,  83, 147,  98,
    163,  97, 163, 113, 147, 129, 147, 129, 131, 145, 115, 240,
     35, 240,  51, 240,  35, 240,  35, 240,  50, 129, 147, 129,
    131, 145, 115, 161, 115, 161,  99, 162,  83, 178,  67, 164,
     79,   1,   0,  32,  16,   9,  27,   0,  81,  15,   8,   0,
     81,  64,  14,  49,   0, 127,   0,  20,  15,  15,  15,   0,
    127,   0,  20,  64,  24,  16,   0,   6,  50,  82,  99,  67,
     99,  67,  98,  82,  98,  82, 114,  82, 113,  97, 114,  82,
    113,  97,   0,  75,  15,  19,   0,  12,  36, 113, 102,  81,
     97,  86,  97, 116,   0,  95, 112,
};

//*****************************************************************************
//
// The font definition for the 48 point Cm font.
//
//*****************************************************************************
const tFont g_sFontCm48 =
{
    //
    // The format of the font.
    //
    FONT_FMT_PIXEL_RLE,

    //
    // The maximum width of the font.
    //
    44,

    //
    // The height of the font.
    //
    49,

    //
    // The baseline of the font.
    //
    37,

    //
    // The offset to each character in the font.
    //
    {
           0,    5,   43,   78,  214,  313,  456,  568,
         588,  640,  692,  743,  840,  860,  869,  880,
         982, 1053, 1119, 1190, 1260, 1339, 1410, 1484,
        1559, 1630, 1704, 1721, 1747, 1785, 1798, 1865,
        1932, 2058, 2166, 2255, 2354, 2453, 2553, 2644,
        2755, 2827, 2866, 2938, 3039, 3113, 3251, 3352,
        3458, 3529, 3668, 3759, 3844, 3926, 4030, 4139,
        4288, 4389, 4495, 4568, 4619, 4656, 4707, 4726,
        4737, 4758, 4817, 4894, 4942, 5019, 5068, 5112,
        5187, 5261, 5295, 5344, 5424, 5463, 5541, 5593,
        5644, 5716, 5790, 5826, 5875, 5925, 5975, 6032,
        6118, 6175, 6255, 6305, 6314, 6328, 6352,
    },

    //
    // A pointer to the actual font data
    //
    g_pucCm48Data
};
