source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

%_IO_FILE = type { i32 }

@global_var_403fe0 = local_unnamed_addr global i64 0
@global_var_402004 = constant [29 x i8] c"Please input your password: \00"
@global_var_402023 = constant [27 x i8] c"Authentication successful!\00"
@global_var_40203e = constant [16 x i8] c"Wrong password.\00"
@0 = external global i32
@global_var_404040 = global %_IO_FILE* null
@global_var_404048 = local_unnamed_addr global i8 0
@1 = internal constant [2 x i8] c"\0A\00"
@2 = constant i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i64 0, i64 0)
@global_var_402021 = constant [2 x i8] c"\0A\00"

define i64 @function_401000() local_unnamed_addr {
dec_label_pc_401000:
  %rax.0.reg2mem = alloca i64, !insn.addr !0
  %0 = load i64, i64* @global_var_403fe0, align 8, !insn.addr !1
  %1 = icmp eq i64 %0, 0, !insn.addr !2
  store i64 0, i64* %rax.0.reg2mem, !insn.addr !3
  br i1 %1, label %dec_label_pc_401016, label %dec_label_pc_401014, !insn.addr !3

dec_label_pc_401014:                              ; preds = %dec_label_pc_401000
  call void @__gmon_start__(), !insn.addr !4
  store i64 ptrtoint (i32* @0 to i64), i64* %rax.0.reg2mem, !insn.addr !4
  br label %dec_label_pc_401016, !insn.addr !4

dec_label_pc_401016:                              ; preds = %dec_label_pc_401014, %dec_label_pc_401000
  %rax.0.reload = load i64, i64* %rax.0.reg2mem
  ret i64 %rax.0.reload, !insn.addr !5
}

define i32 @function_401080(i8* %s) local_unnamed_addr {
dec_label_pc_401080:
  %0 = call i32 @puts(i8* %s), !insn.addr !6
  ret i32 %0, !insn.addr !6
}

define void @function_401090() local_unnamed_addr {
dec_label_pc_401090:
  call void @__stack_chk_fail(), !insn.addr !7
  ret void, !insn.addr !7
}

define i32 @function_4010a0(i8* %s, i8* %reject) local_unnamed_addr {
dec_label_pc_4010a0:
  %0 = call i32 @strcspn(i8* %s, i8* %reject), !insn.addr !8
  ret i32 %0, !insn.addr !8
}

define i8* @function_4010b0(i8* %s, i32 %n, %_IO_FILE* %stream) local_unnamed_addr {
dec_label_pc_4010b0:
  %0 = call i8* @fgets(i8* %s, i32 %n, %_IO_FILE* %stream), !insn.addr !9
  ret i8* %0, !insn.addr !9
}

define i32 @function_4010c0(i8* %nptr) local_unnamed_addr {
dec_label_pc_4010c0:
  %0 = call i32 @atoi(i8* %nptr), !insn.addr !10
  ret i32 %0, !insn.addr !10
}

define i64 @entry_point(i64 %arg1, i64 %arg2, i64 %arg3, i64 %arg4, i64 %arg5, i64 %arg6) local_unnamed_addr {
dec_label_pc_4010d0:
  %stack_var_8 = alloca i64, align 8
  %0 = trunc i64 %arg6 to i32, !insn.addr !11
  %1 = bitcast i64* %stack_var_8 to i8**, !insn.addr !11
  %2 = inttoptr i64 %arg3 to void ()*, !insn.addr !11
  %3 = call i32 @__libc_start_main(i64 4198838, i32 %0, i8** nonnull %1, void ()* null, void ()* null, void ()* %2), !insn.addr !11
  %4 = call i64 @__asm_hlt(), !insn.addr !12
  unreachable, !insn.addr !12
}

define i64 @function_401100() local_unnamed_addr {
dec_label_pc_401100:
  %0 = alloca i64
  %1 = load i64, i64* %0
  ret i64 %1, !insn.addr !13
}

define i64 @function_401110() local_unnamed_addr {
dec_label_pc_401110:
  ret i64 ptrtoint (%_IO_FILE** @global_var_404040 to i64), !insn.addr !14
}

define i64 @function_401140() local_unnamed_addr {
dec_label_pc_401140:
  ret i64 0, !insn.addr !15
}

define i64 @function_401180() local_unnamed_addr {
dec_label_pc_401180:
  %0 = alloca i64
  %1 = load i64, i64* %0
  %2 = load i8, i8* @global_var_404048, align 1, !insn.addr !16
  %3 = icmp eq i8 %2, 0, !insn.addr !16
  %4 = icmp eq i1 %3, false, !insn.addr !17
  br i1 %4, label %dec_label_pc_4011a0, label %dec_label_pc_40118d, !insn.addr !17

dec_label_pc_40118d:                              ; preds = %dec_label_pc_401180
  %5 = call i64 @function_401110(), !insn.addr !18
  store i8 1, i8* @global_var_404048, align 1, !insn.addr !19
  ret i64 %5, !insn.addr !20

dec_label_pc_4011a0:                              ; preds = %dec_label_pc_401180
  ret i64 %1, !insn.addr !21

; uselistorder directives
  uselistorder i8* @global_var_404048, { 1, 0 }
}

define i64 @function_4011b0() local_unnamed_addr {
dec_label_pc_4011b0:
  %0 = call i64 @function_401140(), !insn.addr !22
  ret i64 %0, !insn.addr !22
}

