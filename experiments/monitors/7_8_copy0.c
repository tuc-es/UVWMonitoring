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

const uint32_t lut0[256] = {0x18102,0x18002,0x18c02,0x18002,0x18103,0x18003,0x78c02,0x18003,
    0x18102,0x1da0a,0x18e02,0x1da02,0x18103,0x1da0b,0x78e02,0x1da03,
    0x18102,0x1e012,0x1ec12,0x1e002,0x18103,0x1e013,0x7ec12,0x1e003,
    0x18102,0x1fa1a,0x1ee12,0x1fa02,0x18103,0x1fa1b,0x7ee12,0x1fa03,
    0x498120,0x498020,0x18c02,0x498020,0x498103,0x498021,0x78c02,0x498003,
    0x498120,0x49da28,0x18e02,0x49da20,0x498103,0x49da29,0x78e02,0x49da03,
    0x498120,0x49e030,0x1ec12,0x49e020,0x498103,0x49e031,0x7ec12,0x49e003,
    0x498120,0x49fa38,0x1ee12,0x49fa20,0x498103,0x49fa39,0x7ee12,0x49fa03,
    0x1818102,0x18002,0x1818c02,0x1818002,0x1818141,0x518003,0x1878c40,0x1818041,
    0x1818102,0x1da0a,0x1818e02,0x181da02,0x1818141,0x51da0b,0x1878e40,0x181da41,
    0x1818102,0x1e012,0x181ec12,0x181e002,0x1818141,0x51e013,0x187ec50,0x181e041,
    0x1818102,0x1fa1a,0x181ee12,0x181fa02,0x1818141,0x51fa1b,0x187ee50,0x181fa41,
    0x1c98120,0x498020,0x1818c02,0x1c98020,0x1c98141,0x598021,0x1878c40,0x1c98041,
    0x1c98120,0x49da28,0x1818e02,0x1c9da20,0x1c98141,0x59da29,0x1878e40,0x1c9da41,
    0x1c98120,0x49e030,0x181ec12,0x1c9e020,0x1c98141,0x59e031,0x187ec50,0x1c9e041,
    0x1c98120,0x49fa38,0x181ee12,0x1c9fa20,0x1c98141,0x59fa39,0x187ee50,0x1c9fa41,
    0x6018102,0x6018002,0x18c02,0x6018002,0x6018181,0x6618003,0x78c02,0x6018081,
    0x6018102,0x601da0a,0x18e02,0x601da02,0x6018181,0x661da0b,0x78e02,0x601da81,
    0x6018102,0x601e012,0x1ec12,0x601e002,0x6018181,0x661e013,0x7ec12,0x601e081,
    0x6018102,0x601fa1a,0x1ee12,0x601fa02,0x6018181,0x661fa1b,0x7ee12,0x601fa81,
    0x6498120,0x6498020,0x18c02,0x6498020,0x6498181,0x6698021,0x78c02,0x6498081,
    0x6498120,0x649da28,0x18e02,0x649da20,0x6498181,0x669da29,0x78e02,0x649da81,
    0x6498120,0x649e030,0x1ec12,0x649e020,0x6498181,0x669e031,0x7ec12,0x649e081,
    0x6498120,0x649fa38,0x1ee12,0x649fa20,0x6498181,0x669fa39,0x7ee12,0x649fa81,
    0x7818102,0x6018002,0x1818c02,0x7818002,0x78181c1,0x6718003,0x1878c40,0x78180c1,
    0x7818102,0x601da0a,0x1818e02,0x781da02,0x78181c1,0x671da0b,0x1878e40,0x781dac1,
    0x7818102,0x601e012,0x181ec12,0x781e002,0x78181c1,0x671e013,0x187ec50,0x781e0c1,
    0x7818102,0x601fa1a,0x181ee12,0x781fa02,0x78181c1,0x671fa1b,0x187ee50,0x781fac1,
    0x7c98120,0x6498020,0x1818c02,0x7c98020,0x7c981c1,0x6798021,0x1878c40,0x7c980c1,
    0x7c98120,0x649da28,0x1818e02,0x7c9da20,0x7c981c1,0x679da29,0x1878e40,0x7c9dac1,
    0x7c98120,0x649e030,0x181ec12,0x7c9e020,0x7c981c1,0x679e031,0x187ec50,0x7c9e0c1,
    0x7c98120,0x649fa38,0x181ee12,0x7c9fa20,0x7c981c1,0x679fa39,0x187ee50,0x7c9fac1};
