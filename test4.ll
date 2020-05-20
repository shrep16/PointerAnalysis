; ModuleID = 'preronaTest/test4.cpp'
source_filename = "preronaTest/test4.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@x = dso_local global i32* null, align 8
@y = dso_local global i32* null, align 8
@p = dso_local global i32** null, align 8
@arr = dso_local global [2 x i32] zeroinitializer, align 4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_Z5mainsv() #0 {
  store i32* getelementptr inbounds ([2 x i32], [2 x i32]* @arr, i64 0, i64 0), i32** @x, align 8
  %1 = load i32*, i32** @x, align 8
  %2 = getelementptr inbounds i32, i32* %1, i32 1
  store i32* %2, i32** @x, align 8
  %3 = load i32*, i32** @x, align 8
  %4 = getelementptr inbounds i32, i32* %3, i64 4
  store i32* %4, i32** @x, align 8
  store i32** @x, i32*** @p, align 8
  ret void
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 9.0.0-2~ubuntu18.04.1 (tags/RELEASE_900/final)"}
