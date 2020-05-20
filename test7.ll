; ModuleID = 'preronaTest/test7.cpp'
source_filename = "preronaTest/test7.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.MyStruct = type { i32* }

@a = dso_local global i32 0, align 4
@arr = dso_local global [2 x %struct.MyStruct] zeroinitializer, align 16

; Function Attrs: noinline norecurse nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.MyStruct, align 8
  store i32 0, i32* %1, align 4
  %3 = getelementptr inbounds %struct.MyStruct, %struct.MyStruct* %2, i32 0, i32 0
  store i32* @a, i32** %3, align 8
  %4 = bitcast %struct.MyStruct* %2 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 bitcast ([2 x %struct.MyStruct]* @arr to i8*), i8* align 8 %4, i64 8, i1 false)
  store i32* @a, i32** getelementptr inbounds ([2 x %struct.MyStruct], [2 x %struct.MyStruct]* @arr, i64 0, i64 1, i32 0), align 8
  ret i32 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i1 immarg) #1

attributes #0 = { noinline norecurse nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 9.0.0-2~ubuntu18.04.1 (tags/RELEASE_900/final)"}
