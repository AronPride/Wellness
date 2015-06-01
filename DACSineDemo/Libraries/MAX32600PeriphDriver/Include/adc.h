/*******************************************************************************
* Copyright (C) 2014 Maxim Integrated Products, Inc., All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of Maxim Integrated
* Products, Inc. shall not be used except as stated in the Maxim Integrated
* Products, Inc. Branding Policy.
*
* The mere transfer of this software does not imply any licenses
* of trade secrets, proprietary technology, copyrights, patents,
* trademarks, maskwork rights, or any other form of intellectual
* property whatsoever. Maxim Integrated Products, Inc. retains all
* ownership rights.
*******************************************************************************
*/

/* $Revision: 2905 $ $Date: 2014-08-05 17:18:09 -0500 (Tue, 05 Aug 2014) $ */

#ifndef _ADC_H
#define _ADC_H

#include "adc_regs.h"
#include "pmu.h"

/**
 * @file  adc.h
 * @addtogroup adc ADC
 * @{
 * @brief This is the high level API for the analog-to-digital converter module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.\n
 * @ref Refer to ADC_SetRate().\n
 * \f$\\ \f$
 * <b>Full Rate Mode with PGA enabled:</b>\n
 *     For sample rate above 162KHz, the sample rate is adjusted by increasing the \f$pga\_trk\_cnt\f$.\n
 * \f$T_s = {\left({pga\_trk\_cnt + pga\_acq\_cnt + adc\_acq\_cnt + 8 }\right)} \cdot T_c\f$\n
 * \f$ pga\_trk\_cnt = \frac{T_{s\_desired}}{T_c} - pga\_acq\_cnt - adc\_acq\_cnt - 8 \f$\n
 * \f$T_c\f$ => ADC clock rate, typically 8MHz\n
 * \f$pga\_trk\_cnt\f$ => A rounded up and down integer to determine two closest sample rates
 * achievable to the desired.\n
 * The user will need to select which on is desired. For sample rates above 162KHz the PGA and ADC
 * are enabled for the duration of the data collection. The total current draw is sum of the ADC and
 * PGA maximum current. 
 * \f$\\ \\ \f$
 * <b>Full Rate Burst Mode with PGA enabled:</b>\n
 *     Burst reduced effective sample rate by the decimation rate. \f$2^{adc\_brst\_cnt}\f$ samples are collected 
 * and averaged to improve the SNR of the output. Only the averaged data sample is output so the data rate is 
 * reduced by \f$2^{adc\_brst\_cnt}\f$ \n
 * \f$T_s = 2^{adc\_brst\_cnt} \cdot {\left({pga\_trk\_cnt + pga\_acq\_cnt + adc\_acq\_cnt + 8 }\right)}
 * \cdot T_c\f$\n
 * \f$ pga\_trk\_cnt = \frac{T_{s\_desired}}{T_c \cdot 2^{adc\_brst\_cnt}} - pga\_acq\_cnt - adc\_acq\_cnt-8\f$
 * \f$\\ \\ \f$
 * <b>Full Rate Scan Mode with PGA enabled:</b>\n 
 *     When the channel scanning is enabled, the ADC cycles through \f$N_{scan}\f$ different input based on 
 *     the 8 different scan descriptors. Similar to burst, the sample rate per channel is reduced by the number
 *     of scan channels.\n
 * \f$T_s = N_{scan} \cdot {\left({pga\_trk\_cnt + pga\_acq\_cnt + adc\_acq\_cnt + 8 }\right)} \cdot T_c\f$\n
 * \f$ pga\_trk\_cnt = \frac{T_{s\_desired}}{T_c \cdot N_{scan}} 
 * - pga\_acq\_cnt - adc\_acq\_cnt - 8 \\\f$
 * \f$\\ \\ \f$
 * <b>Full Rate Scan Burst Mode with PGA enabled:</b>\n 
 *    When both scanning and averaging are enabled, the ADC collects \f$2^{adc\_brst\_cnt}\f$ of each channel
 *    before moving to the next channel. Thus the maximum possible sample rate is 
 *    reduced by \f$N_{scan} \cdot 2^{adc\_brst\_cnt}\f$ \n
 * \f$T_s = N_{scan}2^{adc\_brst\_cnt}{\left({pga\_trk\_cnt + pga\_acq\_cnt + adc\_acq\_cnt + 8 }\right)}
 *  \cdot T_c\f$\n
 * \f$ pga\_trk\_cnt = \frac{T_{s\_desired}}{T_c \cdot N_{scan} \cdot 2^{adc\_brst\_cnt}} 
 * - pga\_acq\_cnt - adc\_acq\_cnt - 8 \\ \f$
 * \f$\\ \\\f$
 * <b>Low Power Mode with PGA enabled:</b>\n
 *     For sample rates below 162KHz the low-power mode can be utilized. 
 *     The \f$pga\_trk\_cnt\f$ is set to the minimum
 *     and the sample rate is adjusted by increasing the \f$adc\_slp\_cnt\f$ \n
 * \f$T_s = {\left({pga\_trk\_cnt + pga\_acq\_cnt + adc\_acq\_cnt + adc\_slp\_cnt  + 40 }\right)} \cdot T_c\f$\n
 * \f$adc\_slp\_cnt = \frac{T_{s\_desired}}{T_c} - pga\_trk\_cnt - pga\_acq\_cnt - adc\_acq\_cnt - 40 \\ \f$
 * \f$\\ \\ \f$
 * <b>Low Power Mode Burst with PGA enabled:</b>\n
 *     The decimation filter can be used in the low power mode. The effective sample rate is a function of the 
 *     decimation rate and the sleep counter. With \f$decimation\_mode\f$ being set in ADC_SetMode(), 
 *     the \f$adc\_brst\_cnt\f$ defines the length of the decimation filter. The sample rate is controlled 
 *     by adjusting the \f$adc\_slp\_cnt\f$ \n
 * \f$T_s = \left[2^{adc\_brst\_cnt} \left({pga\_trk\_cnt + pga\_acq\_cnt + adc\_acq\_cnt + 8}
 * \right)+adc\_slp\_cnt + 32  \right] \cdot T_c\f$ \n
 * \f$adc\_slp\_cnt = \frac{T_{s\_desired}}{T_c} - 2^{adc\_brst\_cnt} 
 * \left({pga\_trk\_cnt - pga\_acq\_cnt - adc\_acq\_cnt + 8}\right) -32 \f$
 * \f$\\ \\ \f$
 * <b>Low Power Scan with PGA enabled:</b>\n
 *     When the channel scanning is enabled, the ADC cycles through \f$N_{scan}\f$ different input based on 
 *     the 8 different scan descriptors. The maximum potential sample rate per channel is reduced by 
 *     the number of scan channels. 
 * 
 * \f$T_s = \left[N_{scan} \left({pga\_trk\_cnt + pga\_acq\_cnt + adc\_acq\_cnt + 8}
 * \right)+adc\_slp\_cnt + 32  \right] \cdot T_c\f$ \n
 * 
 * \f$adc\_slp\_cnt = \frac{T_{s\_desired}}{T_c} - N_{scan} 
 * \left({pga\_trk\_cnt - pga\_acq\_cnt - adc\_acq\_cnt + 8}\right) -32 \\ \f$
 * 
 * <b>Low Power Scan Burst with PGA enabled:</b>\n 
 *     When both scanning and averaging are enabled, the ADC collects \f$2^{adc\_brst\_cnt}\f$ of each channel
 *     before moving to the next channel. Thus the maximum possible sample rate is reduced by 
 *     \f$N_{scan} \cdot 2^{adc\_brst\_cnt}\f$ \n
 * 
 * \f$T_s = \left[2^{adc\_brst\_cnt} N_{scan} \left({pga\_trk\_cnt + pga\_acq\_cnt + adc\_acq\_cnt + 8}
 * \right)+adc\_slp\_cnt + 32  \right] \cdot T_c\f$ \n
 * 
 * \f$adc\_slp\_cnt = \frac{T_{s\_desired}}{T_c} - N_{scan} \cdot 2^{adc\_brst\_cnt}
 * \left({pga\_trk\_cnt - pga\_acq\_cnt - adc\_acq\_cnt + 8}\right) -32 \\ \f$ 
 * 
 * <b>Full Rate Mode with PGA bypass:</b>\n
 *     For sample rates above 333KHz, the sample rate is adjusted by increasing the \f$pga\_trk\_cnt\f$
 * 
 * \f$T_s = {\left({pga\_trk\_cnt + adc\_acq\_cnt + 7}\right)} \cdot T_c\f$\n
 * \f$pga\_trk\_cnt = \frac{T_{s\_desired}}{T_c} - adc\_acq\_cnt-7 \f$ \n
 * 
 * \f$T_c\f$ => ADC clock rate, typically 8MHz. For example,
 * if \f$pga\_trk\_cnt\f$ is 9 and \f$adc\_acq\_cnt\f$ is 0, \f$T_s = 16 \cdot T_c\f$. 
 * Which results in the target maximum sampling rate of 500Ksps.\f$\\ \f$
 * 
 * <b>Full Rate Burst Mode with PGA bypass:</b>\n
 *     Burst reduced effective sample rate by decimation rate. \f$2^{adc\_brst\_cnt}\f$ samples are collected and 
 *     averaged to improve the SNR of the output. Only the averaged data sample is output so the data rate 
 *     is reduced by \f$2^{adc\_brst\_cnt}\f$.
 * 
 * \f$T_s = 2^{adc\_brst\_cnt}{\left({pga\_trk\_cnt + adc\_acq\_cnt + 7}\right)} \cdot T_c\f$\n
 * \f$pga\_trk\_cnt = \frac{T_{s\_desired}}{2^{adc\_brst\_cnt}T_c} - adc\_acq\_cnt-7 \\ \f$
 * 
 * <b>Full Rate Scan Mode with PGA bypass:</b>\n
 *     For sample rates above 333KHz, the sample rate is adjusted by increasing the \f$pga\_trk\_cnt\f$.
 * 
 * \f$T_s = {\left({pga\_trk\_cnt + adc\_acq\_cnt + 7}\right)} \cdot T_c\f$\n
 * \f$pga\_trk\_cnt = \frac{T_{s\_desired}}{T_c} - adc\_acq\_cnt-7 \\ \f$
 * 
 * <b>Full Rate Burst Mode with PGA bypass:</b>\n
 *     Burst reduced effective sample rate by the decimation rate. \f$2^{adc\_brst\_cnt}\f$ samples are collected
 *     and averaged to improve the SNR of the output. Only the averaged data sample is output so the data rate is
 *     reduced by \f$2^{adc\_brst\_cnt}\f$.
 * 
 * \f$T_s = 2^{adc\_brst\_cnt} \cdot {\left({pga\_trk\_cnt + adc\_acq\_cnt + 7}\right)} \cdot T_c\f$\n
 * \f$pga\_trk\_cnt = \frac{T_{s\_desired}}{2^{adc\_brst\_cnt}T_c} - adc\_acq\_cnt-7 \\ \f$
 * 
 * <b>Full Rate Scan Mode with PGA bypass:</b>\n
 *     Scan mode divides the sample rate across \f$N_{scan}\f$ channels without additional overhead.
 * 
 * \f$T_s = N_{scan} \cdot {\left({pga\_trk\_cnt + adc\_acq\_cnt + 7}\right)} \cdot T_c\f$\n
 * \f$pga\_trk\_cnt = \frac{T_{s\_desired}}{N_{scan}T_c} - adc\_acq\_cnt-7 \\ \f$
 * 
 * <b>Full Rate Scan and Bypass Mode with PGA bypass:</b>\n
 *     Burst adds an additional reduction in sample rate.
 * 
 * \f$T_s = N_{scan} 2^{adc\_brst\_cnt} {\left({pga\_trk\_cnt + adc\_acq\_cnt + 7}\right)} \cdot T_c\f$\n
 * \f$pga\_trk\_cnt = \frac{T_{s\_desired}}{N_{scan}2^{adc\_brst\_cnt}T_c} - adc\_acq\_cnt-7 \\ \f$
 * 
 * <b>Low Power Mode with PGA bypass:</b>\n
 *     The PGA wake and track counters are not used if the PGA is bypassed. 
 *     Thus the sample rate calculation is different.
 * 
 * \f$T_s = {\left({adc\_acq\_cnt + adc\_slp\_cnt + 24}\right)} \cdot T_c\f$\n
 * \f$adc\_slp\_cnt = \frac{T_{s\_desired}}{T_c} - adc\_acq\_cnt-24 \f$ \n
 * In PGA bypass mode, the low power mode can be used for \f$Ts <= 3\mu\f$s. \f$\\\f$ 
 * 
 * <b>Low Power Mode and Decimation Filter with PGA bypass:</b>\n
 *     The decimation filter can be used in the low power mode with the PGA in bypass mode. The effective sample
 *     rate is a function of the decimation rate and hte sleep counter. With \f$decimation\_mode\f$ being set to 1 
 *     in ADC_SetMode(), the \f$adc\_brst\_cnt\f$ defines the length of the decimation filter. 
 *     The sample rate is controlled by adjusting the \f$adc\_slp\_cnt\f$ \n
 * 
 * \f$T_s = {\left[\left({2^{adc\_brst\_cnt}-1}\right) \left({pga\_trk\_cnt + adc\_acq\_cnt +7}\right)
 * {+adc\_slp\_cnt + adc\_acq\_cnt + 24}\right]}\cdot T_c\f$\n
 * 
 * \f$adc\_slp\_cnt = \frac{T_{s\_desired}}{T_c} - \left({2^{adc\_brst\_cnt}-1}\right)
 * \left({pga\_trk\_cnt + adc\_acq\_cnt + 7}\right)- adc\_acq\_cnt -24 \\ \f$
 * 
 * <b>Low Power Scan Mode with PGA bypass:</b>\n
 *     Low power scan mode is like low power burst except a different channel is sampled each time.
 * 
 * \f$T_s = {\left[\left({N_{scan}-1}\right) \left({pga\_trk\_cnt + adc\_acq\_cnt +7}\right)
 * {+adc\_slp\_cnt + adc\_acq\_cnt + 24}\right]}\cdot T_c\f$\n
 * 
 * \f$adc\_slp\_cnt = \frac{T_{s\_desired}}{T_c} - \left({N_{scan}-1}\right)
 * \left({pga\_trk\_cnt + adc\_acq\_cnt + 7}\right)- adc\_acq\_cnt -24 \\ \f$
 * 
 * <b>Low Power Scan Mode with Burst and PGA bypass:</b>\n
 *     In this mode, a burst of each channel is take.
 * 
 * \f$T_s = {\left[\left({2^{adc\_brst\_cnt}N_{scan}-1}\right) \left({pga\_trk\_cnt + adc\_acq\_cnt +7}\right)
 * {+adc\_slp\_cnt + adc\_acq\_cnt + 24}\right]}\cdot T_c\f$\n
 * 
 * \f$adc\_slp\_cnt = \frac{T_{s\_desired}}{T_c} - \left({2^{adc\_brst\_cnt}N_{scan}-1}\right)
 * \left({pga\_trk\_cnt + adc\_acq\_cnt + 7}\right)- adc\_acq\_cnt -24 \\ \f$
 */

