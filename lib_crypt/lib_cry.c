#include "lib_cry.h"

unsigned char header=0;

const unsigned char  header_const[7]= {0xFE,0xA0,'S','k','O','t','A'};



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



//private service Functions

unsigned char pull_incom_crypt(void)
{
    incom_crypt_buf_count++;
    if (incom_crypt_buf_count>=64) incom_crypt_buf_count=0;
    return incom_crypt_buf[incom_crypt_buf_count];
}

void push_incom_decrypt  (unsigned char sym)
{
    incom_decrypt_buf_head++;
    if (incom_decrypt_buf_head>=64) incom_decrypt_buf_head=0;
    incom_decrypt_buf[incom_decrypt_buf_head]=sym;
}

void push_outcom_crypt(unsigned char sym)
{
    outcom_crypt_buf_head++;
    if (outcom_crypt_buf_head>=64) outcom_crypt_buf_head=0;
    outcom_crypt_buf[outcom_crypt_buf_head]=sym;
}

unsigned char pull_outcom_decrypt  (void)
{
    outcom_decrypt_buf_count++;
    if (outcom_decrypt_buf_count>=64) outcom_decrypt_buf_count=0;
    return outcom_decrypt_buf[outcom_decrypt_buf_count];
}

void incom_erase(void)
{
    incom_crypt_buf_count   =0;
    incom_crypt_buf_head    =0;
    incom_decrypt_buf_count =0;
    incom_decrypt_buf_head  =0;
    incom_crypt_count       =0;
    incom_crypt_length      =0;

}

void outcom_erase(void)
{
    outcom_crypt_buf_count  =0;
    outcom_crypt_buf_head   =0;
    outcom_decrypt_buf_count=0;
    outcom_decrypt_buf_head =0;
    outcom_crypt_count      =0;
    outcom_crypt_offset     =0;

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

//Verify preambula
            if ((header_const[incom_crypt_count]^crypt_char)!=0) incom_erase();

        }
        else if (incom_crypt_count=11)
        {
            incom_open_key[0]=

        }

    }

    if (outcom_decrypt_buf_count!=outcom_decrypt_buf_head)
    {
//encrypting process
        if (outcom_crypt_count==0)
        {
            push_outcom_crypt(header_const[0]);
            push_outcom_crypt(header_const[1]);
            push_outcom_crypt(header_const[2]);
            push_outcom_crypt(header_const[3]);
            push_outcom_crypt(header_const[4]);
            push_outcom_crypt(header_const[5]);
            push_outcom_crypt(header_const[6]);
            push_outcom_crypt(0);
            push_outcom_crypt(public_key[0]);
            push_outcom_crypt(public_key[1]);
            push_outcom_crypt(public_key[2]);
            push_outcom_crypt(public_key[3]);
        }
        while(outcom_decrypt_buf_count!=outcom_decrypt_buf_head)
        {
            push_outcom_crypt(pull_outcom_decrypt()^public_key[outcom_crypt_count%4]^private_key[outcom_crypt_offset+outcom_crypt_count]);
            outcom_crypt_count++;
        }
    }


}

