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

const uint16_t lut0[128] = {0x1808,0x1808,0x1c00,0x1c00,0x1809,0x1809,0x1c01,0x1c01,
    0x1900,0x1900,0x1d00,0x1d00,0x1808,0x1808,0x1c00,0x1c00,
    0x180a,0x188a,0x1c02,0x1c82,0x180b,0x188b,0x1c03,0x1c83,
    0x1902,0x1982,0x1d02,0x1d82,0x180a,0x188a,0x1c02,0x1c82,
    0x1a08,0x1a88,0x1e20,0x1ea0,0x1a09,0x1a89,0x1e21,0x1ea1,
    0x1b10,0x1b90,0x1f30,0x1fb0,0x1a08,0x1a88,0x1e20,0x1ea0,
    0x1808,0x1808,0x1c00,0x1c00,0x1809,0x1809,0x1c01,0x1c01,
    0x1900,0x1900,0x1d00,0x1d00,0x1808,0x1808,0x1c00,0x1c00,
    0x180c,0x180c,0x1808,0x1808,0x180d,0x180d,0x1809,0x1809,
    0x1904,0x1904,0x1900,0x1900,0x180c,0x180c,0x1808,0x1808,
    0x180e,0x188e,0x180a,0x188a,0x180f,0x188f,0x180b,0x188b,
    0x1906,0x1986,0x1902,0x1982,0x180e,0x188e,0x180a,0x188a,
    0x1a0c,0x1a8c,0x1a08,0x1a88,0x1a0d,0x1a8d,0x1a09,0x1a89,
    0x1b14,0x1b94,0x1b10,0x1b90,0x1a0c,0x1a8c,0x1a08,0x1a88,
    0x180c,0x180c,0x1808,0x1808,0x180d,0x180d,0x1809,0x1809,
    0x1904,0x1904,0x1900,0x1900,0x180c,0x180c,0x1808,0x1808};
const uint32_t lut1[128] = {0x180,0x8,0x6040,0x0,0x1a0,0xb28,0x6040,0xb21,
    0x180,0x8,0x6000,0x0,0x1a0,0xb28,0x6000,0xb21,
    0x180,0x2d00c,0x7040,0x2d000,0x1a0,0x2db2c,0x7040,0x2db21,
    0x180,0x2d00c,0x7000,0x2d000,0x1a0,0x2db2c,0x7000,0x2db21,
    0x180,0x30018,0x36050,0x30000,0x1a0,0x30b38,0x36050,0x30b21,
    0x180,0x30018,0x36010,0x30000,0x1a0,0x30b38,0x36010,0x30b21,
    0x180,0x3d01c,0x37050,0x3d000,0x1a0,0x3db3c,0x37050,0x3db21,
    0x180,0x3d01c,0x37010,0x3d000,0x1a0,0x3db3c,0x37010,0x3db21,
    0xd82,0xc08,0x6040,0xc02,0xda2,0xf28,0x6040,0xf23,
    0xd82,0xc08,0x6000,0xc02,0xda2,0xf28,0x6000,0xf23,
    0xd82,0x2dc0c,0x7040,0x2dc02,0xda2,0x2df2c,0x7040,0x2df23,
    0xd82,0x2dc0c,0x7000,0x2dc02,0xda2,0x2df2c,0x7000,0x2df23,
    0xd82,0x30c18,0x36050,0x30c02,0xda2,0x30f38,0x36050,0x30f23,
    0xd82,0x30c18,0x36010,0x30c02,0xda2,0x30f38,0x36010,0x30f23,
    0xd82,0x3dc1c,0x37050,0x3dc02,0xda2,0x3df3c,0x37050,0x3df23,
    0xd82,0x3dc1c,0x37010,0x3dc02,0xda2,0x3df3c,0x37010,0x3df23};