define i64 @function_4011b6() local_unnamed_addr {
dec_label_pc_4011b6:
  %rax.0.reg2mem = alloca i64, !insn.addr !23
  %stack_var_-152 = alloca i64, align 8
  %stack_var_-8 = alloca i64, align 8
  %0 = ptrtoint i64* %stack_var_-8 to i64, !insn.addr !24
  %1 = call i64 @__readfsqword(i64 40), !insn.addr !25
  %2 = call i32 @puts(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @global_var_402004, i64 0, i64 0)), !insn.addr !26
  %3 = load %_IO_FILE*, %_IO_FILE** @global_var_404040, align 8, !insn.addr !27
  %4 = bitcast i64* %stack_var_-152 to i8*, !insn.addr !28
  %5 = call i8* @fgets(i8* nonnull %4, i32 128, %_IO_FILE* %3), !insn.addr !28
  %6 = call i32 @strcspn(i8* nonnull %4, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @global_var_402021, i64 0, i64 0)), !insn.addr !29
  %7 = sext i32 %6 to i64, !insn.addr !29
  %8 = add i64 %0, -144, !insn.addr !30
  %9 = add i64 %8, %7, !insn.addr !30
  %10 = inttoptr i64 %9 to i8*, !insn.addr !30
  store i8 0, i8* %10, align 1, !insn.addr !30
  %11 = call i32 @atoi(i8* nonnull %4), !insn.addr !31
  %12 = load i32, i32* inttoptr (i64 4210744 to i32*), align 8, !insn.addr !32
  %13 = icmp eq i32 %11, %12, !insn.addr !33
  %14 = icmp eq i1 %13, false, !insn.addr !34
  br i1 %14, label %dec_label_pc_401253, label %dec_label_pc_401242, !insn.addr !34

dec_label_pc_401242:                              ; preds = %dec_label_pc_4011b6
  %15 = call i32 @puts(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @global_var_402023, i64 0, i64 0)), !insn.addr !35
  br label %dec_label_pc_401262, !insn.addr !36

dec_label_pc_401253:                              ; preds = %dec_label_pc_4011b6
  %16 = call i32 @puts(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @global_var_40203e, i64 0, i64 0)), !insn.addr !37
  br label %dec_label_pc_401262, !insn.addr !37

dec_label_pc_401262:                              ; preds = %dec_label_pc_401253, %dec_label_pc_401242
  %17 = call i64 @__readfsqword(i64 40), !insn.addr !38
  %18 = icmp eq i64 %1, %17, !insn.addr !38
  store i64 0, i64* %rax.0.reg2mem, !insn.addr !39
  br i1 %18, label %dec_label_pc_40127b, label %dec_label_pc_401276, !insn.addr !39

dec_label_pc_401276:                              ; preds = %dec_label_pc_401262
  call void @__stack_chk_fail(), !insn.addr !40
  store i64 ptrtoint (i32* @0 to i64), i64* %rax.0.reg2mem, !insn.addr !40
  br label %dec_label_pc_40127b, !insn.addr !40

dec_label_pc_40127b:                              ; preds = %dec_label_pc_401276, %dec_label_pc_401262
  %rax.0.reload = load i64, i64* %rax.0.reg2mem
  ret i64 %rax.0.reload, !insn.addr !41

; uselistorder directives
  uselistorder i8 0, { 1, 2, 0 }
  uselistorder %_IO_FILE** @global_var_404040, { 1, 0 }
  uselistorder i32 (i8*)* @puts, { 2, 1, 0, 3 }
  uselistorder i64 0, { 0, 7, 8, 9, 10, 2, 3, 11, 12, 4, 1, 14, 5, 6, 13 }
}

define i64 @function_401280() local_unnamed_addr {
dec_label_pc_401280:
  %0 = alloca i64
  %1 = load i64, i64* %0
  ret i64 %1, !insn.addr !42

; uselistorder directives
  uselistorder i32 1, { 2, 6, 5, 3, 1, 0, 7, 4 }
}

declare i32 @__libc_start_main(i64, i32, i8**, void ()*, void ()*, void ()*) local_unnamed_addr

declare void @__gmon_start__() local_unnamed_addr

declare i32 @puts(i8*) local_unnamed_addr

declare void @__stack_chk_fail() local_unnamed_addr

declare i32 @strcspn(i8*, i8*) local_unnamed_addr

declare i8* @fgets(i8*, i32, %_IO_FILE*) local_unnamed_addr

declare i32 @atoi(i8*) local_unnamed_addr

declare i64 @__asm_hlt() local_unnamed_addr

declare i64 @__readfsqword(i64) local_unnamed_addr

!0 = !{i64 4198400}
!1 = !{i64 4198408}
!2 = !{i64 4198415}
!3 = !{i64 4198418}
!4 = !{i64 4198420}
!5 = !{i64 4198426}
!6 = !{i64 4198532}
!7 = !{i64 4198548}
!8 = !{i64 4198564}
!9 = !{i64 4198580}
!10 = !{i64 4198596}
!11 = !{i64 4198639}
!12 = !{i64 4198645}
!13 = !{i64 4198660}
!14 = !{i64 4198704}
!15 = !{i64 4198768}
!16 = !{i64 4198788}
!17 = !{i64 4198795}
!18 = !{i64 4198801}
!19 = !{i64 4198806}
!20 = !{i64 4198814}
!21 = !{i64 4198816}
!22 = !{i64 4198836}
!23 = !{i64 4198838}
!24 = !{i64 4198843}
!25 = !{i64 4198853}
!26 = !{i64 4198878}
!27 = !{i64 4198883}
!28 = !{i64 4198905}
!29 = !{i64 4198930}
!30 = !{i64 4198935}
!31 = !{i64 4198953}
!32 = !{i64 4198964}
!33 = !{i64 4198970}
!34 = !{i64 4198976}
!35 = !{i64 4198988}
!36 = !{i64 4198993}
!37 = !{i64 4199005}
!38 = !{i64 4199019}
!39 = !{i64 4199028}
!40 = !{i64 4199030}
!41 = !{i64 4199036}
!42 = !{i64 4199052}
