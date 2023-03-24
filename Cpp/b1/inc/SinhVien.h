#pragma once
#include <stdint.h>
#include <string>

using namespace std;

class SinhVien
{
private:
    uint8_t id;
    string ten;
    string gioiTinh;
    int tuoi;
    double diemToan;
    double diemLy;
    double diemHoa;
    double diemTrungBinh;
    string hocLuc;

public:
    SinhVien();
    //setter
    void setTen(string ten);
    void setGioiTinh(string gioiTinh);
    void setTuoi(int tuoi);
    void setDiemToan(double diemToan);
    void setDiemLy(double diemLy);
    void setDiemHoa(double diemHoa);

    //getter
    uint8_t getID();
    string getTen();
    string getGioiTinh();
    int getTuoi();
    double getDiemToan();
    double getDiemLy();
    double getDiemHoa();
    double getDiemTrungBinh();
    string getHocLuc();
};