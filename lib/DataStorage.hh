// 2011/02/20 Yuki YOKOKURA
//
//
// Copyright (C) 2011 Yuki YOKOKURA
// This program is free software;
// you can redistribute it and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3 of the License, or any later version.
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details <http://www.gnu.org/licenses/>.
// Besides, you can negotiate about other options of licenses instead of GPL.
// If you would like to get other licenses, please contact us<yuki@katsura.sd.keio.ac.jp>.

#ifndef DATASTORAGE
#define DATASTORAGE

#include <fstream>

namespace ARCS {	
	
	class DataStorage {
		private:
			DataStorage(const DataStorage&);	
			const DataStorage& operator=(const DataStorage&);
			const unsigned int N;
			const unsigned long Ts;
			const double Tend;
			const unsigned long tlen;
			double** Data;
			unsigned long count;
		public:
			enum SaveType {FORMAT_CSV, FORMAT_DAT};
			DataStorage(const unsigned int NumOfVar, const unsigned long SmplTime, const double SaveTime);
			~DataStorage();
			void PutData(double* Value, unsigned int NumOfVar);
			bool SaveDataFile(const char* const FileName, const SaveType FileType, const unsigned short DataPresicion);
			void ClearCounter(void);
	};
}

#endif