const uint16_t lut2[128] = {0x1,0x1,0x1,0x1,0x1,0x1,0x61,0x1,
    0x1,0x1,0x1,0x1,0x2,0x2,0x61,0x2,
    0x484,0x484,0x1,0x484,0x481,0x484,0x61,0x481,
    0x484,0x484,0x1,0x484,0x482,0x486,0x61,0x482,
    0x1801,0x1,0x1801,0x1801,0x1808,0x501,0x1868,0x1808,
    0x1801,0x1,0x1801,0x1801,0x180a,0x502,0x1868,0x180a,
    0x1c84,0x484,0x1801,0x1c84,0x1c88,0x584,0x1868,0x1c88,
    0x1c84,0x484,0x1801,0x1c84,0x1c8a,0x586,0x1868,0x1c8a,
    0x6001,0x6001,0x1,0x6001,0x6010,0x6601,0x61,0x6010,
    0x6001,0x6001,0x1,0x6001,0x6012,0x6602,0x61,0x6012,
    0x6484,0x6484,0x1,0x6484,0x6490,0x6684,0x61,0x6490,
    0x6484,0x6484,0x1,0x6484,0x6492,0x6686,0x61,0x6492,
    0x7801,0x6001,0x1801,0x7801,0x7818,0x6701,0x1868,0x7818,
    0x7801,0x6001,0x1801,0x7801,0x781a,0x6702,0x1868,0x781a,
    0x7c84,0x6484,0x1801,0x7c84,0x7c98,0x6784,0x1868,0x7c98,
    0x7c84,0x6484,0x1801,0x7c84,0x7c9a,0x6786,0x1868,0x7c9a};
const uint8_t lut3[128] = {0x2,0x2,0x2,0x1,0x2,0x2,0x1,0x1,
    0x2,0x1,0x2,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1};
const uint16_t lut4[128] = {0x8,0x8,0x8,0x9,0x8,0x8,0x8,0x9,
    0x8,0x8,0x8,0x9,0x8,0x8,0x8,0x9,
    0x20,0x20,0x20,0x21,0x30,0x30,0x30,0x31,
    0x1a4,0x1a4,0x1a4,0x1a4,0x1b4,0x1b4,0x1b4,0x1b4,
    0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
    0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
    0x20,0x20,0x20,0x20,0x30,0x30,0x30,0x30,
    0x1a4,0x1a4,0x1a4,0x1a4,0x1b4,0x1b4,0x1b4,0x1b4,
    0x0,0x0,0x0,0x1,0x172,0x172,0x172,0x172,
    0x184,0x184,0x184,0x184,0x1f6,0x1f6,0x1f6,0x1f6,
    0x0,0x0,0x0,0x1,0x170,0x170,0x170,0x171,
    0x180,0x180,0x180,0x181,0x1f0,0x1f0,0x1f0,0x1f1,
    0x0,0x0,0x0,0x0,0x172,0x172,0x172,0x172,
    0x184,0x184,0x184,0x184,0x1f6,0x1f6,0x1f6,0x1f6,
    0x0,0x0,0x0,0x0,0x170,0x170,0x170,0x170,
    0x180,0x180,0x180,0x180,0x1f0,0x1f0,0x1f0,0x1f0};
const uint16_t lut5[128] = {0x10,0x11,0x10,0x11,0x0,0x1,0x0,0x1,
    0x40,0x41,0x40,0x41,0x0,0x1,0x0,0x1,
    0x10,0x11,0x18,0x18,0x0,0x1,0x8,0x8,
    0x40,0x41,0x48,0x48,0x0,0x1,0x8,0x8,
    0x10,0x11,0x10,0x11,0x304,0x304,0x304,0x304,
    0x344,0x344,0x344,0x344,0x300,0x301,0x300,0x301,
    0x10,0x11,0x18,0x18,0x304,0x304,0x30c,0x30c,
    0x344,0x344,0x34c,0x34c,0x300,0x301,0x308,0x308,
    0x10,0x11,0x10,0x11,0x2e2,0x2e2,0x2e2,0x2e2,
    0x60,0x61,0x60,0x61,0x2e0,0x2e1,0x2e0,0x2e1,
    0x10,0x11,0x18,0x18,0x2e2,0x2e2,0x2ea,0x2ea,
    0x60,0x61,0x68,0x68,0x2e0,0x2e1,0x2e8,0x2e8,
    0x10,0x11,0x10,0x11,0x3e6,0x3e6,0x3e6,0x3e6,
    0x364,0x364,0x364,0x364,0x3e0,0x3e1,0x3e0,0x3e1,
    0x10,0x11,0x18,0x18,0x3e6,0x3e6,0x3ee,0x3ee,
    0x364,0x364,0x36c,0x36c,0x3e0,0x3e1,0x3e8,0x3e8};
