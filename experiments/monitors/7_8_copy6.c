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

const uint16_t lut0[256] = {0x309,0x301,0x311,0x301,0x309,0x304,0x311,0x301,
    0x329,0x321,0x334,0x321,0x309,0x301,0x311,0x301,
    0x309,0x301,0x311,0x301,0x30c,0x304,0x314,0x304,
    0x329,0x321,0x334,0x321,0x309,0x301,0x311,0x301,
    0x349,0x341,0x351,0x341,0x349,0x344,0x351,0x341,
    0x36c,0x364,0x374,0x364,0x349,0x341,0x351,0x341,
    0x309,0x301,0x311,0x301,0x309,0x304,0x311,0x301,
    0x329,0x321,0x334,0x321,0x309,0x301,0x311,0x301,
    0x309,0x304,0x311,0x301,0x309,0x304,0x311,0x301,
    0x329,0x324,0x334,0x321,0x309,0x304,0x311,0x301,
    0x30c,0x304,0x314,0x304,0x30c,0x304,0x314,0x304,
    0x32c,0x324,0x334,0x324,0x30c,0x304,0x314,0x304,
    0x349,0x344,0x351,0x341,0x349,0x344,0x351,0x341,
    0x36c,0x364,0x374,0x364,0x349,0x344,0x351,0x341,
    0x309,0x304,0x311,0x301,0x309,0x304,0x311,0x301,
    0x329,0x324,0x334,0x321,0x309,0x304,0x311,0x301,
    0x389,0x381,0x394,0x381,0x389,0x384,0x394,0x381,
    0x3a9,0x3a1,0x3b4,0x3a1,0x389,0x381,0x394,0x381,
    0x389,0x381,0x394,0x381,0x38c,0x384,0x394,0x384,
    0x3a9,0x3a1,0x3b4,0x3a1,0x389,0x381,0x394,0x381,
    0x3cc,0x3c4,0x3d4,0x3c4,0x3cc,0x3c4,0x3d4,0x3c4,
    0x3ec,0x3e4,0x3f4,0x3e4,0x3cc,0x3c4,0x3d4,0x3c4,
    0x389,0x381,0x394,0x381,0x389,0x384,0x394,0x381,
    0x3a9,0x3a1,0x3b4,0x3a1,0x389,0x381,0x394,0x381,
    0x309,0x301,0x311,0x301,0x309,0x304,0x311,0x301,
    0x329,0x321,0x334,0x321,0x309,0x301,0x311,0x301,
    0x309,0x301,0x311,0x301,0x30c,0x304,0x314,0x304,
    0x329,0x321,0x334,0x321,0x309,0x301,0x311,0x301,
    0x349,0x341,0x351,0x341,0x349,0x344,0x351,0x341,
    0x36c,0x364,0x374,0x364,0x349,0x341,0x351,0x341,
    0x309,0x301,0x311,0x301,0x309,0x304,0x311,0x301,
    0x329,0x321,0x334,0x321,0x309,0x301,0x311,0x301};
