#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NAM         0  
#define LAM         1  
#define TRAM        0  
#define TRAM_LINH   1 

//Quản lý mảng cấp phát động dùng struct
typedef struct 
{
    uint8_t length;     //Kích thước mảng
    uint8_t *p_addr;    //Địa chỉ mảng
}my_array_t;

/********************************************************************************************
 * Name         :   separateNumber
 * Function     :   Tách số thành các chữ cái riêng lẻ --> lưu vào mảng
 * Input params :   - (1) num            : số cần tách
 *                  - (2) *indexing_array: mảng lưu trữ các chữ số
 * Return       :   Địa chỉ của mảng các chữ số đã được tách
*/
uint8_t *separateNumber(uint32_t num, my_array_t *indexing_array) {
    uint8_t count_digits = 0;           /*!< Lưu số lượng chữ số      >*/
    uint32_t temp = num;                /*!< Biến tạm dùng đếm chữ số >*/
    uint8_t position_digits = 0;        /*!< Lưu vị trí chữ số        >*/

    //Đếm số chữ số
    while (temp != 0)
    {
        ++count_digits;
        temp /= 10;                     //Loại 1 chữ số cuối cùng từ phải sang trái
    }

    //Tạo mảng
    if (num == 0) count_digits = 1;             //Trường hợp số nhập vào là 0 --> vẫn có 1 chữ số
    indexing_array->length = count_digits;      //Số phần tử mảng = số chữ số
    indexing_array->p_addr = (uint8_t *)calloc(count_digits, sizeof(uint8_t));  //Tạo vùng nhớ mảng

    //Lưu các chữ số vào mảng
    while (num != 0)
    {
        indexing_array->p_addr[position_digits++] = num % 10; //Tách lấy chữ số phải cùng, lưu lần lượt vào mảng
        num /= 10;                                            //Sau khi đã lưu chữ số phải cùng, loại bỏ chữ số đó
    }

    return indexing_array->p_addr;      //Trả về địa chỉ mảng
}

/********************************************************************************************
 * Name         :   digitToWord
 * Function     :   Chuyển chữ số thành dạng chữ viết tương ứng
 * Input params :   - (1) digit: chữ số cần chuyển đổi
 *                  - (2) lam  : liệu là "lăm" hay "năm"
 * Return       :   Dạng chữ viết của chữ số tương ứng
*/
uint8_t *digitToWord(uint8_t digit, uint8_t lam) {
    uint8_t *word;                  /*!< Lưu kết quả dạng chữ viết của chữ số >*/
    switch (digit)                  //Dựa theo đó là chữ chữ mấy
    {
        case 0:
            word = "KHÔNG ";
            break;
        case 1:
            word = "MỘT ";
            break;
        case 2:
            word = "HAI ";
            break;
        case 3:
            word = "BA ";
            break;
        case 4:
            word = "BỐN ";
            break;
        case 5:                     //Xét thêm cắc trường hợp đặc biệt của số 5
        {
            switch (lam)            //Nếu lam = LAM thì dùng "LĂM"
            {                       //Nếu lam = NAM thì dùng "NĂM"
            case NAM:
                word = "NĂM ";
                break;
            default:
                word = "LĂM ";
                break;
            }
            break;
        }
        case 6:
            word = "SÁU ";
            break;
        case 7:
            word = "BẢY ";
            break;
        case 8:
            word = "TÁM ";
            break;
        case 9:
            word = "CHÍN ";
            break;
        default:
            word = "";
            break;
        }
    return word;
}

