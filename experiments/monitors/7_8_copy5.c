#ifndef NO_MONITORING
#include "UVWMonitor.h"
#include <stdbool.h>
/* Declare variables for monitoring */
bool uvwState0 = 0;
bool uvwState1 = 0;
bool uvwState2 = 0;
bool uvwState3 = 0;
bool uvwState4 = 0;
bool uvwState5 = 0;
bool uvwState6 = 0;
bool uvwState7 = 0;
bool uvwState8 = 0;
bool uvwState9 = 0;
bool uvwState10 = 0;
bool uvwState11 = 0;
bool uvwState12 = 0;
bool uvwState13 = 0;
bool uvwState14 = 0;
bool uvwState15 = 0;
bool uvwState16 = 0;
bool uvwState17 = 1;
bool uvwState18 = 0;
bool uvwState19 = 0;
bool uvwState20 = 1;
bool uvwState21 = 1;
struct bufType {
  uint32_t b0p0;
  uint32_t b1p0;
  uint32_t b2p0;
  uint32_t b3p0;
  uint32_t b4p0;
  uint32_t b5p0;
  uint32_t b6p0;
  uint32_t b7p0;
  uint32_t b8p0;
  uint32_t b9p0;
  uint32_t b10p0;
  uint32_t b11p0;
  uint32_t b12p0;
  uint32_t b13p0;
  uint32_t b14p0;
  uint32_t b15p0;
  uint32_t b16p0;
  uint32_t b18p0;
  uint32_t b19p0;
} buf = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint32_t b17p0 = 0;
const uint32_t b20p0 = 0;
const uint32_t b21p0 = 0;

const uint16_t lut0[256] = {0xc26,0xc27,0xc66,0xc26,0xc26,0xc33,0xc66,0xc26,
    0xca6,0xca7,0xcf2,0xca6,0xc26,0xc27,0xc66,0xc26,
    0xc26,0xc27,0xc66,0xc26,0xc32,0xc33,0xc72,0xc32,
    0xca6,0xca7,0xcf2,0xca6,0xc26,0xc27,0xc66,0xc26,
    0xd26,0xd27,0xd66,0xd26,0xd26,0xd33,0xd66,0xd26,
    0xdb2,0xdb3,0xdf2,0xdb2,0xd26,0xd27,0xd66,0xd26,
    0xc26,0xc27,0xc66,0xc26,0xc26,0xc33,0xc66,0xc26,
    0xca6,0xca7,0xcf2,0xca6,0xc26,0xc27,0xc66,0xc26,
    0xc04,0xc11,0xc44,0xc04,0xc04,0xc11,0xc44,0xc04,
    0xc84,0xc91,0xcd0,0xc84,0xc04,0xc11,0xc44,0xc04,
    0xc10,0xc11,0xc50,0xc10,0xc10,0xc11,0xc50,0xc10,
    0xc90,0xc91,0xcd0,0xc90,0xc10,0xc11,0xc50,0xc10,
    0xd04,0xd11,0xd44,0xd04,0xd04,0xd11,0xd44,0xd04,
    0xd90,0xd91,0xdd0,0xd90,0xd04,0xd11,0xd44,0xd04,
    0xc04,0xc11,0xc44,0xc04,0xc04,0xc11,0xc44,0xc04,
    0xc84,0xc91,0xcd0,0xc84,0xc04,0xc11,0xc44,0xc04,
    0xe04,0xe05,0xe50,0xe04,0xe04,0xe11,0xe50,0xe04,
    0xe84,0xe85,0xed0,0xe84,0xe04,0xe05,0xe50,0xe04,
    0xe04,0xe05,0xe50,0xe04,0xe10,0xe11,0xe50,0xe10,
    0xe84,0xe85,0xed0,0xe84,0xe04,0xe05,0xe50,0xe04,
    0xf10,0xf11,0xf50,0xf10,0xf10,0xf11,0xf50,0xf10,
    0xf90,0xf91,0xfd0,0xf90,0xf10,0xf11,0xf50,0xf10,
    0xe04,0xe05,0xe50,0xe04,0xe04,0xe11,0xe50,0xe04,
    0xe84,0xe85,0xed0,0xe84,0xe04,0xe05,0xe50,0xe04,
    0xc06,0xc07,0xc46,0xc06,0xc06,0xc13,0xc46,0xc06,
    0xc86,0xc87,0xcd2,0xc86,0xc06,0xc07,0xc46,0xc06,
    0xc06,0xc07,0xc46,0xc06,0xc12,0xc13,0xc52,0xc12,
    0xc86,0xc87,0xcd2,0xc86,0xc06,0xc07,0xc46,0xc06,
    0xd06,0xd07,0xd46,0xd06,0xd06,0xd13,0xd46,0xd06,
    0xd92,0xd93,0xdd2,0xd92,0xd06,0xd07,0xd46,0xd06,
    0xc06,0xc07,0xc46,0xc06,0xc06,0xc13,0xc46,0xc06,
    0xc86,0xc87,0xcd2,0xc86,0xc06,0xc07,0xc46,0xc06};
