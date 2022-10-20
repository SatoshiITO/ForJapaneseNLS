#include "mysse2.h"
#include <stdint.h>

static int16_t saturate_add_int16(int16_t a, int16_t b)
{
	if (a > 0) {
		if (b > INT16_MAX - a) return INT16_MAX;
	} else {
		if (b < INT16_MIN - a) return INT16_MIN;
	}
	return a + b;
}

static uint8_t saturate_add_uint8(uint8_t a, uint8_t b)
{
	return (a > 0xFF - b) ? 0xFF : a + b;
}

static uint8_t saturate_sub_uint8(uint8_t a, uint8_t b)
{
	return (a < b) ? 0 : a - b;
}

static uint16_t saturate_sub_uint16(uint16_t a, uint16_t b)
{
	return (a < b) ? 0 : a - b;
}

static int16_t l2b16(int16_t a)
{
	int16_t r;
	uint8_t *ap = (uint8_t *) &a;
	uint8_t *rp = (uint8_t *) &r;
	rp[0] = ap[1];
	rp[1] = ap[0];
	return r;
}

#define b2l16 l2b16

static uint16_t l2b16u(uint16_t a)
{
	uint16_t r;
	uint8_t *ap = (uint8_t *) &a;
	uint8_t *rp = (uint8_t *) &r;
	rp[0] = ap[1];
	rp[1] = ap[0];
	return r;
}

#define b2l16u l2b16u

static int32_t l2b32(int32_t a)
{
	uint32_t r;
	uint8_t *ap = (uint8_t *) &a;
	uint8_t *rp = (uint8_t *) &r;
	rp[0] = ap[3];
	rp[1] = ap[2];
	rp[2] = ap[1];
	rp[3] = ap[0];
	return r;
}

#define b2l32 l2b32

/** _mm_adds_epi16		8つの16ビット符号付き整数の加算
 */
__m128i _mm_adds_epi16 (__m128i a, __m128i b)
{
/* Adds the 8 signed 16-bit integers in a to the 8 signed 16-bit integers */
/* in b and saturates. */
/* r0 := SignedSaturate(a0 + b0) */
/* r1 := SignedSaturate(a1 + b1) */
/* ... */
/* r7 := SignedSaturate(a7 + b7) */

	__m128i r;
	int16_t *ap = (int16_t *) &a;
	int16_t *bp = (int16_t *) &b;
	int16_t *rp = (int16_t *) &r;
	int i;
	for (i = 0; i < 8; i++) {
		rp[i] = b2l16( saturate_add_int16(l2b16(ap[i]), l2b16(bp[i])) );
	}
	return r;
}

/** _mm_adds_epu8		16この8ビット符号無し整数の加算
 */
__m128i _mm_adds_epu8 (__m128i a, __m128i b)
{
/* Adds the 16 unsigned 8-bit integers in a to the 16 unsigned 8-bit */
/* integers in b and saturates. */
/* r0 := UnsignedSaturate(a0 + b0) */
/* r1 := UnsignedSaturate(a1 + b1) */
/* ... */
/* r15 := UnsignedSaturate(a15 + b15) */

	__m128i r;
	uint8_t *ap = (uint8_t *) &a;
	uint8_t *bp = (uint8_t *) &b;
	uint8_t *rp = (uint8_t *) &r;
	int i;
	for (i = 0; i < 16; i++) {
		rp[i] = saturate_add_uint8(ap[i], bp[i]);
	}
	return r;
}

/** _mm_cmpeq_epi8		16この8ビット符号付きor無し整数の等式比較
 */
__m128i _mm_cmpeq_epi8 (__m128i a, __m128i b)
{
/* Compares the 16 signed or unsigned 8-bit integers in a and the 16 */
/* signed or unsigned 8-bit integers in b for equality. */
/* r0 := (a0 == b0) ? 0xff : 0x0 */
/* r1 := (a1 == b1) ? 0xff : 0x0 */
/* ... */
/* r15 := (a15 == b15) ? 0xff : 0x0 */

	__m128i r;
	int8_t *ap = (int8_t *) &a;
	int8_t *bp = (int8_t *) &b;
	int8_t *rp = (int8_t *) &r;
	int i;
	for (i = 0; i < 16; i++) {
		rp[i] = (ap[i] == bp[i]) ? 0xff : 0x0;
	}
	return r;
}

/** _mm_cmpgt_epi16		8この16ビット符号付き整数の＞不等式比較
 */