const uint8_t lut1[256] = {0x4,0x4,0x4,0x4,0x4,0x1,0x4,0x4,
    0x6,0x6,0x3,0x6,0x4,0x4,0x4,0x4,
    0x4,0x4,0x4,0x4,0x1,0x1,0x1,0x1,
    0x6,0x6,0x3,0x6,0x4,0x4,0x4,0x4,
    0xc,0xc,0xc,0xc,0xc,0x9,0xc,0xc,
    0xb,0xb,0xb,0xb,0xc,0xc,0xc,0xc,
    0x4,0x4,0x4,0x4,0x4,0x1,0x4,0x4,
    0x6,0x6,0x3,0x6,0x4,0x4,0x4,0x4,
    0x4,0x1,0x4,0x4,0x4,0x1,0x4,0x4,
    0x6,0x3,0x3,0x6,0x4,0x1,0x4,0x4,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x3,0x3,0x3,0x3,0x1,0x1,0x1,0x1,
    0xc,0x9,0xc,0xc,0xc,0x9,0xc,0xc,
    0xb,0xb,0xb,0xb,0xc,0x9,0xc,0xc,
    0x4,0x1,0x4,0x4,0x4,0x1,0x4,0x4,
    0x6,0x3,0x3,0x6,0x4,0x1,0x4,0x4,
    0x14,0x14,0x11,0x14,0x14,0x11,0x11,0x14,
    0x16,0x16,0x13,0x16,0x14,0x14,0x11,0x14,
    0x14,0x14,0x11,0x14,0x11,0x11,0x11,0x11,
    0x16,0x16,0x13,0x16,0x14,0x14,0x11,0x14,
    0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
    0x1b,0x1b,0x1b,0x1b,0x19,0x19,0x19,0x19,
    0x14,0x14,0x11,0x14,0x14,0x11,0x11,0x14,
    0x16,0x16,0x13,0x16,0x14,0x14,0x11,0x14,
    0x4,0x4,0x4,0x4,0x4,0x1,0x4,0x4,
    0x6,0x6,0x3,0x6,0x4,0x4,0x4,0x4,
    0x4,0x4,0x4,0x4,0x1,0x1,0x1,0x1,
    0x6,0x6,0x3,0x6,0x4,0x4,0x4,0x4,
    0xc,0xc,0xc,0xc,0xc,0x9,0xc,0xc,
    0xb,0xb,0xb,0xb,0xc,0xc,0xc,0xc,
    0x4,0x4,0x4,0x4,0x4,0x1,0x4,0x4,
    0x6,0x6,0x3,0x6,0x4,0x4,0x4,0x4};