const uint8_t lut6[128] = {0x10,0x11,0x0,0x1,0x10,0x10,0x0,0x0,
    0xd4,0xd4,0x0,0x1,0xd4,0xd4,0x0,0x0,
    0x10,0x10,0x0,0x0,0x10,0x10,0x0,0x0,
    0xd4,0xd4,0x0,0x0,0xd4,0xd4,0x0,0x0,
    0x18,0x19,0x0,0x1,0x18,0x18,0x0,0x0,
    0xdc,0xdc,0x0,0x1,0xdc,0xdc,0x0,0x0,
    0x18,0x18,0x0,0x0,0x18,0x18,0x0,0x0,
    0xdc,0xdc,0x0,0x0,0xdc,0xdc,0x0,0x0,
    0x0,0x1,0x0,0x1,0x0,0x0,0x0,0x0,
    0xc0,0xc1,0xc4,0xc4,0xc0,0xc0,0xc4,0xc4,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0xc0,0xc0,0xc4,0xc4,0xc0,0xc0,0xc4,0xc4,
    0xb8,0xb9,0xba,0xba,0xb8,0xb8,0xba,0xba,
    0xf8,0xf9,0xfe,0xfe,0xf8,0xf8,0xfe,0xfe,
    0xb8,0xb8,0xba,0xba,0xb8,0xb8,0xba,0xba,
    0xf8,0xf8,0xfe,0xfe,0xf8,0xf8,0xfe,0xfe};
const uint16_t lut7[128] = {0x28,0x38,0x28,0x38,0x2c,0x3c,0x2c,0x3c,
    0x1aa,0x1aa,0x1aa,0x1aa,0x1ae,0x1ae,0x1ae,0x1ae,
    0x0,0x10,0x3000,0x3010,0x164,0x174,0x3164,0x3174,
    0x180,0x190,0x3180,0x3190,0x1e4,0x1f4,0x31e4,0x31f4,
    0x400,0x410,0x3400,0x3410,0x400,0x410,0x3400,0x3410,
    0x400,0x410,0x3400,0x3410,0x400,0x410,0x3400,0x3410,
    0x0,0x10,0x3000,0x3010,0x165,0x165,0x3165,0x3165,
    0x182,0x182,0x3182,0x3182,0x1e7,0x1e7,0x31e7,0x31e7,
    0x28,0x38,0x28,0x38,0x2c,0x3c,0x2c,0x3c,
    0x1aa,0x1aa,0x1aa,0x1aa,0x1ae,0x1ae,0x1ae,0x1ae,
    0x2e00,0x2e10,0x3e00,0x3e10,0x2f64,0x2f74,0x3f64,0x3f74,
    0x2f80,0x2f90,0x3f80,0x3f90,0x2fe4,0x2ff4,0x3fe4,0x3ff4,
    0x600,0x610,0x3600,0x3610,0x600,0x610,0x3600,0x3610,
    0x600,0x610,0x3600,0x3610,0x600,0x610,0x3600,0x3610,
    0x2e00,0x2e10,0x3e00,0x3e10,0x2f65,0x2f65,0x3f65,0x3f65,
    0x2f82,0x2f82,0x3f82,0x3f82,0x2fe7,0x2fe7,0x3fe7,0x3fe7};
