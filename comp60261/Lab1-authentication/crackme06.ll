source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

%_IO_FILE = type { i32 }

@global_var_403fe0 = local_unnamed_addr global i64 0
@global_var_404061 = local_unnamed_addr global i64 0
@global_var_404062 = local_unnamed_addr global i64 0
@global_var_404063 = local_unnamed_addr global i64 0
@global_var_404064 = local_unnamed_addr global i64 0
@global_var_404065 = local_unnamed_addr global i64 0
@global_var_404066 = local_unnamed_addr global i64 0
@global_var_404067 = local_unnamed_addr global i64 0
@global_var_404068 = local_unnamed_addr global i64 0
@global_var_404069 = local_unnamed_addr global i64 0
@global_var_40406a = local_unnamed_addr global i64 0
@global_var_40406b = local_unnamed_addr global i64 0
@global_var_402004 = constant [29 x i8] c"Please input your password: \00"
@global_var_402023 = constant [27 x i8] c"Authentication successful!\00"
@global_var_40203e = constant [17 x i8] c"Wrong password.\0A\00"
@0 = external global i32
@global_var_404040 = local_unnamed_addr global %_IO_FILE* null
@global_var_404048 = local_unnamed_addr global i8 0
@global_var_404060 = external global i8*
@1 = internal constant [2 x i8] c"\0A\00"
@2 = constant i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i64 0, i64 0)
@global_var_402021 = constant [2 x i8] c"\0A\00"

define i64 @set_password() local_unnamed_addr {
dec_label_pc_4011d6:
  %0 = alloca i64
  %1 = load i64, i64* %0
  store i8 112, i8* bitcast (i8** @global_var_404060 to i8*), align 8, !insn.addr !0
  store i8 101, i8* bitcast (i64* @global_var_404061 to i8*), align 8, !insn.addr !1
  store i8 110, i8* bitcast (i64* @global_var_404062 to i8*), align 8, !insn.addr !2
  store i8 101, i8* bitcast (i64* @global_var_404063 to i8*), align 8, !insn.addr !3
  store i8 116, i8* bitcast (i64* @global_var_404064 to i8*), align 8, !insn.addr !4
  store i8 114, i8* bitcast (i64* @global_var_404065 to i8*), align 8, !insn.addr !5
  store i8 97, i8* bitcast (i64* @global_var_404066 to i8*), align 8, !insn.addr !6
  store i8 116, i8* bitcast (i64* @global_var_404067 to i8*), align 8, !insn.addr !7
  store i8 105, i8* bitcast (i64* @global_var_404068 to i8*), align 8, !insn.addr !8
  store i8 111, i8* bitcast (i64* @global_var_404069 to i8*), align 8, !insn.addr !9
  store i8 110, i8* bitcast (i64* @global_var_40406a to i8*), align 8, !insn.addr !10
  store i8 0, i8* bitcast (i64* @global_var_40406b to i8*), align 8, !insn.addr !11
  ret i64 %1, !insn.addr !12
}

define i64 @main(i64 %argc, i8** %argv) local_unnamed_addr {
dec_label_pc_401235:
  %rax.0.reg2mem = alloca i64, !insn.addr !13
  %stack_var_-152 = alloca i64, align 8
  %stack_var_-8 = alloca i64, align 8
  %0 = ptrtoint i64* %stack_var_-8 to i64, !insn.addr !14
  %1 = call i64 @__readfsqword(i64 40), !insn.addr !15
  %2 = call i64 @set_password(), !insn.addr !16
  %3 = call i32 @puts(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @global_var_402004, i64 0, i64 0)), !insn.addr !17
  %4 = load %_IO_FILE*, %_IO_FILE** @global_var_404040, align 8, !insn.addr !18
  %5 = bitcast i64* %stack_var_-152 to i8*, !insn.addr !19
  %6 = call i8* @fgets(i8* nonnull %5, i32 128, %_IO_FILE* %4), !insn.addr !19
  %7 = call i32 @strcspn(i8* nonnull %5, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @global_var_402021, i64 0, i64 0)), !insn.addr !20
  %8 = sext i32 %7 to i64, !insn.addr !20
  %9 = add i64 %0, -144, !insn.addr !21
  %10 = add i64 %9, %8, !insn.addr !21
  %11 = inttoptr i64 %10 to i8*, !insn.addr !21
  store i8 0, i8* %11, align 1, !insn.addr !21
  %12 = call i32 @strcmp(i8* nonnull %5, i8* bitcast (i8** @global_var_404060 to i8*)), !insn.addr !22
  %13 = icmp eq i32 %12, 0, !insn.addr !23
  %14 = icmp eq i1 %13, false, !insn.addr !24
  br i1 %14, label %dec_label_pc_4012d6, label %dec_label_pc_4012c5, !insn.addr !24