const uint16_t lut1[256] = {0xc0,0xc0,0xc0,0xd0,0xe0,0xe0,0xe0,0xf0,
    0x6c8,0x6c8,0x6c8,0x6d8,0x6e8,0x6e8,0x6e8,0x6f8,
    0x0,0x0,0x0,0x10,0x5a0,0x5a0,0x5a0,0x5b0,
    0x600,0x600,0x600,0x610,0x7a0,0x7a0,0x7a0,0x7b0,
    0x1000,0x1000,0x1000,0x1010,0x1000,0x1000,0x1000,0x1010,
    0x1000,0x1000,0x1000,0x1010,0x1000,0x1000,0x1000,0x1010,
    0x0,0x0,0x0,0x10,0x5a4,0x5a4,0x5a4,0x5b4,
    0x608,0x608,0x608,0x618,0x7ac,0x7ac,0x7ac,0x7bc,
    0xc0,0xc0,0xc0,0xd0,0xe0,0xe0,0xe0,0xf0,
    0x6c8,0x6c8,0x6c8,0x6d8,0x6e8,0x6e8,0x6e8,0x6f8,
    0xc002,0xc002,0xc002,0xc012,0xc5a2,0xc5a2,0xc5a2,0xc5b2,
    0xc602,0xc602,0xc602,0xc612,0xc7a2,0xc7a2,0xc7a2,0xc7b2,
    0xd002,0xd002,0xd002,0xd012,0xd002,0xd002,0xd002,0xd012,
    0xd002,0xd002,0xd002,0xd012,0xd002,0xd002,0xd002,0xd012,
    0xc000,0xc000,0xc000,0xc010,0xc5a4,0xc5a4,0xc5a4,0xc5b4,
    0xc608,0xc608,0xc608,0xc618,0xc7ac,0xc7ac,0xc7ac,0xc7bc,
    0xc0,0xc0,0xc0,0xd0,0xe0,0xe0,0xe0,0xf0,
    0x6c8,0x6c8,0x6c8,0x6d8,0x6e8,0x6e8,0x6e8,0x6f8,
    0xb801,0xb801,0xb801,0xb811,0xbda1,0xbda1,0xbda1,0xbdb1,
    0xbe01,0xbe01,0xbe01,0xbe11,0xbfa1,0xbfa1,0xbfa1,0xbfb1,
    0x1800,0x1800,0x1800,0x1810,0x1800,0x1800,0x1800,0x1810,
    0x1800,0x1800,0x1800,0x1810,0x1800,0x1800,0x1800,0x1810,
    0xb800,0xb800,0xb800,0xb810,0xbda4,0xbda4,0xbda4,0xbdb4,
    0xbe08,0xbe08,0xbe08,0xbe18,0xbfac,0xbfac,0xbfac,0xbfbc,
    0xc0,0xc0,0xc0,0xd0,0xe0,0xe0,0xe0,0xf0,
    0x6c8,0x6c8,0x6c8,0x6d8,0x6e8,0x6e8,0x6e8,0x6f8,
    0xf803,0xf803,0xf803,0xf813,0xfda3,0xfda3,0xfda3,0xfdb3,
    0xfe03,0xfe03,0xfe03,0xfe13,0xffa3,0xffa3,0xffa3,0xffb3,
    0xd802,0xd802,0xd802,0xd812,0xd802,0xd802,0xd802,0xd812,
    0xd802,0xd802,0xd802,0xd812,0xd802,0xd802,0xd802,0xd812,
    0xf800,0xf800,0xf800,0xf810,0xfda4,0xfda4,0xfda4,0xfdb4,
    0xfe08,0xfe08,0xfe08,0xfe18,0xffac,0xffac,0xffac,0xffbc};
const uint16_t lut2[256] = {0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,
    0x1800,0x0,0x1800,0x0,0x1801,0x1,0x1801,0x1,
    0x6000,0x6000,0x6000,0x6000,0x6001,0x6001,0x6001,0x6001,
    0x7800,0x6000,0x7800,0x6000,0x7801,0x6001,0x7801,0x6001,
    0x0,0x0,0x2,0x2,0x1,0x1,0x2,0x2,
    0x1808,0x500,0x180a,0x502,0x1808,0x501,0x180a,0x502,
    0x6010,0x6600,0x6012,0x6602,0x6010,0x6601,0x6012,0x6602,
    0x7818,0x6700,0x781a,0x6702,0x7818,0x6701,0x781a,0x6702,
    0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,
    0x1800,0x0,0x1800,0x0,0x1801,0x1,0x1801,0x1,
    0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,
    0x1800,0x0,0x1800,0x0,0x1801,0x1,0x1801,0x1,
    0x60,0x0,0x60,0x0,0x61,0x1,0x61,0x1,
    0x1868,0x0,0x1868,0x0,0x1868,0x1,0x1868,0x1,
    0x60,0x0,0x60,0x0,0x61,0x1,0x61,0x1,
    0x1868,0x0,0x1868,0x0,0x1868,0x1,0x1868,0x1,
    0x484,0x484,0x484,0x484,0x484,0x484,0x484,0x484,
    0x1c84,0x484,0x1c84,0x484,0x1c84,0x484,0x1c84,0x484,
    0x6484,0x6484,0x6484,0x6484,0x6484,0x6484,0x6484,0x6484,
    0x7c84,0x6484,0x7c84,0x6484,0x7c84,0x6484,0x7c84,0x6484,
    0x480,0x484,0x482,0x486,0x481,0x484,0x482,0x486,
    0x1c88,0x584,0x1c8a,0x586,0x1c88,0x584,0x1c8a,0x586,
    0x6490,0x6684,0x6492,0x6686,0x6490,0x6684,0x6492,0x6686,
    0x7c98,0x6784,0x7c9a,0x6786,0x7c98,0x6784,0x7c9a,0x6786,
    0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,
    0x1800,0x0,0x1800,0x0,0x1801,0x1,0x1801,0x1,
    0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,
    0x1800,0x0,0x1800,0x0,0x1801,0x1,0x1801,0x1,
    0x60,0x0,0x60,0x0,0x61,0x1,0x61,0x1,
    0x1868,0x0,0x1868,0x0,0x1868,0x1,0x1868,0x1,
    0x60,0x0,0x60,0x0,0x61,0x1,0x61,0x1,
    0x1868,0x0,0x1868,0x0,0x1868,0x1,0x1868,0x1};
