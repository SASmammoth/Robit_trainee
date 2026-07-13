### 같은 폴더의 map.txt 파일을 복붙하면 편하게 맵 생성이 가능함

SIZE_OF_MAP = 10 #미로의 크기


class Maze:
    def __init__(self):
        self.map_ = []
        self.position = {"loc_x":1, "loc_y":1}

    def location_return(self, y = 0 , x = 0):
        # 현재 개미의 위치와 xy좌표 증분을 입력받아 그 타일의 값을 반환
        return self.map_[self.position["loc_y"] + y][self.position["loc_x"] + x]

    def map_clear(self):
        # 맵 클리어
        self.map_.clear()
        self.position = {"loc_x": 1, "loc_y": 1}

    def location_drow(self):
        # 개미의 위치에
        self.map_[self.position["loc_y"]][self.position["loc_x"]] = 9

    def map_builder(self):
        # 사용자의 입력을 받아 맵을 생성함
        print("맵을 숫자로 입력하시오(맵의 크기는", SIZE_OF_MAP, " x ", SIZE_OF_MAP, "입니다)")
        for i1 in range(SIZE_OF_MAP):
            temp_input = input().replace(" ", "")
            temp_list = []
            if len(temp_input) != SIZE_OF_MAP:
                raise Exception("맵의 가로 길이가 입력과 다름.")
            for i2 in temp_input:
                try:
                    value = int(i2)
                except ValueError:
                    raise Exception("index는 int형식의 문자가 와야함")
                temp_list.append(value)
            self.map_.append(temp_list)

    def print_map(self):
        # 맵을 출력하는 코드
        print()
        for i1 in self.map_:
            for i2 in i1:
                print(i2, end=' ')
            print()
        print()

    def direction_compus(self):
        # 개미의 이동규칙에 따라 개미의 다음행동을 반환함
        if self.location_return() == 2:
            return '2'
        elif self.location_return(0, 1) == 0 or self.location_return(0, 1) == 2:
            return 'r'
        elif self.location_return(1, 0) == 0 or self.location_return(1, 0) == 2:
            return 'd'
        else :
            return 'X'

    def ant_finder(self):
        # 개미가 먹이를 찾거나 더 이상 이동할 수 없을때 까지 흔적을 남기며 이동하는 코드, 끝나면 맵을 화면에 표시해줌
        while True :
            # print(self.position)
            if self.direction_compus() == 'r':
                self.location_drow()
                self.position["loc_x"] += 1
            elif self.direction_compus() == 'd':
                self.location_drow()
                self.position["loc_y"] += 1
            elif self.direction_compus() != '2' or self.direction_compus() != 'X':
                self.location_drow()
                break

        self.print_map()

def main():
    maze = Maze()
    while True:
        try:
            maze.map_builder()
            maze.ant_finder()
        except Exception as e:
            print(e)
            maze.map_clear()
        maze.map_clear()


if __name__ == "__main__":
    main()