const uint32_t lut1[256] = {0x42,0x2,0x2,0x2,0x42,0x2,0x302,0x2,
    0x62,0xe2,0x2,0xe2,0x62,0xe2,0x302,0xe2,
    0x42,0x2,0x2,0x2,0x41,0x1,0x302,0x1,
    0x62,0xe2,0x2,0xe2,0x61,0xe1,0x302,0xe1,
    0x2444,0x2404,0x2,0x2404,0x2442,0x2404,0x302,0x2402,
    0x2464,0x24e4,0x2,0x24e4,0x2462,0x24e4,0x302,0x24e2,
    0x2444,0x2404,0x2,0x2404,0x2441,0x2405,0x302,0x2401,
    0x2464,0x24e4,0x2,0x24e4,0x2461,0x24e5,0x302,0x24e1,
    0xc042,0x2,0xc002,0xc002,0xc048,0x2802,0xc308,0xc008,
    0xc062,0xe2,0xc002,0xc0e2,0xc068,0x28e2,0xc308,0xc0e8,
    0xc042,0x2,0xc002,0xc002,0xc049,0x2801,0xc308,0xc009,
    0xc062,0xe2,0xc002,0xc0e2,0xc069,0x28e1,0xc308,0xc0e9,
    0xe444,0x2404,0xc002,0xe404,0xe448,0x2c04,0xc308,0xe408,
    0xe464,0x24e4,0xc002,0xe4e4,0xe468,0x2ce4,0xc308,0xe4e8,
    0xe444,0x2404,0xc002,0xe404,0xe449,0x2c05,0xc308,0xe409,
    0xe464,0x24e4,0xc002,0xe4e4,0xe469,0x2ce5,0xc308,0xe4e9,
    0x30042,0x30002,0x2,0x30002,0x30050,0x33002,0x302,0x30010,
    0x30062,0x300e2,0x2,0x300e2,0x30070,0x330e2,0x302,0x300f0,
    0x30042,0x30002,0x2,0x30002,0x30051,0x33001,0x302,0x30011,
    0x30062,0x300e2,0x2,0x300e2,0x30071,0x330e1,0x302,0x300f1,
    0x32444,0x32404,0x2,0x32404,0x32450,0x33404,0x302,0x32410,
    0x32464,0x324e4,0x2,0x324e4,0x32470,0x334e4,0x302,0x324f0,
    0x32444,0x32404,0x2,0x32404,0x32451,0x33405,0x302,0x32411,
    0x32464,0x324e4,0x2,0x324e4,0x32471,0x334e5,0x302,0x324f1,
    0x3c042,0x30002,0xc002,0x3c002,0x3c058,0x33802,0xc308,0x3c018,
    0x3c062,0x300e2,0xc002,0x3c0e2,0x3c078,0x338e2,0xc308,0x3c0f8,
    0x3c042,0x30002,0xc002,0x3c002,0x3c059,0x33801,0xc308,0x3c019,
    0x3c062,0x300e2,0xc002,0x3c0e2,0x3c079,0x338e1,0xc308,0x3c0f9,
    0x3e444,0x32404,0xc002,0x3e404,0x3e458,0x33c04,0xc308,0x3e418,
    0x3e464,0x324e4,0xc002,0x3e4e4,0x3e478,0x33ce4,0xc308,0x3e4f8,
    0x3e444,0x32404,0xc002,0x3e404,0x3e459,0x33c05,0xc308,0x3e419,
    0x3e464,0x324e4,0xc002,0x3e4e4,0x3e479,0x33ce5,0xc308,0x3e4f9};
