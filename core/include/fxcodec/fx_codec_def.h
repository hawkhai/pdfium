// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_INCLUDE_FXCODEC_FX_CODEC_DEF_H_
#define CORE_INCLUDE_FXCODEC_FX_CODEC_DEF_H_

enum FXCODEC_IMAGE_TYPE {
    FXCODEC_IMAGE_UNKNOWN = 0,
    FXCODEC_IMAGE_BMP,
    FXCODEC_IMAGE_JPG,
    FXCODEC_IMAGE_PNG,
    FXCODEC_IMAGE_GIF,
    FXCODEC_IMAGE_TIF,
    FXCODEC_IMAGE_MAX
};
enum FXCODEC_STATUS {
    FXCODEC_STATUS_ERROR = -1,
    FXCODEC_STATUS_FRAME_READY,
    FXCODEC_STATUS_FRAME_TOBECONTINUE,
    FXCODEC_STATUS_DECODE_READY,
    FXCODEC_STATUS_DECODE_TOBECONTINUE,
    FXCODEC_STATUS_DECODE_FINISH,
    FXCODEC_STATUS_ERR_MEMORY,
    FXCODEC_STATUS_ERR_READ,
    FXCODEC_STATUS_ERR_FLUSH,
    FXCODEC_STATUS_ERR_FORMAT,
    FXCODEC_STATUS_ERR_PARAMS
};
#define JP2_SPACE_INVALID	-1
#define JPX_SPACE_INVALID	-1
#define JP2_SPACE_bilevel1	0
#define JP2_SPACE_YCbCr1	1
#define JP2_SPACE_YCbCr2	3
#define JP2_SPACE_YCbCr3	4
#define JP2_SPACE_PhotoYCC	9
#define JP2_SPACE_CMY		11
#define JP2_SPACE_CMYK		12
#define JP2_SPACE_YCCK		13
#define JP2_SPACE_CIELab	14
#define JP2_SPACE_bilevel2	15
#define JP2_SPACE_sRGB		16
#define JP2_SPACE_sLUM		17
#define JP2_SPACE_sYCC		18
#define JP2_SPACE_CIEJab	19
#define JP2_SPACE_esRGB		20
#define JP2_SPACE_ROMMRGB	21
#define JP2_SPACE_YPbPr60	22
#define JP2_SPACE_YPbPr50	23
#define JP2_SPACE_esYCC		24
#define JP2_SPACE_iccLUM	100
#define JP2_SPACE_iccRGB	101
#define Icc_INTENT_PERCEPTUAL				0
#define Icc_INTENT_RELATIVE_COLORIMETRIC	1
#define Icc_INTENT_SATURATION				2
#define Icc_INTENT_ABSOLUTE_COLORIMETRIC	3
#define Icc_FORMAT_DEFAULT					0
#define Icc_FORMAT_SWAP						(1<<10)
#define Icc_FLAGS_DEFAULT					0x0000
#define Icc_FLAGS_BLACKPOINTCOMPENSATION	0x2000
#define Icc_FLAGS_NOWHITEONWHITEFIXUP		0x0004
#define Icc_FLAGS_HIGHRESPRECALC			0x0400
#define Icc_FLAGS_LOWRESPRECALC				0x0800
#define Icc_FLAGS_GAMUTCHECK				0x1000
#define Icc_FLAGS_SOFTPROOFING				0x4000
#define Icc_PARAMTYPE_NONE					0
#define Icc_PARAMTYPE_BUFFER				1
#define Icc_PARAMTYPE_PARAM					2
enum FXCODEC_RESUNIT {
    FXCODEC_RESUNIT_NONE = 0,
    FXCODEC_RESUNIT_INCH,
    FXCODEC_RESUNIT_CENTIMETER,
    FXCODEC_RESUNIT_METER
};
#define EXIFTAG_USHORT_RESUNIT				296
#define EXIFTAG_FLOAT_DPIX					282
#define EXIFTAG_FLOAT_DPIY					283
#define EXIFTAG_USHORT_ORIENTATION			274
#define EXIFTAG_STRING_MANUFACTURER			271
#define EXIFTAG_STRING_MODULE				272
#define EXIFTAG_STRING_SOFTWARE				305
#define EXIFTAG_STRING_IAMGEDESCRIPTION		270
#define EXIFTAG_STRING_DATETIME				306
#define EXIFTAG_STRING_COPYRIGHT			33432

#endif  // CORE_INCLUDE_FXCODEC_FX_CODEC_DEF_H_
