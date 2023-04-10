#include "../inc/Menu.h"
#include <iostream>
#include <iomanip>

#define EMPTY        0
#define NOT_EMPTY    1
#define NONE        -1

//Các tiêu đề của danh sách sinh viên
#define HEADER                                                                                                     \
    do                                                                                                             \
    {                                                                                                              \
        cout << setfill((char)205) << setw(92) << (char)205 << setfill(' ') << endl;                               \
        cout << (char)186 << setw(5) << left << "ID" << (char)179 << setw(22) << left << "Ho va ten" << (char)179; \
        cout << setw(12) << left << "Gioi tinh" << (char)179 << setw(6) << left << "Tuoi" << (char)179;            \
        cout << setw(6) << left << "Toan" << (char)179 << setw(6) << left << "Ly" << (char)179;                    \
        cout << setw(6) << left << "Hoa" << (char)179 << setw(9) << left << "Diem TB" << (char)179;                \
        cout << setw(10) << left << "Hoc luc" << (char)186 << endl;                                                \
        cout << setfill((char)205) << setw(92) << (char)205 << setfill(' ') << endl;                               \
    } while (0);

//Nội dung trong danh sách sinh viên
#define CONTENT                                                                                                               \
    do                                                                                                                        \
    {                                                                                                                         \
        cout << (char)186 << setw(5) << left << (int)sv.getID() << (char)179 << setw(22) << left << sv.getTen() << (char)179; \
        cout << setw(12) << left << sv.getGioiTinh() << (char)179 << setw(6) << left << sv.getTuoi() << (char)179;            \
        cout << setw(6) << left << sv.getDiemToan() << (char)179 << setw(6) << left << sv.getDiemLy() << (char)179;           \
        cout << setw(6) << left << sv.getDiemHoa() << (char)179 << setw(9) << left << sv.getDiemTrungBinh() << (char)179;     \
        cout << setw(10) << left << sv.getHocLuc() << (char)186 << endl;                                                      \
        cout << setfill((char)205) << setw(92) << (char)205 << setfill(' ') << endl;                                          \
    } while (0);

//Nhập thông tin bằng getline --> nhập có dấu cách
#define NHAP_THONG_TIN_GETLINE(thong_bao, ten_bien, phuong_thuc) \
    do                                                           \
    {                                                            \
        cout << thong_bao;                                       \
        getline(cin, ten_bien);                                  \
        phuong_thuc(ten_bien);                                   \
    } while (0)

//Nhập thông tin bằng cin
#define NHAP_THONG_TIN_CIN(thong_bao, ten_bien, phuong_thuc) \
    do                                                       \
    {                                                        \
        cout << thong_bao;                                   \
        cin >> ten_bien;                                     \
        cin.ignore(255, '\n');                               \
        phuong_thuc(ten_bien);                               \
    } while (0)

// Cac lua chon cho option 2: cap nhat thong tin sinh vien theo ID
enum OPTION
{
    EXIT,
    NAME,
    SEX,
    AGE,
    MATH,
    PHYSICS,
    CHEMISTRY,
    ALL
};

/* Option 1: Them sinh vien */
void Menu::themSinhVien()
{
    SinhVien sv;
    string ten;
    string gioiTinh;
    int tuoi;
    double diemToan;
    double diemLy;
    double diemHoa;
    double diemTrungBinh;
    string hocLuc;

    cout << "\nID: " << (int)sv.getID() << endl;

    NHAP_THONG_TIN_GETLINE("Ho va ten: ", ten, sv.setTen);
    NHAP_THONG_TIN_GETLINE("Gioi tinh: ", gioiTinh, sv.setGioiTinh);
    NHAP_THONG_TIN_CIN("Tuoi: ", tuoi, sv.setTuoi);
    NHAP_THONG_TIN_CIN("Diem Toan: ", diemToan, sv.setDiemToan);
    NHAP_THONG_TIN_CIN("Diem Ly: ", diemLy, sv.setDiemLy);
    NHAP_THONG_TIN_CIN("Diem Hoa: ", diemHoa, sv.setDiemHoa);

    sv.getDiemTrungBinh();      //Tính điểm trung bình
    sv.getHocLuc();             //Tính học lực --> hiển thị trên daanh sách sinh viên

    danhSachSinhVien.push_back(sv);
}

