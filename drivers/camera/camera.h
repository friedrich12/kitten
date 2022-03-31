/* 
 * 2022, Friedrich Doku <frd20@pitt.edu>
 */
#ifndef CAMERA_H
#define CAMERA_H

#include <lwk/types.h>

#define CSI_BASE_ADDRESS 0x01CB0000             // Camera base address

#define CSI0_EN_REG 0x0000                      // CSI Enable register
#define CSI0_IF_CFG_REG 0x0004                  // CSI Interface Configuration Register
#define CSI0_CAP_REG 0x0008                     // CSI Capture Register
#define CSI0_SYNC_CNT_REG 0x000C                // CSI Synchronization Counter Register
#define CSI0_FIFO_THRS_REG 0x0010               // CSI FIFO Threshold Register
#define CSI0_PTN_LEN_REG 0x0030                 // CSI Pattern Generation Length register
#define CSI0_PTN_ADDR_REG 0x0034                // CSI Pattern Generation Address register
#define CSI0_VER_REG 0x003C                     // CSI Version Register
#define CSI0_C0_CFG_REG 0x0044                  // CSI Channel_0 configuration register
#define CSI0_C0_SCALE_REG 0x004C                // CSI Channel_0 scale register
#define CSI0_C0_F0_BUFA_REG 0x0050              // CSI Channel_0 FIFO 0 output buffer-A address register
#define CSI0_C0_F1_BUFA_REG 0x0058              // CSI Channel_0 FIFO 1 output buffer-A address register
#define CSI0_C0_F2_BUFA_REG 0x0060              // CSI Channel_0 FIFO 2 output buffer-A address register
#define CSI0_C0_CAP_STA_REG 0x006C              // CSI Channel_0 status register
#define CSI0_C0_INT_EN_REG 0x0070               // CSI Channel_0 interrupt enable register
#define CSI0_C0_INT_STA_REG 0x0074              // CSI Channel_0 interrupt status register
#define CSI0_C0_HSIZE_REG 0x0080                // CSI Channel_0 horizontal size register
#define CSI0_C0_VSIZE_REG 0x0084                // CSI Channel_0 vertical size register
#define CSI0_C0_BUF_LEN_REG 0x0088              // CSI Channel_0 line buffer length register
#define CSI0_C0_FLIP_SIZE_REG 0x008C            // CSI Channel_0 flip size register
#define CSI0_C0_FRM_CLK_CNT_REG 0x0090          // CSI Channel_0 frame clock counter register
#define CSI0_C0_ACC_ITNL_CLK_CNT_REG 0x0094     // CSI Channel_0 accumulated and internal clock counter register
#define CSI0_C0_FIFO_STAT_REG 0x0098            // CSI Channel_0 FIFO Statistic Register
#define CSI0_C0_PCLK_STAT_REG 0x009C            // CSI Channel_0 PCLK Statistic Register

#define CCI_CTRL 0x3000                         // CCI control register
#define CCI_CFG 0x3004                          // CCI transmission config register
#define CCI_FMT 0x3008                          // CCI packet format register
#define CCI_BUS_CTRL 0x300C                     // CCI bus control register
#define CCI_INT_CTRL 0x3014                     // CCI interrupt control register
#define CCI_LC_TRIG 0x3018                      // CCI line counter trigger register
#define CCI_FIFO_ACC 0x3100                     // CCI FIFO access register
#define CCI_RSV_REG 0x3200                      // CCI reserved register

/* CSI Enable Register */
struct csi0_en_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t csi_en : 1;
                        uint32_t ptn_gen_en : 1;
                        uint32_t clk_cnt_en : 1;
                        uint32_t clk_cnt_spl : 1;
                        uint32_t ptn_start : 1;
                        uint32_t res0 : 3;
                        uint32_t sram_pwdn : 1;
                        uint32_t res1 : 7;
                        uint32_t ptn_cycle : 8;
                        uint32_t res2 : 6;
                        uint32_t ver_en : 1; /* Turn this on to read Version Number */
                        uint32_t res3 : 1;
                };

        };
} __attribute__((packed)); 

/* CSI Interface Configuration Register */
struct csi0_if_cfg_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t csi_if : 5;
                        uint32_t res0 : 3;
                        uint32_t if_data_width : 2;
                        uint32_t seq_8plus2 : 2;
                        uint32_t res1 : 4;
                        uint32_t clk_pol : 1;
                        uint32_t herf_pol : 1;
                        uint32_t verf_pol : 1;
                        uint32_t field : 1;
                        uint32_t fps_ds : 1;
                        uint32_t src_type 1;
                        uint32_t res2 : 10;
                };

        };
} __attribute__((packed)); 

