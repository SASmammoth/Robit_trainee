class Getter:
    # 사용자로 부터 입력을 받는 클래스
    def __init__(self):
        self.words = []

    def pin_(self):
        #하나의 줄로 입력받은 문자열들을 띄어쓰기 단위로 분리하여 요청할때마다 단어 단위로 반환함
        if len(self.words) == 0:
            self.words = input("=>").split()
            return self.words.pop(0)
        else:
            return self.words.pop(0)
    
    def buffer_clear(self):
        #오류가 났을때를 대비해 버퍼를 지움
        self.words.clear()


my_getter = Getter()


class List_method:
    # 리스트 매서드 본체
    def __init__(self):
        self.my_list = []

    def find_index(self, velue):
        #"pop index" 와 같이 인덱스를 입력받을때, 문자인지 확인하고, 합당한 인덱스 범위 여부를 확인함.
        if not isinstance(velue, int):
            try:
                #정수로 변환할수 있는 형식인지 확인함
                velue = int(velue)
            except ValueError:
                raise Exception("index는 int형식의 문자가 와야함")

        #인덱스의 크기가 합당한 크기인지 확인함.
        if not(-velue <= len(self.my_list) and velue < len(self.my_list)):
            raise Exception("indexerror : 리스트의 범위를 벗어남, 현재 리스트의 크기 : " + str(len(self.my_list)))
        return velue

    def func_pop(self):
        # 특정 위치 값 삭제
        if(len(self.my_list) == 0): raise Exception("pop 명령어는 리스트에 내용이 1개 이상 있어야함")
        index_velue = my_getter.pin_()
        self.my_list.pop(self.find_index(index_velue))

    def func_remove(self):
        # 특정 값 삭제
        velue = my_getter.pin_()
        if not velue in self.my_list: raise Exception("리스트에 없는 값이 remove명령어의 값으로 들어옴")
        self.my_list.remove(velue)

    def func_append(self):
        # 리스트 맨 뒤에 값 추가
        velue = my_getter.pin_()
        self.my_list.append(velue)

    def func_insert(self):
        # 특정 위치에 값 추가
        index_velue = my_getter.pin_()
        index_velue = self.find_index(index_velue)
        velue = my_getter.pin_()
        self.my_list.insert(index_velue, velue) 

    def prompt(self):
        #명령어 문자열 입력을 받하 맞는 함수로 매칭함
        func_ = my_getter.pin_()
        if func_ == "append": 
            self.func_append()
        elif func_ ==  "insert": 
            self.func_insert()
        elif func_ ==  "remove":
            self.func_remove()
        elif func_ == "pop":
            self.func_pop()
        elif func_ == "len":
            print(len(self.my_list))
        elif func_ == "print":
            print(self.my_list)
        elif func_ == "clear":
            self.my_list.clear()
        else:
            raise Exception(func_ + "는 올바른 명령어가 아닙니다.")


def main():
    my_list_method = List_method()
    while True:
        try:
            my_list_method.prompt()
        except Exception as e:
            print(e)
            my_getter.buffer_clear()
        except TypeError as e:
            print(e)
            my_getter.buffer_clear()


if __name__ == '__main__':
    main()