/* Option 2: Cap nhat thong tin sinh vien theo ID */
bool Menu::capNhatThongTinTheoID()
{
    if (danhSachSinhVien.size() == EMPTY)           //Danh sách trống
    {
        cout << "\nDanh sach trong !!" << endl;
        return EMPTY;
    }

    cout << "\nNhap ID: ";              //Nhập ID để tìm kiếm
    uint8_t id;
    scanf("%hhu", &id);
    cin.ignore(255, '\n');

    for (SinhVien &sv : danhSachSinhVien)       //Duyệt qua từng phần tử trong danh sách sinh viên
    {
        if (id == sv.getID())
        {
            uint8_t option = NONE;
            string ten;
            string gioiTinh;
            int tuoi;
            double diemToan;
            double diemLy;
            double diemHoa;
            double diemTrungBinh;
            string hocLuc;

            do      //Menu các tùy chọn trong mục cập nhật thông tin sinh viên, có thể cập nhật 1 nội dung tùy ý
            {
                cout << "\n\t\t\t\t THONG TIN SINH VIEN HIEN TAI" << endl;
                HEADER;
                CONTENT;

                cout << "\n\tMENU CAP NHAT THONG TIN SINH VIEN" << endl;
                cout << setfill((char)205) << setw(50) << (char)205 << endl;
                cout << " 0 - Thoat." << endl;
                cout << " 1 - Ho va ten." << endl;
                cout << " 2 - Gioi tinh." << endl;
                cout << " 3 - Tuoi." << endl;
                cout << " 4 - Diem toan." << endl;
                cout << " 5 - Diem ly." << endl;
                cout << " 6 - Diem hoa." << endl;
                cout << " 7 - Tat ca." << endl;
                cout << setfill((char)205) << setw(50) << (char)205 << endl;
                cout << "--> Nhap vao tuy chon: ";
                scanf("%hhu", &option);
                cin.ignore(255, '\n');

                switch (option)
                {
                case EXIT:
                {
                    cout << "\n--> Exiting ..." << endl;
                    break;
                }
                case NAME:
                {
                    NHAP_THONG_TIN_GETLINE("Ho va ten: ", ten, sv.setTen);
                    break;
                }
                case SEX:
                {
                    NHAP_THONG_TIN_GETLINE("Gioi tinh: ", gioiTinh, sv.setGioiTinh);
                    break;
                }
                case AGE:
                {
                    NHAP_THONG_TIN_CIN("Tuoi: ", tuoi, sv.setTuoi);
                    break;
                }
                case MATH:
                {
                    NHAP_THONG_TIN_CIN("Diem Toan: ", diemToan, sv.setDiemToan);
                    break;
                }
                case PHYSICS:
                {
                    NHAP_THONG_TIN_CIN("Diem Ly: ", diemLy, sv.setDiemLy);
                    break;
                }
                case CHEMISTRY:
                {
                    NHAP_THONG_TIN_CIN("Diem Hoa: ", diemHoa, sv.setDiemHoa);
                    break;
                }
                case ALL:
                {
                    NHAP_THONG_TIN_GETLINE("Ho va ten: ", ten, sv.setTen);
                    NHAP_THONG_TIN_GETLINE("Gioi tinh: ", gioiTinh, sv.setGioiTinh);
                    NHAP_THONG_TIN_CIN("Tuoi: ", tuoi, sv.setTuoi);
                    NHAP_THONG_TIN_CIN("Diem Toan: ", diemToan, sv.setDiemToan);
                    NHAP_THONG_TIN_CIN("Diem Ly: ", diemLy, sv.setDiemLy);
                    NHAP_THONG_TIN_CIN("Diem Hoa: ", diemHoa, sv.setDiemHoa);
                    break;
                }
                default:
                {
                    cout << "Invalid option !! Please enter again." << endl;
                    break;
                }
                }
            } while (option != EXIT);
            return NOT_EMPTY;
        }
    }
    cout << "Khong tim thay ID trung khop\n";
    return NOT_EMPTY;
}

