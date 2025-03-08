#!/bin/bash

HIST_FILE="calc_history.txt"
ANS_FILE="calc_ans.txt"

# Khởi tạo biến ANS nếu chưa có
if [ ! -f "$ANS_FILE" ]; then
    echo "0" > "$ANS_FILE"
fi

# Đọc giá trị ANS từ file
ANS=$(cat "$ANS_FILE")

declare -a HISTORY
if [ -f "$HIST_FILE" ]; then
    mapfile -t HISTORY < "$HIST_FILE"
fi

# Hàm lưu lịch sử tối đa 5 dòng
save_history() {
    HISTORY=("$1" "${HISTORY[@]}")
    if [ ${#HISTORY[@]} -gt 5 ]; then
        HISTORY=("${HISTORY[@]:0:5}")
    fi
    printf "%s\n" "${HISTORY[@]}" > "$HIST_FILE"
}

while true; do
    echo -n ">> "
    read input
    
    if [[ "$input" == "EXIT" ]]; then
        break
    fi
    
    if [[ "$input" == "HIST" ]]; then
        printf "%s\n" "${HISTORY[@]}"
        continue
    fi
    
    input=${input/ANS/$ANS}  # Thay ANS bằng giá trị trước đó
    
    if [[ ! "$input" =~ ^[-+]?[0-9]+([.][0-9]+)?[[:space:]]+[-+x/%/][[:space:]]+[-+]?[0-9]+([.][0-9]+)?$ ]]; then
        echo "SYNTAX ERROR"
        continue
    fi
    
    # Trích xuất toán tử và toán hạng
    num1=$(echo "$input" | awk '{print $1}')
    op=$(echo "$input" | awk '{print $2}')
    num2=$(echo "$input" | awk '{print $3}')
    
    # Xử lý phép tính
    case "$op" in
        +) result=$(echo "$num1 + $num2" | bc -l);;
        -) result=$(echo "$num1 - $num2" | bc -l);;
        x) result=$(echo "$num1 * $num2" | bc -l);;
        /) 
            if [[ "$num2" == "0" ]]; then
                echo "MATH ERROR"
                continue
            fi
            result=$(echo "scale=2; $num1 / $num2" | bc -l)
            ;;
        %) 
            if [[ "$num2" == "0" ]]; then
                echo "MATH ERROR"
                continue
            fi
            result=$(echo "$num1 % $num2" | bc)
            ;;
    esac
    
    # Làm tròn kết quả với 2 chữ số thập phân
    result=$(printf "%.2f" "$result")
    
    # Lưu ANS và lịch sử
    echo "$result" > "$ANS_FILE"
    ANS="$result"
    save_history "$input = $result"
    
    echo "$result"
    read -n 1 -s  # Chờ người dùng bấm phím trước khi tiếp tục
    clear
done

