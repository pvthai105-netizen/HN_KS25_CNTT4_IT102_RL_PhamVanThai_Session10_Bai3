# BÀI TẬP 03: PHÂN TÍCH TRADE-OFF TRONG C

## 1. Phân tích Input/Output

**Đầu vào (Input):**
- Thông tin khu vực vé: mã khu vực, tên khu vực, giá vé, sức chứa và số vé đã bán.
- Thông tin giao dịch: mã khu vực, số lượng vé mua và trạng thái Early Bird.
- Thông tin QR: mã QR, mã khu vực và trạng thái đã sử dụng.
- Số lượng khu vực và số lượng mã QR hiện có.

**Đầu ra (Output):**
- Giá vé sau khi áp dụng giảm giá Early Bird.
- Kết quả bán vé thành công hoặc thất bại.
- Số vé đã bán sau giao dịch.
- Kết quả check-in QR thành công hoặc thất bại.
- Thông báo lỗi khi số lượng mua không hợp lệ, khu vực không tồn tại, hết chỗ hoặc QR đã sử dụng.

## 2. Đề xuất hai giải pháp thiết kế

### Giải pháp 1: Gộp xử lý vào hàm main()

Toàn bộ việc kiểm tra số lượng, tính giá, kiểm tra sức chứa, cập nhật số vé đã bán và check-in được viết trực tiếp trong `main()`.

Ưu điểm:
- Dễ viết với chương trình rất nhỏ.
- Không cần thiết kế nhiều hàm.

Nhược điểm:
- Mã nguồn dài và khó đọc.
- Dễ lặp lại code.
- Khó kiểm thử từng chức năng riêng biệt.
- Khi thay đổi nghiệp vụ phải sửa nhiều đoạn code.

### Giải pháp 2: Chia chương trình thành các hàm riêng biệt

Tách các chức năng thành các hàm như `timKhuVuc()`, `tinhGiaVe()`, `banVe()` và `checkInQR()`.

Ưu điểm:
- Mỗi hàm đảm nhiệm một nhiệm vụ cụ thể.
- Có thể tái sử dụng hàm tìm kiếm.
- Dễ kiểm tra điều kiện biên và xử lý lỗi.
- Dễ bảo trì khi cần bổ sung nghiệp vụ.

Nhược điểm:
- Cần khai báo prototype và thiết kế tham số, giá trị trả về.
- Ban đầu cần thời gian để hiểu cách các hàm phối hợp với nhau.

## 3. Bảng so sánh

| Tiêu chí | Giải pháp 1: Gộp trong main | Giải pháp 2: Chia hàm |
|---|---|---|
| Tính đóng gói | Thấp | Cao hơn |
| Khả năng tái sử dụng | Thấp | Cao |
| Kiểm soát lỗi biên | Khó quản lý khi code dài | Dễ kiểm tra tại từng hàm |
| Độ phức tạp bảo trì | Cao khi chương trình mở rộng | Thấp hơn khi chương trình mở rộng |

## 4. Lựa chọn giải pháp

Chọn **Giải pháp 2: Chia chương trình thành các hàm riêng biệt**.

Lý do: Hệ thống có nhiều quy tắc nghiệp vụ độc lập như tính giá, kiểm tra tồn kho và check-in QR. Việc chia hàm giúp chương trình dễ đọc, hạn chế lỗi và thuận tiện mở rộng.

## 5. Danh sách Function Prototypes

- `int timKhuVuc(...)`: Tìm vị trí khu vực theo mã, trả về `-1` nếu không tìm thấy.
- `float tinhGiaVe(...)`: Tính giá vé sau giảm giá Early Bird.
- `int banVe(...)`: Kiểm tra điều kiện bán vé và cập nhật số vé đã bán.
- `int timQR(...)`: Tìm mã QR, trả về `-1` nếu không tìm thấy.
- `int checkInQR(...)`: Kiểm tra và cập nhật trạng thái QR.

## 6. Kết luận

Thiết kế theo hướng chia hàm giúp tách biệt trách nhiệm, tăng khả năng tái sử dụng và kiểm soát các lỗi nghiệp vụ. Các hàm trả về kết quả để `main()` thông báo trạng thái giao dịch.
