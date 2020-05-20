; ModuleID = 'preronaTest/test5.cpp'
source_filename = "preronaTest/test5.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@x = dso_local global i32* null, align 8
@y = dso_local global i32* null, align 8
@c = dso_local global i32 0, align 4
@d = dso_local global i32 0, align 4
@z = dso_local global i32* null, align 8

; Function Attrs: noinline norecurse nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 0, i32* %2, align 4
  br label %3

3:                                                ; preds = %14, %0
  %4 = load i32, i32* %2, align 4
  %5 = icmp slt i32 %4, 11
  br i1 %5, label %6, label %17

6:                                                ; preds = %3
  %7 = load i32*, i32** @x, align 8
  store i32* %7, i32** @z, align 8
  %8 = load i32, i32* %2, align 4
  %9 = srem i32 %8, 2
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %11, label %12

11:                                               ; preds = %6
  store i32* @c, i32** @x, align 8
  br label %13

12:                                               ; preds = %6
  store i32* @d, i32** @x, align 8
  br label %13

13:                                               ; preds = %12, %11
  br label %14

14:                                               ; preds = %13
  %15 = load i32, i32* %2, align 4
  %16 = add nsw i32 %15, 1
  store i32 %16, i32* %2, align 4
  br label %3

17:                                               ; preds = %3
  %18 = load i32*, i32** @x, align 8
  store i32* %18, i32** @y, align 8
  %19 = load i32, i32* %1, align 4
  ret i32 %19
}

attributes #0 = { noinline norecurse nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 9.0.0-2~ubuntu18.04.1 (tags/RELEASE_900/final)"}
