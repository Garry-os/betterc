#pragma once
#include "types.h"

typedef struct {
    void* data;
    usize size;
    usize capacity;
    usize elementSize;
} Vector;

#define vector_getv(type, buffer, index) (*(type*)vector_get(buffer, index))
#define v_type(type) (sizeof(type))

// Generic types functions
void vector_pushfloat(Vector* buffer, float value);
void vector_pushdouble(Vector* buffer, double value);

// Unsigned integers
void vector_pushu8(Vector* buffer, u8 value);
void vector_pushu16(Vector* buffer, u16 value);
void vector_pushu32(Vector* buffer, u32 value);
void vector_pushu64(Vector* buffer, u64 value);

// Signed integers
void vector_pushi8(Vector* buffer, i8 value);
void vector_pushi16(Vector* buffer, i16 value);
void vector_pushi32(Vector* buffer, i32 value);
void vector_pushi64(Vector* buffer, i64 value);

// _Generic macros
#define vector_push(buffer, value) _Generic((value), \
    float: vector_pushfloat, \
    double: vector_pushdouble, \
    u8: vector_pushu8, \
    u16: vector_pushu16, \
    u32: vector_pushu32, \
    u64: vector_pushu64, \
    i8: vector_pushi8, \
    i16: vector_pushi16, \
    i32: vector_pushi32, \
    i64: vector_pushi64, \
    default: vector_push_impl \
)(buffer, value)

Vector vector_new(usize elementSize);
Vector vector_new_reserve(usize elementSize, usize reservedSize);
void vector_free(Vector* buffer);

// Methods
void vector_push_impl(Vector* buffer, const void* content);
void* vector_get(Vector* buffer, usize index);
void vector_reserve(Vector* buffer, usize growthAmount);
