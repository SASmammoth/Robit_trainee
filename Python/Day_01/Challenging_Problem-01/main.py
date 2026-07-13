class Getter:
    # 사용자로 부터 입력을 받는 클래스
    def __init__(self):
        self.words = []

    def pin_(self):
        if len(self.words) == 0:
            # 입력을 의미있는 요소(", (, ) 등)을 포함하여 분리하기위해 특수문자인 ◆를 앞뒤에 넣어 분리 후 삭제하는 형식을 취함 
            # 더 좋은 방법이 있을거 같음
            temp_ = input("=>")
            temp_ = temp_.replace(" ", "")
            # print(temp_)
            temp_ = temp_.replace("(", "◆(◆")
            temp_ = temp_.replace(")", "◆)◆")
            # print(temp_)
            temp_ = temp_.replace('"', '◆"◆')
            # print(temp_)
            self.words = temp_.split("◆")
            self.words = [x for x in self.words if x]
            # print(self.words)
            return self.words.pop(0)
        else:
            return self.words.pop(0)

    def buffer_push(self, word):
        self.words.insert(0, word)

    def buffer_clear(self):
        self.words.clear()


class Compressor:
    def __init__(self):
        pass

    def compress(self, text):
        #압축코드
        if not text.isalpha():
            raise Exception("오직 영문자로 구성된 문자열 만 압축할수 있음")

        code = ""
        prev_char = '\0'
        text += '\0'
        prev_char_num = 1

        #인접한 두 문자를 비교하여 두개가 서로 같으면 prev_char_num를 증가시켜 개수를 세고, 문자와 prev_char_num를 code 마지막에 넣는다. 
        for i in range(1, len(text)):
            if text[i-1] != text[i]:
                code += text[i-1]
                code += str(prev_char_num)
                prev_char_num = 1
            else:
                prev_char_num+=1
        
        #print("text : ", len(text), "code : ", len(code))
        if len(text) < len(code): #code와 text중 작은거만 반환한다.
            return text
        else : 
            return code

    def decompress(self, code):
        #압축 해제 코드
        text = ""
        
        if self.is_valid_code(code) == "ERROR": return "ERROR" #code가 유효한지 검사  
        
        word_list = self.sprite_word_(code)
        for pt in range(0,len(word_list), 2):
            #유효한 code라면 문자와 숫자가 한 쌍 씩 짝수개 만큼 있을
            text += word_list[pt] * word_list[pt+1]
            
        return text
                    
    def sprite_word_(self, code):
        #문자열로 된 코드를 입력받아서 리스트 형식으로 반환
        #리스트는 문자와 int형 정수로 구성되어 있다.
        word_list = []
        temp_number = ""
        num_flag = False #앞에 나온 문자가 숫자인지 저장하는 플래그
        code += '\0' # 마지막 문자 or 숫자가 무시되는걸 방지하기위한 \0
        for pt in code:
            if pt.isalpha() or pt == '\0':
                #문자를 입력받았을때 문자를 저장. 앞에 숫자였으면 숫자를 int형식으로 변환하여 먼저 그 앞에 저장
                #print("--", pt)
                if num_flag:
                    num_flag = False
                    word_list.append(int(temp_number))
                    word_list.append(pt)
                    temp_number = ""
                else:    
                    word_list.append(pt)
            elif pt.isdigit() :
                if num_flag: temp_number += pt
                else: 
                    num_flag = True
                    temp_number += pt
        word_list.pop()
        return word_list
                    
                

    def is_valid_code(self, code):
        #유효한 코드인지 확인
        word_list = self.sprite_word_(code)
        triger = [False, False] #유효 코드 여부를 확인하는 트리거, 앞의 값은 문자, 뒤의 값은 int형 숫자를 나타낸다.
        
        for pt in word_list:
            if isinstance(pt, str):
                if triger == [False, False] or triger == [True, True]: # 문자는 가장 처음 혹은 완성된 코드쌍 뒤에 와야함
                    triger = [True, False]
                    continue
                else : 
                    #raise Exception("문자는 맨 처음에 오거나 숫자 뒤에 와야함")
                    return "ERROR"
            elif isinstance(pt, int):
                if triger == [True, False]: # 숫자는 문자 뒤에만 와야함
                    if pt <= 0:
                        #raise Exception("숫자는 양의 정수만 올수 있음")
                        return "ERROR"
                    else: triger[1] = True
                else: 
                    #raise Exception("숫자는 오직 문자 뒤에만 올수있음")
                    return "ERROR"
        if triger == [True, True]: return "OK"
        else : return "ERROR" # code 는 숫자로 끝나야 함.

my_getter = Getter()
my_compressor = Compressor()

class Compressor_manager:
    # 문자열 압축, 복원 프로그램을 위한 파서 이다. 파서의 형식은 paser.txt파일에 있다.
    # paser.txt 참조 바람
    #
    def __init__(self):
        pass

    def print_statement(self):
        left = my_getter.pin_()
        if not ( left == "print" or left == "Print"):
            raise Exception("압축프로그램의 시작은 오직 \"print (Print)\" 만 올수있음.")

        mid = my_getter.pin_()
        if not mid == "(":
            raise Exception('print 다음에는 \"(\"가 와야됨')

        out_put = self.commend()

        right = my_getter.pin_()
        if not right == ")":
            raise Exception('print 마지막에는 \")\"가 와야됨')
        return out_put

    def commend(self):
        out_put = ""
        cmd = my_getter.pin_()
        if cmd == "compress" or cmd == "decompress":
            left = my_getter.pin_()
            if not left == "(":
                raise Exception('명령어 다음에는 \"(\"가 와야됨')

            mid_l = my_getter.pin_()
            if not mid_l == '"':
                raise Exception('text나 code는 \"로 감싸저 있어야 함')

            text_or_code = my_getter.pin_()
            if cmd == "compress":
                out_put = my_compressor.compress(text_or_code)
            elif cmd == "decompress":
                out_put = my_compressor.decompress(text_or_code)

            mid_r = my_getter.pin_()
            if not mid_r == '"':
                raise Exception('text나 code는 "로 감싸저 있어야 함')

            right = my_getter.pin_()
            if not right == ")":
                raise Exception('명령어 마지막에는 ")"가 와야됨')
        else:
            raise Exception("명령어는 오직 compress와 decompress만이 가능함")
        return out_put

my_compressor_manager = Compressor_manager()


def main():
    while True:
        # temp = input()

        try:
            print(my_compressor_manager.print_statement())
        except Exception as e:
            print(e)


if __name__ == "__main__":
    main()
