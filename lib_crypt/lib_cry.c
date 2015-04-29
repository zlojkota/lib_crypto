#include "lib_cry.h"
void push_incom_crypt  (unsigned char sym){
incom_crypt_buf_head++;
if (incom_crypt_buf_head>=64) incom_crypt_buf_head=0;
incom_crypt_buf[incom_crypt_buf_head]=sym;
}

unsigned char pull_incom_decrypt(void){
incom_decrypt_buf_count++;
if (incom_decrypt_buf_count>=64) incom_decrypt_buf_count=0;
return incom_decrypt_buf[incom_decrypt_buf_count];
}

void push_outcom_decrypt(unsigned char sym){
outcom_decrypt_buf_head++;
if (outcom_decrypt_buf_head>=64) outcom_decrypt_buf_head=0;
outcom_decrypt_buf[outcom_decrypt_buf_head]=sym;
}

unsigned char pull_outcom_crypt  (void){
outcom_crypt_buf_count++;
if (outcom_crypt_buf_count>=64) outcom_crypt_buf_count=0;
return outcom_crypt_buf[outcom_crypt_buf_count];
}

void crypt_init(void){
incom_crypt_buf_count   =0;
incom_crypt_buf_head    =0;
incom_decrypt_buf_count =0;
incom_decrypt_buf_head  =0;
outcom_crypt_buf_count  =0;
outcom_crypt_buf_head   =0;
outcom_decrypt_buf_count=0;
outcom_decrypt_buf_head =0;
}