const uint16_t lut2[256] = {0x10,0x10,0x10,0x10,0x10,0x10,0x11,0x11,
    0x10,0x10,0x10,0x10,0x10,0x10,0x11,0x11,
    0x10,0x18,0x10,0x18,0x10,0x18,0x11,0x18,
    0x10,0x18,0x10,0x18,0x10,0x18,0x11,0x18,
    0x10,0x10,0x10,0x10,0x10,0x10,0x11,0x11,
    0x10,0x10,0x10,0x10,0x10,0x10,0x11,0x11,
    0x10,0x18,0x10,0x18,0x10,0x18,0x11,0x18,
    0x10,0x18,0x10,0x18,0x10,0x18,0x11,0x18,
    0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,
    0x304,0x304,0x304,0x304,0x304,0x304,0x304,0x304,
    0x0,0x8,0x0,0x8,0x0,0x8,0x1,0x8,
    0x304,0x30c,0x304,0x30c,0x304,0x30c,0x304,0x30c,
    0x2e2,0x2e2,0x2e2,0x2e2,0x2e2,0x2e2,0x2e2,0x2e2,
    0x3e6,0x3e6,0x3e6,0x3e6,0x3e6,0x3e6,0x3e6,0x3e6,
    0x2e2,0x2ea,0x2e2,0x2ea,0x2e2,0x2ea,0x2e2,0x2ea,
    0x3e6,0x3ee,0x3e6,0x3ee,0x3e6,0x3ee,0x3e6,0x3ee,
    0x40,0x40,0x40,0x40,0x40,0x40,0x41,0x41,
    0x344,0x344,0x344,0x344,0x344,0x344,0x344,0x344,
    0x40,0x48,0x40,0x48,0x40,0x48,0x41,0x48,
    0x344,0x34c,0x344,0x34c,0x344,0x34c,0x344,0x34c,
    0x60,0x60,0x60,0x60,0x60,0x60,0x61,0x61,
    0x364,0x364,0x364,0x364,0x364,0x364,0x364,0x364,
    0x60,0x68,0x60,0x68,0x60,0x68,0x61,0x68,
    0x364,0x36c,0x364,0x36c,0x364,0x36c,0x364,0x36c,
    0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,
    0x300,0x300,0x300,0x300,0x300,0x300,0x301,0x301,
    0x0,0x8,0x0,0x8,0x0,0x8,0x1,0x8,
    0x300,0x308,0x300,0x308,0x300,0x308,0x301,0x308,
    0x2e0,0x2e0,0x2e0,0x2e0,0x2e0,0x2e0,0x2e1,0x2e1,
    0x3e0,0x3e0,0x3e0,0x3e0,0x3e0,0x3e0,0x3e1,0x3e1,
    0x2e0,0x2e8,0x2e0,0x2e8,0x2e0,0x2e8,0x2e1,0x2e8,
    0x3e0,0x3e8,0x3e0,0x3e8,0x3e0,0x3e8,0x3e1,0x3e8};
const uint16_t lut3[128] = {0xc0,0xc1,0xc0,0xc1,0xe0,0xe1,0xe0,0xe1,
    0x6c2,0x6c3,0x6c2,0x6c3,0x6e2,0x6e3,0x6e2,0x6e3,
    0x0,0x1,0xc010,0xc010,0x5a0,0x5a1,0xc5b0,0xc5b0,
    0x600,0x601,0xc610,0xc610,0x7a0,0x7a1,0xc7b0,0xc7b0,
    0x1000,0x1001,0xd010,0xd010,0x1000,0x1001,0xd010,0xd010,
    0x1000,0x1001,0xd010,0xd010,0x1000,0x1001,0xd010,0xd010,
    0x0,0x1,0xc000,0xc001,0x5a4,0x5a5,0xc5a4,0xc5a5,
    0x602,0x603,0xc602,0xc603,0x7a6,0x7a7,0xc7a6,0xc7a7,
    0xc0,0xc1,0xc0,0xc1,0xe0,0xe1,0xe0,0xe1,
    0x6c2,0x6c3,0x6c2,0x6c3,0x6e2,0x6e3,0x6e2,0x6e3,
    0xb808,0xb808,0xf818,0xf818,0xbda8,0xbda8,0xfdb8,0xfdb8,
    0xbe08,0xbe08,0xfe18,0xfe18,0xbfa8,0xbfa8,0xffb8,0xffb8,
    0x1800,0x1801,0xd810,0xd810,0x1800,0x1801,0xd810,0xd810,
    0x1800,0x1801,0xd810,0xd810,0x1800,0x1801,0xd810,0xd810,
    0xb800,0xb801,0xf800,0xf801,0xbda4,0xbda5,0xfda4,0xfda5,
    0xbe02,0xbe03,0xfe02,0xfe03,0xbfa6,0xbfa7,0xffa6,0xffa7};
