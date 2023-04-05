/*
  This file is part of MAMBO, a low-overhead dynamic binary modification tool:
      https://github.com/beehive-lab/mambo

  Copyright 2013-2016 Cosmin Gorgovan <cosmin at linux-geek dot org>
  Copyright 2015-2017 Guillermo Callaghan <guillermocallaghan at hotmail dot com>
  Copyright 2017-2020 The University of Manchester

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
.macro START_PC_ROUTINE name 
.global \name 
.p2align 4
.type  \name,@function
.Lfunc_begin_\name:
.cfi_startproc purecap
.endm

.macro END_PC_ROUTINE name 
.Lfunc_end_\name:
.size \name, .Lfunc_end_\name-.Lfunc_begin_\name
.cfi_endproc
.endm


#ifdef __aarch64__ 
  #ifdef MORELLO
    #define PTR_REG(n)	c##n
		#define GP_REG(n)	PTR_REG(n)
    #define GP_REG_W(n)	PTR_REG(n)
		#define SP_REG		csp
		#define PTR_SIZE	__SIZEOF_POINTER__
  #else
    #define PTR_REG(n)	x##n
		#define GP_REG(n)	PTR_REG(n)
    #define GP_REG_W(n)	w##n
		#define SP_REG		sp
		#define PTR_SIZE	8
  #endif
#endif

.global start_of_dispatcher_s
start_of_dispatcher_s:

START_PC_ROUTINE push_neon



push_neon:
  STP  GP_REG(0),  GP_REG(1), [PTR_REG(SP), #-512]!
  STP  GP_REG(2),  GP_REG(3), [PTR_REG(SP),   #32]
  STP  GP_REG(4),  GP_REG(5), [PTR_REG(SP),   #64]
  STP  GP_REG(6),  GP_REG(7), [PTR_REG(SP),   #96]
  STP  GP_REG(8),  GP_REG(9), [PTR_REG(SP),  #128]
  STP GP_REG(10), GP_REG(11), [PTR_REG(SP),  #160]
  STP GP_REG(12), GP_REG(13), [PTR_REG(SP),  #192]
  STP GP_REG(14), GP_REG(15), [PTR_REG(SP),  #224]
  STP GP_REG(16), GP_REG(17), [PTR_REG(SP),  #256]
  STP GP_REG(18), GP_REG(19), [PTR_REG(SP),  #288]
  STP GP_REG(20), GP_REG(21), [PTR_REG(SP),  #320]
  STP GP_REG(22), GP_REG(23), [PTR_REG(SP),  #352]
  STP GP_REG(24), GP_REG(25), [PTR_REG(SP),  #384]
  STP GP_REG(26), GP_REG(27), [PTR_REG(SP),  #416]
  STP GP_REG(28), GP_REG(29), [PTR_REG(SP),  #448]
  STP GP_REG(30), GP_REG(31), [PTR_REG(SP),  #480]
  RET

END_PC_ROUTINE push_neon

START_PC_ROUTINE pop_neon


pop_neon:
  LDP  GP_REG(2),  GP_REG(3), [PTR_REG(SP), #32]
  LDP  GP_REG(4),  GP_REG(5), [PTR_REG(SP), #64]
  LDP  GP_REG(6),  GP_REG(7), [PTR_REG(SP), #96]
  LDP  GP_REG(8),  GP_REG(9), [PTR_REG(SP), #128]
  LDP GP_REG(10), GP_REG(11), [PTR_REG(SP), #160]
  LDP GP_REG(12), GP_REG(13), [PTR_REG(SP), #192]
  LDP GP_REG(14), GP_REG(15), [PTR_REG(SP), #224]
  LDP GP_REG(16), GP_REG(17), [PTR_REG(SP), #256]
  LDP GP_REG(18), GP_REG(19), [PTR_REG(SP), #288]
  LDP GP_REG(20), GP_REG(21), [PTR_REG(SP), #320]
  LDP GP_REG(22), GP_REG(23), [PTR_REG(SP), #352]
  LDP GP_REG(24), GP_REG(25), [PTR_REG(SP), #384]
  LDP GP_REG(26), GP_REG(27), [PTR_REG(SP), #416]
  LDP GP_REG(28), GP_REG(29), [PTR_REG(SP), #448]
  LDP GP_REG(30), GP_REG(31), [PTR_REG(SP), #480]
  LDP  GP_REG(0),  GP_REG(1), [PTR_REG(SP)], #512
  RET

END_PC_ROUTINE pop_neon

START_PC_ROUTINE push_x4_x21 

push_x4_x21:
  STP  GP_REG(4),  GP_REG(5), [PTR_REG(SP), #-(18 * PTR_SIZE)]!
  STP  GP_REG(6),  GP_REG(7), [PTR_REG(SP), #(2 * PTR_SIZE)]
  STP  GP_REG(8),  GP_REG(9), [PTR_REG(SP), #(4 * PTR_SIZE)]
  STP GP_REG(10), GP_REG(11), [PTR_REG(SP), #(6 * PTR_SIZE)]
  STP GP_REG(12), GP_REG(13), [PTR_REG(SP), #(8 * PTR_SIZE)]
  STP GP_REG(14), GP_REG(15), [PTR_REG(SP), #(10 * PTR_SIZE)]
  STP GP_REG(16), GP_REG(17), [PTR_REG(SP), #(12 * PTR_SIZE)]
  STP GP_REG(18), GP_REG(19), [PTR_REG(SP), #(14 * PTR_SIZE)]
  STP GP_REG(20), GP_REG(21), [PTR_REG(SP), #(16 * PTR_SIZE)]
  RET

END_PC_ROUTINE push_x4_x21 

START_PC_ROUTINE pop_x4_x21 

pop_x4_x21:
  LDP  GP_REG(6),  GP_REG(7), [PTR_REG(SP), #(2 * PTR_SIZE)]
  LDP  GP_REG(8),  GP_REG(9), [PTR_REG(SP), #(4 * PTR_SIZE)]
  LDP GP_REG(10), GP_REG(11), [PTR_REG(SP), #(6 * PTR_SIZE)]
  LDP GP_REG(12), GP_REG(13), [PTR_REG(SP), #(8 * PTR_SIZE)]
  LDP GP_REG(14), GP_REG(15), [PTR_REG(SP), #(10 * PTR_SIZE)]
  LDP GP_REG(16), GP_REG(17), [PTR_REG(SP), #(12 * PTR_SIZE)]
  LDP GP_REG(18), GP_REG(19), [PTR_REG(SP), #(14 * PTR_SIZE)]
  LDP GP_REG(20), GP_REG(21), [PTR_REG(SP), #(16 * PTR_SIZE)]
  LDP  GP_REG(4),  GP_REG(5), [PTR_REG(SP)], #(18 * PTR_SIZE)
  RET
END_PC_ROUTINE pop_x4_x21 

START_PC_ROUTINE dispatcher_trampoline

dispatcher_trampoline:
  // PUSH all general purpose registers but X0, X1
  // X0 and X1 are pushed by the exit stub
  STP  GP_REG(2),  GP_REG(3), [PTR_REG(SP), #-(6 * PTR_SIZE)]!
  STP GP_REG(29), GP_REG(30), [PTR_REG(SP), #(2 * PTR_SIZE)]
  STR  GP_REG(0),      [PTR_REG(SP), #(5 * PTR_SIZE)]
  BL push_x4_x21

  MRS X19, NZCV
  MRS X20, FPCR
  MRS X21, FPSR
//FIXME - Check the add 176  
  ADD GP_REG(2), PTR_REG(SP), #(22 * PTR_SIZE)
  LDR GP_REG(3), disp_thread_data
  LDR GP_REG(9), dispatcher_addr
  BL push_neon

  BLR GP_REG(9) // BLR to dispatcher()

  BL pop_neon
  MSR NZCV, X19
  MSR FPCR, X20
  MSR FPSR, X21

  BL pop_x4_x21
  LDP GP_REG(29), GP_REG(30), [PTR_REG(SP), #(2 * PTR_SIZE)]
  LDP  GP_REG(0),  GP_REG(1), [PTR_REG(SP), #(4 * PTR_SIZE)]
  LDP  GP_REG(2),  GP_REG(3), [PTR_REG(SP)], #(6 * PTR_SIZE)

  B checked_cc_return
END_PC_ROUTINE dispatcher_trampoline
.p2align 4
dispatcher_addr: .quad dispatcher


START_PC_ROUTINE trace_head_incr
trace_head_incr:
  /*
   * X1 = Basic Block number
   * X30 = Address to return on the code cache.
   * X2 = address of the counter
   */
  STP      GP_REG(2),  GP_REG(3), [PTR_REG(SP), #-(2 * PTR_SIZE)]!
  // Leave space for storing the address of the counter to X2
  NOP  // MOVZ X2, #address_first_half_word
  NOP  // MOVK X2, #address_second_half_word, lsl #16
  NOP  // MOVK X2, #address_third_half_word,  lsl #32
  NOP  // MOVK X2, #address_fourth_half_word, lsl #48
  LDRB W3, [GP_REG(2), X1]
  SUB  W3,  W3, #1
  STRB W3, [GP_REG(2), X1]
  CBZ  W3,  create_trace_trampoline
  LDP  GP_REG(2),  GP_REG(3), [PTR_REG(SP)], #(2 * PTR_SIZE)
  RET
END_PC_ROUTINE trace_head_incr

START_PC_ROUTINE create_trace_trampoline

create_trace_trampoline:
  LDP GP_REG(2), GP_REG(30), [PTR_REG(SP), #(2 * PTR_SIZE)]
  STP GP_REG(0),  GP_REG(2), [PTR_REG(SP), #(2 * PTR_SIZE)]

  STP GP_REG(29), GP_REG(30), [PTR_REG(SP), #-(4 * PTR_SIZE)]!
  BL push_x4_x21

  MRS X19, NZCV
  MRS X20, FPCR
  MRS X21, FPSR

  /*
   * create_trace(dbm_thread   *thread_data,   X0
   *              uint32_t      bb_source,     X1
   *              cc_addr_pair *trace_addr)    X2
   */
  ADD GP_REG(2), PTR_REG(SP), #(20 * PTR_SIZE)
  LDR GP_REG(0), disp_thread_data
  //LDR GP_REG(3), =create_trace
  ADR GP_REG(3), create_trace
  BL push_neon

  BLR GP_REG(3)

  BL pop_neon
  MSR NZCV, X19
  MSR FPCR, X20
  MSR FPSR, X21

  BL pop_x4_x21
  /* Stack layout:
   * SP ->| X29 | X30 | SP + 0
   *      | TPC | SPC | SP + 16
   *      | X2  | X3  | SP + 32
   *      ---------------------
   *      | X0  | X1  | SP + 48 (Pushed by the basic block
   *                             and popped in the newly created trace)
   */
  LDP  GP_REG(0),  GP_REG(1), [PTR_REG(SP), #(2 * PTR_SIZE)]
  LDP  GP_REG(2),  GP_REG(3), [PTR_REG(SP), #(4 * PTR_SIZE)]
  LDP GP_REG(29), GP_REG(30), [PTR_REG(SP)], #(6 * PTR_SIZE)

  B checked_cc_return

END_PC_ROUTINE create_trace_trampoline

.global syscall_wrapper
.global syscall_wrapper_svc

syscall_wrapper:
  STP GP_REG(30), GP_REG(29), [PTR_REG(SP), #-(2 * PTR_SIZE)]!
  BL push_x4_x21
  STP GP_REG(0), GP_REG(1), [PTR_REG(SP), #-(4 * PTR_SIZE)]!
  STP GP_REG(2), GP_REG(3), [PTR_REG(SP), #(2 * PTR_SIZE)]
  BL push_neon

  MRS X19, NZCV
  MRS X20, FPCR
  MRS X21, FPSR

  MOV GP_REG(0), GP_REG(8)
  ADD GP_REG(1), PTR_REG(SP), #(8 * PTR_SIZE)
  MOV GP_REG(2), GP_REG(29)
  LDR GP_REG(3), disp_thread_data
  LDR GP_REG(4), syscall_handler_pre_addr

  BLR GP_REG(4)

  CBZ x0, s_w_r

  ADD GP_REG(9), PTR_REG(SP), #(64 * PTR_SIZE)
  LDP GP_REG(0), GP_REG(1), [GP_REG(9), #0]
  LDP GP_REG(2), GP_REG(3), [GP_REG(9), #(2 * PTR_SIZE)]
  LDP GP_REG(4), GP_REG(5), [GP_REG(9), #(4 * PTR_SIZE)]
  LDP GP_REG(6), GP_REG(7), [GP_REG(9), #(6 * PTR_SIZE)]
  LDR GP_REG(8),     [GP_REG(9), #(8 * PTR_SIZE)]

  // Balance the stack on rt_sigreturn, which doesn't return here
  CMP X8, #0x8b
  BNE svc
  ADD GP_REG(SP), GP_REG(SP), #((8 * PTR_SIZE) + (18 * PTR_SIZE) + (64 * PTR_SIZE))

svc: SVC 0
syscall_wrapper_svc:
  ADD GP_REG(1), PTR_REG(SP), #(64 * PTR_SIZE)
  STR GP_REG(0), [PTR_REG(1), #0]
  MOV GP_REG(0), GP_REG(8)
  MOV GP_REG(2), GP_REG(29)
  LDR GP_REG(3), disp_thread_data
  LDR GP_REG(4), syscall_handler_post_addr
  BLR GP_REG(4)

s_w_r:
  BL pop_neon
  MSR NZCV, X19
  MSR FPCR, X20
  MSR FPSR, X21

  LDP GP_REG(2), GP_REG(3), [PTR_REG(SP), #(2 * PTR_SIZE)]
  LDP GP_REG(0), GP_REG(1), [PTR_REG(SP)], #(4 * PTR_SIZE)
  BL pop_x4_x21
  LDP GP_REG(29), GP_REG(30), [PTR_REG(SP), #(2 * PTR_SIZE)]
  STP GP_REG(0), GP_REG(1), [PTR_REG(SP), #(2 * PTR_SIZE)]
  LDP GP_REG(0), GP_REG(1), [PTR_REG(SP)], #(2 * PTR_SIZE)
//FIXME BR X0 ignore
  B checked_cc_return

.p2align 4
syscall_handler_pre_addr: .quad syscall_handler_pre
.p2align 4
syscall_handler_post_addr: .quad syscall_handler_post

.global disp_thread_data
.p2align 4
disp_thread_data: .quad 0

.global send_self_signal


START_PC_ROUTINE checked_cc_return
checked_cc_return:
  STR GP_REG(2), [PTR_REG(SP), #-(2 * PTR_SIZE)]!
  LDR GP_REG(2), th_is_pending_ptr
  LDR W2, [GP_REG(2)]
  CBNZ W2, deliver_signals_trampoline
  LDR GP_REG(2), [PTR_REG(SP)], #(2 * PTR_SIZE)
  BR GP_REG(0)
deliver_signals_trampoline:
  STP GP_REG(0), GP_REG(1), [PTR_REG(SP), #-(2 * PTR_SIZE)]!
  MOV GP_REG(0), GP_REG(1) // set the SPC argument

  STR GP_REG(3), [PTR_REG(SP), #-(8 * PTR_SIZE)]!
  STP GP_REG(29), GP_REG(30), [PTR_REG(SP), #(2 * PTR_SIZE)]
  ADD GP_REG(1), PTR_REG(SP), #(4 * PTR_SIZE)
  BL push_x4_x21
  BL push_neon

  MRS X19, NZCV
  MRS X20, FPCR
  MRS X21, FPSR

  MOV X2, #0xd6db
  CMP X0, X2
  BEQ .

  ADR GP_REG(3), deliver_signals
  BLR GP_REG(3)

  MSR NZCV, X19
  MSR FPCR, X20
  MSR FPSR, X21

  BL pop_neon
  BL pop_x4_x21
  LDP GP_REG(29), GP_REG(30), [PTR_REG(SP), #(2 * PTR_SIZE)]
  LDR GP_REG(3), [PTR_REG(SP)], #(4 * PTR_SIZE)

  CBZ X0, abort_self_signal

  LDR GP_REG(2), [PTR_REG(SP), #(2 * PTR_SIZE)]
  LDP GP_REG(0), GP_REG(1), [PTR_REG(SP)], #(4 * PTR_SIZE)

  STR GP_REG(8), [PTR_REG(SP), #(3 * PTR_SIZE)]

  /*
    TPC, SPC
    X2, X8
    X0, X1
  */
r:
  MOV X8, #131
  SVC 0
send_self_signal:
  LDP GP_REG(2), GP_REG(8), [PTR_REG(SP), #(2 * PTR_SIZE)]
  LDR GP_REG(0), [PTR_REG(SP)], #(4 * PTR_SIZE)
  BR X0
abort_self_signal:
  ADD PTR_REG(SP), PTR_REG(SP), #(4 * PTR_SIZE)
  LDR GP_REG(2), [PTR_REG(SP), #(2 * PTR_SIZE)]
  LDR GP_REG(0), [PTR_REG(SP)], #(4 * PTR_SIZE)
  BR GP_REG(0)

END_PC_ROUTINE checked_cc_return
.global th_is_pending_ptr
.p2align 4
th_is_pending_ptr: .quad 0

# place the literal pool before the end_of_dispatcher_s symbol
.ltorg

.global end_of_dispatcher_s
.p2align 4
end_of_dispatcher_s:


