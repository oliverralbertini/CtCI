SRCS=$(wildcard *.c)

all: $(SRCS:.c=)

run_CheckPermutation: CheckPermutation
	./CheckPermutation "qwertyuiop" "poiuytrewq"
run_IsUnique: IsUnique
	./IsUnique "as;ldkf asd" "qwertyuiop"
run_Median: Median
	./Median 19 18 23 55 32 127 234
run_OneAway: OneAway
	./OneAway "test" "test1"
run_PalindromePermutation: PalindromePermutation
	./PalindromePermutation "Tact aco"
run_RotateMatrix: RotateMatrix
	./RotateMatrix
run_StringCompression: StringCompression
	./StringCompression "aabbccdd" "aaabbccdd" "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAbbcc"
run_URLify: URLify
	./URLify "this has some spaces      "
run_ZeroMatrix: ZeroMatrix
	./ZeroMatrix 15 15
.PHONY: all
