// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
 
// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_INCLUDE_FXCODEC_FX_CODEC_H_
#define CORE_INCLUDE_FXCODEC_FX_CODEC_H_

#include "../fxcrt/fx_ext.h"
#include "fx_codec_def.h"
#include "fx_codec_provider.h"

class CFX_DIBSource;
class ICodec_ScanlineDecoder;
class ICodec_ProgressiveDecoder;
class ICodec_BasicModule;
class ICodec_FaxModule;
class ICodec_JpegModule;
class ICodec_JpxModule;
class ICodec_Jbig2Module;
class ICodec_IccModule;
class ICodec_FlateModule;
class ICodec_Jbig2Encoder;
class ICodec_PngModule;
class ICodec_GifModule;
class ICodec_BmpModule;
class ICodec_TiffModule;
class CFX_DIBAttribute;
class ICodec_ScanlineDecoder;
class CCodec_ModuleMgr 
{
public:

    static CCodec_ModuleMgr*	Create();

    void				Destroy();

    void				InitJbig2Decoder();

    void				InitJpxDecoder();


    void				InitIccDecoder();


    ICodec_ProgressiveDecoder*	CreateProgressiveDecoder();

    ICodec_Jbig2Encoder*		CreateJbig2Encoder();
protected:
    CCodec_ModuleMgr();
    ~CCodec_ModuleMgr();
public:
    ICodec_BasicModule*	GetBasicModule()
    {
        return m_pBasicModule;
    }
    ICodec_FaxModule*	GetFaxModule()
    {
        return m_pFaxModule;
    }
    ICodec_JpegModule*	GetJpegModule()
    {
        return m_pJpegModule;
    }
    ICodec_JpxModule*	GetJpxModule()
    {
        return m_pJpxModule;
    }
    ICodec_Jbig2Module*	GetJbig2Module()
    {
        return m_pJbig2Module;
    }
    ICodec_IccModule*	GetIccModule()
    {
        return m_pIccModule;
    }
    ICodec_FlateModule*	GetFlateModule()
    {
        return m_pFlateModule;
    }
    ICodec_PngModule*	GetPngModule()
    {
        return m_pPngModule;
    }
    ICodec_GifModule*	GetGifModule()
    {
        return m_pGifModule;
    }
    ICodec_BmpModule*	GetBmpModule()
    {
        return m_pBmpModule;
    }
    ICodec_TiffModule*	GetTiffModule()
    {
        return m_pTiffModule;
    }
protected:
    ICodec_BasicModule*	m_pBasicModule;
    ICodec_FaxModule*	m_pFaxModule;
    ICodec_JpegModule*	m_pJpegModule;
    ICodec_JpxModule*	m_pJpxModule;
    ICodec_Jbig2Module*	m_pJbig2Module;
    ICodec_IccModule*	m_pIccModule;
    ICodec_FlateModule*	m_pFlateModule;
    ICodec_PngModule*	m_pPngModule;
    ICodec_GifModule*	m_pGifModule;
    ICodec_BmpModule*	m_pBmpModule;
    ICodec_TiffModule*	m_pTiffModule;

};
class ICodec_BasicModule 
{
public:

    virtual ~ICodec_BasicModule() {}
    virtual FX_BOOL	RunLengthEncode(const uint8_t* src_buf, FX_DWORD src_size, uint8_t*& dest_buf,
                                    FX_DWORD& dest_size) = 0;
    virtual FX_BOOL	A85Encode(const uint8_t* src_buf, FX_DWORD src_size, uint8_t*& dest_buf,
                              FX_DWORD& dest_size) = 0;
    virtual ICodec_ScanlineDecoder*	CreateRunLengthDecoder(const uint8_t* src_buf, FX_DWORD src_size, int width, int height,
            int nComps, int bpc) = 0;
};
class ICodec_ScanlineDecoder 
{
public:

    virtual ~ICodec_ScanlineDecoder() {}

    virtual FX_DWORD	GetSrcOffset() = 0;