const uint16_t lut4[256] = {0xc0,0xc1,0x6d0,0x6d1,0x0,0x1,0x600,0x601,
    0x1000,0x1001,0x1000,0x1001,0x0,0x1,0x610,0x611,
    0xc0,0xc0,0x6d0,0x6d0,0x0,0x0,0x600,0x600,
    0x1000,0x1000,0x1000,0x1000,0x0,0x0,0x610,0x610,
    0xc0,0xc1,0x6d0,0x6d1,0xc004,0xc004,0xc604,0xc604,
    0xd004,0xd004,0xd004,0xd004,0xc000,0xc001,0xc610,0xc611,
    0xc0,0xc0,0x6d0,0x6d0,0xc004,0xc004,0xc604,0xc604,
    0xd004,0xd004,0xd004,0xd004,0xc000,0xc000,0xc610,0xc610,
    0xe0,0xe1,0x6f0,0x6f1,0x5a0,0x5a1,0x7a0,0x7a1,
    0x1000,0x1001,0x1000,0x1001,0x5a8,0x5a9,0x7b8,0x7b9,
    0xe0,0xe0,0x6f0,0x6f0,0x5a0,0x5a0,0x7a0,0x7a0,
    0x1000,0x1000,0x1000,0x1000,0x5a8,0x5a8,0x7b8,0x7b8,
    0xe0,0xe1,0x6f0,0x6f1,0xc5a4,0xc5a4,0xc7a4,0xc7a4,
    0xd004,0xd004,0xd004,0xd004,0xc5a8,0xc5a9,0xc7b8,0xc7b9,
    0xe0,0xe0,0x6f0,0x6f0,0xc5a4,0xc5a4,0xc7a4,0xc7a4,
    0xd004,0xd004,0xd004,0xd004,0xc5a8,0xc5a8,0xc7b8,0xc7b8,
    0xc0,0xc1,0x6d0,0x6d1,0xb802,0xb802,0xbe02,0xbe02,
    0x1800,0x1801,0x1800,0x1801,0xb800,0xb801,0xbe10,0xbe11,
    0xc0,0xc0,0x6d0,0x6d0,0xb802,0xb802,0xbe02,0xbe02,
    0x1800,0x1800,0x1800,0x1800,0xb800,0xb800,0xbe10,0xbe10,
    0xc0,0xc1,0x6d0,0x6d1,0xf806,0xf806,0xfe06,0xfe06,
    0xd804,0xd804,0xd804,0xd804,0xf800,0xf801,0xfe10,0xfe11,
    0xc0,0xc0,0x6d0,0x6d0,0xf806,0xf806,0xfe06,0xfe06,
    0xd804,0xd804,0xd804,0xd804,0xf800,0xf800,0xfe10,0xfe10,
    0xe0,0xe1,0x6f0,0x6f1,0xbda2,0xbda2,0xbfa2,0xbfa2,
    0x1800,0x1801,0x1800,0x1801,0xbda8,0xbda9,0xbfb8,0xbfb9,
    0xe0,0xe0,0x6f0,0x6f0,0xbda2,0xbda2,0xbfa2,0xbfa2,
    0x1800,0x1800,0x1800,0x1800,0xbda8,0xbda8,0xbfb8,0xbfb8,
    0xe0,0xe1,0x6f0,0x6f1,0xfda6,0xfda6,0xffa6,0xffa6,
    0xd804,0xd804,0xd804,0xd804,0xfda8,0xfda9,0xffb8,0xffb9,
    0xe0,0xe0,0x6f0,0x6f0,0xfda6,0xfda6,0xffa6,0xffa6,
    0xd804,0xd804,0xd804,0xd804,0xfda8,0xfda8,0xffb8,0xffb8};
