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

#ifndef LOWPASSFILTER
#define LOWPASSFILTER

namespace ARCS {	// ARCS名前空間
	class LowPassFilter {
		private:
			double Ts;	// [s]		制御周期
			double g;	// [rad/s]	遮断周波数
			double uZ1;	// 			状態変数1 変数名Z1の意味はz変換のz^(-1)を示す
			double yZ1;	//			状態変数2
		
		public:
			LowPassFilter(double CutFreq, double SmplTime);
			// コンストラクタ CutFreq；[rad/s] 遮断周波数，SmplTime；[s] 制御周期
			~LowPassFilter();					// デストラクタ
			double GetSignal(double u);			// 出力信号の取得 u；入力信号
			void SetCutFreq(double CutFreq);	// 遮断周波数の再設定 CutFreq；[rad/s] 遮断周波数
			void SetSmplTime(double SmplTime);	// 制御周期の再設定 SmplTime；[s] 制御周期
			void ClearStateVars(void);			// すべての状態変数のリセット
	};
}

#endif