    virtual void		DownScale(int dest_width, int dest_height) = 0;

    virtual uint8_t*	GetScanline(int line) = 0;

    virtual FX_BOOL		SkipToScanline(int line, IFX_Pause* pPause) = 0;

    virtual int			GetWidth() = 0;

    virtual int			GetHeight() = 0;

    virtual int			CountComps() = 0;

    virtual int			GetBPC() = 0;

    virtual FX_BOOL		IsColorTransformed() = 0;

    virtual void		ClearImageData() = 0;
};
class ICodec_FlateModule 
{
public:

    virtual ~ICodec_FlateModule() {}
    virtual ICodec_ScanlineDecoder*	CreateDecoder(const uint8_t* src_buf, FX_DWORD src_size, int width, int height,
            int nComps, int bpc, int predictor, int Colors, int BitsPerComponent, int Columns) = 0;
    virtual FX_DWORD	FlateOrLZWDecode(FX_BOOL bLZW, const uint8_t* src_buf, FX_DWORD src_size, FX_BOOL bEarlyChange,
                                         int predictor, int Colors, int BitsPerComponent, int Columns,
                                         FX_DWORD estimated_size, uint8_t*& dest_buf, FX_DWORD& dest_size) = 0;
    virtual FX_BOOL		Encode(const uint8_t* src_buf, FX_DWORD src_size,
                               int predictor, int Colors, int BitsPerComponent, int Columns,
                               uint8_t*& dest_buf, FX_DWORD& dest_size) = 0;
    virtual FX_BOOL		Encode(const uint8_t* src_buf, FX_DWORD src_size, uint8_t*& dest_buf, FX_DWORD& dest_size) = 0;
};
class ICodec_FaxModule 
{
public:

    virtual ~ICodec_FaxModule() {}

    virtual ICodec_ScanlineDecoder*	CreateDecoder(const uint8_t* src_buf, FX_DWORD src_size, int width, int height,
            int K, FX_BOOL EndOfLine, FX_BOOL EncodedByteAlign, FX_BOOL BlackIs1, int Columns, int Rows) = 0;


    virtual FX_BOOL		Encode(const uint8_t* src_buf, int width, int height, int pitch,
                               uint8_t*& dest_buf, FX_DWORD& dest_size) = 0;
};
class ICodec_JpegModule 
{
public:

    virtual ~ICodec_JpegModule() {}

    virtual void		SetPovider(IFX_JpegProvider* pJP) = 0;

    virtual ICodec_ScanlineDecoder*	CreateDecoder(const uint8_t* src_buf, FX_DWORD src_size,
            int width, int height, int nComps, FX_BOOL ColorTransform) = 0;

    virtual FX_BOOL		LoadInfo(const uint8_t* src_buf, FX_DWORD src_size, int& width, int& height,
                                 int& num_components, int& bits_per_components, FX_BOOL& color_transform,
                                 uint8_t** icc_buf_ptr = NULL, FX_DWORD* icc_length = NULL) = 0;

    virtual FX_BOOL		Encode(const class CFX_DIBSource* pSource, uint8_t*& dest_buf, FX_STRSIZE& dest_size, int quality = 75,
                               const uint8_t* icc_buf = NULL, FX_DWORD icc_length = 0) = 0;

    virtual void*		Start() = 0;

    virtual void		Finish(void* pContext) = 0;

    virtual void		Input(void* pContext, const uint8_t* src_buf, FX_DWORD src_size) = 0;

    virtual int			ReadHeader(void* pContext, int* width, int* height, int* nComps, CFX_DIBAttribute* pAttribute = NULL) = 0;


    virtual int			StartScanline(void* pContext, int down_scale) = 0;


    virtual FX_BOOL		ReadScanline(void* pContext, uint8_t* dest_buf) = 0;


    virtual FX_DWORD	GetAvailInput(void* pContext, uint8_t** avail_buf_ptr = NULL) = 0;
};
class ICodec_JpxModule 
{
public:

