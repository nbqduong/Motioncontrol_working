## 1. Phân tích Pic24fj256gb
- Chân MCLR có dùng để reset không? 
- Tiêu chuẩn nối mạch với các chân Pic
- Chân ENVReg dùng để hiệu chỉnh điện áp core logic, vì dòng pic này được thiết kế cho mức digital logic hoạt động ở 2.5V, cấp nguồn 3.3V cho chân để điều chỉnh mức điện áp hoạt động của core logic, để tăng tính ổn định thì mắc tụ gốm(đề nghị) vào chân V_DDCORE/V_CAP, hướng đãn ở mục 26.2 datasheet.
- Chân 36,37, VBUS, VUSB dùng để giao tiếp với máy tính thông qua cổng USB 2.0. Phần cứng ở đây dùng theo chế độ BUS POWER ONLY. Phần chức năng đề cập ở mục 18.0  
- Chân 31 và 32 sử dụng giao tiếp I2C với ... thông qua Header 20X2
### Chức năng của điện trở:
- Điện trở nối trực tiếp giữa nguồn và PIN để đảm bảo dòng điện đi vào PIN không vượt quá mức cho phép, theo công thức I=U/R, dòng điện đi vào càng nhỏ nếu R càng lớn. Thông thường dòng điện tối đa đi vào các chân khoảng vài chục mA.
### Chức năng của tụ điện
- Dùng như một acquy dự phòng, khi nguồn điện không ổn định hoặc bị cúp đột ngột, tụ sẽ phóng điện cung cấp điện áp tạm thời trong thời gian ngắn

### SST25VF040B-50-4I-S2AF 
- Đóng vai trò là bộ nhớ ngoài cho MCU
- Giao tiếp với MCU bằng chuẩn SPI
- Trong phiên bản hiện tại không dùng

### DS9638 được dùng làm driver?

### AM26LV32 dùng làm bộ ổn định?

### TLP281-4G dùng để cách ly truyền nhận tín hiệu, tránh cho điện áp của bên truyền ảnh hưởng(gây phá hủy hoặc nhiễu) cho bên nhận
- tín hiệu bên truyền là 24V, trong khi mạch điện chỉ sử dụng điện thế từ 3,3 - 5V, nếu không cách ly do nhiều nguyên nhân có thể dẫn đến việc điện áp rò rỉ qua gây hư mạch

### Vì sao I2C cần điện trở kéo lên
- https://mv-organizing.com/why-pull-up-and-pull-down-resistors-are-used/
- https://www.dientuhello.com/mot-so-khai-niem-can-ban-ve-gpio-cua-vi-dieu-khien-push-pull-va-open-drain/
- Nhưng tại sao không dùng mode High và low để điều khiển mà lại dùng mode high và open circuit - thiết kế loại này có lợi gì khi dùng vi điều khiển để điều khiển nhiều thiết bị? để đỡ phải dùng đến thanh ghi

## 2.Phân tích MCX 501
- Tại sao D0 tới D13 của từ PIC 24 nối qua MCX còn được nối thêm vào nguồn 3.3V, trong khi trong datasheet của MX501 thì có ghi khi những chân này không được dùng mới nên nối vô nguồn qua điện trở
- Chân [DCC](https://www.pulsemotor.com/global/Engineering/Glossary/deviation_counter_clear_signal.html)
- 
