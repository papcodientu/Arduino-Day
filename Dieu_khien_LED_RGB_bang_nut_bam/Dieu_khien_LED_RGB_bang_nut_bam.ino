/*
Bật tắt đèn LED RGB dùng Arduino

Linh kiện:
1. Nút bấm
2. Đèn LED RGB 4 chân
3. Điện trở 10K và 220 Ohm

Cách hoạt động:
Khi bấm nút đèn LED sẻ chuyển từ màu đỏ --> xanh lá cây --> xanh nước biển --> màu trắng.

Các pin sử dụng:
1. Digital Pin 2: Nút bấm
2. Digital Pin 11: Chân đèn màu đỏ
3. Digital Pin 10: Chân đèn màu xanh lá cây
4. Digital Pin 9: Chân đèn màu xanh nước biển

Tác giả:
Công ty Cơ Điện Tử PAP
Website: http://papcodientu.com
Revison: 1.0
Date: 27-March-2015
*/
const int buttonPin = 2;  // nút bấm được kết nối vào cổng digital 2 của Arduino
int buttonState = LOW;  // trạng thái nút bấm hiện tại
int lastButtonState = HIGH;  // trạng thái nút bấm trước đó
long lastDebounceTime = 0;  // thời gian nút bấm trước đó
long debounceDelay = 50;  // độ trễ của nút bấm
int keyPressValue = 0;  // giá trị điều khiển đèn LED

const int redPin = 11;  // chân màu đỏ của đèn LED kết nối vào cổng digital 3 của Arduino
const int greenPin = 10;  // chân màu xanh lá cây của đèn LED kết nối vào cổng digital 5 của Arduino
const int bluePin = 9;  // chân màu xanh nước biển của đèn LED kết nối vào cổng digital 6 của Arduino

void setup() {
  Serial.begin(57600);  // khởi tạo cổng Serial với baudrate = 57600
  
  pinMode(buttonPin, INPUT);  // khai báo cổng 2 là đầu vào
  pinMode(redPin, OUTPUT);  // khai báo cổng 11 (đỏ), 10 (xanh lá cây), 9 (xanh nước biển) là đầu ra
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
 
  digitalWrite(redPin, HIGH); // ghi giá trị cao vào chân đỏ, xanh lá cây và xanh nước biển của đèn LED
  digitalWrite(greenPin, HIGH); // vì đèn LED là cực dương chung nên ghi giá trị cao 
  digitalWrite(bluePin, HIGH); // thì đèn sẽ tắt
}

void loop() {
  int reading = digitalRead(buttonPin);  // đọc giá trị nút nhấn
  
  if (reading != lastButtonState) {  // khi nút được nhấn
    lastDebounceTime = millis();   // cập nhật lại thời gian nút được nhấn
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {  // nút được nhấn sau khoản thời gian debounceDelay = 50ms
                                                        // tránh trường hợp nút bị nhấn nhiều lần trong khoảng thời gian ngắn
    if (reading != buttonState) { // trạng thái nút bấm bị thay đổi
      buttonState = reading;  // cập nhật lại trạng thái nút bấm
      //Serial.println(buttonState);
      
      if (buttonState == LOW) {  // nút được nhấn thì tăng giá trị keyPressValue lên 1
        keyPressValue += 1;  // nút bấm đọc giá trị thấp (LOW) do dùng điện trở kéo lên
        ///Serial.println(keyPressValue);
      }
    } 
  }
  
  switch(keyPressValue) {  // tùy vào giá trị của keyPressValue sẻ hiển thị đèn LED tương ứng
    case 1:
      analogWrite(redPin, 0);  // đèn LED đỏ sáng
      analogWrite(greenPin, 255);  // đèn xanh lá cây tắt
      analogWrite(bluePin, 255);  // đèn xanh nước biển tắt
      break;
    case 2:
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);  // đèn xanh lá cây sáng
      analogWrite(bluePin, 255);
      break;
    case 3:
      analogWrite(redPin, 255);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);  // đèn xanh nước biển sáng
      break;
    case 4:
      analogWrite(redPin, 0);  // cả 3 đèn đỏ, xanh lá cây và xanh nước biển đều sáng
      analogWrite(greenPin, 0);  // tạo ra ánh sáng trắng
      analogWrite(bluePin, 0);
      break;
    default:
     analogWrite(redPin, 255);  // các trường hợp còn lại thì đèn LED sẽ tắt
     analogWrite(greenPin, 255);
     analogWrite(bluePin, 255);
     keyPressValue = 0;  // cập nhật lại giá trị keyPressValue = 0
  }
  
  lastButtonState = reading;  // ghi lại trạng thái nút bấm trước
}