    virtual ~ICodec_JpxModule() {}

    virtual void* 	CreateDecoder(const uint8_t* src_buf, FX_DWORD src_size, FX_BOOL useColorSpace = FALSE) = 0;

    virtual void		GetImageInfo(void* ctx, FX_DWORD& width, FX_DWORD& height,
                                     FX_DWORD& codestream_nComps, FX_DWORD& output_nComps) = 0;

    virtual FX_BOOL		Decode(void* ctx, uint8_t* dest_data, int pitch,
                               FX_BOOL bTranslateColor, uint8_t* offsets) = 0;

    virtual void		DestroyDecoder(void* ctx) = 0;
};
class ICodec_PngModule
{
public:

    virtual ~ICodec_PngModule() {}

    virtual void*		Start(void* pModule) = 0;

    virtual void		Finish(void* pContext) = 0;

    virtual FX_BOOL		Input(void* pContext, const uint8_t* src_buf, FX_DWORD src_size, CFX_DIBAttribute* pAttribute = NULL) = 0;

    FX_BOOL				(*ReadHeaderCallback)(void* pModule, int width, int height, int bpc, int pass, int* color_type, double* gamma);

    FX_BOOL				(*AskScanlineBufCallback)(void* pModule, int line, uint8_t*& src_buf);

    void				(*FillScanlineBufCompletedCallback)(void* pModule, int pass, int line);
};
class ICodec_GifModule
{
public:

    virtual ~ICodec_GifModule() {}

    virtual void*		Start(void* pModule) = 0;

    virtual void		Finish(void* pContext) = 0;

    virtual FX_DWORD	GetAvailInput(void* pContext, uint8_t** avail_buf_ptr = NULL) = 0;

    virtual void		Input(void* pContext, const uint8_t* src_buf, FX_DWORD src_size) = 0;

    virtual int32_t	ReadHeader(void* pContext, int* width, int* height,
                                   int* pal_num, void** pal_pp, int* bg_index, CFX_DIBAttribute* pAttribute = NULL) = 0;

    virtual int32_t	LoadFrameInfo(void* pContext, int* frame_num) = 0;

    void				(*RecordCurrentPositionCallback)(void* pModule, FX_DWORD& cur_pos);

    uint8_t*			(*AskLocalPaletteBufCallback)(void* pModule, int32_t frame_num, int32_t pal_size);

    virtual int32_t	LoadFrame(void* pContext, int frame_num, CFX_DIBAttribute* pAttribute = NULL) = 0;

    FX_BOOL				(*InputRecordPositionBufCallback)(void* pModule, FX_DWORD rcd_pos, const FX_RECT& img_rc,
            int32_t pal_num, void* pal_ptr,
            int32_t delay_time, FX_BOOL user_input,
            int32_t trans_index, int32_t disposal_method, FX_BOOL interlace);

    void				(*ReadScanlineCallback)(void* pModule, int32_t row_num, uint8_t* row_buf);
};
class ICodec_BmpModule
{
public:

    virtual ~ICodec_BmpModule() {}

    virtual void*		Start(void* pModule) = 0;

    virtual void		Finish(void* pContext) = 0;

    virtual FX_DWORD	GetAvailInput(void* pContext, uint8_t** avail_buf_ptr = NULL) = 0;

    virtual void		Input(void* pContext, const uint8_t* src_buf, FX_DWORD src_size) = 0;

    virtual int32_t	ReadHeader(void* pContext, int32_t* width, int32_t* height, FX_BOOL* tb_flag, int32_t* components,
                                   int* pal_num, FX_DWORD** pal_pp, CFX_DIBAttribute* pAttribute = NULL) = 0;

    virtual int32_t	LoadImage(void* pContext) = 0;

    FX_BOOL				(*InputImagePositionBufCallback)(void* pModule, FX_DWORD rcd_pos);

    void				(*ReadScanlineCallback)(void* pModule, int32_t row_num, uint8_t* row_buf);
};
class ICodec_TiffModule
{
public:

    virtual ~ICodec_TiffModule() {}

    virtual void* 	CreateDecoder(IFX_FileRead* file_ptr) = 0;


    virtual void		GetFrames(void* ctx, int32_t& frames) = 0;

    virtual FX_BOOL		LoadFrameInfo(void* ctx, int32_t frame, FX_DWORD& width, FX_DWORD& height, FX_DWORD& comps, FX_DWORD& bpc, CFX_DIBAttribute* pAttribute = NULL) = 0;


    virtual FX_BOOL		Decode(void* ctx, class CFX_DIBitmap* pDIBitmap) = 0;

    virtual void		DestroyDecoder(void* ctx) = 0;
};
class ICodec_Jbig2Module 
{
public:

    virtual ~ICodec_Jbig2Module() {}

    virtual FX_BOOL		Decode(FX_DWORD width, FX_DWORD height, const uint8_t* src_buf, FX_DWORD src_size,
                               const uint8_t* global_data, FX_DWORD global_size, uint8_t* dest_buf, FX_DWORD dest_pitch)  = 0;

    virtual FX_BOOL		Decode(IFX_FileRead* file_ptr, FX_DWORD& width, FX_DWORD& height,
                               FX_DWORD& pitch, uint8_t*& dest_buf) = 0;
    virtual void*				CreateJbig2Context() = 0;

    virtual FXCODEC_STATUS		StartDecode(void* pJbig2Context, FX_DWORD width, FX_DWORD height, const uint8_t* src_buf, FX_DWORD src_size,
                                            const uint8_t* global_data, FX_DWORD global_size, uint8_t* dest_buf, FX_DWORD dest_pitch, IFX_Pause* pPause) = 0;

    virtual FXCODEC_STATUS		StartDecode(void* pJbig2Context, IFX_FileRead* file_ptr,
                                            FX_DWORD& width, FX_DWORD& height, FX_DWORD& pitch, uint8_t*& dest_buf, IFX_Pause* pPause) = 0;
    virtual FXCODEC_STATUS		ContinueDecode(void* pJbig2Content, IFX_Pause* pPause) = 0;
    virtual void				DestroyJbig2Context(void* pJbig2Content) = 0;
};
class ICodec_ProgressiveDecoder
{
public:

    virtual ~ICodec_ProgressiveDecoder() {}

    virtual FXCODEC_STATUS		LoadImageInfo(IFX_FileRead* pFile, FXCODEC_IMAGE_TYPE imageType = FXCODEC_IMAGE_UNKNOWN, CFX_DIBAttribute* pAttribute = NULL) = 0;

    virtual FXCODEC_IMAGE_TYPE	GetType() = 0;

    virtual int32_t			GetWidth() = 0;

    virtual int32_t			GetHeight() = 0;

    virtual int32_t			GetNumComponents() = 0;

    virtual int32_t			GetBPC() = 0;

    virtual void				SetClipBox(FX_RECT* clip) = 0;

    virtual FXCODEC_STATUS		GetFrames(int32_t& frames, IFX_Pause* pPause = NULL) = 0;

    virtual FXCODEC_STATUS		StartDecode(class CFX_DIBitmap* pDIBitmap,
                                            int32_t start_x, int32_t start_y, int32_t size_x, int32_t size_y,
                                            int32_t frames = 0, FX_BOOL bInterpol = TRUE) = 0;

    virtual FXCODEC_STATUS		ContinueDecode(IFX_Pause* pPause = NULL) = 0;
};
class ICodec_Jbig2Encoder 
{
public:

    virtual ~ICodec_Jbig2Encoder() {}
};
class ICodec_IccModule 
{
public:
    typedef enum {
        IccCS_Unknown = 0,
        IccCS_XYZ,
        IccCS_Lab,
        IccCS_Luv,
        IccCS_YCbCr,
        IccCS_Yxy,
        IccCS_Hsv,
        IccCS_Hls,
        IccCS_Gray,
        IccCS_Rgb,
        IccCS_Cmyk,
        IccCS_Cmy
    } IccCS;
    typedef struct _IccParam {
        FX_DWORD	Version;
        IccCS		ColorSpace;
        FX_DWORD	dwProfileType;
        FX_DWORD	dwFormat;
        uint8_t*	pProfileData;
        FX_DWORD	dwProfileSize;
        double		Gamma;
    } IccParam;