const uint16_t lut3[256] = {0x20,0x22,0x20,0x20,0x30,0x32,0x30,0x30,
    0x1a0,0x1a2,0x1a0,0x1a0,0x1b0,0x1b2,0x1b0,0x1b0,
    0x20,0x22,0x20,0x20,0x30,0x32,0x30,0x30,
    0x1a0,0x1a2,0x1a0,0x1a0,0x1b0,0x1b2,0x1b0,0x1b0,
    0x20,0x22,0x20,0x20,0x30,0x32,0x30,0x30,
    0x1a0,0x1a2,0x1a0,0x1a0,0x1b0,0x1b2,0x1b0,0x1b0,
    0x20,0x22,0x20,0x20,0x30,0x32,0x30,0x30,
    0x1a0,0x1a2,0x1a0,0x1a0,0x1b0,0x1b2,0x1b0,0x1b0,
    0x0,0x2,0x0,0x0,0x170,0x172,0x170,0x170,
    0x180,0x182,0x180,0x180,0x1f0,0x1f2,0x1f0,0x1f0,
    0x2e01,0x2e01,0x2e01,0x2e01,0x2f71,0x2f71,0x2f71,0x2f71,
    0x2f81,0x2f81,0x2f81,0x2f81,0x2ff1,0x2ff1,0x2ff1,0x2ff1,
    0x3008,0x3008,0x3008,0x3008,0x3178,0x3178,0x3178,0x3178,
    0x3188,0x3188,0x3188,0x3188,0x31f8,0x31f8,0x31f8,0x31f8,
    0x3e09,0x3e09,0x3e09,0x3e09,0x3f79,0x3f79,0x3f79,0x3f79,
    0x3f89,0x3f89,0x3f89,0x3f89,0x3ff9,0x3ff9,0x3ff9,0x3ff9,
    0x400,0x402,0x400,0x400,0x400,0x402,0x400,0x400,
    0x400,0x402,0x400,0x400,0x400,0x402,0x400,0x400,
    0x600,0x602,0x600,0x600,0x600,0x602,0x600,0x600,
    0x600,0x602,0x600,0x600,0x600,0x602,0x600,0x600,
    0x3408,0x3408,0x3408,0x3408,0x3408,0x3408,0x3408,0x3408,
    0x3408,0x3408,0x3408,0x3408,0x3408,0x3408,0x3408,0x3408,
    0x3608,0x3608,0x3608,0x3608,0x3608,0x3608,0x3608,0x3608,
    0x3608,0x3608,0x3608,0x3608,0x3608,0x3608,0x3608,0x3608,
    0x0,0x2,0x0,0x0,0x174,0x176,0x174,0x174,
    0x180,0x182,0x180,0x180,0x1f4,0x1f6,0x1f4,0x1f4,
    0x2e00,0x2e02,0x2e00,0x2e00,0x2f74,0x2f76,0x2f74,0x2f74,
    0x2f80,0x2f82,0x2f80,0x2f80,0x2ff4,0x2ff6,0x2ff4,0x2ff4,
    0x3000,0x3002,0x3000,0x3000,0x3174,0x3176,0x3174,0x3174,
    0x3180,0x3182,0x3180,0x3180,0x31f4,0x31f6,0x31f4,0x31f4,
    0x3e00,0x3e02,0x3e00,0x3e00,0x3f74,0x3f76,0x3f74,0x3f74,
    0x3f80,0x3f82,0x3f80,0x3f80,0x3ff4,0x3ff6,0x3ff4,0x3ff4};
