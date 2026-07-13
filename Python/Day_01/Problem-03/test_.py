#잠깐 테스트 한 파일이다.


class Getter:
    # 사용자로 부터 입력을 받는 클래스
    def __init__(self):
        self.words = []

    def pin_(self):
        if len(self.words) == 0:
            self.words = input().split()
            return self.words.pop(0)
        else:
            return self.words.pop(0)


my_getter = Getter()


def main():
    print(my_getter.pin_())
    print(my_getter.pin_())
    print(my_getter.pin_())



if __name__ == '__main__':
    main()