const uint16_t lut2[256] = {0xc0,0xc0,0xc0,0xc1,0xe0,0xe0,0xe0,0xe1,
    0x6c8,0x6c8,0x6c8,0x6c9,0x6e8,0x6e8,0x6e8,0x6e9,
    0xc0,0xc0,0xc0,0xc1,0xe0,0xe0,0xe0,0xe1,
    0x6c8,0x6c8,0x6c8,0x6c9,0x6e8,0x6e8,0x6e8,0x6e9,
    0xc0,0xc0,0xc0,0xc1,0xe0,0xe0,0xe0,0xe1,
    0x6c8,0x6c8,0x6c8,0x6c9,0x6e8,0x6e8,0x6e8,0x6e9,
    0xc0,0xc0,0xc0,0xc1,0xe0,0xe0,0xe0,0xe1,
    0x6c8,0x6c8,0x6c8,0x6c9,0x6e8,0x6e8,0x6e8,0x6e9,
    0x0,0x0,0x0,0x1,0x5a0,0x5a0,0x5a0,0x5a1,
    0x600,0x600,0x600,0x601,0x7a0,0x7a0,0x7a0,0x7a1,
    0xb802,0xb802,0xb802,0xb802,0xbda2,0xbda2,0xbda2,0xbda2,
    0xbe02,0xbe02,0xbe02,0xbe02,0xbfa2,0xbfa2,0xbfa2,0xbfa2,
    0xc010,0xc010,0xc010,0xc010,0xc5b0,0xc5b0,0xc5b0,0xc5b0,
    0xc610,0xc610,0xc610,0xc610,0xc7b0,0xc7b0,0xc7b0,0xc7b0,
    0xf812,0xf812,0xf812,0xf812,0xfdb2,0xfdb2,0xfdb2,0xfdb2,
    0xfe12,0xfe12,0xfe12,0xfe12,0xffb2,0xffb2,0xffb2,0xffb2,
    0x1000,0x1000,0x1000,0x1001,0x1000,0x1000,0x1000,0x1001,
    0x1000,0x1000,0x1000,0x1001,0x1000,0x1000,0x1000,0x1001,
    0x1800,0x1800,0x1800,0x1801,0x1800,0x1800,0x1800,0x1801,
    0x1800,0x1800,0x1800,0x1801,0x1800,0x1800,0x1800,0x1801,
    0xd010,0xd010,0xd010,0xd010,0xd010,0xd010,0xd010,0xd010,
    0xd010,0xd010,0xd010,0xd010,0xd010,0xd010,0xd010,0xd010,
    0xd810,0xd810,0xd810,0xd810,0xd810,0xd810,0xd810,0xd810,
    0xd810,0xd810,0xd810,0xd810,0xd810,0xd810,0xd810,0xd810,
    0x0,0x0,0x0,0x1,0x5a4,0x5a4,0x5a4,0x5a5,
    0x608,0x608,0x608,0x609,0x7ac,0x7ac,0x7ac,0x7ad,
    0xb800,0xb800,0xb800,0xb801,0xbda4,0xbda4,0xbda4,0xbda5,
    0xbe08,0xbe08,0xbe08,0xbe09,0xbfac,0xbfac,0xbfac,0xbfad,
    0xc000,0xc000,0xc000,0xc001,0xc5a4,0xc5a4,0xc5a4,0xc5a5,
    0xc608,0xc608,0xc608,0xc609,0xc7ac,0xc7ac,0xc7ac,0xc7ad,
    0xf800,0xf800,0xf800,0xf801,0xfda4,0xfda4,0xfda4,0xfda5,
    0xfe08,0xfe08,0xfe08,0xfe09,0xffac,0xffac,0xffac,0xffad};
const uint16_t lut3[128] = {0xc0,0xc1,0xc0,0xc1,0xe0,0xe1,0xe0,0xe1,
    0x6d0,0x6d1,0x6d0,0x6d1,0x6f0,0x6f1,0x6f0,0x6f1,
    0x0,0x1,0xc008,0xc008,0x5a0,0x5a1,0xc5a8,0xc5a8,
    0x600,0x601,0xc608,0xc608,0x7a0,0x7a1,0xc7a8,0xc7a8,
    0x1000,0x1001,0xd008,0xd008,0x1000,0x1001,0xd008,0xd008,
    0x1000,0x1001,0xd008,0xd008,0x1000,0x1001,0xd008,0xd008,
    0x0,0x1,0xc000,0xc001,0x5a4,0x5a5,0xc5a4,0xc5a5,
    0x610,0x611,0xc610,0xc611,0x7b4,0x7b5,0xc7b4,0xc7b5,
    0xc0,0xc1,0xc0,0xc1,0xe0,0xe1,0xe0,0xe1,
    0x6d0,0x6d1,0x6d0,0x6d1,0x6f0,0x6f1,0x6f0,0x6f1,
    0xb802,0xb802,0xf80a,0xf80a,0xbda2,0xbda2,0xfdaa,0xfdaa,
    0xbe02,0xbe02,0xfe0a,0xfe0a,0xbfa2,0xbfa2,0xffaa,0xffaa,
    0x1800,0x1801,0xd808,0xd808,0x1800,0x1801,0xd808,0xd808,
    0x1800,0x1801,0xd808,0xd808,0x1800,0x1801,0xd808,0xd808,
    0xb800,0xb801,0xf800,0xf801,0xbda4,0xbda5,0xfda4,0xfda5,
    0xbe10,0xbe11,0xfe10,0xfe11,0xbfb4,0xbfb5,0xffb4,0xffb5};
