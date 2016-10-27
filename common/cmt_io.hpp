#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600, RX200 グループ・CMT I/O 制御 @n
			Copyright 2013, 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"

/// F_PCKB は周期パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCKB
#  error "cmt_io.hpp requires F_PCKB to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT I/O クラス
		@param[in]	CMT	チャネルクラス
		@param[in]	TASK	タイマー動作クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CMT, class TASK>
	class cmt_io {

		uint8_t		level_;

		void sleep_() const { asm("nop"); }

		static TASK	task_;

		static volatile uint32_t counter_;

		static INTERRUPT_FUNC void cmt_task_() {
			++counter_;
			task_();
			switch(CMT::get_chanel()) {
			case 0:
//				ICU::IR.CMI0 = 0;
				break;
			case 1:
//				ICU::IR.CMI1 = 0;
				break;
			case 2:
///				ICU::IR.CMI2 = 0;
				break;
			case 3:
///				ICU::IR.CMI3 = 0;
				break;
			}
		}

		void set_vector_(ICU::VECTOR vec) {
			set_interrupt_task(cmt_task_, static_cast<uint32_t>(vec));
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		cmt_io() : level_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, uint8_t level) {

			level_ = level;

			if(freq == 0) return false;

			uint32_t cmcor = F_PCKB / freq / 8;
			uint8_t cks = 0;
			while(cmcor > 65536) {
				cmcor >>= 2;
				++cks;
			}
			if(cks > 3 || cmcor == 0) {
				return false;
			}

			power_cfg::turn(CMT::get_peripheral());

			auto chanel = CMT::get_chanel();
			switch(chanel) {
			case 0:
				set_vector_(ICU::VECTOR::CMI0);
				CMT::CMSTR0.STR0 = 0;
				break;
			case 1:
				set_vector_(ICU::VECTOR::CMI1);
				CMT::CMSTR0.STR1 = 0;
				break;
			case 2:
//				set_vector_(ICU::VECTOR::CMI2);
				CMT::CMSTR1.STR2 = 0;
				break;
			case 3:
//				set_vector_(ICU::VECTOR::CMI3);
				CMT::CMSTR1.STR3 = 0;
				break;
			}

			if(level_) {
			    CMT::CMCR = CMT::CMCR.CMIE.b() | CMT::CMCR.CKS.b(cks);
			} else {
			    CMT::CMCR = CMT::CMCR.CKS.b(cks);
			}
		    CMT::CMCOR = cmcor - 1;
			icu_mgr::set_level(CMT::get_peripheral(), level_);

			switch(chanel) {
			case 0:
			    CMT::CMSTR0.STR0 = 1;
				break;
			case 1:
			    CMT::CMSTR0.STR1 = 1;
				break;
			case 2:
			    CMT::CMSTR1.STR2 = 1;
				break;
			case 3:
			    CMT::CMSTR1.STR3 = 1;
				break;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みと同期
		*/
		//-----------------------------------------------------------------//
		void sync() const {
			volatile uint32_t cnt = counter_;
			while(cnt == counter_) sleep_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みカウンターの値を取得
		*/
		//-----------------------------------------------------------------//
		uint32_t get_count() const {
			return counter_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  CMT カウンターの値を取得
		*/
		//-----------------------------------------------------------------//
		uint16_t get_cmt_count() const {
			return CMT::CMCNT();
		}
	};

	template <class CMT, class TASK> volatile uint32_t cmt_io<CMT, TASK>::counter_ = 0;
}