typedef struct {
    pmu_transfer_des_t transfer;
    pmu_jump_des_t jump;
} adc_pmu_t;

typedef struct {
    uint32_t buf1;
    uint32_t buf2;
    void(*done_cb)(int32_t exit_status, void *arg);
    void *done_cb_arg;
    adc_pmu_t des1;
    adc_pmu_t des2;
    int8_t  pmu_channel;
    uint8_t stop;
} adc_transport_t;

/**
 * @brief Enable and power up the ADC
 *
 */
void ADC_Enable(void);

/**
 * @brief Disable and power down the ADC
 *
 */
void ADC_Disable(void);

/**
 * @brief Setup ADC Configuration
 *
 * @param adc_mode         ADC Operation Mode
 * @param decimation_mode  Turns on/off decimation averaging filter
 * @param decimation_rate  Decimation Filter rate if enabled
 * @param bipolar_enable   ADC bipolar operation control
 * @param bipolar_range    ADC Range Control when in bi-polar mode of operation
 */
void ADC_SetMode(mxc_adc_mode_t adc_mode, mxc_adc_avg_mode_t decimation_mode, uint32_t decimation_rate, mxc_adc_bi_pol_t bipolar_enable, mxc_adc_range_t bipolar_range);

/**
 * @brief Set ADC Sample Rate
 * 
 * @param pga_acq_cnt  PGA Acquisition Count
 * @param adc_acq_cnt  ADC Acquisition Count
 * @param pga_trk_cnt  PGA Tracking Count
 * @param adc_slp_cnt  ADC Sleep Count
 *
 */
