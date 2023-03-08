#include <stdio.h>
#include <stdlib.h> 

//Quản lý mảng cấp phát động dùng struct
typedef struct {
    int len;                //Kích thước mảng
    char *p_array_addr;     //Địa chỉ mảng
}My_Array_t;

/********************************************************************************************
 * Name         :   length
 * Function     :   Tính độ dài chuỗi
 * Input params :   - (1) s[]: chuỗi cần tính độ dài
 *                  - (2) 
 * Return       :   Độ dài chuỗi
*/
int length(const char s[]) {
    int count = 0;
    int i = 0;
    while (s[i++] != '\0') {     //Đếm đến khi gặp ký tự NULL ở cuối
        ++count;
    }
    return count;
}

/********************************************************************************************
 * Name         :   reverseWord
 * Function     :   Copy từ (word) từ mảng nguồn vào mảng đích
 * Input params :   - (1) start_index: chỉ số đầu của từ
 *                  - (2) end_index  : chỉ số cuối của từ
 *                  - (3) *p_array   : mảng đích
 *                  - (4) arr[]      : mảng nguồn
 * Return       :   None
*/
void reverseWord(int start_index, int end_index, char *p_array, char arr[]) {
    static int word_index = 0;          //word_index: đánh dấu vị trí tiếp theo cần gán kỹ tự trong mảng đích
    for (int i = start_index; i <= end_index; i++) {     //Duyệt từng chữ cái trong word, từ trái --> phải
        p_array[word_index++] = arr[i];                 //và copy từ mảng nguồn vào mảng đích
    }
    if (start_index != 0)                //Nếu chưa kết thúc chuỗi
        p_array[word_index++] = ' ';    //thì thêm dấu cách sau mỗi word
}

/********************************************************************************************
 * Name         :   reverseString
 * Function     :   Tách từng từ (word) trong chuỗi từ cuối về đầu
 * Input params :   - (1) *p_array: mảng đích
 *                  - (2) arr[]   : mảng nguồn
 * Return       :   None
*/
void reverseString(char *p_array, char arr[]) {
    //Duyệt từng ký tự từ cuối chuỗi về đầu
    for (int end_index = (length(arr) - 1); end_index >= 0;) {
        int start_index = end_index;      //start_index: chỉ số đầu của word
        int j = end_index;                //end_index  : chỉ số cuối của word
        //Tách word khi gặp khoảng trắng && chưa kết thúc chuỗi
        while ((arr[j] != ' ') && (j >= 0)) {   
            j--;                //duyệt qua từng chữ cái
        }
        start_index = ++j;    //lưu chỉ số đầu của word, không tính dấu cách
        //Gọi hàm copy word theo chiều từ đầu về cuối chuỗi
        reverseWord(start_index, end_index, p_array, arr);  
        end_index = start_index-2;  //Chỉ số cuối của word tiếp theo, không tính dấu cách 
    }
}

/********************************************************************************************
 * Name         :   capitalizeAfterDot
 * Function     :   In hoa chữ cái đầu tiên sau dấu chấm
 * Input params :   - (1) arr[]: mảng xét
 *                  - (2) 
 * Return       :   None
*/
void capitalizeAfterDot(char arr[]) {
    for (int i = 0; i < length(arr); i++)       //Duyệt từ đầu đến cuối chuỗi
    {
        if (arr[i] == '.') {                     //Xác định vị trí dấu chấm
            int j = i + 1;                      //Tìm chữ cái đầu tiên sau dấu chấm
            while (j < length(arr)) {            //trong chuỗi
                if (arr[j] >= 'a' && arr[j] <= 'z') {    //Nếu là chữ thường thì in hoa
                    arr[j] -= 32;               //chữ thường - 32 = chữ hoa
                    break;
                }
                else if (arr[j] >= 'A' && arr[j] <= 'Z') break;  //Không xét chữ hoa
                ++j;                            //Tăng j --> duyệt chữ cái tiếp theo nếu chưa tìm thấy chữ thường
            }
            i = j;                              //Xét tiếp các chữ cái còn lại
        }
    }  
}

/********************************************************************************************
 * Name         :   capitalizeAllString
 * Function     :   In hoa toàn bộ chuỗi
 * Input params :   - (1) arr[]: mảng xét
 *                  - (2) 
 * Return       :   None
*/
void capitalizeAllString(char arr[]) {
    for (int i = 0; i < length(arr); i++)           //Duyệt toàn bộ chuỗi
    {
        if ((arr[i] >= 'a') && (arr[i] <= 'z')) {    //Nếu là ký tự in thường
            arr[i] -= 32;                           //thì gán bằng ký tự in hoa tương ứng
        } 
    } 
}

/********************************************************************************************
 * Name         :   lowerAllString
 * Function     :   In thường toàn bộ chuỗi
 * Input params :   - (1) arr[]: mảng xét
 *                  - (2) 
 * Return       :   None
*/
void lowerAllString(char arr[]) {
    for (int i = 0; i < length(arr); i++)           //Duyệt toàn bộ chuỗi
    {
        if ((arr[i] >= 'A') && (arr[i] <= 'Z')) {    //Nếu là ký tự in hoa
            arr[i] += 32;                           //thì gán bằng ký tự in thường tương ứng
        } 
    } 
}

int main(int argc, char const *argv[])
{
    //Sample input
    char arr[] = "The Grammy award-winning singer... who has been less active on digital platforms in recent weeks. \
explained her decision to distance herself from social media platforms during an appearance on the Conan OBrien \
Needs a Friend podcast, alongside her brother Finneas";

    My_Array_t str;         //Tạo mảng cấp phát động để lưu chuỗi đảo ngược
    str.len = length(arr);  //Xác định kích thước mảng
    str.p_array_addr = (char *)calloc((str.len + 1), sizeof(char)); //Cấp phát động cho mảng, thêm 1 ô nhớ cho '\0'
    str.p_array_addr[str.len] = '\0';   //Cho phần tử cuối là NULL --> Kết thúc chuỗi
    /*Câu 1: Viết chuỗi đảo ngược*/
    printf("---------------------------------------------------------------------\n");
    reverseString(str.p_array_addr, arr);
    printf("%s\n", arr);
    printf("\n");
    printf("%s\n", str.p_array_addr);
    /*Câu 2: In hoa chữ cái đầu tiên sau dấu chấm*/
    capitalizeAfterDot(arr);
    printf("\n");
    printf("%s\n", arr);
    /*Câu 3: Chuyển chuỗi thành chữ thường*/
    capitalizeAllString(arr);
    printf("\n");
    printf("%s\n", arr);
    /*Câu 4: Chuyển chuỗi thành chữ hoa*/
    lowerAllString(arr);
    printf("\n");
    printf("%s\n", arr);

    printf("---------------------------------------------------------------------\n");
    free(str.p_array_addr);     //Giải phóng bộ nhớ được cấp phát động
    return 0;
}
