## 로빛 수습단원 과제 저장소

**컴퓨터정보공학부 장경민**

이 저장소는 로빛 수습단원 과제 제출용입니다.

폴더 구조는 주제/날짜/과제명(Python/Day_02/Problem-01)으로 구성되어 있습니다.

보통 메인 코드와 보고서등은 다음과 같은 양식을 사용하였습니다. (main.* / 보고서.pdf / reprot.pdf) 

또한 가능한 각 문제 폴더 마다 README.md 파일을 추가하려고 노력하였습니다. 

이외 과제에서 요구한 파일은 요구사항 그대로 작성하였고, 기타 test_case.txt 메모등이 포함되어 있습니다.


***

### 개발환경

- **OS**: Arch Linux (rolling)
- **컴파일러**: GCC
- **표준**: C11
- **Python**: 3.14.x
- **에디터**: VSCode 

### 빌드

\```
gcc -std=c11 -g -Wall -Wextra -fsanitize=address,undefined *.c -o main -lm
\```