const uint16_t lut4[128] = {0xc0,0xe0,0x6d0,0x6f0,0x0,0x20,0x600,0x620,
    0x1000,0x1020,0x1000,0x1020,0x0,0x20,0x610,0x630,
    0xc0,0xe0,0x6d0,0x6f0,0xb801,0xb801,0xbe01,0xbe01,
    0x1800,0x1820,0x1800,0x1820,0xb800,0xb820,0xbe10,0xbe30,
    0xc0,0xe0,0x6d0,0x6f0,0xc002,0xc002,0xc602,0xc602,
    0xd002,0xd002,0xd002,0xd002,0xc000,0xc020,0xc610,0xc630,
    0xc0,0xe0,0x6d0,0x6f0,0xf803,0xf803,0xfe03,0xfe03,
    0xd802,0xd802,0xd802,0xd802,0xf800,0xf820,0xfe10,0xfe30,
    0xc4,0xe4,0x6d4,0x6f4,0x584,0x5a4,0x784,0x7a4,
    0x1000,0x1020,0x1000,0x1020,0x58c,0x5ac,0x79c,0x7bc,
    0xc4,0xe4,0x6d4,0x6f4,0xbd85,0xbd85,0xbf85,0xbf85,
    0x1800,0x1820,0x1800,0x1820,0xbd8c,0xbdac,0xbf9c,0xbfbc,
    0xc4,0xe4,0x6d4,0x6f4,0xc586,0xc586,0xc786,0xc786,
    0xd002,0xd002,0xd002,0xd002,0xc58c,0xc5ac,0xc79c,0xc7bc,
    0xc4,0xe4,0x6d4,0x6f4,0xfd87,0xfd87,0xff87,0xff87,
    0xd802,0xd802,0xd802,0xd802,0xfd8c,0xfdac,0xff9c,0xffbc};
const uint8_t lut5[256] = {0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x20,0x20,0x28,0x20,0x0,0x0,0x8,0x0,
    0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x20,0x9d,0x2c,0xbc,0x0,0x9d,0xc,0x9c,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x20,0xc2,0xca,0xe0,0x0,0xc2,0xca,0xc0,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc,
    0x20,0xdf,0xce,0xfc,0x0,0xdf,0xce,0xdc,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc};
