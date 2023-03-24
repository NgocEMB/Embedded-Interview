#include "../inc/SinhVien.h"
#include <iostream>

#define NONE    -1

SinhVien::SinhVien()
{
    // Tạo mã sinh viên và tự động tăng
    static uint8_t id = 100;
    this->id = id;
    id++;

    //Khởi tạo các thuộc tính là rỗng
    ten = "";
    gioiTinh = "";
    tuoi = 0;
    diemToan = NONE;
    diemLy = NONE;
    diemHoa = NONE;
    diemTrungBinh = NONE;
    hocLuc = "";
}

void SinhVien::setTen(string ten)
{
    this->ten = ten;
}

void SinhVien::setGioiTinh(string gioiTinh)
{
    if (gioiTinh != "Nam" && gioiTinh != "Nu")
    {
        printf("ERROR!! Gioi tinh khong hop le!\n");
    }
    else
    {
        this->gioiTinh = gioiTinh;
    }
}

void SinhVien::setTuoi(int tuoi)
{
    // tuoi chi co the la so duong
    if (tuoi <= 0)
    {
        cout << "ERROR!! Tuoi khong hop le!\n";
    }
    else
    {
        this->tuoi = tuoi;
    }
}

void SinhVien::setDiemToan(double diemToan)
{
    // diem chi co the la so duong va <= 10
    if (diemToan <= 0 || diemToan >= 10)
    {
        cout << "ERROR!! Diem khong hop le!\n";
        this->diemToan = NONE;
    }
    else
    {
        this->diemToan = diemToan;
    }
}

void SinhVien::setDiemLy(double diemLy)
{
    // diem chi co the la so duong va <= 10
    if (diemLy <= 0 || diemLy >= 10)
    {
        cout << "ERROR!! Diem khong hop le!\n";
        this->diemLy = NONE;
    }
    else
    {
        this->diemLy = diemLy;
    }
}

void SinhVien::setDiemHoa(double diemHoa)
{
    // Diem chi co the la so duong va <= 10
    if (diemHoa <= 0 || diemHoa >= 10)
    {
        cout << "ERROR!! Diem khong hop le!\n";
        this->diemHoa = NONE;
    }
    else
    {
        this->diemHoa = diemHoa;
    }
}

uint8_t SinhVien::getID()
{
    return id;
}

string SinhVien::getTen()
{
    return ten;
}

string SinhVien::getGioiTinh()
{
    return gioiTinh;
}

int SinhVien::getTuoi()
{
    return tuoi;
}

double SinhVien::getDiemToan()
{
    return diemToan;
}

double SinhVien::getDiemLy()
{
    return diemLy;
}

double SinhVien::getDiemHoa()
{
    return diemHoa;
}

double SinhVien::getDiemTrungBinh()
{
    if(diemHoa == NONE) {             //Nếu điểm không hợp lệ hoặc chưa được nhập
        cout << "ERROR!! Vui long cap nhat lai diem Hoa!\n";
        diemTrungBinh = NONE;         //Không tính điểm trung bình
    }
    else if(diemLy == NONE) {
        cout << "ERROR!! Vui long cap nhat lai diem Ly!\n";
        diemTrungBinh = NONE;
    }
    else if(diemToan == NONE) {
        cout << "ERROR!! Vui long cap nhat lai diem Toan!\n";
        diemTrungBinh = NONE;
    }
    else {
        diemTrungBinh = (diemHoa + diemLy + diemToan)/3;    //Tính điểm trung bình 
    }
    return diemTrungBinh;
}

string SinhVien::getHocLuc()
{
    if(getDiemTrungBinh() >= 8.0)
    {
        hocLuc = "Gioi";
    }
    else if(getDiemTrungBinh() >= 6.5)
    {
        hocLuc = "Kha";
    }
    else if(getDiemTrungBinh() >= 5.0)
    {
        hocLuc = "Trung binh";
    }
    else if(getDiemTrungBinh() >= 0)
    {
        hocLuc = "Yeu";
    }
    else{       //Nếu chưa có điểm trung bình
        cout << "ERROR!! Vui long cap nhat diem trung binh!\n";
    }
    return hocLuc;
}