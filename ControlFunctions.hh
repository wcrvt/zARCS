// Copyright (C) 2011-2017 Yuki YOKOKURA, Hiroki KURUMATANI
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

/* Note: This program is for ARM(PS) on zynq.
Heavy process should be executed on FPGA(PL).
Available threads are 2. */

namespace ARCS{
	
	enum CtrlMode{CTRL_INIT,CTRL_LOOP,CTRL_EXIT};

	class ControlFunctions{
		private:			
			static void ControlFunction1(ControlFunctions*);
			static void ControlFunction2(ControlFunctions*);
		public:
			ControlFunctions();
			~ControlFunctions();
			int uio_irq_on(int uio_fd);
			int uio_wait_irq(int uio_fd);
			void InitProcess();
			void LoopProcess();
			void ExitProcess();
			void (*pCtrlFuncs[2])(ControlFunctions*);
	};
}
