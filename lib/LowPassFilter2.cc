// 2次低域通過濾波器クラス
// 2011/02/14 Yuki YOKOKURA
//
// 2次低域通過濾波器 G(s)=w^2/(s^2 + w/Q*s + w^2) (双一次変換)
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

#include "LowPassFilter2.hh"

using namespace ARCS;

LowPassFilter2::LowPassFilter2(double CutFreq, double Sharp, double SmplTime)
	// コンストラクタ CutFreq；[rad/s] 遮断周波数，SmplTime；[s] 制御周期
	: Ts(SmplTime),	// [s]		制御周期の格納
	  w(CutFreq),	// [rad/s]	遮断周波数
	  Q(Sharp),		//			鋭さ(0.5のときに重根設定となる)
	  uZ1(0), uZ2(0), uZ3(0), yZ1(0), yZ2(0), yZ3(0)
{
	
}

LowPassFilter2::~LowPassFilter2(){
	// デストラクタ
}

double LowPassFilter2::GetSignal(double u){
	// 出力信号の取得 u；入力信号
	double y;
	
	y = Q*Ts*Ts*Ts*w*w*(u+3.0*uZ1+3.0*uZ2+uZ3)
	   -4.0*Q*Ts*(yZ3-yZ2-yZ1)
	   -2.0*w*Ts*Ts*(-yZ3-yZ2+yZ1)
	   -Q*Ts*Ts*Ts*w*w*(yZ3+3.0*yZ2+3.0*yZ1);
	y = y * 1.0/(4.0*Q*Ts + 2.0*w*Ts*Ts + Q*Ts*Ts*Ts*w*w);
	
	uZ3=uZ2;
	uZ2=uZ1;
	uZ1=u;
	yZ3=yZ2;
	yZ2=yZ1;
	yZ1=y;
	
	return y;
}

void LowPassFilter2::SetCutFreq(double CutFreq){
	// 遮断周波数の再設定 CutFreq；[rad/s] 遮断周波数
	w=CutFreq;		// [rad/s]	遮断周波数の再設定
}

void LowPassFilter2::SetSharpness(double Sharp){
	// 鋭さの再設定 Sharp；鋭さ
	Q=Sharp;
}

void LowPassFilter2::SetSmplTime(double SmplTime){
	// 制御周期の再設定 SmplTime；[s] 制御周期
	Ts=SmplTime;	// [s] 制御周期の再設定
}

void LowPassFilter2::ClearStateVars(void){
	// すべての状態変数のリセット
	uZ1=0;	// 状態変数1のゼロクリア
	uZ2=0;	// 状態変数2のゼロクリア
	uZ3=0;	// 状態変数3のゼロクリア
	yZ1=0;	// 状態変数4のゼロクリア
	yZ2=0;	// 状態変数5のゼロクリア
	yZ3=0;	// 状態変数6のゼロクリア
}



