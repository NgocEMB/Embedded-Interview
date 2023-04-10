#include <vector>
#include "../inc/SinhVien.h"

class Menu
{
private:
    vector<SinhVien> danhSachSinhVien;          /* Tạo danh sách sinh viên --> mảng các phần tử, mỗi phần tử là 1 sinh viên */

public:
    void themSinhVien();                        /* Option 1 */
    bool capNhatThongTinTheoID();               /* Option 2 */
    bool xoaSinhVienTheoID();                   /* Option 3 */
    bool timKiemSinhVienTheoTen();              /* Option 4 */
    void sapXepSinhVienTheoDTB();               /* Option 5 */
    void sapXepSinhVienTheoTen();               /* Option 6 */
    void hienThiDanhSach();                     /* Option 7 */
};