/* Option 3: Xoa sinh vien theo ID */
bool Menu::xoaSinhVienTheoID()
{
    if (danhSachSinhVien.size() == EMPTY)
    {
        cout << "\nDanh sach trong !!" << endl;
        return EMPTY;
    }

    cout << "\nNhap ID: ";      //Nhập ID cần tìm
    uint8_t id;
    scanf("%hhu", &id);
    cin.ignore(255, '\n');

    int count = 0;
    for (SinhVien sv : danhSachSinhVien)
    {
        if (id == sv.getID())       //Nếu trùng ID
        {
            cout << "ID: " << (int)id << " trung khop: ";
            danhSachSinhVien.erase(danhSachSinhVien.begin() + count);       //Xóa sinh viên đó khỏi danh sách
            cout << "Da xoa !!" << endl;
            return NOT_EMPTY;
        }
        count++;
    }
    cout << "Khong tim thay ID trung khop\n";
    return NOT_EMPTY;
}

/* Option 4: Tim kien sinh vien theo ten */
bool Menu::timKiemSinhVienTheoTen()
{
    if (danhSachSinhVien.size() == EMPTY)
    {
        cout << "\nDanh sach trong !!" << endl;
        return EMPTY;
    }

    cout << "\nNhap ten: ";
    string ten;
    getline(cin, ten);

    for (SinhVien sv : danhSachSinhVien)
    {
        if (ten == sv.getTen())             //Nếu trùng tên
        {
            cout << "Da tim thay !!" << endl;
            HEADER;                         //In ra thong tin sinh viên đó
            CONTENT;
            return NOT_EMPTY;
        }
    }
    cout << "Khong tim thay ten trung khop\n";
    return NOT_EMPTY;
}

/* Option 5: Sap xep sinh vien theo diem trung binh */
static void swap(SinhVien &sv1, SinhVien &sv2)          //Đổi chỗ 2 phần từ trong mảng/vector
{
    SinhVien tmp = sv1;
    sv1 = sv2;
    sv2 = tmp;
}

void Menu::sapXepSinhVienTheoDTB()
{
    if (danhSachSinhVien.size() == EMPTY)
    {
        cout << "\nDanh sach trong !!" << endl;
        return;
    }
    for (int i = 0; i < danhSachSinhVien.size() - 1; i++)
    {
        double max = i;
        for (int j = i + 1; j < danhSachSinhVien.size(); j++)
        {
            if (danhSachSinhVien[max].getDiemTrungBinh() < danhSachSinhVien[j].getDiemTrungBinh())  //Sắp xếp theo điểm trung bình giảm dần
            {
                max = j;
            }
        }
        swap(danhSachSinhVien[i], danhSachSinhVien[max]); // đổi chỗ 2 phần tử mảng/vector
    }
    cout << "Done !!\n";
}

/* Option 6: Sap xep sinh vien theo ten */
void Menu::sapXepSinhVienTheoTen()
{
    if (danhSachSinhVien.size() == EMPTY)           //Nếu danh sách sinh viên trống
    {
        cout << "\nDanh sach trong !!" << endl;
        return;
    }
    for (int i = 0; i < danhSachSinhVien.size() - 1; i++)
    {
        double min = i;
        for (int j = i + 1; j < danhSachSinhVien.size(); j++)
        {
            if (danhSachSinhVien[min].getTen() > danhSachSinhVien[j].getTen())      //Sắp xếp theo bảng chữ cái a b c ...
            {
                min = j;
            }
        }
        swap(danhSachSinhVien[i], danhSachSinhVien[min]);           //Đổi chỗ 2 phần từ mảng/vector
    }
    cout << "Done !!\n";
}

/* Option 7: Hien thi danh sach sinh vien */
void Menu::hienThiDanhSach()
{
    if (danhSachSinhVien.size() == EMPTY)                   //Nếu danh sách sinh viên trống
    {
        cout << "\nDanh sach trong !!" << endl;
        return;
    }
    cout << "\n\t\t\t\t DANH SACH SINH VIEN" << endl;
    HEADER;                                                 //In ra các mục trong danh sách

    for (SinhVien sv : danhSachSinhVien)
    {
        CONTENT;                                            //In ra nội dung thông tin từng sinh viên
    }
}
