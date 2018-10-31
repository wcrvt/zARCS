// 2次擬似微分器クラス
// 2011/02/14 Yuki YOKOKURA
//
// 2次擬似微分器 G(s)=s^2*w^2/(s^2 + w/Q*s + w^2) (双一次変換)
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

#ifndef DIFFERENTIATOR2
#define DIFFERENTIATOR2

namespace ARCS {	// ARCS名前空間
	class Differentiator2 {
		private:
			double Ts;	// [s]		制御周期
			double w;	// [rad/s]	擬似微分の帯域
			double Q;	//			鋭さ
			double uZ1;	//			状態変数1 変数名Z1の意味はz変換のz^(-1)を示す
			double uZ2;	//			状態変数2
			double uZ3;	//			状態変数3
			double yZ1;	//			状態変数4
			double yZ2;	//			状態変数5
			double yZ3;	//			状態変数6
		
		public:
			Differentiator2(double Bandwidth, double Sharp, double SmplTime);
			// コンストラクタ  Bandwidth；[rad/s] 帯域，Sharp；鋭さ，SmplTime；[s] 制御周期
			~Differentiator2();					// デストラクタ
			double GetSignal(double u);			// 出力信号の取得 u；入力信号
			void SetBandwidth(double Bandwidth);// 擬似微分の帯域の再設定 Bandwidth；[rad/s] 帯域
			void SetSharpness(double Sharp);	// 鋭さの再設定 Sharp；鋭さ
			void SetSmplTime(double SmplTime);	// 制御周期の再設定 SmplTime；[s] 制御周期
			void ClearStateVars(void);			// すべての状態変数のリセット
	};
}

#endif



