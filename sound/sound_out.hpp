#pragma once
//=====================================================================//
/*!	@file
	@brief	サウンド出力バッファ
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/fixed_fifo.hpp"

namespace sound {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	波形構造体
		@param[in]	T	波形単位型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T>
	struct wave_t {
		T	l_ch;
		T	r_ch;

		wave_t() noexcept { }
		wave_t(T v) noexcept : l_ch(v), r_ch(v) { }
		wave_t(const wave_t& t) noexcept : l_ch(t.l_ch), r_ch(t.r_ch) { }
		void set(T zl) noexcept { l_ch = zl; r_ch = zl; }
		static wave_t linear(int32_t base, int32_t mod, const wave_t& a, const wave_t& b) noexcept
		{
			wave_t tmp;
			tmp.l_ch = a.l_ch + (static_cast<int32_t>(b.l_ch - a.l_ch) * mod) / base;
			tmp.r_ch = a.r_ch + (static_cast<int32_t>(b.r_ch - a.r_ch) * mod) / base;
			return tmp;
		}
		void offset(T ofs) noexcept { l_ch += ofs; r_ch += ofs; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	サウンド出力クラス
		@param[in]	T		基本型
		@param[in]	BFS		fifo バッファのサイズ
		@param[in]	OUTS	出力バッファのサイズ（外部ハードウェアの仕様による）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<typename T, uint32_t BFS, uint32_t OUTS>
	class sound_out {
	public:
		typedef T value_type;
		typedef wave_t<T> WAVE;
		typedef utils::fixed_fifo<WAVE, BFS> FIFO;		

	private:

		WAVE		wave_[OUTS];
		uint32_t	w_put_;

		FIFO		fifo_;

		uint32_t	out_rate_;
		uint32_t	inp_rate_;
		uint32_t	timebase_;
		WAVE		wbase_;

		T			zero_ofs_;

		volatile uint32_t	sample_count_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	zero_ofs	中心レベルのオフセット
		*/
		//-----------------------------------------------------------------//
		sound_out(T zero_ofs) noexcept : w_put_(0), fifo_(),
			out_rate_(48'000), inp_rate_(48'000), timebase_(0), wbase_(), zero_ofs_(zero_ofs),
			sample_count_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レート設定
			@param[in]	rate	出力レート（Hz）
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool set_output_rate(uint32_t rate) noexcept
		{
			if(rate == 0) return false;

			out_rate_ = rate;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レートの取得
			@return	出力レート（Hz）
		*/
		//-----------------------------------------------------------------//
		uint32_t get_output_rate() const noexcept { return out_rate_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レート設定 @n
					アップサンプリングのみ対応なので、出力レートより高い周波数は設定エラー
			@param[in]	rate	入力レート（Hz）
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool set_input_rate(uint32_t rate) noexcept
		{
			if(rate == 0 || out_rate_ < rate) return false;
			if(inp_rate_ != rate) {
				timebase_ = 0;
			}
			inp_rate_ = rate;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ミュート
		*/
		//-----------------------------------------------------------------//
		void mute() noexcept
		{
			fifo_.clear();
			for(uint32_t i = 0; i < OUTS; ++i) {
				wave_[i].set(zero_ofs_);
			}
			wbase_.set(0);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	FIFO の参照
			@return FIFO
		*/
		//-----------------------------------------------------------------//
		FIFO& at_fifo() noexcept { return fifo_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	出力波形メモリアドレスのを取得
			@return 出力波形メモリのアドレス
		*/
		//-----------------------------------------------------------------//
		const WAVE* get_wave(uint32_t pos = 0) const noexcept { return &wave_[pos]; }


		//-----------------------------------------------------------------//
		/*!
			@brief	波形サイズの取得
			@return 波形サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t size() const noexcept { return OUTS; }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	org	先頭位置
		*/
		//-----------------------------------------------------------------//
		void start(uint32_t org) noexcept
		{
			w_put_ = org & (OUTS - 1);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス
			@param[in]	num		波形メモリに移動する数（出力周期に沿った数）
		*/
		//-----------------------------------------------------------------//
		void service(uint32_t num) noexcept
		{
			volatile auto len = fifo_.length();
			if(inp_rate_ == out_rate_) {
				for(uint32_t i = 0; i < num; ++i) {
					WAVE t;
					if(len > 0) {
						t = fifo_.get();
						--len;
					} else {
						t.set(0);
					}
					wave_[w_put_] = t;
					wave_[w_put_].offset(zero_ofs_);
					++w_put_;
					w_put_ &= (OUTS - 1);
				}
				sample_count_ += num;
			} else {
				uint32_t i = 0;
				WAVE next(0);
				while(i < num) {
					if(timebase_ >= out_rate_) {
						timebase_ -= out_rate_;
						if(len > 0) {
							wbase_ = fifo_.get();
							next = fifo_.get_at();
							--len;
						} else {
							wbase_.set(0);
							next.set(0);
						}
					}
//					wave_[w_put_] = WAVE::linear(out_rate_, timebase_, wbase_, next);
					wave_[w_put_] = wbase_;
					wave_[w_put_].offset(zero_ofs_);
					++w_put_;
					w_put_ &= (OUTS - 1);
					timebase_ += inp_rate_;
					++i;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	波形メモリの位置を返す
			@return 波形メモリの位置
		*/
		//-----------------------------------------------------------------//
		auto get_wave_pos() const noexcept { return w_put_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	総サンプル数の取得
			@return 総サンプル数
		*/
		//-----------------------------------------------------------------//
		auto get_sample_count() const noexcept { return sample_count_; }
	};
}
