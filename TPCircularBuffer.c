//
//  TPCircularBuffer.c
//  Circular buffer implementation
//
//  Created by Michael Tyson on 20/03/2011.
//  Copyright 2011 A Tasty Pixel. All rights reserved.
//

#include "TPCircularBuffer.h"
#include <string.h>
#include <libkern/OSAtomic.h>

static inline int min(int a, int b) {
    return (a>b ? b : a);
}


inline void TPCircularBufferInit(TPCircularBufferRecord *record, int length) {
    record->head = record->tail = record->fillCount = 0;
    record->length = length;
}

inline int TPCircularBufferFillCount(TPCircularBufferRecord *record) {
    return record->fillCount;
}

inline int TPCircularBufferFillCountContiguous(TPCircularBufferRecord *record) {
    return min(record->fillCount, record->length-record->tail);
}

inline int TPCircularBufferSpace(TPCircularBufferRecord *record) {
    return record->length - record->fillCount;
}

inline int TPCircularBufferSpaceContiguous(TPCircularBufferRecord *record) {
    return min(record->length-record->fillCount, record->length-record->head);
}

inline int TPCircularBufferHead(TPCircularBufferRecord *record) {
    return record->head;
}

inline int TPCircularBufferTail(TPCircularBufferRecord *record) {
    return record->tail;
}

inline void TPCircularBufferProduce(TPCircularBufferRecord *record, int amount) {
    record->head = (record->head + amount) % record->length;
    OSAtomicAdd32Barrier(amount, &record->fillCount);
}

inline void TPCircularBufferConsume(TPCircularBufferRecord *record, int amount) {
    record->tail = (record->tail + amount) % record->length;
    OSAtomicAdd32Barrier(-amount, &record->fillCount);
}

inline void TPCircularBufferClear(TPCircularBufferRecord *record) {
    record->tail = record->head;
    record->fillCount = 0;
}

inline int TPCircularBufferCopy(TPCircularBufferRecord *record, void* dst, const void* src, int count, int len) {
    int copied = 0;
    while ( count > 0 ) {
        int space = TPCircularBufferSpaceContiguous(record);
        if ( space == 0 ) {
            return copied;
        }
        
        int toCopy = min(count, space);
        int bytesToCopy = toCopy * len;
        memcpy(dst + (len*TPCircularBufferHead(record)), src, bytesToCopy);
        
        src += bytesToCopy;
        count -= toCopy;
        copied += bytesToCopy;
        TPCircularBufferProduce(record, toCopy);
    }
    return copied;
}