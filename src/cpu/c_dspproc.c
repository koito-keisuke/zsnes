#include <string.h>

#include "../asm_call.h"
#include "../endmem.h"
#include "../gblvars.h"
#include "../macros.h"
#include "../ui.h"
#include "c_dspproc.h"
#include "dsp.h"
#include "dspproc.h"
#include "spc700.h"


void conv2speed(u4 ecx, u4* esi, u4 const* edi)
{
	do *esi++ = (u8)*edi++ * SBToSPC / 11025U; while (--ecx != 0);
}


void InitSPC(void)
{
	asm_call(AdjustFrequency);

	for (u4 i = 0; i != lengthof(VolumeConvTable); ++i)
		VolumeConvTable[i] = (s1)((i >> 8) * (i & 0xFFU) >> 7);

	memset(SPCRAM, 0, 0xEF);
	spcPCRam = SPCRAM + 0xFFC0;
	spcS     = 0x1EF;
	spcRamDP = SPCRAM;
	spcX     = 0;

	// initialize all the SPC write registers
	spcWptr[0x00] = SPCRegF0;
	spcWptr[0x01] = SPCRegF1;
	spcWptr[0x02] = SPCRegF2;
	spcWptr[0x03] = SPCRegF3;
	spcWptr[0x04] = SPCRegF4;
	spcWptr[0x05] = SPCRegF5;
	spcWptr[0x06] = SPCRegF6;
	spcWptr[0x07] = SPCRegF7;
	spcWptr[0x08] = SPCRegF8;
	spcWptr[0x09] = SPCRegF9;
	spcWptr[0x0A] = SPCRegFA;
	spcWptr[0x0B] = SPCRegFB;
	spcWptr[0x0C] = SPCRegFC;
	spcWptr[0x0D] = SPCRegFD;
	spcWptr[0x0E] = SPCRegFE;
	spcWptr[0x0F] = SPCRegFF;

	spcRptr[0x00] = RSPCRegF0;
	spcRptr[0x01] = RSPCRegF1;
	spcRptr[0x02] = RSPCRegF2;
	spcRptr[0x03] = RSPCRegF3;
	spcRptr[0x04] = RSPCRegF4;
	spcRptr[0x05] = RSPCRegF5;
	spcRptr[0x06] = RSPCRegF6;
	spcRptr[0x07] = RSPCRegF7;
	spcRptr[0x08] = RSPCRegF8;
	spcRptr[0x09] = RSPCRegF9;
	spcRptr[0x0A] = RSPCRegFA;
	spcRptr[0x0B] = RSPCRegFB;
	spcRptr[0x0C] = RSPCRegFC;
	spcRptr[0x0D] = RSPCRegFD;
	spcRptr[0x0E] = RSPCRegFE;
	spcRptr[0x0F] = RSPCRegFF;

	dspRptr[0x00] = RDSPReg00;
	dspRptr[0x01] = RDSPReg01;
	dspRptr[0x02] = RDSPReg02;
	dspRptr[0x03] = RDSPReg03;
	dspRptr[0x04] = RDSPReg04;
	dspRptr[0x05] = RDSPReg05;
	dspRptr[0x06] = RDSPReg06;
	dspRptr[0x07] = RDSPReg07;
	dspRptr[0x08] = RDSPReg08;
	dspRptr[0x09] = RDSPReg09;
	dspRptr[0x0A] = RDSPReg0A;
	dspRptr[0x0B] = RDSPReg0B;
	dspRptr[0x0C] = RDSPReg0C;
	dspRptr[0x0D] = RDSPReg0D;
	dspRptr[0x0E] = RDSPReg0E;
	dspRptr[0x0F] = RDSPReg0F;
	dspRptr[0x10] = RDSPReg10;
	dspRptr[0x11] = RDSPReg11;
	dspRptr[0x12] = RDSPReg12;
	dspRptr[0x13] = RDSPReg13;
	dspRptr[0x14] = RDSPReg14;
	dspRptr[0x15] = RDSPReg15;
	dspRptr[0x16] = RDSPReg16;
	dspRptr[0x17] = RDSPReg17;
	dspRptr[0x18] = RDSPReg18;
	dspRptr[0x19] = RDSPReg19;
	dspRptr[0x1A] = RDSPReg1A;
	dspRptr[0x1B] = RDSPReg1B;
	dspRptr[0x1C] = RDSPReg1C;
	dspRptr[0x1D] = RDSPReg1D;
	dspRptr[0x1E] = RDSPReg1E;
	dspRptr[0x1F] = RDSPReg1F;
	dspRptr[0x20] = RDSPReg20;
	dspRptr[0x21] = RDSPReg21;
	dspRptr[0x22] = RDSPReg22;
	dspRptr[0x23] = RDSPReg23;
	dspRptr[0x24] = RDSPReg24;
	dspRptr[0x25] = RDSPReg25;
	dspRptr[0x26] = RDSPReg26;
	dspRptr[0x27] = RDSPReg27;
	dspRptr[0x28] = RDSPReg28;
	dspRptr[0x29] = RDSPReg29;
	dspRptr[0x2A] = RDSPReg2A;
	dspRptr[0x2B] = RDSPReg2B;
	dspRptr[0x2C] = RDSPReg2C;
	dspRptr[0x2D] = RDSPReg2D;
	dspRptr[0x2E] = RDSPReg2E;
	dspRptr[0x2F] = RDSPReg2F;
	dspRptr[0x30] = RDSPReg30;
	dspRptr[0x31] = RDSPReg31;
	dspRptr[0x32] = RDSPReg32;
	dspRptr[0x33] = RDSPReg33;
	dspRptr[0x34] = RDSPReg34;
	dspRptr[0x35] = RDSPReg35;
	dspRptr[0x36] = RDSPReg36;
	dspRptr[0x37] = RDSPReg37;
	dspRptr[0x38] = RDSPReg38;
	dspRptr[0x39] = RDSPReg39;
	dspRptr[0x3A] = RDSPReg3A;
	dspRptr[0x3B] = RDSPReg3B;
	dspRptr[0x3C] = RDSPReg3C;
	dspRptr[0x3D] = RDSPReg3D;
	dspRptr[0x3E] = RDSPReg3E;
	dspRptr[0x3F] = RDSPReg3F;
	dspRptr[0x40] = RDSPReg40;
	dspRptr[0x41] = RDSPReg41;
	dspRptr[0x42] = RDSPReg42;
	dspRptr[0x43] = RDSPReg43;
	dspRptr[0x44] = RDSPReg44;
	dspRptr[0x45] = RDSPReg45;
	dspRptr[0x46] = RDSPReg46;
	dspRptr[0x47] = RDSPReg47;
	dspRptr[0x48] = RDSPReg48;
	dspRptr[0x49] = RDSPReg49;
	dspRptr[0x4A] = RDSPReg4A;
	dspRptr[0x4B] = RDSPReg4B;
	dspRptr[0x4C] = RDSPReg4C;
	dspRptr[0x4D] = RDSPReg4D;
	dspRptr[0x4E] = RDSPReg4E;
	dspRptr[0x4F] = RDSPReg4F;
	dspRptr[0x50] = RDSPReg50;
	dspRptr[0x51] = RDSPReg51;
	dspRptr[0x52] = RDSPReg52;
	dspRptr[0x53] = RDSPReg53;
	dspRptr[0x54] = RDSPReg54;
	dspRptr[0x55] = RDSPReg55;
	dspRptr[0x56] = RDSPReg56;
	dspRptr[0x57] = RDSPReg57;
	dspRptr[0x58] = RDSPReg58;
	dspRptr[0x59] = RDSPReg59;
	dspRptr[0x5A] = RDSPReg5A;
	dspRptr[0x5B] = RDSPReg5B;
	dspRptr[0x5C] = RDSPReg5C;
	dspRptr[0x5D] = RDSPReg5D;
	dspRptr[0x5E] = RDSPReg5E;
	dspRptr[0x5F] = RDSPReg5F;
	dspRptr[0x60] = RDSPReg60;
	dspRptr[0x61] = RDSPReg61;
	dspRptr[0x62] = RDSPReg62;
	dspRptr[0x63] = RDSPReg63;
	dspRptr[0x64] = RDSPReg64;
	dspRptr[0x65] = RDSPReg65;
	dspRptr[0x66] = RDSPReg66;
	dspRptr[0x67] = RDSPReg67;
	dspRptr[0x68] = RDSPReg68;
	dspRptr[0x69] = RDSPReg69;
	dspRptr[0x6A] = RDSPReg6A;
	dspRptr[0x6B] = RDSPReg6B;
	dspRptr[0x6C] = RDSPReg6C;
	dspRptr[0x6D] = RDSPReg6D;
	dspRptr[0x6E] = RDSPReg6E;
	dspRptr[0x6F] = RDSPReg6F;
	dspRptr[0x70] = RDSPReg70;
	dspRptr[0x71] = RDSPReg71;
	dspRptr[0x72] = RDSPReg72;
	dspRptr[0x73] = RDSPReg73;
	dspRptr[0x74] = RDSPReg74;
	dspRptr[0x75] = RDSPReg75;
	dspRptr[0x76] = RDSPReg76;
	dspRptr[0x77] = RDSPReg77;
	dspRptr[0x78] = RDSPReg78;
	dspRptr[0x79] = RDSPReg79;
	dspRptr[0x7A] = RDSPReg7A;
	dspRptr[0x7B] = RDSPReg7B;
	dspRptr[0x7C] = RDSPReg7C;
	dspRptr[0x7D] = RDSPReg7D;
	dspRptr[0x7E] = RDSPReg7E;
	dspRptr[0x7F] = RDSPReg7F;
	dspRptr[0x80] = RDSPReg80;
	dspRptr[0x81] = RDSPReg81;
	dspRptr[0x82] = RDSPReg82;
	dspRptr[0x83] = RDSPReg83;
	dspRptr[0x84] = RDSPReg84;
	dspRptr[0x85] = RDSPReg85;
	dspRptr[0x86] = RDSPReg86;
	dspRptr[0x87] = RDSPReg87;
	dspRptr[0x88] = RDSPReg88;
	dspRptr[0x89] = RDSPReg89;
	dspRptr[0x8A] = RDSPReg8A;
	dspRptr[0x8B] = RDSPReg8B;
	dspRptr[0x8C] = RDSPReg8C;
	dspRptr[0x8D] = RDSPReg8D;
	dspRptr[0x8E] = RDSPReg8E;
	dspRptr[0x8F] = RDSPReg8F;
	dspRptr[0x90] = RDSPReg90;
	dspRptr[0x91] = RDSPReg91;
	dspRptr[0x92] = RDSPReg92;
	dspRptr[0x93] = RDSPReg93;
	dspRptr[0x94] = RDSPReg94;
	dspRptr[0x95] = RDSPReg95;
	dspRptr[0x96] = RDSPReg96;
	dspRptr[0x97] = RDSPReg97;
	dspRptr[0x98] = RDSPReg98;
	dspRptr[0x99] = RDSPReg99;
	dspRptr[0x9A] = RDSPReg9A;
	dspRptr[0x9B] = RDSPReg9B;
	dspRptr[0x9C] = RDSPReg9C;
	dspRptr[0x9D] = RDSPReg9D;
	dspRptr[0x9E] = RDSPReg9E;
	dspRptr[0x9F] = RDSPReg9F;
	dspRptr[0xA0] = RDSPRegA0;
	dspRptr[0xA1] = RDSPRegA1;
	dspRptr[0xA2] = RDSPRegA2;
	dspRptr[0xA3] = RDSPRegA3;
	dspRptr[0xA4] = RDSPRegA4;
	dspRptr[0xA5] = RDSPRegA5;
	dspRptr[0xA6] = RDSPRegA6;
	dspRptr[0xA7] = RDSPRegA7;
	dspRptr[0xA8] = RDSPRegA8;
	dspRptr[0xA9] = RDSPRegA9;
	dspRptr[0xAA] = RDSPRegAA;
	dspRptr[0xAB] = RDSPRegAB;
	dspRptr[0xAC] = RDSPRegAC;
	dspRptr[0xAD] = RDSPRegAD;
	dspRptr[0xAE] = RDSPRegAE;
	dspRptr[0xAF] = RDSPRegAF;
	dspRptr[0xB0] = RDSPRegB0;
	dspRptr[0xB1] = RDSPRegB1;
	dspRptr[0xB2] = RDSPRegB2;
	dspRptr[0xB3] = RDSPRegB3;
	dspRptr[0xB4] = RDSPRegB4;
	dspRptr[0xB5] = RDSPRegB5;
	dspRptr[0xB6] = RDSPRegB6;
	dspRptr[0xB7] = RDSPRegB7;
	dspRptr[0xB8] = RDSPRegB8;
	dspRptr[0xB9] = RDSPRegB9;
	dspRptr[0xBA] = RDSPRegBA;
	dspRptr[0xBB] = RDSPRegBB;
	dspRptr[0xBC] = RDSPRegBC;
	dspRptr[0xBD] = RDSPRegBD;
	dspRptr[0xBE] = RDSPRegBE;
	dspRptr[0xBF] = RDSPRegBF;
	dspRptr[0xC0] = RDSPRegC0;
	dspRptr[0xC1] = RDSPRegC1;
	dspRptr[0xC2] = RDSPRegC2;
	dspRptr[0xC3] = RDSPRegC3;
	dspRptr[0xC4] = RDSPRegC4;
	dspRptr[0xC5] = RDSPRegC5;
	dspRptr[0xC6] = RDSPRegC6;
	dspRptr[0xC7] = RDSPRegC7;
	dspRptr[0xC8] = RDSPRegC8;
	dspRptr[0xC9] = RDSPRegC9;
	dspRptr[0xCA] = RDSPRegCA;
	dspRptr[0xCB] = RDSPRegCB;
	dspRptr[0xCC] = RDSPRegCC;
	dspRptr[0xCD] = RDSPRegCD;
	dspRptr[0xCE] = RDSPRegCE;
	dspRptr[0xCF] = RDSPRegCF;
	dspRptr[0xD0] = RDSPRegD0;
	dspRptr[0xD1] = RDSPRegD1;
	dspRptr[0xD2] = RDSPRegD2;
	dspRptr[0xD3] = RDSPRegD3;
	dspRptr[0xD4] = RDSPRegD4;
	dspRptr[0xD5] = RDSPRegD5;
	dspRptr[0xD6] = RDSPRegD6;
	dspRptr[0xD7] = RDSPRegD7;
	dspRptr[0xD8] = RDSPRegD8;
	dspRptr[0xD9] = RDSPRegD9;
	dspRptr[0xDA] = RDSPRegDA;
	dspRptr[0xDB] = RDSPRegDB;
	dspRptr[0xDC] = RDSPRegDC;
	dspRptr[0xDD] = RDSPRegDD;
	dspRptr[0xDE] = RDSPRegDE;
	dspRptr[0xDF] = RDSPRegDF;
	dspRptr[0xE0] = RDSPRegE0;
	dspRptr[0xE1] = RDSPRegE1;
	dspRptr[0xE2] = RDSPRegE2;
	dspRptr[0xE3] = RDSPRegE3;
	dspRptr[0xE4] = RDSPRegE4;
	dspRptr[0xE5] = RDSPRegE5;
	dspRptr[0xE6] = RDSPRegE6;
	dspRptr[0xE7] = RDSPRegE7;
	dspRptr[0xE8] = RDSPRegE8;
	dspRptr[0xE9] = RDSPRegE9;
	dspRptr[0xEA] = RDSPRegEA;
	dspRptr[0xEB] = RDSPRegEB;
	dspRptr[0xEC] = RDSPRegEC;
	dspRptr[0xED] = RDSPRegED;
	dspRptr[0xEE] = RDSPRegEE;
	dspRptr[0xEF] = RDSPRegEF;
	dspRptr[0xF0] = RDSPRegF0;
	dspRptr[0xF1] = RDSPRegF1;
	dspRptr[0xF2] = RDSPRegF2;
	dspRptr[0xF3] = RDSPRegF3;
	dspRptr[0xF4] = RDSPRegF4;
	dspRptr[0xF5] = RDSPRegF5;
	dspRptr[0xF6] = RDSPRegF6;
	dspRptr[0xF7] = RDSPRegF7;
	dspRptr[0xF8] = RDSPRegF8;
	dspRptr[0xF9] = RDSPRegF9;
	dspRptr[0xFA] = RDSPRegFA;
	dspRptr[0xFB] = RDSPRegFB;
	dspRptr[0xFC] = RDSPRegFC;
	dspRptr[0xFD] = RDSPRegFD;
	dspRptr[0xFE] = RDSPRegFE;
	dspRptr[0xFF] = RDSPRegFF;

	dspWptr[0x00] = WDSPReg00;
	dspWptr[0x01] = WDSPReg01;
	dspWptr[0x02] = WDSPReg02;
	dspWptr[0x03] = WDSPReg03;
	dspWptr[0x04] = WDSPReg04;
	dspWptr[0x05] = WDSPReg05;
	dspWptr[0x06] = WDSPReg06;
	dspWptr[0x07] = WDSPReg07;
	dspWptr[0x08] = WDSPReg08;
	dspWptr[0x09] = WDSPReg09;
	dspWptr[0x0A] = WDSPReg0A;
	dspWptr[0x0B] = WDSPReg0B;
	dspWptr[0x0C] = WDSPReg0C;
	dspWptr[0x0D] = WDSPReg0D;
	dspWptr[0x0E] = WDSPReg0E;
	dspWptr[0x0F] = WDSPReg0F;
	dspWptr[0x10] = WDSPReg10;
	dspWptr[0x11] = WDSPReg11;
	dspWptr[0x12] = WDSPReg12;
	dspWptr[0x13] = WDSPReg13;
	dspWptr[0x14] = WDSPReg14;
	dspWptr[0x15] = WDSPReg15;
	dspWptr[0x16] = WDSPReg16;
	dspWptr[0x17] = WDSPReg17;
	dspWptr[0x18] = WDSPReg18;
	dspWptr[0x19] = WDSPReg19;
	dspWptr[0x1A] = WDSPReg1A;
	dspWptr[0x1B] = WDSPReg1B;
	dspWptr[0x1C] = WDSPReg1C;
	dspWptr[0x1D] = WDSPReg1D;
	dspWptr[0x1E] = WDSPReg1E;
	dspWptr[0x1F] = WDSPReg1F;
	dspWptr[0x20] = WDSPReg20;
	dspWptr[0x21] = WDSPReg21;
	dspWptr[0x22] = WDSPReg22;
	dspWptr[0x23] = WDSPReg23;
	dspWptr[0x24] = WDSPReg24;
	dspWptr[0x25] = WDSPReg25;
	dspWptr[0x26] = WDSPReg26;
	dspWptr[0x27] = WDSPReg27;
	dspWptr[0x28] = WDSPReg28;
	dspWptr[0x29] = WDSPReg29;
	dspWptr[0x2A] = WDSPReg2A;
	dspWptr[0x2B] = WDSPReg2B;
	dspWptr[0x2C] = WDSPReg2C;
	dspWptr[0x2D] = WDSPReg2D;
	dspWptr[0x2E] = WDSPReg2E;
	dspWptr[0x2F] = WDSPReg2F;
	dspWptr[0x30] = WDSPReg30;
	dspWptr[0x31] = WDSPReg31;
	dspWptr[0x32] = WDSPReg32;
	dspWptr[0x33] = WDSPReg33;
	dspWptr[0x34] = WDSPReg34;
	dspWptr[0x35] = WDSPReg35;
	dspWptr[0x36] = WDSPReg36;
	dspWptr[0x37] = WDSPReg37;
	dspWptr[0x38] = WDSPReg38;
	dspWptr[0x39] = WDSPReg39;
	dspWptr[0x3A] = WDSPReg3A;
	dspWptr[0x3B] = WDSPReg3B;
	dspWptr[0x3C] = WDSPReg3C;
	dspWptr[0x3D] = WDSPReg3D;
	dspWptr[0x3E] = WDSPReg3E;
	dspWptr[0x3F] = WDSPReg3F;
	dspWptr[0x40] = WDSPReg40;
	dspWptr[0x41] = WDSPReg41;
	dspWptr[0x42] = WDSPReg42;
	dspWptr[0x43] = WDSPReg43;
	dspWptr[0x44] = WDSPReg44;
	dspWptr[0x45] = WDSPReg45;
	dspWptr[0x46] = WDSPReg46;
	dspWptr[0x47] = WDSPReg47;
	dspWptr[0x48] = WDSPReg48;
	dspWptr[0x49] = WDSPReg49;
	dspWptr[0x4A] = WDSPReg4A;
	dspWptr[0x4B] = WDSPReg4B;
	dspWptr[0x4C] = WDSPReg4C;
	dspWptr[0x4D] = WDSPReg4D;
	dspWptr[0x4E] = WDSPReg4E;
	dspWptr[0x4F] = WDSPReg4F;
	dspWptr[0x50] = WDSPReg50;
	dspWptr[0x51] = WDSPReg51;
	dspWptr[0x52] = WDSPReg52;
	dspWptr[0x53] = WDSPReg53;
	dspWptr[0x54] = WDSPReg54;
	dspWptr[0x55] = WDSPReg55;
	dspWptr[0x56] = WDSPReg56;
	dspWptr[0x57] = WDSPReg57;
	dspWptr[0x58] = WDSPReg58;
	dspWptr[0x59] = WDSPReg59;
	dspWptr[0x5A] = WDSPReg5A;
	dspWptr[0x5B] = WDSPReg5B;
	dspWptr[0x5C] = WDSPReg5C;
	dspWptr[0x5D] = WDSPReg5D;
	dspWptr[0x5E] = WDSPReg5E;
	dspWptr[0x5F] = WDSPReg5F;
	dspWptr[0x60] = WDSPReg60;
	dspWptr[0x61] = WDSPReg61;
	dspWptr[0x62] = WDSPReg62;
	dspWptr[0x63] = WDSPReg63;
	dspWptr[0x64] = WDSPReg64;
	dspWptr[0x65] = WDSPReg65;
	dspWptr[0x66] = WDSPReg66;
	dspWptr[0x67] = WDSPReg67;
	dspWptr[0x68] = WDSPReg68;
	dspWptr[0x69] = WDSPReg69;
	dspWptr[0x6A] = WDSPReg6A;
	dspWptr[0x6B] = WDSPReg6B;
	dspWptr[0x6C] = WDSPReg6C;
	dspWptr[0x6D] = WDSPReg6D;
	dspWptr[0x6E] = WDSPReg6E;
	dspWptr[0x6F] = WDSPReg6F;
	dspWptr[0x70] = WDSPReg70;
	dspWptr[0x71] = WDSPReg71;
	dspWptr[0x72] = WDSPReg72;
	dspWptr[0x73] = WDSPReg73;
	dspWptr[0x74] = WDSPReg74;
	dspWptr[0x75] = WDSPReg75;
	dspWptr[0x76] = WDSPReg76;
	dspWptr[0x77] = WDSPReg77;
	dspWptr[0x78] = WDSPReg78;
	dspWptr[0x79] = WDSPReg79;
	dspWptr[0x7A] = WDSPReg7A;
	dspWptr[0x7B] = WDSPReg7B;
	dspWptr[0x7C] = WDSPReg7C;
	dspWptr[0x7D] = WDSPReg7D;
	dspWptr[0x7E] = WDSPReg7E;
	dspWptr[0x7F] = WDSPReg7F;
	dspWptr[0x80] = WDSPReg80;
	dspWptr[0x81] = WDSPReg81;
	dspWptr[0x82] = WDSPReg82;
	dspWptr[0x83] = WDSPReg83;
	dspWptr[0x84] = WDSPReg84;
	dspWptr[0x85] = WDSPReg85;
	dspWptr[0x86] = WDSPReg86;
	dspWptr[0x87] = WDSPReg87;
	dspWptr[0x88] = WDSPReg88;
	dspWptr[0x89] = WDSPReg89;
	dspWptr[0x8A] = WDSPReg8A;
	dspWptr[0x8B] = WDSPReg8B;
	dspWptr[0x8C] = WDSPReg8C;
	dspWptr[0x8D] = WDSPReg8D;
	dspWptr[0x8E] = WDSPReg8E;
	dspWptr[0x8F] = WDSPReg8F;
	dspWptr[0x90] = WDSPReg90;
	dspWptr[0x91] = WDSPReg91;
	dspWptr[0x92] = WDSPReg92;
	dspWptr[0x93] = WDSPReg93;
	dspWptr[0x94] = WDSPReg94;
	dspWptr[0x95] = WDSPReg95;
	dspWptr[0x96] = WDSPReg96;
	dspWptr[0x97] = WDSPReg97;
	dspWptr[0x98] = WDSPReg98;
	dspWptr[0x99] = WDSPReg99;
	dspWptr[0x9A] = WDSPReg9A;
	dspWptr[0x9B] = WDSPReg9B;
	dspWptr[0x9C] = WDSPReg9C;
	dspWptr[0x9D] = WDSPReg9D;
	dspWptr[0x9E] = WDSPReg9E;
	dspWptr[0x9F] = WDSPReg9F;
	dspWptr[0xA0] = WDSPRegA0;
	dspWptr[0xA1] = WDSPRegA1;
	dspWptr[0xA2] = WDSPRegA2;
	dspWptr[0xA3] = WDSPRegA3;
	dspWptr[0xA4] = WDSPRegA4;
	dspWptr[0xA5] = WDSPRegA5;
	dspWptr[0xA6] = WDSPRegA6;
	dspWptr[0xA7] = WDSPRegA7;
	dspWptr[0xA8] = WDSPRegA8;
	dspWptr[0xA9] = WDSPRegA9;
	dspWptr[0xAA] = WDSPRegAA;
	dspWptr[0xAB] = WDSPRegAB;
	dspWptr[0xAC] = WDSPRegAC;
	dspWptr[0xAD] = WDSPRegAD;
	dspWptr[0xAE] = WDSPRegAE;
	dspWptr[0xAF] = WDSPRegAF;
	dspWptr[0xB0] = WDSPRegB0;
	dspWptr[0xB1] = WDSPRegB1;
	dspWptr[0xB2] = WDSPRegB2;
	dspWptr[0xB3] = WDSPRegB3;
	dspWptr[0xB4] = WDSPRegB4;
	dspWptr[0xB5] = WDSPRegB5;
	dspWptr[0xB6] = WDSPRegB6;
	dspWptr[0xB7] = WDSPRegB7;
	dspWptr[0xB8] = WDSPRegB8;
	dspWptr[0xB9] = WDSPRegB9;
	dspWptr[0xBA] = WDSPRegBA;
	dspWptr[0xBB] = WDSPRegBB;
	dspWptr[0xBC] = WDSPRegBC;
	dspWptr[0xBD] = WDSPRegBD;
	dspWptr[0xBE] = WDSPRegBE;
	dspWptr[0xBF] = WDSPRegBF;
	dspWptr[0xC0] = WDSPRegC0;
	dspWptr[0xC1] = WDSPRegC1;
	dspWptr[0xC2] = WDSPRegC2;
	dspWptr[0xC3] = WDSPRegC3;
	dspWptr[0xC4] = WDSPRegC4;
	dspWptr[0xC5] = WDSPRegC5;
	dspWptr[0xC6] = WDSPRegC6;
	dspWptr[0xC7] = WDSPRegC7;
	dspWptr[0xC8] = WDSPRegC8;
	dspWptr[0xC9] = WDSPRegC9;
	dspWptr[0xCA] = WDSPRegCA;
	dspWptr[0xCB] = WDSPRegCB;
	dspWptr[0xCC] = WDSPRegCC;
	dspWptr[0xCD] = WDSPRegCD;
	dspWptr[0xCE] = WDSPRegCE;
	dspWptr[0xCF] = WDSPRegCF;
	dspWptr[0xD0] = WDSPRegD0;
	dspWptr[0xD1] = WDSPRegD1;
	dspWptr[0xD2] = WDSPRegD2;
	dspWptr[0xD3] = WDSPRegD3;
	dspWptr[0xD4] = WDSPRegD4;
	dspWptr[0xD5] = WDSPRegD5;
	dspWptr[0xD6] = WDSPRegD6;
	dspWptr[0xD7] = WDSPRegD7;
	dspWptr[0xD8] = WDSPRegD8;
	dspWptr[0xD9] = WDSPRegD9;
	dspWptr[0xDA] = WDSPRegDA;
	dspWptr[0xDB] = WDSPRegDB;
	dspWptr[0xDC] = WDSPRegDC;
	dspWptr[0xDD] = WDSPRegDD;
	dspWptr[0xDE] = WDSPRegDE;
	dspWptr[0xDF] = WDSPRegDF;
	dspWptr[0xE0] = WDSPRegE0;
	dspWptr[0xE1] = WDSPRegE1;
	dspWptr[0xE2] = WDSPRegE2;
	dspWptr[0xE3] = WDSPRegE3;
	dspWptr[0xE4] = WDSPRegE4;
	dspWptr[0xE5] = WDSPRegE5;
	dspWptr[0xE6] = WDSPRegE6;
	dspWptr[0xE7] = WDSPRegE7;
	dspWptr[0xE8] = WDSPRegE8;
	dspWptr[0xE9] = WDSPRegE9;
	dspWptr[0xEA] = WDSPRegEA;
	dspWptr[0xEB] = WDSPRegEB;
	dspWptr[0xEC] = WDSPRegEC;
	dspWptr[0xED] = WDSPRegED;
	dspWptr[0xEE] = WDSPRegEE;
	dspWptr[0xEF] = WDSPRegEF;
	dspWptr[0xF0] = WDSPRegF0;
	dspWptr[0xF1] = WDSPRegF1;
	dspWptr[0xF2] = WDSPRegF2;
	dspWptr[0xF3] = WDSPRegF3;
	dspWptr[0xF4] = WDSPRegF4;
	dspWptr[0xF5] = WDSPRegF5;
	dspWptr[0xF6] = WDSPRegF6;
	dspWptr[0xF7] = WDSPRegF7;
	dspWptr[0xF8] = WDSPRegF8;
	dspWptr[0xF9] = WDSPRegF9;
	dspWptr[0xFA] = WDSPRegFA;
	dspWptr[0xFB] = WDSPRegFB;
	dspWptr[0xFC] = WDSPRegFC;
	dspWptr[0xFD] = WDSPRegFD;
	dspWptr[0xFE] = WDSPRegFE;
	dspWptr[0xFF] = WDSPRegFF;

	// first fill all pointer to an invalid access function
	// XXX seems to be redundant, all entries are overwritten below
	for (eop** i = opcjmptab; i != endof(opcjmptab); ++i) *i = Invalidopcode;

	// now fill the table
	opcjmptab[0x00] = Op00;
	opcjmptab[0x01] = Op01;
	opcjmptab[0x02] = Op02;
	opcjmptab[0x03] = Op03;
	opcjmptab[0x04] = Op04;
	opcjmptab[0x05] = Op05;
	opcjmptab[0x06] = Op06;
	opcjmptab[0x07] = Op07;
	opcjmptab[0x08] = Op08;
	opcjmptab[0x09] = Op09;
	opcjmptab[0x0A] = Op0A;
	opcjmptab[0x0B] = Op0B;
	opcjmptab[0x0C] = Op0C;
	opcjmptab[0x0D] = Op0D;
	opcjmptab[0x0E] = Op0E;
	opcjmptab[0x0F] = Op0F;
	opcjmptab[0x10] = Op10;
	opcjmptab[0x11] = Op11;
	opcjmptab[0x12] = Op12;
	opcjmptab[0x13] = Op13;
	opcjmptab[0x14] = Op14;
	opcjmptab[0x15] = Op15;
	opcjmptab[0x16] = Op16;
	opcjmptab[0x17] = Op17;
	opcjmptab[0x18] = Op18;
	opcjmptab[0x19] = Op19;
	opcjmptab[0x1A] = Op1A;
	opcjmptab[0x1B] = Op1B;
	opcjmptab[0x1C] = Op1C;
	opcjmptab[0x1D] = Op1D;
	opcjmptab[0x1E] = Op1E;
	opcjmptab[0x1F] = Op1F;
	opcjmptab[0x20] = Op20;
	opcjmptab[0x21] = Op21;
	opcjmptab[0x22] = Op22;
	opcjmptab[0x23] = Op23;
	opcjmptab[0x24] = Op24;
	opcjmptab[0x25] = Op25;
	opcjmptab[0x26] = Op26;
	opcjmptab[0x27] = Op27;
	opcjmptab[0x28] = Op28;
	opcjmptab[0x29] = Op29;
	opcjmptab[0x2A] = Op2A;
	opcjmptab[0x2B] = Op2B;
	opcjmptab[0x2C] = Op2C;
	opcjmptab[0x2D] = Op2D;
	opcjmptab[0x2E] = Op2E;
	opcjmptab[0x2F] = Op2F;
	opcjmptab[0x30] = Op30;
	opcjmptab[0x31] = Op31;
	opcjmptab[0x32] = Op32;
	opcjmptab[0x33] = Op33;
	opcjmptab[0x34] = Op34;
	opcjmptab[0x35] = Op35;
	opcjmptab[0x36] = Op36;
	opcjmptab[0x37] = Op37;
	opcjmptab[0x38] = Op38;
	opcjmptab[0x39] = Op39;
	opcjmptab[0x3A] = Op3A;
	opcjmptab[0x3B] = Op3B;
	opcjmptab[0x3C] = Op3C;
	opcjmptab[0x3D] = Op3D;
	opcjmptab[0x3E] = Op3E;
	opcjmptab[0x3F] = Op3F;
	opcjmptab[0x40] = Op40;
	opcjmptab[0x41] = Op41;
	opcjmptab[0x42] = Op42;
	opcjmptab[0x43] = Op43;
	opcjmptab[0x44] = Op44;
	opcjmptab[0x45] = Op45;
	opcjmptab[0x46] = Op46;
	opcjmptab[0x47] = Op47;
	opcjmptab[0x48] = Op48;
	opcjmptab[0x49] = Op49;
	opcjmptab[0x4A] = Op4A;
	opcjmptab[0x4B] = Op4B;
	opcjmptab[0x4C] = Op4C;
	opcjmptab[0x4D] = Op4D;
	opcjmptab[0x4E] = Op4E;
	opcjmptab[0x4F] = Op4F;
	opcjmptab[0x50] = Op50;
	opcjmptab[0x51] = Op51;
	opcjmptab[0x52] = Op52;
	opcjmptab[0x53] = Op53;
	opcjmptab[0x54] = Op54;
	opcjmptab[0x55] = Op55;
	opcjmptab[0x56] = Op56;
	opcjmptab[0x57] = Op57;
	opcjmptab[0x58] = Op58;
	opcjmptab[0x59] = Op59;
	opcjmptab[0x5A] = Op5A;
	opcjmptab[0x5B] = Op5B;
	opcjmptab[0x5C] = Op5C;
	opcjmptab[0x5D] = Op5D;
	opcjmptab[0x5E] = Op5E;
	opcjmptab[0x5F] = Op5F;
	opcjmptab[0x60] = Op60;
	opcjmptab[0x61] = Op61;
	opcjmptab[0x62] = Op62;
	opcjmptab[0x63] = Op63;
	opcjmptab[0x64] = Op64;
	opcjmptab[0x65] = Op65;
	opcjmptab[0x66] = Op66;
	opcjmptab[0x67] = Op67;
	opcjmptab[0x68] = Op68;
	opcjmptab[0x69] = Op69;
	opcjmptab[0x6A] = Op6A;
	opcjmptab[0x6B] = Op6B;
	opcjmptab[0x6C] = Op6C;
	opcjmptab[0x6D] = Op6D;
	opcjmptab[0x6E] = Op6E;
	opcjmptab[0x6F] = Op6F;
	opcjmptab[0x70] = Op70;
	opcjmptab[0x71] = Op71;
	opcjmptab[0x72] = Op72;
	opcjmptab[0x73] = Op73;
	opcjmptab[0x74] = Op74;
	opcjmptab[0x75] = Op75;
	opcjmptab[0x76] = Op76;
	opcjmptab[0x77] = Op77;
	opcjmptab[0x78] = Op78;
	opcjmptab[0x79] = Op79;
	opcjmptab[0x7A] = Op7A;
	opcjmptab[0x7B] = Op7B;
	opcjmptab[0x7C] = Op7C;
	opcjmptab[0x7D] = Op7D;
	opcjmptab[0x7E] = Op7E;
	opcjmptab[0x7F] = Op7F;
	opcjmptab[0x80] = Op80;
	opcjmptab[0x81] = Op81;
	opcjmptab[0x82] = Op82;
	opcjmptab[0x83] = Op83;
	opcjmptab[0x84] = Op84;
	opcjmptab[0x85] = Op85;
	opcjmptab[0x86] = Op86;
	opcjmptab[0x87] = Op87;
	opcjmptab[0x88] = Op88;
	opcjmptab[0x89] = Op89;
	opcjmptab[0x8A] = Op8A;
	opcjmptab[0x8B] = Op8B;
	opcjmptab[0x8C] = Op8C;
	opcjmptab[0x8D] = Op8D;
	opcjmptab[0x8E] = Op8E;
	opcjmptab[0x8F] = Op8F;
	opcjmptab[0x90] = Op90;
	opcjmptab[0x91] = Op91;
	opcjmptab[0x92] = Op92;
	opcjmptab[0x93] = Op93;
	opcjmptab[0x94] = Op94;
	opcjmptab[0x95] = Op95;
	opcjmptab[0x96] = Op96;
	opcjmptab[0x97] = Op97;
	opcjmptab[0x98] = Op98;
	opcjmptab[0x99] = Op99;
	opcjmptab[0x9A] = Op9A;
	opcjmptab[0x9B] = Op9B;
	opcjmptab[0x9C] = Op9C;
	opcjmptab[0x9D] = Op9D;
	opcjmptab[0x9E] = Op9E;
	opcjmptab[0x9F] = Op9F;
	opcjmptab[0xA0] = OpA0;
	opcjmptab[0xA1] = OpA1;
	opcjmptab[0xA2] = OpA2;
	opcjmptab[0xA3] = OpA3;
	opcjmptab[0xA4] = OpA4;
	opcjmptab[0xA5] = OpA5;
	opcjmptab[0xA6] = OpA6;
	opcjmptab[0xA7] = OpA7;
	opcjmptab[0xA8] = OpA8;
	opcjmptab[0xA9] = OpA9;
	opcjmptab[0xAA] = OpAA;
	opcjmptab[0xAB] = OpAB;
	opcjmptab[0xAC] = OpAC;
	opcjmptab[0xAD] = OpAD;
	opcjmptab[0xAE] = OpAE;
	opcjmptab[0xAF] = OpAF;
	opcjmptab[0xB0] = OpB0;
	opcjmptab[0xB1] = OpB1;
	opcjmptab[0xB2] = OpB2;
	opcjmptab[0xB3] = OpB3;
	opcjmptab[0xB4] = OpB4;
	opcjmptab[0xB5] = OpB5;
	opcjmptab[0xB6] = OpB6;
	opcjmptab[0xB7] = OpB7;
	opcjmptab[0xB8] = OpB8;
	opcjmptab[0xB9] = OpB9;
	opcjmptab[0xBA] = OpBA;
	opcjmptab[0xBB] = OpBB;
	opcjmptab[0xBC] = OpBC;
	opcjmptab[0xBD] = OpBD;
	opcjmptab[0xBE] = OpBE;
	opcjmptab[0xBF] = OpBF;
	opcjmptab[0xC0] = OpC0;
	opcjmptab[0xC1] = OpC1;
	opcjmptab[0xC2] = OpC2;
	opcjmptab[0xC3] = OpC3;
	opcjmptab[0xC4] = OpC4;
	opcjmptab[0xC5] = OpC5;
	opcjmptab[0xC6] = OpC6;
	opcjmptab[0xC7] = OpC7;
	opcjmptab[0xC8] = OpC8;
	opcjmptab[0xC9] = OpC9;
	opcjmptab[0xCA] = OpCA;
	opcjmptab[0xCB] = OpCB;
	opcjmptab[0xCC] = OpCC;
	opcjmptab[0xCD] = OpCD;
	opcjmptab[0xCE] = OpCE;
	opcjmptab[0xCF] = OpCF;
	opcjmptab[0xD0] = OpD0;
	opcjmptab[0xD1] = OpD1;
	opcjmptab[0xD2] = OpD2;
	opcjmptab[0xD3] = OpD3;
	opcjmptab[0xD4] = OpD4;
	opcjmptab[0xD5] = OpD5;
	opcjmptab[0xD6] = OpD6;
	opcjmptab[0xD7] = OpD7;
	opcjmptab[0xD8] = OpD8;
	opcjmptab[0xD9] = OpD9;
	opcjmptab[0xDA] = OpDA;
	opcjmptab[0xDB] = OpDB;
	opcjmptab[0xDC] = OpDC;
	opcjmptab[0xDD] = OpDD;
	opcjmptab[0xDE] = OpDE;
	opcjmptab[0xDF] = OpDF;
	opcjmptab[0xE0] = OpE0;
	opcjmptab[0xE1] = OpE1;
	opcjmptab[0xE2] = OpE2;
	opcjmptab[0xE3] = OpE3;
	opcjmptab[0xE4] = OpE4;
	opcjmptab[0xE5] = OpE5;
	opcjmptab[0xE6] = OpE6;
	opcjmptab[0xE7] = OpE7;
	opcjmptab[0xE8] = OpE8;
	opcjmptab[0xE9] = OpE9;
	opcjmptab[0xEA] = OpEA;
	opcjmptab[0xEB] = OpEB;
	opcjmptab[0xEC] = OpEC;
	opcjmptab[0xED] = OpED;
	opcjmptab[0xEE] = OpEE;
	opcjmptab[0xEF] = OpEF;
	opcjmptab[0xF0] = OpF0;
	opcjmptab[0xF1] = OpF1;
	opcjmptab[0xF2] = OpF2;
	opcjmptab[0xF3] = OpF3;
	opcjmptab[0xF4] = OpF4;
	opcjmptab[0xF5] = OpF5;
	opcjmptab[0xF6] = OpF6;
	opcjmptab[0xF7] = OpF7;
	opcjmptab[0xF8] = OpF8;
	opcjmptab[0xF9] = OpF9;
	opcjmptab[0xFA] = OpFA;
	opcjmptab[0xFB] = OpFB;
	opcjmptab[0xFC] = OpFC;
	opcjmptab[0xFD] = OpFD;
	opcjmptab[0xFE] = OpFE;
	opcjmptab[0xFF] = OpFF;

#ifdef __MSDOS__
	asm_call(SB_alloc_dma);
#endif
}