const uint8_t lut6[256] = {0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x0,0x0,0x0,0x0,0x4,0x4,0x4,0x4,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x1e,0x1c,0x4,0x1e,0x1e,0x1c,0x4,0x1e,
    0x1e,0x1c,0x4,0x1e,0x1e,0x1c,0x4,0x1e,
    0x1e,0x1c,0x4,0x1e,0x1e,0x1c,0x4,0x1e,
    0x1e,0x1c,0x4,0x1e,0x1e,0x1c,0x4,0x1e,
    0x1e,0x18,0x0,0x1e,0x1e,0x1c,0x4,0x1e,
    0x1e,0x1c,0x4,0x1e,0x1e,0x1c,0x4,0x1e,
    0x1e,0x1c,0x4,0x1e,0x1e,0x1c,0x4,0x1e,
    0x1e,0x1c,0x4,0x1e,0x1e,0x1c,0x4,0x1e,
    0x4,0x14,0x4,0x15,0x4,0x14,0x4,0x15,
    0x4,0x14,0x4,0x15,0x4,0x14,0x4,0x15,
    0x4,0x14,0x4,0x15,0x4,0x14,0x4,0x15,
    0x4,0x14,0x4,0x15,0x4,0x14,0x4,0x15,
    0x0,0x10,0x0,0x15,0x4,0x14,0x4,0x15,
    0x4,0x14,0x4,0x15,0x4,0x14,0x4,0x15,
    0x4,0x14,0x4,0x15,0x4,0x14,0x4,0x15,
    0x4,0x14,0x4,0x15,0x4,0x14,0x4,0x15,
    0x1e,0x1c,0x4,0x1f,0x1e,0x1c,0x4,0x1f,
    0x1e,0x1c,0x4,0x1f,0x1e,0x1c,0x4,0x1f,
    0x1e,0x1c,0x4,0x1f,0x1e,0x1c,0x4,0x1f,
    0x1e,0x1c,0x4,0x1f,0x1e,0x1c,0x4,0x1f,
    0x1e,0x18,0x0,0x1f,0x1e,0x1c,0x4,0x1f,
    0x1e,0x1c,0x4,0x1f,0x1e,0x1c,0x4,0x1f,
    0x1e,0x1c,0x4,0x1f,0x1e,0x1c,0x4,0x1f,
    0x1e,0x1c,0x4,0x1f,0x1e,0x1c,0x4,0x1f};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = (apValues & 255);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = ((apValues & 256)>0?4:0) | (uvwState1>0?8:0) | (uvwState18>0?16:0) | (uvwState19>0?32:0) | (uvwState20>0?64:0) | (uvwState21>0?128:0) | (apValues & 3);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = (uvwState7>0?4:0) | (uvwState8>0?8:0) | (uvwState15>0?16:0) | (uvwState16>0?32:0) | (lut0output & 1) | (lut1output & 2) | (apValues & 192);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = (uvwState14>0?2:0) | (uvwState5>0?4:0) | (uvwState6>0?8:0) | (uvwState13>0?64:0) | (lut2output & 1) | (apValues & 48);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = (uvwState4>0?2:0) | (uvwState11>0?16:0) | (uvwState12>0?32:0) | (uvwState3>0?64:0) | (lut3output & 1) | (apValues & 12);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = (uvwState9>0?64:0) | (uvwState10>0?128:0) | (apValues & 3) | (lut2output & 12) | (lut3output & 16) | (lut4output & 32);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = (uvwState2>0?64:0) | (uvwState1>0?128:0) | (apValues & 3) | (lut3output & 4) | (lut4output & 24) | (lut5output & 32);
  uint32_t lut6output = lut6[lut6input];
  if ((lut0output & 2)) {
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
  } else if ((lut3output & 4)) {
        buf.b0p0 = buf.b5p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 16)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 4)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 8)) {
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
  } else if ((lut3output & 2)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 8)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 2)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 16)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 4)) {
        buf.b0p0 = b17p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 1)) {
        buf.b0p0 = buf.b18p0 | (apValues << 18) | (17 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 4)) {
        buf.b0p0 = buf.b19p0 | (apValues << 18) | (18 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 8)) {
        buf.b0p0 = b20p0 | (apValues << 18) | (19 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 16)) {
        buf.b0p0 = b21p0 | (apValues << 18) | (20 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  if ((lut1output & 32)) {
  } else if ((lut0output & 8)) {
        buf.b1p0 = b17p0 | (apValues << 0);
  }
  if ((lut1output & 128)) {
        buf.b2p0 = buf.b1p0 | (apValues << 9);
  } else if ((lut6output & 8)) {
  }
  if ((lut4output & 4)) {
  } else if ((lut4output & 64)) {
        buf.b3p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 256)) {
        buf.b4p0 = buf.b3p0 | (apValues << 9);
  } else if ((lut4output & 512)) {
  }
  if ((lut3output & 32)) {
  } else if ((lut3output & 64)) {
        buf.b5p0 = b17p0 | (apValues << 0);
  }
  if ((lut3output & 256)) {
        buf.b6p0 = buf.b5p0 | (apValues << 9);
  } else if ((lut3output & 512)) {
  }
  if ((lut2output & 32)) {
  } else if ((lut2output & 64)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut2output & 256)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut2output & 512)) {
  }
  if ((lut5output & 4)) {
  } else if ((lut0output & 16)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut5output & 16)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut5output & 64)) {
  }
  if ((lut4output & 2048)) {
  } else if ((lut0output & 32)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 8192)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut4output & 16384)) {
  }
  if ((lut3output & 2048)) {
  } else if ((lut0output & 64)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut3output & 8192)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut3output & 16384)) {
  }
  if ((lut2output & 2048)) {
  } else if ((lut0output & 128)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut2output & 8192)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut2output & 16384)) {
  }
  if ((lut0output & 256)) {
  }
  if ((lut1output & 256)) {
        buf.b18p0 = b17p0 | (apValues << 0);
  }
  if ((lut1output & 1024)) {
  } else if ((lut1output & 2048)) {
        buf.b19p0 = b20p0 | (apValues << 0) | (0 << 9);
  } else if ((lut1output & 4096)) {
        buf.b19p0 = b21p0 | (apValues << 0) | (1 << 9);
  }
  if ((lut1output & 16384)) {
  }
  if ((lut1output & 65536)) {
  }
  uvwState0 = (lut6output & 4);
  uvwState1 = (lut1output & 64);
  uvwState2 = (lut6output & 16);
  uvwState3 = (lut4output & 128);
  uvwState4 = (lut4output & 1024);
  uvwState5 = (lut3output & 128);
  uvwState6 = (lut3output & 1024);
  uvwState7 = (lut2output & 128);
  uvwState8 = (lut2output & 1024);
  uvwState9 = (lut5output & 8);
  uvwState10 = (lut5output & 128);
  uvwState11 = (lut4output & 4096);
  uvwState12 = (lut4output & 32768);
  uvwState13 = (lut3output & 4096);
  uvwState14 = (lut3output & 32768);
  uvwState15 = (lut2output & 4096);
  uvwState16 = (lut2output & 32768);
  uvwState17 = (lut0output & 512);
  uvwState18 = (lut1output & 512);
  uvwState19 = (lut1output & 8192);
  uvwState20 = (lut1output & 32768);
  uvwState21 = (lut1output & 131072);
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
  -> Outputs new_n77 uvwState0incoming0 uvwState0incoming17 uvwState1incoming1 uvwState9incoming1 uvwState11incoming1 uvwState13incoming1 uvwState15incoming1 uvwState17incoming0 uvwState17Next