/* CSI Capture Register */
struct csi0_cap_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t ch0_scap_on : 1;
                        uint32_t ch0_vcap_on : 1;
                        uint32_t ch0_cap_mask : 4;
                        uint32_t res0 : 26;
                };

        };
} __attribute__((packed)); 

/* CSI Synchronization Counter Register */
struct csi0_sync_cnt_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t sync_cnt : 24;
                        uint32_t res0 : 8;
                };

        };
} __attribute__((packed)); 

/* CSI FIFO Threshold Register */
struct csi0_fifo_thrs_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t fifo_thrs : 12;
                        uint32_t res0 : 4;
                        uint32_t ptn_gen_dly : 8;
                        uint32_t ptn_gen_clk_dly : 2;
                        uint32_t fifo_nearly_full_th : 3;
                        uint32_t res1 : 3;
                };

        };
} __attribute__((packed)); 

/* CSI Pattern Generation Length Register */
struct csi0_ptn_len_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t ptn_len : 32;
                };

        };
} __attribute__((packed)); 

/* CSI Pattern Generation Address Register */
struct csi0_ptn_addr_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t ptn_addr : 32;
                };

        };
} __attribute__((packed)); 

/* CSI Version Reigster
 * Version of hardware circuit. Only can be read when version register read enable is on */
struct csi0_ver_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t ver : 32;
                };

        };
} __attribute__((packed)); 

/* CSI Channel 0 Configuration Register */
struct csi0_c0_cfg_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t min_sdr_wr_size : 2;
                        uint32_t res0 : 6;
                        uint32_t input_seq : 2;
                        uint32_t field_sel : 2;
                        uint32_t hflip_en : 1;
                        uint32_t vflip_en : 1;
                        uint32_t res1 : 2;
                        uint32_t output_fmt : 4;
                        uint32_t input_fmt : 4;
                        uint32_t pad_val : 8;
                };

        };
} __attribute__((packed));

/* CSI Channel 0 Scale Register */
struct csi0_c0_scale_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t quart_en : 1;
                        uint32_t res : 31;
                };

        };
} __attribute__((packed)); 

/* CSI Channel 0 FIFO 0 output buffer-A address Register */
struct csi0_c0_f0_bufa_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t c0f0_bufa : 32;
                };

        };
} __attribute__((packed)); 

/* CSI Channel 0 FIFI 1 output buffer-A address Register */
struct csi0_c0_f1_bufa_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t c0f1_bufa : 32;
                };

        };
} __attribute__((packed)); 

/* CSI Channel 0 FIFI 2 output buffer-A address Register */
struct csi0_c0_f2_bufa_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t c0f2_bufa : 32;
                };

        };
} __attribute__((packed));

/* CSI Channel 0 status Register */
struct csi0_c0_cap_sta_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t scap_sta : 1;
                        uint32_t vcap_sta : 1;
                        uint32_t field_sta : 1;
                        uint32_t res0 : 29;
                };

        };
} __attribute__((packed));

/* CSI Channel 0 interrupt enable Register */
struct csi0_c0_int_en_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t cd_int_en : 1;
                        uint32_t fd_int_en : 1;
                        uint32_t fifo0_of_int_en : 1;
                        uint32_t fifo1_of_int_en : 1;
                        uint32_t fifo2_of_int_en : 1;
                        uint32_t mul_err_int_en : 1;
                        uint32_t hb_of_int_en : 1;
                        uint32_t vs_int_en : 1;
                        uint32_t res0 : 24;
                };

        };
} __attribute__((packed));

/* CSI Channel 0 interrupt status Register */
struct csi0_c0_int_sta_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t cd_pd : 1;
                        uint32_t fd_pd : 1;
                        uint32_t fifo0_of_pd : 1;
                        uint32_t fifo1_of_pd : 1;
                        uint32_t fifo2_of_pd : 1;
                        uint32_t mul_err_pd : 1;
                        uint32_t hb_of_pd : 1;
                        uint32_t vs_pd : 1;
                        uint32_t res0 : 24;
                };

        };
} __attribute__((packed));

/* CSI Channel 0 horizontal size Register */
struct csi0_c0_int_hsize_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t hor_start : 13;
                        uint32_t res0 : 3;
                        uint32_t hor_len : 13;
                        uint32_t res1 : 3;
                };

        };
} __attribute__((packed));