void ADC_SetRate(uint32_t pga_acq_cnt, uint32_t adc_acq_cnt, uint32_t pga_trk_cnt,uint32_t adc_slp_cnt);

/**
 * @brief Setup ADC Input Mux
 *
 * @param mux_ch_sel      Selection of Input Mux to ADC. Decoded in concert with mux_diff
 * @param mux_diff        Select differential or single ended input mode
 */
void ADC_SetMuxSel(mxc_adc_pga_mux_ch_sel_t mux_ch_sel, mxc_adc_pga_mux_diff_t mux_diff);

/**
 * @brief Setup PGA Configuration
 *
 * @param pga_bypass      When set to 1, the PGA is in Bypass Mode
 * @param pga_gain        When the PGA is enabled, sets the PGA gain
 */
void ADC_SetPGAMode(uint32_t pga_bypass, mxc_adc_pga_gain_t pga_gain);

/**
 * @brief Setup ADC Scan Count
 *
 * @param scan_cnt   Number of channels to scan, see enumeration for correct values.
 */
void ADC_SetScanCount(mxc_adc_scan_cnt_t scan_cnt);

/**
 * @brief Setup Scan Mode Channel Configuration
 *
 * @param scan_desc_index  Specifies the number of the scan channel being configured
 * @param mux_diff         Selects differential or single ended input mode for the selected channel
 * @param pga_gain         Selects PGA input gain for the selected channel
 * @param mux_ch_sel       Selects the input mux for the selected channel
 *
 */
