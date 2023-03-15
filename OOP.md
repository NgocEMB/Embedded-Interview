# Tổng hợp kiến thức C++ được học 
*(tính đến T2 - 13/03/2023)*
___
1. **Class**

- Là một kiểu dữ liệu do người dùng tự định nghĩa.
- Khai báo *class* bắt đầu bằng từ khóa `class`.
- Bao gồm: các biến (*thuộc tính/property*) và hàm (*phương thức/method*).
- Biến thuộc kiểu dữ liệu *class* được gọi là *object*, mỗi *object* thuộc cùng một *class* sẽ là riêng biệt và được lưu ở vùng nhớ khác nhau, 
mặc dù có tên các thuộc tính và phương thức giống nhau nhưng lại mang giá trị khác nhau.

2. **Access modifiers**

- Là phạm vi truy cập các *thuộc tính* và *phương thức* trong *class*.
- Bao gồm: *public*, *private*, *protected*
  - *public*: các *object* có thể truy cập vào các *thuộc tính* và *phương thức* trong *class* của nó; các *class* con có thể *kế thừa* các 
  *thuộc tính* và *phương thức* của *class* cha.
  - *private*: các *object* không thể truy cập vào các *thuộc tính* và *phương thức* trong *class* của nó; các *class* con không thể *kế thừa* các 
  *thuộc tính* và *phương thức* của *class* cha.
  - *protected*: giống *private* nhưng có một điểm khác biệt là các *class* con kế thừa sẽ chỉ kế thừa được các *thuộc tính* và *phương thức* của *class* cha 
  được đặt trong *public* và *protected*.
  
3. **Thuộc tính và phương thức**

Phần khai báo được đặt trong *access modifier*. Thông thường chỉ khai báo trong *class*, phần implement đặt bên ngoài.
- **_Thuộc tính_**:
  - Là các biến, lưu các đặc tính của đối tượng.
  - Có thể được truy cập trực tiếp thông qua *object* của *class* (sử dụng dấu chấm `<obj_name>.<pro_name>` giống như *struct*) nếu được đặt trong phạm vi *public*.
  - Được kế thừa nếu đặt trong phạm vi *public* và *protected*.
  - Các *phương thức* có thể truy cập vào *thuộc tính* trong cùng *class* bất kể nó thuộc phạm vi nào.
- **_Phương thức_**:
  - Là các hàm, thể hiện các hành động của đối tượng.
  - Có thể được truy cập trực tiếp thông qua *object* của *class* (sử dụng dấu chấm `<obj_name>.<pro_name>` giống như *struct*) nếu được đặt trong phạm vi *public*.
  - Được kế thừa nếu đặt trong phạm vi *public* và *protected*.
  - Có thể implement bên trong hoặc bên ngoài *class*, nhưng thông thường được implement bên ngoài *class*, sử dụng kèm toán tử `::` để xác định thuộc *class* nào 
  (implement bên trong *class* thì không cần `::`). 
  Tương tự, nếu truy xuất *thuộc tính*:
  - VD:

        void ClassName::MethodName() { 
            ClassName::PropertyName = 10;
        }

4. **Constructor**

- Phải được khai báo trong *public*.
- Là một *phương thức* tự động được gọi đầu tiên khi khởi tạo *object* và không truy cập được thông qua *object* giống như *phương thức* bình thường.
- Tên *constructor* trùng với tên *class* và không có kiểu dữ liệu trả về.
- Có thể có *input parameter* hoặc không. Nếu có *input parameter* thì khi khởi tạo *object* phải truyền tham số vào giống như gọi hàm bình thường.
Nếu không có *input parameter* thì khi khởi tạo *object* không cần dấu `()` sau tên *object*.
- Nếu không khai báo *constructor*, mặc định vẫn có.
- Có thể được implement trong *class* hoặc bên ngoài *class* như *phương thức* bình thường nhưng không có dữ liệu trả về.

5. **Các đặc tính của lập trình hướng đối tượng**

Có 4 đặc tính: *kế thừa*, *trừu tượng*, *đa hình*, *đóng gói*.
- **_Tính kế thừa_**: Một class có thể sử dụng các *thuộc tính* và *phương thức* đặt trong phạm vi *public* hoặc *protected* của *class* khác mà không cần phải viết lại từ đầu.
Ví dụ: *class B* muốn có các *thuộc tính* và *phương thức* giống *class A* mà không phải viết lại từ đầu, khi đó *class B* sẽ *kế thừa* từ *class A*. Sử dụng 
toán tử `:`
          
      class ClassA:ClassB { 
          ...
      }
  Ngoài ra, *class B* cũng có thể ghi đè/implement lại *phương thức* kế thừa từ *class A*.
- **_Tính trừu tượng_**: người dùng chỉ cần tập trung vào đầu vào và đầu ra của dữ liệu cần xử lý, không cần biết dữ liệu đầu vào được xử lý ra làm sao để có được đầu ra.
Tức là người dùng chỉ cần gọi các *phương thức* ra sử dụng, sau đó nhận kết quả chứ không cần quan tâm phần implement của phương thức đó.
- **_Tính đa hình_**: các *phương thức* trong *class* có thể có cùng tên nhưng lại có thể cho ra các kết quả khác nhau, phụ thuộc vào kiểu trả về của *phương thức*, 
kiểu dữ liệu *input parameter* và thứ tự của chúng.

      class TinhTong {
          public:
              void tong(int, int);
              int tong(int, int);
              float tong(float, float);
      };
      ...
      int main() {
          TinhTong sum;
          sum.tong(1, 1);
          printf("%d", sum.tong(1, 1);
          printf("%f", sum.tong(1.1, 1.2);
      
          return 0;
      }
- **_Tính đóng gói_**: chỉ để lộ ra các dữ liệu mà người dùng cần, che dấu đi các dữ liệu cần thiết. Người dùng không thể tác động vào các dữ liệu bị che dấu mà chỉ bên
trong đối tượng đó mới có thể tác động. Do đó, đảm bảo được tính an toàn của đối tượng. Ví dụ:

      class Person {
          private:
              string _ten;
              int _tuoi;
              string _queQuan;
              int _sdt;
          public:
              Person(string, int, string, int);
              void hienThiThongTin();
              void suaThongTin(string, int, string, int);
      };
      ...
      int main() {
          Person A("Ngoc", 25, "Bac Ninh", 0987654321);
          A.hienThiThongTin();
          A.suaThongTin();
          A._ten;         //lỗi, không được phép
      
          return 0;
      }
Trong ví dụ trên, ta không thể truy cập trực tiếp vào các *thuộc tính* của *class Person* vì nó thuộc *private* mà phải thông qua các *phương thức* được *public*.
Do đó, các *thuộc tính* đã bị *đóng gói* không thể được truy xuất bằng cách thông thường `A._ten` mà phải thông qua *phương thức* được *public* thuộc *class Person*.
