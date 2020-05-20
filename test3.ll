; ModuleID = 'preronaTest/test3.cpp'
source_filename = "preronaTest/test3.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.myStruct = type { i32*, i32 }

@a = dso_local global i32 10, align 4
@y = dso_local global i32* @a, align 8
@k = dso_local global [11 x i32] zeroinitializer, align 16
@global = dso_local global %struct.myStruct { i32* @a, i32 30 }, align 8

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_Z4funcv() #0 {
  store i32 70, i32* getelementptr inbounds (%struct.myStruct, %struct.myStruct* @global, i32 0, i32 1), align 8
  %1 = load i32*, i32** @y, align 8
  store i32* %1, i32** getelementptr inbounds (%struct.myStruct, %struct.myStruct* @global, i32 0, i32 0), align 8
  store i32 112, i32* getelementptr inbounds ([11 x i32], [11 x i32]* @k, i64 0, i64 2), align 8
  ret void
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 9.0.0-2~ubuntu18.04.1 (tags/RELEASE_900/final)"}
