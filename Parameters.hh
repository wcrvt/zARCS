// Copyright (C) 2011-2017 Yuki YOKOKURA, Hiroki KURUMATANI
// This program is free software;
// you can redistribute it and/or modify it under the terms of the FreeBSD License.
// For details, see the License.txt file.

#include "DataStorage.hh"

namespace ARCS{
	class ConstParams{
		private:
		public:

			//Thread
			static const unsigned short THREAD_MAX=2;
			static const unsigned short THREAD_NUM=1;
			static const unsigned long SAMPLING_TIME_NS[THREAD_MAX];
			//Save
			static const DataStorage::SaveType DATA_TYPE=DataStorage::FORMAT_DAT;
			static const unsigned short DATA_DECIMAL_PLACES=7;
			static const unsigned short DATA_NUM=4;
			static const double DATA_TIME;
			static const unsigned long DATA_CYCLE;
			//Actuation
			static const unsigned short ACT_MAX=8;
			static const double AMP_IREFtoVOLT[ACT_MAX];
			static const double AMP_TORQUE_CONSTANT[ACT_MAX];
			static const double MOTOR_INERTIA[ACT_MAX];
			static const double MOTOR_RATED_CUR[ACT_MAX];
			//Peripheral: DAC, ADC, Encoder Pulse Counter (EPC)
			static const unsigned short PERIPH_NUM=8;
			//DAC
			static const unsigned short DAC_NUM=1;
			static const unsigned short DAC_BIT=16;
			static const double DAC_RANGE;
			static const double DAC_VOLTtoBIT;
			//EPC
			static const unsigned short ADC_NUM=1;
			static const unsigned short ADC_BIT=18;
			static const double ADC_RANGE;
			static const double ADC_BITtoVOLT;
			//Encoder Pulse Counter
			static const unsigned short EPC_NUM=1;
			static const double EPC_RESOLUTION[ACT_MAX];
	};
}	