    virtual ~ICodec_IccModule() {}

    virtual IccCS			GetProfileCS(const uint8_t* pProfileData, unsigned int dwProfileSize) = 0;

    virtual IccCS			GetProfileCS(IFX_FileRead* pFile) = 0;

    virtual void*	CreateTransform(ICodec_IccModule::IccParam* pInputParam,
                                        ICodec_IccModule::IccParam* pOutputParam,
                                        ICodec_IccModule::IccParam* pProofParam = NULL,
                                        FX_DWORD dwIntent = Icc_INTENT_PERCEPTUAL,
                                        FX_DWORD dwFlag = Icc_FLAGS_DEFAULT,
                                        FX_DWORD dwPrfIntent = Icc_INTENT_ABSOLUTE_COLORIMETRIC,
                                        FX_DWORD dwPrfFlag = Icc_FLAGS_SOFTPROOFING
                                     ) = 0;


    virtual void*	CreateTransform_sRGB(const uint8_t* pProfileData, FX_DWORD dwProfileSize, int32_t& nComponents, int32_t intent = 0,
            FX_DWORD dwSrcFormat = Icc_FORMAT_DEFAULT) = 0;

    virtual void*	CreateTransform_CMYK(const uint8_t* pSrcProfileData, FX_DWORD dwSrcProfileSize, int32_t& nSrcComponents,
            const uint8_t* pDstProfileData, FX_DWORD dwDstProfileSize, int32_t intent = 0,
            FX_DWORD dwSrcFormat = Icc_FORMAT_DEFAULT,
            FX_DWORD dwDstFormat = Icc_FORMAT_DEFAULT
                                          ) = 0;

    virtual void			DestroyTransform(void* pTransform) = 0;

    virtual void			Translate(void* pTransform, FX_FLOAT* pSrcValues, FX_FLOAT* pDestValues) = 0;

    virtual void			TranslateScanline(void* pTransform, uint8_t* pDest, const uint8_t* pSrc, int pixels) = 0;
    virtual void                        SetComponents(FX_DWORD nComponents) = 0;
};

void AdobeCMYK_to_sRGB(FX_FLOAT c, FX_FLOAT m, FX_FLOAT y, FX_FLOAT k, FX_FLOAT& R, FX_FLOAT& G, FX_FLOAT& B);
void AdobeCMYK_to_sRGB1(uint8_t c, uint8_t m, uint8_t y, uint8_t k, uint8_t& R, uint8_t& G, uint8_t& B);
FX_BOOL MD5ComputeID(const void* buf, FX_DWORD dwSize, uint8_t ID[16]);
class CFX_DIBAttribute
{
public:
    CFX_DIBAttribute();
    ~CFX_DIBAttribute();

    int32_t		m_nXDPI;

    int32_t		m_nYDPI;

    FX_FLOAT		m_fAspectRatio;

    FX_WORD			m_wDPIUnit;

    CFX_ByteString	m_strAuthor;

    uint8_t			m_strTime[20];

    int32_t		m_nGifLeft;
    int32_t		m_nGifTop;

    FX_DWORD*		m_pGifLocalPalette;

    FX_DWORD		m_nGifLocalPalNum;

    int32_t		m_nBmpCompressType;
    class IFX_DIBAttributeExif* m_pExif;
};
class IFX_DIBAttributeExif
{
public:
    virtual ~IFX_DIBAttributeExif() {};
    virtual FX_BOOL		GetInfo(FX_WORD tag, void* val) = 0;
};

#endif  // CORE_INCLUDE_FXCODEC_FX_CODEC_H_
