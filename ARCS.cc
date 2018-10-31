// Copyright (C) 2011-2017 Yuki YOKOKURA, Hiroki KURUMATANI
// This program is free software;
// you can redistribute it and/or modify it under the terms of the FreeBSD License.
// For details, see the License.txt file.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ControlFunctions.hh"
#include "Parameters.hh"

using namespace ARCS;

int main(){

	ControlFunctions* CtrlFuncs = new ControlFunctions;
	
	CtrlFuncs->InitProcess();
	for(unsigned long i=0;i<ConstParams::DATA_CYCLE;i++) CtrlFuncs->LoopProcess();
	CtrlFuncs->ExitProcess();

	delete CtrlFuncs;

	return 0;
}
