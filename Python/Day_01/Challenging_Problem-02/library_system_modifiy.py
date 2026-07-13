class LibrarySystem:
    """명령어 기반 도서 대출 관리 시스템"""

    def __init__(self):
        # 책 이름 -> {"total": 총 수량, "remain": 남은 수량}
        # dict는 삽입 순서를 보존하므로 등록 순서 출력에 그대로 사용 가능
        self.books = {}
        # 사용자 이름 -> 대출 중인 책 이름 set
        self.users = {}

    def add_book(self, book_name, num):
        if num <= 0:
            print("ERROR: 수량은 1 이상이어야 합니다.")
            return
        if book_name in self.books:
            self.books[book_name]["total"] += num
            self.books[book_name]["remain"] += num
        else:
            self.books[book_name] = {"total": num, "remain": num}
        print(f"OK: '{book_name}' 등록 완료 (남은 수량: {self.books[book_name]['remain']})")

    def borrow_book(self, user_name, book_name):
        if book_name not in self.books:
            print(f"ERROR: '{book_name}' 책이 존재하지 않습니다.")
            return
        if self.books[book_name]["remain"] <= 0:
            print(f"ERROR: '{book_name}' 남은 수량이 없습니다.")
            return
        borrowed = self.users.get(user_name, set())
        if book_name in borrowed:
            print(f"ERROR: '{user_name}'은(는) 이미 '{book_name}'을(를) 대출 중입니다.")
            return
        self.books[book_name]["remain"] -= 1
        self.users.setdefault(user_name, set()).add(book_name)
        print(f"OK: '{user_name}'이(가) '{book_name}' 대출 완료")

    def return_book(self, user_name, book_name):
        borrowed = self.users.get(user_name, set())
        if book_name not in borrowed:
            print(f"ERROR: '{user_name}'은(는) '{book_name}'을(를) 대출 중이 아닙니다.")
            return
        borrowed.remove(book_name)
        if not borrowed:  # 빈 set이면 사용자 항목 정리
            del self.users[user_name]
        self.books[book_name]["remain"] += 1
        print(f"OK: '{user_name}'이(가) '{book_name}' 반납 완료")

    def status_book(self, book_name):
        if book_name not in self.books:
            print(f"ERROR: '{book_name}' 책이 존재하지 않습니다.")
            return
        info = self.books[book_name]
        print(f"'{book_name}': 남은 수량 {info['remain']} / 전체 {info['total']}")

    def user(self, user_name): #user가 빌린 책을 보기 편하게 수정함
        borrowed = self.users.get(user_name)
        if not borrowed:
            print("EMPTY")
            return
        print("'", user_name, "'이가 빌린 책은 : ", end='')
        for book_name in sorted(borrowed):
            print(book_name, end=', ')
        print()

    def list_books(self):
        if not self.books:
            print("EMPTY")
            return
        for book_name, info in self.books.items():
            print(f"{book_name}: 남은 수량 {info['remain']} / 전체 {info['total']}")


def main():
    system = LibrarySystem()
    print("도서 대출 관리 시스템 (명령어: add, borrow, return, return_book, user, list, Exit)")
    # 수정 : 명령어를 문제에 나와있는것으로 수정함

    while True:
        try:
            line = input("> ").strip()
        except EOFError:
            break
        if not line:
            continue

        tokens = line.split()
        cmd, args = tokens[0], tokens[1:]

        if cmd == "Exit":
            print("종료합니다.")
            break
        elif cmd == "add":  #수정 : 명령어를 문제에 나와있는것으로 수정함
            if len(args) != 2:
                print("ERROR: 사용법 - add <책이름> <수량>")
                continue
            book_name, num_str = args
            if not num_str.isdigit():
                print("ERROR: 수량은 정수여야 합니다.")
                continue
            system.add_book(book_name, int(num_str))
        elif cmd == "borrow":  # 수정 : 명령어를 문제에 나와있는것으로 수정함
            if len(args) != 2:
                print("ERROR: 사용법 - borrow <사용자이름> <책이름>")
                continue    
            system.borrow_book(args[0], args[1])
        elif cmd == "return":  # 수정 : 명령어를 문제에 나와있는것으로 수정함
            if len(args) != 2:
                print("ERROR: 사용법 - return <사용자이름> <책이름>")
                continue
            system.return_book(args[0], args[1])
        elif cmd == "status":  # 수정 : 명령어를 문제에 나와있는것으로 수정함
            if len(args) != 1:
                print("ERROR: 사용법 - status <책이름>")
                continue
            system.status_book(args[0])
        elif cmd == "user":
            if len(args) != 1:
                print("ERROR: 사용법 - user <사용자이름>")
                continue
            system.user(args[0])
        elif cmd == "list":
            if args:
                print("ERROR: 사용법 - list")
                continue
            system.list_books()
        else:
            print(f"ERROR: 알 수 없는 명령어 '{cmd}'")


if __name__ == "__main__":
    main()
