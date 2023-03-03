#ifdef PLUGINS_NEW
#ifndef __EMIT_PIE_PIE_A64C_ENCODER_C__
#define __EMIT_PIE_PIE_A64C_ENCODER_C__
#include "../dbm.h"
#include "../pie/pie-a64c-encoder.h"
#include "plugin_support.h"
void emit_a64c_CBZ_CBNZ (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int op,
	unsigned int imm19,
	unsigned int rt
);
void emit_a64c_B_cond (
	mambo_context *ctx,
	unsigned int imm19,
	unsigned int cond
);
void emit_a64c_SVC (
	mambo_context *ctx,
	unsigned int imm16
);
void emit_a64c_HVC (
	mambo_context *ctx,
	unsigned int imm16
);
void emit_a64c_SMC (
	mambo_context *ctx,
	unsigned int imm16
);
void emit_a64c_BRK (
	mambo_context *ctx,
	unsigned int imm16
);
void emit_a64c_HLT (
	mambo_context *ctx,
	unsigned int imm16
);
void emit_a64c_DCPS1 (
	mambo_context *ctx,
	unsigned int imm16
);
void emit_a64c_DCPS2 (
	mambo_context *ctx,
	unsigned int imm16
);
void emit_a64c_DCPS3 (
	mambo_context *ctx,
	unsigned int imm16
);
void emit_a64c_MSR_immed (
	mambo_context *ctx,
	unsigned int op1,
	unsigned int crm,
	unsigned int op2
);
void emit_a64c_HINT (
	mambo_context *ctx,
	unsigned int crm,
	unsigned int op2
);
void emit_a64c_CLREX (
	mambo_context *ctx,
	unsigned int crm
);
void emit_a64c_DSB (
	mambo_context *ctx,
	unsigned int crm
);
void emit_a64c_DMB (
	mambo_context *ctx,
	unsigned int crm
);
void emit_a64c_ISB (
	mambo_context *ctx,
	unsigned int crm
);
void emit_a64c_SYS (
	mambo_context *ctx,
	unsigned int op1,
	unsigned int crn,
	unsigned int crm,
	unsigned int op2,
	unsigned int rt
);
void emit_a64c_MRS_MSR_reg (
	mambo_context *ctx,
	unsigned int r,
	unsigned int o0,
	unsigned int op1,
	unsigned int crn,
	unsigned int crm,
	unsigned int op2,
	unsigned int rt
);
void emit_a64c_SYSL (
	mambo_context *ctx,
	unsigned int op1,
	unsigned int crn,
	unsigned int crm,
	unsigned int op2,
	unsigned int rt
);
void emit_a64c_TBZ_TBNZ (
	mambo_context *ctx,
	unsigned int b5,
	unsigned int op,
	unsigned int b40,
	unsigned int imm14,
	unsigned int rt
);
void emit_a64c_B_BL (
	mambo_context *ctx,
	unsigned int op,
	unsigned int imm26
);
void emit_a64c_BR (
	mambo_context *ctx,
	unsigned int rn
);
void emit_a64c_BLR (
	mambo_context *ctx,
	unsigned int rn
);
void emit_a64c_RET (
	mambo_context *ctx,
	unsigned int rn
);
void emit_a64c_ERET (
	mambo_context *ctx
);
void emit_a64c_DRPS (
	mambo_context *ctx
);
void emit_a64c_LDX_STX (
	mambo_context *ctx,
	unsigned int size,
	unsigned int o2,
	unsigned int l,
	unsigned int o1,
	unsigned int rs,
	unsigned int o0,
	unsigned int rt2,
	unsigned int rn,
	unsigned int rt
);
void emit_a64c_LDR_lit (
	mambo_context *ctx,
	unsigned int opc,
	unsigned int v,
	unsigned int imm19,
	unsigned int rt
);
void emit_a64c_LDP_STP (
	mambo_context *ctx,
	unsigned int opc,
	unsigned int v,
	unsigned int type,
	unsigned int l,
	unsigned int imm7,
	unsigned int rt2,
	unsigned int rn,
	unsigned int rt
);
void emit_a64c_LDR_STR_immed (
	mambo_context *ctx,
	unsigned int size,
	unsigned int v,
	unsigned int opc,
	unsigned int imm9,
	unsigned int type,
	unsigned int rn,
	unsigned int rt
);
void emit_a64c_LDR_STR_reg (
	mambo_context *ctx,
	unsigned int size,
	unsigned int v,
	unsigned int opc,
	unsigned int rm,
	unsigned int option,
	unsigned int s,
	unsigned int rn,
	unsigned int rt
);
void emit_a64c_LDR_STR_unsigned_immed (
	mambo_context *ctx,
	unsigned int size,
	unsigned int v,
	unsigned int opc,
	unsigned int imm12,
	unsigned int rn,
	unsigned int rt
);
void emit_a64c_LDx_STx_multiple (
	mambo_context *ctx,
	unsigned int q,
	unsigned int l,
	unsigned int opcode,
	unsigned int size,
	unsigned int rn,
	unsigned int rt
);
void emit_a64c_LDx_STx_multiple_post (
	mambo_context *ctx,
	unsigned int q,
	unsigned int l,
	unsigned int rm,
	unsigned int opcode,
	unsigned int size,
	unsigned int rn,
	unsigned int rt
);
void emit_a64c_LDx_STx_single (
	mambo_context *ctx,
	unsigned int q,
	unsigned int l,
	unsigned int r,
	unsigned int opcode,
	unsigned int s,
	unsigned int size,
	unsigned int rn,
	unsigned int rt
);
void emit_a64c_LDx_STx_single_post (
	mambo_context *ctx,
	unsigned int q,
	unsigned int l,
	unsigned int r,
	unsigned int rm,
	unsigned int opcode,
	unsigned int s,
	unsigned int size,
	unsigned int rn,
	unsigned int rt
);
void emit_a64c_ADD_SUB_immed (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int op,
	unsigned int s,
	unsigned int shift,
	unsigned int imm12,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_BFM (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int opc,
	unsigned int n,
	unsigned int immr,
	unsigned int imms,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_EXTR (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int n,
	unsigned int rm,
	unsigned int imms,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_logical_immed (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int opc,
	unsigned int n,
	unsigned int immr,
	unsigned int imms,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_MOV_wide (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int opc,
	unsigned int hw,
	unsigned int imm16,
	unsigned int rd
);
void emit_a64c_ADR (
	mambo_context *ctx,
	unsigned int op,
	unsigned int immlo,
	unsigned int immhi,
	unsigned int rd
);
void emit_a64c_ADD_SUB_ext_reg (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int op,
	unsigned int s,
	unsigned int rm,
	unsigned int option,
	unsigned int imm3,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_ADD_SUB_shift_reg (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int op,
	unsigned int s,
	unsigned int shift,
	unsigned int rm,
	unsigned int imm6,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_ADC_SBC (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int op,
	unsigned int s,
	unsigned int rm,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_CCMP_CCMN_immed (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int op,
	unsigned int imm5,
	unsigned int cond,
	unsigned int rn,
	unsigned int nzcv
);
void emit_a64c_CCMP_CCMN_reg (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int op,
	unsigned int rm,
	unsigned int cond,
	unsigned int rn,
	unsigned int nzcv
);
void emit_a64c_cond_select (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int op,
	unsigned int rm,
	unsigned int cond,
	unsigned int op2,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_data_proc_reg1 (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_data_proc_reg2 (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int rm,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_data_proc_reg3 (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int op31,
	unsigned int rm,
	unsigned int o0,
	unsigned int Ra,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_logical_reg (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int opc,
	unsigned int shift,
	unsigned int n,
	unsigned int rm,
	unsigned int imm6,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_across_lane (
	mambo_context *ctx,
	unsigned int q,
	unsigned int u,
	unsigned int size,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_copy (
	mambo_context *ctx,
	unsigned int q,
	unsigned int op,
	unsigned int imm5,
	unsigned int imm4,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_extract (
	mambo_context *ctx,
	unsigned int q,
	unsigned int rm,
	unsigned int imm4,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_modified_immed (
	mambo_context *ctx,
	unsigned int q,
	unsigned int op,
	unsigned int abc,
	unsigned int cmode,
	unsigned int defgh,
	unsigned int rd
);
void emit_a64c_simd_permute (
	mambo_context *ctx,
	unsigned int q,
	unsigned int size,
	unsigned int rm,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_scalar_copy (
	mambo_context *ctx,
	unsigned int imm5,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_scalar_pairwise (
	mambo_context *ctx,
	unsigned int u,
	unsigned int size,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_scalar_shift_immed (
	mambo_context *ctx,
	unsigned int u,
	unsigned int immh,
	unsigned int immb,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_scalar_three_diff (
	mambo_context *ctx,
	unsigned int u,
	unsigned int size,
	unsigned int rm,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_scalar_three_same (
	mambo_context *ctx,
	unsigned int u,
	unsigned int size,
	unsigned int rm,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_scalar_two_reg (
	mambo_context *ctx,
	unsigned int u,
	unsigned int size,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_scalar_x_indexed (
	mambo_context *ctx,
	unsigned int u,
	unsigned int size,
	unsigned int l,
	unsigned int m,
	unsigned int rm,
	unsigned int opcode,
	unsigned int H,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_shift_immed (
	mambo_context *ctx,
	unsigned int q,
	unsigned int u,
	unsigned int immh,
	unsigned int immb,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_table_lookup (
	mambo_context *ctx,
	unsigned int q,
	unsigned int rm,
	unsigned int len,
	unsigned int op,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_three_diff (
	mambo_context *ctx,
	unsigned int q,
	unsigned int u,
	unsigned int size,
	unsigned int rm,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_three_same (
	mambo_context *ctx,
	unsigned int q,
	unsigned int u,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_two_reg (
	mambo_context *ctx,
	unsigned int q,
	unsigned int u,
	unsigned int size,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_simd_x_indexed (
	mambo_context *ctx,
	unsigned int q,
	unsigned int u,
	unsigned int size,
	unsigned int l,
	unsigned int m,
	unsigned int rm,
	unsigned int opcode,
	unsigned int H,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_crypto_aes (
	mambo_context *ctx,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_crypto_sha_reg3 (
	mambo_context *ctx,
	unsigned int rm,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_crypto_sha_reg2 (
	mambo_context *ctx,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_FCMP (
	mambo_context *ctx,
	unsigned int type,
	unsigned int rm,
	unsigned int rn,
	unsigned int opcode2
);
void emit_a64c_FCCMP (
	mambo_context *ctx,
	unsigned int type,
	unsigned int rm,
	unsigned int cond,
	unsigned int rn,
	unsigned int op,
	unsigned int nzcv
);
void emit_a64c_FCSEL (
	mambo_context *ctx,
	unsigned int type,
	unsigned int rm,
	unsigned int cond,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_float_reg1 (
	mambo_context *ctx,
	unsigned int type,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_float_reg2 (
	mambo_context *ctx,
	unsigned int type,
	unsigned int rm,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_float_reg3 (
	mambo_context *ctx,
	unsigned int type,
	unsigned int o1,
	unsigned int rm,
	unsigned int o0,
	unsigned int Ra,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_FMOV_immed (
	mambo_context *ctx,
	unsigned int type,
	unsigned int imm8,
	unsigned int rd
);
void emit_a64c_float_cvt_fixed (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int type,
	unsigned int rmode,
	unsigned int opcode,
	unsigned int scale,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_float_cvt_int (
	mambo_context *ctx,
	unsigned int sf,
	unsigned int type,
	unsigned int rmode,
	unsigned int opcode,
	unsigned int rn,
	unsigned int rd
);
void emit_a64c_add_c_cri_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm,
	unsigned int option,
	unsigned int imm3
);
void emit_a64c_add_c_cis_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int sh,
	unsigned int imm12
);
void emit_a64c_adrdp_c_id_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int immhi,
	unsigned int immlo
);
void emit_a64c_adrp_c_ip_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int immhi,
	unsigned int immlo
);
void emit_a64c_alignd_c_ci_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int imm6
);
void emit_a64c_alignu_c_ci_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int imm6
);
void emit_a64c_bicflgs_c_ci_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int imm8
);
void emit_a64c_bicflgs_c_cr_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm
);
void emit_a64c_blr_c_c (
	mambo_context *ctx,
	unsigned int Cn
);
void emit_a64c_blr_ci_c (
	mambo_context *ctx,
	unsigned int Cn,
	unsigned int imm7
);
void emit_a64c_blrr_c_c (
	mambo_context *ctx,
	unsigned int Cn
);
void emit_a64c_blrs_c_c (
	mambo_context *ctx,
	unsigned int Cn
);
void emit_a64c_blrs_c_c_c (
	mambo_context *ctx,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_br_c_c (
	mambo_context *ctx,
	unsigned int Cn
);
void emit_a64c_br_ci_c (
	mambo_context *ctx,
	unsigned int Cn,
	unsigned int imm7
);
void emit_a64c_brr_c_c (
	mambo_context *ctx,
	unsigned int Cn
);
void emit_a64c_brs_c_c (
	mambo_context *ctx,
	unsigned int Cn
);
void emit_a64c_brs_c_c_c (
	mambo_context *ctx,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_build_c_c_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_bx_c (
	mambo_context *ctx
);
void emit_a64c_cas_c_r_c (
	mambo_context *ctx,
	unsigned int Cs,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_casa_c_r_c (
	mambo_context *ctx,
	unsigned int Cs,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_casal_c_r_c (
	mambo_context *ctx,
	unsigned int Cs,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_casl_c_r_c (
	mambo_context *ctx,
	unsigned int Cs,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_cfhi_r_c_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn
);
void emit_a64c_chkeq_cc_c (
	mambo_context *ctx,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_chksld_c_c (
	mambo_context *ctx,
	unsigned int Cn
);
void emit_a64c_chkss_cc_c (
	mambo_context *ctx,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_chkssu_c_cc_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_chktgd_c_c (
	mambo_context *ctx,
	unsigned int Cn
);
void emit_a64c_clrperm_c_ci_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int perm
);
void emit_a64c_clrperm_c_cr_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm
);
void emit_a64c_clrtag_c_c_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn
);
void emit_a64c_CMP_subs_r_cc_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_cpy_c_c_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn
);
void emit_a64c_cpytype_c_c_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_cpyvalue_c_c_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_cseal_c_c_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_csel_c_ci_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Cm,
	unsigned int cond
);
void emit_a64c_cthi_c_cr_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm
);
void emit_a64c_cvt_r_cc_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_cvt_c_cr_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm
);
void emit_a64c_cvtd_r_c_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn
);
void emit_a64c_cvtd_c_r_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Rn
);
void emit_a64c_cvtdz_c_r_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Rn
);
void emit_a64c_cvtp_r_c_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn
);
void emit_a64c_cvtp_c_r_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Rn
);
void emit_a64c_cvtpz_c_r_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Rn
);
void emit_a64c_cvtz_c_cr_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm
);
void emit_a64c_eorflgs_c_ci_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int imm8
);
void emit_a64c_eorflgs_c_cr_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm
);
void emit_a64c_gcbase_r_c_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn
);
void emit_a64c_gcflgs_r_c_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn
);
void emit_a64c_gclen_r_c_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn
);
void emit_a64c_gclim_r_c_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn
);
void emit_a64c_gcoff_r_c_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn
);
void emit_a64c_gcperm_r_c_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn
);
void emit_a64c_gcseal_r_c_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn
);
void emit_a64c_gctag_r_c_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn
);
void emit_a64c_gctype_r_c_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn
);
void emit_a64c_gcvalue_r_c_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn
);
void emit_a64c_ldapr_c_r_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_aldar_c_r_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_ldar_c_r_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_aldar_r_r_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn
);
void emit_a64c_aldarb_r_r_b (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn
);
void emit_a64c_ldaxp_c_r_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Ct2,
	unsigned int Rn
);
void emit_a64c_ldaxr_c_r_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_ldct_r_r_ (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn
);
void emit_a64c_ldnp_c_rib_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Ct2,
	unsigned int Rn,
	unsigned int imm7
);
void emit_a64c_ldp_cc_riaw_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Ct2,
	unsigned int Rn,
	unsigned int imm7
);
void emit_a64c_ldp_c_ribw_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Ct2,
	unsigned int Rn,
	unsigned int imm7
);
void emit_a64c_ldp_c_rib_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Ct2,
	unsigned int Rn,
	unsigned int imm7
);
void emit_a64c_ldpblr_c_c_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Cn
);
void emit_a64c_ldpbr_c_c_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Cn
);
void emit_a64c_ldr_c_i_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int imm17
);
void emit_a64c_ldr_c_riaw_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_ldr_c_ribw_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldr_c_rrb_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_ldr_c_rrb_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_aldr_r_rrb_64 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_aldr_r_rrb_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_aldr_v_rrb_d (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_aldr_v_rrb_s (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_aldr_c_rui_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_ldr_c_ruib_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm12
);
void emit_a64c_aldr_r_rui_64 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldr_r_rui_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldrb_r_rrb_b (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_aldrb_r_rui_b (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldrh_r_rrb_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_aldrsb_r_rrb_64 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_aldrsb_r_rrb_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_aldrsh_r_rrb_64 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_aldrsh_r_rrb_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_ldtr_c_rib_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldur_c_ri_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_ldur_c_ri_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldur_r_ri_64 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldur_r_ri_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldur_v_ri_b (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldur_v_ri_h (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldur_v_ri_s (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldur_v_ri_d (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldur_v_ri_q (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldurb_r_ri_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldurh_r_ri_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldursb_r_ri_64 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldursb_r_ri_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldursh_r_ri_64 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldursh_r_ri_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_aldursw_r_ri_64 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_ldxp_c_r_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Ct2,
	unsigned int Rn
);
void emit_a64c_ldxr_c_r_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_MOV_cpy_c_c_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn
);
void emit_a64c_mrs_c_i_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int o0,
	unsigned int op1,
	unsigned int CRn,
	unsigned int CRm,
	unsigned int op2
);
void emit_a64c_msr_c_i_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int o0,
	unsigned int op1,
	unsigned int CRn,
	unsigned int CRm,
	unsigned int op2
);
void emit_a64c_orrflgs_c_ci_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int imm8
);
void emit_a64c_orrflgs_c_cr_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm
);
void emit_a64c_ret_c_c (
	mambo_context *ctx,
	unsigned int Cn
);
void emit_a64c_retr_c_c (
	mambo_context *ctx,
	unsigned int Cn
);
void emit_a64c_rets_c_c (
	mambo_context *ctx,
	unsigned int Cn
);
void emit_a64c_rets_c_c_c (
	mambo_context *ctx,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_rrlen_r_r_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Rn
);
void emit_a64c_rrmask_r_r_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Rn
);
void emit_a64c_scbnds_c_ci_s (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int imm6
);
void emit_a64c_scbnds_c_ci_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int imm6
);
void emit_a64c_scbnds_c_cr_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm
);
void emit_a64c_scbndse_c_cr_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm
);
void emit_a64c_scflgs_c_cr_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm
);
void emit_a64c_scoff_c_cr_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm
);
void emit_a64c_sctag_c_cr_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm
);
void emit_a64c_scvalue_c_cr_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Rm
);
void emit_a64c_seal_c_cc_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_seal_c_ci_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int form
);
void emit_a64c_stct_r_r_ (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn
);
void emit_a64c_astlr_c_r_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_stlr_c_r_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_astlr_r_r_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn
);
void emit_a64c_astlrb_r_r_b (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn
);
void emit_a64c_stlxp_r_cr_c (
	mambo_context *ctx,
	unsigned int Rs,
	unsigned int Ct,
	unsigned int Ct2,
	unsigned int Rn
);
void emit_a64c_stlxr_r_cr_c (
	mambo_context *ctx,
	unsigned int Rs,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_stnp_c_rib_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Ct2,
	unsigned int Rn,
	unsigned int imm7
);
void emit_a64c_stp_cc_riaw_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Ct2,
	unsigned int Rn,
	unsigned int imm7
);
void emit_a64c_stp_c_ribw_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Ct2,
	unsigned int Rn,
	unsigned int imm7
);
void emit_a64c_stp_c_rib_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Ct2,
	unsigned int Rn,
	unsigned int imm7
);
void emit_a64c_str_c_riaw_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_str_c_ribw_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_astr_c_rrb_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_str_c_rrb_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_astr_r_rrb_64 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_astr_r_rrb_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_astr_v_rrb_d (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_astr_v_rrb_s (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_astr_c_rui_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_str_c_ruib_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm12
);
void emit_a64c_astr_r_rui_64 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_astr_r_rui_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_astrb_r_rrb_b (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_astrb_r_rui_b (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_astrh_r_rrb_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int Rm,
	unsigned int sign,
	unsigned int sz,
	unsigned int S
);
void emit_a64c_sttr_c_rib_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_astur_c_ri_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_stur_c_ri_c (
	mambo_context *ctx,
	unsigned int Ct,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_astur_r_ri_64 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_astur_r_ri_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_astur_v_ri_b (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_astur_v_ri_h (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_astur_v_ri_s (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_astur_v_ri_d (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_astur_v_ri_q (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_asturb_r_ri_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_asturh_r_ri_32 (
	mambo_context *ctx,
	unsigned int Rt,
	unsigned int Rn,
	unsigned int imm9
);
void emit_a64c_stxp_r_cr_c (
	mambo_context *ctx,
	unsigned int Rs,
	unsigned int Ct,
	unsigned int Ct2,
	unsigned int Rn
);
void emit_a64c_stxr_r_cr_c (
	mambo_context *ctx,
	unsigned int Rs,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_sub_c_cis_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int sh,
	unsigned int imm12
);
void emit_a64c_subs_r_cc_c (
	mambo_context *ctx,
	unsigned int Rd,
	unsigned int Cn,
	unsigned int Cm
);
void emit_a64c_swp_cc_r_c (
	mambo_context *ctx,
	unsigned int Cs,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_swpa_cc_r_c (
	mambo_context *ctx,
	unsigned int Cs,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_swpal_cc_r_c (
	mambo_context *ctx,
	unsigned int Cs,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_swpl_cc_r_c (
	mambo_context *ctx,
	unsigned int Cs,
	unsigned int Ct,
	unsigned int Rn
);
void emit_a64c_unseal_c_cc_c (
	mambo_context *ctx,
	unsigned int Cd,
	unsigned int Cn,
	unsigned int Cm
);
#endif
#endif
