// Copyright (C) 2018, Hiroki KURUMATANI
// This program is free software;
// you can redistribute it and/or modify it under the terms of the FreeBSD License.
// For details, see the License.txt file.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int uio_irq_on(int uio_fd){
	unsigned int irq_on=1;
	return write(uio_fd,&irq_on,sizeof(irq_on));
}

int uio_wait_irq(int uio_fd){
	unsigned int ret=0;
	return read(uio_fd,&ret,sizeof(ret));
}


int main()
{
    int uio_fd;
    if((uio_fd=open("/dev/uio0",O_RDWR))==-1){
        printf("Can not open /dev/uio0\n"); exit(1);
    }

    volatile unsigned int* map_addr;
    map_addr=(unsigned int*)mmap(NULL,0x1000,PROT_READ|PROT_WRITE,MAP_SHARED,uio_fd,0);	
    
	int ena=0x0;
	ena|=(1<<0);
	ena|=(1<<1);
//	map_addr[2]=0x00004e1f;	//200us
	map_addr[2]=0x0000270f;	//100us
//	map_addr[2]=0x00001387;	//50us
	map_addr[1]=ena;	//enable DAC

	unsigned int d=0.0;
	volatile double wave=0.0;
	const double bitweight=20.0/pow(2,16);
	const double midscale=pow(2,15);
		
	volatile double t=0.0;
	const double Ts=1e-4;
	double logt[10000]={0.0};
		
	struct timespec st,ed;
	struct timespec stx,edx;
	clock_gettime(CLOCK_MONOTONIC,&stx);
	clock_gettime(CLOCK_MONOTONIC,&st);

	wave=1;
	
	for(int i=0;i<1e4;i++){
					
		if(uio_irq_on(uio_fd)==-1){  printf("error1\n");break;};
		if(uio_wait_irq(uio_fd)==-1){printf("error2\n");break;};

		wave=4.0*sin(100.0*2.0*M_PI*t);
		d=wave/bitweight+midscale;
		map_addr[0]=d;
	
		clock_gettime(CLOCK_MONOTONIC,&ed);
		logt[i]=(ed.tv_nsec-st.tv_nsec)*1e-9;
		st=ed;
		
		t+=Ts;
	}
    
	clock_gettime(CLOCK_MONOTONIC,&edx);
	printf("%lf %lf\n",(edx.tv_sec-stx.tv_sec)+(edx.tv_nsec-stx.tv_nsec)*1e-9,t);

	FILE *lt;
	lt=fopen("sampling.dat","w");
	for(int i=0;i<1e4;i++) fprintf(lt,"%lf\n",logt[i]);
	fclose(lt);

	map_addr[1]=0;
    munmap((void*)map_addr, 0x1000);
    close(uio_fd);

	return 0;
}

