#ifndef LIB_CRY_H_INCLUDED
#define LIB_CRY_H_INCLUDED

//_buf   - loop bufer in 64 symbols.
//_buf_head  - last pushed buffer symbol
//_buf_count - last pulled buffer symbol
//_count - counter crypt/decrypt symbol
//If _head=_count - NOP
//incom_crypt    - crypted   input
//incom_decrypt  - decrypted output
//outcom_decrypt - decrypted input
//outcom_crypt   - crypted   output

const unsigned char  header_const[]=[0xFE,0xA0,'S','k','O','t','A'];
unsigned char incom_crypt_buf   [64];
unsigned char incom_crypt_buf_count ;
unsigned char incom_crypt_buf_head  ;
unsigned char incom_crypt_count     ;
unsigned char incom_crypt_length    ;

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