const uint16_t lut4[256] = {0xc0,0xc0,0xe0,0xc0,0x0,0x0,0x20,0x0,
    0x1000,0x1000,0x1020,0x1000,0x0,0x0,0x20,0x0,
    0xc0,0xc0,0xe0,0xc0,0xb801,0xb801,0xb801,0xb801,
    0x1800,0x1800,0x1820,0x1800,0xb800,0xb800,0xb820,0xb800,
    0xc0,0xc0,0xe0,0xc0,0xc002,0xc002,0xc002,0xc002,
    0xd002,0xd002,0xd002,0xd002,0xc000,0xc000,0xc020,0xc000,
    0xc0,0xc0,0xe0,0xc0,0xf803,0xf803,0xf803,0xf803,
    0xd802,0xd802,0xd802,0xd802,0xf800,0xf800,0xf820,0xf800,
    0x6d0,0x6d0,0x6f0,0x6d0,0x600,0x600,0x620,0x600,
    0x1000,0x1000,0x1020,0x1000,0x610,0x610,0x630,0x610,
    0x6d0,0x6d0,0x6f0,0x6d0,0xbe01,0xbe01,0xbe01,0xbe01,
    0x1800,0x1800,0x1820,0x1800,0xbe10,0xbe10,0xbe30,0xbe10,
    0x6d0,0x6d0,0x6f0,0x6d0,0xc602,0xc602,0xc602,0xc602,
    0xd002,0xd002,0xd002,0xd002,0xc610,0xc610,0xc630,0xc610,
    0x6d0,0x6d0,0x6f0,0x6d0,0xfe03,0xfe03,0xfe03,0xfe03,
    0xd802,0xd802,0xd802,0xd802,0xfe10,0xfe10,0xfe30,0xfe10,
    0xc4,0xc4,0xe4,0xc4,0x584,0x584,0x5a4,0x584,
    0x1000,0x1000,0x1020,0x1000,0x58c,0x58c,0x5ac,0x58c,
    0xc4,0xc4,0xe4,0xc4,0xbd85,0xbd85,0xbd85,0xbd85,
    0x1800,0x1800,0x1820,0x1800,0xbd8c,0xbd8c,0xbdac,0xbd8c,
    0xc4,0xc4,0xe4,0xc4,0xc586,0xc586,0xc586,0xc586,
    0xd002,0xd002,0xd002,0xd002,0xc58c,0xc58c,0xc5ac,0xc58c,
    0xc4,0xc4,0xe4,0xc4,0xfd87,0xfd87,0xfd87,0xfd87,
    0xd802,0xd802,0xd802,0xd802,0xfd8c,0xfd8c,0xfdac,0xfd8c,
    0x6d4,0x6d4,0x6f4,0x6d4,0x784,0x784,0x7a4,0x784,
    0x1000,0x1000,0x1020,0x1000,0x79c,0x79c,0x7bc,0x79c,
    0x6d4,0x6d4,0x6f4,0x6d4,0xbf85,0xbf85,0xbf85,0xbf85,
    0x1800,0x1800,0x1820,0x1800,0xbf9c,0xbf9c,0xbfbc,0xbf9c,
    0x6d4,0x6d4,0x6f4,0x6d4,0xc786,0xc786,0xc786,0xc786,
    0xd002,0xd002,0xd002,0xd002,0xc79c,0xc79c,0xc7bc,0xc79c,
    0x6d4,0x6d4,0x6f4,0x6d4,0xff87,0xff87,0xff87,0xff87,
    0xd802,0xd802,0xd802,0xd802,0xff9c,0xff9c,0xffbc,0xff9c};
const uint16_t lut5[256] = {0x4,0x0,0x10,0x0,0x4,0x0,0x10,0x0,
    0x4,0x0,0x10,0x0,0x4,0x0,0x10,0x0,
    0x4,0x0,0x10,0x0,0x4,0x0,0x10,0x0,
    0x4,0x0,0x10,0x0,0x4,0x0,0x10,0x0,
    0x24,0x20,0x30,0x20,0x4,0x0,0x10,0x0,
    0x4,0x0,0x10,0x0,0x4,0x0,0x10,0x0,
    0x4,0x0,0x10,0x0,0x4,0x0,0x10,0x0,
    0x4,0x0,0x10,0x0,0x4,0x0,0x10,0x0,
    0x4,0x159,0x18,0x158,0x4,0x159,0x18,0x158,
    0x4,0x159,0x18,0x158,0x4,0x159,0x18,0x158,
    0x4,0x159,0x18,0x158,0x4,0x159,0x18,0x158,
    0x4,0x159,0x18,0x158,0x4,0x159,0x18,0x158,
    0x24,0x159,0x38,0x178,0x4,0x159,0x18,0x158,
    0x4,0x159,0x18,0x158,0x4,0x159,0x18,0x158,
    0x4,0x159,0x18,0x158,0x4,0x159,0x18,0x158,
    0x4,0x159,0x18,0x158,0x4,0x159,0x18,0x158,
    0x4,0x182,0x192,0x180,0x4,0x182,0x192,0x180,
    0x4,0x182,0x192,0x180,0x4,0x182,0x192,0x180,
    0x4,0x182,0x192,0x180,0x4,0x182,0x192,0x180,
    0x4,0x182,0x192,0x180,0x4,0x182,0x192,0x180,
    0x24,0x182,0x192,0x1a0,0x4,0x182,0x192,0x180,
    0x4,0x182,0x192,0x180,0x4,0x182,0x192,0x180,
    0x4,0x182,0x192,0x180,0x4,0x182,0x192,0x180,
    0x4,0x182,0x192,0x180,0x4,0x182,0x192,0x180,
    0x4,0x1db,0x19a,0x1d8,0x4,0x1db,0x19a,0x1d8,
    0x4,0x1db,0x19a,0x1d8,0x4,0x1db,0x19a,0x1d8,
    0x4,0x1db,0x19a,0x1d8,0x4,0x1db,0x19a,0x1d8,
    0x4,0x1db,0x19a,0x1d8,0x4,0x1db,0x19a,0x1d8,
    0x24,0x1db,0x19a,0x1f8,0x4,0x1db,0x19a,0x1d8,
    0x4,0x1db,0x19a,0x1d8,0x4,0x1db,0x19a,0x1d8,
    0x4,0x1db,0x19a,0x1d8,0x4,0x1db,0x19a,0x1d8,
    0x4,0x1db,0x19a,0x1d8,0x4,0x1db,0x19a,0x1d8};