__m128i _mm_cmpgt_epi16 (__m128i a, __m128i b)
{
/* Compares the 8 signed 16-bit integers in a and the 8 signed 16-bit */
/* integers in b for greater than. */
/* r0 := (a0 > b0) ? 0xffff : 0x0 */
/* r1 := (a1 > b1) ? 0xffff : 0x0 */
/* ... */
/* r7 := (a7 > b7) ? 0xffff : 0x0 */

	__m128i r;
	int16_t *ap = (int16_t *) &a;
	int16_t *bp = (int16_t *) &b;
	int16_t *rp = (int16_t *) &r;
	int i;
	for (i = 0; i < 8; i++) {
		rp[i] = (l2b16(ap[i]) > l2b16(bp[i])) ? 0xffff : 0x0;
	}
	return r;
}

/** _mm_extract_epi16	指定された16ビット符号付きor無し整数の取り出し
 */
int _mm_extract_epi16 (__m128i a, int imm)
{
/* Extracts the selected signed or unsigned 16-bit integer from a and */
/* zero extends. */
/* r := (imm == 0) ? a0 : */
/* ( (imm == 1) ? a1 : */
/* ... */
/* (imm == 7) ? a7 ) */

	int16_t *ap = (int16_t *) &a;
	return (int) l2b16(ap[imm]);
}

/** _mm_load_si128		
 */
__m128i _mm_load_si128 (__m128i *p)
{
/* Loads 128-bit value. */
/* Returns the value loaded in a variable representing a register. */
/* Address p must be 16-byte aligned. For the unaligned version of this */
/* intrinsic, see _mm_loadu_si128. */
	__m128i r = *p;
	return r;
}

/** _mm_max_epi16		8つの16ビット符号付き整数の大きい方を取る
 */
__m128i _mm_max_epi16 (__m128i a, __m128i b)
{
/* Computes the pairwise maxima of the 8 signed 16-bit integers from a */
/* and the 8 signed 16-bit integers from b. */
/* r0 := max(a0, b0) */
/* r1 := max(a1, b1) */
/* ... */
/* r7 := max(a7, b7) */

	__m128i r;
	int16_t *ap = (int16_t *) &a;
	int16_t *bp = (int16_t *) &b;
	int16_t *rp = (int16_t *) &r;
	int i;
	for (i = 0; i < 8; i++) {
		int16_t ai = l2b16(ap[i]);
		int16_t bi = l2b16(bp[i]);
		rp[i] = b2l16( (ai > bi) ? ai : bi );
	}
	return r;
}

/** _mm_max_epu8		16この8ビット符号無し整数の大きい方を取る
 */
__m128i _mm_max_epu8 (__m128i a, __m128i b)
{
/* Computes the pairwise maxima of the 16 unsigned 8-bit integers from a */
/* and the 16 unsigned 8-bit integers from b. */
/* r0 := max(a0, b0) */
/* r1 := max(a1, b1) */
/* ... */
/* r15 := max(a15, b15) */

	__m128i r;
	uint8_t *ap = (uint8_t *) &a;
	uint8_t *bp = (uint8_t *) &b;
	uint8_t *rp = (uint8_t *) &r;
	int i;
	for (i = 0; i < 16; i++) {
		rp[i] = (ap[i] > bp[i]) ? ap[i] : bp[i];
	}
	return r;
}

/** _mm_movemask_epi8	16この8ビット符号付きor無し整数の最大ビットから16ビットマスク生成
 */
int _mm_movemask_epi8 (__m128i a)
{
/* Creates a 16-bit mask from the most significant bits of the 16 signed */
/* or unsigned 8-bit integers in a and zero extends the upper bits. */
/* r := a15[7] << 15 | */
/* a14[7] << 14 | */
/* ... */
/* a1[7] << 1 | */
/* a0[7] */
	int r = 0;
	uint8_t *ap = (uint8_t *) &a;
	int i;
	for (i = 0; i < 16; i++) {
		r |= (ap[i] >> 7) << i;
		/* uint8_t ai = ap[i]; */
		/* uint8_t ai7 = ai >> 7; */
		/* r |= ai7 << i; */
		/* printf("%d: ap[i]=%x, ap[i]>>7=%x, r=%x\n", i, ai, ai7, r); */
	}
	r &= 0xffff;
	return r;
}

/** _mm_set1_epi16		
 */