/********************************************************************************************
 * Name         :   numberUnits
 * Function     :   Lựa chọn đơn vị tương ứng cho nhóm phần MƯƠI, phần TRĂM, phần NGHÌN, phần TRIỆU, phần TỶ
 * Input params :   - (1) position: vị trí của chữ số
 *                  - (2) linh    : "TRĂM LINH" hay chỉ là "TRĂM"
 * Return       :   Đơn vị cho nhóm phần tương ứng
*/
uint8_t *numberUnits(uint8_t position, uint8_t linh) {
    uint8_t *word;                      /*!< Lưu kết quả đơn vị của nhóm phần tương ứng >*/
    switch (position)                   //Dựa theo vị trí chữ số
    {
        case 1:
        case 4:
        case 7:
            word = "MƯƠI ";
            break;    
        case 2:
        case 5:
        case 8:                         //Xét trường hợp đặc biệt khi là nhóm phần TRĂM
        {                               //Sẽ có thêm "LINH" hoặc không
            switch (linh)
            {
            case TRAM:
                word = "TRĂM ";
                break;
            default:
                word = "TRĂM LINH ";
                break;
            }
            break;   
        }
        case 3:
            word = "NGHÌN ";
            break;
        case 6:
            word = "TRIỆU ";
            break;
        case 9:
            word = "TỶ ";
            break;
        default:
            word = "";
    }
    return word;
}

/********************************************************************************************
 * Name         :   printGroup3D
 * Function     :   In cách đọc/viết theo nhóm 3 chữ số: nhóm phần trăm, phần nghìn, phần triệu, phần tỷ.
 * Input params :   - (1) group_index  : chỉ số của chữ số đầu tiên trong nhóm
 *                  - (2) biggest_index: chỉ số của chữ số cuối cùng, có trọng số cao nhất
 *                  - (3) *arr         : mảng chữ số
 * Return       :   None
*/
void printGroup3D(uint8_t group_index, uint8_t biggest_index, uint8_t *arr) {
    uint8_t num_group_digit = biggest_index - group_index;  //Số chữ số tính từ số có trọng cao nhất 
                                                            //đến chữ số đầu tiên trong nhóm, 
                                                            //VD: 905673 --> Xét nhóm phần nghìn, từ 9 đến 5 có 2 chữ số
    //Xét các TH đặc biệt, TQ: x1-x2-x3
    if (num_group_digit == 0) {                             //Nếu chỉ có 1 chữ số 0-0-x3 --> in ra luôn x3
        printf("%s", digitToWord(arr[group_index], NAM));
    } else {                                                //Nếu có 2 hoặc 3 chữ số trong nhóm, 0-x2-x3 hoặc x1-x2-x3
        int8_t third_digit = (num_group_digit >= 2) ? arr[group_index+2] : -1;  /*!< Lưu chữ số thứ ba >*/
        int8_t third_index = (num_group_digit >= 2) ? (group_index+2) : -1;     /*!< Lưu chỉ số chữ số thứ ba >*/
                                                                                //có 2 chữ số --> = -1 --> case default
        if (arr[group_index + 1] == 1) {        //x2 = 1
            if (arr[group_index] != 0) {        //In ra theo x1-1-x3 hoặc 0-1-x3 --> x1 trăm-mười-x3 hoặc mười-x3
                printf("%s%s%s%s", digitToWord(third_digit, NAM), numberUnits(third_index, TRAM), "MƯỜI ", \
                                   digitToWord(arr[group_index], LAM));
            }
            else {                              //In ra theo x1-1-0 hoặc 0-1-0 --> x1 trăm mười hoặc mười
                printf("%s%s%s", digitToWord(third_digit, NAM), numberUnits(third_index, TRAM), "MƯỜI ");
            }
        }
        else if (arr[group_index + 1] == 0) {   //x2 = 0
            if (arr[group_index] != 0) {        //x1-0-x3 hoặc 0-0-x3 --> x1 trăm-linh-x3 hoặc x3
                printf("%s%s%s", digitToWord(third_digit, NAM), numberUnits(third_index, TRAM_LINH), \
                                 digitToWord(arr[group_index], NAM));
            }
            else {                              //x1-0-0 hoặc 0-0-0 --> x1 trăm
                printf("%s%s", digitToWord(third_digit, NAM), numberUnits(third_index, TRAM));
            }
        }
        else {
            if(arr[group_index] != 0) { //x1-x2-x3 hoặc 0-x2-x3 --> x1 trăm-x2 mươi-x3 hoặc x2 mươi-x3
                printf("%s%s%s%s%s", digitToWord(third_digit, NAM), numberUnits(third_index, TRAM),          \
                                     digitToWord(arr[group_index+1], NAM), numberUnits(group_index+1, TRAM), \
                                     digitToWord(arr[group_index], LAM));
            }
            else {  //x1-x2-0 hoặc 0-x2-0 --> x1 trăm-x2 mươi hoặc x2 mươi
                printf("%s%s%s%s", digitToWord(third_digit, NAM), numberUnits(third_index, TRAM), \
                                   digitToWord(arr[group_index+1], NAM), numberUnits(group_index+1, TRAM));
            }
        }
    }   
}

