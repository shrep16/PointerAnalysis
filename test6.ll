; ModuleID = 'preronaTest/test6.cpp'
source_filename = "preronaTest/test6.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@arr = dso_local global [3 x i32**] zeroinitializer, align 16
@a = dso_local global i32* null, align 8
@b = dso_local global i32* null, align 8
@c = dso_local global i32* null, align 8

; Function Attrs: noinline norecurse nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32** @a, i32*** getelementptr inbounds ([3 x i32**], [3 x i32**]* @arr, i64 0, i64 0), align 16
  store i32** @b, i32*** getelementptr inbounds ([3 x i32**], [3 x i32**]* @arr, i64 0, i64 1), align 8
  %2 = load i32**, i32*** getelementptr inbounds ([3 x i32**], [3 x i32**]* @arr, i64 0, i64 0), align 16
  store i32** %2, i32*** getelementptr inbounds ([3 x i32**], [3 x i32**]* @arr, i64 0, i64 2), align 16
  ret i32 0
}

attributes #0 = { noinline norecurse nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 9.0.0-2~ubuntu18.04.1 (tags/RELEASE_900/final)"}