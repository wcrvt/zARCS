// Copyright (C) 2011-2017 Yuki YOKOKURA, Hiroki KURUMATANI
// This program is free software;
// you can redistribute it and/or modify it under the terms of the FreeBSD License.
// For details, see the License.txt file.

#include "ControlFunctions.hh"
#include "Parameters.hh"

//Control libraries
#include "Differentiator.hh"
#include "LowPassFilter.hh"

//Data Storage
#include "DataStorage.hh"

#define print_bit(a) for(int i=31;i>=0;i--) printf("%d",(a>>i)&1);printf("\n");

using namespace ARCS;

namespace{
	volatile CtrlMode CmdFlag = CTRL_INIT;
	int uio_fd;
	volatile unsigned int* map_addr;
	typedef union { float f; int i; } ufloat;
	DataStorage* ExpData=0;
}


void ControlFunctions::ControlFunction1(ControlFunctions*){
	
	//Sampling time
	const double Ts=ConstParams::SAMPLING_TIME_NS[0]*1e-9;
	static double t=0.0;

	//Libraries
	static Differentiator*		DIFF;
	static LowPassFilter*	LPF[2];
	
	//Control references
	static double Xcmd	= 0.0;
	static double Fcmd	= 0.0;
	static double Xref		= 0.0;

	//Data storage
	static double Data[ConstParams::DATA_NUM]={0};	// データ格納用変数
	
	////////////////////////////////////////////////
	////	FPGA Configuration	////
	////////////////////////////////////////////////
	//Sampling time of FPGA
		const double fpga_Ts=2e-6;
		const double fpga_Tc=1e-8;
		//Control references
		static ufloat fpga_Xcmd	= {.f=0.0};
		static ufloat fpga_Fcmd	= {.f=0.0};
		//Response
		static ufloat fpga_Xres	= {.f=0.0};
		static ufloat fpga_Fres	= {.f=0.0};
	//Register Access
		//Virtual memory mapping to physical memory 
		const unsigned int IRQtimer_reg	= (unsigned int) ((Ts/fpga_Tc)-1);
		static unsigned int enable_reg		= 0x0;
		static unsigned int inout_reg[6]	= {0};
		//Enable
		static unsigned int ena_DAC = 0x0;		//DAC
		static unsigned int ena_ADC = 0x0;		//ADC
		static unsigned int ena_EPC = 0x0;		//Encoder pulse counter
		static unsigned int ena_TSC = 0x0;			//Time stamp counter
		
	if(CmdFlag==CTRL_INIT){
		// Instance
		DIFF = new Differentiator(gdif,Ts);
		LPF[0] = new LowPassFilter(glpf,Ts);
		LPF[1] = new LowPassFilter(glpf,Ts);
		//Enabling peripheral
		for(int i=0;i<ConstParams::DAC_NUM;i++) ena_DAC|= (1<<i);
		for(int i=0;i<ConstParams::ADC_NUM;i++) ena_ADC|= (1<<i);
		for(int i=0;i<ConstParams::EPC_NUM;i++) ena_EPC|= (1<<i);
		ena_TSC=0x1;
		enable_reg |= (ena_DAC << ConstParams::PERIPH_NUM*0);
		enable_reg |= (ena_ADC << ConstParams::PERIPH_NUM*1);
		enable_reg |= (ena_EPC << ConstParams::PERIPH_NUM*2);
		enable_reg |= (ena_TSC << ConstParams::PERIPH_NUM*3);
		map_addr[1]=0xffffffff;	//forcibly enable
		map_addr[2]=IRQtimer_reg;
	}else if(CmdFlag==CTRL_EXIT){
		//Release
		delete DIFF;
		delete LPF[0];
		delete LPF[1];
		//Disabling peripheral
		enable_reg = 0x0;
		for(int i=0;i<6;i++) inout_reg[i]=0;
		map_addr[1]=enable_reg;
	}else if(CmdFlag==CTRL_LOOP){
		
		fpga_Xres.i	= inout_reg[2];
		fpga_Fres.i	= inout_reg[3];
		
		if(t<2.0) Xcmd=0.0; else Xcmd=1.0;
		Xcmd=LPF[0]->GetSignal(LPF[1]->GetSignal(Xcmd));
		
		fpga_Xcmd.f = (float) Xcmd;
		fpga_Fcmd.f = (float) Fcmd;
		
		inout_reg[0]	= fpga_Xcmd.i;
		inout_reg[1]	= fpga_Fcmd.i;	
		
		Xref=4.0*sin(100.0*2.0*M_PI*t);
		fpga_Xres.i=(unsigned int) (Xref/(20.0/pow(2,16))+pow(2,15));
		inout_reg[0]=fpga_Xres.i;
		
		map_addr[0]=inout_reg[0];

		Data[0]=t;
		Data[1]=fpga_Xcmd.f;
		Data[2]=fpga_Xres.f;
		Data[3]=fpga_Fres.f;
		ExpData->PutData(Data,ConstParams::DATA_NUM);
		
		t+=Ts;
	}
}

void ControlFunctions::ControlFunction2(ControlFunctions*){
	if(CmdFlag==CTRL_INIT){
	}else if(CmdFlag==CTRL_EXIT){
	}else if(CmdFlag==CTRL_LOOP){
	}
}

void ControlFunctions::InitProcess(){
	printf("Initial process:\n");
	CmdFlag = CTRL_INIT;
	ExpData = new DataStorage(ConstParams::DATA_NUM,ConstParams::SAMPLING_TIME_NS[0],ConstParams::DATA_TIME);
	if((uio_fd=open("/dev/uio0",O_RDWR))==-1){ printf("Can not open /dev/uio0\n"); exit(1);}
	map_addr=(unsigned int*)mmap(NULL,0x1000,PROT_READ|PROT_WRITE,MAP_SHARED,uio_fd,0);
	for(unsigned short i=0;i<ConstParams::THREAD_NUM;i++) (*pCtrlFuncs[i])(this);
	if(ControlFunctions::uio_irq_on(uio_fd)==-1){  printf("uio interrupt accept error\n");exit(1);};
}

void ControlFunctions::LoopProcess(){
	CmdFlag = CTRL_LOOP;
	if(ControlFunctions::uio_wait_irq(uio_fd)==-1){printf("uio read error\n");exit(1);};
	for(unsigned short i=0;i<ConstParams::THREAD_NUM;i++) (*pCtrlFuncs[i])(this);
	if(ControlFunctions::uio_irq_on(uio_fd)==-1){  printf("uio interrupt accept error\n");exit(1);};
}
void ControlFunctions::ExitProcess(){
	printf("Exit process:\n");
	CmdFlag = CTRL_EXIT;
	for(unsigned short i=0;i<ConstParams::THREAD_NUM;i++) (*pCtrlFuncs[i])(this);
	munmap((void*)map_addr, 0x1000);
	ExpData->SaveDataFile("DATA.dat",ConstParams::DATA_TYPE,ConstParams::DATA_DECIMAL_PLACES);
}

// constructor
ControlFunctions::ControlFunctions(){
	pCtrlFuncs[0]=ControlFunction1;
	pCtrlFuncs[1]=ControlFunction2;
}

// destructor
ControlFunctions::~ControlFunctions(){
	delete ExpData;
}

int ControlFunctions::uio_irq_on(int uio_fd){
	unsigned int irq_on=1;
	return write(uio_fd,&irq_on,sizeof(irq_on));
}
	
int ControlFunctions::uio_wait_irq(int uio_fd){
	unsigned int ret=0;
	return read(uio_fd,&ret,sizeof(ret));
}
