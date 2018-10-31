// 2011/03/14 Yuki YOKOKURA
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

#include "DataStorage.hh"

using namespace ARCS;

DataStorage::DataStorage(const unsigned int NumOfVar, const unsigned long SmplTime, const double SaveTime)
	: N(NumOfVar),
	  Ts(SmplTime),
	  Tend(SaveTime),
	  //2018/11/01 H.Kurumatani changed "unsigned long" -> "unsigned long long"
	  tlen(((unsigned long long)(Tend*1e9))/Ts),
	  Data(0),
	  count(0)
{
	Data = new double*[N];
	Data[0] = new double[N*tlen];
	for(unsigned int i=1;i<N;i++)Data[i]=Data[0]+i*tlen;
}

DataStorage::~DataStorage(){
	delete[] Data[0];
	delete[] Data;
}

void DataStorage::PutData(double* Value, unsigned int NumOfVar){
	for(unsigned int k=0;k<NumOfVar;k++) if(k<N && count<tlen)Data[k][count]=Value[k];
	count++;
}

bool DataStorage::SaveDataFile(const char* const FileName, const SaveType FileType, const unsigned short DecimalPlaces){
	
	std::ofstream fout(FileName, std::ios::out | std::ios::trunc);
	if(fout.bad()==true || fout.fail()==true) return false;
	
	fout.setf(std::ios::scientific);
	fout.width(DecimalPlaces+1);
	fout.precision(DecimalPlaces);
	
	unsigned int i;
	unsigned long j;
	for(j=0;j<tlen;j++){
		for(i=0;i<N;i++){
			fout<<Data[i][j];
			if(i<N-1){
				if(FileType==FORMAT_CSV)fout<<',';	
				if(FileType==FORMAT_DAT)fout<<'\t';
			}
		}
		fout<<std::endl;
	}
	
	return true;
}

void DataStorage::ClearCounter(void){
	count=0;
}

