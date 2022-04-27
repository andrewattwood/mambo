/*
  This file is part of MAMBO, a low-overhead dynamic binary modification tool:
      https://github.com/beehive-lab/mambo

  Copyright 2013-2016 Cosmin Gorgovan <cosmin at linux-geek dot org>
  Copyright 2017 The University of Manchester

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

# These helpers are executed from .text and are not copied to the code cache

#ifdef __arm__
.syntax unified
#endif

#ifdef __aarch64__ 
  #ifdef MORELLOBSD
    #define PTR_REG(n)	c##n
		#define GP_REG(n)	PTR_REG(n)
		#define SP_REG		csp
		#define PTR_SIZE	__SIZEOF_POINTER__
  #else
    #define PTR_REG(n)	x##n
		#define GP_REG(n)	PTR_REG(n)
		#define SP_REG		sp
		#define PTR_SIZE	8
  #endif
#endif




.global  dbm_client_entry                             // -- Begin function dbm_client_entry
.p2align        2
.type   dbm_client_entry,@function
.Lfunc_begin_dbm_client_entry:
.cfi_startproc purecap

#ifdef __arm__

.code 32
dbm_client_entry:
  MOV SP, R1
  MOV LR, R0
  MOV R0, #0
  MOV R1, #0
  MOV R2, #0
  MOV R3, #0
  BLX LR
  BX LR

#endif // __arm__

#ifdef __aarch64__ 

dbm_client_entry:
  MOV PTR_REG(SP), GP_REG(1)
  STP GP_REG(ZR), GP_REG(ZR), [PTR_REG(SP), #-(2 * PTR_SIZE)]!
  BR PTR_REG(0)

#endif

.Lfunc_end_dbm_client_entry:
.size   dbm_client_entry, .Lfunc_end_dbm_client_entry-.Lfunc_begin_dbm_client_entry
.cfi_endproc


# Thread entry
# R0 - new SP
# R1 - Thread entry instruction
.global  th_enter                             // -- Begin function th_enter
.p2align        2
.type   th_enter,@function
.Lfunc_begin_th_enter:
.cfi_startproc purecap

#ifdef __arm__
.thumb_func
th_enter:
  MOV SP, R0
  STR R1, [SP, #56]
  POP {R0-R12, R14}
  POP {PC}
#endif

#ifdef __aarch64__
th_enter:
  MOV PTR_REG(SP), GP_REG(0)
  LDP  GP_REG(4),  GP_REG(5), [PTR_REG(SP),  #(2 * PTR_SIZE)]
  LDP  GP_REG(6),  GP_REG(7), [PTR_REG(SP),  #(4 * PTR_SIZE)]
  LDP  GP_REG(8),  GP_REG(9), [PTR_REG(SP),  #(6 * PTR_SIZE)]
  LDP GP_REG(10), GP_REG(11), [PTR_REG(SP),  #(8 * PTR_SIZE)]
  LDP GP_REG(12), GP_REG(13), [PTR_REG(SP),  #(10 * PTR_SIZE)]
  LDP GP_REG(14), GP_REG(15), [PTR_REG(SP),  #(12 * PTR_SIZE)]
  LDP GP_REG(16), GP_REG(17), [PTR_REG(SP), #(14 * PTR_SIZE)]
  LDP GP_REG(18), GP_REG(19), [PTR_REG(SP), #(16 * PTR_SIZE)]
  LDP GP_REG(20), GP_REG(21), [PTR_REG(SP), #(18 * PTR_SIZE)]
  LDP GP_REG(22), GP_REG(23), [PTR_REG(SP), #(20 * PTR_SIZE)]
  LDP GP_REG(24), GP_REG(25), [PTR_REG(SP), #(22 * PTR_SIZE)]
  LDP GP_REG(26), GP_REG(27), [PTR_REG(SP), #(24 * PTR_SIZE)]
  LDR GP_REG(28),      [PTR_REG(SP), #(26 * PTR_SIZE)]
  LDP GP_REG(29), GP_REG(30), [PTR_REG(SP), #(28 * PTR_SIZE)]
  LDP  GP_REG(2),  GP_REG(3), [PTR_REG(SP)], #(30 * PTR_SIZE)

  BR PTR_REG(1)
#endif

.Lfunc_end_th_enter:
.size   th_enter, .Lfunc_end_th_enter-.Lfunc_begin_th_enter
.cfi_endproc

# passed to thread_create
.global  new_thread_trampoline                             // -- Begin function new_thread_trampoline
.p2align        2
.type   new_thread_trampoline,@function
.Lfunc_begin_new_thread_trampoline:
.cfi_startproc purecap

new_thread_trampoline:
#ifdef __arm__
  PUSH {R4-R12, LR}
  MOV R1, SP
  B dbm_start_thread_pth
#elif __aarch64__
  STP GP_REG(X19), GP_REG(X20), [PTR_REG(SP), #-(12 * PTR_SIZE)]!
  STP GP_REG(X21), GP_REG(X22), [PTR_REG(SP), #(2 * PTR_SIZE)]
  STP GP_REG(X23), GP_REG(X24), [PTR_REG(SP), #(4 * PTR_SIZE)]
  STP GP_REG(X25), GP_REG(X26), [PTR_REG(SP), #(6 * PTR_SIZE)]
  STP GP_REG(X27), GP_REG(X28), [PTR_REG(SP), #(8 * PTR_SIZE)]
  STP GP_REG(X29), GP_REG(X30), [PTR_REG(SP), #(10 * PTR_SIZE)]
  MOV GP_REG(X1), PTR_REG(SP)
  B dbm_start_thread_pth
#endif


.Lfunc_end_new_thread_trampoline:
.size   new_thread_trampoline, .Lfunc_end_new_thread_trampoline-.Lfunc_begin_new_thread_trampoline
.cfi_endproc

.global  return_with_sp                             // -- Begin function return_with_sp
.p2align        2
.type   return_with_sp,@function
.Lfunc_begin_return_with_sp:
.cfi_startproc purecap

return_with_sp:
#ifdef __arm__
  MOV SP, R0
  POP {R4-R12, PC}
#elif __aarch64__
  MOV PTR_REG(SP), X0
  LDP GP_REG(X21), GP_REG(X22), [PTR_REG(SP), #(2 * PTR_SIZE)]
  LDP GP_REG(X23), GP_REG(X24), [PTR_REG(SP), #(4 * PTR_SIZE)]
  LDP GP_REG(X25), GP_REG(X26), [PTR_REG(SP), #(6 * PTR_SIZE)]
  LDP GP_REG(X27), GP_REG(X28), [PTR_REG(SP), #(8 * PTR_SIZE)]
  LDP GP_REG(X29), GP_REG(X30), [PTR_REG(SP), #(10 * PTR_SIZE)]
  LDP GP_REG(X19), GP_REG(X20), [PTR_REG(SP)], #(12 * PTR_SIZE)
  RET
#endif

.Lfunc_end_return_with_sp:
.size   return_with_sp, .Lfunc_end_return_with_sp-.Lfunc_begin_return_with_sp
.cfi_endproc

.global  raw_syscall                             // -- Begin function raw_syscall
.p2align        2
.type   raw_syscall,@function
.Lfunc_begin_raw_syscall:
.cfi_startproc purecap

raw_syscall:
#ifdef __arm__
  MOV R12, SP
  PUSH {R4 - R7}
  MOV R7, R0
  MOV R0, R1
  MOV R1, R2
  MOV R2, R3
  LDM R12, {R3 - R6}
  SVC 0
  POP {R4 - R7}
  BX LR
#endif
#ifdef __aarch64__
  MOV W8, W0
  MOV X0, X1
  MOV X1, X2
  MOV X2, X3
  MOV X3, X4
  MOV X4, X5
  MOV X5, X6
  MOV X6, X7
  SVC 0
  RET
#endif

.Lfunc_end_raw_syscall:
.size   raw_syscall, .Lfunc_end_raw_syscall-.Lfunc_begin_raw_syscall
.cfi_endproc

.global signal_trampoline
.func signal_trampoline
.type signal_trampoline, %function

signal_trampoline:
#ifdef __arm__
  SUB SP, SP, #4
  PUSH {r0-r3, r9, r12, lr}
  BL signal_dispatcher
  CBZ R0, sigret
  STR R0, [SP, #28]
  POP {r0-r3, r9, r12, lr}
  POP {PC}
sigret:
  ADD SP, SP, #32
  MOV R7, #173
  SVC 0
#endif
#ifdef __aarch64__
  STP  X2,  X3, [SP, #-176]!
  STP  X4,  X5, [SP, #16]
  STP  X6,  X7, [SP, #32]
  STP  X8,  X9, [SP, #48]
  STP X10, X11, [SP, #64]
  STP X12, X13, [SP, #80]
  STP X14, X15, [SP, #96]
  STP X16, X17, [SP, #112]
  STP X18, X29, [SP, #128]
  STR X30,      [SP, #144]
  STP  X0,  X1, [SP, #160]

  BL signal_dispatcher

  LDP  X4,  X5, [SP, #16]
  LDP  X6,  X7, [SP, #32]
  LDP  X8,  X9, [SP, #48]
  LDP X10, X11, [SP, #64]
  LDP X12, X13, [SP, #80]
  LDP X14, X15, [SP, #96]
  LDP X16, X17, [SP, #112]
  LDP X18, X29, [SP, #128]
  LDR X30,      [SP, #144]
  LDP  X2,  X3, [SP], #160

  CBZ X0, sigret

  BR X0
sigret:
  ADD SP, SP, #16
  MOV X8, #139
  SVC 0
#endif
.endfunc

.global atomic_increment_u64
.func atomic_increment_u64
.type atomic_increment_u64, %function

atomic_increment_u64:
#ifdef __arm__
  // R0 - ptr, R2 inc (low), R3, inc (high)
  PUSH {R4, R5}

retry:
  LDREXD R4, R5, [R0]
  ADDS R4, R2
  ADC R5, R3
  STREXD R1, R4, R5, [R0]
  CMP R1, #0
  BNE retry

  MOV R0, R4
  MOV R1, R5
  POP {R4, R5}
  BX LR

#elif __aarch64__
  LDXR X2, [X0]
  ADD X2, X2, X1
  STXR W3, X2, [X0]
  CBNZ W3, atomic_increment_u64
  MOV X0, X2
  RET

#endif
.endfunc

.global atomic_increment_u32
.func atomic_increment_u32
.type atomic_increment_u32, %function

atomic_increment_u32:
#ifdef __arm__
  LDREX R2, [R0]
  ADD R2, R1
  STREX R3, R2, [R0]
  CMP R3, #0
  BNE atomic_increment_u32
  MOV R0, R2
  BX LR

#elif __aarch64__
  LDXR W2, [X0]
  ADD W2, W2, W1
  STXR W3, W2, [X0]
  CBNZ W3, atomic_increment_u32
  MOV W0, W2
  RET

#endif
.endfunc

.global atomic_decrement_if_positive_i32
.func atomic_decrement_if_positive_i32
.type atomic_decrement_if_positive_i32, %function

atomic_decrement_if_positive_i32:
#ifdef __arm__
  LDREX R2, [R0]
  CMP R2, R1
  BLT abort
  SUB R2, R2, R1
  STREX R3, R2, [R0]
  CMP R3, #0
  BNE atomic_decrement_if_positive_i32
  MOV R0, R2
  BX LR
abort:
  CLREX
  MOV R0, #-1
  BX LR

#elif __aarch64__
  LDXR W2, [X0]
  CMP W2, W1
  BLT abort
  SUB W2, W2, W1
  STXR W3, W2, [X0]
  CBNZ W3, atomic_decrement_if_positive_i32
  MOV W0, W2
  RET
abort:
  CLREX
  MOV W0, #-1
  RET

#endif
.endfunc


.global safe_fcall_trampoline
.func safe_fcall_trampoline
.type safe_fcall_trampoline, %function

safe_fcall_trampoline:
#ifdef __arm__
  PUSH {R5-R7, R9, R12, LR}
  VPUSH {d16-d31}
  VPUSH {d0-d7}

  MOV R7, SP
  BIC R6, R7, #7
  MOV SP, R6

  MRS R5, CPSR
  VMRS R6, FPSCR

  BLX R4

  MOV SP, R7

  MSR CPSR, R5
  VMSR FPSCR, R6

  VPOP {d0-d7}
  VPOP {d16-d31}
  POP {R5-R7, R9, R12, PC}

#elif __aarch64__
  STP X8,  X9,  [SP, #-128]!
  STP X10, X11, [SP, #16]
  STP X12, X13, [SP, #32]
  STP X14, X15, [SP, #48]
  STP X16, X17, [SP, #64]
  STP X18, X19, [SP, #80]
  STP X20, X21, [SP, #96]
  STP X29, X30, [SP, #112]

  MRS X19, NZCV
  MRS X20, FPCR
  MRS X21, FPSR

  BL push_neon

  BLR X8

  BL pop_neon

  MSR NZCV, X19
  MSR FPCR, X20
  MSR FPSR, X21

  LDP X10, X11, [SP, #16]
  LDP X12, X13, [SP, #32]
  LDP X14, X15, [SP, #48]
  LDP X16, X17, [SP, #64]
  LDP X18, X19, [SP, #80]
  LDP X20, X21, [SP, #96]
  LDP X29, X30, [SP, #112]
  LDP X8,  X9,  [SP], #128

  RET
#endif

.endfunc

.global __try_memcpy_error
.type __try_memcpy_error, %function
.global __try_memcpy
.type __try_memcpy, %function

__try_memcpy:
#ifdef __arm__
  LDRB R3, [R1], #1
  STRB R3, [R0], #1
  SUB R2, #1
  CBZ R2, __try_memcpy_ret
  B __try_memcpy
__try_memcpy_ret:
  MOV R0, #0
  BX LR

__try_memcpy_error:
  MOV R0, #-1
  BX LR
#elif __aarch64__
  LDRB W3, [X1], #1
  STRB W3, [X0], #1
  SUB X2, X2, #1
  CBNZ X2, __try_memcpy
  MOV X0, #0
  RET

__try_memcpy_error:
  MOV X0, #-1
  RET
#endif
