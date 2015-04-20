#ifndef LIB_CRY_H_INCLUDED
#define LIB_CRY_H_INCLUDED
extern unsigned char private_key[56];
extern unsigned char public_key[8];

unsigned char* crypt(unsigned char* str);
unsigned char* decrypt(unsigned char* str);

#endif // LIB_CRY_H_INCLUDED