const uint8_t lut6[256] = {0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0x10,0x0,0x0,0x0,0x14,0x4,0x4,0x4,
    0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0xd6,0xc0,0x0,0xc6,0xd6,0xc4,0x4,0xc6,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0x18,0xb8,0x0,0xbd,0x1c,0xbc,0x4,0xbd,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff,
    0xde,0xf8,0x0,0xff,0xde,0xfc,0x4,0xff,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = (apValues & 255);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = (uvwState5>0?4:0) | (uvwState6>0?8:0) | (uvwState14>0?64:0) | (uvwState13>0?128:0) | (uvwState8 & 1) | (lut0output & 2) | (apValues & 48);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = (uvwState18>0?2:0) | (uvwState20>0?8:0) | (uvwState21>0?16:0) | ((apValues & 256)>0?32:0) | (uvwState19>0?128:0) | (lut0output & 69);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = (uvwState7>0?4:0) | (uvwState8>0?8:0) | (uvwState15>0?16:0) | (uvwState16>0?32:0) | (lut2output & 1) | (lut1output & 2) | (apValues & 192);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = (uvwState11>0?16:0) | (uvwState12>0?32:0) | (uvwState4>0?64:0) | (uvwState3>0?128:0) | (lut1output & 1) | (lut3output & 2) | (apValues & 12);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = (uvwState9>0?64:0) | (uvwState10>0?128:0) | (apValues & 3) | (lut3output & 4) | (lut1output & 24) | (lut4output & 32);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = (uvwState2>0?64:0) | (uvwState1>0?128:0) | (apValues & 3) | (lut1output & 4) | (lut4output & 24) | (lut5output & 32);
  uint32_t lut6output = lut6[lut6input];
  if ((lut0output & 8)) {
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 1)) {
        buf.b0p0 = buf.b1p0 | (apValues << 18) | (0 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 2)) {
        buf.b0p0 = buf.b2p0 | (apValues << 18) | (1 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 8)) {
        buf.b0p0 = buf.b3p0 | (apValues << 18) | (2 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 16)) {
        buf.b0p0 = buf.b4p0 | (apValues << 18) | (3 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 4)) {
        buf.b0p0 = buf.b5p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 8)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 4)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 16)) {
        buf.b0p0 = buf.b8p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 1)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 2)) {
        buf.b0p0 = buf.b10p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 1)) {
        buf.b0p0 = buf.b11p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 2)) {
        buf.b0p0 = buf.b12p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 1)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 2)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 1)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 8)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 16)) {
        buf.b0p0 = b17p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 2)) {
        buf.b0p0 = buf.b18p0 | (apValues << 18) | (17 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 4)) {
        buf.b0p0 = buf.b19p0 | (apValues << 18) | (18 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 8)) {
        buf.b0p0 = b20p0 | (apValues << 18) | (19 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 16)) {
        buf.b0p0 = b21p0 | (apValues << 18) | (20 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  if ((lut6output & 8)) {
  } else if ((lut5output & 4)) {
        buf.b1p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 32)) {
        buf.b2p0 = buf.b1p0 | (apValues << 9);
  } else if ((lut6output & 64)) {
  }
  if ((lut4output & 4)) {
  } else if ((lut4output & 64)) {
        buf.b3p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 256)) {
        buf.b4p0 = buf.b3p0 | (apValues << 9);
  } else if ((lut4output & 512)) {
  }
  if ((lut1output & 32)) {
  } else if ((lut1output & 64)) {
        buf.b5p0 = b17p0 | (apValues << 0);
  }
  if ((lut1output & 256)) {
        buf.b6p0 = buf.b5p0 | (apValues << 9);
  } else if ((lut1output & 512)) {
  }
  if ((lut3output & 16)) {
  } else if ((lut0output & 32)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut3output & 64)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut3output & 128)) {
  }
  if ((lut5output & 8)) {
  } else if ((lut0output & 64)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut5output & 64)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut5output & 128)) {
  }
  if ((lut4output & 2048)) {
  } else if ((lut0output & 128)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 8192)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut4output & 16384)) {
  }
  if ((lut1output & 2048)) {
  } else if ((lut0output & 256)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut1output & 8192)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut1output & 16384)) {
  }
  if ((lut3output & 512)) {
  } else if ((lut0output & 512)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut3output & 2048)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut3output & 4096)) {
  }
  if ((lut0output & 1024)) {
  }
  if ((lut2output & 32)) {
        buf.b18p0 = b17p0 | (apValues << 0);
  }
  if ((lut2output & 128)) {
  } else if ((lut2output & 256)) {
        buf.b19p0 = b20p0 | (apValues << 0) | (0 << 9);
  } else if ((lut2output & 512)) {
        buf.b19p0 = b21p0 | (apValues << 0) | (1 << 9);
  }
  if ((lut2output & 2048)) {
  }
  if ((lut2output & 8192)) {
  }
  uvwState0 = (lut6output & 4);
  uvwState1 = (lut6output & 16);
  uvwState2 = (lut6output & 128);
  uvwState3 = (lut4output & 128);
  uvwState4 = (lut4output & 1024);
  uvwState5 = (lut1output & 128);
  uvwState6 = (lut1output & 1024);
  uvwState7 = (lut3output & 32);
  uvwState8 = (lut3output & 256);
  uvwState9 = (lut5output & 16);
  uvwState10 = (lut5output & 256);
  uvwState11 = (lut4output & 4096);
  uvwState12 = (lut4output & 32768);
  uvwState13 = (lut1output & 4096);
  uvwState14 = (lut1output & 32768);
  uvwState15 = (lut3output & 1024);
  uvwState16 = (lut3output & 8192);
  uvwState17 = (lut0output & 2048);
  uvwState18 = (lut2output & 64);
  uvwState19 = (lut2output & 1024);
  uvwState20 = (lut2output & 4096);
  uvwState21 = (lut2output & 16384);
}

