#ifndef BITMATH_H_
#define BITMATH_H_


#define SET_BIT(P, B) (P |= (1 << B))
#define GET_BIT(P, B) ((P >> B) & 1)
#define TGL_BIT(P, B) (P ^= (1 << B))
#define CLR_BIT(P, B) (P &= ~(1 << B))

#endif