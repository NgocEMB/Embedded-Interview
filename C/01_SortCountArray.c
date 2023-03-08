#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
/*
Cho mang bat ky
1. Sap xep mang theo thu tu tang dan
2. Liet ke cac phan tu co so lan xuat hien, vd: 1 xuat hien 1 lan
*/

//Quản lý mảng cấp phát động dùng struct
typedef struct{
    uint8_t size;       //Kích thước mảng
    uint8_t *firstAdd;  //Địa chỉ mảng
}typeArray;

/********************************************************************************************
 * Name         :   randomA
 * Function     :   Tạo số ngẫu nhiên trong đoạn từ minN --> maxN
 * Input params :   - [1] minN: Số nhỏ nhất trong đoạn
 *                  - [2] maxN: Số lớn nhất trong đoạn 
 * Return       :   Số nguyên ngẫu nhiên trong đoạn [minN;maxN]
*/
int randomA(int minN, int maxN){
    return minN + rand() % (maxN + 1 - minN);
}

/********************************************************************************************
 * Name         :   randomArray
 * Function     :   Tạo mảng với các phần tử ngẫu nhiên
 * Input params :   - [1] *value: địa chỉ mảng 
 *                  - [2] length: kích thước mảng 
 * Return       :   None
*/
void randomArray(typeArray *value, uint8_t length){
    srand((int)time(0));

    value->size = length;

    value->firstAdd = (uint8_t *)malloc(sizeof(uint8_t)*value->size);   //mảng cấp phát động
    for(int i = 0; i < value->size; ++i){
        value->firstAdd[i] = randomA(0,10);     //Sinh số ngẫu nhiên và lưu vào từng phần tử mảng
    }    
}

/********************************************************************************************
 * Name         :   displayArray
 * Function     :   Hiển thị mảng
 * Input params :   - [1] arr : tên mảng 
 *                  - [2] 
 * Return       :   None
*/
void displayArray(typeArray arr) {
    for (int i = 0; i < arr.size; i++)      //Duyệt qua từng phần tử mảng sau đó in ra
    {
        printf("%d ", arr.firstAdd[i]);
    }
}

/********************************************************************************************
 * Name         :   sortArray
 * Function     :   Sắp xếp mảng theo thứ tự tăng dần
 * Input params :   - [1] *arr : địa chỉ mảng 
 *                  - [2] 
 * Return       :   None
*/
void sortArray(typeArray *arr) {
    for(int i = 0; i < ((arr->size) - 1); i++) {    //Duyệt mảng từ phần tử 0 --> (cuối - 1)
        int minIndex = i;                           //minIndex: lưu chỉ số của phần tử có giá trị nhỏ nhất
        for(int j = i + 1; j < arr->size; j++) {    //Duyệt mảng từ phần tử (i + 1) --> cuối
            if(arr->firstAdd[j] < arr->firstAdd[minIndex]) {
                minIndex = j;                       //Tìm phần tử có giá trị min --> Lưu chỉ số đó vào minIndex
            }
        }
        int temp = arr->firstAdd[i];                //
        arr->firstAdd[i] = arr->firstAdd[minIndex]; //Đổi chỗ phần tử i với minIndex (có giá trị min)
        arr->firstAdd[minIndex] = temp;             //
    }
}

/********************************************************************************************
 * Name         :   sortArray
 * Function     :   Đếm số lần xuất hiện các phần tử mảng cách 1
 * Input params :   - [1] arr : tên mảng 
 *                  - [2] 
 * Return       :   None
*/
void countArrayElements1(typeArray arr) {
    int count = 1;      //count: lưu số lần xuất hiện phần tử mảng
    int i;              //biến lặp
    for (i = 0; i < (arr.size - 1); i++)    //Duyệt từ phần tử 0 --> (cuối - 1)
    {
        if(arr.firstAdd[i] == arr.firstAdd[i + 1]) {
            count++;    //Nếu 2 phần tử liền kề bằng nhau --> tăng số lần xuất hiện
        }
        else {          //Nếu 2 phần tử liền kề không bằng nhau --> Số lần xuất hiện chỉ là 1
            printf("%2d appears %2d time(s)\n", arr.firstAdd[i], count);
            count = 1;
        }
    }
    printf("%2d appears %2d time(s)\n", arr.firstAdd[i], count);
    
}

/********************************************************************************************
 * Name         :   sortArray
 * Function     :   Đếm số lần xuất hiện các phần tử mảng cách 2
 * Input params :   - [1] arr : tên mảng 
 *                  - [2] 
 * Return       :   None
*/
void countArrayElements2(typeArray arr) {
    typeArray checkingArray;        //Mảng đánh dấu các phần tử đã xét, kích thước bằng mảng ban đầu
    checkingArray.size = arr.size;  //và khởi tạo bằng 0
    checkingArray.firstAdd = (uint8_t *)calloc(checkingArray.size, sizeof(checkingArray.size));

    for(int i = 0; i < arr.size; i++) { //Duyệt từ đầu --> cuối mảng
        if(checkingArray.firstAdd[i])   //Nếu phần tử i đã được xét trước đó --> bỏ qua
            continue;
        int count = 1;                  //count: lưu số lần xuất hiện phần tử
        checkingArray.firstAdd[i] = 1;  //Đánh dấu phần tử i đang được xét
        for(int j = i + 1; j < arr.size; j++) {         //Lặp từ phần tử sau i --> cuối
            if(checkingArray.firstAdd[j])               //Bỏ qua các phần tử đã xét
                continue;
            if(arr.firstAdd[i] == arr.firstAdd[j]) {    //Nếu phần tử i và j bằng nhau --> tăng số lần xuất hiện
                count++;
                checkingArray.firstAdd[j] = 1;          //Đánh dấu phần tử đã được xét
            }
        }
        printf("%2d appears %2d time(s)\n", arr.firstAdd[i], count);
    }
    free(checkingArray.firstAdd);       //Giải phóng mảng đánh giấu khỏi bộ nhớ
}

int main(int argc, char const *argv[])
{
    typeArray arr;              //Tạo struct lưu trữ mảng arr
    randomArray(&arr, 20);      //Sinh mảng ngẫu nhiên 20 phần tử, lưu vào arr

    printf("\nBefore sorting: ");
    displayArray(arr);          //Hiển thị mảng
    printf("\nCount the number of the array's elements before sorting\n");
    countArrayElements2(arr);   //Đếm số lần xuất hiện phần tử mảng trước khi được sắp xếp
    printf("\nBefore sorting: ");
    displayArray(arr);          //Hiển thị mảng
    sortArray(&arr);            //Sắp xếp mảng theo thứ tự tăng dần
    printf("\nAfter sorting:  ");
    displayArray(arr);          //Hiển thị mảng
    printf("\nCount the number of the array's elements after sorting\n");
    countArrayElements1(arr);   //Đếm số lần xuất hiện phần tử mảng sau khi được sắp xếp
    
    free(arr.firstAdd);         //Giải phóng vùng nhớ được cấp phát động
    return 0;
}