#endif
/* Decoding information for the buffers:
   -------------------------------------

 - UVW state 0 with LTL subformula (Polish notation):
    Bits 0 to 17: previous buffer
    Bits 18 to 26: propositions
    Bits 27 to 31: incoming transition
       -> Value 0 for transition from UVW state 1
       -> Value 1 for transition from UVW state 2
       -> Value 2 for transition from UVW state 3
       -> Value 3 for transition from UVW state 4
       -> Value 4 for transition from UVW state 5
       -> Value 5 for transition from UVW state 6
       -> Value 6 for transition from UVW state 7
       -> Value 7 for transition from UVW state 8
       -> Value 8 for transition from UVW state 9
       -> Value 9 for transition from UVW state 10
       -> Value 10 for transition from UVW state 11
       -> Value 11 for transition from UVW state 12
       -> Value 12 for transition from UVW state 13
       -> Value 13 for transition from UVW state 14
       -> Value 14 for transition from UVW state 15
       -> Value 15 for transition from UVW state 16
       -> Value 16 for transition from UVW state 17
       -> Value 17 for transition from UVW state 18
       -> Value 18 for transition from UVW state 19
       -> Value 19 for transition from UVW state 20
       -> Value 20 for transition from UVW state 21
 - UVW state 1 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 2 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 3 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 4 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 5 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 6 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 7 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 8 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 9 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 10 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 11 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 12 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 13 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 14 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 15 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 16 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 17 with LTL subformula (Polish notation):
    Initial state only
 - UVW state 18 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 19 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
    Bits 9 to 9: incoming transition
       -> Value 0 for transition from UVW state 20
       -> Value 1 for transition from UVW state 21
 - UVW state 20 with LTL subformula (Polish notation):
    Initial state only
 - UVW state 21 with LTL subformula (Polish notation):
    Initial state only


UVW on which the monitor is based:
 UVW with 22 states and initial states [17, 20, 21]:
 - State No. 0 with name reject (rej.):
   - t.t.s. 0 for TRUE
 - State No. 1 with name || reject R & ! a1 a2 | | & ! a1 ! a2 & ! a1 a2 & & a1 ! a2 R & ! a1 a2 | & ! a1 a2 & a1 ! a2:
   - t.t.s. 1 for ite(a1, TRUE, (~ a2))
   - t.t.s. 0 for ite(a1, a2, FALSE)
   - t.t.s. 2 for a1
 - State No. 2 with name || reject || reject || reject || reject R & ! a1 a2 | & ! a1 a2 & a1 ! a2:
   - t.t.s. 2 for ite(a1, TRUE, (~ a2))
   - t.t.s. 0 for ite(a1, a2, (~ a2))
 - State No. 3 with name || reject R & ! b1 b2 | | & ! b1 ! b2 & ! b1 b2 & & b1 ! b2 R & ! b1 b2 | & ! b1 b2 & b1 ! b2:
   - t.t.s. 3 for ite(b1, TRUE, (~ b2))
   - t.t.s. 0 for ite(b1, b2, FALSE)
   - t.t.s. 4 for b1
 - State No. 4 with name || reject || reject || reject || reject R & ! b1 b2 | & ! b1 b2 & b1 ! b2:
   - t.t.s. 4 for ite(b1, TRUE, (~ b2))
   - t.t.s. 0 for ite(b1, b2, (~ b2))
 - State No. 5 with name || reject R & ! c1 c2 | | & ! c1 ! c2 & ! c1 c2 & & c1 ! c2 R & ! c1 c2 | & ! c1 c2 & c1 ! c2:
   - t.t.s. 5 for ite(c1, TRUE, (~ c2))
   - t.t.s. 0 for ite(c1, c2, FALSE)
   - t.t.s. 6 for c1
 - State No. 6 with name || reject || reject || reject || reject R & ! c1 c2 | & ! c1 c2 & c1 ! c2:
   - t.t.s. 6 for ite(c1, TRUE, (~ c2))
   - t.t.s. 0 for ite(c1, c2, (~ c2))
 - State No. 7 with name || reject R & ! d1 d2 | | & ! d1 ! d2 & ! d1 d2 & & d1 ! d2 R & ! d1 d2 | & ! d1 d2 & d1 ! d2:
   - t.t.s. 7 for ite(d1, TRUE, (~ d2))
   - t.t.s. 0 for ite(d1, d2, FALSE)
   - t.t.s. 8 for d1
 - State No. 8 with name || reject || reject || reject || reject R & ! d1 d2 | & ! d1 d2 & d1 ! d2:
   - t.t.s. 8 for ite(d1, TRUE, (~ d2))
   - t.t.s. 0 for ite(d1, d2, (~ d2))
 - State No. 9 with name || reject R & ! a1 ! a2 | | & ! a1 a2 & ! a1 ! a2 & & a1 a2 R & ! a1 ! a2 | & ! a1 ! a2 & a1 a2:
   - t.t.s. 9 for ite(a1, TRUE, a2)
   - t.t.s. 0 for (~ ite(a1, a2, TRUE))
   - t.t.s. 10 for a1
 - State No. 10 with name || reject || reject || reject || reject R & ! a1 ! a2 | & ! a1 ! a2 & a1 a2:
   - t.t.s. 10 for ite(a1, TRUE, a2)
   - t.t.s. 0 for (~ ite(a1, a2, (~ a2)))
 - State No. 11 with name || reject R & ! b1 ! b2 | | & ! b1 b2 & ! b1 ! b2 & & b1 b2 R & ! b1 ! b2 | & ! b1 ! b2 & b1 b2:
   - t.t.s. 11 for ite(b1, TRUE, b2)
   - t.t.s. 0 for (~ ite(b1, b2, TRUE))
   - t.t.s. 12 for b1
 - State No. 12 with name || reject || reject || reject || reject R & ! b1 ! b2 | & ! b1 ! b2 & b1 b2:
   - t.t.s. 12 for ite(b1, TRUE, b2)
   - t.t.s. 0 for (~ ite(b1, b2, (~ b2)))
 - State No. 13 with name || reject R & ! c1 ! c2 | | & ! c1 c2 & ! c1 ! c2 & & c1 c2 R & ! c1 ! c2 | & ! c1 ! c2 & c1 c2:
   - t.t.s. 13 for ite(c1, TRUE, c2)
   - t.t.s. 0 for (~ ite(c1, c2, TRUE))
   - t.t.s. 14 for c1
 - State No. 14 with name || reject || reject || reject || reject R & ! c1 ! c2 | & ! c1 ! c2 & c1 c2:
   - t.t.s. 14 for ite(c1, TRUE, c2)
   - t.t.s. 0 for (~ ite(c1, c2, (~ c2)))
 - State No. 15 with name || reject R & ! d1 ! d2 | | & ! d1 d2 & ! d1 ! d2 & & d1 d2 R & ! d1 ! d2 | & ! d1 ! d2 & d1 d2:
   - t.t.s. 15 for ite(d1, TRUE, d2)
   - t.t.s. 0 for (~ ite(d1, d2, TRUE))
   - t.t.s. 16 for d1
 - State No. 16 with name || reject || reject || reject || reject R & ! d1 ! d2 | & ! d1 ! d2 & d1 d2:
   - t.t.s. 16 for ite(d1, TRUE, d2)
   - t.t.s. 0 for (~ ite(d1, d2, (~ d2)))
 - State No. 17 with name & & & & & & & & & & & & & & & & & & G | | d1 ! d2 R & ! d1 ! d2 | | & ! d1 d2 & ! d1 ! d2 & & d1 d2 R & ! d1 ! d2 | & ! d1 ! d2 & d1 d2 & G | | c1 ! c2 R & ! c1 ! c2 | | & ! c1 c2 & ! c1 ! c2 & & c1 c2 R & ! c1 ! c2 | & ! c1 ! c2 & c1 c2 & G | | b1 ! b2 R & ! b1 ! b2 | | & ! b1 b2 & ! b1 ! b2 & & b1 b2 R & ! b1 ! b2 | & ! b1 ! b2 & b1 b2 & G | | a1 ! a2 R & ! a1 ! a2 | | & ! a1 a2 & ! a1 ! a2 & & a1 a2 R & ! a1 ! a2 | & ! a1 ! a2 & a1 a2 & G | | d1 d2 R & ! d1 d2 | | & ! d1 ! d2 & ! d1 d2 & & d1 ! d2 R & ! d1 d2 | & ! d1 d2 & d1 ! d2 & G | | c1 c2 R & ! c1 c2 | | & ! c1 ! c2 & ! c1 c2 & & c1 ! c2 R & ! c1 c2 | & ! c1 c2 & c1 ! c2 & G | | b1 b2 R & ! b1 b2 | | & ! b1 ! b2 & ! b1 b2 & & b1 ! b2 R & ! b1 b2 | & ! b1 b2 & b1 ! b2 G | | a1 a2 R & ! a1 a2 | | & ! a1 ! a2 & ! a1 a2 & & a1 ! a2 R & ! a1 a2 | & ! a1 a2 & a1 ! a2 G | | a1 ! a2 | b1 ! b2 G | | a1 ! a2 | d1 ! d2 G | | b1 ! b2 | a1 ! a2 G | | b1 ! b2 | c1 ! c2 G | | c1 ! c2 | b1 ! b2 G | | c1 ! c2 | d1 ! d2 G | | d1 ! d2 | a1 ! a2 G | | d1 ! d2 | c1 ! c2 G | | ! a1 a2 | ! b1 b2 G | | ! a1 a2 | ! d1 d2 G | | ! b1 b2 | ! a1 a2 G | | ! b1 b2 | ! c1 c2 G | | ! c1 c2 | ! b1 b2 G | | ! c1 c2 | ! d1 d2 G | | ! d1 d2 | ! a1 a2 G | | ! d1 d2 | ! c1 c2 G | | | a1 ! a2 ! m X | ! m & ! a1 a2:
   - t.t.s. 15 for (~ ite(d1, TRUE, (~ d2)))
   - t.t.s. 17 for TRUE
   - t.t.s. 13 for (~ ite(c1, TRUE, (~ c2)))
   - t.t.s. 11 for (~ ite(b1, TRUE, (~ b2)))
   - t.t.s. 9 for (~ ite(a1, TRUE, (~ a2)))
   - t.t.s. 7 for (~ ite(d1, TRUE, d2))
   - t.t.s. 5 for (~ ite(c1, TRUE, c2))
   - t.t.s. 3 for (~ ite(b1, TRUE, b2))
   - t.t.s. 1 for (~ ite(a1, TRUE, a2))
   - t.t.s. 0 for (~ ite(a1, ite(a2, ite(b1, ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)), ite(c1, c2, ite(c2, ite(d1, TRUE, (~ d2)), TRUE))), ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), (~ c2)), ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)))), ite(b1, ite(b2, ite(c1, ite(d1, d2, TRUE), ite(c2, ite(d1, d2, (~ d2)), ite(d1, d2, TRUE))), FALSE), ite(b2, ite(c1, ite(d1, d2, TRUE), (~ ite(c2, TRUE, (~ ite(d1, d2, TRUE))))), ite(c1, ite(d1, d2, TRUE), ite(c2, ite(d1, d2, (~ d2)), ite(d1, d2, TRUE)))))), ite(a2, ite(b1, ite(b2, ite(c1, ite(c2, ite(d1, TRUE, (~ d2)), ite(d1, d2, (~ d2))), ite(d1, TRUE, (~ d2))), ite(c1, ite(c2, ite(d1, TRUE, (~ d2)), FALSE), ite(d1, TRUE, (~ d2)))), (~ ite(b2, TRUE, (~ ite(c1, ite(c2, ite(d1, TRUE, (~ d2)), ite(d1, d2, (~ d2))), ite(d1, TRUE, (~ d2))))))), ite(b1, ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)), ite(c1, c2, ite(c2, ite(d1, TRUE, (~ d2)), TRUE))), ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), (~ c2)), ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)))))))
   - t.t.s. 18 for (~ ite(a1, TRUE, (~ ite(a2, m, FALSE))))
 - State No. 18 with name || reject | ! m & ! a1 a2:
   - t.t.s. 0 for ite(a1, m, (~ ite(a2, TRUE, (~ m))))
 - State No. 19 with name || reject R & ! a1 a2 | & & | a2 m | ! a1 m | ! a1 a2 X 0:
   - t.t.s. 19 for ite(a1, TRUE, (~ a2))
   - t.t.s. 0 for (~ ite(a1, ite(a2, m, FALSE), ite(a2, TRUE, m)))
 - State No. 20 with name & R & a1 ! a2 | | | ! a1 a2 ! m X R & ! a1 a2 | & & | a2 m | ! a1 m | ! a1 a2 X 0 R & a1 ! a2 | & | a1 ! m | ! a2 ! m X 0:
   - t.t.s. 20 for ite(a1, a2, TRUE)
   - t.t.s. 19 for (~ ite(a1, ite(a2, TRUE, (~ m)), TRUE))
   - t.t.s. 0 for ite(a1, ite(a2, m, FALSE), m)
 - State No. 21 with name & R & ! a1 a2 | | | ! a1 a2 ! m X R & ! a1 a2 | & & | a2 m | ! a1 m | ! a1 a2 X 0 R & ! a1 a2 | & | | a1 a2 ! m | | ! a1 ! a2 ! m X 0:
   - t.t.s. 21 for ite(a1, TRUE, (~ a2))
   - t.t.s. 19 for (~ ite(a1, ite(a2, TRUE, (~ m)), TRUE))
   - t.t.s. 0 for ite(a1, ite(a2, m, FALSE), (~ ite(a2, TRUE, (~ m))))

*/