/********************************************************************************************
 * Name         :   group3Digits
 * Function     :   Xác định nhóm phần tỷ, triệu, nghìn hay đơn vị
 * Input params :   - (1) group_index  : chỉ số của chữ số đầu tiên trong nhóm
 *                  - (2) biggest_index: chỉ số của chữ số cuối cùng, có trọng số cao nhất
 *                  - (3) *arr         : mảng chữ số
 * Return       :   None
*/
void group3Digits(uint8_t group_index, uint8_t biggest_index, uint8_t *arr) {
    //Các chữ số trong nhóm khác 0 mới cần đọc, nếu cả nhóm = 0 thì không cần phân tích. 
    //VD: 9,000,100 --> bỏ qua nhóm phần nghìn --> chín triệu một trăm
    if ((arr[group_index] != 0) || (arr[group_index + 1] != 0) || (arr[group_index + 2] != 0)) {
        if (group_index >= 9) {      //Nhóm phần tỷ
            printGroup3D(group_index, biggest_index, arr);      //Đọc theo nhóm
            printf("%s ", "TỶ");                                //Thêm đơn vị vào cuối nhóm
        }
        else if (group_index >= 6) { //Nhóm phần triệu
            printGroup3D(group_index, biggest_index, arr);      //Đọc theo nhóm
            printf("%s ", "TRIỆU");                             //Thêm đơn vị vào cuối nhóm
        }
        else if (group_index >= 3) { //Nhóm phần nghìn
            printGroup3D(group_index, biggest_index, arr);      //Đọc theo nhóm
            printf("%s ", "NGHÌN");                             //Thêm đơn vị vào cuối nhóm
        }
        else if (group_index >= 0) { //Nhóm phần đơn vị
            printGroup3D(group_index, biggest_index, arr);      //Đọc theo nhóm, nhóm này không cần thêm đơn vị
        }
    }
}

/********************************************************************************************
 * Name         :   numberToSentence
 * Function     :   Chuyển số thành cách đọc/ cách viết
 * Input params :   - (1) indexing_array : mảng lưu các chữ số
 * Return       :   None
*/
void numberToSentence(my_array_t indexing_array) {
    uint8_t biggest_index = indexing_array.length - 1;  /*!< Lưu chỉ số của chữ số có trọng số cao nhất >*/
    int8_t i;                                           /*!< Biến chạy cho vòng lặp >*/
    //Tách mỗi 3 chữ số thành 1 nhóm
    for (i = biggest_index; i >= 0; i -= 3)     //Duyệt từ nhóm cao xuống thấp, từ trọng số cao xuống trọng số thấp
    {  
        uint8_t temp = i % 3;                   //Xác định vị trí/chỉ số của chữ số bắt đầu nhóm, là (i - temp)
        group3Digits((i - temp), biggest_index, indexing_array.p_addr); 
    }
}

int main() {
    uint32_t num;                           /*!< Số cần xét >*/
    my_array_t indexing_array;              /*!< Mảng lưu các chữ số >*/

    printf("\nBằng số: ");
    scanf("%d", &num);
    separateNumber(num, &indexing_array);   //Tách chữ số và lưu vào mảng
    printf("Bằng chữ: ");
    numberToSentence(indexing_array);       //Chuyển số thành cách đọc/viết, dựa vào vị trí chữ số
    printf("\n\n");

    free(indexing_array.p_addr);            //Thu hồi vùng nhớ động
    return 0;
}