const uint8_t lut8[128] = {0x14,0x14,0x14,0x14,0x4,0x4,0x4,0x4,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x10,0x14,0x14,0x14,0x0,0x4,0x4,0x4,
    0x0,0x4,0x4,0x4,0x0,0x4,0x4,0x4,
    0x1c,0x1c,0x1c,0x1c,0xbc,0xbc,0xbc,0xbc,
    0x4,0x4,0x4,0x4,0xbd,0xbd,0xbd,0xbd,
    0x18,0x1c,0x1c,0x1c,0xb8,0xbc,0xbc,0xbc,
    0x0,0x4,0x4,0x4,0xbd,0xbd,0xbd,0xbd,
    0xd6,0xd6,0xd6,0xd6,0xc4,0xc4,0xc4,0xc4,
    0x4,0x4,0x4,0x4,0xc6,0xc6,0xc6,0xc6,
    0xd6,0xd6,0xd6,0xd6,0xc0,0xc4,0xc4,0xc4,
    0x0,0x4,0x4,0x4,0xc6,0xc6,0xc6,0xc6,
    0xde,0xde,0xde,0xde,0xfc,0xfc,0xfc,0xfc,
    0x4,0x4,0x4,0x4,0xff,0xff,0xff,0xff,
    0xde,0xde,0xde,0xde,0xf8,0xfc,0xfc,0xfc,
    0x0,0x4,0x4,0x4,0xff,0xff,0xff,0xff};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = ((apValues & 128)>0?2:0) | (uvwState14 & 1) | (apValues & 124);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = (uvwState1>0?4:0) | (uvwState9>0?16:0) | (uvwState10>0?32:0) | (uvwState2>0?64:0) | (apValues & 3) | (lut0output & 8);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = ((apValues & 256)>0?4:0) | (uvwState18>0?8:0) | (uvwState19>0?16:0) | (uvwState20>0?32:0) | (uvwState21>0?64:0) | (apValues & 3);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = (lut0output & 55) | (lut1output & 72);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = (uvwState15>0?4:0) | (uvwState16>0?8:0) | ((apValues & 128)>0?16:0) | ((lut0output & 128)>0?32:0) | (lut2output & 1) | (lut3output & 2) | (apValues & 64);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = (uvwState13>0?16:0) | (uvwState12>0?32:0) | (uvwState11>0?64:0) | (lut4output & 1) | (lut0output & 2) | (apValues & 12);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = ((apValues & 128)>0?2:0) | (uvwState8>0?8:0) | (uvwState7>0?32:0) | (lut5output & 1) | (lut1output & 20) | (apValues & 64);
  uint32_t lut6output = lut6[lut6input];
  uint32_t lut7input = (uvwState14>0?2:0) | (uvwState5>0?4:0) | (uvwState6>0?8:0) | (uvwState13>0?64:0) | (lut6output & 1) | (apValues & 48);
  uint32_t lut7output = lut7[lut7input];
  uint32_t lut8input = (uvwState3>0?32:0) | (uvwState4>0?64:0) | (lut1output & 3) | (apValues & 12) | (lut7output & 16);
  uint32_t lut8output = lut8[lut8input];
  if ((lut0output & 64)) {
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 1)) {
        buf.b0p0 = buf.b1p0 | (apValues << 18) | (0 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 2)) {
        buf.b0p0 = buf.b2p0 | (apValues << 18) | (1 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut8output & 1)) {
        buf.b0p0 = buf.b3p0 | (apValues << 18) | (2 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut8output & 2)) {
        buf.b0p0 = buf.b4p0 | (apValues << 18) | (3 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 1)) {
        buf.b0p0 = buf.b5p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 2)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 2)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 4)) {
        buf.b0p0 = buf.b8p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 4)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 16)) {
        buf.b0p0 = buf.b10p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 2)) {
        buf.b0p0 = buf.b11p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 4)) {
        buf.b0p0 = buf.b12p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 8)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 128)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 2)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 4)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 1)) {
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
  if ((lut1output & 32)) {
  } else if ((lut1output & 128)) {
        buf.b1p0 = b17p0 | (apValues << 0);
  }
  if ((lut1output & 512)) {
        buf.b2p0 = buf.b1p0 | (apValues << 9);
  } else if ((lut1output & 1024)) {
  }
  if ((lut8output & 8)) {
  } else if ((lut5output & 16)) {
        buf.b3p0 = b17p0 | (apValues << 0);
  }
  if ((lut8output & 32)) {
        buf.b4p0 = buf.b3p0 | (apValues << 9);
  } else if ((lut8output & 64)) {
  }
  if ((lut7output & 4)) {
  } else if ((lut7output & 8)) {
        buf.b5p0 = b17p0 | (apValues << 0);
  }
  if ((lut7output & 64)) {
        buf.b6p0 = buf.b5p0 | (apValues << 9);
  } else if ((lut7output & 128)) {
  }
  if ((lut6output & 8)) {
  } else if ((lut4output & 8)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 32)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut6output & 64)) {
  }
  if ((lut1output & 4096)) {
  } else if ((lut1output & 8192)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut1output & 32768)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut1output & 65536)) {
  }
  if ((lut5output & 32)) {
  } else if ((lut0output & 256)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut5output & 128)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut5output & 256)) {
  }
  if ((lut7output & 512)) {
  } else if ((lut0output & 512)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut7output & 2048)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut7output & 4096)) {
  }
  if ((lut4output & 16)) {
  } else if ((lut0output & 1024)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 64)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut4output & 128)) {
  }
  if ((lut0output & 2048)) {
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
  uvwState0 = (lut8output & 4);
  uvwState1 = (lut1output & 256);
  uvwState2 = (lut1output & 2048);
  uvwState3 = (lut8output & 16);
  uvwState4 = (lut8output & 128);
  uvwState5 = (lut7output & 32);
  uvwState6 = (lut7output & 256);
  uvwState7 = (lut6output & 16);
  uvwState8 = (lut6output & 128);
  uvwState9 = (lut1output & 16384);
  uvwState10 = (lut1output & 131072);
  uvwState11 = (lut5output & 64);
  uvwState12 = (lut5output & 512);
  uvwState13 = (lut7output & 1024);
  uvwState14 = (lut7output & 8192);
  uvwState15 = (lut4output & 32);
  uvwState16 = (lut4output & 256);
  uvwState17 = (lut0output & 4096);
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
  -> Inputs uvwState14 d2 b1 b2 c1 c2 d1
  -> Outputs new_n40 new_n46 new_n52 new_n65 new_n70 new_n74 uvwState0incoming0 uvwState0incoming14 uvwState11incoming1 uvwState13incoming1 uvwState15incoming1 uvwState17incoming0 uvwState17Next
- LUT 1 has:
  -> Inputs a1 a2 uvwState1 new_n65 uvwState9 uvwState10 uvwState2
  -> Outputs uvwState0incoming1 uvwState0incoming2 uvwState0incoming9 new_n34 uvwState0incoming10 uvwState1incoming0 new_n66 uvwState1incoming1 uvwState1Next uvwState2incoming0 uvwState2incoming1 uvwState2Next uvwState9incoming0 uvwState9incoming1 uvwState9Next uvwState10incoming0 uvwState10incoming1 uvwState10Next
- LUT 2 has:
  -> Inputs a1 a2 m uvwState18 uvwState19 uvwState20 uvwState21
  -> Outputs new_n89 uvwState0incoming18 uvwState0incoming19 uvwState0incoming20 uvwState0incoming21 uvwState18incoming0 uvwState18Next uvwState19incoming0 uvwState19incoming1 uvwState19incoming2 uvwState19Next uvwState20incoming0 uvwState20Next uvwState21incoming0 uvwState21Next
- LUT 3 has:
  -> Inputs new_n40 new_n46 new_n52 new_n34 new_n70 new_n74 new_n66
  -> Outputs uvwState0incoming17 new_n77
- LUT 4 has:
  -> Inputs new_n89 new_n77 uvwState15 uvwState16 d2 uvwState0incoming14 d1
  -> Outputs new_n93 uvwState0incoming15 uvwState0incoming16 uvwState7incoming1 uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 5 has:
  -> Inputs new_n93 new_n46 b1 b2 uvwState13 uvwState12 uvwState11
  -> Outputs new_n96 uvwState0incoming11 uvwState0incoming12 uvwState0incoming13 uvwState3incoming1 uvwState11incoming0 uvwState11Next uvwState12incoming0 uvwState12incoming1 uvwState12Next
- LUT 6 has:
  -> Inputs new_n96 d2 uvwState0incoming9 uvwState8 uvwState0incoming10 uvwState7 d1
  -> Outputs new_n100 uvwState0incoming7 uvwState0incoming8 uvwState7incoming0 uvwState7Next uvwState8incoming0 uvwState8incoming1 uvwState8Next
- LUT 7 has:
  -> Inputs new_n100 uvwState14 uvwState5 uvwState6 c1 c2 uvwState13
  -> Outputs uvwState0incoming5 uvwState0incoming6 uvwState5incoming0 uvwState5incoming1 new_n102 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next uvwState13incoming0 uvwState13Next uvwState14incoming0 uvwState14incoming1 uvwState14Next
- LUT 8 has:
  -> Inputs uvwState0incoming1 uvwState0incoming2 b1 b2 new_n102 uvwState3 uvwState4
  -> Outputs uvwState0incoming3 uvwState0incoming4 uvwState0Next uvwState3incoming0 uvwState3Next uvwState4incoming0 uvwState4incoming1 uvwState4Next
*/