dec_label_pc_4012c5:                              ; preds = %dec_label_pc_401235
  %15 = call i32 @puts(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @global_var_402023, i64 0, i64 0)), !insn.addr !25
  br label %dec_label_pc_4012f4, !insn.addr !26

dec_label_pc_4012d6:                              ; preds = %dec_label_pc_401235
  %16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @global_var_40203e, i64 0, i64 0)), !insn.addr !27
  br label %dec_label_pc_4012f4, !insn.addr !27

dec_label_pc_4012f4:                              ; preds = %dec_label_pc_4012d6, %dec_label_pc_4012c5
  %17 = call i64 @__readfsqword(i64 40), !insn.addr !28
  %18 = icmp eq i64 %1, %17, !insn.addr !28
  store i64 0, i64* %rax.0.reg2mem, !insn.addr !29
  br i1 %18, label %dec_label_pc_40130d, label %dec_label_pc_401308, !insn.addr !29

dec_label_pc_401308:                              ; preds = %dec_label_pc_4012f4
  call void @__stack_chk_fail(), !insn.addr !30
  store i64 ptrtoint (i32* @0 to i64), i64* %rax.0.reg2mem, !insn.addr !30
  br label %dec_label_pc_40130d, !insn.addr !30

dec_label_pc_40130d:                              ; preds = %dec_label_pc_401308, %dec_label_pc_4012f4
  %rax.0.reload = load i64, i64* %rax.0.reg2mem
  ret i64 %rax.0.reload, !insn.addr !31

; uselistorder directives
  uselistorder i8 0, { 1, 2, 0 }
  uselistorder i32 (i8*)* @puts, { 1, 0 }
  uselistorder i64 0, { 0, 5, 6, 7, 8, 1, 2, 9, 10, 3, 4, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 }
  uselistorder i32 1, { 3, 2, 1, 0 }
}

declare i32 @puts(i8*) local_unnamed_addr

declare void @__stack_chk_fail() local_unnamed_addr

declare i32 @printf(i8*, ...) local_unnamed_addr

declare i32 @strcspn(i8*, i8*) local_unnamed_addr

declare i8* @fgets(i8*, i32, %_IO_FILE*) local_unnamed_addr

declare i32 @strcmp(i8*, i8*) local_unnamed_addr

declare i64 @__readfsqword(i64) local_unnamed_addr

!0 = !{i64 4198878}
!1 = !{i64 4198885}
!2 = !{i64 4198892}
!3 = !{i64 4198899}
!4 = !{i64 4198906}
!5 = !{i64 4198913}
!6 = !{i64 4198920}
!7 = !{i64 4198927}
!8 = !{i64 4198934}
!9 = !{i64 4198941}
!10 = !{i64 4198948}
!11 = !{i64 4198955}
!12 = !{i64 4198964}
!13 = !{i64 4198965}
!14 = !{i64 4198970}
!15 = !{i64 4198980}
!16 = !{i64 4199000}
!17 = !{i64 4199015}
!18 = !{i64 4199020}
!19 = !{i64 4199042}
!20 = !{i64 4199067}
!21 = !{i64 4199072}
!22 = !{i64 4199100}
!23 = !{i64 4199105}
!24 = !{i64 4199107}
!25 = !{i64 4199119}
!26 = !{i64 4199124}
!27 = !{i64 4199151}
!28 = !{i64 4199165}
!29 = !{i64 4199174}
!30 = !{i64 4199176}
!31 = !{i64 4199182}
