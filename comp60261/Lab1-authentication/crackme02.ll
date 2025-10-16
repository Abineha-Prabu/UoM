source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

%_IO_FILE = type { i32 }

@global_var_403fe0 = local_unnamed_addr global i64 0
@global_var_402004 = constant [29 x i8] c"Please input your password: \00"
@global_var_402023 = constant [27 x i8] c"Authentication successful!\00"
@global_var_40203e = constant [16 x i8] c"Wrong password.\00"
@0 = external global i32
@global_var_404040 = local_unnamed_addr global %_IO_FILE* null
@global_var_404048 = local_unnamed_addr global i8 0
@1 = internal constant [2 x i8] c"\0A\00"
@2 = constant i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i64 0, i64 0)
@global_var_402021 = constant [2 x i8] c"\0A\00"

define i64 @main(i64 %argc, i8** %argv) local_unnamed_addr {
dec_label_pc_4011b6:
  %rax.0.reg2mem = alloca i64, !insn.addr !0
  %stack_var_-152 = alloca i64, align 8
  %stack_var_-8 = alloca i64, align 8
  %0 = ptrtoint i64* %stack_var_-8 to i64, !insn.addr !1
  %1 = call i64 @__readfsqword(i64 40), !insn.addr !2
  %2 = call i32 @puts(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @global_var_402004, i64 0, i64 0)), !insn.addr !3
  %3 = load %_IO_FILE*, %_IO_FILE** @global_var_404040, align 8, !insn.addr !4
  %4 = bitcast i64* %stack_var_-152 to i8*, !insn.addr !5
  %5 = call i8* @fgets(i8* nonnull %4, i32 128, %_IO_FILE* %3), !insn.addr !5
  %6 = call i32 @strcspn(i8* nonnull %4, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @global_var_402021, i64 0, i64 0)), !insn.addr !6
  %7 = sext i32 %6 to i64, !insn.addr !6
  %8 = add i64 %0, -144, !insn.addr !7
  %9 = add i64 %8, %7, !insn.addr !7
  %10 = inttoptr i64 %9 to i8*, !insn.addr !7
  store i8 0, i8* %10, align 1, !insn.addr !7
  %11 = call i32 @atoi(i8* nonnull %4), !insn.addr !8
  %12 = load i32, i32* inttoptr (i64 4210744 to i32*), align 8, !insn.addr !9
  %13 = icmp eq i32 %11, %12, !insn.addr !10
  %14 = icmp eq i1 %13, false, !insn.addr !11
  br i1 %14, label %dec_label_pc_401253, label %dec_label_pc_401242, !insn.addr !11

dec_label_pc_401242:                              ; preds = %dec_label_pc_4011b6
  %15 = call i32 @puts(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @global_var_402023, i64 0, i64 0)), !insn.addr !12
  br label %dec_label_pc_401262, !insn.addr !13

dec_label_pc_401253:                              ; preds = %dec_label_pc_4011b6
  %16 = call i32 @puts(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @global_var_40203e, i64 0, i64 0)), !insn.addr !14
  br label %dec_label_pc_401262, !insn.addr !14

dec_label_pc_401262:                              ; preds = %dec_label_pc_401253, %dec_label_pc_401242
  %17 = call i64 @__readfsqword(i64 40), !insn.addr !15
  %18 = icmp eq i64 %1, %17, !insn.addr !15
  store i64 0, i64* %rax.0.reg2mem, !insn.addr !16
  br i1 %18, label %dec_label_pc_40127b, label %dec_label_pc_401276, !insn.addr !16

dec_label_pc_401276:                              ; preds = %dec_label_pc_401262
  call void @__stack_chk_fail(), !insn.addr !17
  store i64 ptrtoint (i32* @0 to i64), i64* %rax.0.reg2mem, !insn.addr !17
  br label %dec_label_pc_40127b, !insn.addr !17

dec_label_pc_40127b:                              ; preds = %dec_label_pc_401276, %dec_label_pc_401262
  %rax.0.reload = load i64, i64* %rax.0.reg2mem
  ret i64 %rax.0.reload, !insn.addr !18

; uselistorder directives
  uselistorder i8 0, { 1, 0 }
  uselistorder i32 (i8*)* @puts, { 2, 1, 0 }
  uselistorder i64 0, { 0, 5, 6, 7, 8, 1, 2, 9, 10, 3, 4, 11 }
  uselistorder i32 1, { 2, 1, 0 }
}

declare i32 @puts(i8*) local_unnamed_addr

declare void @__stack_chk_fail() local_unnamed_addr

declare i32 @strcspn(i8*, i8*) local_unnamed_addr

declare i8* @fgets(i8*, i32, %_IO_FILE*) local_unnamed_addr

declare i32 @atoi(i8*) local_unnamed_addr

declare i64 @__readfsqword(i64) local_unnamed_addr

!0 = !{i64 4198838}
!1 = !{i64 4198843}
!2 = !{i64 4198853}
!3 = !{i64 4198878}
!4 = !{i64 4198883}
!5 = !{i64 4198905}
!6 = !{i64 4198930}
!7 = !{i64 4198935}
!8 = !{i64 4198953}
!9 = !{i64 4198964}
!10 = !{i64 4198970}
!11 = !{i64 4198976}
!12 = !{i64 4198988}
!13 = !{i64 4198993}
!14 = !{i64 4199005}
!15 = !{i64 4199019}
!16 = !{i64 4199028}
!17 = !{i64 4199030}
!18 = !{i64 4199036}
