import csv
import json
from pathlib import Path

def students_list_cleaner(csv_reader, csv_header):
    #학생부의 reader를 받아와서 유효한 리스트를 반환함
    clean_list = []
    for row in csv_reader:
        row[0] = row[0].strip() # 이름과 점수 공백 제거
        row[1] = row[1].strip()
        try : int(row[1]) # 예외를 이용하여 정수로의 변환을 시도함
        except ValueError as e: 
            print(e, " :\n", row[0], " : ", row[1], " → 숫자 변환 실패")
            continue
        else:
            row[1] = int(row[1])
        
        if 0 <= row[1] and row[1] < 100: #성적의 유효성을 검토함
            clean_list.append(row)
        else:
            print(row[0], " : ", row[1], " → 허용 범위 초과")
    #print(clean_list)
    return clean_list

def student_csv_opener(src_file_location, dist_file_location):
    # csv파일의 위치를 받아서 파일을 연 뒤에 유효한 학생 리스트를 반환함. 또한 clean_students.csv 파일을 생성하여 유효한 학생리스트를 저장함
    try:
        #try문을 이용하여 파일이 존재하는지 확인
        with open(src_file_location, "r", newline="", encoding="utf-8") as file:
            reader = csv.reader(file)
            header = next(reader)
            clean_list = students_list_cleaner(reader, header)
    except FileNotFoundError: print(FileNotFoundError, src_file_location, "이 존재하지 않습니다.") 
    except Exception as e : print("예기치 못한 에러 : ", e)
    else: 
        #유효한 파일이 존재하면 변환후 결과 를 알림
        print("모든 성적을 유효한 성적으로 변환함.\n")
        cleaner_flag = True
    
    with open(dist_file_location, "w", newline="", encoding="utf-8") as file:
        writer = csv.writer(file)
        writer.writerows(clean_list)
        print("유효한 성적을 ", dist_file_location, "에 저장함")
    
    return clean_list


def make_summary(clean_list, dist_file_location):
    # student_csv_opener 함수에서 규격화 된 리스트와 가져와서 요약을 생성함
    # 요약은 인수로 받는 파일 위치에 저장
    
    count = 0
    max_score = -1
    sum_score = 0
    for student in clean_list: #반복문을 이용하여 인원수, 평균, 최고점을 구한다.
        count += 1
        sum_score += student[1]
        if max_score < student[1]:
            max_score = student[1]
    avg = sum_score / count

    summery = {"인원수" : count, "평균" : avg, "최고점" : max_score}
    with open(dist_file_location, "w", encoding="utf-8") as file:
        json.dump(summery, file, ensure_ascii=False, indent=2)


def main():
    open_file_name = "./students.csv"
    new_file_name = "./clean_students.csv"
    new_json_filename = "./summary.json"
    student_list = student_csv_opener(open_file_name, new_file_name)
    make_summary(student_list, new_json_filename)


if __name__ == "__main__":
    main()