- LUT 1 has:
  -> Inputs a1 a2 m uvwState1 uvwState18 uvwState19 uvwState20 uvwState21
  -> Outputs uvwState0incoming18 new_n89 uvwState0incoming19 uvwState0incoming20 uvwState0incoming21 uvwState1incoming0 uvwState1Next uvwState2incoming0 uvwState18incoming0 uvwState18Next uvwState19incoming0 uvwState19incoming1 uvwState19incoming2 uvwState19Next uvwState20incoming0 uvwState20Next uvwState21incoming0 uvwState21Next
- LUT 2 has:
  -> Inputs new_n77 new_n89 uvwState7 uvwState8 uvwState15 uvwState16 d1 d2
  -> Outputs new_n92 uvwState0incoming15 uvwState0incoming7 uvwState0incoming8 uvwState0incoming16 uvwState7incoming0 uvwState7incoming1 uvwState7Next uvwState8incoming0 uvwState8incoming1 uvwState8Next uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 3 has:
  -> Inputs new_n92 uvwState14 uvwState5 uvwState6 c1 c2 uvwState13
  -> Outputs new_n94 uvwState0incoming13 uvwState0incoming5 uvwState0incoming14 uvwState0incoming6 uvwState5incoming0 uvwState5incoming1 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next uvwState13incoming0 uvwState13Next uvwState14incoming0 uvwState14incoming1 uvwState14Next
- LUT 4 has:
  -> Inputs new_n94 uvwState4 b1 b2 uvwState11 uvwState12 uvwState3
  -> Outputs uvwState0incoming11 uvwState0incoming12 uvwState3incoming0 uvwState0incoming3 uvwState0incoming4 new_n96 uvwState3incoming1 uvwState3Next uvwState4incoming0 uvwState4incoming1 uvwState4Next uvwState11incoming0 uvwState11Next uvwState12incoming0 uvwState12incoming1 uvwState12Next
- LUT 5 has:
  -> Inputs a1 a2 uvwState0incoming7 uvwState0incoming8 uvwState0incoming6 new_n96 uvwState9 uvwState10
  -> Outputs uvwState0incoming9 uvwState0incoming10 uvwState9incoming0 uvwState9Next uvwState10incoming0 new_n101 uvwState10incoming1 uvwState10Next
- LUT 6 has:
  -> Inputs a1 a2 uvwState0incoming5 uvwState0incoming3 uvwState0incoming4 new_n101 uvwState2 uvwState1
  -> Outputs uvwState0incoming1 uvwState0incoming2 uvwState0Next uvwState2incoming1 uvwState2Next
*/
