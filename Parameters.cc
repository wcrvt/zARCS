// Copyright (C) 2011-2017 Yuki YOKOKURA, Hiroki KURUMATANI
// This program is free software;
// you can redistribute it and/or modify it under the terms of the FreeBSD License.
// For details, see the License.txt file.

#include <math.h>
#include "Parameters.hh"

using namespace ARCS;
//Thread
const unsigned long ConstParams::SAMPLING_TIME_NS[THREAD_MAX]={
	100000,
	100000
};

//Save
const double ConstParams::DATA_TIME=7;
const unsigned long long DATA_TIME_NS=ConstParams::DATA_TIME*1e9;
const unsigned long ConstParams::DATA_CYCLE=DATA_TIME_NS/ConstParams::SAMPLING_TIME_NS[1]; 

//Actuation
const double ConstParams::AMP_IREFtoVOLT[ACT_MAX]={
	1.0,
	1.0,
	1.0,
	1.0,
	1.0,
	1.0,
	1.0,
	1.0
};
const double ConstParams::AMP_TORQUE_CONSTANT[ACT_MAX]={
	1.0,
	1.0,
	1.0,
	1.0,
	1.0,
	1.0,
	1.0,
	1.0
};
const double ConstParams::MOTOR_INERTIA[ACT_MAX]={
	1.0,
	1.0,
	1.0,
	1.0,
	1.0,
	1.0,
	1.0,
	1.0
};

//DAC
const double ConstParams::DAC_RANGE=20.0;
const double ConstParams::DAC_VOLTtoBIT=pow(2,ConstParams::DAC_BIT)/ConstParams::DAC_RANGE;

//ADC
const double ConstParams::ADC_RANGE=10.0;
const double ConstParams::ADC_BITtoVOLT=ConstParams::ADC_RANGE/pow(2,ConstParams::ADC_BIT);

//EPC
const double ConstParams::EPC_RESOLUTION[ACT_MAX]={
	50e-9,
	50e-9,
	50e-9,
	50e-9,
	50e-9,
	50e-9,
	50e-9,
	50e-9	
};




