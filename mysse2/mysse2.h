#ifndef MYSSE2_H_
#define MYSSE2_H_

#include <stdint.h>
#include <emmintrin.h>

/** _mm_adds_epi16		8つの16ビット符号付き整数の加算
 */
__m128i _mm_adds_epi16 (__m128i a, __m128i b);

/** _mm_adds_epu8		16この8ビット符号無し整数の加算
 */
__m128i _mm_adds_epu8 (__m128i a, __m128i b);

/** _mm_cmpeq_epi8		16この8ビット符号付きor無し整数の等式比較
 */
__m128i _mm_cmpeq_epi8 (__m128i a, __m128i b);

/** _mm_cmpgt_epi16		8この16ビット符号付き整数の＞不等式比較
 */
__m128i _mm_cmpgt_epi16 (__m128i a, __m128i b);

/** _mm_extract_epi16	指定された16ビット符号付きor無し整数の取り出し
 */
int _mm_extract_epi16 (__m128i a, int imm);

/** _mm_load_si128		
 */
__m128i _mm_load_si128 (__m128i *p);

/** _mm_max_epi16		8つの16ビット符号付き整数の大きい方を取る
 */
__m128i _mm_max_epi16 (__m128i a, __m128i b);

/** _mm_max_epu8		16この8ビット符号無し整数の大きい方を取る
 */
__m128i _mm_max_epu8 (__m128i a, __m128i b);

/** _mm_movemask_epi8	16この8ビット符号付きor無し整数の最大ビットから16ビットマスク生成
 */
int _mm_movemask_epi8 (__m128i a);

/** _mm_set1_epi16		
 */
__m128i _mm_set1_epi16 (int16_t w);

/** _mm_set1_epi32		
 */
__m128i _mm_set1_epi32 (int i);

/** _mm_set1_epi8		
 */
__m128i _mm_set1_epi8 (int8_t b);

/** _mm_slli_si128		
 */
__m128i _mm_slli_si128 (__m128i a, int imm);

/** _mm_srli_si128		
 */
__m128i _mm_srli_si128 (__m128i a, int imm);

/** _mm_store_si128		
 */
void _mm_store_si128 (__m128i *p, __m128i a);

/** _mm_subs_epu16		8つの16ビット符号無し整数の減算
 */
__m128i _mm_subs_epu16 (__m128i a, __m128i b);

/** _mm_subs_epu8		16この8ビット符号無し整数の減算
 */
__m128i _mm_subs_epu8 (__m128i a, __m128i b);

#endif /* MYSSE2_H_ */
