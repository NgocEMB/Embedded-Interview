#include <iostream>
#include <iomanip>
#include "../inc/Menu.h"

#define NONE        -1
#define EMPTY       0
//Bắt lỗi nhập vào và nhập tùy chọn tiếp tục hay không?
#define AGAIN_OR_NOT(opt)                                                                                      \
    do                                                                                                         \
    {                                                                                                          \
        do                                                                                                     \
        {                                                                                                      \
            cout << "--> Tiep tuc " << opt << " <Yes/No>: ";                                                   \
            getline(cin, again);                                                                               \
            if (again == "Yes" || again == "yes" || again == "Y" || again == "y")                              \
                break;                                                                                         \
            else if (again == "No" || again == "no" || again == "N" || again == "n")                           \
            {                                                                                                  \
                break;                                                                                         \
            }                                                                                                  \
            else                                                                                               \
                cout << "--> Nhap sai ! Nhap Yes/yes/Y/y neu dong y, nhap No/no/N/n neu khong dong y" << endl; \
        } while (again != "No" && again != "no" && again != "N" && again != "n"                                \
                && again != "Yes" && again != "yes" && again != "Y" && again != "y" );                                                                                  \
} while (0);

enum OPTION
{
    EXIT,           //0
    ADD,            //1
    UPDATE_BY_ID,   //2
    DELETE_BY_ID,   //3
    SEEK_BY_NAME,   //4
    SORT_BY_DTB,    //5
    SORT_BY_NAME,   //6
    SHOW_LIST       //7
};

int main(int argc, char const *argv[])
{
    Menu sv;
    uint8_t option = NONE;    //Lưu các tùy chọn người dùng

    do
    {
        cout << "\n\t\tMENU CHINH" << endl;
        cout << setfill((char)205) << setw(50) << (char)205 << endl;
        cout << " 0 - Thoat." << endl;
        cout << " 1 - Them sinh vien." << endl;
        cout << " 2 - Cap nhat thong tin sinh vien theo ID." << endl;
        cout << " 3 - Xoa sinh vien theo ID." << endl;
        cout << " 4 - Tim kiem sinh vien theo ten." << endl;
        cout << " 5 - Sap xep sinh vien theo diem trung binh." << endl;
        cout << " 6 - Sap xep sinh vien theo ten." << endl;
        cout << " 7 - Hien thi danh sach sinh vien." << endl;
        cout << setfill((char)205) << setw(50) << (char)205 << endl;
        cout << "--> Nhap vao tuy chon: ";

        scanf("%hhu", &option);         //Nhập vào tùy chọn
        cin.ignore(255, '\n');          //bỏ ký tự '\n' trong input bufer

        switch (option)
        {
            case EXIT:  //Số 0 --> thoát
            {
                cout << "--> Exiting ..." << endl;
                break;
            }
            case ADD:   //Số 1 --> Nhập thêm sinh vien
            {
                string again;                               //Lưu giá trị để kiểm tra tiếp tục hay không 
                do
                {
                    cout << "--> Them sinh vien:";
                    sv.themSinhVien();
                    AGAIN_OR_NOT("them sinh vien khac?");   //Tiếp tục hay không?
                } while (again != "No" && again != "no" && again != "N" && again != "n");   //Lặp lại tùy chọn nếu đúng 
                break;
            }
            case UPDATE_BY_ID:  //Số 2 --> Cập nhật sinh viên theo ID
            {
                string again;
                do
                {
                    cout << "--> Cap nhat thong tinh sinh vien theo ID:";
                    if (sv.capNhatThongTinTheoID() == EMPTY)                //Nếu danh sách trống thì thoát tùy chọn
                        again = "No";
                    else
                        AGAIN_OR_NOT("cap nhat thong tin sinh vien khac?");
                } while (again != "No" && again != "no" && again != "N" && again != "n");
                break;
            }
            case DELETE_BY_ID:  //Số 3 --> Xóa sinh viên theo ID
            {
                string again;
                do
                {
                    cout << "--> Xoa sinh vien theo ID:";
                    if (sv.xoaSinhVienTheoID() == EMPTY)
                        again = "No";
                    else
                        AGAIN_OR_NOT("xoa sinh vien khac?");
                } while (again != "No" && again != "no" && again != "N" && again != "n");
                break;
            }
            case SEEK_BY_NAME:  //Số 4 --> Tìm kiếm theo tên sinh viên
            {
                string again;
                do
                {
                    cout << "--> Tim kiem sinh vien theo ten: ";
                    if (sv.timKiemSinhVienTheoTen() == EMPTY)
                        again = "No";
                    else
                        AGAIN_OR_NOT("tim kiem sinh vien khac?");
                } while (again != "No" && again != "no" && again != "N" && again != "n");
                break;
            }
            case SORT_BY_DTB:   //Số 5 --> Sắp xếp theo điểm trung bình giảm dần
            {
                cout << "--> Sap xep sinh vien theo DTB: ";
                sv.sapXepSinhVienTheoDTB();
                break;
            }
            case SORT_BY_NAME:  //Số 6 --> Sắp xếp theo tên sinh viên, theo bảng chữ cái
            {
                cout << "--> Sap xep sinh vien theo ten: ";
                sv.sapXepSinhVienTheoTen();
                break;
            }
            case SHOW_LIST: //Số 7 --> Hiển thị danh sách sinh viên
            {
                cout << "--> Hien thi danh sach sinh vien: ";
                sv.hienThiDanhSach();
                break;
            }
            default:    //Nếu tùy chọn nhập vào không hợp lệ
            {
                cout << "--> Invalid option !! Please enter again." << endl;
                break;
            }
        }
    } while (option != EXIT);   //Thoát khi nhập 0 = EXIT 

    return 0;
}
