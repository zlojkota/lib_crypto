#include "lib_cry.h"

unsigned char header=0;

void push_incom_crypt  (unsigned char sym)
{
    incom_crypt_buf_head++;
    if (incom_crypt_buf_head>=64) incom_crypt_buf_head=0;
    incom_crypt_buf[incom_crypt_buf_head]=sym;
}

unsigned char pull_incom_decrypt(void)
{
    incom_decrypt_buf_count++;
    if (incom_decrypt_buf_count>=64) incom_decrypt_buf_count=0;
    return incom_decrypt_buf[incom_decrypt_buf_count];
}

void push_outcom_decrypt(unsigned char sym)
{
    outcom_decrypt_buf_head++;
    if (outcom_decrypt_buf_head>=64) outcom_decrypt_buf_head=0;
    outcom_decrypt_buf[outcom_decrypt_buf_head]=sym;
}

unsigned char pull_outcom_crypt  (void)
{
    outcom_crypt_buf_count++;
    if (outcom_crypt_buf_count>=64) outcom_crypt_buf_count=0;
    return outcom_crypt_buf[outcom_crypt_buf_count];
}




unsigned char pull_incom_crypt(void)
{
    incom_crypt_buf_count++;
    if (incom_crypt_buf_count>=64) incom_crypt_buf_count=0;
    return incom_crypt_buf[incom_crypt_buf_count];
}

void incom_erase(void)
{
    incom_crypt_buf_count   =0;
    incom_crypt_buf_head    =0;
    incom_decrypt_buf_count =0;
    incom_decrypt_buf_head  =0;
    incom_crypt_count       =0;
    incom_crypt_length      =8;

}

void outcom_erase(void)
{
    outcom_crypt_buf_count  =0;
    outcom_crypt_buf_head   =0;
    outcom_decrypt_buf_count=0;
    outcom_decrypt_buf_head =0;

}

void crypt_init(void)
{
    incom_erase();
    outcom_erase();
}

void crypt_processing(void)
{
    unsigned char crypt_char;
    if (incom_crypt_buf_count!=incom_crypt_buf_head)
    {
//decrypting process

        crypt_char=pull_incom_crypt();

        if (incom_crypt_count<7)
        {
//Analyzing Preambula
            if (incom_crypt_count==1)
            {
//Get length packet - 1- 8byte, 2 - 44 byte
                incom_crypt_length=header_const[incom_crypt_count]^crypt_char;
                if ((if incom_crypt_length!=1)&&(if incom_crypt_length!=2)) incom_erase();
            }
            else
            {
//Verify preambula
                if ((header_const[incom_crypt_count]^crypt_char)!=0) incom_erase();
            }
        }
        else
        {
//get open key and decrypt

        }

    }

    if (outcom_decrypt_buf_count!=outcom_decrypt_buf_head)
    {
//encrypting process

    }


}