void ADC_SetScanDesc(uint8_t scan_desc_index, uint8_t mux_diff, uint8_t pga_gain,  uint8_t mux_ch_sel);

/**
 * @brief Setup ADC Start Mode
 *
 * @param adc_strt_mode    Data Collection Start Mode: 'software' or 'pulse train' control
 *
 */
void ADC_SetStartMode(mxc_adc_strt_mode_t adc_strt_mode);

/**
 * @brief This function will setup a single and re-usable capture object for the ADC input port.
 *           For the most efficient usage, the buffer sizes should be a multiple of 3/4 ADC FIFO size.
 *
 * @param transport     pointer to state structure.  This API will populate the required fields of the struct, 
 *                                                   no initialization necessary.
 * @param buf1          pointer to first RAM allocated capture buffer
 *                          location, needs to be at least samples*2 bytes long.
 * @param buf1_samples  number of samples to place in buf1
 *
 * @param buf2          (OPTIONAL) pointer to second buffer for double-buffer style capture
 * @param buf2_samples  (OPTIONAL) number of samples to place in buf2
 *
 * @param done_cb       (OPTIONAL) pointer to a callback function to be called
 *                          by ISR when one buffer is full.
 * @param done_cb_arg
 * @param stop          stop the capture when all buffers are full or continue forever filling each
 *                           buffer until ADC_CaptureStop() is called.
 *
 * @return 0 on success
 *
 */
int32_t ADC_CaptureConfig(adc_transport_t *transport, uint16_t *buf1, uint32_t buf1_samples, uint16_t *buf2, uint32_t buf2_samples,
                          void(*done_cb)(int32_t exit_status, void *done_arg),
                          void *done_cb_arg, uint8_t stop);

/**
 * @brief Start a capture process using a previously allocated handle from ADC_CaptureConfig().
 * @param transport  Return handle from a call to ADC_CaptureConfig().
 *
 * @return 0 => Success. Non zero => error condition.
 *
 */
int32_t ADC_CaptureStart(adc_transport_t *transport);

/**
 * @brief Stop a running analog capture that was started without the stop bit set.
 *        Capture will complete to the next end of buffer condition and callback function
 *        will be called with 'stop_bit' set.
 *
 * @param transport  Return handle from a call to ADC_CaptureConfig().
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t ADC_CaptureStop(adc_transport_t *transport);

/**
 * @brief Trigger and read a single sample from the ADC.  This function will place the ADC
 *            into 'full power' mode, trigger the capture and return the collected data.
 *
 * @return 16-bit data value.
 */
uint16_t ADC_ManualRead(void);

/**
 * @}
*/



#endif /* _ADC_H */