/* Lookup-Table contents:
- LUT 0 has:
  -> Inputs a1 a2 b1 b2 c1 c2 d1 d2
  -> Outputs new_n34 new_n54 new_n77 uvwState0incoming0 uvwState0incoming17 uvwState7incoming1 uvwState9incoming1 uvwState11incoming1 uvwState13incoming1 uvwState15incoming1 uvwState17incoming0 uvwState17Next
- LUT 1 has:
  -> Inputs uvwState8 new_n54 uvwState5 uvwState6 c1 c2 uvwState14 uvwState13
  -> Outputs uvwState0incoming13 uvwState0incoming14 uvwState0incoming5 uvwState0incoming6 uvwState0incoming8 uvwState5incoming0 uvwState5incoming1 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next uvwState13incoming0 uvwState13Next uvwState14incoming0 uvwState14incoming1 uvwState14Next
- LUT 2 has:
  -> Inputs new_n34 uvwState18 new_n77 uvwState20 uvwState21 m uvwState9incoming1 uvwState19
  -> Outputs new_n90 uvwState0incoming18 uvwState0incoming19 uvwState0incoming20 uvwState0incoming21 uvwState18incoming0 uvwState18Next uvwState19incoming0 uvwState19incoming1 uvwState19incoming2 uvwState19Next uvwState20incoming0 uvwState20Next uvwState21incoming0 uvwState21Next
- LUT 3 has:
  -> Inputs new_n90 uvwState0incoming14 uvwState7 uvwState8 uvwState15 uvwState16 d1 d2
  -> Outputs uvwState0incoming15 new_n93 uvwState0incoming7 uvwState0incoming16 uvwState7incoming0 uvwState7Next uvwState8incoming0 uvwState8incoming1 uvwState8Next uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 4 has:
  -> Inputs uvwState0incoming13 new_n93 b1 b2 uvwState11 uvwState12 uvwState4 uvwState3
  -> Outputs uvwState0incoming11 uvwState0incoming12 uvwState3incoming0 uvwState0incoming3 uvwState0incoming4 new_n96 uvwState3incoming1 uvwState3Next uvwState4incoming0 uvwState4incoming1 uvwState4Next uvwState11incoming0 uvwState11Next uvwState12incoming0 uvwState12incoming1 uvwState12Next
- LUT 5 has:
  -> Inputs a1 a2 uvwState0incoming7 uvwState0incoming6 uvwState0incoming8 new_n96 uvwState9 uvwState10
  -> Outputs uvwState0incoming9 uvwState0incoming10 uvwState1incoming1 uvwState9incoming0 uvwState9Next new_n101 uvwState10incoming0 uvwState10incoming1 uvwState10Next
- LUT 6 has:
  -> Inputs a1 a2 uvwState0incoming5 uvwState0incoming3 uvwState0incoming4 new_n101 uvwState2 uvwState1
  -> Outputs uvwState0incoming1 uvwState0incoming2 uvwState0Next uvwState1incoming0 uvwState1Next uvwState2incoming0 uvwState2incoming1 uvwState2Next
*/
