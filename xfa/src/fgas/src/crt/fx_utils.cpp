// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "../fgas_base.h"
#include "fx_utils.h"
CFX_ThreadLock::CFX_ThreadLock()
    : m_pData(NULL)
{
}
CFX_ThreadLock::~CFX_ThreadLock()
{
}
void CFX_ThreadLock::Lock()
{
}
void CFX_ThreadLock::Unlock()
{
}
typedef struct _FX_BASEARRAYDATA : public CFX_Target {
    int32_t	iGrowSize;
    int32_t	iBlockSize;
    int32_t	iTotalCount;
    int32_t	iBlockCount;
    uint8_t*	pBuffer;
} FX_BASEARRAYDATA, * FX_LPBASEARRAYDATA;
typedef FX_BASEARRAYDATA const * FX_LPCBASEARRAYDATA;
CFX_BaseArray::CFX_BaseArray(int32_t iGrowSize, int32_t iBlockSize)
{
    FXSYS_assert(iGrowSize > 0 && iBlockSize > 0);
    m_pData = FXTARGET_New FX_BASEARRAYDATA;
    FX_memset(m_pData, 0, sizeof(FX_BASEARRAYDATA));
    ((FX_LPBASEARRAYDATA)m_pData)->iGrowSize = iGrowSize;
    ((FX_LPBASEARRAYDATA)m_pData)->iBlockSize = iBlockSize;
}
CFX_BaseArray::~CFX_BaseArray()
{
    FX_LPBASEARRAYDATA pData = (FX_LPBASEARRAYDATA)m_pData;
    if (pData->pBuffer != NULL) {
        FX_Free(pData->pBuffer);
    }
    FXTARGET_Delete pData;
}
int32_t CFX_BaseArray::GetSize() const
{
    return ((FX_LPBASEARRAYDATA)m_pData)->iBlockCount;
}
int32_t CFX_BaseArray::GetBlockSize() const
{
    return ((FX_LPBASEARRAYDATA)m_pData)->iBlockSize;
}
uint8_t* CFX_BaseArray::AddSpaceTo(int32_t index)
{
    FXSYS_assert(index > -1);
    uint8_t* &pBuffer = ((FX_LPBASEARRAYDATA)m_pData)->pBuffer;
    int32_t &iTotalCount = ((FX_LPBASEARRAYDATA)m_pData)->iTotalCount;
    int32_t iBlockSize = ((FX_LPBASEARRAYDATA)m_pData)->iBlockSize;
    if (index >= iTotalCount) {
        int32_t iGrowSize = ((FX_LPBASEARRAYDATA)m_pData)->iGrowSize;
        iTotalCount = (index / iGrowSize + 1) * iGrowSize;
        int32_t iNewSize = iTotalCount * iBlockSize;
        if (pBuffer == NULL) {
            pBuffer = (uint8_t*)FX_Alloc(uint8_t, iNewSize);
        } else {
            pBuffer = (uint8_t*)FX_Realloc(uint8_t, pBuffer, iNewSize);
        }
    }
    FXSYS_assert(pBuffer != NULL);
    int32_t &iBlockCount = ((FX_LPBASEARRAYDATA)m_pData)->iBlockCount;
    if (index >= iBlockCount) {
        iBlockCount = index + 1;
    }
    return pBuffer + index * iBlockSize;
}
uint8_t* CFX_BaseArray::GetAt(int32_t index) const
{
    FXSYS_assert(index > -1 && index < ((FX_LPBASEARRAYDATA)m_pData)->iBlockCount);
    return ((FX_LPBASEARRAYDATA)m_pData)->pBuffer + index * ((FX_LPBASEARRAYDATA)m_pData)->iBlockSize;
}
uint8_t* CFX_BaseArray::GetBuffer() const
{
    return ((FX_LPBASEARRAYDATA)m_pData)->pBuffer;
}
int32_t CFX_BaseArray::Append(const CFX_BaseArray &src, int32_t iStart, int32_t iCount)
{
    int32_t iBlockSize = ((FX_LPBASEARRAYDATA)m_pData)->iBlockSize;
    FXSYS_assert(iBlockSize == ((FX_LPBASEARRAYDATA)src.m_pData)->iBlockSize);
    int32_t &iBlockCount = ((FX_LPBASEARRAYDATA)m_pData)->iBlockCount;
    int32_t iAdded = src.GetSize();
    FXSYS_assert(iStart > -1 && iStart < iAdded);
    if (iCount < 0) {
        iCount = iAdded;
    }
    if (iStart + iCount > iAdded) {
        iCount = iAdded - iStart;
    }
    if (iCount < 1) {
        return 0;
    }
    uint8_t* pDst = ((FX_LPBASEARRAYDATA)m_pData)->pBuffer + iBlockCount * iBlockSize;
    AddSpaceTo(iBlockCount + iCount - 1);
    FX_memcpy(pDst, ((FX_LPBASEARRAYDATA)src.m_pData)->pBuffer + iStart * iBlockSize, iCount * iBlockSize);
    return iCount;
}
int32_t CFX_BaseArray::Copy(const CFX_BaseArray &src, int32_t iStart, int32_t iCount)
{
    int32_t iBlockSize = ((FX_LPBASEARRAYDATA)m_pData)->iBlockSize;
    FXSYS_assert(iBlockSize == ((FX_LPBASEARRAYDATA)src.m_pData)->iBlockSize);
    int32_t iCopied = src.GetSize();
    FXSYS_assert(iStart > -1 && iStart < iCopied);
    if (iCount < 0) {
        iCount = iCopied;
    }
    if (iStart + iCount > iCopied) {
        iCount = iCopied - iStart;
    }
    if (iCount < 1) {
        return 0;
    }
    RemoveAll(TRUE);
    AddSpaceTo(iCount - 1);
    FX_memcpy(((FX_LPBASEARRAYDATA)m_pData)->pBuffer, ((FX_LPBASEARRAYDATA)src.m_pData)->pBuffer + iStart * iBlockSize, iCount * iBlockSize);
    return iCount;
}
int32_t CFX_BaseArray::RemoveLast(int32_t iCount)
{
    int32_t &iBlockCount = ((FX_LPBASEARRAYDATA)m_pData)->iBlockCount;
    if (iCount < 0 || iCount > iBlockCount) {
        iCount = iBlockCount;
        iBlockCount = 0;
    } else {
        iBlockCount -= iCount;
    }
    return iCount;
}
void CFX_BaseArray::RemoveAll(FX_BOOL bLeaveMemory)
{
    if (!bLeaveMemory) {
        uint8_t* &pBuffer = ((FX_LPBASEARRAYDATA)m_pData)->pBuffer;
        if (pBuffer != NULL) {
            FX_Free(pBuffer);
            pBuffer = NULL;
        }
        ((FX_LPBASEARRAYDATA)m_pData)->iTotalCount = 0;
    }
    ((FX_LPBASEARRAYDATA)m_pData)->iBlockCount = 0;
}
CFX_BaseMassArrayImp::CFX_BaseMassArrayImp(int32_t iChunkSize, int32_t iBlockSize)
    : m_iChunkSize(iChunkSize)
    , m_iBlockSize(iBlockSize)
    , m_iChunkCount(0)
    , m_iBlockCount(0)
{
    FXSYS_assert(m_iChunkSize > 0 && m_iBlockSize > 0);
    m_pData = FX_NEW CFX_PtrArray;
    m_pData->SetSize(16);
}
CFX_BaseMassArrayImp::~CFX_BaseMassArrayImp()
{
    RemoveAll();
    delete m_pData;
}
uint8_t* CFX_BaseMassArrayImp::AddSpaceTo(int32_t index)
{
    FXSYS_assert(index > -1);
    uint8_t* pChunk;
    if (index < m_iBlockCount) {
        pChunk = (uint8_t*)m_pData->GetAt(index / m_iChunkSize);
    } else {
        int32_t iMemSize = m_iChunkSize * m_iBlockSize;
        while (TRUE) {
            if (index < m_iChunkCount * m_iChunkSize) {
                pChunk = (uint8_t*)m_pData->GetAt(index / m_iChunkSize);
                break;
            } else {
                pChunk = (uint8_t*)FX_Alloc(uint8_t, iMemSize);
                if (m_iChunkCount < m_pData->GetSize()) {
                    m_pData->SetAt(m_iChunkCount, pChunk);
                } else {
                    m_pData->Add(pChunk);
                }
                m_iChunkCount ++;
            }
        }
    }
    FXSYS_assert(pChunk != NULL);
    m_iBlockCount = index + 1;
    return pChunk + (index % m_iChunkSize) * m_iBlockSize;
}
uint8_t* CFX_BaseMassArrayImp::GetAt(int32_t index) const
{
    FXSYS_assert(index > -1 && index < m_iBlockCount);
    uint8_t* pChunk = (uint8_t*)m_pData->GetAt(index / m_iChunkSize);
    FXSYS_assert(pChunk != NULL);
    return pChunk + (index % m_iChunkSize) * m_iBlockSize;
}
int32_t CFX_BaseMassArrayImp::Append(const CFX_BaseMassArrayImp &src, int32_t iStart, int32_t iCount)
{
    FXSYS_assert(m_iBlockSize == src.m_iBlockSize);
    int32_t iAdded = src.m_iBlockCount;
    FXSYS_assert(iStart > -1 && iStart < iAdded);
    if (iCount < 0) {
        iCount = iAdded;
    }
    if (iStart + iCount > iAdded) {
        iCount = iAdded - iStart;
    }
    if (iCount < 1) {
        return m_iBlockCount;
    }
    int32_t iBlockCount = m_iBlockCount;
    int32_t iTotal = m_iBlockCount + iCount;
    AddSpaceTo(iTotal - 1);
    Append(iBlockCount, src, iStart, iCount);
    return m_iBlockCount;
}
int32_t CFX_BaseMassArrayImp::Copy(const CFX_BaseMassArrayImp &src, int32_t iStart, int32_t iCount)
{
    FXSYS_assert(m_iBlockSize == src.m_iBlockSize);
    int32_t iCopied = src.m_iBlockCount;
    FXSYS_assert(iStart > -1);
    if (iStart >= iCopied) {
        return 0;
    }
    RemoveAll(TRUE);
    if (iCount < 0) {
        iCount = iCopied;
    }
    if (iStart + iCount > iCopied) {
        iCount = iCopied - iStart;
    }
    if (iCount < 1) {
        return 0;
    }
    if (m_iBlockCount < iCount) {
        AddSpaceTo(iCount - 1);
    }
    Append(0, src, iStart, iCount);
    return m_iBlockCount;
}
void CFX_BaseMassArrayImp::Append(int32_t iDstStart, const CFX_BaseMassArrayImp &src, int32_t iSrcStart, int32_t iSrcCount)
{
    FXSYS_assert(iDstStart > -1 && m_iBlockSize == src.m_iBlockSize);
    int32_t iSrcTotal = src.m_iBlockCount;
    FXSYS_assert(iSrcTotal > 0 && m_iBlockCount >= iDstStart + iSrcCount);
    FXSYS_assert(iSrcStart > -1 && iSrcStart < iSrcTotal && iSrcCount > 0 && iSrcStart + iSrcCount <= iSrcTotal);
    int32_t iDstChunkIndex = iDstStart / m_iChunkSize;
    int32_t iSrcChunkIndex = iSrcStart / src.m_iChunkSize;
    uint8_t* pDstChunk = (uint8_t*)GetAt(iDstStart);
    uint8_t* pSrcChunk = (uint8_t*)src.GetAt(iSrcStart);
    int32_t iDstChunkSize = m_iChunkSize - (iDstStart % m_iChunkSize);
    int32_t iSrcChunkSize = src.m_iChunkSize - (iSrcStart % src.m_iChunkSize);
    int32_t iCopySize = FX_MIN(iSrcCount, FX_MIN(iSrcChunkSize, iDstChunkSize));
    int32_t iCopyBytes = iCopySize * m_iBlockSize;
    while (iSrcCount > 0) {
        FXSYS_assert(pDstChunk != NULL && pSrcChunk != NULL);
        FXSYS_memcpy(pDstChunk, pSrcChunk, iCopyBytes);
        iSrcCount -= iCopySize;
        iSrcChunkSize -= iCopySize;
        if (iSrcChunkSize < 1) {
            iSrcChunkSize = src.m_iChunkSize;
            iSrcChunkIndex ++;
            pSrcChunk = (uint8_t*)src.m_pData->GetAt(iSrcChunkIndex);
        } else {
            pSrcChunk += iCopyBytes;
        }
        iDstChunkSize -= iCopySize;
        if (iDstChunkSize < 1) {
            iDstChunkSize = m_iChunkSize;
            iDstChunkIndex ++;
            pDstChunk = (uint8_t*)m_pData->GetAt(iDstChunkIndex);
        } else {
            pDstChunk += iCopyBytes;
        }
        iCopySize = FX_MIN(iSrcCount, FX_MIN(iSrcChunkSize, iDstChunkSize));
        iCopyBytes = iCopySize * m_iBlockSize;
    }
}
int32_t CFX_BaseMassArrayImp::RemoveLast(int32_t iCount)
{
    if (iCount < 0 || iCount >= m_iBlockCount) {
        m_iBlockCount = 0;
    } else {
        m_iBlockCount -= iCount;
    }
    return m_iBlockCount;
}
void CFX_BaseMassArrayImp::RemoveAll(FX_BOOL bLeaveMemory)
{
    if (bLeaveMemory) {
        m_iBlockCount = 0;
        return;
    }
    for (int32_t i = 0; i < m_iChunkCount; i ++) {
        void* p = m_pData->GetAt(i);
        if (p == NULL) {
            continue;
        }
        FX_Free(p);
    }
    m_pData->RemoveAll();
    m_iChunkCount = 0;
    m_iBlockCount = 0;
}
CFX_BaseMassArray::CFX_BaseMassArray(int32_t iChunkSize, int32_t iBlockSize)
{
    m_pData = FXTARGET_New CFX_BaseMassArrayImp(iChunkSize, iBlockSize);
}
CFX_BaseMassArray::~CFX_BaseMassArray()
{
    FXTARGET_Delete m_pData;
}
int32_t CFX_BaseMassArray::GetSize() const
{
    return m_pData->m_iBlockCount;
}
uint8_t* CFX_BaseMassArray::AddSpaceTo(int32_t index)
{
    return m_pData->AddSpaceTo(index);
}
uint8_t* CFX_BaseMassArray::GetAt(int32_t index) const
{
    return m_pData->GetAt(index);
}
int32_t CFX_BaseMassArray::Append(const CFX_BaseMassArray &src, int32_t iStart, int32_t iCount)
{
    return m_pData->Append(*(CFX_BaseMassArrayImp*)src.m_pData, iStart, iCount);
}
int32_t CFX_BaseMassArray::Copy(const CFX_BaseMassArray &src, int32_t iStart, int32_t iCount)
{
    return m_pData->Copy(*(CFX_BaseMassArrayImp*)src.m_pData, iStart, iCount);
}
int32_t CFX_BaseMassArray::RemoveLast(int32_t iCount)
{
    return m_pData->RemoveLast(iCount);
}
void CFX_BaseMassArray::RemoveAll(FX_BOOL bLeaveMemory)
{
    m_pData->RemoveAll(bLeaveMemory);
}
typedef struct _FX_BASEDISCRETEARRAYDATA {
    int32_t		iBlockSize;
    int32_t		iChunkSize;
    int32_t		iChunkCount;
    CFX_PtrArray	ChunkBuffer;
} FX_BASEDISCRETEARRAYDATA, * FX_LPBASEDISCRETEARRAYDATA;
typedef FX_BASEDISCRETEARRAYDATA const * FX_LPCBASEDISCRETEARRAYDATA;
CFX_BaseDiscreteArray::CFX_BaseDiscreteArray(int32_t iChunkSize, int32_t iBlockSize)
{
    FXSYS_assert(iChunkSize > 0 && iBlockSize > 0);
    FX_LPBASEDISCRETEARRAYDATA pData;
    m_pData = pData = FX_NEW FX_BASEDISCRETEARRAYDATA;
    pData->ChunkBuffer.SetSize(16);
    pData->iChunkCount = 0;
    pData->iChunkSize = iChunkSize;
    pData->iBlockSize = iBlockSize;
}
CFX_BaseDiscreteArray::~CFX_BaseDiscreteArray()
{
    RemoveAll();
    delete (FX_LPBASEDISCRETEARRAYDATA)m_pData;
}
uint8_t* CFX_BaseDiscreteArray::AddSpaceTo(int32_t index)
{
    FXSYS_assert(index > -1);
    FX_LPBASEDISCRETEARRAYDATA pData = (FX_LPBASEDISCRETEARRAYDATA)m_pData;
    int32_t &iChunkCount = pData->iChunkCount;
    int32_t iChunkSize = pData->iChunkSize;
    uint8_t* pChunk = NULL;
    int32_t iChunk = index / iChunkSize;
    if (iChunk < iChunkCount) {
        pChunk = (uint8_t*)pData->ChunkBuffer.GetAt(iChunk);
    }
    if (pChunk == NULL) {
        int32_t iMemSize = iChunkSize * pData->iBlockSize;
        pChunk = (uint8_t*)FX_Alloc(uint8_t, iMemSize);
        FXSYS_memset(pChunk, 0, iMemSize);
        pData->ChunkBuffer.SetAtGrow(iChunk, pChunk);
        if (iChunkCount <= iChunk) {
            iChunkCount = iChunk + 1;
        }
    }
    return pChunk + (index % iChunkSize) * pData->iBlockSize;
}
uint8_t* CFX_BaseDiscreteArray::GetAt(int32_t index) const
{
    FXSYS_assert(index > -1);
    FX_LPBASEDISCRETEARRAYDATA pData = (FX_LPBASEDISCRETEARRAYDATA)m_pData;
    int32_t iChunkSize = pData->iChunkSize;
    int32_t iChunk = index / iChunkSize;
    if (iChunk >= pData->iChunkCount) {
        return NULL;
    }
    uint8_t* pChunk = (uint8_t*)pData->ChunkBuffer.GetAt(iChunk);
    if (pChunk == NULL) {
        return NULL;
    }
    return pChunk + (index % iChunkSize) * pData->iBlockSize;
}
void CFX_BaseDiscreteArray::RemoveAll()
{
    FX_LPBASEDISCRETEARRAYDATA pData = (FX_LPBASEDISCRETEARRAYDATA)m_pData;
    CFX_PtrArray &ChunkBuffer = pData->ChunkBuffer;
    int32_t &iChunkCount = pData->iChunkCount;
    for (int32_t i = 0; i < iChunkCount; i++) {
        void* p = ChunkBuffer.GetAt(i);
        if (p == NULL) {
            continue;
        }
        FX_Free(p);
    }
    ChunkBuffer.RemoveAll();
    iChunkCount = 0;
}
CFX_BaseStack::CFX_BaseStack(int32_t iChunkSize, int32_t iBlockSize)
{
    m_pData = FXTARGET_New CFX_BaseMassArrayImp(iChunkSize, iBlockSize);
}
CFX_BaseStack::~CFX_BaseStack()
{
    FXTARGET_Delete (CFX_BaseMassArrayImp*)m_pData;
}
uint8_t* CFX_BaseStack::Push()
{
    return m_pData->AddSpace();
}
void CFX_BaseStack::Pop()
{
    int32_t &iBlockCount = m_pData->m_iBlockCount;
    if (iBlockCount < 1) {
        return;
    }
    iBlockCount --;
}
uint8_t* CFX_BaseStack::GetTopElement() const
{
    int32_t iSize = m_pData->m_iBlockCount;
    if (iSize < 1) {
        return NULL;
    }
    return m_pData->GetAt(iSize - 1);
}
int32_t CFX_BaseStack::GetSize() const
{
    return m_pData->m_iBlockCount;
}
uint8_t* CFX_BaseStack::GetAt(int32_t index) const
{
    return m_pData->GetAt(index);
}
void CFX_BaseStack::RemoveAll(FX_BOOL bLeaveMemory )
{
    m_pData->RemoveAll(bLeaveMemory);
}
