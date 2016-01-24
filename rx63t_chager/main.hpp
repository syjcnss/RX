#pragma once
//=====================================================================//
/*! @file
    @brief  メイン
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <time.h>
#include "common/format.hpp"

#ifdef __cplusplus
extern "C" {
#endif

	//-----------------------------------------------------------------//
	/*!
		@brief	無駄ループによる時間待ち
		@param[in]	n	無駄ループ回数
	 */
	//-----------------------------------------------------------------//
	void wait_delay(uint32_t n);


	//-----------------------------------------------------------------//
	/*!
		@brief	SCI 文字出力
		@param[in]	ch	文字コード
	 */
	//-----------------------------------------------------------------//
	void sci_putch(char ch);


	//-----------------------------------------------------------------//
	/*!
		@brief	SCI 文字列出力
		@param[in]	str	文字列
	 */
	//-----------------------------------------------------------------//
	void sci_puts(const char *str);


	//-----------------------------------------------------------------//
	/*!
		@brief	SCI 文字入力
		@return 文字コード
	 */
	//-----------------------------------------------------------------//
	char sci_getch(void);


	//-----------------------------------------------------------------//
	/*!
		@brief	SCI 文字入力数を取得
		@return 入力文字数
	 */
	//-----------------------------------------------------------------//
	uint32_t sci_length(void);

#ifdef __cplusplus
}
#endif

//-----------------------------------------------------------------//
/*!
	@brief	10ms 単位タイマー
 */
//-----------------------------------------------------------------//
void delay_10ms(uint32_t n);


struct chout {
	void operator() (char ch) {
		sci_putch(ch);
	}
};
typedef utils::format<chout> tformat;