__m128i _mm_set1_epi16 (int16_t w)
{
/* Sets the 8 signed 16-bit integer values to w. */
/* r0 := w */
/* r1 := w */
/* ... */
/* r7 := w */

	__m128i r;
	int16_t *rp = (int16_t *) &r;
	int i;
	w = b2l16(w);
	for (i = 0; i < 8; i++) {
		rp[i] = w;
	}
	return r;
}

/** _mm_set1_epi32		
 */
__m128i _mm_set1_epi32 (int i)
{
/* Sets the 4 signed 32-bit integer values to i. */
/* r0 := i */
/* r1 := i */
/* r2 := i */
/* r3 := I */
	__m128i r;
	int *rp = (int *) &r;
	int k;
	i = b2l32(i);
	for (k = 0; k < 4; k++) {
		rp[k] = i;
	}
	return r;
}

/** _mm_set1_epi8		
 */
__m128i _mm_set1_epi8 (int8_t b)
{
/* Sets the 16 signed 8-bit integer values to b. */
/* r0 := b */
/* r1 := b */
/* ... */
/* r15 := b */

	__m128i r;
	int8_t *rp = (int8_t *) &r;
	int i;
	for (i = 0; i < 16; i++) {
		rp[i] = b;
	}
	return r;
}

/** _mm_slli_si128		
 */
__m128i _mm_slli_si128 (__m128i a, int imm)
{
/* Shifts the 128-bit value in a left by imm bytes while shifting in */
/* zeros. imm must be an immediate. */
/* r := a << (imm * 8) */

	__m128i r;
	int8_t *ap = (int8_t *) &a;
	int8_t *rp = (int8_t *) &r;
	int i;
	for (i = 0; i < imm; i++) {
		rp[i] = 0;
	}
	for (i = imm; i < 16; i++) {
		rp[i] = ap[i-imm];
	}
	return r;
}

/** _mm_srli_si128		
 */
__m128i _mm_srli_si128 (__m128i a, int imm)
{
/* Shifts the 128-bit value in a right by imm bytes while shifting in */
/* zeros. imm must be an immediate. */
/* r := srl(a, imm*8) */

	__m128i r;
	int8_t *ap = (int8_t *) &a;
	int8_t *rp = (int8_t *) &r;
	int i;
	for (i = imm; i < 16; i++) {
		rp[i-imm] = ap[i];
	}
	for (i = 16-imm; i < 16; i++) {
		rp[i] = 0;
	}
	return r;
}

/** _mm_store_si128		
 */
void _mm_store_si128 (__m128i *p, __m128i a)
{
/* Stores 128-bit value. */
/* *p := a */
/* Address p must be 16-byte aligned. */
	*p = a;
}

/** _mm_subs_epu16		8つの16ビット符号無し整数の減算
 */
__m128i _mm_subs_epu16 (__m128i a, __m128i b)
{
/* Subtracts the 8 unsigned 16-bit integers of b from the 8 signed 16-bit */
/* integers of a and saturates. */
/* r0 := SignedSaturate(a0 - b0) */
/* r1 := SignedSaturate(a1 - b1) */
/* ... */
/* r7 := SignedSaturate(a7 - b7) */

	__m128i r;
	uint16_t *ap = (uint16_t *) &a;
	uint16_t *bp = (uint16_t *) &b;
	uint16_t *rp = (uint16_t *) &r;
	int i;
	for (i = 0; i < 8; i++) {
		rp[i] = b2l16u( saturate_sub_uint16(l2b16u(ap[i]), l2b16u(bp[i])) );
	}
	return r;
}

/** _mm_subs_epu8		16この8ビット符号無し整数の減算
 */
__m128i _mm_subs_epu8 (__m128i a, __m128i b)
{
/* Subtracts the 16 unsigned 8-bit integers of b from the 16 unsigned */
/* 8-bit integers of a and saturates. */
/* r0 := UnsignedSaturate(a0 - b0) */
/* r1 := UnsignedSaturate(a1 - b1) */
/* ... */
/* r15 := UnsignedSaturate(a15 - b15) */

	__m128i r;
	uint8_t *ap = (uint8_t *) &a;
	uint8_t *bp = (uint8_t *) &b;
	uint8_t *rp = (uint8_t *) &r;
	int i;
	for (i = 0; i < 16; i++) {
		rp[i] = saturate_sub_uint8(ap[i], bp[i]);
	}
	return r;
}
