; ModuleID = 'preronaTest/test1.cpp'
source_filename = "preronaTest/test1.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@x = dso_local global i32* null, align 8
@y = dso_local global i32* null, align 8
@a = dso_local global i32 0, align 4
@b = dso_local global i32 0, align 4
@c = dso_local global i32 0, align 4
@d = dso_local global i32 0, align 4
@p = dso_local global i32** null, align 8
@z = dso_local global i32* null, align 8
@q = dso_local global i32*** null, align 8
@l = dso_local global i32** null, align 8
@r = dso_local global i32** null, align 8
@s = dso_local global i32** null, align 8

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_Z7if_elsev() #0 {
  store i32 10, i32* @a, align 4
  %1 = load i32, i32* @a, align 4
  %2 = icmp sgt i32 %1, 0
  br i1 %2, label %3, label %4

3:                                                ; preds = %0
  store i32* @a, i32** @x, align 8
  br label %5

4:                                                ; preds = %0
  store i32* @b, i32** @x, align 8
  br label %5

5:                                                ; preds = %4, %3
  %6 = load i32*, i32** @x, align 8
  store i32* %6, i32** @y, align 8
  store i32 12, i32* @c, align 4
  %7 = load i32, i32* @c, align 4
  %8 = icmp eq i32 %7, 13
  br i1 %8, label %9, label %10

9:                                                ; preds = %5
  store i32** @x, i32*** @p, align 8
  br label %11

10:                                               ; preds = %5
  store i32** @y, i32*** @p, align 8
  br label %11

11:                                               ; preds = %10, %9
  %12 = load i32**, i32*** @p, align 8
  store i32* @c, i32** %12, align 8
  %13 = load i32*, i32** @x, align 8
  store i32* %13, i32** @z, align 8
  store i32** @z, i32*** @p, align 8
  %14 = load i32**, i32*** @p, align 8
  store i32* @d, i32** %14, align 8
  %15 = load i32**, i32*** @p, align 8
  %16 = load i32*, i32** %15, align 8
  store i32* %16, i32** @x, align 8
  ret void
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 9.0.0-2~ubuntu18.04.1 (tags/RELEASE_900/final)"}