const uint8_t lut5[128] = {0x8,0x28,0x8,0x8,0xc,0x2c,0xc,0xc,
    0x8,0x8,0x8,0x8,0xc,0xc,0xc,0xc,
    0xca,0xca,0xca,0xca,0xce,0xce,0xce,0xce,
    0xca,0xca,0xca,0xca,0xce,0xce,0xce,0xce,
    0x0,0x20,0x0,0x0,0x0,0x20,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x20,0x0,0x0,0x0,0x20,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x20,0x0,0x0,0x9c,0xbc,0x9c,0x9c,
    0x0,0x0,0x0,0x0,0x9c,0x9c,0x9c,0x9c,
    0xc0,0xe0,0xc0,0xc0,0xdc,0xfc,0xdc,0xdc,
    0xc0,0xc0,0xc0,0xc0,0xdc,0xdc,0xdc,0xdc,
    0x0,0x20,0x0,0x0,0x9d,0x9d,0x9d,0x9d,
    0x0,0x0,0x0,0x0,0x9d,0x9d,0x9d,0x9d,
    0xc2,0xc2,0xc2,0xc2,0xdf,0xdf,0xdf,0xdf,
    0xc2,0xc2,0xc2,0xc2,0xdf,0xdf,0xdf,0xdf};
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
  uint32_t lut0input = ((apValues & 256)>0?4:0) | (uvwState9>0?8:0) | (uvwState10>0?16:0) | (uvwState19>0?32:0) | (uvwState20>0?64:0) | (uvwState21>0?128:0) | (apValues & 3);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = (apValues & 255);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = (uvwState16>0?8:0) | (uvwState18>0?16:0) | (uvwState15>0?32:0) | (lut0output & 3) | (lut1output & 4) | (apValues & 192);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = (uvwState14>0?2:0) | (uvwState5>0?4:0) | (uvwState6>0?8:0) | (uvwState13>0?64:0) | (lut2output & 1) | (apValues & 48);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = (uvwState4>0?2:0) | (uvwState12>0?32:0) | (uvwState3>0?64:0) | (uvwState11>0?128:0) | (lut3output & 1) | (apValues & 12) | (lut0output & 16);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = (uvwState7>0?4:0) | (uvwState8>0?16:0) | ((apValues & 128)>0?32:0) | (lut4output & 1) | (lut3output & 2) | (lut0output & 8) | (apValues & 64);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = (uvwState2>0?64:0) | (uvwState1>0?128:0) | (apValues & 3) | (lut3output & 4) | (lut4output & 24) | (lut5output & 32);
  uint32_t lut6output = lut6[lut6input];
  if ((lut0output & 4)) {
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
  } else if ((lut3output & 2)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 1)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 2)) {
        buf.b0p0 = buf.b8p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 8)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 16)) {
        buf.b0p0 = buf.b10p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 2)) {
        buf.b0p0 = buf.b11p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 4)) {
        buf.b0p0 = buf.b12p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 8)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 16)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 2)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 4)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 1)) {
        buf.b0p0 = b17p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 8)) {
        buf.b0p0 = buf.b18p0 | (apValues << 18) | (17 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 32)) {
        buf.b0p0 = buf.b19p0 | (apValues << 18) | (18 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 64)) {
        buf.b0p0 = b20p0 | (apValues << 18) | (19 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 128)) {
        buf.b0p0 = b21p0 | (apValues << 18) | (20 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  if ((lut6output & 8)) {
  } else if ((lut0output & 256)) {
        buf.b1p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 32)) {
        buf.b2p0 = buf.b1p0 | (apValues << 9);
  } else if ((lut6output & 64)) {
  }
  if ((lut4output & 32)) {
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
  if ((lut5output & 4)) {
  } else if ((lut2output & 16)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut5output & 16)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut5output & 64)) {
  }
  if ((lut0output & 512)) {
  } else if ((lut0output & 1024)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut0output & 4096)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut0output & 8192)) {
  }
  if ((lut4output & 2048)) {
  } else if ((lut1output & 2)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 8192)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut4output & 16384)) {
  }
  if ((lut3output & 2048)) {
  } else if ((lut1output & 8)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut3output & 8192)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut3output & 16384)) {
  }
  if ((lut2output & 32)) {
  } else if ((lut1output & 16)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut2output & 128)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut2output & 256)) {
  }
  if ((lut0output & 32768)) {
  }
  if ((lut0output & 131072)) {
        buf.b18p0 = b17p0 | (apValues << 0);
  }
  if ((lut0output & 524288)) {
  } else if ((lut0output & 1048576)) {
        buf.b19p0 = b20p0 | (apValues << 0) | (0 << 9);
  } else if ((lut0output & 2097152)) {
        buf.b19p0 = b21p0 | (apValues << 0) | (1 << 9);
  }
  if ((lut0output & 8388608)) {
  }
  if ((lut0output & 33554432)) {
  }
  uvwState0 = (lut6output & 4);
  uvwState1 = (lut6output & 16);
  uvwState2 = (lut6output & 128);
  uvwState3 = (lut4output & 128);
  uvwState4 = (lut4output & 1024);
  uvwState5 = (lut3output & 128);
  uvwState6 = (lut3output & 1024);
  uvwState7 = (lut5output & 8);
  uvwState8 = (lut5output & 128);
  uvwState9 = (lut0output & 2048);
  uvwState10 = (lut0output & 16384);
  uvwState11 = (lut4output & 4096);
  uvwState12 = (lut4output & 32768);
  uvwState13 = (lut3output & 4096);
  uvwState14 = (lut3output & 32768);
  uvwState15 = (lut2output & 64);
  uvwState16 = (lut2output & 512);
  uvwState17 = (lut0output & 65536);
  uvwState18 = (lut0output & 262144);
  uvwState19 = (lut0output & 4194304);
  uvwState20 = (lut0output & 16777216);
  uvwState21 = (lut0output & 67108864);
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
  -> Inputs a1 a2 m uvwState9 uvwState10 uvwState19 uvwState20 uvwState21
  -> Outputs new_n79 new_n88 uvwState0incoming0 uvwState0incoming9 uvwState0incoming10 uvwState0incoming19 uvwState0incoming20 uvwState0incoming21 uvwState1incoming1 uvwState9incoming0 uvwState9incoming1 uvwState9Next uvwState10incoming0 uvwState10incoming1 uvwState10Next uvwState17incoming0 uvwState17Next uvwState18incoming0 uvwState18Next uvwState19incoming0 uvwState19incoming1 uvwState19incoming2 uvwState19Next uvwState20incoming0 uvwState20Next uvwState21incoming0 uvwState21Next
