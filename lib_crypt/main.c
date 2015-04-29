/////////////////////////////////////////////////
// Serial port interface program               //
/////////////////////////////////////////////////
#include <stdio.h> // standard input / output functions
#include <string.h> // string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include "termios.h" // POSIX terminal control definitionss
#include <time.h>   // time calls
#include <stdlib.h>

// unkoment to use wireless communication
//#define xbee 1

unsigned char private_key[56],public_key[8];

int open_port(char *port)
{
    int fd; // file description for the serial port


    fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd == -1) // if open is unsucessful
    {
        perror("open_port: Unable to open");
    }
    else
    {
        //fcntl(fd, F_SETFL, FNDELAY);
        fcntl(fd, F_SETFL, 0);
    }
    return(fd);
}

int configure_port(int fd)      // configure the port
{
    struct termios port_settings;      // structure to store the port settings in
    unsigned int tmr=0,i;
    unsigned char buf[16];
    unsigned char c=0,nxt=0;

    cfsetispeed(&port_settings, B38400);    // set baud rates
    cfsetospeed(&port_settings, B38400);

    port_settings.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits
    port_settings.c_cflag &= ~CSTOPB;
    port_settings.c_cflag &= ~CSIZE;
    port_settings.c_cflag |= CS8;

    cfmakeraw(&port_settings);
    tcsetattr(fd, TCSANOW, &port_settings);    // apply the settings to the port


#ifdef xbee
    write(fd,"+++",3);
    buf[0]=0;
    for(; nxt==0;)
    {
        read(fd,buf,3);
        printf("%u %s\n",tmr,buf);
        for (i=15; i>0; i--) buf[i]=buf[i-1];
        if ((buf[1]==0x4f)&&(buf[2]==0x4b)) nxt=1;
    }

    write(fd,"ATCH10\r\n",8);
    read(fd,buf,3);
    printf("ATCH10-%s\n",buf);
    usleep(5000);
    write(fd,"ATMYFFFF\r\n",10);
    read(fd,buf,3);
    printf("ATMYFFFF-%s\n",buf);
    usleep(5000);
    write(fd,"ATDLFFFF\r\n",10);
    read(fd,buf,3);
    printf("ATDLFFFF-%s\n",buf);
    usleep(5000);
    write(fd,"ATDH0000\r\n",10);
    read(fd,buf,3);
    printf("ATDH0000-%s\n",buf);
    usleep(5000);
    write(fd,"ATWR\r\n",6);
    read(fd,buf,3);
    printf("ATWR-%s\n",buf);
    usleep(5000);
    write(fd,"ATCN\r\n",6);
    read(fd,buf,3);
    printf("ATCN-%s\n",buf);
    usleep(5000);
#endif
    return(fd);

}


int main(void)
{   srand(time(NULL));
    int fd = open_port("/dev/ttyUSB0"); //master
    int fd1 = open_port("/dev/ttyUSB1");//slave
    unsigned char str[44]="HuemHujNaLbu4eshiNuABat'kuNeSmeshiDesatochka";
    unsigned char buffer[44],i;
    configure_port(fd);
    configure_port(fd1);
    write(fd,"abrygalg",8);
    read(fd1,buffer,16);
    printf("%s",buffer);
printf("Private_Key:\n");
    for (i=0; i<56; i++)
    {
        private_key[i]=rand()%256;
        printf("%X\n",private_key[i]);

    }
printf("Public_Key:\n");

        for (i=0; i<8; i++)
    {
        public_key[i]=rand()%256;
        printf("%X\n",public_key[i]);

    }





    close(fd);
    close(fd1);

    return(0);
}
