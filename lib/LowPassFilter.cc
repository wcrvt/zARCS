// 低域通過濾波器クラス
// 2011/02/14 Yuki YOKOKURA
//
// 1次低域通過濾波器 G(s)=g/(s+g) (双一次変換)
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

#include "LowPassFilter.hh"

using namespace ARCS;

LowPassFilter::LowPassFilter(double CutFreq, double SmplTime)
	// コンストラクタ CutFreq；[rad/s] 遮断周波数，SmplTime；[s] 制御周期
	: Ts(SmplTime),	// [s]		制御周期の格納
	  g(CutFreq),	// [rad/s]	遮断周波数
	  uZ1(0), yZ1(0)
{
	
}

LowPassFilter::~LowPassFilter(){
	// デストラクタ
}

double LowPassFilter::GetSignal(double u){
	// 出力信号の取得 u；入力信号
	double y;
	
	y= g*Ts/(2.0+g*Ts)*(u+uZ1) + (2.0-g*Ts)/(2.0+g*Ts)*yZ1;
	
	uZ1=u;
	yZ1=y;
	
	return y;
}

void LowPassFilter::SetCutFreq(double CutFreq){
	// 遮断周波数の再設定 CutFreq；[rad/s] 遮断周波数
	g=CutFreq;		// [rad/s]	遮断周波数の再設定
}

void LowPassFilter::SetSmplTime(double SmplTime){
	// 制御周期の再設定 SmplTime；[s] 制御周期
	Ts=SmplTime;	// [s] 制御周期の再設定
}

void LowPassFilter::ClearStateVars(void){
	// すべての状態変数のリセット
	uZ1=0;	// 状態変数1のゼロクリア
	yZ1=0;	// 状態変数2のゼロクリア
}