- LUT 1 has:
  -> Inputs a1 a2 b1 b2 c1 c2 d1 d2
  -> Outputs uvwState0incoming17 uvwState11incoming1 new_n77 uvwState13incoming1 uvwState15incoming1
- LUT 2 has:
  -> Inputs new_n79 new_n88 new_n77 uvwState16 uvwState18 uvwState15 d1 d2
  -> Outputs new_n92 uvwState0incoming15 uvwState0incoming16 uvwState0incoming18 uvwState7incoming1 uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 3 has:
  -> Inputs new_n92 uvwState14 uvwState5 uvwState6 c1 c2 uvwState13
  -> Outputs new_n94 uvwState0incoming6 uvwState0incoming5 uvwState0incoming13 uvwState0incoming14 uvwState5incoming0 uvwState5incoming1 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next uvwState13incoming0 uvwState13Next uvwState14incoming0 uvwState14incoming1 uvwState14Next
- LUT 4 has:
  -> Inputs new_n94 uvwState4 b1 b2 uvwState0incoming10 uvwState12 uvwState3 uvwState11
  -> Outputs new_n97 uvwState0incoming11 uvwState0incoming12 uvwState0incoming3 uvwState0incoming4 uvwState3incoming0 uvwState3incoming1 uvwState3Next uvwState4incoming0 uvwState4incoming1 uvwState4Next uvwState11incoming0 uvwState11Next uvwState12incoming0 uvwState12incoming1 uvwState12Next
- LUT 5 has:
  -> Inputs new_n97 uvwState0incoming6 uvwState7 uvwState0incoming9 uvwState8 d2 d1
  -> Outputs uvwState0incoming7 uvwState0incoming8 uvwState7incoming0 uvwState7Next uvwState8incoming0 new_n101 uvwState8incoming1 uvwState8Next
- LUT 6 has:
  -> Inputs a1 a2 uvwState0incoming5 uvwState0incoming3 uvwState0incoming4 new_n101 uvwState2 uvwState1
  -> Outputs uvwState0incoming1 uvwState0incoming2 uvwState0Next uvwState1incoming0 uvwState1Next uvwState2incoming0 uvwState2incoming1 uvwState2Next
*/