/* CSI Channel 0 verticel size Register */
struct csi0_c0_int_vsize_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t ver_start : 13;
                        uint32_t res0 : 3;
                        uint32_t ver_len : 13;
                        uint32_t res1 : 3;
                };

        };
} __attribute__((packed));

/* CSI Channel 0 buffer length Register*/
struct csi0_c0_buf_len_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t buf_len : 14;
                        uint32_t res0 : 2;
                        uint32_t buf_len_c : 14;
                        uint32_t res1 : 2;
                };

        };
} __attribute__((packed));

/* CSI Channel 0 flip size Register */
struct csi0_c0_flip_size_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t valid_len : 13;
                        uint32_t res0 : 3;
                        uint32_t ver_len : 13;
                        uint32_t res1 : 3;
                };

        };
} __attribute__((packed));

/* CSI Channel 0 frame clock counter Register */
struct csi0_c0_frm_clk_cnt_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t frm_clk_cnt : 24;
                        uint32_t res0 : 8;
                };

        };
} __attribute__((packed));

/* CSI Channel 0 accumulated and internal clock counter Register */
struct csi0_c0_acc_itnl_clk_cnt_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t itnl_clk_cnt : 24;
                        uint32_t acc_clk_cnt : 8;
                };

        };
} __attribute__((packed));

/* CSI Channel 0 FIFO Statistic Register */
struct csi0_c0_fifo_stat_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t fifo_frm_max : 12;
                        uint32_t res0 : 20;
                };

        };
} __attribute__((packed));

/* CSI Channel 0 PCLK Statistic Register */
struct csi0_c0_pclk_stat_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t pclk_cnt_line_min : 15;
                        uint32_t res0 : 1;
                        uint32_t pclk_cnt_line_max : 15;
                        uint32_t res1 : 1;
                };

        };
} __attribute__((packed));


/* CCI Control Register*/
struct cci_ctrl_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t cci_en : 1;
                        uint32_t soft_reset : 1;
                        uint32_t res0 : 14;
                        uint32_t cci_sta : 8;
                        uint32_t tran_result : 4;
                        uint32_t read_tran_mode : 1;
                        uint32_t restart_mode : 1;
                        uint32_t repeat_tran : 1;
                        uint32_t single_tran : 1;
                };

        };
} __attribute__((packed));

/* CCI Transmission Configuration Register */
struct cci_cfg_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t csi_trig : 4;
                        uint32_t trig_mode : 3;
                        uint32_t res0 : 8;
                        uint32_t packet_mode : 1;
                        uint32_t interval : 8;
                        uint32_t timeout_h : 8;
                };

        };
} __attribute__((packed));

/* CCI Packet Format Register */
struct cci_fmt_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t packet_cnt : 16;
                        uint32_t data_byte : 4;
                        uint32_t addr_byte : 4;
                        uint32_t cmd : 1;
                        uint32_t slv_id : 7;
                };

        };
} __attribute__((packed));

/* CCI Bus Control Register */
struct cci_bus_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t sda_moe : 1;
                        uint32_t scl_moe : 1;
                        uint32_t sda_mov : 1;
                        uint32_t scl_mov : 1;
                        uint32_t sda_pen : 1;
                        uint32_t scl_pen : 1;
                        uint32_t sda_sta : 1;
                        uint32_t scl_sta : 1;
                        uint32_t clk_m : 4;
                        uint32_t clk_n : 3;
                        uint32_t dly_trig : 1;
                        uint32_t dly_cyc : 16;
                };

        };
} __attribute__((packed));

/* CCI Interrupt Control Register */
struct cci_int_ctrl_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t s_tran_com_pd : 1;
                        uint32_t s_tran_err_pdf : 1;
                        uint32_t res0 : 14;
                        uint32_t s_tran_com_int_en : 1;
                        uint32_t s_tran_err_int_en : 1;
                        uint32_t res1 : 14;
                };

        };
} __attribute__((packed));

/* CCI Line Counter Trigger Control Register */
struct cci_lc_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t ln_cnt : 13;
                        uint32_t res0 : 19;
                };

        };
} __attribute__((packed));

/* CCI FIFO Acess Register */
struct cci_fifo_acc_reg {
        union {
                uint32_t val;
                struct{
                        uint32_t data_fifo : 32;
                };

        };
} __attribute__((packed));
#endif
