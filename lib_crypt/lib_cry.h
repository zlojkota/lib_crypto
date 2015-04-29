#ifndef LIB_CRY_H_INCLUDED
#define LIB_CRY_H_INCLUDED

//_buf   - loop bufer in 64 symbols.
//_head  - last pushed symbol
//_count - last pulled symbol
//If _head=_count - NOP

unsigned char incom_crypt_buf   [64];
unsigned char incom_crypt_buf_count ;
unsigned char incom_crypt_buf_head ;

unsigned char incom_decrypt_buf [64];
unsigned char incom_decrypt_buf_count ;
unsigned char incom_decrypt_buf_head ;

unsigned char outcom_crypt_buf  [64];
unsigned char outcom_crypt_buf_count ;
unsigned char outcom_crypt_buf_head ;

unsigned char outcom_decrypt_buf[64];
unsigned char outcom_decrypt_buf_count ;
unsigned char outcom_decrypt_buf_head ;

unsigned char public_key[4];
unsigned char secret_key[128];


void          push_incom_crypt  (unsigned char sym);
unsigned char pull_incom_decrypt(void);

void          push_oucom_decrypt(unsigned char sym);
unsigned char pull_oucom_crypt  (void);

void crypt_processing(void);

#endif // LIB_CRY_H_INCLUDED
